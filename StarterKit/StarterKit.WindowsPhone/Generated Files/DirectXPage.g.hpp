﻿

//------------------------------------------------------------------------------
//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
//------------------------------------------------------------------------------
#include "pch.h"
#include "DirectXPage.xaml.h"




void ::StarterKit::DirectXPage::InitializeComponent()
{
    if (_contentLoaded)
        return;

    _contentLoaded = true;

    // Call LoadComponent on ms-appx:///DirectXPage.xaml
    ::Windows::UI::Xaml::Application::LoadComponent(this, ref new ::Windows::Foundation::Uri(L"ms-appx:///DirectXPage.xaml"), ::Windows::UI::Xaml::Controls::Primitives::ComponentResourceLocation::Application);

    // Get the SwapChainPanel named 'swapChainPanel'
    swapChainPanel = safe_cast<::Windows::UI::Xaml::Controls::SwapChainPanel^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"swapChainPanel"));
}

void ::StarterKit::DirectXPage::Connect(int connectionId, Platform::Object^ target)
{
    switch (connectionId)
    {
    case 1:
        (safe_cast<::Windows::UI::Xaml::UIElement^>(target))->Tapped +=
            ref new ::Windows::UI::Xaml::Input::TappedEventHandler(this, (void (::StarterKit::DirectXPage::*)(Platform::Object^, Windows::UI::Xaml::Input::TappedRoutedEventArgs^))&DirectXPage::OnTapped);
        (safe_cast<::Windows::UI::Xaml::UIElement^>(target))->PointerEntered +=
            ref new ::Windows::UI::Xaml::Input::PointerEventHandler(this, (void (::StarterKit::DirectXPage::*)(Platform::Object^, Windows::UI::Xaml::Input::PointerRoutedEventArgs^))&DirectXPage::OnPointerEntered);
        (safe_cast<::Windows::UI::Xaml::UIElement^>(target))->PointerMoved +=
            ref new ::Windows::UI::Xaml::Input::PointerEventHandler(this, (void (::StarterKit::DirectXPage::*)(Platform::Object^, Windows::UI::Xaml::Input::PointerRoutedEventArgs^))&DirectXPage::OnPointerMoved);
        (safe_cast<::Windows::UI::Xaml::UIElement^>(target))->PointerExited +=
            ref new ::Windows::UI::Xaml::Input::PointerEventHandler(this, (void (::StarterKit::DirectXPage::*)(Platform::Object^, Windows::UI::Xaml::Input::PointerRoutedEventArgs^))&DirectXPage::OnPointerExited);
        break;
    }
    (void)connectionId; // Unused parameter
    (void)target; // Unused parameter
    _contentLoaded = true;
}

