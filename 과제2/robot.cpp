#include "robot.h"

robot::robot()
{
	dir = rand() % 4;

		//Leg[0].g_color_buffer_data[i] = Leg[1].g_color_buffer_data[i];
		arm[0].R = 0.5;
		arm[0].G = 0.2;
		arm[0].B = 0.2;
					 
		arm[1].R= 0.5;
		arm[1].G = 0.2;
		arm[1].B = 0.2;
					 
		Leg[0].R = 0.5;
		Leg[0].G = 0.5;
		Leg[0].B = 0.5;

		Leg[1].R=	0.5;
		Leg[1].G=	0.2;
		Leg[1].B=	0.2;

		body.R = 0.2;
		body.G = 0.2;
		body.B = 0.2;

		head.R = 1.0; // 머리
		head.G = 0.8;
		head.B = 0.6;

		nose.R = 0.5; //다리
		nose.G = 0.5;
		nose.B = 0.5;
}

//void robot::set_camera(camera &Camera)
//{
//	C = Camera;
//}

void robot::draw(GLuint program)
{	

	modelLoc = glGetUniformLocation(program, "model");
	glm::mat4 transform = glm::mat4(1.0f);
	transform *= body.TransCube(program, camera_model_pos.x , camera_model_pos.y + 1.0, camera_model_pos.z);
	transform *= body.RotateCube(program, 90 -Direction_angle, 0.0, 1.0, 0.0);
	transform *= body.ScaleCube(program, 1.0, 1.1, 1.2, 1.1);
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(transform));
	head.DrawCube(program);
	


	transform = glm::mat4(1.0f);
//	transform *= head.RotateCube(program, 40, 0.0, 1.0, 0.0);	
	transform *= head.TransCube(program, camera_model_pos.x, camera_model_pos.y+3.0, camera_model_pos.z);
	transform *= head.RotateCube(program, 90 -Direction_angle, 0.0, 1.0, 0.0);
	transform *= head.ScaleCube(program, 1.0, 0.8, 0.8, 0.8);
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(transform));
	body.DrawCube(program);

	transform = glm::mat4(1.0f);
	transform *= nose.TransCube(program, camera_model_pos.x , camera_model_pos.y + 3.0, camera_model_pos.z);
	transform *= nose.RotateCube(program, 90 -Direction_angle, 0.0, 1.0, 0.0);
	transform *= nose.TransCube(program, 0.0 , 0.0 , 2.0);
	transform *= nose.ScaleCube(program, 1.0, 0.2, 0.2, 1.2);
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(transform));
	nose.DrawCube(program);

	transform = glm::mat4(1.0f);
	for (int i = 0; i < 2; ++i)
	{

		transform = glm::mat4(1.0f);
		transform *= arm[i].TransCube(program, camera_model_pos.x, camera_model_pos.y +  0.0, camera_model_pos.z);
		transform *= arm[i].RotateCube(program,90 -Direction_angle, 0.0, 1.0, 0.0);

		if ( i == 0 )
			transform *= arm[i].TransCube(program, 0.5, 0.0, 0.0);
		if (i == 1)								   			 
			transform *= arm[i].TransCube(program,  -0.5, 0.0,0.0);
		transform *= arm[i].RotateCube(program, -Leg_angle[i], 1.0, 0.0, 0.0);
		transform *= arm[i].TransCube(program, 0.0, -1.5, 0);
		transform *= arm[i].ScaleCube(program, 1.0, 0.4, 1.5, 0.4);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(transform));
		arm[i].DrawCube(program);


		transform = glm::mat4(1.0f);		
		transform *= Leg[i].TransCube(program, camera_model_pos.x , camera_model_pos.y , camera_model_pos.z);
		transform *= Leg[i].RotateCube(program, 90-Direction_angle, 0.0, 1.0, 0.0);


		if (i == 0)
			transform *= Leg[i].TransCube(program,  1.5, 2.0, 0.0f);
		if (i == 1)											  
			transform *= Leg[i].TransCube(program, -1.5, 2.0, 0.0f);


		if (i == 0)
		{
			transform *= Leg[i].RotateCube(program, Leg_angle[i], 1.0, 0.0, 0.0);
			transform *= Leg[i].TransCube(program, 0.0, -1.0, 0);
			transform *= Leg[i].ScaleCube(program, 1.0, 0.3, 1.2, 0.3);
		}				 
		else if (i ==1)	 
		{				 
			transform *= Leg[i].RotateCube(program, right_arm_angle, 1.0, 0.0, 0.0);
			transform *= Leg[i].TransCube(program, 0.0, -1.0, 0);
			transform *= Leg[i].ScaleCube(program, 1.0, 0.3, 1.2, 0.3);
		}
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(transform));
		Leg[i].DrawCube(program);

		
	}

	transform = glm::mat4(1.0f);
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(transform));
	glBegin(GL_QUADS);
	glVertex3f(-15.f, - 3.0, -15.0);
	glVertex3f(-15.f, - 3.0, 15.0);
	glVertex3f(15.f, - 3.0, 15.0);
	glVertex3f(15.f, - 3.0, -15.0);

	glEnd();
}

void robot::Leg_animation()
{
	
	if (Leg_angle[0] > 30)
	{
		Is_Leg_dir = false;
	}
	else if (Leg_angle[0] < -30)
	{
		Is_Leg_dir = true;
	}
	if (Is_Leg_dir)
	{
		Leg_angle[0] += 5;
		Leg_angle[1] -= 5;
		right_arm_angle -= 5;
	}
	else
	{
		Leg_angle[0] -= 5;
		Leg_angle[1] += 5;
		right_arm_angle += 5;
	}

}

void robot::set_angle()
{
	switch (dir)
	{
	case 0:
		Direction_angle = 0.0f;
		break;
	case 1:
		Direction_angle = 90.0f;
		break;
	case 2:
		Direction_angle = 180.0f;
		break;
	case 3:
		Direction_angle = 270.0f;
		break;
	default:
		break;
	}
}

void robot::reset_dir()
{
	dir = rand() % 4;
}
void robot::update_move()
{
	float speed = 0.2;
	switch (dir)
	{
	case 0:
		if (Z < 10)
			Z += speed;
		else
		{
			reset_dir();
			set_angle();
		}
		break;
	case 1:
		if (X >-10)
			X -= speed;
		else
		{
			reset_dir();
			set_angle();
		}
		break;
	case 2:
		if (Z > -10)
			Z -= speed;
		else
		{
			reset_dir();
			set_angle();
		}
		break;
	case 3:
		if (X < 10)
			X += speed;
		else
		{
			reset_dir();
			set_angle();
		}
		break;
	default:
		break;
	}
}

void robot::update()
{	
	//dist_camera();

	if (is_click)
	{
		right_arm_angle += 30;
	}
	if (right_arm_angle > 360)
	{
		right_arm_angle = 0;
		is_click = false;
	}
	//std::cout << " 로봇의 위치 " << X << ", " << Z << std::endl;

}

void robot::click(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		is_click = true;
		//right_arm_angle += 5;
	}

}

//void robot::dist_camera()
//{
//	float dist = (C.cameraPos.x - X) * (C.cameraPos.x - X) + (C.cameraPos.y - Y) * (C.cameraPos.y - Y) + (C.cameraPos.z - Z) * (C.cameraPos.z - Z);
//	if (dist < 2500.0)
//	{
//		std::cout << "crash" << dist << std::endl ;
//		if ((C.cameraPos.x - X) * (C.cameraPos.x - X) > (C.cameraPos.z - Z)* (C.cameraPos.z - Z))
//		{
//			if (C.cameraPos.x - X < 0)
//			{
//				dir = 1;
//			}
//			else if (C.cameraPos.x - X > 0)
//			{
//				dir = 3;
//			}
//		}
//		else
//		{
//			if (C.cameraPos.z - Z < 0)
//			{
//				dir = 2;
//			}
//			else
//			{
//				dir = 0;
//			}
//		}
//	}
//}
