#include "Helpers.h"

static std::mt19937 s_randomNumberGenerator;
static std::recursive_mutex s_rngLock;
static bool s_rngSeeded = false;

INLINE time_t getMSTime()
{
#ifdef _WIN32
#if WINVER >= 0x0600
	typedef ULONGLONG(WINAPI* GetTickCount64_t)(void);
	static GetTickCount64_t pGetTickCount64 = nullptr;

	if (!pGetTickCount64)
	{
		HMODULE hModule = LoadLibraryA("KERNEL32.DLL");
		pGetTickCount64 = (GetTickCount64_t)GetProcAddress(hModule, "GetTickCount64");
		if (!pGetTickCount64)
			pGetTickCount64 = (GetTickCount64_t)GetTickCount;
		FreeLibrary(hModule);
	}

	return pGetTickCount64();
#else
	return GetTickCount();
#endif
#else
	struct timeval tv;
	gettimeofday(&tv, nullptr);
	return (tv.tv_sec * SECOND) + (tv.tv_usec / SECOND);
#endif
}

INLINE void SeedRNG()
{
	if (!s_rngSeeded)
	{
		s_randomNumberGenerator.seed((unsigned long)getMSTime());
		s_rngSeeded = true;
	}
}

int32 myrand(int32 min, int32 max)
{
	Guard lock(s_rngLock);
	SeedRNG();
	if (min > max) std::swap(min, max);
	std::uniform_int_distribution<int32> dist(min, max);
	return dist(s_randomNumberGenerator);
}

uint64 RandUInt64()
{
	Guard lock(s_rngLock);
	SeedRNG();
	std::uniform_int_distribution<uint64> dist;
	return dist(s_randomNumberGenerator);
}