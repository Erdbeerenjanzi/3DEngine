#ifndef COLORRGB8_H
#define COLORRGB8_H


class ColorRGB8
{
public:
    ColorRGB8();
    ColorRGB8(unsigned char red, unsigned char green, unsigned char blue);
    unsigned char r,g,b;
    ColorRGB8 operator *(const double scalar);
    ColorRGB8 operator +(const ColorRGB8 color);

};

#endif // COLORRGB8_H
