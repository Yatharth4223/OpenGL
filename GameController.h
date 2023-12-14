#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "StandardIncludes.h"
#include "Mesh.h"
#include "Shader.h"
#include "Skybox.h"
#include "WindowController.h"
#include "Camera.h"
#include "Postprocessor.h"

class GameController : public Singleton<GameController>
{
public:
	GameController();
	virtual ~GameController();

	static Shader m_MoveToSphere;
	static Camera m_camera;
	static vector<Mesh> boxes;
	static double lastTime;

	//Methods
	void Initialize();
	void RunGame();

private:
	Shader m_shaderColor;
	Shader m_shaderDiffuse;
	Shader m_shaderMoveLight;
	Shader m_shaderColorByPosition;
	//Skybox m_skybox;
	Shader m_shaderSkybox;
	Shader m_shaderFont;
	Shader m_shaderWater;
	Shader m_shaderPost;
	PostProcessor m_postProcessor;
	vector<Mesh> m_meshes;
	Mesh m_meshLight;
	GLuint vao;
};

#endif GAME_CONTROLLER_H