#pragma once

#include <iostream>
#include "GL/glew.h";
#include <GL/freeglut.h>
#include <string>
#include <fstream>

using namespace std;

namespace Protoone
{
	class ShaderProgShroud
	{
	private:
		GLuint _prog;

		void printShaderInfoLog(GLuint shader);
		string readShaderFile(string fileName);

	public:
		ShaderProgShroud(string shaderName);
		~ShaderProgShroud(void);

		void use();


	};
}
