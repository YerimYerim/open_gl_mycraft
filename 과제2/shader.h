#include <GL/glew.h> // �ʿ��� ������� 
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
	//---���ؽ����̴��о������ϰ��������ϱ� 
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
		std::cerr << "ERROR: vertex shader �����Ͻ���\n" << errorLog << std::endl;
		return false;
	}

	const GLchar* fragmentShaderSource =
		"#version 330 core\n"
		"out vec4 fragmentColor;"
		"void main()"
		"{"
		"fragmentColor = vec4(1.0, 0.0, 0.0, 1.0);//Red color"
		"}";
	//---�����׸�Ʈ���̴��о������ϰ��������ϱ� 
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
		std::cerr << "ERROR: fragment shader �����Ͻ���\n" << errorLog
			<< std::endl;
		return false;
	};
	GLuint ShaderProgramID = glCreateProgram(); //---���̴����α׷������
	glAttachShader(ShaderProgramID, vertexShader); // ���̴����α׷������ؽ����̴����̱� 
	glAttachShader (ShaderProgramID, fragmentShader); // ���̴����α׷��������׸�Ʈ���̴����̱�
	glLinkProgram(ShaderProgramID); // ���̴����α׷���ũ�ϱ�
	glDeleteShader(vertexShader); // ���̴����α׷�����ũ�Ͽ����̴���ü��ü�»������� 
	glDeleteShader (fragmentShader);
	glGetProgramiv(ShaderProgramID, GL_LINK_STATUS, &result); // ���̴����߿���Ǿ�����üũ�ϱ� 
	if (!result) { 
		glGetProgramInfoLog (triangleShaderProgramID, 512, NULL, errorLog); 
		std::cerr << "ERROR: shader program �������\n" << errorLog << std::endl;
		return false; 
	}
	glUseProgram(ShaderProgramID); //---����������̴����α׷�����ϱ� 
								   // �����������α׷�������ְ�, Ư�����α׷�������Ϸ��� 
								   // glUseProgram�Լ���ȣ���Ͽ������Ư�����α׷��������Ѵ�. 
								   // ����ϱ�������ȣ���Ҽ��ִ�.
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

