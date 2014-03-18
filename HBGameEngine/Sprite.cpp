//////////////////////////////////////
//File:              <Sprite.cpp>
//Author:            <Hunter Bergerud>
//Date Created:      <3/3/14>
//Date Modified:     <3/10/14>
//Brief:             <Sprite Code>
//////////////////////////////////////
#include "Sprite.h"

Sprite::Sprite(void)
{
	srand(time(NULL));
	//Load the Vertex and Fragment Shaders
	LoadVertShader("resources/VertexShader.glsl");
	LoadFragShader("resources/FragmentShader.glsl");
	//Link the Shaders
	LinkShaders();
	//Set the Sprite Color
	m_v4SpriteColor = Vector4(1,1,1,1);
	//Set the Color to SpriteColor
	m_aoVerts[0].Color = m_v4SpriteColor;
	m_aoVerts[1].Color = m_v4SpriteColor;
	m_aoVerts[2].Color = m_v4SpriteColor;
	m_aoVerts[3].Color = m_v4SpriteColor;
	//Set the UV coordinates
	m_aoVerts[0].UV = Vector2(1.0f,  0.0f);
	m_aoVerts[1].UV = Vector2(0.0f,  1.0f);
	m_aoVerts[2].UV = Vector2(1.0f,  0.0f);
	m_aoVerts[3].UV = Vector2(1.0f,  1.0f);
	//Set the Scale
	m_v2Scale = Vector2(1,1);
	//Set the Position
	m_v3Position = Vector3(g_gl_width/2,g_gl_height/2,0);
}
Sprite::~Sprite(void)
{
}
Sprite::Sprite(const char* a_pTexture, int a_iWidth, int a_iHeight, tbyte::Vector4 a_v4Color, GLFWwindow * window)
{
	//Make GameWindow equal to window
	GameWindow = window;
	//Load the Vertex and Fragment Shaders
	LoadVertShader("resources/VertexShader.glsl");
	LoadFragShader("resources/FragmentShader.glsl");
	//Link the Shaders
	LinkShaders();

	//Set the position
	m_aoVerts[0].Pos = Vector3(	-0.5f,  0.5f,  0.0f);
	m_aoVerts[1].Pos = Vector3(	0.5f,  0.5f,  0.0f);
	m_aoVerts[2].Pos = Vector3(	-0.5f,  -0.5f,  0.0f);
	m_aoVerts[3].Pos = Vector3(	0.5f,  -0.5f,  0.0f);
	//Set the Sprite Color
	m_v4SpriteColor = a_v4Color;
	//Set the Color to SpriteColor
	m_aoVerts[0].Color = m_v4SpriteColor;
	m_aoVerts[1].Color = m_v4SpriteColor;
	m_aoVerts[2].Color = m_v4SpriteColor;
	m_aoVerts[3].Color = m_v4SpriteColor;
	//Set the UV coordinates
	m_aoVerts[0].UV = Vector2(0.0f,  0.0f);
	m_aoVerts[1].UV = Vector2(0.0f,  1.0f);
	m_aoVerts[2].UV = Vector2(1.0f,  0.0f);
	m_aoVerts[3].UV = Vector2(1.0f,  1.0f);
	//Make a GLint and equal it to glGetAttribLocation
	GLint uvAttrib = glGetAttribLocation(m_ShaderProgram,"texcoord");
	//Call glEnableVertexAttribArray with the required data
	glEnableVertexAttribArray(uvAttrib);
	//Make matrix_location equal to glGetUniformLocation
	matrix_location = glGetUniformLocation(m_ShaderProgram, "matrix");
	//Call LoadTexture with the required data
	LoadTexture(a_pTexture);

	//Set the Scale
	m_v2Scale = tbyte::Vector2(a_iWidth,a_iHeight);
	//Set the Position
	m_v3Position = tbyte::Vector3(0,0,0);
}
//Draw the Sprite
void Sprite::Draw()
{
	modelMatrix->m_afArray[0]  = m_v2Scale.m_fX;
	modelMatrix->m_afArray[5]  = m_v2Scale.m_fY;
	modelMatrix->m_afArray[12] = m_v3Position.m_fX;
	modelMatrix->m_afArray[13] = m_v3Position.m_fY;
	modelMatrix->m_afArray[14] = m_v3Position.m_fZ;
	//Matrix4 MVP = (*Ortho * *modelMatrix);
	*MVP = (*Ortho * *modelMatrix);
	Quad::Draw();
}
void Sprite::Input()
{
	//If the "W" Key is press when the user is in the GameWindow
	if(GLFW_PRESS == glfwGetKey(GameWindow, GLFW_KEY_W))
	{
		//Move the Sprite Up
		m_v3Position += tbyte::Vector3(0.0f, 1.f, 0.0f);
	}
	//If the "A" Key is press when the user is in the GameWindow
	if(GLFW_PRESS == glfwGetKey(GameWindow, GLFW_KEY_A))
	{
		//Move the Sprite Left
		m_v3Position += tbyte::Vector3(-1.f, 0.0f, 0.0f);
	}
	//If the "S" Key is press when the user is in the GameWindow
	if(GLFW_PRESS == glfwGetKey(GameWindow, GLFW_KEY_S))
	{
		//Move the Sprite Down
		m_v3Position += tbyte::Vector3(0.0f, -1.f, 0.0f);
	}
	//If the "D" Key is press when the user is in the GameWindow
	if(GLFW_PRESS == glfwGetKey(GameWindow, GLFW_KEY_D))
	{
		//Move the Sprite Right
		m_v3Position += tbyte::Vector3(1.f, 0.0f, 0.0f);
	}
}
//Set the Position of the Sprite
void Sprite::SetPosition(Vector3 a_v3Pos)
{
	//Vector3 m_v3Position = a_v3Pos; // don't redeclare the class member
	m_v3Position = a_v3Pos;
}
//
void Sprite::SetPosition(float a_fX, float a_fY)
{
	m_v3Position.m_fX  = a_fX;
	m_v3Position.m_fY  = a_fY;

}
//
Vector3 Sprite::GetPosition()
{
	return m_v3Position;

}
//
void Sprite::SetScale(Vector2 a_v2Scale)
{
	m_v2Scale = a_v2Scale;
}
//
void Sprite::SetScale(float a_fScale)
{
	m_v2Scale.m_fX = a_fScale;
	m_v2Scale.m_fY = a_fScale;
}
//
void Sprite::SetScale(float a_fScaleX,float a_fScaleY)
{
	m_v2Scale.m_fX = a_fScaleX;
	m_v2Scale.m_fY = a_fScaleY;
}
//
Vector2 Sprite::GetScale()
{
	return m_v2Scale;

}