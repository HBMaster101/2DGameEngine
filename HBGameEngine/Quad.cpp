//////////////////////////////////////
//File:              <Quad.cpp>
//Author:            <Hunter Bergerud>
//Date Created:      <3/3/14>
//Date Modified:     <3/10/14>
//Brief:             <Quad Code>
//////////////////////////////////////
#include "Quad.h"
Quad::Quad(void)
{

	//Default Vertex Shader
	const char * VertexShader = 
		"#version 330\n"
		"in vec3 position;"
		"in vec4 color;"
		"in vec2 texcoord;"
		"out vec4 vColor;"
		"out vec2 UV;"
		"void main() {"
		"	vColor = color;"
		"	UV = texcoord;"
		"	gl_Position = vec4 (position, 1.0);"
		"}";

	//Default Fragment Shader
	const char * FragmentShader =
		"#version 330\n"
		"in vec4 vColor;"
		"in vec2 UV;"
		"out vec4 outColour;"
		"void main () {"
		"	outColour = vColor;"
		"}";

	//Compile Vertex Shader
	m_VertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(m_VertexShader, 1, &VertexShader, NULL);
	glCompileShader(m_VertexShader);
	printShaderInfoLog(m_VertexShader);

	//Compile Fragment Shader
	m_FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(m_FragmentShader, 1, &FragmentShader, NULL);
	glCompileShader(m_FragmentShader);
	printShaderInfoLog(m_FragmentShader);

	//Link Shaders into Shader Program
	m_ShaderProgram = glCreateProgram();

	glAttachShader(m_ShaderProgram, m_FragmentShader);
	glAttachShader(m_ShaderProgram, m_VertexShader);

	glLinkProgram(m_ShaderProgram);
	printProgramInfoLog(m_ShaderProgram);

	glUseProgram(m_ShaderProgram);

	//Set the position
	m_aoVerts[0].Pos = Vector3(	-0.5f,  0.5f,  0.0f);
	m_aoVerts[1].Pos = Vector3(	0.5f,  0.5f,  0.0f);
	m_aoVerts[2].Pos = Vector3(	-0.5f,  -0.5f,  0.0f);
	m_aoVerts[3].Pos = Vector3(	0.5f,  -0.5f,  0.0f);
	
	//Set the color
	SetColor( 
		Vector4(1.0f,  0.0f,  0.0f, 1.0f),
		Vector4(0.0f,  1.0f,  0.0f, 1.0f), 
		Vector4(0.0f,  0.0f,  1.0f, 1.0f), 
		Vector4(1.0f,  1.0f,  1.0f, 1.0f));

	//Set the UV coordinates
	m_aoVerts[0].UV = Vector2(0.0f,  0.0f);
	m_aoVerts[1].UV = Vector2(1.0f,  0.0f);
	m_aoVerts[2].UV = Vector2(0.0f,  1.0f);
	m_aoVerts[3].UV = Vector2(1.0f,  1.0f);
	//Make a GLuint array with 4 elements
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
	//Vertex Attribute Pointers
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(colAttrib, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
	glVertexAttribPointer(uvAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(7 * sizeof(float)));
	//Bind Vertex Array
	glBindVertexArray(0);
	//Make these Matrix4s new Matrix4s
	modelMatrix = new tbyte::Matrix4();
	viewMatrix = new tbyte::Matrix4();
	MVP = new tbyte::Matrix4();
	//Make these Matrix4 pointers each equal the IdentityMatrix
	*modelMatrix = tbyte::Matrix4::IdentityMatrix();
	*viewMatrix = tbyte::Matrix4::IdentityMatrix();
	*MVP = tbyte::Matrix4::IdentityMatrix();
	//Make the matrix_location equal the Uniform Location of the Shader Program
	matrix_location = glGetUniformLocation (m_ShaderProgram, "matrix");
}
Quad::~Quad(void)
{
	//Delete these Matrix4s
	delete modelMatrix;
	delete viewMatrix;
	delete MVP;
}
void Quad::Draw()
{
	

	//Call glBlendFunc with the required data 
	glBlendFunc (m_uSourceBlendMode, m_uDestinationBlendMode);
	//Call glUseProgram with the required data
	glUseProgram(m_ShaderProgram);

	glUniformMatrix4fv (matrix_location, 1, GL_FALSE, MVP->m_afArray);
	//Call glActiveTexture with the required data
	glActiveTexture(GL_TEXTURE0);
	//Call glUniform1i with the required data
	glUniform1i (tex_location, 0); 
	glBindTexture( GL_TEXTURE_2D,m_uiTexture);
	//Bind buffers and the Vertex Array
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);	// EBO
	glBindVertexArray(m_VAO);						// VAO
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);			// VBO
	//Put Data into buffers
	glBufferData(GL_ARRAY_BUFFER, 4* sizeof(Vertex), m_aoVerts, GL_STATIC_DRAW);
	//Draw elements
	glDrawElements(GL_TRIANGLE_STRIP, 4,GL_UNSIGNED_INT,0);	
}
//Load the Vertex Shader
bool Quad::LoadVertShader(const char* filePath)
{
	std::string vs =textFileReader(filePath);
	const char * VertexShader = vs.c_str();
	glShaderSource(m_VertexShader, 1, &VertexShader, NULL);
	glCompileShader(m_VertexShader);
	printShaderInfoLog(m_VertexShader);
	return printShaderInfoLog(m_VertexShader);
}
//Load the Fragment Shader
bool Quad::LoadFragShader(const char* filePath)
{
	std::string vs =textFileReader(filePath);
	const char * FragmentShader = vs.c_str();
	glShaderSource(m_FragmentShader, 1, &FragmentShader, NULL);
	glCompileShader(m_FragmentShader);
	return printShaderInfoLog(m_FragmentShader);
}
//Link the Shaders
bool Quad::LinkShaders()
{
	glAttachShader(m_ShaderProgram, m_FragmentShader);
	glAttachShader(m_ShaderProgram, m_VertexShader);
	glLinkProgram(m_ShaderProgram);
	glUseProgram(m_ShaderProgram);
	return printProgramInfoLog(m_ShaderProgram);
}
//
void Quad::LoadTexture(const char* a_pTexture)
{
	m_uiTexture = 0;
	m_uSourceBlendMode	= GL_SRC_ALPHA;
	m_uDestinationBlendMode = GL_ONE_MINUS_SRC_ALPHA;
	glGenTextures(1, &m_uiTexture);
	glActiveTexture (GL_TEXTURE0);
	int width, height;
	unsigned char* image = SOIL_load_image(a_pTexture, &width, &height, 0, SOIL_LOAD_RGBA);
	glBindTexture( GL_TEXTURE_2D,m_uiTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	tex_location = glGetUniformLocation (m_ShaderProgram, "diffuseTexture");
	m_minUVCoords = Vector2( 0.f, 0.f );
	m_maxUVCoords = Vector2( 1.f, 1.f );
	m_uvScale = Vector2( 1.f, 1.f );
	m_fZoom = 1.f;
}
//Set the UV Data
void Quad::SetUVData()
{
	m_aoVerts[0].UV = Vector2(m_minUVCoords.m_fX/m_uvScale.m_fX,
							  m_minUVCoords.m_fY/m_uvScale.m_fY);
	
	m_aoVerts[1].UV = Vector2(m_minUVCoords.m_fX/m_uvScale.m_fX,
							  m_maxUVCoords.m_fY/m_uvScale.m_fY);
	
	m_aoVerts[2].UV = Vector2(m_maxUVCoords.m_fX/m_uvScale.m_fX,
							  m_minUVCoords.m_fY/m_uvScale.m_fY);
	
	m_aoVerts[3].UV = Vector2(m_maxUVCoords.m_fX/m_uvScale.m_fX,
							  m_maxUVCoords.m_fY/m_uvScale.m_fY);

}
//Set the color
void Quad::SetColor()
{
	m_aoVerts[0].Color = Vector4(1.0f,  1.0f,  1.0f, 1.0f);
	m_aoVerts[1].Color = Vector4(1.0f,  1.0f,  1.0f, 1.0f);
	m_aoVerts[2].Color = Vector4(1.0f,  1.0f,  1.0f, 1.0f);
	m_aoVerts[3].Color = Vector4(1.0f,  1.0f,  1.0f, 1.0f);
}
//Set the color with the required data
void Quad::SetColor(Vector4 a_v4Color)
{
	m_aoVerts[0].Color = a_v4Color;
	m_aoVerts[1].Color = a_v4Color;
	m_aoVerts[2].Color = a_v4Color;
	m_aoVerts[3].Color = a_v4Color;

}
//Set the color with the required data
void Quad::SetColor(Vector4 a_v4Color0,
					Vector4 a_v4Color1,
					Vector4 a_v4Color2,
					Vector4 a_v4Color3)
{
	m_aoVerts[0].Color = a_v4Color0;
	m_aoVerts[1].Color = a_v4Color1;
	m_aoVerts[2].Color = a_v4Color2;
	m_aoVerts[3].Color = a_v4Color3;
}