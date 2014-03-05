//////////////////////////////////////
//File:              <Quad.cpp>
//Author:            <Hunter Bergerud>
//Date Created:      <3/3/14>
//Date Modified:     <3/3/14>
//Brief:             <Quad Code>
//////////////////////////////////////
#include "Quad.h"

Quad::Quad(void)
{

	//Default Vertex Shader
	const char * VertexShader = 
		"#version 330\n"
		"layout(location = 0) in vec3 position;"
		"layout(location = 1) in vec4 color;"
		"out vec4 vColor;"
		"void main() {"
		"   vColor = color;"
		"   gl_Position = vec4 (position, 1.0);"
		"}";

	//Default Fragment Shader
	const char * FragmentShader =
		"#version 330\n"
		"in vec4 vColor;"
		"out vec4 outColor;"
		"void main() {"
		"   outColor = vColor;"
		"}";

	// Compile Vertex Shader
	m_VertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(m_VertexShader, 1, &VertexShader,0);
	glCompileShader(m_VertexShader);
	printShaderInfoLog(m_VertexShader);

	// Compile Fragment Shader
	m_FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(m_FragmentShader, 1, &FragmentShader, 0);
	glCompileShader(m_FragmentShader);
	printShaderInfoLog(m_FragmentShader);

	// Link Shaders into Shader Program
	m_ShaderProgram = glCreateProgram();
	glAttachShader(m_ShaderProgram, m_FragmentShader);
	glAttachShader(m_ShaderProgram, m_VertexShader);
	glLinkProgram(m_ShaderProgram);
	printProgramInfoLog(m_ShaderProgram);
	glUseProgram(m_ShaderProgram);

	//
	m_aoVerts[0].Pos = tbyte::Vector3(	-0.5f,  0.5f,  0.0f);
	m_aoVerts[1].Pos = Vector3(	0.5f,  0.5f,  0.0f);
	m_aoVerts[2].Pos = Vector3(	-0.5f,  -0.5f,  0.0f);
	m_aoVerts[3].Pos = Vector3(	0.5f,  -0.5f,  0.0f);
	
	//
	SetColor( 
		Vector4(1.0f,  0.0f,  0.0f, 1.0f),
		Vector4(0.0f,  1.0f,  0.0f, 1.0f), 
		Vector4(0.0f,  0.0f,  1.0f, 1.0f), 
		Vector4(1.0f,  1.0f,  1.0f, 1.0f));

	//
	m_aoVerts[0].UV = Vector2(0.0f,  0.0f);
	m_aoVerts[1].UV = Vector2(0.0f,  1.0f);
	m_aoVerts[2].UV = Vector2(1.0f,  0.0f);
	m_aoVerts[3].UV = Vector2(1.0f,  1.0f);

	//
	GLuint elements[] =
	{
		0,1,2,3
	};
	//Gen Buffers
	glGenBuffers(1,&m_VBO);
	glGenBuffers(1,&m_EBO);
	glGenVertexArrays(1, &m_VAO);

	//Bind Buffers
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

	//Put Data into buffers
	glBufferData(GL_ARRAY_BUFFER, 4* sizeof(Vertex), m_aoVerts, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	//Enable some attributes
	GLint posAttrib = glGetAttribLocation(m_ShaderProgram,"position");
	glEnableVertexAttribArray(posAttrib);
	GLint colAttrib = glGetAttribLocation(m_ShaderProgram,"color");
	glEnableVertexAttribArray(colAttrib);
	GLint uvAttrib = glGetAttribLocation(m_ShaderProgram,"texcoord");
	glEnableVertexAttribArray(uvAttrib);


	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(colAttrib, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
	glVertexAttribPointer(uvAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(7 * sizeof(float)));

	glBindVertexArray(0);


	modelMatrix = new tbyte::Matrix4();
	viewMatrix = new tbyte::Matrix4();
	MVP = new tbyte::Matrix4();

	*modelMatrix = tbyte::Matrix4::IdentityMatrix();
	*viewMatrix = tbyte::Matrix4::IdentityMatrix();
	*MVP = tbyte::Matrix4::IdentityMatrix();
	
	matrix_location = glGetUniformLocation (m_ShaderProgram, "matrix");
	
}

Quad::~Quad(void)
{
	delete modelMatrix;
	delete viewMatrix;
	delete MVP;
}

void Quad::Draw()
{
	glBlendFunc (m_uSourceBlendMode, m_uDestinationBlendMode);
	glUseProgram(m_ShaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glUniform1i (tex_location, 0); 

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	glBufferData(GL_ARRAY_BUFFER, 4* sizeof(Vertex), m_aoVerts, GL_STATIC_DRAW);

	glDrawElements(GL_TRIANGLE_STRIP, 4,GL_UNSIGNED_INT,0);	
}
bool Quad::LoadVertShader(const char* filePath)
{
	std::string vs =textFileReader(filePath);
	const char * VertexShader = vs.c_str();
	glShaderSource(m_VertexShader, 1, &VertexShader, NULL);
	glCompileShader(m_VertexShader);
	printShaderInfoLog(m_VertexShader);
	return printShaderInfoLog(m_VertexShader);
}
bool Quad::LoadFragShader(const char* filePath)
{
	std::string vs =textFileReader(filePath);
	const char * FragmentShader = vs.c_str();
	glShaderSource(m_FragmentShader, 1, &FragmentShader, NULL);
	glCompileShader(m_FragmentShader);
	return printShaderInfoLog(m_FragmentShader);
}
bool Quad::LinkShaders()
{

	glAttachShader(m_ShaderProgram, m_FragmentShader);
	glAttachShader(m_ShaderProgram, m_VertexShader);

	glLinkProgram(m_ShaderProgram);
	glUseProgram(m_ShaderProgram);

	return printProgramInfoLog(m_ShaderProgram);
}
void	Quad::SetUVData()
{
	m_aoVerts[0].UV = Vector2(m_minUVCoords.m_fX/m_uvScale.m_fX,m_minUVCoords.m_fY/m_uvScale.m_fY);
	m_aoVerts[1].UV = Vector2(m_minUVCoords.m_fX/m_uvScale.m_fX,m_maxUVCoords.m_fY/m_uvScale.m_fY);
	m_aoVerts[2].UV = Vector2(m_maxUVCoords.m_fX/m_uvScale.m_fX,m_minUVCoords.m_fY/m_uvScale.m_fY);
	m_aoVerts[3].UV = Vector2(m_maxUVCoords.m_fX/m_uvScale.m_fX,m_maxUVCoords.m_fY/m_uvScale.m_fY);

}
void Quad::SetColor()
{
	m_aoVerts[0].Color = Vector4(1.0f,  1.0f,  1.0f, 1.0f);
	m_aoVerts[1].Color = Vector4(1.0f,  1.0f,  1.0f, 1.0f);
	m_aoVerts[2].Color = Vector4(1.0f,  1.0f,  1.0f, 1.0f);
	m_aoVerts[3].Color = Vector4(1.0f,  1.0f,  1.0f, 1.0f);


}
void Quad::SetColor(Vector4 a_v4Color)
{
	m_aoVerts[0].Color = a_v4Color;
	m_aoVerts[1].Color = a_v4Color;
	m_aoVerts[2].Color = a_v4Color;
	m_aoVerts[3].Color = a_v4Color;

}
void Quad::SetColor(Vector4 a_v4Color0,Vector4 a_v4Color1,Vector4 a_v4Color2,Vector4 a_v4Color3)
{
	m_aoVerts[0].Color = a_v4Color0;
	m_aoVerts[1].Color = a_v4Color1;
	m_aoVerts[2].Color = a_v4Color2;
	m_aoVerts[3].Color = a_v4Color3;
}