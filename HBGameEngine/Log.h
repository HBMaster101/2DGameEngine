//////////////////////////////////////
//File:              <Log.h>
//Author:            <Hunter Bergerud>
//Date Created:      <3/3/14>
//Date Modified:     <3/3/14>
//Brief:             <Log Class>
//////////////////////////////////////
#define LOG_FILE "gl.log"
#ifndef _LOG_H_
#define _LOG_H_
#include <time.h>
#include <iostream>
#include <GL\glew.h>
//Make a bool function called restart_gl_log
bool restart_gl_log ();
//Make a bool function called gl_log with the required data
bool gl_log (const char* message, const char* filename, int line);
//Make a bool function called printShaderInfoLog with the required data
bool printShaderInfoLog(GLuint obj);
//Make a bool function called printProgramInfoLog with the required data
bool printProgramInfoLog(GLuint obj);
#endif _LOG_H_