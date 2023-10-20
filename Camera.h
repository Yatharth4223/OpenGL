#ifndef CAMERA_H
#define CAMERA_H

#include "StandardIncludes.h"

class Camera
{
public:
	Camera();
	Camera(Resolution _screenResolution);
	virtual ~Camera();

	glm::mat4 GetProjection() { return m_projection; }
	glm::mat4 GetView() { return m_view; }

private:
	glm::mat4 m_projection;
	glm::mat4 m_view;
};

#endif CAMERA_H

