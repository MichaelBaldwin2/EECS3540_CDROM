#include "DirectoryRecord.h"
#include <iostream>
#include <ostream>
#include <string>
#include "Endian.h"

DirectoryRecord::DirectoryRecord() : length(), extendedAttributeRecordLength(), startSector{ -1, -1 }, dataLength(), dateAndTime(), fileFlags(), fileUnitSize(), interleaveSize(), volumeSeqNbr(), fileIDLength(), fileIdentifier(), padding()
{
}

DirectoryRecord::DirectoryRecord(unsigned char* block) : DirectoryRecord()
{
	length = block[0];
	extendedAttributeRecordLength = block[1];
	startSector[0] = *((int32_t*)&block[2]);
	startSector[1] = *((int32_t*)&block[6]);
	dataLength[0] = *((int32_t*)&block[10]);
	dataLength[1] = *((int32_t*)&block[14]);

	for(int i = 0; i < 6; i++)
	{
		dateAndTime[i] = block[18 + i];
	}

	fileFlags = block[25];
	fileUnitSize = block[26];
	interleaveSize = block[27];
	fileIDLength = block[32];

	unsigned char* buffer = new unsigned char[fileIDLength + 1];
	buffer[fileIDLength] = '\0';
	for(int i = 0; i < fileIDLength; i++)
	{
		buffer[i] = block[33 + i];
	}

	fileIdentifier = std::string((char*)buffer);
	delete[] buffer;
}

int DirectoryRecord::GetLength()
{
	return length;
}

std::string DirectoryRecord::GetFileIdentifier()
{
	return fileIdentifier;
}

void DirectoryRecord::SetFileIdentifier(std::string fileIdentifier)
{
	this->fileIdentifier = fileIdentifier;
}

int DirectoryRecord::GetStartSector()
{
	return startSector[GetEndian()];
}

bool DirectoryRecord::IsValidSector()
{
	return GetStartSector() > 0;
}

int DirectoryRecord::GetDataLength()
{
	return dataLength[GetEndian()];
}

unsigned char DirectoryRecord::GetFileFlags()
{
	return fileFlags;
}

unsigned char DirectoryRecord::GetFileUnitSize()
{
	return fileUnitSize;
}

unsigned char DirectoryRecord::GetInterleaveSize()
{
	return interleaveSize;
}

short DirectoryRecord::GetVolumeSeqNbr()
{
	return volumeSeqNbr[GetEndian()];
}

bool DirectoryRecord::IsDirectory()
{
	return ((fileFlags & 0x02) != 0);
}

