#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "StandardIncludes.h"
#include "Mesh.h"
#include "Shader.h"
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
	Camera m_camera;
	vector<Mesh> m_meshBoxes;
	Mesh m_meshLight;
};

#endif GAME_CONTROLLER_H