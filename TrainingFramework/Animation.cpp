#include <stdafx.h>
#include "Animation.h"

Animation::Animation() {

}

Animation::Animation(std::string resourceID, const char* file)
	: m_strResourceID(resourceID) {
	FILE* dataFile;
	dataFile = fopen(file, "r");

	int iFrameCount;
	fscanf(dataFile, "#FRAME_COUNT %d\n", &iFrameCount);
	while (iFrameCount--) {
		int id;
		fscanf(dataFile, "ID %d\n", &id);
		float SPF;
		fscanf(dataFile, "SPF %f\n", &SPF);
		char strTGAFile[100];
		fscanf(dataFile, "FILE %s\n", &strTGAFile);
		char strTiling[30];
		GLint iTiling = 0;
		fscanf(dataFile, "TILING %s\n", &strTiling);
		if (!strcmp(strTiling, "GL_REPEAT"))
			iTiling = GL_REPEAT;
		else if (!strcmp(strTiling, "GL_CLAMP_TO_EDGE"))
			iTiling = GL_CLAMP_TO_EDGE;
		else if (!strcmp(strTiling, "GL_MIRRORED_REPEAT"))
			iTiling = GL_MIRRORED_REPEAT;

		Texture *texture = new Texture(id, strTGAFile, iTiling, SPF);
		AddFrame(texture);
	}

	fclose(dataFile);
}

Animation::~Animation() {
	for (auto& object : m_FrameList) {
		delete object;
	}
	m_FrameList.resize(0);
}

void Animation::AddFrame(Texture *texture) {
	m_FrameList.push_back(texture);
}