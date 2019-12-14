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
#include "cube.h"
#include "robot.h"

struct camera {
	robot me;
	glm::vec3 front;
	//int dist;	
	int dist = 10;
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	float view_angle_x = 0.0f;
	float view_angle_y = 0.0f;
	float view_angle = 0.0f;
	bool Is_Look_around = false;
	glm::vec3  view;
	glm::vec3 cameraDirection;
	bool Is3rdmode = true;
	glm::vec3 camera_model_pos;
	void view_rotate();
	void click(int button, int state, int x, int y); 
	void angle_Keydown(int key, int x, int y);
	void move_key_down(unsigned char key, int x, int y);
	void restruct_view(GLint program);
	void draw(GLuint program);
	void invert_3rd();
	void turn_around();
	void camera_rot(int x, int y);
	
};