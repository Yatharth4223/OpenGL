#include "Mesh.h"
#include "Shader.h"
#include <OBJ_Loader.h>
#include "ToolWindow.h"
#include <msclr/marshal_cppstd.h>
#include "ASEMesh.h"

using namespace ASEMeshes;

vector<Mesh> Mesh::Lights;
vector<Mesh> Mesh::m_meshes;


Mesh::Mesh()
{
	//providing default values
	m_shader = nullptr;
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_textureDiffuse = {};
	m_textureSpecular = {};
	m_textureNormal = {};
	m_position = { 0,0,0 };
	m_rotation = { 0,0,0 };
	m_scale = { 1, 1, 1 };
	m_world = glm::mat4();
	m_instanceCount = 0;
	m_enableInstancing = false;
	m_elementSize = 0;

}

Mesh::~Mesh()
{

}

void Mesh::Create(Shader* _shader, string _file, int _instanceCount)
{
	m_shader = _shader;
	m_instanceCount = _instanceCount;
	if (m_instanceCount > 1)
	{
		m_enableInstancing = true;
	}

	if (EndsWith(_file, ".ase"))
	{
		ASEMesh^ meshData = gcnew ASEMesh(_file.c_str());
		meshData->ParseASEFile();
		MeshInfo^ m = meshData->GeoObjects[0]->MeshI;
		Material^ mat = meshData->Materials[meshData->GeoObjects[0]->MaterialID];

		vector<objl::Vector3> tangents;
		vector<objl::Vector3> bitangents;
		vector<objl::Vertex> traingle;
		objl::Vector3 tangent;
		objl::Vector3 bitangent;
		int vCount = 0;
		for (int count = 0; count < m->NumFaces; count++)
		{
			Vec3^ tF = m->TexFaces[count];
			Vec3^ f = m->Faces[count];
			traingle.clear();

			objl::Vertex vert = objl::Vertex();
			vert.Position = objl::Vector3(m->Vertices[(int)f->X]->X, m->Vertices[(int)f->X]->Y, m->Vertices[(int)f->X]->Z);
			vert.Normal = objl::Vector3(m->VertexNormals[vCount]->X, m->VertexNormals[vCount]->Y, m->VertexNormals[vCount]->Z);
			vert.TextureCoordinate = objl::Vector2(m->TexVertices[(int)tF->X]->X, m->TexVertices[(int)tF->X]->Y);
			traingle.push_back(vert);
			vCount++;

			vert = objl::Vertex();
			vert.Position = objl::Vector3(m->Vertices[(int)f->X]->X, m->Vertices[(int)f->X]->Y, m->Vertices[(int)f->X]->Z);
			vert.Normal = objl::Vector3(m->VertexNormals[vCount]->X, m->VertexNormals[vCount]->Y, m->VertexNormals[vCount]->Z);
			vert.TextureCoordinate = objl::Vector2(m->TexVertices[(int)tF->X]->X, m->TexVertices[(int)tF->X]->Y);
			traingle.push_back(vert);
			vCount++;

			vert = objl::Vertex();
			vert.Position = objl::Vector3(m->Vertices[(int)f->X]->X, m->Vertices[(int)f->X]->Y, m->Vertices[(int)f->X]->Z);
			vert.Normal = objl::Vector3(m->VertexNormals[vCount]->X, m->VertexNormals[vCount]->Y, m->VertexNormals[vCount]->Z);
			vert.TextureCoordinate = objl::Vector2(m->TexVertices[(int)tF->X]->X, m->TexVertices[(int)tF->X]->Y);
			traingle.push_back(vert);
			vCount++;

			CalculateTangents(traingle, tangent, bitangent);
			tangents.push_back(tangent);
			bitangents.push_back(bitangent);

			for (int c = 0; c < 3; c++)
			{
				m_vertexData.push_back(traingle[c].Position.X);
				m_vertexData.push_back(traingle[c].Position.Y);
				m_vertexData.push_back(traingle[c].Position.Z);
				m_vertexData.push_back(traingle[c].Normal.X);
				m_vertexData.push_back(traingle[c].Normal.Y);
				m_vertexData.push_back(traingle[c].Normal.Z);
				m_vertexData.push_back(traingle[c].TextureCoordinate.X);
				m_vertexData.push_back(traingle[c].TextureCoordinate.Y);

				int index = (vCount / 3) - 1;
				m_vertexData.push_back(tangents[index].X);
				m_vertexData.push_back(tangents[index].Y);
				m_vertexData.push_back(tangents[index].Z);
				m_vertexData.push_back(bitangents[index].X);
				m_vertexData.push_back(bitangents[index].Y);
				m_vertexData.push_back(bitangents[index].Z);

			}
		}
		m_textureDiffuse = Texture();
		if (mat->Maps[0]->Name == "DIFFUSE")
		{
			string fn = msclr::interop::marshal_as<std::string>(mat->Maps[0]->TextureFileName);
			m_textureDiffuse.LoadTexture("./Assets/FinalProjectAssets/Textures/" + RemoveFolder(fn));
		}
		m_textureSpecular = Texture();
		if (mat->Maps[1]->Name == "SPECULAR")
		{
			string fn = msclr::interop::marshal_as<std::string>(mat->Maps[1]->TextureFileName);
			m_textureSpecular.LoadTexture("./Assets/FinalProjectAssets/Textures/" + RemoveFolder(fn));
		}
		m_textureNormal = Texture();
		if (mat->Maps[1]->Name == "BUMP")
		{
			string fn = msclr::interop::marshal_as<std::string>(mat->Maps[1]->TextureFileName);
			m_textureNormal.LoadTexture("./Assets/FinalProjectAssets/Textures/" + RemoveFolder(fn));
			m_enableNormalMap = true;
		}
		else if (mat->Maps[2]->Name == "BUMP")
		{
			string fn = msclr::interop::marshal_as<std::string>(mat->Maps[2]->TextureFileName);
			m_textureNormal.LoadTexture("./Assets/FinalProjectAssets/Textures/" + RemoveFolder(fn));
			m_enableNormalMap = true;
		}
	}
	else
	{

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
			m_textureDiffuse = Texture();
			m_textureDiffuse.LoadTexture("./Assets/Textures/FinalProjectAssets/" + diffuseMap);
			m_textureSpecular = Texture();
			m_textureSpecular.LoadTexture("./Assets/Textures/Exercise2/TeapotSpecular.jpg");
		}
		//this one is for lights
		else
		{
			m_textureDiffuse = Texture();
			m_textureDiffuse.LoadTexture("./Assets/Textures/Exercise2/Teapot.jpg");
			m_textureSpecular = Texture();
			m_textureSpecular.LoadTexture("./Assets/Textures/Exercise2/Teapot.jpg");
		}
	}

	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_vertexData.size() * sizeof(float), m_vertexData.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	if (m_enableInstancing)
	{
		glGenBuffers(1, &m_instanceBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_instanceBuffer);

		srand(glfwGetTime());
		for (unsigned int i = 0; i < m_instanceCount; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(-20 + rand() % 40, -10 + rand() % 20, -10 + rand() % 20));

			for (int x = 0; x < 4; x++)
			{
				for (int y = 0; y < 4; y++)
				{
					m_instanceData.push_back(model[x][y]);
				}
			}
		}
		glBufferData(GL_ARRAY_BUFFER, m_instanceCount * sizeof(glm::mat4), m_instanceData.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}

void Mesh::Create(Shader* _shader, string _file, string _type, int _instanceCount)
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
	m_textureDiffuse = Texture();
	m_textureDiffuse.LoadTexture("./Assets/Textures/Exercise2/" + diffuseMap);
	m_textureSpecular = Texture();
	m_textureSpecular.LoadTexture("./Assets/Textures/Exercise2/MetalFrameSpecular.jpg");

	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_vertexData.size() * sizeof(float), m_vertexData.data(), GL_STATIC_DRAW);

}

void Mesh::Cleanup()
{
	glDeleteBuffers(1, &m_vertexBuffer);
	glDeleteBuffers(1, &m_indexBuffer);
	m_textureDiffuse.Cleanup();
	m_textureNormal.Cleanup();
	m_textureSpecular.Cleanup();
}

void Mesh::Render(glm::mat4 _pv)
{
	glUseProgram(m_shader->GetProgramID());

	m_rotation.x += 0.001f;
	
	CalculateTransform();
	SetShaderVariables(_pv);
	BindAttributes();

	if (m_enableInstancing)
	{
		glDrawArraysInstanced(GL_TRIANGLES, 0, m_vertexData.size() / m_elementSize, m_instanceCount);
	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, m_vertexData.size() / m_elementSize);
	}
	glDisableVertexAttribArray(m_shader->GetAttrNormals());
	glDisableVertexAttribArray(m_shader->GetAttrVertices());
	glDisableVertexAttribArray(m_shader->GetAttrTexCoords());
	if (m_enableNormalMap)
	{
		glDisableVertexAttribArray(m_shader->GetAttrTangents());
		glDisableVertexAttribArray(m_shader->GetAttrBitangents());
	}
	if (m_enableInstancing)
	{
		glDisableVertexAttribArray(m_shader->GetAttrInstanceMatrix());
		glDisableVertexAttribArray(m_shader->GetAttrInstanceMatrix() + 1);
		glDisableVertexAttribArray(m_shader->GetAttrInstanceMatrix() + 2);
		glDisableVertexAttribArray(m_shader->GetAttrInstanceMatrix() + 3);
	}

}

void Mesh::BindAttributes()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);

	int stride = 8;

	if (m_enableNormalMap)
	{
		stride += 6;
	}

	glEnableVertexAttribArray(m_shader->GetAttrVertices());
	glVertexAttribPointer(m_shader->GetAttrVertices(),
		3,
		GL_FLOAT,
		GL_FALSE,
		stride * sizeof(float),
		(void*)0);

	glEnableVertexAttribArray(m_shader->GetAttrNormals());
	glVertexAttribPointer(m_shader->GetAttrNormals(),
		3,
		GL_FLOAT,
		GL_FALSE,
		stride * sizeof(float),
		(void*)(3 * sizeof(float)));

	glEnableVertexAttribArray(m_shader->GetAttrTexCoords());
	glVertexAttribPointer(m_shader->GetAttrTexCoords(),
		2,
		GL_FLOAT,
		GL_FALSE,
		stride * sizeof(float),
		(void*)(6 * sizeof(float)));
	m_elementSize = 8;

#pragma region BindInstancingData
	if (m_enableInstancing)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_instanceBuffer);

		glEnableVertexAttribArray(m_shader->GetAttrInstanceMatrix());
		glVertexAttribPointer(m_shader->GetAttrInstanceMatrix(),
			4,
			GL_FLOAT,
			GL_FALSE,
			sizeof(glm::mat4),
			(void*)0);

		glEnableVertexAttribArray(m_shader->GetAttrInstanceMatrix() + 1);
		glVertexAttribPointer(m_shader->GetAttrInstanceMatrix() + 1,
			4,
			GL_FLOAT,
			GL_FALSE,
			sizeof(glm::mat4),
			(void*)(sizeof(glm::vec4)));

		glEnableVertexAttribArray(m_shader->GetAttrInstanceMatrix() + 2);
		glVertexAttribPointer(m_shader->GetAttrInstanceMatrix() + 2,
			4,
			GL_FLOAT,
			GL_FALSE,
			sizeof(glm::mat4),
			(void*)(2 * sizeof(glm::vec4)));

		glEnableVertexAttribArray(m_shader->GetAttrInstanceMatrix() + 3);
		glVertexAttribPointer(m_shader->GetAttrInstanceMatrix() + 3,
			4,
			GL_FLOAT,
			GL_FALSE,
			sizeof(glm::mat4),
			(void*)(3 * sizeof(glm::vec4)));
		glVertexAttribDivisor(m_shader->GetAttrInstanceMatrix(), 1);
		glVertexAttribDivisor(m_shader->GetAttrInstanceMatrix() + 1, 1);
		glVertexAttribDivisor(m_shader->GetAttrInstanceMatrix() + 2, 1);
		glVertexAttribDivisor(m_shader->GetAttrInstanceMatrix() + 3, 1);
	}
#pragma endregion BindInstancingData
}

void Mesh::CalculateTransform()
{
	m_world = glm::translate(glm::mat4(1.0f), m_position);
	//m_world = glm::rotate(m_world, m_rotation.y, glm::vec3(0, 1, 0));
	m_world = glm::rotate(m_world, glm::radians(m_rotation.x), glm::vec3(0, 1, 0));
	m_world = glm::scale(m_world, m_scale);
}

void Mesh::SetShaderVariables(glm::mat4 _pv)
{
	m_shader->SetMat4("World", m_world);
	m_shader->SetMat4("WVP", _pv * m_world);
	m_shader->SetVec3("CameraPosition", m_cameraPosition);
	m_shader->SetInt("EnableNormalMap", m_enableNormalMap);
	m_shader->SetInt("EnableInstancing", m_enableInstancing);

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
	}
	else if (InitOpenGL::ToolWindow::isTransforming)
	{
		m_shader->SetTextureSampler("material.diffuseTexture", GL_TEXTURE0, 0, m_textureDiffuse.GetTexture());
		m_shader->SetTextureSampler("material.specularTexture", GL_TEXTURE1, 1, m_textureSpecular.GetTexture());
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
			m_shader->SetVec3(Concat("light[", i, "].specularColor").c_str(), { 3.0f, 3.0f, 3.0f });

			m_shader->SetVec3(Concat("light[", i, "].position").c_str(), Lights[i].GetPosition());
			m_shader->SetVec3(Concat("light[", i, "].direction").c_str(), glm::normalize(glm::vec3({ 0.0f + i * 0.1f, 0, 0.0f + i * 0.1f }) - Lights[i].GetPosition()));
			m_shader->SetFloat(Concat("light[", i, "].coneAngle").c_str(), glm::radians(5.0f));
			m_shader->SetFloat(Concat("light[", i, "].falloff").c_str(), 200);
		}
		m_shader->SetFloat("material.specularStrength", 8);

	}

	m_shader->SetTextureSampler("material.diffuseTexture", GL_TEXTURE0, 0, m_textureDiffuse.GetTexture());
	m_shader->SetTextureSampler("material.specularTexture", GL_TEXTURE1, 1, m_textureSpecular.GetTexture());
	m_shader->SetTextureSampler("material.normalTexture", GL_TEXTURE2, 2, m_textureNormal.GetTexture());

}

string Mesh::Concat(string _s1, int _index, string _s2)
{
	string index = to_string(_index);
	return (_s1 + index + _s2);
}

string Mesh::RemoveFolder(string _map)
{
	const size_t last_slash_idx = _map.find_last_of("\\/");
	if (std::string::npos != last_slash_idx)
	{
		_map.erase(0, last_slash_idx + 1);
	}
	return _map;
}

void Mesh::CalculateTangents(vector<objl::Vertex> _vertices, objl::Vector3& _tangent, objl::Vector3& _bitangent)
{
	objl::Vector3 edge1 = _vertices[1].Position - _vertices[0].Position;
	objl::Vector3 edge2 = _vertices[2].Position - _vertices[0].Position;
	objl::Vector2 deltaUV1 = _vertices[1].TextureCoordinate - _vertices[0].TextureCoordinate;
	objl::Vector2 deltaUV2 = _vertices[2].TextureCoordinate - _vertices[0].TextureCoordinate;

	float f = 1.0f / (deltaUV1.X * deltaUV2.Y - deltaUV2.X * deltaUV1.Y);

	_tangent.X = f * (deltaUV2.Y * edge1.X - deltaUV1.Y * edge2.X);
	_tangent.Y = f * (deltaUV2.Y * edge1.Y - deltaUV1.Y * edge2.Y);
	_tangent.Z = f * (deltaUV2.Y * edge1.Z - deltaUV1.Y * edge2.Z);

	_bitangent.X = f * (-deltaUV2.X * edge1.X - deltaUV1.X * edge2.X);
	_bitangent.Y = f * (-deltaUV2.X * edge1.Y - deltaUV1.X * edge2.Y);
	_bitangent.Z = f * (-deltaUV2.X * edge1.Z - deltaUV1.X * edge2.Z);
}

bool Mesh::EndsWith(std::string const& _fullstring, std::string const& _ending)
{
	if (_fullstring.length() >= _ending.length())
	{
		return (0 == _fullstring.compare(_fullstring.length() - _ending.length(), _ending.length(), _ending));
	}
	else
	{
		return false;
	}
}