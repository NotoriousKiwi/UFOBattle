#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "GameStateManager.h"
#include "DynamicArray.h"

// Colours we use later on when printing coments and players.
enum Colours																									
{
	RED = 0xff0000ff, DK_RED = 0x800000ff, YELLOW = 0xffff00ff, ORANGE = 0xff8000ff,
	GREY = 0xC0C0C0ff, DK_GREY = 0x808080ff, GREEN = 0x00ff00ff, DK_GREEN = 0x008000ff,
	CYAN = 0x00ffffff, DK_CYAN = 0x008080ff, BLUE = 0x0000ffff, WHITE = 0xffffffff, PURPLE = 0x8034f280
};

// Struct for our asteroids (enemy).
struct Comet
{
	Comet() = default;

	bool mAsteroidActive;
	float mX;
	float mY;
	float mRadius;
	float mSpeed;
	Colours mColour;
};																							

// Struct for our player.
struct Player
{
	float mX;		// <--- X coordinate of the Player.
	float mY;		// <--- Y coordinate of the Player.
	float mSpeed;	// <--- Speed of the Player.
	float mRadius;	// <--- Radius of the Player size.
};

class UFOBattleApp : public aie::Application 
{
private:
public:

	UFOBattleApp();													// <--- UFOBattleApp constructor.
	virtual ~UFOBattleApp();										// <--- UFOBattleApp destructor.

	virtual bool startup();											// <--- Bootstrap startup.
	virtual void shutdown();										// <--- Bootstrap shutdown.

	virtual void update(float deltaTime);							// <--- Bootstrap update.
	virtual void draw();											// <--- Bootstrap draw.

	virtual void playerControls(float deltaTime);					// <--- Our main player Controls checker.

	virtual void testCreateAsteroid(float deltaTime);				// <--- Creates our comets.
	virtual void asteroidUpate(Comet *a_ast, float deltaTime);		// <--- Updates the comets.

protected:

	bool	mGameIsOver;											// <--- Checks if the game is over. (Used to exit Bootstrap in essence.)

	float	mTimeInterval;											// <--- Time Interval between comets appearing on screen.
	float	mTimer;													// <--- Timer checking how long it has been since a comet has appeared.

	aie::Renderer2D*	m_2dRenderer;								// <--- Main Renderer pointer.
	aie::Texture*		m_splash;									// <--- Splash Screen pointer texture.
	aie::Texture*		m_credits;									// <--- Credits Screen pointer texture.
	aie::Texture*		m_wallpaper;								// <--- Wallpaper Screen pointer texture.
	aie::Texture*		m_gameBackground;							// <--- Game Background Screen pointer texture.
	aie::Font*			m_font;										// <--- Main Font pointer.

	Player mPlayer;													// <--- Our player object.
	
	DynamicArray<Comet> cometArray;									// <--- Our comet array (container class.)

	GameStateManager *GameStateOperator;							// <--- Our Main Game State Manager object.
};