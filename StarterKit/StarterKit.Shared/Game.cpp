
#include "pch.h"
#include "Game.h"

#include "Common\DirectXHelper.h"
#include "HitTestingHelpers.h"

using namespace StarterKit;

using namespace DirectX;
using namespace Microsoft::WRL;
using namespace Platform;
using namespace Windows::Foundation;
using namespace VSD3DStarter;

// Loads vertex and pixel shaders from files and instantiates the cube geometry.
Game::Game(const std::shared_ptr<DX::DeviceResources>& deviceResources) :
m_loadingComplete(false),
m_deviceResources(deviceResources)
{
	CreateDeviceDependentResources();
	CreateWindowSizeDependentResources();
}

// Loads meshes and other resources that depend on the device, but not on window size.
void Game::CreateDeviceDependentResources()
{
	m_graphics.Initialize(m_deviceResources->GetD3DDevice(), m_deviceResources->GetD3DDeviceContext(), m_deviceResources->GetDeviceFeatureLevel());

	// Set DirectX to not cull any triangles so the entire mesh will always be shown.
	CD3D11_RASTERIZER_DESC d3dRas(D3D11_DEFAULT);
	d3dRas.CullMode = D3D11_CULL_NONE;
	d3dRas.MultisampleEnable = true;
	d3dRas.AntialiasedLineEnable = true;

	ComPtr<ID3D11RasterizerState> p3d3RasState;
	m_deviceResources->GetD3DDevice()->CreateRasterizerState(&d3dRas, &p3d3RasState);
	m_deviceResources->GetD3DDeviceContext()->RSSetState(p3d3RasState.Get());



	auto task1 = m_Model1.LoadAsync(m_graphics, L"saucer.cmo");
	auto task2 = EnviromentModel.LoadAsync(m_graphics, L"Scene.cmo");
	auto task3 = m_Model2.LoadAsync(m_graphics, L"tank.cmo");
	(task1&&task2&&task3).then([this]()
	{
		EnviromentModel.TranslateX(EnviromentCamera.GetPosition().x);
		EnviromentModel.TranslateY(EnviromentCamera.GetPosition().y);
		EnviromentModel.TranslateZ(EnviromentCamera.GetPosition().z);
		EnviromentModel.ScaleX(5);
		EnviromentModel.ScaleY(5);
		EnviromentModel.ScaleZ(5);

		m_Model1.Translate(10.0f, 0.0f ,4.0f);
		m_Model1.Scale(0.2f, 0.2f, 0.2f);
		
		// Scene is ready to be rendered.
		m_loadingComplete = true;
	});
}

// Initializes view parameters when the window size changes.
void Game::CreateWindowSizeDependentResources()
{
	m_miscConstants.ViewportHeight = m_deviceResources->GetScreenViewport().Height;
	m_miscConstants.ViewportWidth = m_deviceResources->GetScreenViewport().Width;
	m_graphics.UpdateMiscConstants(m_miscConstants);

	Size outputSize = m_deviceResources->GetOutputSize();

	float aspectRatio = outputSize.Width / outputSize.Height;
	float fovAngleY = 70.0f * XM_PI / 180.0f;

	XMFLOAT3 up;
	if (aspectRatio < 1.0f)
	{
		// Portrait or snap view
		up = XMFLOAT3(1.0f, 0.0f, 0.0f);
		fovAngleY = 120.0f * XM_PI / 180.0f;
	}
	else
	{
		//Landscape view.
		up = XMFLOAT3(0.0f, 1.0f, 0.0f);
	}


	m_Camera.SetLens(fovAngleY, aspectRatio, m_deviceResources->GetOrientationTransform3D(), 1.00f, 1000.0f);
	m_Camera.LookAt(XMFLOAT3(0.0f, 0.0f, -13.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), up);
	m_Camera.UpdateViewMatrix();

	EnviromentCamera.SetLens(fovAngleY, aspectRatio, m_deviceResources->GetOrientationTransform3D(), 1.00f, 1000.0f);
	EnviromentCamera.LookAt(XMFLOAT3(0.0f, 0.0f, -20.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, -1.0f, 0.0f));
	EnviromentCamera.UpdateViewMatrix();

	EnviromentModel.TranslateX(EnviromentCamera.GetPosition().x);
	EnviromentModel.TranslateY(EnviromentCamera.GetPosition().y);
	EnviromentModel.TranslateZ(EnviromentCamera.GetPosition().z);

	// Setup lightinUpdateViewMatrix();g for our scene.
	static const XMVECTORF32 s_vPos = { 5.0f, 5.0f, -2.5f, 0.f };

	XMFLOAT4 dir;
	DirectX::XMStoreFloat4(&dir, XMVector3Normalize(s_vPos));

	m_lightConstants.ActiveLights = 1;
	m_lightConstants.Ambient = XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f);
	m_lightConstants.IsPointLight[0] = false;
	m_lightConstants.LightColor[0] = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
	m_lightConstants.LightDirection[0] = dir;
	m_lightConstants.LightSpecularIntensity[0].x = 2;

	m_graphics.UpdateLightConstants(m_lightConstants);
}

// Release resources that depend on the device. Called when the device is released.
void Game::ReleaseDeviceDependentResources()
{
	m_loadingComplete = false;
}

// Called once per frame, updates the scene state.
void Game::Update(DX::StepTimer const& timer)
{
	auto timeDelta = static_cast<float>(timer.GetElapsedSeconds());



	//m_model2.UpdateAnimation(timeDelta);

	// Update the "time" variable for the glow effect.
	for (float &time : m_time)
	{
		time = std::max<float>(0.0f, time - timeDelta);
	}
}

// Renders one frame using the Starter Kit helpers.
void Game::Render()
{
	// Loading is asynchronous. Only draw geometry after it's loaded.
	if (!m_loadingComplete)
	{
		return;
	}

	auto context = m_deviceResources->GetD3DDeviceContext();

	// Set render targets to the screen.
	auto rtv = m_deviceResources->GetBackBufferRenderTargetView();
	auto dsv = m_deviceResources->GetDepthStencilView();
	ID3D11RenderTargetView *const targets[1] = { rtv };
	context->OMSetRenderTargets(1, targets, dsv);

	
	
	EnviromentModel.Render(m_graphics, EnviromentCamera);
	m_Model1.Render(m_graphics, m_Camera);
	m_Model2.Render(m_graphics, m_Camera);
	
}


void Game::OnTapped(Windows::Foundation::Point Position)
{

}

void Game::OnPointerEntered(Windows::Foundation::Point Position)
{

}

void Game::OnPointerMoved(Windows::Foundation::Point Position)
{

}

void Game::OnPointerExited(Windows::Foundation::Point Position)
{

}
void Game::OnKeyUp(Windows::System::VirtualKey Key)
{

}
void Game::OnKeyDown(Windows::System::VirtualKey Key)
{

}