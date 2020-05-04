#pragma once

#include <string>
#include <vector>

#include "DirectoryRecord.h"
#include "DescriptorDateAndTime.h"

class PrimaryVolumeDescriptor
{
public:
	PrimaryVolumeDescriptor();
	PrimaryVolumeDescriptor(std::vector<unsigned char> data);

	unsigned char GetType();
	std::string GetSystemID();
	std::string GetVolumeID();
	int GetVolumeSpace();
	int GetVolumeSet();
	int GetVolumeSeq();
	int GetLPathTableLocation();
	int GetMPathTableLocatgion();
	int GetOptLPathTableLocation();
	int GetOptMPathTableLocation();
	std::string GetVolumeSetID();
	std::string GetPublisherID();
	std::string GetDataPreparerID();
	std::string GetApplicationID();
	std::string GetCopyrightFileID();
	std::string GetBibliographyFileID();
	std::string GetAbstractFileID();
	DirectoryRecord &GetRootDirectory();
	DescriptorDateAndTime GetCreationDateAndTime();
	DescriptorDateAndTime GetModificationDateAndTime();
	DescriptorDateAndTime GetEffectiveDateAndTime();
	DescriptorDateAndTime GetExpirationDateAndTime();

private:
	unsigned char descriptortype;
	unsigned char standardID[5];
	unsigned char version;
	std::string systemID;
	std::string volumeID;
	int volumeSpace[2];
	short volumeSet[2];
	short volumeSeq[2];
	short logicalBlockSize[2];
	int pathTableSize[2];
	int lPathTableLoc;
	int optLPathTableLoc;
	int mPathTableLoc;
	int optMPathTableLoc;
	DirectoryRecord  rootDirectory;
	std::string volumeSetID;
	std::string publisherID;
	std::string dataPreparerID;
	std::string applicationID;
	std::string copyrightFileID;
	std::string abstractFileID;
	std::string biblioFileID;
	DescriptorDateAndTime volumeCreation;
	DescriptorDateAndTime volumeModification;
	DescriptorDateAndTime volumeExpiration;
	DescriptorDateAndTime volumeEffective;
	unsigned char fileStructureVersion;
};
