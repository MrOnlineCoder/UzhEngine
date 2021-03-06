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

#ifndef ENGINE_H
#define ENGINE_H

#include <vector>

#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <GL/gl3w.h>

#include "ThirdParty/glm/glm.hpp"
#include "ThirdParty/glm/gtc/matrix_transform.hpp"
#include "ThirdParty/glm/gtc/type_ptr.hpp"

#include "Logger.h"
#include "Render/Shader.h"
#include "Render/Model.h"
#include "Render/Texture.h"




namespace uzh { 
  class Engine {
  public:
	  int run();
	  Engine();
  private:
	  void _crash(std::string msg);

	  sf::RenderWindow window;
	  sf::ContextSettings contextSettings;

	  bool wireframeMode;
  };
}

#endif