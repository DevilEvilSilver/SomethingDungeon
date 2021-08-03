#include <stdafx.h>
#include "../Utilities/TGA.h"
#include "Frame.h"

Frame::Frame() {

}

Frame::Frame(unsigned int resourceID, const char* file, GLint tiling, float SPF)
	: m_iResourceID(resourceID), m_fSPF(SPF) {
	glGenTextures(1, &m_RendererID);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);

	// create CPU buffer and load it with the image data
	char *imageData = LoadTGA(file, &m_iWidth, &m_iHeight, &m_iBpp);
	// load the image data into OpenGL ES texture resource
	GLenum format = (m_iBpp == 24) ? GL_RGB : GL_RGBA;
	glTexImage2D(GL_TEXTURE_2D, 0, format, m_iWidth, m_iHeight, 0, format, GL_UNSIGNED_BYTE, imageData);
	delete[]imageData;

	//Texture parameter
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, tiling);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, tiling);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
}

Frame::~Frame() {
	glDeleteTextures(1, &m_RendererID);
}

void Frame::Bind(unsigned int slot) {
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);
}

void Frame::Unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}