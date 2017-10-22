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

#include "Engine.h"

void uzh::Engine::_crash(std::string msg) {
	MessageBox(NULL, msg.c_str(), "Engine Fatal Error :(", MB_OK | MB_SYSTEMMODAL | MB_ICONHAND);
	ExitProcess(-1);
}

int uzh::Engine::run() {
	if (!GLOG.init()) _crash("Failed to init logging system!");

	GLOG.log("Engine", "Starting engine...");

	GLOG.log("Engine", "Creating sf::ContextSettings");
	contextSettings.antialiasingLevel = 4;
	contextSettings.depthBits = 24;
	contextSettings.stencilBits = 8;

	// Use OpenGL 3.1
	contextSettings.majorVersion = 3;
	contextSettings.minorVersion = 1;

	GLOG.log("Engine", "Creating RenderWindow...");
	window.create(sf::VideoMode(1280, 720), "UzhEngine Application", sf::Style::Default, contextSettings);
	window.setActive(true);
	window.setFramerateLimit(60);

	GLOG.log("Engine", "Loading GL functions through gl3wInit():");
	int gl3wResult = 0;
	if (gl3wResult = gl3wInit()) {
		GLOG.log("Engine", "ERROR: gl3wInit() failed, error code: "+std::to_string(gl3wResult));
		_crash("gl3wInit() call failed.");
	} else {
		GLOG.log("Engine", "Functions loaded.");
	}

	uzh::Shader testShader;
	testShader.loadVertexSource("Content/Shaders/basic.vert");
	testShader.loadFragmentSource("Content/Shaders/basic.frag");
	testShader.link();

	uzh::Texture tex;
	tex.loadFromFile("Content/texture.jpg");

	GLfloat verts[] = {
         0.0f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
    };

	GLfloat texCoords[] = {
         0.0f,  0.0f, 
         1.0f,  0.0f,
         0.5f,  1.0f
    };

	std::vector<GLfloat> v(verts, verts + 9);
	std::vector<GLfloat> tv(texCoords, texCoords + 6);

	Model model;
	model.addVBO(3, v);
	model.addTexCoords(tv);

	GLOG.log("Engine", "Entering window event loop..");
	while (window.isOpen()) {
		sf::Event ev;
		while (window.pollEvent(ev)) {
			switch (ev.type) {
				case sf::Event::Closed:
					GLOG.log("SFMLEventLoop", "sf::Event::Closed got! Closing window...");
					window.close();
					break;
				case sf::Event::KeyReleased:
					if (ev.key.code == sf::Keyboard::F2) {
						wireframeMode = !wireframeMode;
						GLOG.log("Debug", "Switching wireframe mode: "+std::to_string(wireframeMode));
						glPolygonMode(GL_FRONT_AND_BACK, wireframeMode ? GL_LINE : GL_FILL);
					}
			}
		}
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		testShader.bind();
		glActiveTexture(GL_TEXTURE0);
		tex.bind();

		model.render();

		window.display();
	}

	GLOG.log("Engine", "Cleaning up...");
	GLOG.log("Engine", "- Total Shutdown -");
	GLOG.close();
	return 0;
}

uzh::Engine::Engine() {
	wireframeMode = false;
}