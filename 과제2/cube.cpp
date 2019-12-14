#include "cube.h"

cube::cube()
{
	/*
	for (int v = 0; v < 12 * 3; v++) {
		g_color_buffer_data[3 * v + 0] =R;
		g_color_buffer_data[3 * v + 1] =G;
		g_color_buffer_data[3 * v + 2] =B;
	}*/
}


void cube::DrawCube(GLuint program)
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_CULL_FACE);
	glUseProgram(program);

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, (void*)0);
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());


	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);


	//int objColorLocation = glGetUniformLocation(program, "objectColor"); //--- object Color값 전달
	//glUniform3f(objColorLocation, 1.0, 2.0, 5.0);

	int z = glGetUniformLocation(program, "passColor"); //--- object Color값 전달
	glUniform3f(z, R, G, B);

	//GLuint color_buffer;
	//glGenBuffers(1, &color_buffer);
	//glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	//glEnableVertexAttribArray(0);
	//glEnableVertexAttribArray(1);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
	//glDisableVertexAttribArray(0);
	//glDisableVertexAttribArray(1);

	glDeleteBuffers(1, &vertexbuffer);
//	glDeleteBuffers(1, &color_buffer);


	
}

glm::mat4 cube::RotateCube(GLuint program, float radian, float X, float Y, float Z)
{
	glm::mat4 transform = glm::mat4(1.0f);
	transform = glm::rotate(transform, glm::radians(radian), glm::vec3(X, Y, Z));
	return transform;
}

glm::mat4 cube::ScaleCube(GLuint program, float scale, float X, float Y, float Z)
{
	glm::mat4 transform = glm::mat4(1.0f);
	transform = glm::scale(transform, glm::vec3(X, Y, Z));
	return transform;
}

glm::mat4 cube::TransCube(GLuint program, float X, float Y, float Z)
{
	glm::mat4 transform = glm::mat4(1.0f);
	transform = glm::translate(transform, glm::vec3(X, Y, Z));
	return transform;
}




