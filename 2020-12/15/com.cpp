// Compile with -- cl /Zi /D "WIN32" /D "_WINDOWS" /D "_UNICODE" /D "UNICODE" com.cpp ole32.lib user32.lib

#include <windows.h>
#include <shobjidl.h>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow) {
	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

	if (SUCCEEDED(hr)) {
		IFileOpenDialog *pFileOpen = NULL;
		hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_IFileOpenDialog, (void**)(&pFileOpen));

		if (SUCCEEDED(hr)) {
			hr = pFileOpen->Show(NULL);

			if (SUCCEEDED(hr)) {
				IShellItem *pItem = NULL;
				hr = pFileOpen->GetResult(&pItem);

				if (SUCCEEDED(hr)) {
					PWSTR pszFilePath = NULL;
					hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

					if (SUCCEEDED(hr)) {
						MessageBoxW(NULL, pszFilePath, L"Tarek is showing you the file path!", MB_OK | MB_ICONINFORMATION);
						CoTaskMemFree(pszFilePath);
					}
					pItem->Release();
				}
			}

			pFileOpen->Release();
		}

		CoUninitialize();
	}

	return 0;
}