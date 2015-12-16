#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

#define GLX_GLXEXT_LEGACY //Must be declared so that our local glxext.h is picked up, rather than the system one


#include <windows.h>
#include "windowOGL.h"
#include "GameConstants.h"
#include "cWNDManager.h"
#include "cInputMgr.h"
#include "cSoundMgr.h"
#include "cFontMgr.h"
#include "cSprite.h"
#include "invadersGame.h"
#include "cButton.h"

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR cmdLine,
                   int cmdShow)
{

    //Set our window settings
    const int windowWidth = 1024;
    const int windowHeight = 768;
    const int windowBPP = 16;



    //This is our window
	static cWNDManager* pgmWNDMgr = cWNDManager::getInstance();

	// This is the input manager
	static cInputMgr* theInputMgr = cInputMgr::getInstance();

	// This is the sound manager
	static cSoundMgr* theSoundMgr = cSoundMgr::getInstance();

	// This is the Font manager
	static cFontMgr* theFontMgr = cFontMgr::getInstance();

	//The example OpenGL code
    windowOGL theOGLWnd;
	
    //Attach our the OpenGL window
	pgmWNDMgr->attachOGLWnd(&theOGLWnd);

	// Attach the keyboard manager
	pgmWNDMgr->attachInputMgr(theInputMgr);

    //Attempt to create the window
	if (!pgmWNDMgr->createWND(windowWidth, windowHeight, windowBPP))
    {
        //If it fails

        MessageBox(NULL, "Unable to create the OpenGL Window", "An error occurred", MB_ICONERROR | MB_OK);
		pgmWNDMgr->destroyWND(); //Reset the display and exit
        return 1;
    }

	if (!theOGLWnd.initOGL(windowWidth, windowHeight)) //Initialize our example
    {
        MessageBox(NULL, "Could not initialize the application", "An error occurred", MB_ICONERROR | MB_OK);
		pgmWNDMgr->destroyWND(); //Reset the display and exit
        return 1;
    }

	//Clear key buffers
	theInputMgr->clearBuffers(theInputMgr->KEYS_DOWN_BUFFER | theInputMgr->KEYS_PRESSED_BUFFER);

	/* initialize random seed: */
	srand((unsigned int)time(NULL));

	// Create vector array of textures
	LPCSTR texturesToUse[] = { "Images\\SpaceInvader1.png", "Images\\SpaceInvader2.png", "Images\\SpaceInvader3.png", "Images\\SpaceBullet.png" };
	for (int tCount = 0; tCount < 4; tCount++)
	{
		theGameTextures.push_back(new cTexture());
		theGameTextures[tCount]->createTexture(texturesToUse[tCount]);
	}

	// Create vector array of textures
	vector<cTexture*> textureBkgList;
	LPCSTR bkgTexturesToUse[] = { "Images/SpaceInvadersBackground.png", "Images/SpaceInvadersIntro.png", "Images/SpaceInvadersOutro.png" };
	for (int tCount = 0; tCount < 3; tCount++)
	{
		textureBkgList.push_back(new cTexture());
		textureBkgList[tCount]->createTexture(bkgTexturesToUse[tCount]);
	}

	// Creates an int variable for the score and a string for score
	int iScore = 0;
	std::string score;
	// Creates a function to produce a message, and an array of the messages to produce
	string outputMsg;
	string strMsg[] = { "Score:", "Welcome to Super Space Invaders", "To play, use the left and right arrow keys to move,", "and the space bar to shoot", 
		"Congratulations! You have won!!", "You have lost.", "Press Enter to play again or Q to quit", "Press Enter to play. Press Q to quit at any time" };
	

	// load game sounds
	// Load Sound
	LPCSTR gameSounds[7] = { "Audio/who10Edit.wav", "Audio/shot007.wav", "Audio/explosion2.wav", "Audio/EisenfunkStart.wav", "Audio/EisenfunkMain.wav", "Audio/EisenfunkEnd.wav", "Audio/Eisenfunk.wav" };

	//theSoundMgr->add("Theme", gameSounds[0]);
	theSoundMgr->add("Shot", gameSounds[1]);
	theSoundMgr->add("Explosion", gameSounds[2]);
	theSoundMgr->add("SongStart", gameSounds[3]);
	theSoundMgr->add("SongMain", gameSounds[4]);
	theSoundMgr->add("SongEnd", gameSounds[5]);
	theSoundMgr->add("Song", gameSounds[6]);
	// Plays the song used in the game
	theSoundMgr->getSnd("Song")->playAudio(AL_TRUE);

	// load game fontss
	// Load Fonts
	LPCSTR gameFonts[2] = { "Fonts/digital-7.ttf", "Fonts/space age.ttf" };
	
	theFontMgr->addFont("SevenSeg", gameFonts[0], 24);
	theFontMgr->addFont("Space", gameFonts[1], 24);

	// Loop creates an enemy for each iteration. x and y variables are provided so that they spawn in the correct place
		float vecX = 200.0f;
		float vecY = 50.0f;
		for (int invado = 0; invado < 10; invado++)
		{
			theInvaders.push_back(new cInvader);
			theInvaders[invado]->setSpritePos(glm::vec2(vecX, vecY));
			vecY = vecY + 30.0f;
			if (vecY == 530.0f)
			{
				vecY = 50.0f;
			}
			/*
			vecX = vecX + 50.0f;
			if (vecX == 850.0f)
			{
				vecX = vecX - 650.0f;
				vecY = vecY + 60.0f;
			}
			*/
			int randInvader = rand() % 3;
			theInvaders[invado]->setTexture(theGameTextures[randInvader]->getTexture());
			theInvaders[invado]->setTextureDimensions(theGameTextures[randInvader]->getTWidth(), theGameTextures[randInvader]->getTHeight());
			theInvaders[invado]->setInvaderVelocity(glm::vec2(glm::vec2(0.0f, 0.0f)));
			theInvaders[invado]->setSpriteCentre();
			theInvaders[invado]->setActive(true);
			theInvaders[invado]->setMdlRadius();
			theInvaders[invado]->getSpritePos();
			if (iScore == 10)
			{
				invado = 0;
			}
		}

	// adds a background
	cBkGround spriteBkgd;
	spriteBkgd.setSpritePos(glm::vec2(0.0f, 0.0f));
	spriteBkgd.setTexture(textureBkgList[0]->getTexture());
	spriteBkgd.setTextureDimensions(textureBkgList[0]->getTWidth(), textureBkgList[0]->getTHeight());

	cBkGround spriteStartBkgd;
	spriteStartBkgd.setSpritePos(glm::vec2(0.0f, 0.0f));
	spriteStartBkgd.setTexture(textureBkgList[1]->getTexture());
	spriteStartBkgd.setTextureDimensions(textureBkgList[1]->getTWidth(), textureBkgList[1]->getTHeight());

	cBkGround spriteEndBkgd;
	spriteEndBkgd.setSpritePos(glm::vec2(0.0f, 0.0f));
	spriteEndBkgd.setTexture(textureBkgList[2]->getTexture());
	spriteEndBkgd.setTextureDimensions(textureBkgList[2]->getTWidth(), textureBkgList[2]->getTHeight());

	//creates the rocket and makes it function
	cTexture rocketTxt;
	rocketTxt.createTexture("Images\\SpaceInvaderShip.png");
	cRocket rocketSprite;
	rocketSprite.attachInputMgr(theInputMgr); // Attach the input manager to the sprite
	rocketSprite.setSpritePos(glm::vec2(525.0f, 675.0f));
	rocketSprite.setTexture(rocketTxt.getTexture());
	rocketSprite.setTextureDimensions(rocketTxt.getTWidth(), rocketTxt.getTHeight());
	rocketSprite.setSpriteCentre();
	rocketSprite.setRocketVelocity(glm::vec2(0.0f, 0.0f));

	// Create vector array of button textures
	vector<cTexture*> btnTextureList;
	LPCSTR btnTexturesToUse[] = { "Images/Buttons/exitBtn.png", "Images/Buttons/playBtn.png" };
	for (int tCount = 0; tCount < 2; tCount++)
	{
		btnTextureList.push_back(new cTexture());
		btnTextureList[tCount]->createTexture(btnTexturesToUse[tCount]);
	}

	// Attach sound manager to rocket sprite
	rocketSprite.attachSoundMgr(theSoundMgr);
	gameState theGameState = MENU;
	//This is the mainloop, we render frames until isRunning returns false
	while (pgmWNDMgr->isWNDRunning())
	{
		pgmWNDMgr->processWNDEvents(); //Process any window events

		//We get the time that passed since the last frame
		float elapsedTime = pgmWNDMgr->getElapsedSeconds();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		// initializes the InvaderIterator outside the switch
		vector<cInvader*>::iterator InvaderIterator = theInvaders.begin();
		// creates a switch based on game state
		switch (theGameState)
			
		{
		case MENU:

			//renders background
			spriteStartBkgd.render();
			//prints messages to the screen telling the player how to play and how to start the game
			outputMsg = strMsg[1];
			theFontMgr->getFont("Space")->printText(outputMsg.c_str(), FTPoint(200, 30, 0.0f));
			outputMsg = strMsg[2];
			theFontMgr->getFont("Space")->printText(outputMsg.c_str(), FTPoint(50, 190, 0.0f));
			outputMsg = strMsg[3];
			theFontMgr->getFont("Space")->printText(outputMsg.c_str(), FTPoint(250, 300, 0.0f));
			outputMsg = strMsg[7];
			theFontMgr->getFont("Space")->printText(outputMsg.c_str(), FTPoint(80, 600, 0.0f));
			
			//makes sure the players score is at 0 on the main menu
			iScore = 0;
			//if the player presses space, start the game
			if (theInputMgr->isKeyDown(VK_RETURN))
			{
				theGameState = PLAYING;
			}
			//if the player press Q, quit the game
			if (theInputMgr->isKeyDown('Q'))
			{
				SendMessage(pgmWNDMgr->getWNDHandle(), WM_CLOSE, NULL, NULL);
			}
			break;

		case PLAYING:

			spriteBkgd.render();
			//changes the score string to the int value, allowing use in printing to screen
			score = std::to_string(iScore);
			//prints score to screen
			outputMsg = strMsg[0];
			theFontMgr->getFont("Space")->printText(outputMsg.c_str(), FTPoint(435, 20, 0.0f));
			theFontMgr->getFont("Space")->printText(score.c_str(), FTPoint(565, 20, 0.0f));
			//if there's still enemies in the enemy array
			if (InvaderIterator != theInvaders.end())
			{
				//if an enemy got destroyed
				if ((*InvaderIterator)->isActive() == false)
				{
					//increase score erase enemy
					++iScore;
					InvaderIterator = theInvaders.erase(InvaderIterator);
				}
				else
				{
					(*InvaderIterator)->update(elapsedTime);
					(*InvaderIterator)->render();
					++InvaderIterator;
				}
				//if the players score is 10 (killed 10 enemies)
				if (iScore == 10)
				{
					//present the game over screen
					theGameState = END;
				}
			}

			rocketSprite.update(elapsedTime);
			//quit game onQ press
			if (theInputMgr->isKeyDown('Q'))
			{
				SendMessage(pgmWNDMgr->getWNDHandle(), WM_CLOSE, NULL, NULL);
			}
			//increase players score if A is pressed, used for testing
			if (theInputMgr->isKeyDown('A'))
			{
				iScore++;
			}
			rocketSprite.render();

			break;

		case END:

			spriteEndBkgd.render();
			//if players score is 10, present them with text saying they won
			if (iScore == 10)
			{
				outputMsg = strMsg[4];
				theFontMgr->getFont("Space")->printText(outputMsg.c_str(), FTPoint(250, 200, 0.0f));
			}
			//if players score is less than 10, present them with text saying they lost (can't be achieved currently)
			else
			{
				outputMsg = strMsg[5];
				theFontMgr->getFont("Space")->printText(outputMsg.c_str(), FTPoint(300, 200, 0.0f));
			}
			//prints score and a message asking if palyer wants to play again or quit
			outputMsg = strMsg[0];
			theFontMgr->getFont("Space")->printText(outputMsg.c_str(), FTPoint(435, 70, 0.0f));
			theFontMgr->getFont("Space")->printText(score.c_str(), FTPoint(565, 70, 0.0f));
			outputMsg = strMsg[6];
			theFontMgr->getFont("Space")->printText(outputMsg.c_str(), FTPoint(175, 500, 0.0f));
			//space to go back to menu
			if (theInputMgr->isKeyDown(VK_RETURN))
			{
				theGameState = MENU;
			}
			//q to quit
			if (theInputMgr->isKeyDown('Q'))
			{
				SendMessage(pgmWNDMgr->getWNDHandle(), WM_CLOSE, NULL, NULL);
			}

			break;
		}

		pgmWNDMgr->swapBuffers();
		theInputMgr->clearBuffers(theInputMgr->KEYS_DOWN_BUFFER | theInputMgr->KEYS_PRESSED_BUFFER);
	}

	theOGLWnd.shutdown(); //Free any resources
	pgmWNDMgr->destroyWND(); //Destroy the program window

	return 0; //Return success
}
