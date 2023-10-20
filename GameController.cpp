#include "GameController.h"
#include "WindowController.h"
#include "ToolWindow.h"

GameController::GameController()
{
	m_shader = {};
	m_mesh = {};
	m_camera = {};
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
	glEnable(GL_CULL_FACE);

	m_camera = Camera(WindowController::GetInstance().GetResolution());
}

void GameController::RunGame()
{
	//Show the C++/CLI tool window
	InitOpenGL::ToolWindow^ window = gcnew InitOpenGL::ToolWindow();
	window->Hide();

	//Create and compile our GLSL program from the shaders
	m_shader = Shader();
	//m_shader.LoadShaders("C:\SheridanDoc\Semester5\ComputerGraphics\OpenGL\InitOpenGL\SimpleVertexShader.vertexshader", "C:\SheridanDoc\Semester5\ComputerGraphics\OpenGL\InitOpenGL\SimpleFragmentShader.fragmentshader");
	m_shader.LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");

	m_mesh = Mesh(); //creating object on stack
	m_mesh.Create(&m_shader);

	GLFWwindow* win = WindowController::GetInstance().GetWindow();
	do
	{
		System::Windows::Forms::Application::DoEvents(); //Handle C++/CLI form events

		GLint loc = glGetUniformLocation(m_shader.GetProgramID(), "RenderRedChannel");
		glUniform1i(loc, (int)InitOpenGL::ToolWindow::RenderRedChannel);
		loc = glGetUniformLocation(m_shader.GetProgramID(), "RenderGreenChannel");
		glUniform1i(loc, (int)InitOpenGL::ToolWindow::RenderGreenChannel);
		loc = glGetUniformLocation(m_shader.GetProgramID(), "RenderBlueChannel");
		glUniform1i(loc, (int)InitOpenGL::ToolWindow::RenderBlueChannel);

		glClear(GL_COLOR_BUFFER_BIT); //Clear the screen
		m_mesh.Render(m_camera.GetProjection() * m_camera.GetView());
		glfwSwapBuffers(WindowController::GetInstance().GetWindow()); //Swap the front and back buffers
		glfwPollEvents();

	} 
	while (glfwGetKey(WindowController::GetInstance().GetWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(WindowController::GetInstance().GetWindow()) == 0);
	
	m_mesh.Cleanup();
	m_shader.Cleanup();
}
