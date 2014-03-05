//////////////////////////////////////
//File:              <Log.cpp>
//Author:            <Hunter Bergerud>
//Date Created:      <3/3/14>
//Date Modified:     <3/3/14>
//Brief:             <Log Code>
//////////////////////////////////////
#include "Log.h"
bool restart_gl_log () 
{
  //Make a FILE pointer called file and make it equal to fopen with the required data
  FILE* file = fopen (LOG_FILE, "w+");
  //If file is nonexistent
  if (!file) 
  {
	//Print out an error telling the user file cannot open
    fprintf (stderr, "ERROR: could not open %s log file for writing\n", LOG_FILE);
	//Return false
    return false;
  }
  //Make a time_t called now and equal it to time with the required data
  time_t now = time (NULL);
  //Make a char pointer called date and equal it to ctime with the required data
  char* date = ctime (&now);
  //Print out file with current time and date
  fprintf (file, "%s log. local time %s\n", LOG_FILE, date);
  //Close file
  fclose (file);
  //Return true
  return true;
}
bool gl_log (const char* message, const char* filename, int line) 
{
  ////Make a FILE pointer called file and make it equal to fopen with the required data
  FILE* file = fopen (LOG_FILE, "a+");
  //If file is nonexistent
  if (!file) 
  {
	////Print out an error telling the user file cannot open
    fprintf (stderr, "ERROR: could not open %s for writing\n", LOG_FILE);
	//Return false
    return false;
  }
  //Print out file with filename, line, message
  fprintf (file, "%s:%i %s\n", filename, line, message);
  //Close file
  fclose (file);
  //Return true
  return true;
}
bool printShaderInfoLog(GLuint obj)
{
	//Make an int called infologLength and equal it to 0
	int infologLength = 0;
	//Make an int called charsWritten and equal it to 0
	int charsWritten  = 0;
	//Make a char pointer called infoLog
	char *infoLog;
	//Call glGetShaderiv with the required data
	glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &infologLength);
	//If infoLogLength is greater than zero
	if (infologLength > 0)
	{
		//Make infoLog equal char pointer times malloc with the required data
		infoLog = (char *)malloc(infologLength);
		//Call  glGetShaderInfoLog with the required data
		glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
		//Print out infoLog
		printf("%s\n",infoLog);
		//Release infoLog
		free(infoLog);
		//Return false
		return false;
	}
	//Return true
	return true;
}
bool printProgramInfoLog(GLuint obj)
{
	//Make an int called infologLength and equal it to 0
	int infologLength = 0;
	//Make an int called charsWritten and equal it to 0
	int charsWritten  = 0;
	//Make a char pointer called infoLog
	char *infoLog;
	//Call glGetShaderiv with the required data
	glGetProgramiv(obj, GL_INFO_LOG_LENGTH, &infologLength);
	//If infoLogLength is greater than zero
	if (infologLength > 0)
	{
		//Make infoLog equal char pointer times malloc with the required data
		infoLog = (char *)malloc(infologLength);
		//Call  glGetShaderInfoLog with the required data
		glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
		//Print out infoLog
		printf("%s\n",infoLog);
		//Release infoLog
		free(infoLog);
		//Return false
		return false;
	}
	//Return true
	return true;
}
//Make a void function called log_gl_params
void log_gl_params () 
{
	GLenum params[] = {
		GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS,
		GL_MAX_CUBE_MAP_TEXTURE_SIZE,
		GL_MAX_DRAW_BUFFERS,
		GL_MAX_FRAGMENT_UNIFORM_COMPONENTS,
		GL_MAX_TEXTURE_IMAGE_UNITS,
		GL_MAX_TEXTURE_SIZE,
		GL_MAX_VARYING_FLOATS,
		GL_MAX_VERTEX_ATTRIBS,
		GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS,
		GL_MAX_VERTEX_UNIFORM_COMPONENTS,
		GL_MAX_VIEWPORT_DIMS,
		GL_STEREO,
	};
	const char* names[] = {
		"GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS",
		"GL_MAX_CUBE_MAP_TEXTURE_SIZE",
		"GL_MAX_DRAW_BUFFERS",
		"GL_MAX_FRAGMENT_UNIFORM_COMPONENTS",
		"GL_MAX_TEXTURE_IMAGE_UNITS",
		"GL_MAX_TEXTURE_SIZE",
		"GL_MAX_VARYING_FLOATS",
		"GL_MAX_VERTEX_ATTRIBS",
		"GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS",
		"GL_MAX_VERTEX_UNIFORM_COMPONENTS",
		"GL_MAX_VIEWPORT_DIMS",
		"GL_STEREO",
	};
	gl_log ("GL Context Params:", __FILE__, __LINE__);
	char msg[256];
	for (int i = 0; i < 10; i++) {
		int v = 0;
		glGetIntegerv (params[i], &v);
		sprintf (msg, "%s %i", names[i], v);
		gl_log (msg, __FILE__, __LINE__);
	}
	int v[2];
	v[0] = v[1] = 0;
	glGetIntegerv (params[10], v);
	sprintf (msg, "%s %i %i", names[10], v[0], v[1]);
	gl_log (msg, __FILE__, __LINE__);
	unsigned char s = 0;
	glGetBooleanv (params[11], &s);
	sprintf (msg, "%s %i", names[11], (unsigned int)s);
	gl_log (msg, __FILE__, __LINE__);
	gl_log ("-----------------------------", __FILE__, __LINE__);
}