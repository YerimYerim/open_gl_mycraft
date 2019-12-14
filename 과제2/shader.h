#include <GL/glew.h> // 필요한 헤더파일 
#include <GL/freeglut.h> 
#include <GL/freeglut_ext.h> 
#include <gl/glm/glm/glm.hpp>
#include <gl/glm/glm/ext.hpp>
#include <gl/glm/glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <time.h>
#include <Windows.h>

GLuint complie_shaders()
{
	const GLchar* vertexShaderSource =
		"#version 330 core\n"
		"void main()"
		"{"
		"gl_Position = vec4(0.0, 0.0, 0.5, 1.0);"
		"}";
	//---버텍스세이더읽어저장하고컴파일하기 
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
		std::cerr << "ERROR: vertex shader 컴파일실패\n" << errorLog << std::endl;
		return false;
	}

	const GLchar* fragmentShaderSource =
		"#version 330 core\n"
		"out vec4 fragmentColor;"
		"void main()"
		"{"
		"fragmentColor = vec4(1.0, 0.0, 0.0, 1.0);//Red color"
		"}";
	//---프래그먼트세이더읽어저장하고컴파일하기 
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
		std::cerr << "ERROR: fragment shader 컴파일실패\n" << errorLog
			<< std::endl;
		return false;
	};
	GLuint ShaderProgramID = glCreateProgram(); //---세이더프로그램만들기
	glAttachShader(ShaderProgramID, vertexShader); // 세이더프로그램에버텍스세이더붙이기 
	glAttachShader (ShaderProgramID, fragmentShader); // 세이더프로그램에프래그먼트세이더붙이기
	glLinkProgram(ShaderProgramID); // 세이더프로그램링크하기
	glDeleteShader(vertexShader); // 세이더프로그램에링크하여세이더객체자체는삭제가능 
	glDeleteShader (fragmentShader);
	glGetProgramiv(ShaderProgramID, GL_LINK_STATUS, &result); // 세이더가잘연결되었는지체크하기 
	if (!result) { 
		glGetProgramInfoLog (triangleShaderProgramID, 512, NULL, errorLog); 
		std::cerr << "ERROR: shader program 연결실패\n" << errorLog << std::endl;
		return false; 
	}
	glUseProgram(ShaderProgramID); //---만들어진세이더프로그램사용하기 
								   // 여러개의프로그램만들수있고, 특정프로그램을사용하려면 
								   // glUseProgram함수를호출하여사용할특정프로그램을지정한다. 
								   // 사용하기직전에호출할수있다.
	return ShaderProgramID;
}


void Display()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);	
	glUseProgram(complie_shaders());
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glutSwapBuffers();
}

