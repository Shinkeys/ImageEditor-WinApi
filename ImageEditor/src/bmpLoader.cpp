#include "../headers/bmpLoader.h"


// getters/setters
const BMPHeaderV5& BMPImg::getHeader() { return header; }
const BMPInfoHeaderV5& BMPImg::getInfoHeader(){ return infoHeader; }
uint8_t* BMPImg::getImagePixelsData() { return imagePixelsData.get(); }




size_t BMPImg::read(const char* path)
{
	std::ifstream file;
	file.open(path, std::ios::in | std::ios::binary); // opening file in binary mode

	if (!file)
	{
		throw std::runtime_error("Error!File is not .bmp!");
	}
		
	// reading data of BMP header
	file.read((reinterpret_cast<char*>(&header)), sizeof(header));
	if (header.signature != 0x4D42)
	{
		file.close();
		throw std::runtime_error("Error!File is not .bmp!");
	}

	// reading data of Information Header
	file.read((reinterpret_cast<char*>(&infoHeader)), sizeof(infoHeader));
	if (!file)
	{
		file.close();
		throw std::runtime_error("Error! Could not read info header!");
	}
	std::cout << "Signature: " << std::hex << header.signature << std::endl;

	// allocating a space for pixels data
	imagePixelsData = std::make_unique<uint8_t[]>(infoHeader.width * infoHeader.height * (infoHeader.bitCount / 8));

	// debug for bmp loader
	std::cout << "\nCurrent data in bmp loader: \n";
	std::cout << "Width: " << infoHeader.width;
	std::cout << "\nHeight: " << infoHeader.height;
	std::cout << "\nBit count: " << infoHeader.bitCount;
	std::cout << "\nSize: " << infoHeader.headerSize;
	

	// moving to the pixel data in file
	file.seekg(header.dataOffset, std::ios::beg);
	size_t indexForImagePixelsData = 0;
	const int padding = (4 - (infoHeader.width * 3) % 4) % 4;
	for (int y = 0; y < infoHeader.height; ++y)
	{
		for (int x = 0; x < infoHeader.width; ++x)
		{
			uint8_t colors[3];
			uint32_t pixelData = 0;

			file.read(reinterpret_cast<char*>(colors), 3);

			//pixelData |= colors[0]; // from 2 to 0 because data in bpm stored as BGR(not rgb)
			//pixelData |= colors[1] << 8;
			//pixelData |= colors[2] << 16;
			//pixelData |= 0xFF << 24; // 0 is white(alpha 255)
			// to change later -------------------------------------
			
			// pushing data to a smart pointer
			/*imagePixelsData[indexForImagePixelsData++] = pixelData;*/
			imagePixelsData[indexForImagePixelsData++] = colors[0];
			imagePixelsData[indexForImagePixelsData++] = colors[1];
			imagePixelsData[indexForImagePixelsData++] = colors[2];


		}
		file.seekg(padding, std::ios::cur);
	}
	// debug colors
	/*std::cout << "COLORS DATA\n";
	for (auto i = 0; i < indexForImagePixelsData; ++i)
	{
		std::cout << imagePixelsData[i] << '\n';
	}*/
	std::cout << "\nImagePixelsData Total count: " << indexForImagePixelsData << '\n';
	
	file.close();

	return indexForImagePixelsData;
}



