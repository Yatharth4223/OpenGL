#include "Mesh.h"
#include "Shader.h"
#include <OBJ_Loader.h>
#include "ToolWindow.h"

vector<Mesh> Mesh::Lights;
vector<Mesh> Mesh::m_meshes;


Mesh::Mesh()
{
	//providing default values
	m_shader = nullptr;
	m_texture = { };
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_texture2 = { };
	
	m_position = { 0,0,0 };
	m_rotation = { 0,0,0 };
	m_scale = { 1, 1, 1 };
	m_world = glm::mat4();

}

Mesh::~Mesh()
{

}

void Mesh::Create(Shader* _shader, string _file)
{
	m_shader = _shader;

	objl::Loader Loader;
	M_ASSERT(Loader.LoadFile(_file) == true, "Failed to load mesh.");

	for (unsigned int i = 0; i < Loader.LoadedMeshes.size(); i++)
	{
		objl::Mesh curMesh = Loader.LoadedMeshes[i];
		for (unsigned int j = 0; j < curMesh.Vertices.size(); j++)
		{
			m_vertexData.push_back(curMesh.Vertices[j].Position.X);
			m_vertexData.push_back(curMesh.Vertices[j].Position.Y);
			m_vertexData.push_back(curMesh.Vertices[j].Position.Z);
			m_vertexData.push_back(curMesh.Vertices[j].Normal.X);
			m_vertexData.push_back(curMesh.Vertices[j].Normal.Y);
			m_vertexData.push_back(curMesh.Vertices[j].Normal.Z);
			m_vertexData.push_back(curMesh.Vertices[j].TextureCoordinate.X);
			m_vertexData.push_back(curMesh.Vertices[j].TextureCoordinate.Y);
		}
	}
	string diffuseMap = Loader.LoadedMaterials[0].map_Kd;
	const size_t last_slash_idx = diffuseMap.find_last_of("\\");
	if (std::string::npos != last_slash_idx)
	{
		diffuseMap.erase(0, last_slash_idx + 1);
	}
	if (!diffuseMap.empty())
	{
		m_texture = Texture();
		m_texture.LoadTexture("./Assets/Textures/Exercise2/" + diffuseMap);
		m_texture2 = Texture();
		m_texture2.LoadTexture("./Assets/Textures/Exercise2/TeapotSpecular.jpg");
	}
	else 
	{
		m_texture = Texture();
		m_texture.LoadTexture("./Assets/Textures/Exercise2/Teapot.jpg");
		m_texture2 = Texture();
		m_texture2.LoadTexture("./Assets/Textures/Exercise2/Teapot.jpg");
	}


	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_vertexData.size() * sizeof(float), m_vertexData.data(), GL_STATIC_DRAW);

}

void Mesh::Cleanup()
{
	glDeleteBuffers(1, &m_vertexBuffer);
	glDeleteBuffers(1, &m_indexBuffer);
	m_texture.Cleanup();
	m_texture2.Cleanup();
}

void Mesh::Render(glm::mat4 _pv)
{
	glUseProgram(m_shader->GetProgramID());

	m_rotation.x += 0.001f;
	
	CalculateTransform();
	SetShaderVariables(_pv);
	BindAttributes();

	//Draw the triangle
	glDrawArrays(GL_TRIANGLES, 0, m_vertexData.size());
	glDisableVertexAttribArray(m_shader->GetAttrNormals());
	glDisableVertexAttribArray(m_shader->GetAttrVertices());
	glDisableVertexAttribArray(m_shader->GetAttrTexCoords());

}

void Mesh::BindAttributes()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);

	glEnableVertexAttribArray(m_shader->GetAttrVertices());
	glVertexAttribPointer(m_shader->GetAttrVertices(),
		3,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(float),
		(void*)0);

	glEnableVertexAttribArray(m_shader->GetAttrNormals());
	glVertexAttribPointer(m_shader->GetAttrNormals(),
		3,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(float),
		(void*)(3 * sizeof(float)));

	glEnableVertexAttribArray(m_shader->GetAttrTexCoords());
	glVertexAttribPointer(m_shader->GetAttrTexCoords(),
		2,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(float),
		(void*)(6 * sizeof(float)));
}

void Mesh::CalculateTransform()
{
	m_world = glm::translate(glm::mat4(1.0f), m_position);
	//m_world = glm::rotate(m_world, m_rotation.y, glm::vec3(0, 1, 0));
	m_world = glm::rotate(m_world, m_rotation.x, glm::vec3(1, 0, 0));
	m_world = glm::scale(m_world, m_scale);
}

void Mesh::SetShaderVariables(glm::mat4 _pv)
{
	m_shader->SetMat4("World", m_world);
	m_shader->SetMat4("WVP", _pv * m_world);
	m_shader->SetVec3("CameraPosition", m_cameraPosition);

	if (InitOpenGL::ToolWindow::isMovingLight)
	{
		for (unsigned int i = 0; i < Lights.size(); i++)
		{
			//configure Light
			m_shader->SetFloat(Concat("light[", i, "].constant").c_str(), 1.0f);
			m_shader->SetFloat(Concat("light[", i, "].linear").c_str(), 0.09f);
			m_shader->SetFloat(Concat("light[", i, "].quadratic").c_str(), 0.032f);

			m_shader->SetVec3(Concat("light[", i, "].ambientColor").c_str(), { 0.1f, 0.1f, 0.1f });
			m_shader->SetVec3(Concat("light[", i, "].diffuseColor").c_str(), Lights[i].GetColor());

			glm::vec3 specColor = { InitOpenGL::ToolWindow::specularColorR ,InitOpenGL::ToolWindow::specularColorG ,InitOpenGL::ToolWindow::specularColorB };
			m_shader->SetVec3(Concat("light[", i, "].specularColor").c_str(), specColor);

			m_shader->SetVec3(Concat("light[", i, "].position").c_str(), Lights[i].GetPosition());
			m_shader->SetVec3(Concat("light[", i, "].direction").c_str(), glm::normalize(glm::vec3({ 0.0f + i * 0.1f, 0, 0.0f + i * 0.1f }) - Lights[i].GetPosition()));
			m_shader->SetFloat(Concat("light[", i, "].coneAngle").c_str(), glm::radians(5.0f));
			m_shader->SetFloat(Concat("light[", i, "].falloff").c_str(), 200);
		}
		m_shader->SetFloat("material.specularStrength", InitOpenGL::ToolWindow::specularStrength);
		m_shader->SetTextureSampler("material.diffuseTexture", GL_TEXTURE0, 0, m_texture.GetTexture());
		m_shader->SetTextureSampler("material.specularTexture", GL_TEXTURE1, 1, m_texture2.GetTexture());
	}
	else if (InitOpenGL::ToolWindow::isColoringByPosition)
	{
		m_shader->SetTextureSampler("material.diffuseTexture", GL_TEXTURE0, 0, m_texture.GetTexture());
		m_shader->SetTextureSampler("material.specularTexture", GL_TEXTURE1, 1, m_texture2.GetTexture());
	}

	else
	{
		for (unsigned int i = 0; i < Lights.size(); i++)
		{
			//configure Light
			m_shader->SetFloat(Concat("light[", i, "].constant").c_str(), 1.0f);
			m_shader->SetFloat(Concat("light[", i, "].linear").c_str(), 0.09f);
			m_shader->SetFloat(Concat("light[", i, "].quadratic").c_str(), 0.032f);

			m_shader->SetVec3(Concat("light[", i, "].ambientColor").c_str(), { 0.1f, 0.1f, 0.1f });
			m_shader->SetVec3(Concat("light[", i, "].diffuseColor").c_str(), Lights[i].GetColor());

			glm::vec3 specColor = { InitOpenGL::ToolWindow::specularColorR ,InitOpenGL::ToolWindow::specularColorG ,InitOpenGL::ToolWindow::specularColorB };
			m_shader->SetVec3(Concat("light[", i, "].specularColor").c_str(), specColor);

			m_shader->SetVec3(Concat("light[", i, "].position").c_str(), Lights[i].GetPosition());
			m_shader->SetVec3(Concat("light[", i, "].direction").c_str(), glm::normalize(glm::vec3({ 0.0f + i * 0.1f, 0, 0.0f + i * 0.1f }) - Lights[i].GetPosition()));
			m_shader->SetFloat(Concat("light[", i, "].coneAngle").c_str(), glm::radians(5.0f));
			m_shader->SetFloat(Concat("light[", i, "].falloff").c_str(), 200);
		}
		m_shader->SetFloat("material.specularStrength", InitOpenGL::ToolWindow::specularStrength);
		m_shader->SetTextureSampler("material.diffuseTexture", GL_TEXTURE0, 0, m_texture.GetTexture());
		m_shader->SetTextureSampler("material.specularTexture", GL_TEXTURE1, 1, m_texture2.GetTexture());
	//configure material

}

string Mesh::Concat(string _s1, int _index, string _s2)
{
	string index = to_string(_index);
	return (_s1 + index + _s2);
}