/**
**    Hatchit Engine
**    Copyright(c) 2015 Third-Degree
**
**    GNU Lesser General Public License
**    This file may be used under the terms of the GNU Lesser
**    General Public License version 3 as published by the Free
**    Software Foundation and appearing in the file LICENSE.LGPLv3 included
**    in the packaging of this file. Please review the following information
**    to ensure the GNU Lesser General Public License requirements
**    will be met: https://www.gnu.org/licenses/lgpl.html
**
**/

#pragma once

#include <ht_platform.h>
#include <ht_window.h>

typedef ABI::Windows::Foundation::ITypedEventHandler<ABI::Windows::ApplicationModel::Core::CoreApplicationView *,
    ABI::Windows::ApplicationModel::Activation::IActivatedEventArgs*>
    IActivatedEventHandler;

namespace Hatchit
{
    namespace Game
    {
        class HT_API UWAWindow : public ABI::Windows::ApplicationModel::Core::IFrameworkView,
                                 public ABI::Windows::ApplicationModel::Core::IFrameworkViewSource,
                                 IActivatedEventHandler
        {
        public:
            UWAWindow();

            ~UWAWindow();

            // Inherited via IFrameworkView
            virtual HRESULT Initialize(ABI::Windows::ApplicationModel::Core::ICoreApplicationView * applicationView) override;
            virtual HRESULT SetWindow(ABI::Windows::UI::Core::ICoreWindow * window) override;
            virtual HRESULT Load(HSTRING entryPoint) override;
            virtual HRESULT Run(void) override;
            virtual HRESULT Uninitialize(void) override;

            virtual HRESULT Invoke(ABI::Windows::ApplicationModel::Core::ICoreApplicationView* view,
                ABI::Windows::ApplicationModel::Activation::IActivatedEventArgs* args) override;

            virtual HRESULT QueryInterface(REFIID riid, void ** ppvObject) override;
            virtual ULONG AddRef(void) override;
            virtual ULONG Release(void) override;
            virtual HRESULT GetIids(ULONG * iidCount, IID ** iids) override;
            virtual HRESULT GetRuntimeClassName(HSTRING * className) override;
            virtual HRESULT GetTrustLevel(TrustLevel * trustLevel) override;
        
            // Inherited via IFrameworkViewSource
            virtual HRESULT CreateView(ABI::Windows::ApplicationModel::Core::IFrameworkView ** viewProvider) override;
        
        protected:
            // Application lifecycle event handlers.
            void OnActivated(ABI::Windows::ApplicationModel::Core::CoreApplicationView* applicationView, ABI::Windows::ApplicationModel::Activation::IActivatedEventArgs* args);
            void OnSuspending(void* sender, ABI::Windows::ApplicationModel::SuspendingEventArgs* args);
            void OnResuming(void* sender, void* args);

            // Window event handlers.
            void OnWindowSizeChanged(ABI::Windows::UI::Core::CoreWindow* sender, ABI::Windows::UI::Core::WindowSizeChangedEventArgs* args);
            void OnVisibilityChanged(ABI::Windows::UI::Core::CoreWindow* sender, ABI::Windows::UI::Core::VisibilityChangedEventArgs* args);
            void OnWindowClosed(ABI::Windows::UI::Core::CoreWindow* sender, ABI::Windows::UI::Core::CoreWindowEventArgs* args);

            // DisplayInformation event handlers.
            void OnDpiChanged(ABI::Windows::Graphics::Display::DisplayInformation* sender, void* args);
            void OnOrientationChanged(ABI::Windows::Graphics::Display::DisplayInformation* sender, void* args);
            void OnDisplayContentsInvalidated(ABI::Windows::Graphics::Display::DisplayInformation* sender, void* args);

        private:
            bool m_closed;
            bool m_visible;
            uint32_t m_refCnt;
            ABI::Windows::UI::Core::ICoreWindow*        m_window;
            ABI::Windows::UI::Core::ICoreDispatcher*    m_dispatcher;
            

        };


    }
}