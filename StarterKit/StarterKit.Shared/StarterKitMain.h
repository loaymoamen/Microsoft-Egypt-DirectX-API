// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved

#pragma once

#include "Common\StepTimer.h"
#include "Common\DeviceResources.h"
#include "Content\SampleFpsTextRenderer.h"
#include "Game.h"

// Renders Direct2D and 3D content on the screen.
namespace StarterKit
{
	class StarterKitMain : public DX::IDeviceNotify
	{
	public:
		StarterKitMain(const std::shared_ptr<DX::DeviceResources>& deviceResources);
		~StarterKitMain();


		void CreateWindowSizeDependentResources();
		void StartRenderLoop();
		void StopRenderLoop();
		Concurrency::critical_section& GetCriticalSection() { return m_criticalSection; }

		// IDeviceNotify
		virtual void OnDeviceLost();
		virtual void OnDeviceRestored();

		void OnTapped(Windows::Foundation::Point Position);
		void OnPointerEntered(Windows::Foundation::Point Position);
		void OnPointerMoved(Windows::Foundation::Point Position);
		void OnPointerExited(Windows::Foundation::Point Position);
		void OnKeyUp(Windows::System::VirtualKey Key);
		void OnKeyDown(Windows::System::VirtualKey Key);

	private:
		void Update();
		bool Render();

		// Cached pointer to device resources.
		std::shared_ptr<DX::DeviceResources> m_deviceResources;

		// TODO: Replace with your own content renderers.
		std::unique_ptr<Game> m_sceneRenderer;
		std::unique_ptr<SampleFpsTextRenderer> m_fpsTextRenderer;

		Windows::Foundation::IAsyncAction^ m_renderLoopWorker;
		Concurrency::critical_section m_criticalSection;

		// Rendering loop timer.
		DX::StepTimer m_timer;
	};
}