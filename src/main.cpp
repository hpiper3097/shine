//#define GLM_FORCE_MESSAGES
#define GLM_FORCE_SILENT_WARNINGS

#include "../include/header.h"

void processInput(GLFWwindow* window, float &mixVar);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//const values
const unsigned int SCR_WIDTH = 800, SCR_HEIGHT = 600;
float lastX = 400, lastY = 300;
float yaw = -90.f, pitch = 0.f;
bool firstMouse = true;
float fov = 45.0f;
//while vars
float deltaTime = 0.0f, lastFrame = 0.0f;
float mixVar = 0.f;

float verticies[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};

GLuint indices[] =
{
	0, 1, 3,
	1, 2, 3
};

Camera cam(glm::vec3(0.0f, 0.0f, 3.0f));

int main()
{
	Application app(SCR_WIDTH, SCR_HEIGHT);

	glfwSetCursorPosCallback(app.Window(), mouse_callback);
	glfwSetScrollCallback(app.Window(), scroll_callback);

	glEnable(GL_DEPTH_TEST);

	GLuint VBO, VAO, EBO; //vertex array object, vertex buffer object, element buffer object
	glGenVertexArrays(1, &VAO); //gens VAO; VAO's contain multiple VBO's and are for containing data for a complete rendered object
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	//bind vertex array first, then bind buffer, then configure buffer
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glfwSetInputMode(app.Window(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//texture coords attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0); //typically not done; ony unbind when you need to, however this is showing that you can

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); //allowed because all that has been done so far was while VBO was bound

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	Shader shader1("../shaders/basicVertexShader.vs", "../shaders/basicFragmentShader.fs");
	Texture tex1("../textures/container.jpg", GL_RGB, GL_TEXTURE_2D, GL_TEXTURE0);
	stbi_set_flip_vertically_on_load(true);
	Texture tex2("../textures/letroll.png", GL_RGBA, GL_TEXTURE_2D, GL_TEXTURE1);

	shader1.use();
	shader1.setInt("texture1", 0);
	shader1.setInt("texture2", 1);

	while (!glfwWindowShouldClose(app.Window()))//game loop
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(app.Window(), mixVar);

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //set color to clear with... sets state
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clears with color... uses state

		shader1.use();

		glActiveTexture(GL_TEXTURE0);
		tex1.bind();
		glActiveTexture(GL_TEXTURE1);
		tex2.bind();

		glBindVertexArray(VAO);

		shader1.setFloat("mixVar", mixVar);
		//unsigned int modelLoc = glGetUniformLocation(shader1.ID, "model");
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glm::mat4 persProj = glm::perspective(glm::radians(fov), static_cast<float>(SCR_WIDTH) / static_cast<float>(SCR_HEIGHT), 0.1f, 100.0f);
		shader1.setMat4("projection", persProj);

		glm::mat4 view = cam.GetViewMatrix();
		shader1.setMat4("view", view);

		//model = glm::rotate(model, 0.001f, glm::vec3(-0.75f, 1.0f, 0.0f));
		for (unsigned int i = 0; i < 10; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 4 * glfwGetTime() * (i+1);
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			shader1.setMat4("model", model);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		glfwSwapBuffers(app.Window());
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	return 0;
}

void processInput(GLFWwindow* window, float &mixVar)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		mixVar += .5 * deltaTime;
		if (mixVar > 1.0)
			mixVar = 1.0;
	}

	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		mixVar -= .5 * deltaTime;
		if (mixVar < 0)
			mixVar = 0;
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cam.ProcessKeyboard(Camera_Movement::FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cam.ProcessKeyboard(Camera_Movement::BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cam.ProcessKeyboard(Camera_Movement::LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cam.ProcessKeyboard(Camera_Movement::RIGHT, deltaTime);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse) //checks if this is first input from mouse
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
		float xoffset = xpos - lastX;
		float yoffset = ypos - lastY;
		lastX = xpos;
		lastY = ypos;

		cam.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	cam.ProcessMouseScroll(yoffset);
}
