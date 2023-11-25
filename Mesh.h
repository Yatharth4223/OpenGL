#ifndef MESH_H
#define MESH_H

#include "StandardIncludes.h"
#include "Texture.h"

#include "Shader.h"

class Mesh
{
public:
	Mesh();
	virtual ~Mesh();

	//Accessors
	void SetPosition(glm::vec3 _position) { m_position = _position; }
	glm::vec3 GetPosition() { return m_position; }
	void SetScale(glm::vec3 _scale) { m_scale = _scale; }
	void SetColor(glm::vec3 _color) { m_color = _color; }
	glm::vec3 GetColor() { return m_color; }
	void SetLightPosition(glm::vec3 _lightPosition) { m_lightPosition = _lightPosition; }
	void SetLightColor(glm::vec3 _lightColor) { m_lightColor = _lightColor; }
	void SetCameraPosition(glm::vec3 _cameraPosition) { m_cameraPosition = _cameraPosition; }

	//Methods()
	void Create(Shader* _shader, string _file);
	void Create(Shader* _shader, string _file, string _type);
	void Cleanup();
	void CalculateTransform();
	void Render(glm::mat4 _pv);

	//Members
	static vector<Mesh> Lights;
	static vector<Mesh> m_meshes;
	bool isVisible;
	
private:

	//Methods
	void SetShaderVariables(glm::mat4 _pv);
	void BindAttributes();
	string Concat(string _s1, int _index, string _s2);

	Shader* m_shader;
	Texture m_texture;
	Texture m_texture2;
	//one point in ram and one on OpenGL
	GLuint m_vertexBuffer;
	GLuint m_indexBuffer;
	std::vector<GLfloat> m_vertexData;
	std::vector<GLubyte> m_indexData;

	//Transform
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;
	glm::mat4 m_world;
	
	//Light
	glm::vec3 m_lightPosition;
	glm::vec3 m_lightColor;
	glm::vec3 m_cameraPosition;
	glm::vec3 m_color;
};

#endif //MESH_H

