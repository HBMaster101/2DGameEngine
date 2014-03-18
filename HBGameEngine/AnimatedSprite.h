////////////////////////////////////////////
//File:              <AnimatedSprite.h>
//Author:            <Hunter Bergerud>
//Date Created:      <3/6/14>
//Date Modified:     <3/6/14>
//Brief:             <Animated Sprite Class>
////////////////////////////////////////////
#ifndef _ANIMATED_SPRITE_H_
#define _ANIMATED_SPRITE_H_
#include <tinyxml2.h>
#include "Sprite.h"
//Make a struct called AniSprite
struct AniSprite
{
	//Make a union
	union
	{
		//Make a struct with a string, a Vector2, and a Vector4
		struct
		{
			std::string sName;
			Vector2 v2Size;
			Vector4 v4Location;
		};
		//Make a struct with a string and 2 floats
		struct
		{
			std::string Name;
			float width, height;
			float x0,x1,y0,y1;
		};
	};
};
//Make a struct call Atlas with a Vector2 and 2 strings
struct Atlas
{
	Vector2 v2Pos;
	Vector2 v2Size;
	std::string sSheet;
	std::string sAnimations;
};
//
typedef std::vector<std::string> frame;
//Make a class called AnimatedSprite that is the child of Sprite
class AnimatedSprite : public Sprite
{
public:
	AnimatedSprite(void);
	~AnimatedSprite(void);
	AnimatedSprite( const char* a_pSpriteSheet, GLFWwindow * window);
	//Make a virtual void function called Draw
	virtual void Draw();
	//Make a void function called Update
	void Update();
	//Make a void function to play animation
	void PlayAnimation();
	//Make a void funcition to set sprite
	void SetSprite();
	//Make 2 void functions for loading sprites and animation
	void LoadSprites(const char* a_pSpriteSheet);
	//void LoadAnimations(const char* a_pAnimationSheet);
	//Make a void function called Input
	void Input();
	//Make 2 map strings for sprites and animations
	std::map<std::string,AniSprite> mSprites;
	std::map<std::string,frame> mAnimations;
	//Make a Atlas called atlas
	Atlas atlas;
	//Make a string for checking the current sprite and animation
	std::string currentAnimation, currentSprite;
	//Make 2 ints for the current frame and looping the Frame
	int currentFrame, loopFrame;
	//Make a double called m_dFrames
	double m_dFrames;
//Make a double for the total elapsed time the game has been opened
double elapsedTime;
};
#endif
