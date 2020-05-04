#pragma once

#include <string>

class DescriptorDateAndTime
{
public:
	DescriptorDateAndTime();
	virtual ~DescriptorDateAndTime();
	DescriptorDateAndTime(unsigned char buffer[17]);

protected:

private:
	std::string year, month, date, hour, minutes, seconds, hundreths;
	unsigned char timezone;
};