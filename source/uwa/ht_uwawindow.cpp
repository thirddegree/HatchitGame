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

#include <ht_uwawindow.h>
#include <cassert>
#include <windows.foundation.h>
#include <windows.foundation.collections.h>

using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::ApplicationModel::Core;


typedef ITypedEventHandler<ABI::Windows::ApplicationModel::Core::CoreApplicationView*,
    ABI::Windows::ApplicationModel::Activation::IActivatedEventArgs*> ActivatedEventHandler;

namespace Hatchit
{
    namespace Game
    {
        UWAWindow::UWAWindow()
            : m_refCnt(0)
        {
            m_window = nullptr;
        }
      
        UWAWindow::~UWAWindow()
        {
            if (m_window)
            {
                m_window->Release();
                m_window = nullptr;
            }
        }

        HRESULT UWAWindow::Initialize(ABI::Windows::ApplicationModel::Core::ICoreApplicationView * applicationView)
        {
            EventRegistrationToken token;
            applicationView->add_Activated(this, &token);

            return S_OK;
        }
        HRESULT UWAWindow::SetWindow(ABI::Windows::UI::Core::ICoreWindow * window)
        {
            m_window = window;

            return S_OK;
        }
        HRESULT UWAWindow::Load(HSTRING entryPoint)
        {
            return S_OK;
        }
        HRESULT UWAWindow::Run(void)
        {
            m_window->get_Dispatcher(&m_dispatcher);

            m_dispatcher->ProcessEvents(ABI::Windows::UI::Core::CoreProcessEventsOption_ProcessUntilQuit);

            return E_NOTIMPL;
        }
        HRESULT UWAWindow::Uninitialize(void)
        {
            return S_OK;
        }

        HRESULT UWAWindow::Invoke(ABI::Windows::ApplicationModel::Core::ICoreApplicationView * view, ABI::Windows::ApplicationModel::Activation::IActivatedEventArgs * args)
        {
            m_window->Activate();

            return S_OK;
        }

        void UWAWindow::OnActivated(ABI::Windows::ApplicationModel::Core::CoreApplicationView * applicationView, ABI::Windows::ApplicationModel::Activation::IActivatedEventArgs * args)
        {
        }
        void UWAWindow::OnSuspending(void * sender, ABI::Windows::ApplicationModel::SuspendingEventArgs * args)
        {
        }
        void UWAWindow::OnResuming(void * sender, void * args)
        {
        }
        void UWAWindow::OnWindowSizeChanged(ABI::Windows::UI::Core::CoreWindow * sender, ABI::Windows::UI::Core::WindowSizeChangedEventArgs * args)
        {
        }
        void UWAWindow::OnVisibilityChanged(ABI::Windows::UI::Core::CoreWindow * sender, ABI::Windows::UI::Core::VisibilityChangedEventArgs * args)
        {
        }
        void UWAWindow::OnWindowClosed(ABI::Windows::UI::Core::CoreWindow * sender, ABI::Windows::UI::Core::CoreWindowEventArgs * args)
        {
        }
        void UWAWindow::OnDpiChanged(ABI::Windows::Graphics::Display::DisplayInformation * sender, void * args)
        {
        }
        void UWAWindow::OnOrientationChanged(ABI::Windows::Graphics::Display::DisplayInformation * sender, void * args)
        {
        }
        void UWAWindow::OnDisplayContentsInvalidated(ABI::Windows::Graphics::Display::DisplayInformation * sender, void * args)
        {
        }
        HRESULT UWAWindow::CreateView(ABI::Windows::ApplicationModel::Core::IFrameworkView ** viewProvider)
        {
            assert(viewProvider);

            *viewProvider = this;
            (*viewProvider)->AddRef();

            return S_OK;
        }

        HRESULT UWAWindow::QueryInterface(REFIID riid, void ** ppvObject)
        {
            assert(ppvObject);
            if (riid == __uuidof(IFrameworkViewSource) ||
                riid == __uuidof(IInspectable) ||
                riid == __uuidof(IUnknown))
            {
                *ppvObject = static_cast<IFrameworkViewSource*>(this);
            }
            else if (riid == __uuidof(IFrameworkView))
            {
                *ppvObject = static_cast<IFrameworkView*>(this);
            }
            else
            {
                *ppvObject = nullptr;
                return E_NOINTERFACE;
            }
            static_cast<IUnknown*>(*ppvObject)->AddRef();

            return S_OK;
        }

        ULONG UWAWindow::AddRef(void)
        {
            InterlockedIncrement(&m_refCnt);

            return m_refCnt;
        }

        ULONG UWAWindow::Release(void)
        {
            ULONG refCount = InterlockedDecrement(&m_refCnt);
            if (refCount == 0)
                delete this;

            return refCount;
        }

        HRESULT UWAWindow::GetIids(ULONG * iidCount, IID ** iids)
        {
            return E_NOTIMPL;
        }
        HRESULT UWAWindow::GetRuntimeClassName(HSTRING * className)
        {
            return E_NOTIMPL;
        }
        HRESULT UWAWindow::GetTrustLevel(TrustLevel * trustLevel)
        {
            return E_NOTIMPL;
        }
    }
}