#include <stdafx.h>
#include "../Utilities/TGA.h"
#include "Frame.h"
#include "define.h"
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
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glGenerateMipmap(GL_TEXTURE_2D);

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
	int iPixelsPerWidthRoom = 100/(MAP_WIDTH-2),//5
		iPixelsPerHeightRoom = 100/(MAP_HEIGHT-2);//5
	int iW = iPixelsPerWidthRoom * (int)size.x,
		iH = iPixelsPerHeightRoom * (int)size.y;
	int iBpp = 32;
	char* imageData = new char[iW*iH*(iBpp/8)];
	
	for (int i = 0; i < iW; i++)
	{
		for (int j = 0; j < iH; j++)
		{
			if (roomType[ (i / iPixelsPerHeightRoom) *(int)size.x  + j / iPixelsPerWidthRoom] == WALL)
			{
				imageData[(j * iW + i) * (iBpp / 8) + 0] = 10;
				imageData[(j * iW + i) * (iBpp / 8) + 1] = 10;
				imageData[(j * iW + i) * (iBpp / 8) + 2] = 10;
				imageData[(j * iW + i) * (iBpp / 8) + 3] = 100;
			}
			/*else if(roomType[(i / iPixelsPerHeightRoom) * (int)size.x + j / iPixelsPerWidthRoom] == END)
			{
				imageData[(j * iW + i) * (iBpp / 8) + 0] = 176;
				imageData[(j * iW + i) * (iBpp / 8) + 1] = 18;
				imageData[(j * iW + i) * (iBpp / 8) + 2] = 10;
				imageData[(j * iW + i) * (iBpp / 8) + 3] = 255;
			}*/
			/*else if (roomType[(i / iPixelsPerHeightRoom) * (int)size.x + j / iPixelsPerWidthRoom] == KEY_ROOM)
			{
				imageData[(j * iW + i) * (iBpp / 8) + 0] = 255;
				imageData[(j * iW + i) * (iBpp / 8) + 1] = 255;
				imageData[(j * iW + i) * (iBpp / 8) + 2] = 59;
				imageData[(j * iW + i) * (iBpp / 8) + 3] = 255;
			}*/
			else 
			{
				imageData[(j * iW + i) * (iBpp / 8) + 0] = 189;
				imageData[(j * iW + i) * (iBpp / 8) + 1] = 189;
				imageData[(j * iW + i) * (iBpp / 8) + 2] = 189;
				imageData[(j * iW + i) * (iBpp / 8) + 3] = 255;
			}
			
		}
	}
	
	glGenTextures(1, &m_RendererID);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, iW, iH, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	delete[]imageData;
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
}
