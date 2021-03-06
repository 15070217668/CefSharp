﻿// Copyright © 2010-2015 The CefSharp Authors. All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be found in the LICENSE file.

#pragma once

#include "include/cef_browser.h"
#include "include/cef_runnable.h"
#include "include/cef_v8.h"

#include "TypeUtils.h"
#include "Stdafx.h"
#include "JavascriptRootObjectWrapper.h"

using namespace CefSharp::Internals;
using namespace System;
using namespace System::ServiceModel;
using namespace System::Threading;
using namespace System::Threading::Tasks;

namespace CefSharp
{
    // "Master class" for wrapping everything that the Cef Subprocess needs 
    // for ONE CefBrowser.
    public ref class CefBrowserWrapper : DisposableResource
    {
    
    private:
        MCefRefPtr<CefBrowser> _cefBrowser;
        JavascriptCallbackRegistry^ _callbackRegistry;
        JavascriptRootObjectWrapper^ _javascriptRootObjectWrapper;

    public:
        CefBrowserWrapper(CefRefPtr<CefBrowser> cefBrowser);
        ~CefBrowserWrapper();

        property int BrowserId;
        property bool IsPopup;

        // This allows us to create the WCF proxies back to our parent process.
        property DuplexChannelFactory<IBrowserProcess^>^ ChannelFactory;

        // The serialized registered object data waiting to be used.
        property JavascriptRootObject^ JavascriptRootObject;

        property JavascriptRootObjectWrapper^ JavascriptRootObjectWrapper 
        {
            CefSharp::JavascriptRootObjectWrapper^ get();
            void set(CefSharp::JavascriptRootObjectWrapper^ value);
        };

        // The WCF proxy to the parent process.
        property IBrowserProcess^ BrowserProcess;

        JavascriptResponse^ EvaluateScriptInContext(CefRefPtr<CefV8Context> context, CefString script);

        virtual void DoDispose(bool disposing) override;

        virtual JavascriptResponse^ DoEvaluateScript(System::Int64 frameId, String^ script);

        JavascriptResponse^ DoCallback(System::Int64 callbackId, array<Object^>^ parameters);

        void DestroyJavascriptCallback(Int64 id);
    };
}
