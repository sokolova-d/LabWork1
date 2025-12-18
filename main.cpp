/*
* Sokolova Dasha
* st141899@student.spbu.ru
* My project number five.
*/

#include "BMPImage.h"

#include <iostream>
#include <exception>
#include <string>

int main()
{
    std::string filename;
    std::cout << "Enter BMP filename: ";
    std::getline(std::cin, filename);

    try
    {
        BMPImage image;
        image.load(filename);

        BMPImage rotatedCW = image;
        rotatedCW.rotate90CW();
        rotatedCW.save("rotated_cw.bmp");

        BMPImage rotatedCCW = image;
        rotatedCCW.rotate90CCW();
        rotatedCCW.save("rotated_ccw.bmp");

        BMPImage blurred = rotatedCW;
        blurred.applyGaussianBlur();
        blurred.save("blurred.bmp");

        std::cout << "Processing completed successfully.\n";
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}