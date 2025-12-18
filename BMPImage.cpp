/*
* Sokolova Dasha
* st141899@student.spbu.ru
* My project number five.
*/

#include "BMPImage.h"

#include <fstream>
#include <stdexcept>
#include <algorithm>

int BMPImage::index(int x, int y) const {
return (y * width() + x) * 3;
}

void BMPImage::load(const std::string& filename) {
    std::ifstream in(filename, std::ios::binary);
    if (!in) {
        throw std::runtime_error("Cannot open BMP file");
    }
	header.read(in);
	if (header.file.bfType != 0x4D42) {
        throw std::runtime_error("Not a BMP file");
    }

    if (header.info.biBitCount != 24 || header.info.biCompression != 0) {
        throw std::runtime_error("Only uncompressed 24-bit BMP is supported");
    }
	
	int w = header.info.biWidth;
    int h = header.info.biHeight;
    int padding = header.rowPadding();
	
	data.resize(w * h * 3);
	
	in.seekg(header.file.bfOffBits, std::ios::beg);
	
	for (int y = 0; y < h; ++y) {
        in.read(reinterpret_cast<char*>(&data[y * w * 3]), w * 3);
        in.ignore(padding);
    }
}

void BMPImage::save(const std::string& filename) const {
    std::ofstream out(filename, std::ios::binary);
    if (!out) {
        throw std::runtime_error("Cannot create BMP file");
    }
	BMPHeader outHeader(width(), height());
	outHeader.write(out);
	
	int padding = outHeader.rowPadding();
    std::vector<uint8_t> pad(padding, 0);
	
	for (int y = 0; y < height(); ++y) {
        out.write(reinterpret_cast<const char*>(&data[y * width() * 3]),
                  width() * 3);
        out.write(reinterpret_cast<const char*>(pad.data()), padding);
    }
}

void BMPImage::rotate90CW() {
    int w = width();
    int h = height();
    std::vector<uint8_t> result(w * h * 3);
	
	for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            for (int c = 0; c < 3; ++c) {
                result[(x * h + (h - y - 1)) * 3 + c] =
                    data[(y * w + x) * 3 + c];
            }
        }
    }
	
	std::swap(header.info.biWidth, header.info.biHeight);
    data.swap(result);
}

void BMPImage::rotate90CCW() {
    int w = width();
    int h = height();
    std::vector<uint8_t> result(w * h * 3);
	
	for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            for (int c = 0; c < 3; ++c) {
                result[((w - x - 1) * h + y) * 3 + c] =
                    data[(y * w + x) * 3 + c];
            }
        }
    }
	
	std::swap(header.info.biWidth, header.info.biHeight);
    data.swap(result);
}

void BMPImage::applyGaussianBlur() {
	static const int kernel[3][3] = {
		{1, 2, 1},
		{2, 4, 2},
		{1, 2, 1}
	};
	int w = width();
	int h = height();
	std::vector<uint8_t> result = data;
	
	for (int y = 1; y < h - 1; ++y) {
        for (int x = 1; x < w - 1; ++x) {
            for (int c = 0; c < 3; ++c) {
                int sum = 0;
                for (int ky = -1; ky <= 1; ++ky) {
                    for (int kx = -1; kx <= 1; ++kx) {
                        sum += kernel[ky + 1][kx + 1] *
                               data[index(x + kx, y + ky) + c];
                    }
                }
                result[index(x, y) + c] = static_cast<uint8_t>(sum / 16);
            }
        }
    }
	data.swap(result);
}

