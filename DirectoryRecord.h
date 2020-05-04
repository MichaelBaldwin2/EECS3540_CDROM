#pragma once

#include <string>

class DirectoryRecord
{
public:
	DirectoryRecord();
	DirectoryRecord(unsigned char* block);
	int GetLength();
	std::string GetFileIdentifier();
	void SetFileIdentifier(std::string fileIdentifier);
	int GetStartSector();
	bool IsValidSector();
	int GetDataLength();
	unsigned char GetFileFlags();
	unsigned char GetFileUnitSize();
	unsigned char GetInterleaveSize();
	short GetVolumeSeqNbr();
	bool IsDirectory();

private:
	unsigned char length;       // The length of this directory record in bytes.
	unsigned char extendedAttributeRecordLength;
	int startSector[2];
	int dataLength[2];
	unsigned char dateAndTime[7];
	unsigned char fileFlags;
	unsigned char fileUnitSize;
	unsigned char interleaveSize;
	short volumeSeqNbr[2];
	unsigned char fileIDLength;
	std::string fileIdentifier;
	unsigned char padding;
};
