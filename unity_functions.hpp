#pragma once

#include "includes.h"
#include "ntdef.h"

class unity_functions_t
{
public:

	double GetTimeSinceStartupInSecconds()
	{
		//double v0; // xmm0_8
		//LARGE_INTEGER PerformanceCount;
		//
		//uintptr_t dword_18181B020 = driver.Read<uintptr_t>(storage.unity_player + 0x181B020);
		//
		//uintptr_t qword_18181B018 = 0;
		//
		//if (dword_18181B020 > *(DWORD*)(*((QWORD*)NtCurrentTeb()->ThreadLocalStoragePointer + (unsigned int)tls_index) + 0i64))
		//{
		//	//Init_thread_header(&dword_18181B020);
		//	if (dword_18181B020 == -1)
		//	{
		//		PerformanceCount.QuadPart = 0i64;
		//		QueryPerformanceCounter(&PerformanceCount);
		//		qword_18181B018 = PerformanceCount.QuadPart;
		//		//Init_thread_footer(&dword_18181B020);
		//	}
		//}
		//
		//PerformanceCount.QuadPart = 0i64;
		//QueryPerformanceCounter(&PerformanceCount);
		//v0 = (double)(PerformanceCount.LowPart - (int)qword_18181B018);
		//if (PerformanceCount.QuadPart - qword_18181B018 < 0)
		//	v0 = v0 + 1.844674407370955e19;
		////return v0 * *(double*)&Baselib_Timer_TickToNanosecondsConversionFactor / 1000000000.0;
	}
}unity_functions;