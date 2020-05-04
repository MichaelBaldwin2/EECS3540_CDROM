#include "PrimaryVolumeDescriptor.h"
#include <string>
#include <vector>
#include <iostream>
#include "Endian.h"

PrimaryVolumeDescriptor::PrimaryVolumeDescriptor() : descriptortype(), standardID(), version(), systemID(), volumeID(), volumeSpace(), volumeSet(), volumeSeq(), logicalBlockSize(), pathTableSize(), lPathTableLoc(), optLPathTableLoc(), mPathTableLoc(), optMPathTableLoc(), rootDirectory(), volumeSetID(), publisherID(), dataPreparerID(), applicationID(), copyrightFileID(), abstractFileID(), biblioFileID(), volumeCreation(), volumeModification(), volumeExpiration(), volumeEffective(), fileStructureVersion()
{
}

PrimaryVolumeDescriptor::PrimaryVolumeDescriptor(std::vector<unsigned char> data) : PrimaryVolumeDescriptor()
{
	descriptortype = data[0];
	memcpy(standardID, &(data[1]), 5);
	version = data[6];

	unsigned char tempArray[33];
	memset(tempArray, 0, 33);
	memcpy(tempArray, &(data[8]), 32);
	systemID = std::string((char *)tempArray);
	memcpy(tempArray, &(data[40]), 32);
	volumeID = std::string((char *)tempArray);

	volumeSpace[0] = *((int32_t *)(&data[80]));
	volumeSpace[1] = *((int32_t *)(&data[84]));
	
	volumeSet[0] = *((int16_t *)(&data[120]));
	volumeSet[1] = *((int16_t *)(&data[122]));
	
	volumeSeq[0] = *((int16_t *)(&data[124]));
	volumeSeq[1] = *((int16_t *)(&data[126]));
	
	logicalBlockSize[0] = *((int16_t *)(&data[128]));
	logicalBlockSize[1] = *((int16_t *)(&data[130]));

	pathTableSize[0] = *((int32_t *)(&data[132]));
	pathTableSize[1] = *((int32_t *)(&data[136]));

	lPathTableLoc = data[140] + data[141] * 256 + data[142] * 65536 + data[143] * (256 * 65536);
	optLPathTableLoc = data[144] + (((data[147] * 256) + data[146] * 256) + data[145] * 256);
	mPathTableLoc = (data[148] << 24) | (data[147] << 16) | (data[146] << 8) | data[147];
	optMPathTableLoc = (data[152] << 24) | (data[153] << 16) | (data[154] << 8) | data[155];

	rootDirectory = DirectoryRecord(&data[156]);
	unsigned char buffer[129];
	memcpy(buffer, &(data[190]), 128);
	buffer[128] = '\0';
	volumeSetID = std::string((char *)buffer);
	memcpy(buffer, &(data[318]), 128);
	publisherID = std::string((char *)buffer);
	memcpy(buffer, &(data[446]), 128);
	dataPreparerID = std::string((char *)buffer);
	memcpy(buffer, &(data[574]), 128);
	applicationID = std::string((char *)buffer);
	memcpy(buffer, &(data[702]), 37);
	buffer[37] = '\0';
	copyrightFileID = std::string((char *)buffer);
	memcpy(buffer, &(data[739]), 37);
	buffer[37] = '\0';
	abstractFileID = std::string((char *)buffer);
	memcpy(buffer, &(data[776]), 37);
	buffer[37] = '\0';
	biblioFileID = std::string((char *)buffer);
}

DirectoryRecord &PrimaryVolumeDescriptor::GetRootDirectory()
{
	return rootDirectory;
}

DescriptorDateAndTime PrimaryVolumeDescriptor::GetCreationDateAndTime()
{
	return volumeCreation;
}

DescriptorDateAndTime PrimaryVolumeDescriptor::GetModificationDateAndTime()
{
	return volumeModification;
}

DescriptorDateAndTime PrimaryVolumeDescriptor::GetEffectiveDateAndTime()
{
	return volumeEffective;
}

DescriptorDateAndTime PrimaryVolumeDescriptor::GetExpirationDateAndTime()
{
	return volumeExpiration;
}

unsigned char PrimaryVolumeDescriptor::GetType()
{
	return descriptortype;
}

std::string PrimaryVolumeDescriptor::GetSystemID()
{
	return systemID;
}

std::string PrimaryVolumeDescriptor::GetVolumeID()
{
	return volumeID;
}

int PrimaryVolumeDescriptor::GetVolumeSpace()
{
	return volumeSpace[GetEndian()];
}

int PrimaryVolumeDescriptor::GetVolumeSet()
{
	return volumeSet[GetEndian()];
}

int PrimaryVolumeDescriptor::GetVolumeSeq()
{
	return volumeSeq[GetEndian()];
}

int PrimaryVolumeDescriptor::GetLPathTableLocation()
{
	return lPathTableLoc;
}

int PrimaryVolumeDescriptor::GetMPathTableLocatgion()
{
	return mPathTableLoc;
}

int PrimaryVolumeDescriptor::GetOptLPathTableLocation()
{
	return optLPathTableLoc;
}

int PrimaryVolumeDescriptor::GetOptMPathTableLocation()
{
	return optMPathTableLoc;
}

std::string PrimaryVolumeDescriptor::GetVolumeSetID()
{
	return volumeSetID;
}

std::string PrimaryVolumeDescriptor::GetPublisherID()
{
	return publisherID;
}

std::string PrimaryVolumeDescriptor::GetDataPreparerID()
{
	return dataPreparerID;
}

std::string PrimaryVolumeDescriptor::GetApplicationID()
{
	return applicationID;
}

std::string PrimaryVolumeDescriptor::GetCopyrightFileID()
{
	return copyrightFileID;
}

std::string PrimaryVolumeDescriptor::GetBibliographyFileID()
{
	return biblioFileID;
}

std::string PrimaryVolumeDescriptor::GetAbstractFileID()
{
	return abstractFileID;
}
