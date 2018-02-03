#include "Mat4x4.h"


Mat4x4::Mat4x4()
{
	ele[0][0] = 0.0; //Erste Reihe
	ele[0][1] = 0.0;
	ele[0][2] = 0.0;
	ele[0][3] = 0.0;

	ele[1][0] = 0.0; //Zweite Reihe
	ele[1][1] = 0.0;
	ele[1][2] = 0.0;
	ele[1][3] = 0.0;

	ele[2][0] = 0.0; //Dritte Reihe
	ele[2][1] = 0.0;
	ele[2][2] = 0.0;
	ele[2][3] = 0.0;

	ele[3][0] = 0.0; //Vierte Reihe
	ele[3][1] = 0.0;
	ele[3][2] = 0.0;
	ele[3][3] = 0.0;
}

Mat4x4::Mat4x4(int type)
{
	if (type == MatTyp::IdentityMat)
	{
		ele[0][0] = 1.0; //Erste Reihe
		ele[0][1] = 0.0;
		ele[0][2] = 0.0;
		ele[0][3] = 0.0;

		ele[1][0] = 0.0; //Zweite Reihe
		ele[1][1] = 1.0;
		ele[1][2] = 0.0;
		ele[1][3] = 0.0;

		ele[2][0] = 0.0; //Dritte Reihe
		ele[2][1] = 0.0;
		ele[2][2] = 1.0;
		ele[2][3] = 0.0;

		ele[3][0] = 0.0; //Vierte Reihe
		ele[3][1] = 0.0;
		ele[3][2] = 0.0;
		ele[3][3] = 1.0;
	}
	else
	{
		ele[0][0] = 0.0; //Erste Reihe
		ele[0][1] = 0.0;
		ele[0][2] = 0.0;
		ele[0][3] = 0.0;

		ele[1][0] = 0.0; //Zweite Reihe
		ele[1][1] = 0.0;
		ele[1][2] = 0.0;
		ele[1][3] = 0.0;

		ele[2][0] = 0.0; //Dritte Reihe
		ele[2][1] = 0.0;
		ele[2][2] = 0.0;
		ele[2][3] = 0.0;

		ele[3][0] = 0.0; //Vierte Reihe
		ele[3][1] = 0.0;
		ele[3][2] = 0.0;
		ele[3][3] = 0.0;
	}
}

 void Mat4x4::setIdentity()
 {
     ele[0][0] = 1.0; //Erste Reihe
     ele[0][1] = 0.0;
     ele[0][2] = 0.0;
     ele[0][3] = 0.0;

     ele[1][0] = 0.0; //Zweite Reihe
     ele[1][1] = 1.0;
     ele[1][2] = 0.0;
     ele[1][3] = 0.0;

     ele[2][0] = 0.0; //Dritte Reihe
     ele[2][1] = 0.0;
     ele[2][2] = 1.0;
     ele[2][3] = 0.0;

     ele[3][0] = 0.0; //Vierte Reihe
     ele[3][1] = 0.0;
     ele[3][2] = 0.0;
     ele[3][3] = 1.0;
 }

Mat4x4::Mat4x4(double elements[])
{
	ele[0][0] = elements[0]; //Erste Reihe
	ele[0][1] = elements[1];
	ele[0][2] = elements[2];
	ele[0][3] = elements[3];
	
	ele[1][0] = elements[4]; //Zweite Reihe
	ele[1][1] = elements[5];
	ele[1][2] = elements[6];
	ele[1][3] = elements[7];

	ele[2][0] = elements[4]; //Dritte Reihe
	ele[2][1] = elements[5];
	ele[2][2] = elements[6];
	ele[2][3] = elements[7];

	ele[3][0] = elements[4]; //Vierte Reihe
	ele[3][1] = elements[5];
	ele[3][2] = elements[6];
	ele[3][3] = elements[7];
}


Mat4x4::~Mat4x4()
{
}

Mat4x4 Mat4x4::TranslatioMat(double tx, double ty, double tz)
{
	Mat4x4 retMat = Mat4x4(MatTyp::IdentityMat);
	
	retMat.ele[0][3] = tx;
	retMat.ele[1][3] = ty;
	retMat.ele[2][3] = tz;

	return retMat;
}

Mat4x4 Mat4x4::ScaleMat(double sx, double sy, double sz)
{
	Mat4x4 retMat = Mat4x4(MatTyp::ZeroMat);

	retMat.ele[0][0] = sx;
	retMat.ele[1][1] = sy;
	retMat.ele[2][2] = sz;

	return retMat;
}

Mat4x4 Mat4x4::RotateZMat(double angleRad)
{
    Mat4x4 retMat(MatTyp::IdentityMat);

    const double cosa = cos(angleRad);
    const double sina = sin(angleRad);
    retMat.ele[0][0] = cosa;
    retMat.ele[0][1] = -sina;
    retMat.ele[1][0] = sina;
    retMat.ele[1][1] = cosa;

    return retMat;
}

Mat4x4 Mat4x4::RotateYMat(double angleRad)
{
    Mat4x4 retMat(MatTyp::IdentityMat);

    const double cosa = cos(angleRad);
    const double sina = sin(angleRad);
    retMat.ele[0][0] = cosa;
    retMat.ele[0][2] = sina;
    retMat.ele[2][0] = -sina;
    retMat.ele[2][2] = cosa;

    return retMat;
}

Mat4x4 Mat4x4::ProjectionMat(double fovX, double fovY, double znear, double zfar)
{
    Mat4x4 retMat(MatTyp::ZeroMat);

    retMat.ele[0][0] = 1/tan(fovX/2.0);
    retMat.ele[1][1] = 1/tan(fovY/2.0);
    retMat.ele[2][2] = -(zfar+znear)/(zfar-znear);
    retMat.ele[3][2] = -1;
    retMat.ele[2][3] = -2*(zfar*znear)/(zfar-znear);

    return retMat;
}

Mat4x4 Mat4x4::ViewportMat(double width, double height, double tx, double ty)
{
    Mat4x4 retMat(MatTyp::IdentityMat);

    retMat.ele[0][0] = width/2.0;
    retMat.ele[1][1] = height/2.0;
    retMat.ele[2][2] = 1.0;
    retMat.ele[3][3] = 1.0;

    retMat.ele[0][3] = tx;
    retMat.ele[1][3] = ty;

    return retMat;
}

Mat4x4 Mat4x4::operator*(const Mat4x4 mat)
{
	Mat4x4 retMat = Mat4x4();

	for (int i = 0; i < 4; i++)
	{
		for (int k = 0; k < 4; k++)
		{
			retMat.ele[i][k] = ele[i][0] * mat.ele[0][k] + ele[i][1] * mat.ele[1][k] + ele[i][2] * mat.ele[2][k] + ele[i][3] * mat.ele[3][k];
		}
	}
	return retMat;
}

Vec4 Mat4x4::operator*(const Vec4 vec)
 {
	 Vec4 retVec;

	 for (int i = 0; i < 4; i++)
	 {
		 retVec.ele[i] = ele[i][0] * vec.ele[0] + ele[i][1] * vec.ele[1] + ele[i][2] * vec.ele[2] + ele[i][3] * vec.ele[3];
	 }
	 return retVec;
 }

std::ostream & operator<<(std::ostream & stream, const Mat4x4 & matrix)
{
	stream << matrix.ele[0][0] << " " << matrix.ele[0][1] << " " << matrix.ele[0][2] << " " << matrix.ele[0][3] << std::endl;
	stream << matrix.ele[1][0] << " " << matrix.ele[1][1] << " " << matrix.ele[1][2] << " " << matrix.ele[1][3] << std::endl;
	stream << matrix.ele[2][0] << " " << matrix.ele[2][1] << " " << matrix.ele[2][2] << " " << matrix.ele[2][3] << std::endl;
	stream << matrix.ele[3][0] << " " << matrix.ele[3][1] << " " << matrix.ele[3][2] << " " << matrix.ele[3][3] << std::endl;

	return stream;
}
