#include "Std.h"
#include "CABoost.h"
#include "Res.h"

int main() {
	::SetConsoleTitle( "CABoost 1.0 - Beta ~ Written By Kernel.Win@aol.com" );

	::HANDLE CAProcHandle = NULL;
	::DWORD CAProcId = NULL;
	::DWORD CALaunchRet = NULL;
	::DWORD LoadCABWRet = NULL;

	std::cout << "CABoost 1.0 - Beta\n";
	std::cout << "Written By Kernel.Win@aol.com\n\n";

	std::cout << "Attempting to directly launch Engine.exe (CA)...\n";
	if( ( CALaunchRet = CABoost::DirectLaunchCA( CAProcHandle, CAProcId ) ) == 1 )
	{
		std::cout << "\t\tSuccess!\n";

		std::cout << "Attempting to load CABW.dll...\n";
		if( ( LoadCABWRet = CABoost::LoadCABW( CAProcHandle ) ) == FALSE )
		{
			std::printf( "An error has occured: Unable to load CABW.dll...\n\tError Code = %i\n",
						 LoadCABWRet );
		} else { std::cout << "\t\tSuccess!\n"; }
	}
	else {
		std::printf( "An error has occured: Unable to directly launch CA (Engine.exe)...\n\tError Code = %i\n",
					 CALaunchRet );
	}

	::CloseHandle( CAProcHandle );

	::Sleep( 20000 );
	return 0;
};