/*
* Sokolova Dasha
* st141899@student.spbu.ru
* My project number five.
*/

#include "BMPHeader.h"

BMPHeader::BMPHeader() {
file.bfType = 0x4D42;
info.biSize = 40;
file.bfReserved1 = 0;
file.bfReserved2 = 0;

file.bfOffBits = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader);
file.bfSize = file.bfOffBits;

info.biWidth = 0;
info.biHeight = 0;
info.biPlanes = 1;
info.biBitCount = 24; 
info.biCompression = 0;
info.biSizeImage = 0;
info.biXPelsPerMeter = 0;
info.biYPelsPerMeter = 0;
info.biClrUsed = 0;
info.biClrImportant = 0;
}

BMPHeader::BMPHeader(int width, int height) : BMPHeader() {
info.biWidth = width;
info.biHeight = height;

int padding = rowPadding();

info.biSizeImage = (width * 3 + padding) * height;

file.bfSize = file.bfOffBits + info.biSizeImage;
}

void BMPHeader::read(std::ifstream& in) {
in.read(reinterpret_cast<char*>(&file), sizeof(file));
in.read(reinterpret_cast<char*>(&info), sizeof(info));
}

void BMPHeader::write(std::ofstream& out) const {
out.write(reinterpret_cast<const char*>(&file), sizeof(file));
out.write(reinterpret_cast<const char*>(&info), sizeof(info));
}

int BMPHeader::rowPadding() const {
int rowSize = info.biWidth * 3;
return (4 - (rowSize % 4)) % 4;
}
