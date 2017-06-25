#include "GameStateManager.h"
#include <Windows.h>

// GameStateManager default constructor.
GameStateManager::GameStateManager()
{
}

// GameState Manager default destructor.
GameStateManager::~GameStateManager()
{
}

// Checks which state we are currently in.
CurrentState GameStateManager::checkCurrentState()
{
	return GameStateStack.top();
}

// Sets the GameState to the Splash Screen.
void GameStateManager::setStateToSplash()
{
	GameStateStack.push(SPLASH);
}

// Sets the GameState to the Main Menu.
void GameStateManager::setStateToMainMenu()
{
	GameStateStack.push(MAIN_MENU);
}

// Sets the GameState to the Credits Screen.
void GameStateManager::setStateToCredits()
{
	GameStateStack.push(CREDITS);
}

// Sets the GameState to the Game itself.
void GameStateManager::setStateToGame()
{
	GameStateStack.push(GAME);
}
