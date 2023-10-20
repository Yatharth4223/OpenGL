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

	//Methods()
	void Create(Shader* _shader);
	void Cleanup();
	void Render(glm::mat4 _wvp);
	void GetSomething();

private:

	Shader* m_shader;
	Texture m_texture;
	Texture m_texture2;
	//one point in ram and one on OpenGL
	GLuint m_vertexBuffer;
	GLuint m_indexBuffer;
	std::vector<GLfloat> m_vertexData;
	std::vector<GLubyte> m_indexData;
	glm::vec3 m_position;
	glm::vec3 m_rotation;


};

#endif //MESH_H

