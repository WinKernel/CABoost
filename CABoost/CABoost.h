#ifndef CABOOST_H
#define CABOOST_H

#ifdef UNICODE
#	undef UNICODE
#endif

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>

#define CA_ENGINE_CMD_LINE		"Engine.exe								\
								-windowtitle		CombatArms			\
								-rez				Engine.REZ			\
								-rez				Game				\
								-authip				8.31.100.207		\
								-authport			10001				\
								-pcroom				0					\
								-Ver				VER_US_1304.04		\
								-UserId				0"

namespace CABoost
{
	::DWORD DirectLaunchCA( ::HANDLE &out_CAProcHandle, ::DWORD &out_CAProcId );
	::BOOL LoadCABW( ::HANDLE &in_CAProcHandle );
};

#endif // CABOOST_H