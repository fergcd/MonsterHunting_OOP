#pragma once
#include <vector>
#include <string>
#include "Character.h"

using namespace std;

namespace monsterhunting
{
	enum class eColor;

	class GameManager final
	{
	private:
		enum eCharacterName
		{
			Player,
			Stone,
			Flower,
			Tree,
			Ant,
			GrassHopper,
			InfinitesimalCalculusTextBook,
			Grenade,
			Billy,
			CamelCriket,
			Gandhi,
			Count,
			FlowerEdible = 12,
			Fruit = 13,
			GrenadeEdible = 17
		};
		enum class eCursorType { Visible, Invisible };
		enum eMove { Attack = 10, ThrowStone = 20, EatFlower = 30, UseGrenade = 40, MiddleFinger = 50, FatalAttack = 60, Corn };
	public:
		static GameManager* GetInstance();
		static void DeleteInstance();
		bool IsExitGame() { return mbExitGame; }
		void ShowTitle();
		void InputName();
		void SelectMonster();
		void BeginBattle();	
		bool IsGameOver() { return mKilledMonsterCount == 10 || mCharacters[eCharacterName::Player].IsAlive() == false; }
		void ShowEnding();
		void InitGame();
	private:
		GameManager();
		void SetColor(eColor color);
		void GotoXY(int16_t x, int16_t y);
		void BlinkString(const string& name, const int16_t x, const int16_t y, const eColor color);
		void SetCursorType(eCursorType cursorType);
		void DisplayCharacterImage(const eCharacterName characterName);
		void DisplayCharacterImage(const eCharacterName characterName, const int16_t xOffset);
		void DisplayCharacterState(const eCharacterName characterName);
		void DisplayUpdatedHealthPoint(const eCharacterName characterName, const int16_t previousHp);
		void DisplayUpdatedAttackPoint(const eCharacterName characterName, const int16_t previousAp);
		void InitMessageBox();
		void DisplayMessageAnimation(const string& message);
		void UpdateMoveList();
		void DisplayCharacterAttackAnimation(const eCharacterName characterName);
		void BlinkCharacterImage(const eCharacterName characterName, const eColor color);
		void UseMove(eMove move);
		void DisplayCharacterDownAnimation(const eCharacterName characterName);
		void ShowRewardEvent(const eCharacterName characterName);
		void DisplayItemPickUpAnimation(const eCharacterName characterName);
		void DisplayPlayerArm(int16_t frame, const string& pixel);
		void DisplayPlayerEatingAnimation(const eCharacterName characterName);
		void DisplayPlayerMouthOpenCloseImageFrame(const int16_t frame);
		void DisplayPlayerBodyExplosionAnimation();
	private:
		enum eKey { Up = 72, Down = 80, Left = 75, Right = 77, Enter = 13 };
		enum eMoveFrameCount { ThrowStoneFrame = 16, MiddleFingerFrame = 9};
		enum eImageRowCount { FatalAttackRow = 19, FlowerRow = 5, FruitRow = 4, GrenadeRow = 7, CornShotRow = 4, CornRow = 6, PlayerHeadRow = 7, PlayerHairRow = 2, ItemAreaRow = 7 };
		static GameManager* mGameManager;
		std::vector<Character> mCharacters;
		bool mbExitGame;
		eCharacterName mSelectedMonster;
		int16_t mKilledMonsterCount;
		Image mThrowStoneFrames[16];
		Image mMiddleFingerFrames[9];
		string mFatalAttackImage[19];
		string mCornShotImage[4];
		string mCornImageArea[4];
		string mPlayerHairImage[2];
		string mPlayerHairImageArea[2];
		string mFlowerImage[5];
		string mFruitImage[4];
		string mGrenadeImage[7];
		string mCornImage[6];
		string mPlayerHeadImage[7];
		string mItemArea[7];
		string mPlayerMouthArea[2];
		string mEraser[4];
	};
}