#include "Vec4.h"


Vec4::Vec4()
{
    x = 0;
    y = 0;
    z = 0;
    w = 0;
}


Vec4::Vec4(double dx, double dy, double dz, double dw)
{
    x = dx;
    y = dy;
    z = dz;
    w = dw;
}

Vec4::~Vec4()
{
}


void Vec4::dehomogenize()
{
    x = x/w;
    y = y/w;
    z = z/w;
    w = 0;
}

Vec4 Vec4::crossProduct(Vec4& vecleft, Vec4& vecright)
{
    Vec4 retVec;

    retVec.x = vecleft.y*vecright.z-vecleft.z*vecright.y;
    retVec.y = vecleft.z*vecright.x-vecleft.x*vecright.z;
    retVec.z = vecleft.x*vecright.y-vecleft.y*vecright.x;
    retVec.w = 0;
    return retVec;
}


std::ostream & operator<<(std::ostream & stream, const Vec4 & vec)
{

    stream << vec.x << std::endl << vec.y << std::endl << vec.z << std::endl << vec.w << std::endl;
    return stream;
}

Vec4 Vec4::operator -(Vec4 vec)
{
    Vec4 retVec;

    retVec.x = x-vec.x;
    retVec.y = y-vec.y;
    retVec.z = z-vec.z;

    return retVec;
}




