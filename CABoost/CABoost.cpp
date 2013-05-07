#include "CABoost.h"

::DWORD CABoost::DirectLaunchCA( ::HANDLE &out_CAProcHandle, ::DWORD &out_CAProcId )
{
	::DWORD Ret = 0;

	if( out_CAProcHandle == INVALID_HANDLE_VALUE )
		return Ret;

	::STARTUPINFO				CAStartUpInfo;
	::PROCESS_INFORMATION		CAProcInfo;

	::ZeroMemory( &CAStartUpInfo, sizeof( CAStartUpInfo ) );
	::ZeroMemory( &CAProcInfo, sizeof( CAProcInfo ) );

	CAStartUpInfo.cb = sizeof( CAStartUpInfo );

	if( ! ::CreateProcess( TEXT( "C:\\Nexon\\Combat Arms\\Engine.exe" ),
						   CA_ENGINE_CMD_LINE,
						   NULL,
						   NULL,
						   FALSE,
						   NULL,
						   NULL,
						   NULL,
						   &CAStartUpInfo,
						   &CAProcInfo ) )
	{
		Ret = ::GetLastError();
	} else {
		out_CAProcHandle = ::OpenProcess( PROCESS_ALL_ACCESS, FALSE, CAProcInfo.dwProcessId );
		out_CAProcId = CAProcInfo.dwProcessId;
		Ret = 1;
	}

	::CloseHandle( CAProcInfo.hThread );
	::CloseHandle( CAProcInfo.hProcess );

	return Ret;
};

::BOOL CABoost::LoadCABW( ::HANDLE &in_CAProcHandle )
{
	if( in_CAProcHandle == INVALID_HANDLE_VALUE )
		return -1;

	char		Buffer[ 50 ] = { 0 };
	::LPVOID	RemoteString = NULL;
	::LPVOID	LoadLibAddress = NULL;

	LoadLibAddress = ( ::LPVOID )::GetProcAddress( ::GetModuleHandle( "Kernel32.dll" ), "LoadLibraryA" );

	RemoteString = ( ::LPVOID )::VirtualAllocEx( in_CAProcHandle,
		NULL, strlen( "CABW.dll" ), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE );

	::WriteProcessMemory( in_CAProcHandle,
		( ::LPVOID )RemoteString, "CABW.dll", strlen( "CABW.dll" ), NULL );

	::CreateRemoteThread( in_CAProcHandle,
						  NULL,
						  NULL,
						  ( ::LPTHREAD_START_ROUTINE )LoadLibAddress,
						  ( ::LPVOID )RemoteString,
						  NULL,
						  NULL );

	::CloseHandle( in_CAProcHandle );

	return TRUE;
};