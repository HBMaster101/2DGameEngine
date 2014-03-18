//////////////////////////////////////
//File:              <Sprite.h>
//Author:            <Hunter Bergerud>
//Date Created:      <3/3/14>
//Date Modified:     <3/10/14>
//Brief:             <Sprite Class>
//////////////////////////////////////
#ifndef _SPRITE_H_
#define _SPRITE_H_
#include "Quad.h"
//Make a class called Sprite that is a child of Quad
class Sprite: public Quad
{
public:
	Sprite(void);
	~Sprite(void);
	Sprite(const char* a_pTexture, int a_iWidth, int a_iHeight, tbyte::Vector4 a_v4Color, GLFWwindow* window);
	//Make a virtual void called Draw
	virtual void Draw();
	//Make a void called Input
	void Input();
	//Make 2 SetPosition functions
	void SetPosition(Vector3 a_v3Pos);
	void SetPosition(float a_fX, float a_fY);
	//Make a Vector3 function called GetPosition
	Vector3 GetPosition();
	//Make 3 SetScale functions
	void SetScale(Vector2 a_v2Scale);
	void SetScale(float a_fScale);
	void SetScale(float a_fScaleX,float a_fScaleY);
	//Make a Vector2 function called GetScale
	Vector2 GetScale();
	//Make a function to set the Vertex Data
	void SetVertexData( Vertex* a_vertexData );
	//Make a const Vertex pointer function called GetVertexData
	const Vertex* GetVertexData() const;
	//Make a Vector3 for Position
	Vector3 m_v3Position;
protected:
	//Make a Vector2 for Scale
	Vector2 m_v2Scale;
	//Make a Vector4 for SpriteColor
	Vector4 m_v4SpriteColor;
};
//Set the Vertex Data
inline void	Sprite::SetVertexData( Vertex* a_vertexData )
{
	memcpy( &m_aoVerts, a_vertexData, sizeof(Vertex) * 4 );
}
//Get the Vertex Data
inline const Vertex* Sprite::GetVertexData() const
{
	return static_cast<const Vertex*>( m_aoVerts );
}
#endif