///////////////////////////////////////////
//File:              <AnimatedSprite.cpp>
//Author:            <Hunter Bergerud>
//Date Created:      <3/6/14>
//Date Modified:     <3/11/14>
//Brief:             <Animated Sprite Code>
///////////////////////////////////////////
#include "AnimatedSprite.h"
AnimatedSprite::AnimatedSprite(void)
{
}
AnimatedSprite::~AnimatedSprite(void)
{
}
AnimatedSprite::AnimatedSprite( const char* a_pSpriteSheet, GLFWwindow * window)
{
	//Make GameWindow equal window
	GameWindow = window;
	//Make elapsedTime equal 0
	elapsedTime = 0;
	//Load the Shaders
	LoadVertShader("resources/VertexShader.glsl");
	LoadFragShader("resources/FragmentShader.glsl");
	//Link the Shaders
	LinkShaders();
	//Make a GLint and equal it to glGetAttribLocation
	GLint uvAttrib = glGetAttribLocation(m_ShaderProgram,"texcoord");
	//Call glEnableVertexAttribArray with the required data
	glEnableVertexAttribArray(uvAttrib);
	//Make matrix_location equal to glGetUniformLocation
	matrix_location = glGetUniformLocation (m_ShaderProgram, "matrix");
	
	//Load the Sprites,Animations, and Texture
	LoadSprites(a_pSpriteSheet);
	//
	LoadTexture(atlas.sSheet.c_str());
	//Make m_dFrames equal to 1 divided by 2
	m_dFrames = (1.0/2.0);
	//Make currentAnimation equal nothing
	currentAnimation = "";
	//Make the currentSprite equal idle
	//currentSprite = "idle";
	//Make the currentFrame equal 0
	currentFrame = 0;
	//Make uvScale equale the atlas size
	m_uvScale.m_fX = atlas.v2Size.m_fY;
	m_uvScale.m_fY	= atlas.v2Size.m_fX;
	//Call SetSprite
	SetSprite();
	//call SetUVData
	SetUVData();
}
// set the UVcoords and scale
void AnimatedSprite::SetSprite()
{
	//If currentFrame equals 1 - LEFT
	if(currentFrame == 0)
	{
		//Set the min and max UV coordinates to the Sprite's "x"s and "y"s
		m_minUVCoords.m_fX = mSprites["slice03_2.png"].y0;
		m_minUVCoords.m_fY = mSprites["slice03_2.png"].x0;
		
		m_maxUVCoords.m_fX = mSprites["slice03_2.png"].y1;
		m_maxUVCoords.m_fY = mSprites["slice03_2.png"].x1;
		//Set the Scale to the Sprite's width and height
		m_v2Scale.m_fX =  mSprites["slice03_2.png"].width;
		m_v2Scale.m_fY =  mSprites["slice03_2.png"].height;
	}
	else
	{
		//Set the min and max UV coordinates to currentSprite's "x"s and "y"s
		m_minUVCoords.m_fX = mSprites["slice06_4.png"].y0;
		m_minUVCoords.m_fY = mSprites["slice06_4.png"].x0;
		
		m_maxUVCoords.m_fX = mSprites["slice06_4.png"].y1;
		m_maxUVCoords.m_fY = mSprites["slice06_4.png"].x1;
		//Set the Scale to the currentSprite's width and height
		m_v2Scale.m_fX =  mSprites["slice06_4.png"].width;
		m_v2Scale.m_fY =  mSprites["slice06_4.png"].height;
	}
}
//Load the sprites
void AnimatedSprite::LoadSprites(const char* a_pSpriteSheet)
{
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLNode *rootNode, *currentNode;
	tinyxml2::XMLElement *childElement;
	std::string str;
	doc.LoadFile(a_pSpriteSheet);
	rootNode = doc.FirstChildElement("TextureAtlas");
	currentNode = rootNode;
	childElement = currentNode->ToElement();
	atlas.v2Size.m_fX = (float)childElement->IntAttribute("width"); 
	atlas.v2Size.m_fY = (float)childElement->IntAttribute("height");
	atlas.sSheet = childElement->Attribute("imagePath");
	for (childElement = currentNode->FirstChildElement(); 
		childElement != NULL; childElement = childElement->NextSiblingElement())
	{
		str = childElement->Attribute("name");
		mSprites[str].Name = str;
		mSprites[str].x0 = childElement->IntAttribute("x");
		mSprites[str].y0 = childElement->IntAttribute("y");
		mSprites[str].width = childElement->IntAttribute("width");
		mSprites[str].height = childElement->IntAttribute("height");
		mSprites[str].x1 = mSprites[str].x0 + mSprites[str].width;
		mSprites[str].y1 = mSprites[str].y0 + mSprites[str].height;
	}
	std:printf("done");
}
//Load the animations
/*void AnimatedSprite::LoadAnimations(const char* a_pAnimationSheet)
{
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLNode *rootNode, *currentNode;
	tinyxml2::XMLElement *childElement, *child;
	std::string str,aniName;
	doc.LoadFile(a_pAnimationSheet);
	rootNode = doc.FirstChildElement("animation");
	currentNode = rootNode;
	for (childElement = currentNode->ToElement(); 
		childElement != NULL; childElement = childElement->NextSiblingElement())
	{
		aniName = childElement->Attribute("name");
		int i = 0;
		for (child = childElement->FirstChildElement(); 
			child != NULL; child = child->NextSiblingElement())
		{

			str = child->Attribute("name");
			mAnimations[aniName].push_back(str);
			i++;
		}
	}
	std:printf("done");
}
void AnimatedSprite::SetAnimation(std::string animation,PlayType type)
{

	//Set currentAnimation to animation
	currentAnimation = animation;
	//Set currentFrame and loopFrame to 0
	currentFrame = 0;
	loopFrame = 0;
	//Set currentPlayType to type
	currentPlayType = type;
	//Make a switch for type
	switch (type)
	{
		//Case ONCE
		case ONCE:
			break;
		//Case LOOP
		case LOOP:
			loopFrame = 0;
			break;
		//Case PINGPONG
		case PINGPONG:
			break;
		//Case REVERSE
		case REVERSE:
			currentFrame = mAnimations[currentAnimation].size();
			loopFrame = currentFrame;
			break;
		//Case RANDOMLOOP
		case RANDOMLOOP:
		//Case RANDOM
		case RANDOM:
			srand(time(NULL));
			currentFrame =  (unsigned int)(rand() % mAnimations[currentAnimation].size());
			loopFrame = currentFrame;
			break;
		//Case LOOPSECTION
		case LOOPSECTION:
			SetAnimation(animation,type, 0);
		//Case SINGLE
		case SINGLE:
			break;
		//Default
		default:
			break;
	}
	//Set currentSprite to currentAnimation's currentFrame
	currentSprite = mAnimations.at(currentAnimation)[currentFrame];
	//Call SetSprite
	SetSprite();
	//Call SetUVData
	SetUVData();
}
void AnimatedSprite::SetAnimation(std::string animation,PlayType type, int frame)
{
	//Make a switch for type
	switch(type)
	{
		//Case LOOPSECTION
		case LOOPSECTION:
			currentAnimation = animation;
			currentFrame = 0;
			currentPlayType = type;
			loopFrame = frame;
			break;
		//Default
		default:
			SetAnimation(animation,type);
			break;
	}
}*/
void AnimatedSprite::PlayAnimation()
{
	//Add getDeltaTime to elapsedTime
	elapsedTime += getDeltaTime();
	//If elapsedTime is greater than m_dFrames
	if(elapsedTime > m_dFrames)
	{
		// Reset elapsed time
		elapsedTime = 0;
		//Make currentFrame equal 1
		if(currentFrame == 1)
		{
			currentFrame = 0;
		}
		else
		{
			currentFrame = 1;
		}
		//Call SetSprite
		SetSprite();
		//Call SetUVData
		SetUVData();
	}
}

//Draw the Animated Sprite
void AnimatedSprite::Draw()
{
	Sprite::Draw();
}
//Input the Animated Sprite
void AnimatedSprite::Input()
{
	Sprite::Input();
}
//Update the Animated Sprite
void AnimatedSprite::Update()
{
	this->AnimatedSprite::Input();
	this->AnimatedSprite::Draw();
	PlayAnimation();
}