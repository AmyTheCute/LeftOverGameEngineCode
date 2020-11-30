#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"
#include "GameWindow.h"
#include "ShaderProgram.h"
#define STB_IMAGE_IMPLEMENTATION
#include "Texture.h"
#include "Mesh.h"


#include <iostream>
#include <Windows.h>

const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

// lighting
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

int main()
{
	GameWindow game(SCR_WIDTH, SCR_HEIGHT);
	Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
	game.setCamera(&camera);

	// build and compile our shader zprogram
	// ------------------------------------
	ShaderProgram lightingShader("shaders/main_vertex.glsl", "shaders/main_fragment.glsl");
	ShaderProgram lampShader("shaders/light_vertex.glsl", "shaders/light_fragment.glsl");

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float cube_vertices[] = {
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
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

	glm::vec3 pointLightPositions[] = {
		glm::vec3(0.7f,  0.2f,  2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f,  2.0f, -12.0f),
		glm::vec3(0.0f,  0.0f, -3.0f)
	};

	Mesh cube(cube_vertices, 288);

	// load textures (we now use a utility function to keep the code more organized)
	// -----------------------------------------------------------------------------
	Texture texture("textures/container2.png", 0);
	Texture texture_spec("textures/container2_specular.png", 1);

	// shader configuration
	// --------------------
	lightingShader.use();
	lightingShader.setUniform("material.diffuse", 0);
	lightingShader.setUniform("material.specular", 1);

	float currentFrame;

	// render loop
	// -----------
	while (!game.shouldClose())
	{
		game.update();
		// render
		// ------
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// be sure to activate shader when setting uniforms/drawing objects
		lightingShader.use();
		lightingShader.setUniform("viewPos", camera.Position);
		lightingShader.setUniform("material.shininess", 32.0f);

		/*
		Here we set all the uniforms for the 5/6 types of lights we have. We have to set them manually and index
		the proper PointLight struct in the array to set each uniform variable. This can be done more code-friendly
		by defining light types as classes and set their values in there, or by using a more efficient uniform approach
		by using 'Uniform buffer objects', but that is something we'll discuss in the 'Advanced GLSL' tutorial.
		*/
		// directional light
		lightingShader.setUniform("dirLight.direction", -0.2f, -1.0f, -0.3f);
		lightingShader.setUniform("dirLight.ambient", 0.05f, 0.05f, 0.05f);
		lightingShader.setUniform("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
		lightingShader.setUniform("dirLight.specular", 0.5f, 0.5f, 0.5f);
		// point light 1
		lightingShader.setUniform("pointLights[0].position", pointLightPositions[0]);
		lightingShader.setUniform("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
		lightingShader.setUniform("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
		lightingShader.setUniform("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
		lightingShader.setUniform("pointLights[0].constant", 1.0f);
		lightingShader.setUniform("pointLights[0].linear", 0.09);
		lightingShader.setUniform("pointLights[0].quadratic", 0.032);
		// point light 2
		lightingShader.setUniform("pointLights[1].position", pointLightPositions[1]);
		lightingShader.setUniform("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
		lightingShader.setUniform("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
		lightingShader.setUniform("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
		lightingShader.setUniform("pointLights[1].constant", 1.0f);
		lightingShader.setUniform("pointLights[1].linear", 0.09);
		lightingShader.setUniform("pointLights[1].quadratic", 0.032);
		// point light 3
		lightingShader.setUniform("pointLights[2].position", pointLightPositions[2]);
		lightingShader.setUniform("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
		lightingShader.setUniform("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
		lightingShader.setUniform("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
		lightingShader.setUniform("pointLights[2].constant", 1.0f);
		lightingShader.setUniform("pointLights[2].linear", 0.09);
		lightingShader.setUniform("pointLights[2].quadratic", 0.032);
		// point light 4
		lightingShader.setUniform("pointLights[3].position", pointLightPositions[3]);
		lightingShader.setUniform("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
		lightingShader.setUniform("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
		lightingShader.setUniform("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
		lightingShader.setUniform("pointLights[3].constant", 1.0f);
		lightingShader.setUniform("pointLights[3].linear", 0.09);
		lightingShader.setUniform("pointLights[3].quadratic", 0.032);
		// spotLight
		lightingShader.setUniform("spotLight.position", camera.Position);
		lightingShader.setUniform("spotLight.direction", camera.Front);
		lightingShader.setUniform("spotLight.ambient", 0.0f, 0.0f, 0.0f);
		lightingShader.setUniform("spotLight.diffuse", 0.2f, 0.2f, 0.2f);
		lightingShader.setUniform("spotLight.specular", 0.2f, 0.2f, 0.2f);
		lightingShader.setUniform("spotLight.constant", 1.0f);
		lightingShader.setUniform("spotLight.linear", 0.085);
		lightingShader.setUniform("spotLight.quadratic", 0.028);
		lightingShader.setUniform("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
		lightingShader.setUniform("spotLight.outerCutOff", glm::cos(glm::radians(17.0f)));

		// view/projection transformations
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), static_cast<float>(SCR_WIDTH) / static_cast<float>(SCR_HEIGHT), 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		lightingShader.setUniform("projection", projection);
		lightingShader.setUniform("view", view);

		// world transformation
		glm::mat4 model;
		lightingShader.setUniform("model", model);

		// bind diffuse map
		texture.bind();
		// bind specular map
		texture_spec.bind();

		// render containers
		for (unsigned int i = 0; i < 10; i++)
		{
			// calculate the model matrix for each object and pass it to shader before drawing
			glm::mat4 model;
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			lightingShader.setUniform("model", model);

			cube.Draw();
		}

		// also draw the lamp object(s)
		lampShader.use();
		lampShader.setUniform("projection", projection);
		lampShader.setUniform("view", view);

		// we now draw as many light bulbs as we have point lights.
		for (auto pointLightPosition : pointLightPositions)
		{
			model = glm::mat4();
			model = glm::translate(model, pointLightPosition);
			model = glm::scale(model, glm::vec3(0.2f)); // make it a smaller cube
			lampShader.setUniform("model", model);
			cube.Draw();
		}


		game.pollEvents();
	}

	glfwTerminate();
	return 0;
}
