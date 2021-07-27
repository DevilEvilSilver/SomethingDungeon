#include <stdafx.h>
#include "../Utilities/TGA.h"
#include "Texture2D.h"

Texture2D::Texture2D() {

}

Texture2D::Texture2D(const char* file, GLint tiling) {
	glGenTextures(1, &m_RendererID);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);

	// create CPU buffer and load it with the image data
	char *imageData = LoadTGA(file, &m_iWidth, &m_iHeight, &m_iBpp);
	// load the image data into OpenGL ES texture resource
	GLenum format = (m_iBpp == 24) ? GL_RGB : GL_RGBA;
	glTexImage2D(GL_TEXTURE_2D, 0, format, m_iWidth, m_iHeight, 0, format, GL_UNSIGNED_BYTE, imageData);
	delete[]imageData;

	//Texture2D parameter
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, tiling);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, tiling);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture2D::~Texture2D() {
	glDeleteTextures(1, &m_RendererID);
}

void Texture2D::Bind(unsigned int slot) {
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);
}

void Texture2D::Unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}