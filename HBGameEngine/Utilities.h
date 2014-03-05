//////////////////////////////////////
//File:              <Utilities.h>
//Author:            <Hunter Bergerud>
//Date Created:      <3/3/14>
//Date Modified:     <3/3/14>
//Brief:             <Utilities Class>
//////////////////////////////////////
#pragma once
#ifndef _UTILITIES_H_
#define _UTILITIES_H_
#include <GLFW\glfw3.h>
#include <FreeImage.h>
#include <TerrehByteMath.h>
#include "Log.h"
#include "TextFileReader.h"
#include <string>
#include <queue>
#include <vector>
#include <map>
#include <fstream>
#include <assert.h>
#include <functional>
using namespace tbyte;
extern Matrix4 * Ortho;
//Make a struct called Vertex
struct Vertex
{
	//Make a union
	union
	{
		//Make a struct with a Vector3, a Vector4, and a Vector2
		struct
		{
			tbyte::Vector3 Pos;
			tbyte::Vector4 Color;
			tbyte::Vector2 UV;
		};
		//Make a struct with three floats
		struct
		{
			float X, Y, Z;
			float R, G, B, A;
			float U, V;
		};

	};
	//Make a bool operator function with the required data
	bool operator == (const Vertex& rhs)
	{
		//Return the Vertex
		return (X == rhs.X && Y == rhs.Y && Z == rhs.Z
		&& R == rhs.R && G == rhs.G && B == rhs.B && A == rhs.A
		&& U == rhs.U && V == rhs.V);
	}
};
//Make a void function called Orthographic with the required data
void Orthographic(float a_fLeft, float a_fRight, float a_fTop, float a_fBottom, float a_fNear, float a_fFar, tbyte::Matrix4 * mat);
//Make another void function called Orthographic with the required data
void Orthographic(float a_fWidth, float a_fHeight, float a_fNear, float a_fFar,tbyte::Matrix4 * mat);
//Make a void function called Perspective with the required data
void Perspective(float a_fUpFOV, float a_fAspectRatio, float a_fNear, float a_fFar,tbyte::Matrix4 * mat);
//Make a GLuint function called LoadTexture with the required data
GLuint LoadTexture(const char* a_szTexture, unsigned int a_uiFormat , unsigned int* a_uiWidth , unsigned int* a_uiHeight, unsigned int* a_uiBPP);
#endif _UTILITIES_H_