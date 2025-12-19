/*
* Sokolova Dasha
* st141899@student.spbu.ru
* My project number five.
*/

#include <gtest/gtest.h>

#include "BMPHeader.h"
#include "BMPImage.h"

#include <fstream>
#include <vector>
#include <cstdint>

static void createTestBMP(const std::string& filename)
{
    BMPHeader header;
    header.setWidth(2);
    header.setHeight(2);
    header.updateSizes();

    std::vector<uint8_t> pixels =
    {
        0,   0, 255,   // red
        0, 255,   0,   // green
        255, 0,   0,   // blue
        255,255,255    // white
    };

    std::ofstream out(filename, std::ios::binary);
    header.write(out);

    uint8_t pad[2] = {0, 0};

    out.write(reinterpret_cast<char*>(pixels.data()), 6);
    out.write(reinterpret_cast<char*>(pad), 2);
    out.write(reinterpret_cast<char*>(pixels.data() + 6), 6);
    out.write(reinterpret_cast<char*>(pad), 2);
}

//testing constructor
TEST(BMPHeaderTest, DefaultConstructor)
{
    BMPHeader header;

    EXPECT_EQ(header.getBitsPerPixel(), 24);
    EXPECT_EQ(header.getCompression(), 0);
}
//testing setting dimensions
TEST(BMPHeaderTest, SetDimensions)
{
    BMPHeader header;
    header.setWidth(100);
    header.setHeight(50);
    header.updateSizes();

    EXPECT_EQ(header.getWidth(), 100);
    EXPECT_EQ(header.getHeight(), 50);
}

//test loading files
TEST(BMPImageTest, LoadImage)
{
    createTestBMP("test.bmp");

    BMPImage img;
    EXPECT_NO_THROW(img.load("test.bmp"));
    EXPECT_EQ(img.width(), 2);
    EXPECT_EQ(img.height(), 2);
}
TEST(BMPImageTest, LoadInvalidFile)
{
    BMPImage img;
    EXPECT_THROW(img.load("no_file.bmp"), std::runtime_error);
}

//rotation tests
TEST(BMPImageTest, RotateCWSize)
{
    createTestBMP("test.bmp");

    BMPImage img;
    img.load("test.bmp");
    img.rotate90CW();

    EXPECT_EQ(img.width(), 2);
    EXPECT_EQ(img.height(), 2);
}
TEST(BMPImageTest, RotateCWChangesPixels)
{
    createTestBMP("test.bmp");

    BMPImage img;
    img.load("test.bmp");

    auto before = img.getData();
    img.rotate90CW();
    auto after = img.getData();

    EXPECT_NE(before, after);
}

TEST(BMPImageTest, RotateCCWSize)
{
    createTestBMP("test.bmp");

    BMPImage img;
    img.load("test.bmp");
    img.rotate90CCW();

    EXPECT_EQ(img.width(), 2);
    EXPECT_EQ(img.height(), 2);
}
TEST(BMPImageTest, RotateCWAndCCWRestore)
{
    createTestBMP("test.bmp");

    BMPImage img;
    img.load("test.bmp");

    auto original = img.getData();

    img.rotate90CW();
    img.rotate90CCW();

    EXPECT_EQ(img.getData(), original);
}

//testing gauss filter
TEST(BMPImageTest, GaussianBlurDoesNotCrash)
{
    createTestBMP("test.bmp");

    BMPImage img;
    img.load("test.bmp");

    EXPECT_NO_THROW(img.applyGaussianBlur());
}
TEST(BMPImageTest, GaussianBlurChangesPixels)
{
    createTestBMP("test.bmp");
    BMPImage img;
    img.load("test.bmp");

    auto before = img.getData();
    img.applyGaussianBlur();
    auto after = img.getData();

    EXPECT_NE(before, after);
}

//saving tests
TEST(BMPImageTest, SaveImageDoesNotThrow)
{
    createTestBMP("test.bmp");
    BMPImage img;
    img.load("test.bmp");

    EXPECT_NO_THROW(img.save("out.bmp"));
}
TEST(BMPImageTest, SavedFileExists)
{
    createTestBMP("test.bmp");

    BMPImage img;
    img.load("test.bmp");
    img.save("out.bmp");

    std::ifstream f("out.bmp", std::ios::binary);
    EXPECT_TRUE(f.good());
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}