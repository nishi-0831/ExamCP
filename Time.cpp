#include "time.h"
#include <Windows.h>
#include <stdlib.h>
#include <time.h>

namespace {
	LARGE_INTEGER freq;
	LARGE_INTEGER current;
	float deltaTime;
};
void Time::Init()
{
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&current);
}

void Time::Refresh()
{
	LARGE_INTEGER last = current;
	QueryPerformanceCounter(&current);
	deltaTime = static_cast<float >(current.QuadPart - last.QuadPart) / freq.QuadPart;
}

float Time::DeltaTime()
{
	return deltaTime;
}

int Time::Random(int max)
{
	srand((unsigned int)time(NULL)); // Œ»İ‚Ìî•ñ‚Å‰Šú‰»
	return (rand() % max); 
}
