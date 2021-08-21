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
void Frame::ReInitMiniMapFrame(RoomType* roomType, Vector2 size)
{
	int iPixelsPerWidthRoom = 96/(int)size.x,
		iPixelsPerHeightRoom = 96/(int)size.y;
	int iW = iPixelsPerWidthRoom * (int)size.x,
		iH = iPixelsPerHeightRoom * (int)size.y;
	int iBpp = 24;
	char* imageData = new char[iW*iH*(iBpp/8)];
	for (int i = 0; i < size.x; i++)
	{
		for (int j = 0; j < size.y; j++)
		{
			/*if (roomType[(int)size.x * i + j] == WALL)
			{
				imageData[(i * iW + j) * 3 + 0] = 0;
				imageData[(i * iW + j) * 3 + 1] = 0;
				imageData[(i * iW + j) * 3 + 2] = 0;
			}
			else
			{
				imageData[(i * iW + j) * 3 + 0] = 0;
				imageData[(i * iW + j) * 3 + 1] = 125;
				imageData[(i * iW + j) * 3 + 2] = 0;
			}*/
			if (roomType[(int)size.x*i + j] == WALL)
			{
				for (int m = 0; m < iPixelsPerWidthRoom; m++)
				{
					for (int n = 0; n < iPixelsPerHeightRoom; n++)
					{
						imageData[((i * iPixelsPerWidthRoom + m) * iW + j * iPixelsPerHeightRoom + n) * 3 + 0] = 0;
						imageData[((i * iPixelsPerWidthRoom + m) * iW + j * iPixelsPerHeightRoom + n) * 3 + 1] = 0;
						imageData[((i * iPixelsPerWidthRoom + m) * iW + j * iPixelsPerHeightRoom + n) * 3 + 2] = 0;
					}
				}
			}
			else
			{
				for (int m = 0; m < iPixelsPerWidthRoom; m++)
				{
					for (int n = 0; n < iPixelsPerHeightRoom; n++)
					{
						imageData[((i * iPixelsPerWidthRoom + m) * iW + j * iPixelsPerHeightRoom + n) * 3 + 0] = 0;
						imageData[((i * iPixelsPerWidthRoom + m) * iW + j * iPixelsPerHeightRoom + n) * 3 + 1] = 125;
						imageData[((i * iPixelsPerWidthRoom + m) * iW + j * iPixelsPerHeightRoom + n) * 3 + 2] = 0;
					}
				}
			}
			
		}
	}
	glGenTextures(1, &m_RendererID);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_iWidth, m_iHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
	delete[]imageData;
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
}
