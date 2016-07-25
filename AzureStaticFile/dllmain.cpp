// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "stdio.h"
#include "httpext.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	return TRUE;
}

void WriteContext(EXTENSION_CONTROL_BLOCK *pECB, char *pszFormat, ...)
{
	char szBuffer[1024];
	va_list arg_ptr;
	va_start(arg_ptr, pszFormat);
	vsprintf_s(szBuffer, pszFormat, arg_ptr);
	va_end(arg_ptr);

	DWORD dwSize = strlen(szBuffer);
	pECB->WriteClient(pECB->ConnID, szBuffer, &dwSize, 0);
}

BOOL WINAPI GetExtensionVersion(HSE_VERSION_INFO *pVer) {
	pVer->dwExtensionVersion = HSE_VERSION;
	strncpy_s(pVer->lpszExtensionDesc, "Load static file from Azure storage", HSE_MAX_EXT_DLL_NAME_LEN);
	return TRUE;
}

DWORD WINAPI HttpExtensionProc(EXTENSION_CONTROL_BLOCK *pECB) {
	WriteContext(pECB, "pECB->lpszQueryString: %s", pECB->lpszQueryString);
	WriteContext(pECB, "pECB->lpszPathInfo: %s", pECB->lpszPathInfo);
	WriteContext(pECB, "pECB->lpszPathTranslated: %s", pECB->lpszPathTranslated);

	return HSE_STATUS_SUCCESS;
}