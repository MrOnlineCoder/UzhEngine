/*
	UzhEngine Project

	Copyright (c) 2017 Nikita Kogut (MrOnlineCoder)
	mronlinecoder@gmail.com
	github.com/MrOnlineCoder

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.

*/


#include "Shader.h"

void uzh::Shader::bind() {
	if (linked) glUseProgram(program);
}

uzh::Shader::Shader() {
	linked = false;

	vertex = -1;
	fragment = -1;
}

bool uzh::Shader::loadVertexSource(std::string path) {
	std::ifstream file;
	file.open(path);

	if (!file) {
		GLOG.log("Shader", "Error: Failed to open vertex shader: "+path);
		return false;
	}

	std::stringstream sstream;
	sstream << file.rdbuf();
	file.close();

	std::string src = sstream.str();
	const char* rawSource = src.c_str();

	vertex = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertex, 1, &rawSource, NULL);

	glCompileShader(vertex);

	return checkShader(vertex, false);
}

bool uzh::Shader::loadFragmentSource(std::string path) {
	std::ifstream file;
	file.open(path);

	if (!file) {
		GLOG.log("Shader", "Error: Failed to open fragment shader: "+path);
		return false;
	}

	std::stringstream sstream;
	sstream << file.rdbuf();
	file.close();

	std::string src = sstream.str();
	const char* rawSource = src.c_str();

	fragment = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragment, 1, &rawSource, NULL);

	glCompileShader(fragment);

	return checkShader(fragment, false);
}

bool uzh::Shader::link() {
	program = glCreateProgram();

	if (vertex != -1) {
		glAttachShader(program, vertex);
	}

    if (fragment != -1) {
		glAttachShader(program, fragment);
	}

    glLinkProgram(program);

	linked = true;

	glDeleteShader(vertex);
    glDeleteShader(fragment);

	return checkShader(program, true);
}

bool uzh::Shader::checkShader(GLuint id, bool isProgram) {
	int success = 1;
	char errorLog[1024];

	if (isProgram) {
		glGetProgramiv(id, GL_LINK_STATUS, &success);
		if (!success) {
		   glGetProgramInfoLog(id, 1024, NULL, errorLog);
		   GLOG.log("Shader", "Error: Failed to link shader program: ");
		   GLOG.log("OpenGLShaderCompiler", errorLog);
		   return false;
		}
	} else {
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);
		if (!success) {
		   glGetShaderInfoLog(id, 1024, NULL, errorLog);
		   GLOG.log("Shader", "Error: Failed to compile vertex/fragment shader: " );
		   GLOG.log("OpenGLShaderCompiler", errorLog);
		   return false;
		}
	}

	return true;
}