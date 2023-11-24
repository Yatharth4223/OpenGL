#include "Skybox.h"
#include "Shader.h"
#include "OBJ_Loader.h"

Skybox::Skybox()
{
	m_shader = nullptr;
	m_texture = {};
	m_vertexBuffer = 0;
}

Skybox::~Skybox()
{

}

void Skybox::Create(Shader* _shader, string _file, vector<string> _faces)
{
	m_shader = _shader;

	objl::Loader Loader;
	M_ASSERT(Loader.LoadFile(_file) == true, "failed to load mesh.");

	for (unsigned int i = 0; i < Loader.LoadedMeshes.size(); i++)
	{
		objl::Mesh curMesh = Loader.LoadedMeshes[i];
		for (unsigned int j = 0; j < curMesh.Vertices.size(); j++)
		{
			m_vertexData.push_back(curMesh.Vertices[j].Position.X);
			m_vertexData.push_back(curMesh.Vertices[j].Position.Y);
			m_vertexData.push_back(curMesh.Vertices[j].Position.Z);
		}
	}

	m_texture = Texture();
	m_texture.LoadCubeMap(_faces);

	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_vertexData.size() * sizeof(float), m_vertexData.data(), GL_STATIC_DRAW);

}

void Skybox::Cleanup()
{
	glDeleteBuffers(1, &m_vertexBuffer);
	m_texture.Cleanup();
}

void Skybox::Render(glm::mat4 _pv)
{
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);

	glUseProgram(m_shader->GetProgramID());
	SetShaderVariables(_pv);
	BindAttributes();
	glDrawArrays(GL_TRIANGLES, 0, m_vertexData.size());
	glDisableVertexAttribArray(m_shader->GetAttrNormals());

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

}

void Skybox::SetShaderVariables(glm::mat4 _pv)
{
	m_shader->SetMat4("PV", _pv);
	m_shader->SetTextureSampler("skyboxTexture", GL_TEXTURE_CUBE_MAP, 0, m_texture.GetTexture());
}

void Skybox::BindAttributes()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);

	glEnableVertexAttribArray(m_shader->GetAttrVertices());
	glVertexAttribPointer(m_shader->GetAttrVertices(),
		3,
		GL_FLOAT,
		GL_FALSE,
		3 * sizeof(float),
		(void*)0);
}



