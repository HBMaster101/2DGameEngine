///////////////////////////////////////////////////
//File:              <StaticMathLibrary.h>
//Author:            <Hunter Bergerud>
//Date Created:      <12/10/13>
//Date Modified:     <12/10/13>
//Brief:             <Static MathLibrary Classes>
///////////////////////////////////////////////////
#include <iostream>
#include <math.h>
#ifndef _STATICMATHLIBRARY_H_
#define _STATICMATHLIBRARY_H_


class MathFunctionality
{

public:
	MathFunctionality();
	~ MathFunctionality();

	double linearInterpolation(double yOne, double yTwo, double x);

	double radiansToDegrees(double a);

	float powerOfTwo(float exponent);

};

class Vector2
{

public:
	Vector2();
	Vector2(float a_fX,float a_fY);
	~ Vector2();

	float fX;
	float fY;

	float getMagnitudeV2();

	Vector2 normaliseV2(Vector2 a_vVec);

	float DotProductV2(Vector2 a_vVec);

	Vector2 vect2LinearInterpolationV2(Vector2 otherVector, float time);

	Vector2 operator + (Vector2& a_vVec);
	void operator += (Vector2& a_vVec);

	Vector2 operator - (Vector2& a_vVec);
	void operator -= (Vector2& a_vVec);

	Vector2 operator * (float a_fScal);
	void operator *= (float a_fScal);

	Vector2 operator / (float a_fScal);
	void operator /= (float a_fScal);

};

class Vector3
{

public:
	Vector3();
	Vector3(float a_fX,float a_fY,float a_fZ);
	~ Vector3();

	float fX;
	float fY;
	float fZ;

	float getMagnitudeV3();

	Vector3 normaliseV3(Vector3 a_vVec);

	float DotProductV3(Vector3 a_vVec);

	Vector3 vect3LinearInterpolationV3(Vector3 otherVector, float time);

	Vector3 CrossProductV3(Vector3 a_vVec);

	Vector3 operator + (Vector3& a_vVec);
	void operator += (Vector3& a_vVec);

	Vector3 operator - (Vector3& a_vVec);
	void operator -= (Vector3& a_vVec);

	Vector3 operator * (float a_fScal);
	void operator *= (float a_fScal);

	Vector3 operator / (float a_fScal);
	void operator /= (float a_fScal);

};

class Vector4
{

public:
	Vector4();
	Vector4(float a_fX,float a_fY,float a_fZ, float a_fW);
	~ Vector4();

	float fW;
	float fX;
	float fY;
	float fZ;

	float getMagnitudeV4();

	Vector4 normaliseV4(Vector4 a_vVec);

	Vector4 colorConverter(int hexValue, float al);

};

class Matrix3x3
{

public:
	Matrix3x3();
	Matrix3x3(float m_mNumOne, float m_mNumTwo, float m_mNumThree, float m_mNumFour, float m_mNumFive, float m_mNumSix, float m_mNumSeven, float m_mNumEight, float m_mNumNine);
	~ Matrix3x3();

	float numOne;
	float numTwo;
	float numThree;
	float numFour;
	float numFive;
	float numSix;
	float numSeven;
	float numEight;
	float numNine;

	void identityMatrix3x3();
	Matrix3x3 xRotationMatrix3x3(float m_rotation);
	Matrix3x3 yRotationMatrix3x3(float m_rotation);
	Matrix3x3 zRotationMatrix3x3(float m_rotation);
	Matrix3x3 scaleMatrix3x3(float m_transX, float m_transY);
	Matrix3x3 translationMatrix3x3(float m_transX, float m_transY);

	Matrix3x3 setXRotation3x3(float m_rotation);
	Matrix3x3 setYRotation3x3(float m_rotation);
	Matrix3x3 setZRotation3x3(float m_rotation);
	Matrix3x3 setScale3x3(float m_transX, float m_transY);
	Matrix3x3 setTraslation3x3(float m_transX, float m_transY);

	Matrix3x3 transformXVector3x3();
	Matrix3x3 transformYVector3x3();
	Matrix3x3 transformXPoint3x3();
	Matrix3x3 transformYPoint3x3();

	Matrix3x3 operator * (Matrix3x3 otherMatrix);
	void operator *= (Matrix3x3 otherMatrix);

};

class Matrix4x4
{

public:
	Matrix4x4();
	Matrix4x4(float m_mNumOne, float m_mNumTwo, float m_mNumThree, float m_mNumFour, float m_mNumFive, float m_mNumSix, float m_mNumSeven, float m_mNumEight, 
	float m_mNumNine, float m_mNumTen, float m_mNumEleven, float m_mNumTwelve, float m_mNumTherteen, float m_mNumFourteen, float m_mNumFiveteen, float m_mNumSixteen);
	~ Matrix4x4();

	float numOne;
	float numTwo;
	float numThree;
	float numFour;
	float numFive;
	float numSix;
	float numSeven;
	float numEight;
	float numNine;
	float numTen;
	float numEleven;
	float numTwelve;
	float numThreeteen;
	float numFourteen;
	float numFiveteen;
	float numSixteen;

	Matrix4x4 identityMatrix4x4();
	Matrix4x4 xRotationMatrix4x4(float m_rotation);
	Matrix4x4 yRotationMatrix4x4(float m_rotation);
	Matrix4x4 zRotationMatrix4x4(float m_rotation);
	Matrix4x4 scaleMatrix4x4(float m_transX, float m_transY, float m_transZ);
	Matrix4x4 translationMatrix4x4(float m_transX, float m_transY, float m_transZ);

	Matrix4x4 setXRotation4x4(float m_rotation);
	Matrix4x4 setYRotation4x4(float m_rotation);
	Matrix4x4 setZRotation4x4(float m_rotation);
	Matrix4x4 setScale4x4(float m_transX, float m_transY, float m_transZ);
	Matrix4x4 setTraslation4x4(float m_transX, float m_transY, float m_transZ);

	Matrix4x4 transformXVector4x4();
	Matrix4x4 transformYVector4x4();
	Matrix4x4 transformZVector4x4();
	Matrix4x4 transformXPoint4x4();
	Matrix4x4 transformYPoint4x4();
	Matrix4x4 transformZPoint4x4();

	Matrix4x4 orthoProjection(float m_transX, float m_transY, float m_transZ, float m_transW);

	Matrix4x4 operator * (Matrix4x4 otherMatrix);
	void operator *= (Matrix4x4 otherMatrix);

};

#endif