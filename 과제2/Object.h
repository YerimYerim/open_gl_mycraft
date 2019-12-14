#pragma once
#include<vector>
#include<iostream>
#include<gl/glm/glm/glm.hpp>
#include<gl/glm/glm/gtc/matrix_transform.hpp>
#include<gl/glm/glm/ext.hpp>
#include<GL/glew.h>
#include<GL/freeglut.h>
#include<gl/freeglut_ext.h>
#include"Color.h"

class Object {
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	glm::vec3 position;
	Color color;
	void load_obj(const char*,
		std::vector<glm::vec3>&,
		std::vector<glm::vec2>&,
		std::vector<glm::vec3>&);
public:
	Object();
	Object(const char* path, glm::vec3 pos);
	~Object();
	void draw(GLuint program);
};