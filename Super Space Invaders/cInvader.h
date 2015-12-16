/*
=================
cInvader.h
- Header file for class definition - SPECIFICATION
- Header file for the Rocket class which is a child of cSprite class
=================
*/
#ifndef _CInvader_H
#define _CInvader_H
#include "cSprite.h"

class cInvader : public cSprite
{
private:
	glm::vec2 InvaderVelocity = glm::vec2(0.0f, 0.0f);

public:
	void render();		// Default render function
	void update(float deltaTime);		// Rocket update method
	void setInvaderVelocity(glm::vec2 InvaderVel);   // Sets the velocity for the rocket
	glm::vec2 getInvaderVelocity();				 // Gets the rocket velocity
	void renderCollisionBox();				// Use this function to show the collision box
	bool atLeftEdge = false;				// Variables to control how the enemies move
	bool atRightEdge = false;
	bool moveDown = false;
	bool gameLost = false;
};
#endif