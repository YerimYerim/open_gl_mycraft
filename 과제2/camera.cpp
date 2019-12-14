#include "camera.h"

void camera::view_rotate()
{
	glm::vec3 front;
	//me.Direction_angle = view_angle_y;
	front.x = cos(glm::radians(view_angle_y)) * cos(glm::radians(0.0f));
	front.y = sin(glm::radians(view_angle_x));
	front.z = sin(glm::radians(view_angle_y)) * cos(glm::radians(0.0f));
	cameraFront = glm::normalize(front);
}

void camera::click(int button, int state, int x, int y)
{
	me.click(button, state, x, y);
}

void camera::angle_Keydown(int key, int x, int y)
{
	//Is3rdmode = false;
	float cameraSpeed = 1.0;
	switch (key)
	{
	case GLUT_KEY_UP:
		if (view_angle_x < 90)
			view_angle_x += cameraSpeed;
		break;
	case GLUT_KEY_DOWN:
		if (view_angle_x > -90)
			view_angle_x -= cameraSpeed;
		break;
	case GLUT_KEY_RIGHT:
		view_angle_y += cameraSpeed;
		me.Direction_angle = view_angle_y;
		break;
	case GLUT_KEY_LEFT:
		view_angle_y -= cameraSpeed;
		me.Direction_angle = view_angle_y;
		break;

	}	me.Leg_animation();
//	view_rotate();
//	glutPostRedisplay();

}

void camera::move_key_down(unsigned char key, int x, int y)
{
	
	switch (key)
	{
	case 'w':
		Is_Look_around = false;
		cameraPos += glm::vec3(1.0, 0.0, 1.0) * cameraFront;
		me.camera_model_pos += glm::vec3(1.0, 0.0, 1.0) * cameraFront;

		break;
	case 'a':
		Is_Look_around = false;
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * glm::vec3(1.0, 1.0, 1.0);
		me.camera_model_pos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * glm::vec3(1.0, 0.0, 1.0);

		break;
	case 's':Is_Look_around = false;
		cameraPos -= glm::vec3(1.0, 0.0, 1.0) * cameraFront;
		me.camera_model_pos -= glm::vec3(1.0, 0.0, 1.0) * cameraFront;
		break;
	case'd':Is_Look_around = false;
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * glm::vec3(1.0, 1.0, 1.0);
		me.camera_model_pos += glm::normalize(glm::cross(cameraFront, cameraUp)) * glm::vec3(1.0,0.0, 1.0);
		break;
	case 'v':Is_Look_around = false;
		if(!Is3rdmode)
			invert_3rd();
		else
		{
			Is3rdmode = false;
			for (int i = 0; i < 10; ++i)
				cameraPos += glm::vec3(1.0, 1.0, 1.0) * cameraFront;
		}
		break;
	}	me.Leg_animation();
	//std::cout << "ZK의 위치 " << X << ", " << Y << std::endl;
}
void camera::restruct_view(GLint program)
{
	GLint viewLoc = glGetUniformLocation(program, "view");
		glm::mat4 view = glm::mat4(1.0f);

	if (Is_Look_around)
	{
		view_rotate();
		glm::vec3 camerapos = glm::vec3(dist * cos(view_angle), cameraPos.y, dist * sin(view_angle));
		glm::vec3 temp = glm::vec3(dist * cos(view_angle), cameraPos.y+1.0, dist * sin(view_angle));
		glm::vec3 cameradirection = glm::vec3(camerapos.x + cameraFront.x, camerapos.y + cameraFront.y, camerapos.z + cameraFront.z);
		view = glm::mat4(1.0f);
		view = glm::lookAt(camerapos, cameradirection, cameraUp);
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
		cameraPos = camerapos;
		cameraDirection = cameradirection;
	}
	else
	{

		cameraDirection = glm::vec3(cameraPos.x + cameraFront.x, cameraPos.y + cameraFront.y, cameraPos.z + cameraFront.z);
		view_rotate();
		GLint viewLoc = glGetUniformLocation(program, "view");
		view = glm::mat4(1.0f);
		view = glm::lookAt(cameraPos, cameraDirection, cameraUp);
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
	}
}
void camera::draw(GLuint program)
{

	GLint viewLoc = glGetUniformLocation(program, "model");
	glm::mat4 view = glm::mat4(1.0f);
	camera_model_pos.x = cameraDirection.x;
	camera_model_pos.z = cameraDirection.z;
	camera_model_pos.y = 0.0f;
	for (int i = 0; i < dist; ++i)
		camera_model_pos += glm::vec3(1.0, 0.0, 1.0) * cameraFront;
	view = glm::translate(view, camera_model_pos);
	camera_model_pos.y = 0.0f;
	me.camera_model_pos = camera_model_pos;

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	me.draw(program);

}

void camera::invert_3rd()
{
	for (int i  = 0; i < dist ; ++i)
		cameraPos -= glm::vec3(1.0, 1.0, 1.0) * cameraFront;
	Is3rdmode = true;
}

void camera::turn_around()
{

}

void camera::camera_rot(int x, int y)
{
	int centerX = glutGet(GLUT_WINDOW_WIDTH) / 2;
	int centerY = glutGet(GLUT_WINDOW_HEIGHT) / 2;
	float cameraSpeed = 0.5;
	if (x > centerX)
	{
		view_angle_y += cameraSpeed;
		me.Direction_angle = view_angle_y;
	}
	if (x < centerX)
	{
		view_angle_y -= cameraSpeed;
		me.Direction_angle = view_angle_y;
	}
	if (y > centerY+0.5)
	{
		if (view_angle_x < 90)
			view_angle_x -= cameraSpeed/10;
	}

	if (y < centerY-0.5)
		if (view_angle_x > -90)
			view_angle_x += cameraSpeed/10;
	glutWarpPointer(centerX, centerY);
}




