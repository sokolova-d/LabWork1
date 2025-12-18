/*
* Sokolova Dasha
* st141899@student.spbu.ru
* My project number five.
*/

#ifndef BMP_HEADER_H
#define BMP_HEADER_H

#include <cstdint>
#include <fstream>

#pragma pack(push, 1)
//first header of the file
struct BMPFileHeader {
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
};
//main header
struct BMPInfoHeader {
    uint32_t biSize;
    int32_t  biWidth;
    int32_t  biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    int32_t  biXPelsPerMeter;
	int32_t  biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
};

#pragma pack(pop)

class BMPHeader {
public:
//constuctor
BMPHeader();
BMPHeader(int width, int height);

void setWidth(int w) { info.biWidth = w; updateSizes(); }
void setHeight(int h) { info.biHeight = h; updateSizes(); }
int getWidth() const { return info.biWidth; }
int getHeight() const { return info.biHeight; }
int getBitsPerPixel() const { return info.biBitCount; }
int getCompression() const { return info.biCompression; }

void updateSizes() {
    int padding = rowPadding();
    info.biSizeImage = (info.biWidth * 3 + padding) * info.biHeight;
    file.bfSize = file.bfOffBits + info.biSizeImage;
}

void read(std::ifstream& in);
void write(std::ofstream& out) const;

int rowPadding() const;

BMPFileHeader file;
BMPInfoHeader info;
};

#endif
