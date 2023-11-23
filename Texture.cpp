#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture()
{
	m_width = 0;
	m_height = 0;
	m_channels = 0;
	m_texture = 0;
}

void Texture::Cleanup()
{
	glDeleteTextures(1, &m_texture);
}

void Texture::LoadTexture(string _fileName)
{
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_set_flip_vertically_on_load(true);
	GLubyte* data = stbi_load(_fileName.c_str(), &m_width, &m_height, &m_channels, 0);
	M_ASSERT(data != nullptr, "Failed to load texture");
	if (EndsWith(_fileName, ".png"))
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}
	else
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}

	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
}

bool Texture::EndsWith(const std::string& _str, const std::string& _suffix)
{
	// Find the position of the last dot in the fileName
	size_t dotPosition = _str.find_last_of('.');

	// Check if a dot was found and it is not the first character
	if (dotPosition != std::string::npos && dotPosition > 0) {
		// Extract the file extension
		std::string fileExtension = _str.substr(dotPosition + 1);

		// Compare the file extension with the provided suffix in a case-insensitive manner
		return (fileExtension.size() == _suffix.size()) && std::equal(fileExtension.begin(), fileExtension.end(), _suffix.begin(), [](char a, char b) {
			return tolower(a) == tolower(b);
			});
	}

	// If no dot was found or it is the first character, the file has no extension
	return false;
}