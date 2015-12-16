/*
=================
- cTreePicker.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cTreePicker.h"

/*
=================================================================
 Defualt Constructor
=================================================================
*/
cTreePicker::cTreePicker()
{
	spritePos2D.x = 0.0f;
	spritePos2D.y = 0.0f;
	setSpriteTexCoordData();
	spriteTranslation = glm::vec2(0.0f, 0.0f);
	spriteScaling = glm::vec2(1.0f, 1.0f);
	spriteRotation = 0.0f;
	spriteCentre = glm::vec2(0.0f, 0.0f);
}

/*
=================================================================
Defualt Constructor
=================================================================
*/
cTreePicker::cTreePicker(vector<cTexture*> tileTextList)
{
	spritePos2D.x = 0.0f;
	spritePos2D.y = 0.0f;
	setSpriteTexCoordData();
	spriteTranslation = glm::vec2(0.0f, 0.0f);
	spriteScaling = glm::vec2(1.0f, 1.0f);
	spriteRotation = 0.0f;
	spriteCentre = glm::vec2(0.0f, 0.0f);
	treeTextureList = tileTextList;
}
/*
=================================================================
Defualt Constructor
=================================================================
*/
cTreePicker::cTreePicker(vector<cTexture*> tileTextList, int tMap[][8])
{
	spritePos2D.x = 0.0f;
	spritePos2D.y = 0.0f;
	setSpriteTexCoordData();
	spriteTranslation = glm::vec2(0.0f, 0.0f);
	spriteScaling = glm::vec2(1.0f, 1.0f);
	spriteRotation = 0.0f;
	spriteCentre = glm::vec2(0.0f, 0.0f);
	treeTextureList = tileTextList;
	initialiseTreeList();
}
void cTreePicker::render()
{
	treeListStartXY = spritePos2D;
	glm::vec2 tilePosXY = treeListStartXY;
	for (int row = 0; row < 4; row++)
	{
		switch (treePickingList[row])
			{
			case 1:
				GLTextureID = treeTextureList[4]->getTexture();
				break;
			case 2:
				GLTextureID = treeTextureList[5]->getTexture();
				break;
			case 3:
				GLTextureID = treeTextureList[6]->getTexture();
				break;
			case 4:
				GLTextureID = treeTextureList[7]->getTexture();
				break;
			}
			
			setTextureDimensions(treeTextureList[0]->getTWidth(), treeTextureList[0]->getTHeight());
			setSpriteCentre();

			glPushMatrix();

			glTranslatef(tilePosXY.x, tilePosXY.y, 0.0f);

			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, GLTextureID); // Binding of GLtexture name 

			glBegin(GL_QUADS);
			glColor3f(255.0f, 255.0f, 255.0f);
			glTexCoord2f(spriteTexCoordData[0].x, spriteTexCoordData[0].y);
			glVertex2f(0, 0);
			glTexCoord2f(spriteTexCoordData[1].x, spriteTexCoordData[1].y);
			glVertex2f(textureWidth, 0);
			glTexCoord2f(spriteTexCoordData[2].x, spriteTexCoordData[2].y);
			glVertex2f(textureWidth, textureHeight);
			glTexCoord2f(spriteTexCoordData[3].x, spriteTexCoordData[3].y);
			glVertex2f(0, textureHeight);

			glEnd();
			glDisable(GL_TEXTURE_2D);

			glPopMatrix();

			tilePosXY.y += cSprite::textureHeight;
		}
}
/*
=================================================================
Update the sprite position
=================================================================
*/

void cTreePicker::update()
{
	if (m_InputMgr->getLeftMouseBtn())
	{
		glm::vec2 areaClicked = m_InputMgr->getMouseXY();
		if (areaClicked.x > 740 && areaClicked.x < 804 && areaClicked.y > 100 && areaClicked.y < 356)
		{
			tileClickedRC.x = (int)(areaClicked.x - treeListStartXY.x) / textureWidth;
			tileClickedRC.y = (int)(areaClicked.y - treeListStartXY.y) / textureHeight;
			treeToPlant = tileClickedRC.y + 5;
		}
	}

}

/*
=================================================================
- Set the initial values for the map
=================================================================
*/
void cTreePicker::initialiseTreeList()
{
	for (int row = 0; row < 4; row++)
	{
		treePickingList[row] = row+1;
	}
	 
}
/*
=================================================================
- Load the texture list with the correct textures
=================================================================
*/
void cTreePicker::loadTextures()
{

}
/*
=================================================================
- set start position for tile map
=================================================================
*/
void cTreePicker::setTreeListStartXY(glm::vec2 startPosXY)
{
	treeListStartXY = startPosXY;
}
/*
=================================================================
- get start pposition for tile map
=================================================================
*/
glm::vec2 cTreePicker::getTreeListStartXY()
{
	return treeListStartXY;
}
