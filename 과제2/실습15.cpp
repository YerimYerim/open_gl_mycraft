	// main.cpp 

#include "robot.h"
#include "camera.h"
#include"Object.h"
	struct Point
	{
		float x;
		float y;
	};
	float Size = 0.2;
	float angle = 0;
	void Mouse(int button, int state, int x, int y);
	float win_invert_opengl_x(float x);
	float win_invert_opengl_y(float y);
	int select = 0;
	using namespace Core;
	GLuint program;
	bool IsRotate = false;
	bool Isscale = false;
	bool Ismove = false;
	bool Ispoly = false;
	float X = 0.0f;
	float Y = 0.0f;
	float veiw_angle_y = 0.0f;
	float view_angle_x = 0.0f;
	float t = 0.0;
	float dist = 10.0;
	float move_x = 0.0;
	float move_z = 0.0;
	camera Camera;
	Object obj{ "SM_Env_Cloud_01_Internal.OBJ", glm::vec3(0,0,0) };
	//robot R[4];
	void MouseMove(int x, int y);

	void Timerfunction(int value) {
		// 화면재출력 
		//for (int i = 0; i <4; ++i )
		//{
		//	R[i].update();
		//	R[i].Leg_animation();
		//}
	//	std::cout << R.dir<<std::endl;
		//for (int i = 0; i < 4; ++i)
		//{
		//	R[i].set_camera(Camera);
		//}

		Camera.me.update();
		glutPostRedisplay();
		glutTimerFunc(80, Timerfunction, 1); // 타이머함수재설정
	}	

	void Keyboard(unsigned char key, int x, int y)
	{
		Camera.move_key_down(key, x, y);
	}
	void renderScene(void)
	{
		// Enable depth test

		// Accept fragment if it closer to the camera than the former one

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		//--- modelTransform변수에변환값적용하기 		
		glUseProgram(program);
		glEnable(GL_DEPTH_TEST);		
		glDepthFunc(GL_LESS);

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		int lightPosLocation = glGetUniformLocation(program, "lightPos"); //--- lightPos 값 전달
		glUniform3f(lightPosLocation, dist * cos(90.0), 0.0f, dist * sin(90.0));
		int lightColorLocation = glGetUniformLocation(program, "lightColor"); //--- lightColor 값 전달
		glUniform3f(lightColorLocation, 1.0, 1.0, 1.0);
		int objColorLocation = glGetUniformLocation(program, "objectColor"); //--- object Color값 전달
		glUniform3f(objColorLocation, 1.0, 2.0, 5.0);
		//int z = glGetUniformLocation(program, "passColor"); //--- object Color값 전달
		//glUniform3f(z, 0.5, 0.2, 0.2);w

		GLint projLoc = glGetUniformLocation(program, "projection");
		//--- 모델링변환, 뷰잉변환, 투영변환행렬을설정한후, 버텍스세이더에저장한다. 	

		float g_window_w = 800.0;
		float g_window_h = 500.0;

		obj.draw(program);

		glm::mat4 projection = glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(60.0f), (float)g_window_w / (float)g_window_h, 0.1f, 200.0f);
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, &projection[0][0]);
	
		
		GLint modelLoc = glGetUniformLocation(program, "model");

		Camera.restruct_view(program);
		if (Camera.Is3rdmode == true)
			Camera.draw(program);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(0);



		glutSwapBuffers();
	}
	void SpecialKey(int key, int x, int y)
	{
		Camera.angle_Keydown(key, x, y);
//		glutPostRedisplay();
	}
	void Init() {

		glEnable(GL_DEPTH_TEST); //load and compile shaders 
		Core::Shader_Loader shaderLoader;
		program = shaderLoader.CreateProgram((char*)"Vertex_Shader.glsl", (char*)"Fragment_Shader.glsl");
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	}
	void MouseMove(int x, int y) {

		Camera.camera_rot(x, y);

	}
	int main(int argc, char** argv)
	{
		glutInit(&argc, argv);

		glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDisable(GL_DEPTH_TEST);
		glutInitWindowPosition(100, 100);
		glutInitWindowSize(800, 600);
		glutCreateWindow("Drawing my first triangle");
		glewInit();
		Init(); // register callbacks 
		glutDisplayFunc(renderScene);		
		srand(time(NULL));
		glutTimerFunc(100, Timerfunction, 1);
		glutSpecialFunc(SpecialKey);
		glutMotionFunc(MouseMove);
		glutKeyboardFunc(Keyboard);
		glutMouseFunc(Mouse); // 마우스 클릭 입력
		glutMainLoop();

		glDeleteProgram(program);
		return 0;
	}
	void Mouse(int button, int state, int x, int y)
	{

			Camera.click(button, state, x, y);

	}

	float win_invert_opengl_x(float x)
	{
		int w = glutGet(GLUT_WINDOW_WIDTH);
		int h = glutGet(GLUT_WINDOW_HEIGHT);

		return (float)(x - (float)w / 2.0) * (float)(1.0 / (float)(w / 2.0));
	}
	float win_invert_opengl_y(float y)
	{
		int w = glutGet(GLUT_WINDOW_WIDTH);
		int h = glutGet(GLUT_WINDOW_HEIGHT);

		return -(float)(y - (float)h / 2.0) * (float)(1.0 / (float)(h / 2.0));
	}