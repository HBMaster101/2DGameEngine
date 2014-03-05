//////////////////////////////////////
//File:              <Sprite.cpp>
//Author:            <Hunter Bergerud>
//Date Created:      <3/3/14>
//Date Modified:     <3/3/14>
//Brief:             <Sprite Code>
//////////////////////////////////////
#include "Sprite.h"

Sprite::Sprite(void)
{
	const char * VertexShader = 
		"#version 330\n"
		" in vec3 position;"
		" in vec4 color;"
		" in vec2 texcoord;"
		"uniform mat4 matrix;"
		"out vec4 vColor;"
		"void main() {"
		"   vColor = color;"
		"   gl_Position = vec4 (position, 1.0);"
		"}";
	const char * FragmentShader =
		"#version 330\n"
		"in vec4 vColor;"
		"out vec4 outColor;"
		"uniform sampler2D diffuseTexture;"
		"void main() {"
		"   outColor = vColor;"
		"}";

	m_VertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(m_VertexShader, 1, &VertexShader,NULL);
	glCompileShader(m_VertexShader);
	printShaderInfoLog(m_VertexShader);

	m_FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(m_FragmentShader, 1, &FragmentShader, NULL);
	glCompileShader(m_FragmentShader);
	printShaderInfoLog(m_FragmentShader);

	m_ShaderProgram = glCreateProgram();

	glAttachShader(m_ShaderProgram, m_FragmentShader);
	glAttachShader(m_ShaderProgram, m_VertexShader);

	glLinkProgram(m_ShaderProgram);
	printProgramInfoLog(m_ShaderProgram);

	glUseProgram(m_ShaderProgram);
}

Sprite::~Sprite(void){}

Sprite::Sprite(const char* a_pTexture, int a_iWidth, int a_iHeight, tbyte::Vector4 a_v4Color, GLFWwindow * window)
{
	GameWindow = window;
	
	LoadVertShader("resources/VertexShader.glsl");
	LoadFragShader("resources/FragmentShader.glsl");
	LinkShaders();

	m_v4SpriteColor = a_v4Color;

	m_aoVerts[0].Pos = tbyte::Vector3( -0.5f,  0.5f, 0.0f);
	m_aoVerts[1].Pos = tbyte::Vector3(  0.5f,  0.5f, 0.0f);
	m_aoVerts[2].Pos = tbyte::Vector3( -0.5f, -0.5f, 0.0f);
	m_aoVerts[3].Pos = tbyte::Vector3( 0.5f, -0.5f, 0.0f);

	m_aoVerts[0].Color = m_v4SpriteColor;
	m_aoVerts[1].Color = m_v4SpriteColor;
	m_aoVerts[2].Color = m_v4SpriteColor;
	m_aoVerts[3].Color = m_v4SpriteColor;

	m_aoVerts[0].UV = tbyte::Vector2(0.0f,  0.0f);
	m_aoVerts[1].UV = tbyte::Vector2(0.0f,  1.0f);
	m_aoVerts[2].UV = tbyte::Vector2(1.0f,  0.0f);
	m_aoVerts[3].UV = tbyte::Vector2(1.0f,  1.0f);

	GLuint elements[] =
	{
		0,1,2,3
	};

	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_EBO);
	glGenVertexArrays(1, &m_VAO);

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

	glBufferData(GL_ARRAY_BUFFER, 4* sizeof(Vertex), m_aoVerts, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	GLint posAttrib = glGetAttribLocation(m_ShaderProgram, "position");
	glEnableVertexAttribArray(posAttrib);
	GLint colAttrib = glGetAttribLocation(m_ShaderProgram, "color");
	glEnableVertexAttribArray(colAttrib);
	GLint uvAttrib = glGetAttribLocation(m_ShaderProgram, "texcoord");
	glEnableVertexAttribArray(uvAttrib);

	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(colAttrib, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
	glVertexAttribPointer(uvAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(7 * sizeof(float)));

	glBindVertexArray(0);

	m_v2Scale = tbyte::Vector2(a_iWidth,a_iHeight);
	m_v3Position = tbyte::Vector3(0,0,0);
	
	modelMatrix = new tbyte::Matrix4();
	viewMatrix = new tbyte::Matrix4();
	
	*modelMatrix  =  modelMatrix->MakeIdentityMatrix();

	//ViewLookAt(tbyte::Vector4(0,0,0,0),tbyte::Vector4(0,0,.5,0),tbyte::Vector4(0,1,0,0), viewMatrix);
	
	modelMatrix->m_afArray[12] = m_v3Position.m_fX;
	modelMatrix->m_afArray[13] = m_v3Position.m_fY;
	modelMatrix->m_afArray[14] = m_v3Position.m_fZ;


	matrix_location = glGetUniformLocation (m_ShaderProgram, "matrix");

	m_uiTexture = 0;
	m_minUVCoords = tbyte::Vector2(0.f, 0.f);
	m_maxUVCoords = tbyte::Vector2(1.f, 1.f);
	m_uvScale = tbyte::Vector2(1.f, 1.f);
	m_uvOffSet = tbyte::Vector2(0.f, 0.f);

	m_uSourceBlendMode = GL_SRC_ALPHA;
	m_uDestinationBlendMode = GL_ONE_MINUS_SRC_ALPHA;

	glGenTextures(1, &m_uiTexture);
	glActiveTexture(GL_TEXTURE0);

	int width, height;
	unsigned char* image = SOIL_load_image(a_pTexture, &width, &height, 0, SOIL_LOAD_RGBA);
	glBindTexture(GL_TEXTURE_2D, m_uiTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	tex_loc = glGetUniformLocation (m_ShaderProgram, "diffuseTexture");

	proj_location = glGetUniformLocation (m_ShaderProgram, "projection");

	view_location = glGetUniformLocation (m_ShaderProgram, "view");
}

void Sprite::Draw()
{
	glBlendFunc (m_uSourceBlendMode, m_uDestinationBlendMode);
	glUseProgram(m_ShaderProgram);
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(tex_loc, 0);


	modelMatrix->m_afArray[0]  = m_v2Scale.m_fX;
	modelMatrix->m_afArray[5]  = m_v2Scale.m_fY;
	modelMatrix->m_afArray[12] = m_v3Position.m_fX;
	modelMatrix->m_afArray[13] = m_v3Position.m_fY;
	modelMatrix->m_afArray[14] = m_v3Position.m_fZ;


	Matrix4 MVP = (*Ortho * *modelMatrix);


	glUniformMatrix4fv (matrix_location, 1, GL_FALSE, MVP.m_afArray);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBindVertexArray(m_VAO);

	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, 0);
}

void Sprite::Input()
{
	if(GLFW_PRESS == glfwGetKey(GameWindow, GLFW_KEY_W))
	{
		m_v3Position += tbyte::Vector3(0.0f, 0.05f, 0.0f);
	}

	if(GLFW_PRESS == glfwGetKey(GameWindow, GLFW_KEY_A))
	{
		m_v3Position += tbyte::Vector3(-0.05f, 0.0f, 0.0f);
	}
	if(GLFW_PRESS == glfwGetKey(GameWindow, GLFW_KEY_S))
	{
		m_v3Position += tbyte::Vector3(0.0f, -0.05f, 0.0f);
	}
	if(GLFW_PRESS == glfwGetKey(GameWindow, GLFW_KEY_D))
	{
		m_v3Position += tbyte::Vector3(0.05f, 0.0f, 0.0f);
	}
}