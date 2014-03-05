//////////////////////////////////////
//File:              <Utilities.cpp>
//Author:            <Hunter Bergerud>
//Date Created:      <3/3/14>
//Date Modified:     <3/3/14>
//Brief:             <Utilities Code>
//////////////////////////////////////
#include "Utilities.h"
Matrix4 * Ortho;

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
GLuint LoadTexture(const char* a_szTexture, unsigned int a_uiFormat = GL_RGBA , 
	unsigned int* a_uiWidth  = nullptr , 
	unsigned int* a_uiHeight  = nullptr , unsigned int* a_uiBPP  = nullptr)
{
	//Make a FIBITMAP pointer called pBitmap
	FIBITMAP* pBitmap = nullptr;
	//Check the file and shrink its type and load it
	FREE_IMAGE_FORMAT fif = FreeImage_GetFileType(a_szTexture, 0);
	//If fif is not unknown and the fif support is itself
	if(fif != FIF_UNKNOWN && FreeImage_FIFSupportsReading(fif)) 
	{
		//Make pBitMap equal the fif and a_szTexture
		pBitmap = FreeImage_Load(fif, a_szTexture);
	}
	//If pBitMap equals nullptr
	if(pBitmap == nullptr) 
	{
		//Print out an error to the user the program failed to load the image
		printf("Error: Failed to load image '%s'!\n", a_szTexture);
		//Return 0
		return 0;
	}

	//Get pBitMap's width and height
	if(a_uiWidth != nullptr)
		*a_uiWidth = FreeImage_GetWidth(pBitmap);
	if(a_uiHeight != nullptr)
		*a_uiHeight = FreeImage_GetHeight(pBitmap);

	//Force the image to RGBA
	unsigned int bpp = FreeImage_GetBPP(pBitmap);
	//If a_uiBPP is not nullptr
	if( a_uiBPP != nullptr )
		//Make pointer a_uiBPP equal bpp divided by 8
		*a_uiBPP = bpp/8;
	//Make a FREE_IMAGE_COLOR_TYPE called fi_colourType equal the color type of pBitmap
	FREE_IMAGE_COLOR_TYPE fi_colourType = FreeImage_GetColorType(pBitmap);
	//If fi_colourType is not FIC_RGBALPHA
	if(fi_colourType != FIC_RGBALPHA ) 
	{
		//Make a FIBITMAP pointer called ndib and equal it to pBitmap in 32 Bit format
		FIBITMAP* ndib = FreeImage_ConvertTo32Bits(pBitmap);
		//Upload pBitmap
		FreeImage_Unload(pBitmap);
		//Make pBitMap equal to ndib
		pBitmap = ndib;
		//Make bpp equal to pBitmap's BPP
		bpp = FreeImage_GetBPP(pBitmap);
		//Make fi_colourType equal the color type of pBitmap
		fi_colourType = FreeImage_GetColorType(pBitmap);
	}
	//Get pixel data
	BYTE* pData = FreeImage_GetBits(pBitmap);
	//Try to determine data type of file (bytes/floats)
	FREE_IMAGE_TYPE fit = FreeImage_GetImageType(pBitmap);
	GLenum eType = (fit == FIT_RGBF || fit == FIT_FLOAT) ? GL_FLOAT:GL_UNSIGNED_BYTE;
	//Create GL texture
	GLuint textureID;
	glGenTextures( 1, &textureID );
	glBindTexture( GL_TEXTURE_2D, textureID );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, 
		FreeImage_GetWidth(pBitmap), 
		FreeImage_GetHeight(pBitmap), 0, 
		a_uiFormat, eType, pData);
	// specify default filtering and wrapping
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
	// unbind texture
	glBindTexture( GL_TEXTURE_2D, 0 );
	// delete data
	FreeImage_Unload(pBitmap);
	return textureID;
}