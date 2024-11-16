#include "../headers/bmpLoader.h"


// getters/setters
const BMPHeaderV5& BMPImg::getHeader() const { return header; }
const BMPInfoHeaderV5& BMPImg::getInfoHeader() const { return infoHeader; }
uint32_t* BMPImg::getData() { return imageData.data(); }





void BMPImg::read(const char* path)
{
	std::ifstream file;
	file.open(path, std::ios::in | std::ios::binary); // opening file in binary mode

	if (!file)
	{
		std::cout << "Error! File not found!";
		return;
	}

	// reading data of BMP header
	file.read((reinterpret_cast<char*>(&header)), sizeof(header));
	if (header.signature != 0x4D42)
	{
		std::cout << "Error! File is not .bmp!";
		file.close();
		return;
	}

	// reading data of Information Header
	file.read((reinterpret_cast<char*>(&infoHeader)), sizeof(infoHeader));
	if (!file)
	{
		std::cerr << "Second read failed\n";
	}
	std::cout << "Signature: " << std::hex << header.signature << std::endl;

	// allocating a space for pixels data
	imageData.resize(infoHeader.width * infoHeader.height);

	std::cout << "\nCurrent data in bmp loader: \n";
	std::cout << "Width: " << infoHeader.width;
	std::cout << "\nHeight: " << infoHeader.height;
	std::cout << "\nBit count: " << infoHeader.bitCount;
	std::cout << "\nSize: " << infoHeader.headerSize;
	

	// moving to the pixel data in file
	file.seekg(header.dataOffset, std::ios::beg);

	const int padding = (4 - (infoHeader.width * 3) % 4) % 4;
	for (int y = 0; y < infoHeader.height; ++y)
	{
		for (int x = 0; x < infoHeader.width; ++x)
		{
			uint8_t colors[3];
			uint32_t pixelData = 0;

			file.read(reinterpret_cast<char*>(colors), 3);

			pixelData |= colors[2]; // from 2 to 0 because data in bpm stored as a GBR(not rgb)
			pixelData |= colors[1] << 8;
			pixelData |= colors[0] << 16;
			pixelData |= 0xFF << 24; // 0 is white(alpha 255)
			

			imageData.push_back(pixelData); 

		}
		/*file.seekg(padding, std::ios::cur);*/
	}
	file.close();

}


void BMPImg::displayTexture()
{

	
}

