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

#include "Model.h"

void uzh::Model::render() {
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void uzh::Model::addVBO(int dim, std::vector<GLfloat>& data) {
	if (vbo != 0) {
		glDeleteBuffers(1, &vbo);
	}
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * data.size(), data.data(), GL_STATIC_DRAW);

	//Vertex positions attribute
	glVertexAttribPointer(0, dim, GL_FLOAT, GL_FALSE, dim * sizeof(GLfloat), (GLvoid*) 0);
	glEnableVertexAttribArray(0);
}

void uzh::Model::addTexCoords(std::vector<GLfloat>& data) {
	if (tvbo != 0) {
		glDeleteBuffers(1, &tvbo);
	}
	glBindVertexArray(vao);

	glGenBuffers(1, &tvbo);
	glBindBuffer(GL_ARRAY_BUFFER, tvbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * data.size(), data.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*) 0);
	glEnableVertexAttribArray(1);
}

uzh::Model::Model() {
	vao = 0;
	vbo = 0;

	glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
}

uzh::Model::~Model() {
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &tvbo);
	glDeleteVertexArrays(1, &vao);
}