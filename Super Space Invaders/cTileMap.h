/*
=================
cTileMap.h
- Header file for class definition - SPECIFICATION
- Header file for the tileMap class which is a child of cSprite class
=================
*/
#ifndef _CTILEMAP_H
#define _CTILEMAP_H
#include "cSprite.h"


class cTileMap: public cSprite
{
protected:
	int tileMap[8][8];

private:
	vector<cTexture*> tileTextureList;
	glm::vec2 mapStartXY;
	glm::ivec2 tileClickedRC;

	void initialiseMap(int map[8][8]);		// Set the initial values for the map
	void loadTextures();		// Load the texture list with the correct textures

public:
	cTileMap();
	cTileMap(vector<cTexture*> tileTextList);
	cTileMap(vector<cTexture*> tileTextList, int tMap[][8]);

	void render();		// Default render function
	void update();
	void setMapStartXY(glm::vec2 startPosXY);
	glm::vec2 getMapStartXY();
};
#endif