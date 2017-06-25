#include "UFOBattleApp.h"
#include "DynamicArray.h"
#include "GameStateManager.h"
#include <vector>

#define CATCH_CONFIG_RUNNER

#include "catch.hpp"

using namespace std;

// Factory Main Class
class FactoryHub
{
public:
	// Factory Method
	static FactoryHub *add_child(int choice);
	virtual void Voiceline() = 0;			// Default virtual function that the descendants will have a similar form of.
};

// Factory Child Class A
class Fish : public FactoryHub
{
public:
	void Voiceline()
	{
		cout << "Gloop Gloop\n";
	}
};

// Factory Child Class B
class Monkey : public FactoryHub
{
public:
	void Voiceline()
	{
		cout << "*Monkey Noises*\n";
	}
};

// Factory Child Class C
class Man : public FactoryHub
{
public:
	void Voiceline()
	{
		cout << "I'm important.\n";
	}
};

// Adds a child based on input.
FactoryHub *FactoryHub::add_child(int choice)
{
	/*/////////////////////////////////////////////////////////////////
	
	Returns:

	If #1: Return a new Larry to the Dynamic Array container class.
	If #2: Return a new Moe to the Dynamic Array container class.
	If #3: Return a new Curly to the Dynamic Array container class.

	/////////////////////////////////////////////////////////////////*/

	if (choice == 1)
	{
		return new Fish;
	}
	else if (choice == 2)
	{
		return new Monkey;
	}
	else
	{
		return new Man;
	}
}

// Tests whether or not the Game State operator is correctly changing states or not.
TEST_CASE("Game State Operations Checking")
{
	GameStateManager* GameStateOperator;
	GameStateOperator = new GameStateManager();

	GameStateOperator->setStateToCredits();
	REQUIRE(GameStateOperator->checkCurrentState() == CREDITS);

	GameStateOperator->setStateToGame();
	REQUIRE(GameStateOperator->checkCurrentState() == GAME);

	GameStateOperator->setStateToMainMenu();
	REQUIRE(GameStateOperator->checkCurrentState() == MAIN_MENU);

	GameStateOperator->setStateToSplash();
	REQUIRE(GameStateOperator->checkCurrentState() == SPLASH);

	delete GameStateOperator;
}

// Checks whether or not the size function is correctly returning the size of the array.
TEST_CASE("Dynamic Array Size Checker")
{
	DynamicArray<int> dIntArray;

	REQUIRE(dIntArray.size() == 0);

	for (int i = 0; i < 7; ++i)
	{
		dIntArray.add(i);
	}

	REQUIRE(dIntArray.size() == 7);
}

// Checks whether or not the add function and the get function are returning as desired.
TEST_CASE("Dynamic Array Add / Index Checker")
{
	DynamicArray<int> dIntArray;
	dIntArray.add(5);

	REQUIRE(dIntArray.get(0) == 5);
}

// Checks whether or not the Array is expanding as required.
TEST_CASE("Dynamic Array Expand Checker")
{
	DynamicArray<int> dIntArray;
	
	for (int i = 0; i < 10; ++i)
	{
		dIntArray.add(5);
	}

	REQUIRE(dIntArray.size() == 10);
}

int main() 
{
	auto app = new UFOBattleApp();						// <--- Bootstrap Initialize sequence.
	app->run("AIE", 1280, 720, false);					// <--- Bootstrap definitions: Title, Pixels in width, Pixels in height, fullscreen yes/no.

	DynamicArray<FactoryHub*> Children;					// <--- Dynamic Array class for storing children and their voicelines.
	int choice;											// <--- Int used to choose which child we will use. (Main reason for having a factory method.)
	while (true)										// <--- Keep looping the below until we choose to exit the loop.
	{
		cout << "Fish = (1) Monkey = (2) Man = (3) End and Print = (0): ";
		cin >> choice;
		if (choice == 0)
		{
			break;
		}
		Children.add(FactoryHub::add_child(choice));
	}

	for (int i = 0; i < Children.size(); i++)			// <--- Get the voiceline for every child in the Dynamic Array class.
	{
		Children.get(i)->Voiceline();
	}

	for (int i = 0; i < Children.size(); i++)			// <--- Delete all the children once we are done with them.
	{
		delete Children.get(i);
	}

	cout << endl;

	delete app;											// <--- Delete the application now we are done with it.

	int result = Catch::Session().run();
	system("pause");
	return (result < 0xff ? result : 0xff);
}
