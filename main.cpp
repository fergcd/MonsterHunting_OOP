#include "GameManager.h"

using namespace monsterhunting;

int main(void)
{	
	system("mode con cols=80 lines=25");	

	GameManager* gameManager = GameManager::GetInstance();

	while (gameManager->IsExitGame() == false)
	{
		gameManager->ShowTitle();

		if (gameManager->IsExitGame() == true)
		{
			break;
		}

		gameManager->InputName();
		
		while (gameManager->IsGameOver() == false)
		{
			gameManager->SelectMonster();
			gameManager->BeginBattle();
		}

		gameManager->ShowEnding();
		gameManager->InitGame();
	}

	GameManager::DeleteInstance();
	return 0;
}