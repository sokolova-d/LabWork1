/*
* Sokolova Dasha
* st141899@student.spbu.ru
* My project number five.
*/

#ifndef BMP_IMAGE_H
#define BMP_IMAGE_H

#include "Image.h"
#include "BMPHeader.h"

#include <cstdint>
#include <string>
#include <vector>

class BMPImage : public Image
{
public:
//constructor and destructor
    BMPImage() = default;
    ~BMPImage() override = default;

    void load(const std::string& filename) override;
    void save(const std::string& filename) const override;

    void rotate90CW() override;
    void rotate90CCW() override;

    void applyGaussianBlur() override;

    int width() const override
    {
        return header.info.biWidth;
    }
    int height() const override
    {
        return header.info.biHeight;
    }

    const std::vector<uint8_t>& getData() const
    {
        return data;
    }

private:
    BMPHeader header;

    std::vector<uint8_t> data;

    int index(int x, int y) const;
};

#endif