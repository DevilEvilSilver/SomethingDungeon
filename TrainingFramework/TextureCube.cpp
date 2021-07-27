#include <stdafx.h>
#include "../Utilities/TGA.h"
#include "TextureCube.h"

TextureCube::TextureCube() {

}

TextureCube::TextureCube(std::vector<std::string> file, GLint tiling) {
	glGenTextures(1, &m_RendererID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_RendererID);

	// create CPU buffer and load it with the image data
	int width, height, nrChannels;
	for (unsigned int i = 0; i < file.size(); i++) {
		char *imageData = LoadTGA(file[i].c_str(), &width, &height, &nrChannels);
		// load the image data into OpenGL ES texture resource
		GLenum format = (nrChannels == 24) ? GL_RGB : GL_RGBA;
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, imageData);
		delete[]imageData;
	}

	//TextureCube parameter
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, tiling);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, tiling);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

TextureCube::~TextureCube() {
	glDeleteTextures(1, &m_RendererID);
}

void TextureCube::Bind(unsigned int slot) {
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_RendererID);
}

void TextureCube::Unbind() {
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}