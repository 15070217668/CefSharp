﻿// Copyright © 2010-2015 The CefSharp Authors. All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be found in the LICENSE file.

using System;
using System.Threading.Tasks;

namespace CefSharp
{
    public interface IBrowserHost : IDisposable
    {
        void StartDownload(string url);
        void Print();
        void SetZoomLevel(double zoomLevel);
        Task<double> GetZoomLevelAsync();
        IntPtr GetWindowHandle();
        void CloseBrowser(bool forceClose);
        
        void ShowDevTools();
        void CloseDevTools();

        void AddWordToDictionary(string word);
        void ReplaceMisspelling(string word);

        void Find(int identifier, string searchText, bool forward, bool matchCase, bool findNext);
        void StopFinding(bool clearSelection);
    }
}
