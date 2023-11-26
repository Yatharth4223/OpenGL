#include "GameController.h"
#include "WindowController.h"
#include "ToolWindow.h"
#include "Fonts.h"

GameController::GameController()
{
	m_shaderColor = {};
	m_shaderDiffuse = { };
	m_shaderFont = {};
	m_camera = {};
	m_meshes.clear();
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
	InitOpenGL::ToolWindow^ Window = gcnew InitOpenGL::ToolWindow();
	Window->Hide();

#pragma region SetupShaders
	//Create and compile our GLSL program from the shaders
	m_shaderColor = Shader();
	m_shaderColor.LoadShaders("Color.vertexshader", "Color.fragmentshader");
	m_shaderDiffuse = Shader();
	m_shaderDiffuse.LoadShaders("diffuse.vertexshader", "diffuse.fragmentshader");
	m_shaderFont = Shader();
	m_shaderFont.LoadShaders("Font.vertexshader","Font.fragmentshader");

#pragma endregion

#pragma region CreateMeshes

	Mesh light = Mesh();
	light.Create(&m_shaderColor, "./Assets/Models/Teapot2.obj");
	light.SetPosition({ 1.0f, 0.0f, 0.0f });
	light.SetColor({ 1.0f, 1.0f, 1.0f });
	light.SetScale({ 0.01f,0.01f,0.01f });
	Mesh::Lights.push_back(light);

	Mesh fighter = Mesh();
	fighter.Create(&m_shaderDiffuse, "./Assets/Models/Fighter.obj");
	fighter.SetCameraPosition(m_camera.GetPosition());
	fighter.SetScale({ 0.002f,0.002f,0.002f });
	fighter.SetPosition({ 0.0f, 0.0f, 0.0f });
	m_meshes.push_back(fighter);

#pragma endregion

	Fonts f = Fonts();
	f.Create(&m_shaderFont, "arial.ttf", 100);

#pragma region Render
	GLFWwindow* win = WindowController::GetInstance().GetWindow();
	do
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clear the screen

		//m_camera.Rotate();
		glm::mat4 view = glm::mat4(glm::mat3(m_camera.GetView()));
		for (unsigned int count = 0; count < m_meshes.size(); count++)
		{
			m_meshes[count].Render(m_camera.GetProjection() * m_camera.GetView());
		}
		for (unsigned int count = 0; count < Mesh::Lights.size(); count++)
		{
			Mesh::Lights[count].Render(m_camera.GetProjection() * m_camera.GetView());
		}
		f.RenderText("Testing text", 10, 500, 0.5f, { 1.0f, 1.0f, 0.0f });
		glfwSwapBuffers(WindowController::GetInstance().GetWindow()); //Swap the front and back buffers
		glfwPollEvents();
	} 
	while (glfwGetKey(WindowController::GetInstance().GetWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS && 
		glfwWindowShouldClose(WindowController::GetInstance().GetWindow()) == 0);
#pragma endregion Region

	for (unsigned int count = 0; count < Mesh::Lights.size(); count++)
	{
		Mesh::Lights[count].Cleanup();
	}
	for (unsigned int count = 0; count < m_meshes.size(); count++)
	{
		m_meshes[count].Cleanup();
	}
	m_shaderDiffuse.Cleanup();
	m_shaderColor.Cleanup();
	//m_shaderSkybox.Cleanup();
}
