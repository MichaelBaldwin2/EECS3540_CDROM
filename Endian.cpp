#include "Endian.h"

int GetEndian()
{
	auto testValue = 0x12345678;
	auto charPtr = (unsigned char*)&testValue;
	return (*charPtr == 0x12) ? 1 : 0;
}