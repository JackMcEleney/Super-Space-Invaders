/*
=================
cAsteroid.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cAsteroid.h"

void cAsteroid::render()
{


	glPushMatrix();

	glTranslatef(spritePos2D.x, spritePos2D.y, 0.0f);
	glRotatef(spriteRotation, 0.0f, 0.0f, 1.0f);
	glScalef(spriteScaling.x, spriteScaling.y, 1.0f);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, GLTextureID); // Binding of GLtexture name 

	glBegin(GL_QUADS);
	glColor3f(255.0f, 255.0f, 255.0f);
	glTexCoord2f(spriteTexCoordData[0].x, spriteTexCoordData[0].y);
	glVertex2f(-(textureWidth / 2), -(textureHeight / 2));
	glTexCoord2f(spriteTexCoordData[1].x, spriteTexCoordData[1].y);
	glVertex2f((textureWidth / 2), -(textureHeight / 2));
	glTexCoord2f(spriteTexCoordData[2].x, spriteTexCoordData[2].y);
	glVertex2f((textureWidth / 2), (textureHeight / 2));
	glTexCoord2f(spriteTexCoordData[3].x, spriteTexCoordData[3].y);
	glVertex2f(-(textureWidth / 2), (textureHeight / 2));

	glEnd();
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}
/*
=================================================================
Update the sprite position
=================================================================
*/

void cAsteroid::update(float deltaTime)
{	
	//sets basic hitbox detection
	setBoundingRect(&boundingRect);
	//if the enemy is under the red line, sets a boolean of losing the game to true. (Currently does not work as intended)
	if (spritePos2D.y > 630.0f)
	{
		gameLost = true;
	}
	//if the enemy is on the left side, sets a boolean true to change movement
	if (spritePos2D.x < 60.0f)
	{
		atLeftEdge = true;
		atRightEdge = false;
		moveDown = true;
	}
	//if the enemy is on the right side, sets a boolean true to change movement
	if (spritePos2D.x > 970.0f)
	{
		atRightEdge = true;
		atLeftEdge = false;
		moveDown = true;
	}
	// if the enemy has just spawned or is on the left side of the screen, move to the right
	if (atLeftEdge == 1 && spritePos2D.y < 630.0f || atLeftEdge == 0 && atRightEdge == 0 && spritePos2D.y < 630.0f)
	{
		spritePos2D.x += 7.5f;
	}
	// if the enemy is on the right side, move left
	if (atRightEdge == 1 && spritePos2D.y < 630.0f)
	{
		spritePos2D.x -= 7.5f;
	}
	// when it reaches either side, move down
	if (moveDown == 1)
	{
		spritePos2D.y += 30.0f;
		moveDown = false;
	}
}
/*
=================================================================
  Sets the velocity for the Asteroid
=================================================================
*/
void cAsteroid::setAsteroidVelocity(glm::vec2 AsteroidVel)
{
	asteroidVelocity = AsteroidVel;
}
/*
=================================================================
  Gets the Asteroid velocity
=================================================================
*/
glm::vec2 cAsteroid::getAsteroidVelocity()
{
	return asteroidVelocity;
}
/*
==========================================================================
Use this method to show the collision box.
==========================================================================
*/
void cAsteroid::renderCollisionBox()
{
	glPushMatrix();

	glTranslatef(boundingRect.left, boundingRect.top, 0.0f);
	//glRotatef(spriteRotation, 0.0f, 0.0f, 1.0f);
	//glScalef(spriteScaling.x, spriteScaling.y, 1.0f);

	glColor3f(255.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	//glVertex2f(-(textureWidth / 2), -(textureHeight / 2));
	//glVertex2f((textureWidth / 2), -(textureHeight / 2));
	//glVertex2f((textureWidth / 2), (textureHeight / 2));
	//glVertex2f(-(textureWidth / 2), (textureHeight / 2));

	glVertex2f(-((boundingRect.right - boundingRect.left) / 2), -((boundingRect.bottom - boundingRect.top)/2));
	glVertex2f(((boundingRect.right - boundingRect.left) / 2), -((boundingRect.bottom - boundingRect.top) / 2));
	glVertex2f(((boundingRect.right - boundingRect.left) / 2), ((boundingRect.bottom - boundingRect.top) / 2));
	glVertex2f(-((boundingRect.right - boundingRect.left) / 2), ((boundingRect.bottom - boundingRect.top) / 2));
	glEnd();

	glPopMatrix();
}