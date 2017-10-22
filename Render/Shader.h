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

#ifndef SHADER_H
#define SHADER_H

#include <GL/gl3w.h>

#include "../ThirdParty/glm/glm.hpp"
#include "../ThirdParty/glm/gtc/matrix_transform.hpp"
#include "../ThirdParty/glm/gtc/type_ptr.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "../Logger.h"

namespace uzh {

	class Shader {
		public:
			Shader();
			bool loadVertexSource(std::string path);
			bool loadFragmentSource(std::string path);
			bool link();
			void bind();

			void loadInteger(const std::string& loc, int n);
			void loadFloat(const std::string& loc, float n);

			void loadVector2(const std::string& loc, glm::vec2& vec);
			void loadVector3(const std::string& loc, glm::vec3& vec);
			void loadVector4(const std::string& loc, glm::vec4& vec);

			void loadMatrix(const std::string& loc, glm::mat4& mat);

		private:
			GLuint program;
			GLuint vertex;
			GLuint fragment;

			bool linked;

			std::ofstream file;

			bool checkShader(GLuint id, bool isProgram);
	};
}

#endif