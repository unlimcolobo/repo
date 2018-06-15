#include <SDKDDKVer.h>
#include <tchar.h>
#include <msxml6.h>
#include <wrl.h>
#include "XMLHttpRequest2Callback.h"

using namespace Microsoft::WRL;

VOID Get()
{
    HRESULT hr = S_OK;
    DWORD dwStatus = 0;
    BOOL fAbort = TRUE;
    ComPtr<IXMLHTTPRequest2> spXHR;
    ComPtr<CXMLHttpRequest2Callback> spXhrCallback;
    hr = CoCreateInstance(CLSID_FreeThreadedXMLHTTP60,NULL,CLSCTX_INPROC_SERVER,IID_PPV_ARGS(&spXHR));
    if(FAILED(hr)) goto Exit;
    hr = MakeAndInitialize<CXMLHttpRequest2Callback>(&spXhrCallback);
    if(FAILED(hr)) goto Exit;
    hr = spXhrCallback->WaitForComplete(&dwStatus);
    if(FAILED(hr)) goto Exit;
    fAbort = FALSE;
Exit:
    if(FAILED(hr)) wprintf(L"Failed, Error code = 0x%08x.\n", hr);
    else wprintf(L"Succeed, Status code = %u.\n", dwStatus);
    if(fAbort) spXHR->Abort();
}

int __cdecl wmain(int argc, _In_reads_(argc) WCHAR **argv)
{
    HRESULT hr = S_OK;
    BOOL fCoInit = FALSE;
    if(argc != 2)
    {
        wprintf(L"Usage: %s <Url>\n", argv[0]);
        goto Exit;
    }
    hr = CoInitializeEx(NULL,COINIT_MULTITHREADED);
    if(FAILED(hr)) goto Exit;
    fCoInit = TRUE;
    Get(argv[1]);
Exit:
    if(fCoInit)
    {
        CoUninitialize();
        fCoInit = FALSE;
    }
    return 0;
}
