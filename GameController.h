#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "StandardIncludes.h"
#include "Mesh.h"
#include "Shader.h"
#include "Skybox.h"
#include "WindowController.h"
#include "Camera.h"

class GameController : public Singleton<GameController>
{
public:
	GameController();
	virtual ~GameController();

	//Methods
	void Initialize();
	void RunGame();

private:
	Shader m_shaderColor;
	Shader m_shaderDiffuse;
	Shader m_shaderFont;
	Shader m_shaderMoveLight;
	Shader m_shaderColorByPosition;
	Shader m_MoveToSphere;
	Camera m_camera;
	Skybox m_skybox;
};

#endif GAME_CONTROLLER_H