///////////////////////////////////////////////////
//File:              <Quad.h>
//Author:            <Hunter Bergerud>
//Date Created:      <3/3/14>
//Date Modified:     <3/10/14>
//Brief:             <Quad Class>
///////////////////////////////////////////////////
#ifndef _QUAD_H_
#define _QUAD_H_
#include <SOIL.h>
#include "Utilities.h"
//Make a class called Quad
class Quad
{
public:
	Quad(void);
	~Quad(void);
	//Make 3 GLuints
	GLuint m_VBO;
	GLuint m_EBO;
	GLuint m_VAO;
	//Make 2 GLuints for the Shaders
	GLuint m_FragmentShader;
	GLuint m_VertexShader;
	//Make 2 GLuints for the Shader Program
	GLuint m_ShaderProgram;
	//Make a Vertex Array
	Vertex m_aoVerts[4];
	//Make 2 Vector2s for the minimum and maximum UV coordinates
	Vector2 m_minUVCoords;
	Vector2 m_maxUVCoords;
	//Make a Vector2 for the UV scale
	Vector2 m_uvScale;
	//Make a float for zooming in on the object
	float m_fZoom;
	//Make 3 Matrix4s
	Matrix4* modelMatrix;
	Matrix4* viewMatrix;
	Matrix4* MVP;
	//Make a unsigned int
	unsigned int m_uiTexture;
	//Make a GLFWwindow for game
	GLFWwindow * GameWindow;
	//Make 2 unsigned ints
	unsigned int	m_uSourceBlendMode;
	unsigned int	m_uDestinationBlendMode;
	//Make 4 ints
	int tex_location;
	int matrix_location;
	int proj_location;
	int view_location;
	//Make a void function called Draw
	void Draw();
	//Make 2 bool functions with the required data
	bool LoadVertShader(const char*);
	bool LoadFragShader(const char*);
	//Make a bool function called LinkShaders
	bool LinkShaders();
	//Make a void function called LoadTexture with the required data
	void LoadTexture(const char* a_pTexture);
	//Make a void function called SetUVData
	void SetUVData();
	//Make 3 void functions for setting color
	void SetColor();
	void SetColor(Vector4 a_v4Color);
	void SetColor(Vector4 a_v4Color0,Vector4 a_v4Color1,Vector4 a_v4Color2,Vector4 a_v4Color3);
private:

};
#endif _QUAD_H_