#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include "PrimaryVolumeDescriptor.h"

std::vector<unsigned char> data;
PrimaryVolumeDescriptor primaryDescriptor;
DirectoryRecord rootDirectory;
std::string fileName;

void PrintRecursively(DirectoryRecord record);
std::vector<DirectoryRecord> GetSubRecords(DirectoryRecord record);

int main()
{
	std::string inStr = "";
	while(inStr != "exit")
	{
		std::cin >> inStr;
		auto file = std::fstream(inStr, std::ios::in | std::ios::binary);

		file.seekg(0, file.end);
		auto isoSize = file.tellg();
		file.seekg(0, file.beg);
		data = std::vector<unsigned char>(isoSize);

		// Read File
		if(isoSize > 0)
		{
			data.resize(isoSize);
			file.read((char*)&data[0], isoSize);
		}

		auto first = data.begin() + (16 * 2048);
		auto last = data.begin() + (17 * 2048);
		std::vector<unsigned char> sector(first, last);
		PrimaryVolumeDescriptor primaryDescriptor = PrimaryVolumeDescriptor(sector);
		primaryDescriptor.GetRootDirectory().SetFileIdentifier(inStr);
		PrintRecursively(primaryDescriptor.GetRootDirectory());
	}
	return 0;
}

void PrintRecursively(DirectoryRecord record)
{
	std::cout << record.GetFileIdentifier() << std::endl;
	if(record.IsDirectory())
	{
		std::cout << "Dir : " << record.GetFileIdentifier() << std::endl;
		for(auto iRecord : GetSubRecords(record))
		{
			PrintRecursively(iRecord);
		}
	}
}

std::vector<DirectoryRecord> GetSubRecords(DirectoryRecord record)
{
	std::vector<DirectoryRecord> list;

	if(!record.IsDirectory())
	{
		return list;
	}
	
	auto startSector = record.GetStartSector();
	auto first = data.begin() + (startSector * 2048);
	auto last = data.begin() + ((startSector + 1) * 2048);
	std::vector<unsigned char> sector(first, last);

	auto currentPosition = 0;
	DirectoryRecord tempRecord;
	for(int i = 0; i < 2; i++)
	{
		tempRecord = DirectoryRecord(&sector[currentPosition]);
		currentPosition += tempRecord.GetLength();
	}

	if(tempRecord.IsValidSector())
	{
		tempRecord = DirectoryRecord(&sector[currentPosition]);
		currentPosition += tempRecord.GetLength();
		while(tempRecord.IsValidSector())
		{
			list.push_back(tempRecord);
			tempRecord = DirectoryRecord(&sector[currentPosition]);
			currentPosition += tempRecord.GetLength();
		}

		if(!list.empty())
		{
			std::sort(list.begin(), list.end(), [](auto& firstRecord, auto& secondRecord) -> bool
				{
					return firstRecord.IsDirectory() && !secondRecord.IsDirectory();
				});
		}
	}

	return list;
}

