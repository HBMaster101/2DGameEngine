/////////////////////////////////////////
//File:              <FontManager.h>
//Author:            <Hunter Bergerud>
//Date Created:      <3/10/14>
//Date Modified:     <3/10/14>
//Brief:             <Font Manager Class>
/////////////////////////////////////////
#ifndef _FONT_MANAGER_H_
#define _FONT_MANAGER_H_
#include <tinyxml2.h>
#include "AnimatedSprite.h"
//Make a struct called Char
struct Char
{
	//Make a union
	union
	{
		//Make a struct to hold the following info
		struct
		{
			std::string sName;
			tbyte::Vector2 v2Size;
			tbyte::Vector4 v4Location;
			float yOffset;
		};
		//Make another struct to hold the following info
		struct
		{
			std::string Name;
			float width, height;
			float x0,x1,y0,y1;
			float offset;
		};
	};
};
//Make a struct called Font to hold the following info
struct Font
{
	tbyte::Vector2 v2Size;
	std::string sSheet;
	float fKerning;
};
//Make a class called FontManager
class FontManager
{
public:
	FontManager(void);
	~FontManager(void);
	//Make a void function called LoadFont
	void LoadFont(const char * a_pFontSheet);
	//Make a void function for drawing text and loading text
	void DrawString(std::string str,Vector2 pos,float scale);
	void LoadString(std::string str,Vector2 pos,float scale);
	//Make a Sprite called iSprite
	Sprite iSprite;
	//Make a Font called FontAtlas
	Font FontAtlas;
	//Make a std for map and vector
	std::map<char,Char> charMap;
	std::vector<Char> DrawList;
	//Make a int called CharCount
	int CharCount;
	//Make four GLUints
	GLuint PositionBuffer;
	GLuint ColorBuffer;
	GLuint UVBuffer;
	GLuint MatrixBuffer;
};
#endif