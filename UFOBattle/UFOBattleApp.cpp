#include "UFOBattleApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <Windows.h>
#include <algorithm>
#include <iostream>

// UFOBattleApp constructor.
UFOBattleApp::UFOBattleApp()
{
	mGameIsOver = false;
	mTimeInterval = 3.0f;
	mPlayer.mX = 640.0f;
	mPlayer.mY = 360.0f;
	mPlayer.mRadius = 25.f;
	mPlayer.mSpeed = 100.f;
}

// UFOBattleApp destructor.
UFOBattleApp::~UFOBattleApp()
{

}

// Bootstrap startup. (Resource allocation and some initial values.)
bool UFOBattleApp::startup()
{
	m_2dRenderer = new aie::Renderer2D();
	m_font		 = new aie::Font("./font/consolas.ttf", 32);
	m_splash	 = new aie::Texture("./textures/SplashScreen.png");
	m_credits	 = new aie::Texture("./textures/CreditsScreen.png");
	m_wallpaper = new aie::Texture("./textures/GameWallpaper4.jpg");
	m_gameBackground = new aie::Texture("./textures/MainGame.jpg");

	GameStateOperator = new GameStateManager();
	GameStateOperator->setStateToSplash();
	return true;
}

// Bootstrap draw function.
void UFOBattleApp::draw()
{
	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!

	// If we're in the splash screen, do as follows.
	if (GameStateOperator->checkCurrentState() == SPLASH)
	{
		m_2dRenderer->drawSprite(m_splash, (float)getWindowWidth() / 2, (float)getWindowHeight() / 2, 1280, 720, 0);
	}

	// If we're in the main menu, do as follows.
	if (GameStateOperator->checkCurrentState() == MAIN_MENU)
	{
		m_2dRenderer->drawSprite(m_wallpaper, (float)getWindowWidth() / 2, (float)getWindowHeight() / 2, 1280, 720, 0);
	}

	// If we're in the credits screen, do as follows.
	if (GameStateOperator->checkCurrentState() == CREDITS)
	{
		m_2dRenderer->drawSprite(m_credits, (float)getWindowWidth() / 2, (float)getWindowHeight() / 2, 1280, 720, 0);
	}

	// If we're in the main game section, do as follows.
	if (GameStateOperator->checkCurrentState() == GAME)
	{
		m_2dRenderer->drawSprite(m_gameBackground, (float)getWindowWidth() / 2, (float)getWindowHeight() / 2, 1280, 720, 0);
		m_2dRenderer->setRenderColour(WHITE);					
		m_2dRenderer->drawCircle(mPlayer.mX, mPlayer.mY, mPlayer.mRadius, 0.0f);

		for (signed int i = 0; i < cometArray.size(); ++i)
		{
			m_2dRenderer->setRenderColour(cometArray.get(i).mColour);			
			m_2dRenderer->drawCircle(cometArray.get(i).mX, cometArray.get(i).mY, cometArray.get(i).mRadius, 0.0f);
		}
	}

	// output some text, uses the last used colour
	//m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}

// Bootstrap update function.
void UFOBattleApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();

	// Change the game to the splash screen.
	if (input->isKeyDown(aie::INPUT_KEY_0))
		GameStateOperator->setStateToSplash();

	// Change the game to the main menu.
	if (input->isKeyDown(aie::INPUT_KEY_1))
		GameStateOperator->setStateToMainMenu();

	// Change the game to the credits screen.
	if (input->isKeyDown(aie::INPUT_KEY_2))
		GameStateOperator->setStateToCredits();

	// Change the game to the main game.
	if (input->isKeyDown(aie::INPUT_KEY_3))
		GameStateOperator->setStateToGame();

	// Call the players controls and check if movement is being made.
	playerControls(deltaTime);

	// Create the asteroids.
	testCreateAsteroid(deltaTime);

	//sortAsteroids();

	//Update comets.
	for (signed int i = 0; i < cometArray.size(); ++i)
	{
		asteroidUpate(&cometArray.get(i), deltaTime);
	}
}

// Bootstrap shutdown function.
void UFOBattleApp::shutdown()
{

	delete m_font;
	delete m_2dRenderer;
	delete m_splash;
	delete m_credits;
	delete m_wallpaper;
	delete GameStateOperator;

}

// Hub for controlling how the players moves and acts.
void UFOBattleApp::playerControls(float deltaTime)
{
	aie::Input* input = aie::Input::getInstance();

	//Player moving left.
	if (input->isKeyDown(aie::INPUT_KEY_A) || input->isKeyDown(aie::INPUT_KEY_LEFT))
		mPlayer.mX -= mPlayer.mSpeed*deltaTime;

	//Player moving right.
	if (input->isKeyDown(aie::INPUT_KEY_D) || input->isKeyDown(aie::INPUT_KEY_RIGHT))
		mPlayer.mX += mPlayer.mSpeed*deltaTime;

	//Player moving up.
	if (input->isKeyDown(aie::INPUT_KEY_W) || input->isKeyDown(aie::INPUT_KEY_UP))
		mPlayer.mY += mPlayer.mSpeed*deltaTime;

	//Player moving down.
	if (input->isKeyDown(aie::INPUT_KEY_S) || input->isKeyDown(aie::INPUT_KEY_DOWN))
		mPlayer.mY -= mPlayer.mSpeed*deltaTime;
}

// Create our asteroids.
void UFOBattleApp::testCreateAsteroid(float a_deltaTime)
{
	static float currentTime, stopCreateTime, addTime;
	const float decreaseInterval = 2.0f;

	currentTime += a_deltaTime;
	addTime		+= a_deltaTime;

	// Checks if it is time to add a new comet.
	if (addTime > decreaseInterval)
	{
		addTime = 0;
		mTimeInterval = max(0.2f, mTimeInterval - 0.2f);
	}

	stopCreateTime = max(0.f, stopCreateTime - a_deltaTime);
	if (stopCreateTime) return;

	// If it is time to create a new comet, do as follows.
	if (currentTime >= mTimeInterval)
	{
		currentTime = 0;
		Comet cmt;
		cmt.mX = (float)(rand() % (getWindowWidth() - 50) + 25);
		cmt.mY = (float)getWindowHeight();

		cmt.mSpeed = (float)(rand() % 400 + 50);
		cmt.mAsteroidActive = true;
		int color = (int)(cmt.mSpeed / 100);

		switch (color)
		{
			case 4:  cmt.mColour =  PURPLE; break;
			case 3:  cmt.mColour =  YELLOW; break;
			case 2:  cmt.mColour =  ORANGE; break;
			case 1:  cmt.mColour =  RED;    break;
			default: cmt.mColour =  DK_RED; break;
		}

		cmt.mRadius = 5.0f;

		cometArray.add(cmt);
		currentTime = 0;
	}
}

// Updates our asteroids and flips a switch if they have gone off screen.
void UFOBattleApp::asteroidUpate(Comet *a_ast, float a_deltaTime)
{
	float oldx = a_ast->mX, oldy = a_ast->mY;

	a_ast->mY -= a_ast->mSpeed*a_deltaTime;

	if (a_ast->mY <= 0)
	{
		a_ast->mAsteroidActive = false;
		return;
	}
}
