// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved

#pragma once

#include <memory>
#include <vector>

#include "VSD3DStarter.h"
#include "Animation\Animation.h"
#include "Common\DeviceResources.h"
#include "Common\StepTimer.h"
#include "Common\Model.h"
#include "Common\Camera.h"

namespace StarterKit
{
	class Game
	{
	public:
		Game(const std::shared_ptr<DX::DeviceResources>& deviceResources);
		void CreateDeviceDependentResources();
		void CreateWindowSizeDependentResources();
		void ReleaseDeviceDependentResources();
		void Update(DX::StepTimer const& timer);
		void Render();

	

		void OnTapped(Windows::Foundation::Point Position);
		void OnPointerEntered(Windows::Foundation::Point Position);
		void OnPointerMoved(Windows::Foundation::Point Position);
		void OnPointerExited(Windows::Foundation::Point Position);
	    void OnKeyUp(Windows::System::VirtualKey Key);
		void OnKeyDown(Windows::System::VirtualKey Key);

	private:
		// Members used to keep track of the scene state.
		
		Model m_Model1;
		Model m_Model2;
		Model EnviromentModel;
		DX::Camera m_Camera;
		DX::Camera EnviromentCamera;

		
		std::vector<float> m_time;
		

		// Members used to keep track of the graphics state.
		VSD3DStarter::Graphics m_graphics;
		VSD3DStarter::LightConstants m_lightConstants;
		VSD3DStarter::MiscConstants m_miscConstants;

		// Cached pointer to device resources.
		std::shared_ptr<DX::DeviceResources> m_deviceResources;

		// Variables used with the rendering loop.
		bool m_loadingComplete;
	};
}