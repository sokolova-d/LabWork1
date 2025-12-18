/*
* Sokolova Dasha
* st141899@student.spbu.ru
* My laboratory work number one.
*/

#ifndef IMAGE_H
#define IMAGE_H

#include <string>

class Image
{
public:
//destructor
    virtual ~Image() = default;

    virtual int width() const = 0;
    virtual int height() const = 0;

    virtual void load(const std::string& filename) = 0;
    virtual void save(const std::string& filename) const = 0;

    virtual void rotate90CW() = 0;
    virtual void rotate90CCW() = 0;
    virtual void applyGaussianBlur() = 0;
};

#endif
