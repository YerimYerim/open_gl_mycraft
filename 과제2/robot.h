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

class robot
{
public:

	cube Leg[2];
	cube arm[2];
	cube body;
	cube head;
	cube nose;

	bool Is_Leg_dir = false;
	float X = 0.0f, Y = 0.1f , Z = 0.0f;
	float Direction_angle = 0.0f;
	float Leg_angle[2] = { 0.0f };
	float right_arm_angle = { 0.0f };
	bool is_click = false;
	GLint modelLoc;
	glm::vec3 camera_model_pos = glm::vec3(X, Y, Z);

	robot();
	int dir = rand() % 4;
//	void set_camera(camera &Camera);
	void draw(GLuint program);		
	void Leg_animation();
	void set_angle();
	void reset_dir();
	void update_move();
	void update();
	void click(int button, int state, int x, int y);
	//void dist_camera();
};

