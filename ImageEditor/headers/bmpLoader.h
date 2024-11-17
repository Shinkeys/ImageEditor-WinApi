#pragma once

#include <iostream>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <vector>

#include <windows.h>


enum BMPColors
{
	Red,
	Green,
	Blue,
	Reserved,
};

#pragma pack(push, 1) // remove padding

struct BMPHeaderV5
{
	uint16_t signature{ 0 };
	uint32_t fileSize{ 0 };
	uint16_t reserved{ 0 };
	uint16_t reserved2{ 0 };
	uint32_t dataOffset{ 0 };
};
#pragma pack(pop)

#pragma pack(push, 1) // remove padding
struct BMPInfoHeaderV5
{
	uint32_t headerSize{ 0 };
	int32_t width{ 0 };
	int32_t height{ 0 };
	uint16_t planes{ 1 };
	uint16_t bitCount{ 0 };
	uint32_t compression{ 0 };
	uint32_t imageSize{ 0 };
	int32_t xPixelsPerM{ 0 };
	int32_t yPixelsPerM{ 0 };
	uint32_t colorsUsed{ 0 };
	uint32_t colorsImportant{ 0 };
	
	// v4/v5 data
	uint32_t redMask{ 0 };
	uint32_t greenMask{ 0 };
	uint32_t blueMask{ 0 };
	uint32_t alphaMask{ 0 };
	uint32_t csType{ 0 }; // color space
	uint32_t endpoints[9]{ 0 }; // for red, green, blue --- x,y,z
	uint32_t gammaRed{ 0 };
	uint32_t gammaBlue{ 0 };
	uint32_t gammaGreen{ 0 };
	uint32_t intent{ 0 };
	uint32_t profileData{ 0 };
	uint32_t profileSize{ 0 };
	uint32_t reserved{ 0 };
};
#pragma pack(pop)


class BMPImg
{
private:
	BMPHeaderV5 header;
	BMPInfoHeaderV5 infoHeader;
	static inline std::unique_ptr<uint64_t[]> imagePixelsData{ nullptr };
	
public:
	void read(const char* path);
	void displayTexture();

	// get/set 
	const BMPHeaderV5& getHeader();
	const BMPInfoHeaderV5& getInfoHeader();
	static uint64_t* getImagePixelsData();
	
// constructors/destr
public:
};





