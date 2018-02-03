#pragma once
#include <iostream>
#include "Vec4.h"

class Mat4x4
{
public:
	Mat4x4();
	Mat4x4(int type);
	Mat4x4(double elements[]);
	~Mat4x4();
	double ele[4][4];

    void setIdentity();
	static Mat4x4 TranslatioMat(double tx, double ty, double tz);
	static Mat4x4 ScaleMat(double sx, double sy, double sz);
    static Mat4x4 RotateZMat(double angleRad);
    static Mat4x4 RotateYMat(double angleRad);
    static Mat4x4 ProjectionMat(double fovX, double fovY, double near, double far);
    static Mat4x4 ViewportMat(double width, double height, double tx, double ty);


	Mat4x4 operator *(const Mat4x4 matrix);
	Vec4 operator *(const Vec4 vec);


	enum MatTyp
	{
		ZeroMat, IdentityMat
	};

	friend std::ostream& operator<< (std::ostream& stream, const Mat4x4& matrix);

};

