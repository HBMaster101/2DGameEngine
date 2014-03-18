//////////////////////////////////////
//File:              <Utilities.cpp>
//Author:            <Hunter Bergerud>
//Date Created:      <3/3/14>
//Date Modified:     <3/10/14>
//Brief:             <Utilities Code>
//////////////////////////////////////
#include "Utilities.h"
Matrix4 * Ortho;
int g_gl_width = 1024;
int g_gl_height = 720;
double deltaTime = 0;
int frames;
double fps, elapsedTime;
void Orthographic(float a_fLeft, float a_fRight, float a_fTop, float a_fBottom,
	float a_fNear, float a_fFar, tbyte::Matrix4 * mat)
{
	//Make three floats
	float deltaX = a_fRight - a_fLeft;
	float deltaY = a_fTop - a_fBottom;
	float deltaZ = a_fNear - a_fFar;
	//First line of this array
	mat->m_afArray[0] = 2.f / deltaX;
	mat->m_afArray[1] = 0.f;
	mat->m_afArray[2] = 0.f;
	mat->m_afArray[3] = 0.f;
	//Second line of this array
	mat->m_afArray[4] = 0.f;
	mat->m_afArray[5] = 2.f / deltaY;
	mat->m_afArray[6] = 0.f;
	mat->m_afArray[7] = 0.f;
	//Third line of this array
	mat->m_afArray[8] = 0.f;
	mat->m_afArray[9] = 0.f;
	mat->m_afArray[10] = 2.f / deltaZ;
	mat->m_afArray[11] = 0.f;
	//Fourth line of this array
	mat->m_afArray[12] = ((a_fLeft + a_fRight )/(a_fLeft  - a_fRight));
	mat->m_afArray[13] = ((a_fBottom + a_fTop )/(a_fBottom - a_fTop));
	mat->m_afArray[14] = (-(a_fNear + a_fFar)/(a_fFar - a_fNear));
	mat->m_afArray[15] = 1.f;

}
void Orthographic(float a_fWidth, float a_fHeight, float a_fNear, float a_fFar,tbyte::Matrix4 * mat)
{
	//First line of this array
	mat->m_afArray[0] = 2 / a_fWidth;
	mat->m_afArray[1] = 0;
	mat->m_afArray[2] = 0;
	mat->m_afArray[3] = 0;
	//Second line of this array
	mat->m_afArray[4] = 0;
	mat->m_afArray[5] = 2 / a_fHeight;
	mat->m_afArray[6] = 0;
	mat->m_afArray[7] = 0;
	//Third line of this array
	mat->m_afArray[8] = 0;
	mat->m_afArray[9] = 0;
	mat->m_afArray[10] = 1 / (a_fFar - a_fNear);
	mat->m_afArray[11] = 0;
	//Fourth line of this array
	mat->m_afArray[12] = 0;
	mat->m_afArray[13] = 0;
	mat->m_afArray[14] = a_fNear / (a_fNear - a_fFar);
	mat->m_afArray[15] = 1;
}

void Perspective(float a_fUpFOV, float a_fAspectRatio, float a_fNear, float a_fFar,tbyte::Matrix4 *mat)
{
	//Make two floats
	float halfAngleRadians = 0.5f * a_fUpFOV;
	float cot = 1 / tanf(halfAngleRadians);
	//First line of this array
	mat->m_afArray[0] = cot / a_fAspectRatio;
	mat->m_afArray[1] = 0;
	mat->m_afArray[2] = 0;
	mat->m_afArray[3] = 0;
	//Second line of this array
	mat->m_afArray[4] = 0;
	mat->m_afArray[5] = cot;
	mat->m_afArray[6] = 0;
	mat->m_afArray[7] = 0;
	//Third line of this array
	mat->m_afArray[8] = 0;
	mat->m_afArray[9] = 0;
	mat->m_afArray[10] = a_fFar / (a_fFar - a_fNear);
	mat->m_afArray[11] = 1;
	//Fourth line of this array
	mat->m_afArray[12] = 0;
	mat->m_afArray[13] = 0;
	mat->m_afArray[14] = a_fNear * a_fFar / (a_fNear - a_fFar);
	mat->m_afArray[15] = 0;
}
//Get Delta Time
double getDeltaTime()
{
	return deltaTime;
}
//Reset Delta Time
void resetDeltaTime()
{
	deltaTime =  glfwGetTime();
	elapsedTime += deltaTime;
	frames++;
	if(elapsedTime > 0.25)
	{
		fps = (double)frames/elapsedTime;
		elapsedTime =0;
		frames = 0;
	}
	glfwSetTime(0);	
}