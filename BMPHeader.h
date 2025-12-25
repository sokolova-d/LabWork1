/*
* Sokolova Dasha
* st141899@student.spbu.ru
* My project number five.
*/

#ifndef BMP_HEADER_H
#define BMP_HEADER_H

#include <cstdint>
#include <fstream>

static constexpr int BMP_CHANNELS = 3;
static constexpr int BMP_ALIGNMENT = 4;
static constexpr uint16_t BMP_TYPE_VALUE = 0x4D42;
static constexpr uint32_t BMP_INFO_HEADER_SIZE = 40;
static constexpr uint16_t BMP_PLANES_DEFAULT = 1;
static constexpr uint16_t BMP_BITCOUNT_DEFAULT = 24;
static constexpr uint32_t BMP_COMPRESSION_NONE = 0;

#pragma pack(push, 1)
struct BMPFileHeader
{
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
};

struct BMPInfoHeader
{
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

class BMPHeader
{
public:
    BMPHeader();
    BMPHeader(int width, int height);

    void setWidth(int w)
    {
        info.biWidth = w;
        updateSizes();
    }
    void setHeight(int h)
    {
        info.biHeight = h;
        updateSizes();
    }
    int getWidth() const
    {
        return info.biWidth;
    }
    int getHeight() const
    {
        return info.biHeight;
    }
    int getBitsPerPixel() const
    {
        return info.biBitCount;
    }
    int getCompression() const
    {
        return info.biCompression;
    }

    void updateSizes()
    {
        int padding = rowPadding();
        info.biSizeImage = (info.biWidth * BMP_CHANNELS + padding) * info.biHeight;
        file.bfSize = file.bfOffBits + info.biSizeImage;
    }

    void read(std::ifstream& in);
    void write(std::ofstream& out) const;

    int rowPadding() const;

    BMPFileHeader file;
    BMPInfoHeader info;
};

#endif