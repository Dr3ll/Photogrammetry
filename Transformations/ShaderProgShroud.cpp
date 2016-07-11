#include "ShaderProgShroud.h"

namespace Protoone
{
	ShaderProgShroud::ShaderProgShroud(string shaderName)
	{
		_prog = glCreateProgram();
		string shaderSource;
		const char* sourcePtr;

		// Vertex shader
		if(true)
		{
			GLuint vertexShaderDepth = glCreateShader(GL_VERTEX_SHADER);
			string shaderSource = readShaderFile(shaderName + ".vert");
			const char* sourcePtr = shaderSource.c_str();
			glShaderSource(vertexShaderDepth, 1, &sourcePtr, NULL);
			glCompileShader(vertexShaderDepth);
			glAttachShader(_prog, vertexShaderDepth);

			//printShaderInfoLog(vertexShaderDepth);
		}

		// Fragment shader
		if(true)
		{
			GLuint fragShaderDepth = glCreateShader(GL_FRAGMENT_SHADER);
			shaderSource = readShaderFile(shaderName + ".frag");
			sourcePtr = shaderSource.c_str();
			glShaderSource(fragShaderDepth, 1, &sourcePtr, NULL);
			glCompileShader(fragShaderDepth);
			glAttachShader(_prog, fragShaderDepth);
		}

		// Colors
		//float myFloats[4] = {1.0f, 0.8f, 0.1f, 1.0f};
		//GLint myLoc = glGetUniformLocation(_prog, "color");
		//glProgramUniform4fv(_prog, myLoc, 1, myFloats);
		
		glLinkProgram(_prog);
	}


	ShaderProgShroud::~ShaderProgShroud(void)
	{
	}

	void ShaderProgShroud::use()
	{
		glUseProgram(_prog);
	}

	void ShaderProgShroud::printShaderInfoLog(GLuint shader)
	{
		GLint infologLength = 0;
		GLsizei charsWritten  = 0;
		char *infoLog;

		glGetShaderiv(shader, GL_INFO_LOG_LENGTH,&infologLength);		
		infoLog = (char *)malloc(infologLength);
		glGetShaderInfoLog(shader, infologLength, &charsWritten, infoLog);
		std::cout << "%s\n" << infoLog;
		free(infoLog);
	}

	string ShaderProgShroud::readShaderFile(string fileName)
	{
		string fileContent;
		string line;

		ifstream file(fileName.c_str());
		if (file.is_open()) {
			while (!file.eof()){
				getline (file,line);
				line += "\n";
				fileContent += line;					
			}
			file.close();
		}
		else
			cout << "ERROR: Unable to open file " << fileName << endl;

		return fileContent;
	}
}