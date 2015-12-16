/*
=================
cTreePicker.h
- Header file for class definition - SPECIFICATION
- Header file for the tileMap class which is a child of cSprite class
=================
*/
#ifndef _CTREEPICKER_H
#define _CTREEPICKER_H
#include "cSprite.h"
#include "treeGame.h"

class cTreePicker : public cSprite
{
protected:
	int treePickingList[4];
	int tileMap[8][8];

private:
	vector<cTexture*> treeTextureList;
	glm::vec2 treeListStartXY;
	glm::vec2 tileClickedRC;

	void initialiseTreeList();		// Set the initial values for the map
	void loadTextures();		// Load the texture list with the correct textures

public:
	cTreePicker();
	cTreePicker(vector<cTexture*> tileTextList);
	cTreePicker(vector<cTexture*> tileTextList, int tMap[][8]);

	void render();		// Default render function
	void update();
	void setTreeListStartXY(glm::vec2 startPosXY);
	glm::vec2 getTreeListStartXY();
};
#endif