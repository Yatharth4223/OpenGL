#include "GameController.h"
#include "WindowController.h"
#include "ToolWindow.h"

GameController::GameController()
{
	m_shaderColor = {};
	m_shaderDiffuse = { };
	m_camera = {};
	m_meshBoxes.clear();
	m_meshLight = { };
}

GameController::~GameController()
{

}

void GameController::Initialize()
{
	GLFWwindow* window = WindowController::GetInstance().GetWindow();
	M_ASSERT(glewInit() == GLEW_OK, "Failed to initialise GLEW.");
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //Dark Background
	glEnable(GL_DEPTH_TEST);
	srand(time(0));

	m_camera = Camera(WindowController::GetInstance().GetResolution());
}

void GameController::RunGame()
{
	//Show the C++/CLI tool window
	InitOpenGL::ToolWindow^ window = gcnew InitOpenGL::ToolWindow();
	window->Hide();

	//Create and compile our GLSL program from the shaders
	m_shaderColor = Shader();
	m_shaderColor.LoadShaders("Color.vertexshader", "Color.fragmentshader");
	m_shaderDiffuse = Shader();
	m_shaderDiffuse.LoadShaders("diffuse.vertexshader", "diffuse.fragmentshader");

	m_meshLight = Mesh(); //creating object on stack
	m_meshLight.Create(&m_shaderColor);
	m_meshLight.SetPosition({ 1, -0.5f, 0.0f });
	m_meshLight.SetScale({ 0.1f, 0.1f, 0.1f});

	for (int count = 0; count < 10; count++)
	{
		Mesh box = Mesh();
		box.Create(&m_shaderDiffuse);
		box.SetLightColor({ 0.5f, 0.9f, 0.5f });
		box.SetLightPosition(m_meshLight.GetPosition());
		box.SetCameraPosition(m_camera.GetPosition());
		box.SetScale({ 0.3f,0.3f,0.3f });
		box.SetPosition({ glm::linearRand(-1.0f,1.0f), glm::linearRand(-1.0f,1.0f) , glm::linearRand(-1.0f,1.0f) });
		m_meshBoxes.push_back(box);
	}


	GLFWwindow* win = WindowController::GetInstance().GetWindow();
	do
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clear the screen
		for (unsigned int count = 0; count < m_meshBoxes.size(); count++)
		{
			m_meshBoxes[count].Render(m_camera.GetProjection() * m_camera.GetView());
		}
		m_meshLight.Render(m_camera.GetProjection() * m_camera.GetView());
		glfwSwapBuffers(WindowController::GetInstance().GetWindow()); //Swap the front and back buffers
		glfwPollEvents();

	} 
	while (glfwGetKey(WindowController::GetInstance().GetWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(WindowController::GetInstance().GetWindow()) == 0);
	
	m_meshLight.Cleanup();
	for (unsigned int count = 0; count < m_meshBoxes.size(); count++)
	{
		m_meshBoxes[count].Cleanup();
	}
	m_shaderDiffuse.Cleanup();
	m_shaderColor.Cleanup();
}
