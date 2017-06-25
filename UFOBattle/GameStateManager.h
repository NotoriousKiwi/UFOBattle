#include <stack>

enum CurrentState { SPLASH, MAIN_MENU, CREDITS, GAME, };	// <--- Enums we will use to indicate which GameState we are currently in.

#pragma once
class GameStateManager
{
private:
public:

	GameStateManager();										// <--- GameStateManager default constructor.
	~GameStateManager();									// <--- GameStateManager default destructor.

	CurrentState checkCurrentState();						// <--- Checks what state the GameStateManager is currently in.

	virtual void setStateToSplash();						// <--- Sets the GameState to the Splash Screen.
	virtual void setStateToMainMenu();						// <--- Sets the GameState to the Main Menu.
	virtual void setStateToCredits();						// <--- Sets the GameState to the Credits Screen.
	virtual void setStateToGame();							// <--- Sets the GameState to the Main Game.

	std::stack<CurrentState> GameStateStack;				// <--- Stack we will use to contain which level the gamestate is currently in.

protected:
};

