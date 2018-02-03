#include "colorrgb8.h"

ColorRGB8::ColorRGB8(unsigned char red, unsigned char green, unsigned char blue)
{
    r = red;
    g = green;
    b = blue;

}
ColorRGB8::ColorRGB8()
{
    r=0;
    g=0;
    b=0;
}


ColorRGB8 ColorRGB8::operator*(const double scalar)
{
    ColorRGB8 retColor;
    retColor.r = (unsigned char) (((double)r)*scalar);
    retColor.g = (unsigned char) (((double)g)*scalar);
    retColor.b = (unsigned char) (((double)b)*scalar);
    return retColor;

}

ColorRGB8 ColorRGB8::operator +(const ColorRGB8 color)
{
    ColorRGB8 retColor;
    retColor.r  = r+color.r;
    retColor.g  = g+color.g;
    retColor.b  = b+color.b;
    return retColor;
}
