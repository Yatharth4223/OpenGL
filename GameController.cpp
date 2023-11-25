#include "GameController.h"
#include "WindowController.h"
#include "ToolWindow.h"
#include "Fonts.h"
#include <random>

Shader GameController::m_MoveToSphere;
Camera GameController::m_camera;

GameController::GameController()
{
	m_shaderColor = {};
	m_shaderDiffuse = { };
	m_shaderFont = {};
	m_camera = {};
}

GameController::~GameController()
{

}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

void GameController::Initialize()
{
	GLFWwindow* window = WindowController::GetInstance().GetWindow();
	M_ASSERT(glewInit() == GLEW_OK, "Failed to initialise GLEW.");
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glClearColor(0.1f, 0.1f, 0.1f, 0.0f); //Grey Background
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	srand((unsigned int)time(0));

	m_camera = Camera(WindowController::GetInstance().GetResolution());
}

void GameController::RunGame()
{
	//Show the C++/CLI tool window
	InitOpenGL::ToolWindow^ window = gcnew InitOpenGL::ToolWindow();
	window->Show();

#pragma region SetupShaders
	//Create and compile our GLSL program from the shaders
	m_shaderColor = Shader();
	m_shaderColor.LoadShaders("Color.vertexshader", "Color.fragmentshader");
	m_shaderDiffuse = Shader();
	m_shaderDiffuse.LoadShaders("diffuse.vertexshader", "diffuse.fragmentshader");
	//shader for first part
	m_shaderMoveLight = Shader();
	m_shaderMoveLight.LoadShaders("Movelight.vertexshader", "Movelight.fragmentshader");
	
	m_shaderColorByPosition = Shader();
	m_shaderColorByPosition.LoadShaders("ColorByPosition.vertexshader", "ColorByPosition.fragmentshader");

	m_MoveToSphere = Shader();
	m_shaderColorByPosition.LoadShaders("MoveToSphere.vertexshader", "MoveToSphere.fragmentshader");

	//shader for font
	m_shaderFont = Shader();
	m_shaderFont.LoadShaders("Font.vertexshader", "Font.fragmentshader");
#pragma endregion

#pragma region CreateMeshes
	if (InitOpenGL::ToolWindow::isMovingLight)
	{
		Mesh light = Mesh();
		light.Create(&m_shaderColor, "./Assets/Models/Exercise2/Sphere.obj");
		light.SetPosition({ 0.0f, 0.0f, 0.1f });
		light.SetColor({ 1.0f, 1.0f, 1.0f });
		light.SetScale({ 0.1f,0.1f,0.1f });
		light.isVisible = true;
		Mesh::Lights.push_back(light);

		Mesh box = Mesh();
		box.Create(&m_shaderMoveLight, "./Assets/Models/Exercise2/Teapot.obj");
		box.SetCameraPosition(m_camera.GetPosition());
		box.SetScale({ 0.5f,0.5f,0.5f });
		box.SetPosition({ 0.0f, 0.0f, 0.0f });
		box.isVisible = true;
		Mesh::m_meshes.push_back(box);
	}
	else if(InitOpenGL::ToolWindow::isColoringByPosition)
	{
		for (unsigned int count = 0; count < Mesh::m_meshes.size(); count++)
		{
			Mesh::m_meshes[count].Cleanup();
		}
		Mesh box = Mesh();
		box.Create(&m_shaderMoveLight, "./Assets/Models/Exercise2/Teapot.obj");
		box.SetCameraPosition(m_camera.GetPosition());
		box.SetScale({ 0.5f,0.5f,0.5f });
		box.SetPosition({ 0.0f, 0.0f, 0.0f });
		box.isVisible = true;
		Mesh::m_meshes.push_back(box);
	}
	else 
	{
		for (unsigned int count = 0; count < Mesh::m_meshes.size(); count++)
		{
			Mesh::m_meshes[count].Cleanup();
		}

		Mesh box = Mesh();
		box.Create(&m_MoveToSphere, "./Assets/Models/Exercise2/SphereCube.obj");
		box.SetCameraPosition(m_camera.GetPosition());
		box.SetScale({ 0.5f,0.5f,0.5f });
		box.SetPosition({ 0.0f, 0.0f, 0.0f });
		box.isVisible = true;
		Mesh::m_meshes.push_back(box);

		//Mesh box = Mesh();
		//box.Create(&m_MoveToSphere, "./Assets/Models/Exercise2/Cube.obj", "Cube");
		//box.SetCameraPosition(m_camera.GetPosition());
		//box.SetScale({ 0.5f,0.5f,0.5f });
		//box.SetPosition({ 0.0f, 0.0f, 0.0f });
		//box.isVisible = true;
		//Mesh::m_meshes.push_back(box);
	}
	
#pragma endregion CreateMeshes

#pragma region CreateFonts
	Fonts f = Fonts();
	f.Create(&m_shaderFont, "arial.ttf", 100);
#pragma endregion CreateFonts


#pragma region Render
	GLFWwindow* win = WindowController::GetInstance().GetWindow();
	do
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clear the screen

		if (InitOpenGL::ToolWindow::isMovingLight)
		{
			glfwSetMouseButtonCallback(win, mouse_button_callback);
			if (InitOpenGL::ToolWindow::resetLightPosition)
			{
				Mesh::Lights[0].SetPosition({ 0.0f, 0.0f, 0.1f });
				InitOpenGL::ToolWindow::resetLightPosition = false;
			}

			glm::mat4 view = glm::mat4(glm::mat3(m_camera.GetView()));
			for (unsigned int count = 0; count < Mesh::m_meshes.size(); count++)
			{
				Mesh::m_meshes[count].Render(m_camera.GetProjection() * m_camera.GetView());
			}
			for (unsigned int count = 0; count < Mesh::Lights.size(); count++)
			{
				Mesh::Lights[count].Render(m_camera.GetProjection() * m_camera.GetView());
			}

		}
		else if (InitOpenGL::ToolWindow::isColoringByPosition)
		{
			glfwSetMouseButtonCallback(win, mouse_button_callback);

			if (InitOpenGL::ToolWindow::resetTeapotPosition)
			{
				Mesh::m_meshes[0].SetPosition({ 0.0f, 0.0f, 0.0f });
				InitOpenGL::ToolWindow::resetTeapotPosition = false;
			}

			glm::mat4 view = glm::mat4(glm::mat3(m_camera.GetView()));
			for (unsigned int count = 0; count < Mesh::m_meshes.size(); count++)
			{
				Mesh::m_meshes[count].Render(m_camera.GetProjection() * m_camera.GetView());
			}
		}
		else {

			for (unsigned int count = 0; count < Mesh::m_meshes.size(); count++)
			{
				Mesh::m_meshes[count].Cleanup();
			}

			Mesh box = Mesh();
			box.Create(&m_MoveToSphere, "./Assets/Models/Exercise2/SphereCube.obj");
			box.SetCameraPosition(m_camera.GetPosition());
			box.SetScale({ 0.5f,0.5f,0.5f });
			box.SetPosition({ 0.0f, 0.0f, 0.0f });
			box.isVisible = true;
			Mesh::m_meshes.push_back(box);

			glfwSetMouseButtonCallback(win, mouse_button_callback);

			Mesh::Lights[0].SetPosition({ -30,5,0.1 });
			for (unsigned int count = 0; count < Mesh::Lights.size(); count++)
			{
				Mesh::Lights[count].Render(m_camera.GetProjection() * m_camera.GetView());
			}
			glm::mat4 view = glm::mat4(glm::mat3(m_camera.GetView()));
			for (unsigned int count = 0; count < Mesh::m_meshes.size(); count++)
			{
				Mesh::m_meshes[count].Render(m_camera.GetProjection() * m_camera.GetView());
			}

		}

		f.RenderText("Testing text",10, 500, 0.5f, { 1.0f, 1.0f, 0.0f });
		
		glfwSwapBuffers(WindowController::GetInstance().GetWindow()); //Swap the front and back buffers
		glfwPollEvents();
	} 
	while (glfwGetKey(WindowController::GetInstance().GetWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS && 
		glfwWindowShouldClose(WindowController::GetInstance().GetWindow()) == 0);
#pragma endregion Render

	for (unsigned int count = 0; count < Mesh::Lights.size(); count++)
	{
		Mesh::Lights[count].Cleanup();
	}
	for (unsigned int count = 0; count < Mesh::m_meshes.size(); count++)
	{
		Mesh::m_meshes[count].Cleanup();
	}
	m_shaderDiffuse.Cleanup();
	m_shaderColor.Cleanup();
	m_shaderMoveLight.Cleanup();
}

//void mouse_button_callback(GLFWwindow* window, int _button, int _action, int _mods)
//{
//	if (_button == GLFW_MOUSE_BUTTON_LEFT && _action == GLFW_PRESS) {
//		double mouseX, mouseY;
//		glfwGetCursorPos(window, &mouseX, &mouseY); // 10 10
//
//		float lightPosX = Mesh::Lights[0].GetPosition().x; //0
//		float lightPosY = Mesh::Lights[0].GetPosition().y; //0
//		float lightPosZ = Mesh::Lights[0].GetPosition().z; //1
//
//		int screenWidth = WindowController::GetInstance().GetResolution().m_width; //800
//		int screenHeight = WindowController::GetInstance().GetResolution().m_height; //600
//
//		int quadrantX = (mouseX < screenWidth / 2) ? -1 : 1; // firstQuad 1
//		int quadrantY = (mouseY < screenHeight / 2) ? -1 : 1; //1
//
//		mouseY += screenHeight;
//
//		GLfloat centerX = screenWidth / 2.0f; // 400
//		GLfloat centerY = screenHeight/ 2.0f; //400
//		GLfloat dx = mouseX - lightPosX; // 10
//		GLfloat dy = mouseY - lightPosY; // 10
//
//		// Move the light towards the clicked point
//		float speed = 0.1f;  // Adjust the speed as needed
//		lightPosX += speed * quadrantX; // 0.1 * -398 
//		lightPosY += speed * quadrantY; // 0.1 * 398
//
//		Mesh::Lights[0].SetPosition({ lightPosX,lightPosY,lightPosZ });		
//	}
//}


void mouse_button_callback(GLFWwindow* window, int _button, int _action, int _mods)
{
	if (_button == GLFW_MOUSE_BUTTON_LEFT && _action == GLFW_PRESS) {

		if(InitOpenGL::ToolWindow::isMovingCubesToSpheres)
		{
			std::random_device rd;
			std::mt19937 gen(rd()); // Mersenne Twister engine
			std::uniform_real_distribution<float> dis(-20.0f, 20.0f);

			float x = dis(gen);
			float y = dis(gen);
			float z = dis(gen);

	#pragma region Adding A Box
			Mesh box = Mesh();
			box.Create(&GameController::m_MoveToSphere, "./Assets/Models/Exercise2/Cube.obj", "Cube");
			box.SetCameraPosition(GameController::m_camera.GetPosition());
			box.SetScale({ 0.5f,0.5f,0.5f });
			box.SetPosition({ x, y, z });
			box.isVisible = true;
			Mesh::m_meshes.push_back(box);
	#pragma endregion Adding A Box
		}
		else 
		{
			double mouseX, mouseY;
			glfwGetCursorPos(window, &mouseX, &mouseY); // 10 10

			int screenWidth = WindowController::GetInstance().GetResolution().m_width; //800
			int screenHeight = WindowController::GetInstance().GetResolution().m_height; //600

			mouseX = mouseX - screenWidth / 2;
			mouseY = -mouseY + screenHeight / 2;

			float speed = 1.2f;  // Adjust the speed as needed


			if (InitOpenGL::ToolWindow::isMovingLight)
			{
				float lightPosX = Mesh::Lights[0].GetPosition().x; //0
				float lightPosY = Mesh::Lights[0].GetPosition().y; //0
				float lightPosZ = Mesh::Lights[0].GetPosition().z; //1

				GLfloat dx = mouseX - lightPosX; // 10
				GLfloat dy = mouseY - lightPosY; // 10

				if (sqrt(dy * dy + dx * dx) < speed)
				{
					lightPosX = mouseX;
					lightPosY = mouseY;
				}
				else
				{
					double radian = atan2(dx, dy);
					lightPosX += cos(radian) * speed;
					lightPosY += sin(radian) * speed; // 0.1 * 398
				}

				Mesh::Lights[0].SetPosition({ lightPosX,lightPosY,lightPosZ });

			}
			else if (InitOpenGL::ToolWindow::isColoringByPosition)
			{
				float ObjectPosX = Mesh::m_meshes[0].GetPosition().x; //0
				float ObjectPosY = Mesh::m_meshes[0].GetPosition().y; //0
				float ObjectPosZ = Mesh::m_meshes[0].GetPosition().z; //1

				GLfloat dx = mouseX - ObjectPosX; // 10
				GLfloat dy = mouseY - ObjectPosY; // 10

				float speed = 1.2f;  // Adjust the speed as needed
				if (sqrt(dy * dy + dx * dx) < speed)
				{
					ObjectPosX = mouseX;
					ObjectPosY = mouseY;
				}
				else
				{
					float radian = atan2(dx, dy);
					ObjectPosX += cos(radian) * speed;
					ObjectPosY += sin(radian) * speed; // 0.1 * 398
				}

				Mesh::m_meshes[0].SetPosition({ ObjectPosX,ObjectPosY,ObjectPosZ });
			}
		}
		
	}
}


