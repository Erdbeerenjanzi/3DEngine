#pragma once

#include <iostream>

class Vec4
{
public:
	Vec4();
    Vec4(double dx, double dy, double dz, double dw);


    union
    {
    double ele[4];
    struct{double x,y,z,w;};
    };

    ~Vec4();
    void dehomogenize();

    static Vec4 crossProduct(Vec4& vecleft, Vec4& vecright);

    Vec4 operator -(Vec4 vec);

    friend std::ostream& operator<< (std::ostream& stream, const Vec4& vec);

};

