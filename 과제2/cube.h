#pragma once
#include <iostream> 
#include <fstream> 
#include <vector> 
#include <random>
#include <gl/glm/glm/glm.hpp>
#include <gl/glm/glm/ext.hpp>
#include <gl/glm/glm/gtc/matrix_transform.hpp>
#include <gl/glm/glm/gtx/string_cast.hpp>
#include "shaderloader.h"
#include "loadObj.h"
class cube
{
public:
	GLfloat g_vertex_buffer_data[36*3] = {
	-1.0f,-1.0f,-1.0f, // triangle 1 : begin
	-1.0f,-1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f, // triangle 1 : end
	1.0f, 1.0f,-1.0f, // triangle 2 : begin
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f, // triangle 2 : end
	1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	1.0f,-1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f,-1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f,-1.0f, 1.0f
	};
	float R = rand() % 100 * 0.01;
	float G = rand() % 100 * 0.01;
	float B = rand() % 100 * 0.01;
	GLfloat g_color_buffer_data[36 * 3];
	GLuint ibo_cube_elements;
	GLuint colors , el;
	std::vector< glm::vec3 > vertices;
	std::vector< glm::vec2 > uvs;
	std::vector< glm::vec3 > normals; // 지금은 안쓸거에요.
	bool Snow = LoadOBJ("cube.obj", vertices, uvs, normals);
	cube();
	void set_Color();
	void DrawCube(GLuint program);
	glm::mat4 RotateCube(GLuint program, float radian, float X, float Y, float Z);
	glm::mat4 ScaleCube(GLuint program, float scale, float X, float Y, float Z);
	glm::mat4 TransCube(GLuint program, float X, float Y, float Z);
	GLuint vertexbuffer;
	GLuint normalbuffer;

};

