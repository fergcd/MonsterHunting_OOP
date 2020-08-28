#include <windows.h>
#include <conio.h>
#include <iostream>
#include <iomanip>
#include "GameManager.h"
#include "Character.h"
#include "EColor.h"

using namespace std;

namespace monsterhunting
{
	GameManager* GameManager::mGameManager = nullptr;

	GameManager* GameManager::GetInstance()
	{
		if (mGameManager == nullptr)
		{
			mGameManager = new GameManager();
		}

		return mGameManager;
	}

	void GameManager::DeleteInstance()
	{
		if (mGameManager != nullptr)
		{
			delete mGameManager;
			mGameManager = nullptr;
		}
	}

	void GameManager::ShowTitle()
	{
		int16_t y = 23;
		char select = 0;

		SetColor(eColor::Green);
		cout << "\n";
		cout << "                  ~<                                           \n";
		cout << "                  zBNNNBs                                      \n";
		cout << "                  B(   +z'    '+BNNND'   sh      +BN(       .D+\n";
		cout << "                  D~   ss           N(   zs       BNDNN+    'B~\n";
		cout << "                  B-   D+          -B-   D+           =N.   -B'\n";
		cout << "                 -NzNNBN~          Ds    D~           (h    (B	\n";
		cout << "                  DNB~'D'         =Bz   =NNNND'       +z    <h	\n";
		cout << "                   'B~           ~N<B(  ~N-           B+    +z	\n";
		cout << "                   -B'          'N< ~B- <z            D(    s=	\n";
		cout << "                   hNNNNBB'    .B=   =z +z           ~B-    z<	\n";
		cout << "                <NNNB(   ~     ~N'      <s           ~B     D(	\n";
		cout << "                                        (-           =s    .D~	\n";
		cout << "                  -D+  s+            ss  -=          D<    'D-	\n";
		cout << "                  -B-  +=           'B~  (h          <     'D-	\n";
		cout << "                  +h  -BD           (N   BB'               'D'	\n";
		cout << "                  +z-BNND<          <z-DBNN~               -N.	\n";
		cout << "                  shB= =z           <DBs +s                'B'	\n";
		cout << "                  zBN  B~           =NB- B<                 <'	\n";
		cout << "                  +=BNNz'           ~+zNNs                     \n";
		SetColor(eColor::LightGray);
		GotoXY(36, 23);
		cout << "���� ����";
		GotoXY(36, 24);
		cout << "���� ����";
		GotoXY(36, 23);

		while (select != eKey::Enter)
		{
			select = _getch();
			switch (select)
			{
			case eKey::Up:
				y = 23;
				break;
			case eKey::Down:
				y = 24;
				break;
			case eKey::Enter:
				if (23 == y)
				{
					BlinkString("���� ����", 36, y, eColor::LightYellow);
					system("cls");
					mbExitGame = false;
					return;
				}
				break;
			default:
				break;
			}
			GotoXY(36, y);
		}

		mbExitGame = true;
	}

	GameManager::GameManager()
	{
		InitGame();
	}

	void GameManager::SetColor(eColor color)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<WORD>(color));
	}

	void GameManager::GotoXY(int16_t x, int16_t y)
	{
		COORD XY = { (SHORT)x - 1, (SHORT)y - 1 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), XY);
	}

	void GameManager::BlinkString(const string& name, const int16_t x, const int16_t y, const eColor color)
	{
		SetCursorType(eCursorType::Invisible);

		int16_t blinkCount = 1;

		GotoXY(x, y);
		while (blinkCount <= 20)
		{
			SetColor(color);
			cout << name;
			Sleep(30);
			GotoXY(x, y);
			SetColor(eColor::LightGray);
			cout << name;			
			Sleep(30);
			GotoXY(x, y);
			blinkCount++;
		}

		SetCursorType(eCursorType::Visible);
	}

	void GameManager::SetCursorType(eCursorType cursorType)
	{
		CONSOLE_CURSOR_INFO cursorInfo;

		switch (cursorType)
		{
		case eCursorType::Invisible:
			cursorInfo.dwSize = 1;
			cursorInfo.bVisible = FALSE;
			break;
		case eCursorType::Visible:
			cursorInfo.dwSize = 100;
			cursorInfo.bVisible = TRUE;
			GotoXY(70, 23);
			break;
		default:
			break;
		}

		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	}

	void GameManager::SelectMonster()
	{
		int16_t x = 1;
		int16_t y = 1;				

		for (int index = eCharacterName::Stone; index < eCharacterName::Count; ++index)
		{
			if (mCharacters[index].IsAlive() == false)
			{
				SetColor(eColor::Black);
				cout << setw(11) << left << mCharacters[index].GetName();				
				SetColor(eColor::LightGray);
			}
			else
			{
				cout << setw(11) << left << mCharacters[index].GetName();				
			}

			if (eCharacterName::GrassHopper == index)
			{
				cout << endl;
			}			
		}
		//������     ��         ����       ����       �޶ѱ�	1,1	12,1	23,1	34,1	45,1
		//��������å ����ź     ����       ������     ����		1,2	12,2	23,2	34,2	45,2

		GotoXY(15, 12);
		cout << "����Ű�� ����Ʈ������� ���� �����ϰ� ���͸� ��������";		

		GotoXY(x, y);

		while (true)
		{
			switch (_getch())
			{
			case eKey::Up:
				if (y == 2)
				{
					y--;
				}
				break;
			case eKey::Down:
				if (y == 1)
				{
					y++;
				}
				break;
			case eKey::Left:
				if (x >= 12 && x <= 45)
				{
					x -= 11;
				}
				break;
			case eKey::Right:
				if (x >= 1 && x <= 34)
				{
					x += 11;
				}
				break;
			case eKey::Enter:
				switch (x + y)
				{
				case 2:
					mSelectedMonster = eCharacterName::Stone;
					break;
				case 13:
					mSelectedMonster = eCharacterName::Flower;
					break;
				case 24:
					mSelectedMonster = eCharacterName::Tree;
					break;
				case 35:
					mSelectedMonster = eCharacterName::Ant;
					break;
				case 46:
					mSelectedMonster = eCharacterName::GrassHopper;
					break;
				case 3:
					mSelectedMonster = eCharacterName::InfinitesimalCalculusTextBook;
					break;
				case 14:
					mSelectedMonster = eCharacterName::Grenade;
					break;
				case 25:
					mSelectedMonster = eCharacterName::Billy;
					break;
				case 36:
					mSelectedMonster = eCharacterName::CamelCriket;
					break;
				case 47:
					mSelectedMonster = eCharacterName::Gandhi;
					break;
				default:
					break;
				}
				if (mCharacters[mSelectedMonster].IsAlive() == true)
				{
					BlinkString(mCharacters[mSelectedMonster].GetName(), x, y, eColor::LightYellow);
					system("cls");
					return;
				}
			default:
				break;
			}
			GotoXY(x, y);
		}				
	}

	void GameManager::BeginBattle()
	{		
		bool bIsPlayerTurn = true;
		bool bIsMoveDecided = false;
		int16_t x = 10;
		int16_t previousPlayerHP;
		int16_t previousMonsterHp;
		int16_t previousMonsterAP;

		mCharacters[eCharacterName::Player].UpdateExpression(Character::eExpression::PlayerNormal);
		DisplayCharacterImage(eCharacterName::Player);
		DisplayCharacterState(eCharacterName::Player);

		DisplayCharacterImage(mSelectedMonster);
		DisplayCharacterState(mSelectedMonster);

		InitMessageBox();
		
		DisplayMessageAnimation(mCharacters[mSelectedMonster].GetName() + "��(��) ��Ÿ����!");

		_getch();
		InitMessageBox();

		while (mCharacters[eCharacterName::Player].IsAlive() == true && mCharacters[mSelectedMonster].IsAlive() == true)
		{
			previousPlayerHP = mCharacters[eCharacterName::Player].GetHealthPoint();
			previousMonsterHp = mCharacters[mSelectedMonster].GetHealthPoint();
			previousMonsterAP = mCharacters[mSelectedMonster].GetAttackPoint();

			if (bIsPlayerTurn == true)
			{
				mCharacters[eCharacterName::Player].UpdateExpression(Character::eExpression::PlayerNormal);
				DisplayCharacterImage(eCharacterName::Player);
				GotoXY(4, 22);
				cout << "���ҷ�?";
				GotoXY(10, 23);
				cout << "����";

				UpdateMoveList();

				/*
				GotoXY(1, 21);
				cout << " ����������������������������������������������������������������������������\n";
				cout << " ��000000111111111122222222223333333333444444444455555555556666666666777777��\n";
				cout << " ��456789����456789¯��456789��23456789����ź6789����456789�ʻ��6789012345��\n";	//3(7, 23), (26, 23), (45, 23), (64, 23){70}3 ����72ĭ ����19
				cout << " ����������������������������������������������������������������������������";
				GotoXY(4, 22);
				*/

				GotoXY(10, 23);

				while (bIsMoveDecided == false)
				{
					switch (_getch())	//3(7, 23), (26, 23), (45, 23), (64, 23){70}3 ����72ĭ ����19
					{
					case eKey::Left:
						if (x >= 20 && x <= 60)
						{
							x -= 10;
						}
						break;
					case eKey::Right:
						if (x >= 10 && x <= 50)
						{
							x += 10;
						}
						break;
					case eKey::Enter:
						switch (x)
						{
						case eMove::Attack:
							bIsMoveDecided = true;
							bIsPlayerTurn = false;
							InitMessageBox();
							if (eCharacterName::Gandhi == mSelectedMonster && mCharacters[mSelectedMonster].GetAttackPoint() == 0)
							{
								break;
							}
							cout << mCharacters[eCharacterName::Player].GetName() << "��(��) " << mCharacters[mSelectedMonster].GetName() << "��(��) ���Ƚ��ϴ�.";
							DisplayCharacterAttackAnimation(eCharacterName::Player);
							BlinkCharacterImage(mSelectedMonster, eColor::Red);
							mCharacters[eCharacterName::Player].Attack(mCharacters[mSelectedMonster]);
							DisplayUpdatedHealthPoint(mSelectedMonster, previousMonsterHp);							
							break;
						case eMove::ThrowStone:
							if (mCharacters[eCharacterName::Stone].IsAlive() == false)
							{
								bIsMoveDecided = true;
								bIsPlayerTurn = false;
								InitMessageBox();
								if (eCharacterName::Gandhi == mSelectedMonster && mCharacters[mSelectedMonster].GetAttackPoint() == 0)
								{
									break;
								}
								cout << mCharacters[eCharacterName::Player].GetName() << "��(��) " << mCharacters[mSelectedMonster].GetName() << "���� ¯���� �������ϴ�.";
								UseMove(eMove::ThrowStone);
								if (eCharacterName::Billy == mSelectedMonster)	//���������� 60, 10	�� 62~64, 6
								{
									BlinkString("������", 60, 10, eColor::Red);
									InitMessageBox();
									cout << "�����̸� ¯���� �� ���� ���� ���� �¾ҽ��ϴ�.";
									_getch();
									InitMessageBox();
									cout << mCharacters[mSelectedMonster].GetName() << "�� ������ ���̸� ���� ���� �����ϴ�.";
									mCharacters[mSelectedMonster].UpdateHealthPoint(0);
									DisplayUpdatedHealthPoint(mSelectedMonster, previousMonsterHp);
									InitMessageBox();
									cout << mCharacters[mSelectedMonster].GetName() << ": ����...���� ���ڶ��...";									
								}
								else
								{
									BlinkCharacterImage(mSelectedMonster, eColor::Red);
									mCharacters[mSelectedMonster].UpdateHealthPoint(max(mCharacters[mSelectedMonster].GetHealthPoint() - 1, 0));
									DisplayUpdatedHealthPoint(mSelectedMonster, previousMonsterHp);
								}
							}
							break;
						case eMove::EatFlower:
							if (mCharacters[eCharacterName::Flower].IsAlive() == false)
							{
								bIsMoveDecided = true;
								bIsPlayerTurn = false;
								InitMessageBox();
								if (eCharacterName::Gandhi == mSelectedMonster && mCharacters[mSelectedMonster].GetAttackPoint() == 0)
								{
									break;
								}
								cout << mCharacters[eCharacterName::Player].GetName() << "��(��) " << mCharacters[eCharacterName::Flower].GetName() << "�� �Ծ����ϴ�.";
								DisplayItemPickUpAnimation(eCharacterName::FlowerEdible);
								_getch();
								InitMessageBox();
								cout << "���� ���ο����ϴ�.";
								mCharacters[eCharacterName::Player].UpdateExpression(Character::eExpression::PlayerDisappointed);
								DisplayCharacterImage(eCharacterName::Player);								
							}
							break;
						case eMove::UseGrenade:
							if (mCharacters[eCharacterName::Grenade].IsAlive() == false)
							{
								bIsMoveDecided = true;
								bIsPlayerTurn = false;
								InitMessageBox();
								if (eCharacterName::Gandhi == mSelectedMonster && mCharacters[mSelectedMonster].GetAttackPoint() == 0)
								{
									break;
								}
								cout << mCharacters[eCharacterName::Player].GetName() << "��(��) " << mCharacters[eCharacterName::Grenade].GetName() << "�� �Ծ����ϴ�.";
								DisplayItemPickUpAnimation(eCharacterName::GrenadeEdible);
								InitMessageBox();
								cout << mCharacters[eCharacterName::Player].GetName() << "�� ��ӿ� �ִ� " << mCharacters[eCharacterName::Grenade].GetName()  << "�� �������ϴ�.";
								mCharacters[eCharacterName::Player].UpdateExpression(Character::eExpression::PlayerWhatThe);
								DisplayCharacterImage(eCharacterName::Player);
								DisplayPlayerBodyExplosionAnimation();
								InitMessageBox();
								cout << mCharacters[eCharacterName::Player].GetName() << "��(��) �ſ� ���ļ� ü���� 20 ���������ϴ�.";
								mCharacters[eCharacterName::Player].UpdateHealthPoint(max(mCharacters[eCharacterName::Player].GetHealthPoint() - 20, 0));
								DisplayUpdatedHealthPoint(eCharacterName::Player, previousPlayerHP);
							}
							break;
						case eMove::MiddleFinger:
							if (mCharacters[eCharacterName::Billy].IsAlive() == false)							
							{
								bIsMoveDecided = true;
								bIsPlayerTurn = false;
								InitMessageBox();
								cout << mCharacters[eCharacterName::Player].GetName() << "��(��) " << mCharacters[mSelectedMonster].GetName() << "���� ������ �߽��ϴ�.";
								UseMove(eMove::MiddleFinger);
								InitMessageBox();
								if (eCharacterName::Gandhi == mSelectedMonster && mCharacters[mSelectedMonster].GetAttackPoint() == 0)
								{
									cout << mCharacters[mSelectedMonster].GetName() << ": ...";
									_getch();									
									mCharacters[mSelectedMonster].UpdateExpression(Character::eExpression::GandhiPissedOff);
									DisplayCharacterImage(mSelectedMonster);
									InitMessageBox();
									cout << mCharacters[mSelectedMonster].GetName() << ": ������ ����ϸ� �������´� �Ͼ�� ���� ���Դϴ�.";
									_getch();
									InitMessageBox();
									mCharacters[eCharacterName::Player].UpdateExpression(Character::eExpression::PlayerWhatThe);
									DisplayCharacterImage(eCharacterName::Player);
									BlinkCharacterImage(mSelectedMonster, eColor::LightMagenta);									
									mCharacters[mSelectedMonster].UpdateHealthPoint(66);
									mCharacters[mSelectedMonster].UpdateMaxHealthPoint(66);
									DisplayUpdatedHealthPoint(mSelectedMonster, previousMonsterHp);
									mCharacters[mSelectedMonster].UpdateAttackPoint(mCharacters[eCharacterName::Player].GetHealthPoint() - 1);
								}
								else if (eCharacterName::Gandhi == mSelectedMonster)
								{
									cout << mCharacters[mSelectedMonster].GetName() << ": �׾�� ������ �����ڱ�.";
									_getch();
									InitMessageBox();
									mCharacters[eCharacterName::Player].UpdateExpression(Character::eExpression::PlayerWhatThe);
									DisplayCharacterImage(eCharacterName::Player);
									mCharacters[mSelectedMonster].UpdateExpression(Character::eExpression::GandhiSuperSaiyan);									
									BlinkCharacterImage(mSelectedMonster, eColor::LightYellow);
									mCharacters[mSelectedMonster].UpdateAttackPoint(444);
								}
								else
								{
									cout << mCharacters[mSelectedMonster].GetName() << "��(��) ȭ�� ���� �����߽��ϴ�.";
									_getch();
									InitMessageBox();
									cout << mCharacters[mSelectedMonster].GetName() << "�� ���ݷ��� 5 ����߽��ϴ�.";
									mCharacters[eCharacterName::Player].UpdateExpression(Character::eExpression::PlayerWhatThe);
									DisplayCharacterImage(eCharacterName::Player);
									BlinkCharacterImage(mSelectedMonster, eColor::LightBlue);
									mCharacters[mSelectedMonster].UpdateAttackPoint(mCharacters[mSelectedMonster].GetAttackPoint() + 5);
								}
								DisplayUpdatedAttackPoint(mSelectedMonster, previousMonsterAP);
							}
							break;
						case eMove::FatalAttack:
							if (mKilledMonsterCount >= 9 && mCharacters[eCharacterName::Player].GetHealthPoint() == 1)							
							{
								bIsMoveDecided = true;
								bIsPlayerTurn = false;
								InitMessageBox();
								if (eCharacterName::Gandhi == mSelectedMonster && mCharacters[mSelectedMonster].GetAttackPoint() == 0)
								{
									break;
								}
								cout << mCharacters[eCharacterName::Player].GetName() << "��(��) " << mCharacters[mSelectedMonster].GetName() << "���� �ʻ�⸦ ����ϴ�.";
								UseMove(eMove::FatalAttack);
								mCharacters[mSelectedMonster].UpdateHealthPoint(0);
								DisplayUpdatedHealthPoint(mSelectedMonster, previousMonsterHp);
								InitMessageBox();
								cout << mCharacters[mSelectedMonster].GetName() << ": �Ź�...";								
							}
							break;
						default:
							break;
						}
						break;
					default:
						break;
					}
					GotoXY(x, 23);
				}
				bIsMoveDecided = false;
				if (eCharacterName::Gandhi == mSelectedMonster && mCharacters[mSelectedMonster].GetAttackPoint() == 0 && x != eMove::MiddleFinger)
				{
					GotoXY(4, 22);
					cout << mCharacters[mSelectedMonster].GetName() << "�� ������ ������ �������̱� ������ ������ ������ ������׽��ϴ�.";
					_getch();
					break;
				}
			}
			else
			{
				if (eCharacterName::GrassHopper == mSelectedMonster)
				{
					mCharacters[mSelectedMonster].UpdateExpression(Character::eExpression::GrassHopperNormal);
				}
				else if (eCharacterName::CamelCriket == mSelectedMonster)
				{
					mCharacters[mSelectedMonster].UpdateExpression(Character::eExpression::CamelCriketNormal);
				}
				InitMessageBox();
				if (eCharacterName::Gandhi == mSelectedMonster && mCharacters[mSelectedMonster].GetAttackPoint() == 444)
				{
					UseMove(eMove::Corn);
					mCharacters[eCharacterName::Player].UpdateExpression(Character::eExpression::PlayerFatalKilled);
				}
				else
				{
					cout << mCharacters[mSelectedMonster].GetName() << "��(��) " << mCharacters[eCharacterName::Player].GetName() << "��(��) ���Ƚ��ϴ�.";
					DisplayCharacterImage(mSelectedMonster);
					DisplayCharacterAttackAnimation(mSelectedMonster);
					BlinkCharacterImage(eCharacterName::Player, eColor::Red);					
				}
				mCharacters[mSelectedMonster].Attack(mCharacters[eCharacterName::Player]);				
				bIsPlayerTurn = true;
				DisplayUpdatedHealthPoint(eCharacterName::Player, previousPlayerHP);
			}
			
			if (eCharacterName::Gandhi == mSelectedMonster)
			{
				if (mCharacters[mSelectedMonster].GetAttackPoint() == 444)
				{
					Sleep(1000);
				}
				else if (previousMonsterAP > 0)
				{
					_getch();
				}				
			}			
			else
			{
				_getch();
			}

			InitMessageBox();

			if (mCharacters[mSelectedMonster].IsAlive() == false)
			{
				mKilledMonsterCount++;
				cout << mCharacters[mSelectedMonster].GetName() << "��(��) �̰���ϴ�.";
				switch (mSelectedMonster)
				{
				case eCharacterName::GrassHopper:
					mCharacters[mSelectedMonster].UpdateExpression(Character::eExpression::GrassHopperDead);
					break;
				case eCharacterName::Billy:
					if (x == eMove::ThrowStone)
					{
						mCharacters[mSelectedMonster].UpdateExpression(Character::eExpression::BillyGozaDead);
					}
					else
					{
						mCharacters[mSelectedMonster].UpdateExpression(Character::eExpression::BillyNormalDead);
					}
					break;
				case eCharacterName::CamelCriket:
					mCharacters[mSelectedMonster].UpdateExpression(Character::eExpression::CamelCriketDead);
					break;
				case eCharacterName::Gandhi:
					mCharacters[mSelectedMonster].UpdateExpression(Character::eExpression::GandhiDead);
					break;
				default:
					break;
				}
				DisplayCharacterImage(mSelectedMonster);
				DisplayCharacterDownAnimation(mSelectedMonster);
				ShowRewardEvent(mSelectedMonster);
			}

			if (mCharacters[eCharacterName::Player].IsAlive() == false)
			{
				cout << "����� �й��߽��ϴ�.";
				if (eCharacterName::Gandhi == mSelectedMonster && mCharacters[mSelectedMonster].GetAttackPoint() == 444)
				{
					mCharacters[eCharacterName::Player].UpdateExpression(Character::eExpression::PlayerFatalKilled);					
				}
				else
				{
					mCharacters[eCharacterName::Player].UpdateExpression(Character::eExpression::PlayerDead);
				}
				DisplayCharacterImage(eCharacterName::Player);
				DisplayCharacterDownAnimation(eCharacterName::Player);
				if (x == eMove::UseGrenade)
				{
					_getch();
					InitMessageBox();
					cout << mCharacters[mSelectedMonster].GetName() << ": ������";
				}
				_getch();
			}

			x = 10;			
		}

		system("cls");
	}

	void GameManager::ShowEnding()
	{
		if (mCharacters[eCharacterName::Player].IsAlive() == false)
		{
			GotoXY(35, 12);
			cout << "Game Over";
		}
		else if (mKilledMonsterCount == 10)
		{
			GotoXY(25, 11);
			cout << "��� ���͵��� ����Ʈ�Ƚ��ϴ�.";
			GotoXY(30, 13);
			cout << "����� �ְ����Դϴ�.";
			GotoXY(36, 16);
			cout << "The End";
		}

		GotoXY(19, 20);
		Sleep(1500);
		cout << "�ƹ�Ű�� ������ Ÿ��Ʋ ȭ������ �̵��մϴ�.";
		_getch();
		system("cls");
	}

	void GameManager::InitGame()
	{
		mbExitGame = false;
		mSelectedMonster = eCharacterName::Stone;
		mKilledMonsterCount = 0;

		mCharacters.clear();
		mCharacters.reserve(11);
		mCharacters.push_back(Character("�÷��̾�",
			{
				"                              ",
				"        ������            ",
				"      �������            ",
				"      �����ˡ��          ",
				"      ��������          ",
				"      �������            ",
				"        �������          ",
				"      ������              ",
				"    ��������            ",
				"   ���������           ",
				"  ����������          "
			},
			10, 5, 1, 1));
		mCharacters.push_back(Character("������",
			{
				"                              ",
				"                              ",
				"                              ",
				"                              ",
				"                              ",
				"                              ",
				"                              ",
				"             ��               ",
				"                              ",
				"                              ",
				"                              "
			},
			1, 1, 2, 2));
		mCharacters.push_back(Character("��",
			{
				"                              ",
				"                              ",
				"                              ",
				"                              ",
				"                              ",	//"            _  _              "
				"             ��               ",	//"          �� ��_��            ",
				"           �ܡݡ�             ",	//"         ����`�� ��           ",
				"            �ܡ�              ",	//"          ��_��_��            ",
				"             ��               ",
				"           �Ц� ��            ",
				"                              "
			},
			1, 0, 57, 9));
		mCharacters.push_back(Character("����",
			{
				"                              ",
				"          �� �� ��            ",
				"        �� ��  �� ��          ",
				"       �� �� �� �� ��         ",
				"      ����  ��   �� ��        ",
				"      ��  �� �� �� ��         ",
				"        �� �� ��  ��          ",
				"            �Ƣ�              ",
				"            �Ƣ�              ",
				"            �Ƣ�              ",
				"            �Ƣ�              "
			},
			20, 1, 52, 7));
		mCharacters.push_back(Character("����",
			{
				"                              ",
				"                              ",
				"                              ",
				"                              ",
				"           ��                 ",
				"           ���ۡ�             ",
				"            ����              ",
				"                              ",
				"                              ",
				"                              ",
				"                              "
			},
			6, 1, 57, 8));
		mCharacters.push_back(Character("�޶ѱ�",
			{
				"                              ",
				"                              ",
				"                              ",
				"                ��            ",
				"  ��___________��_____      ",
				"   ���� ���ΥΡ�Ρ��ΡУ�_   ",	//[5] "   ���� ���ΥΡ�Ρ��ΡУ�_   "
				"     ��_��� ��Ӥӡ��������� ",	//index = 5, WhatExpression = 54
				"       �� �����������������  ",	//[5] "   ���� ���ΥΡ�Ρ��ΡУ�_   "
				"       �� ��         ��       ",	////index = 5, WhatExpression = 56
				"                              ",
				"                              "
			},
			10, 2, 48, 8));
		mCharacters.push_back(Character("��������å",
			{
				"                              ",
				"  f(x,y)=x3+x2y3-2y2;(2,1)    ",
				"  fx=3x^2+2xy^3-0             ",
				"  fy=0+x^2*3y^2-4y            ",
				"  f(x,y)=sin(3x+y)            ",
				" fx(x,y)=sin3xsiny-9cos3xcosy ",
				" z=f(x,y)=log��x^2+x^3        ",
				"   fx=1/{2(��x^2+x^3)         ",
				"      (��2x+3x^2)}            ",
				" ���_D ye^(-x^3 ) dA         ",
				" =��_0^1��_0^xye^(-x^3 )dydx  "
			},
			30, 3, 48, 6));
		mCharacters.push_back(Character("����ź",
			{
				"                              ",
				"                              ",
				"                              ",
				"             ��               ",
				"             ��               ",
				"            ���              ",
				"           ����             ",
				"          �����            ",
				"          �����            ",
				"           ����             ",
				"                              "
			},
			44, 4, 56, 10));
		mCharacters.push_back(Character("����",
			{
				"                              ",	//"                              "
				"         Ҭ  ����             ",	//"           ����`��            "
				"        �Σ�����`�� Ҭ        ",	//"            ����              "
				"      �� ��  �Σ� �� ��       ",	//"           ������             "
				"        ����[.][.]�ҫ�        ",	//"         ��������             "
				"          �����ݣ���          ",	//"        ���� ����             "
				"          ����������          ",	//"       [o`]����������         "
				"         ��  ����  ��         ",	//"               ��             "
				"           ��     ��          ",	//"                              "
				"         �� ��  �� ��         ",	//"                              ", 53, 10
				"         �Ы�    ����         "
			},
			70, 20, 61, 10));
		mCharacters.push_back(Character("������",
			{
				"                              ",
				"                              ",
				"                              ",
				"                      ��      ",
				"        �� �� �� �� ��    / ��",
				"    ���� �� �� �� �� �� �� /  ��",	//[7] "  �������������� /����  ��    "
				"   /�� ���� �� �� �� �� ����   ��",	//index = 9, WhatExpression = 94
				"  ���� �ܡ��� �� ��  /�� ��   ��",	//[7] "  �������������� /����  ��    "
				"  / �� �� �� �� �� �� �� �� �� �� ��",	//index = 9, WhatExpression = 96
				" ��          ��           ��   ",
				"                              "
			},
			14, 4, 48, 10));
		mCharacters.push_back(Character("����",
			{
				"                              ",	//�ء۫�4, 5, 7
				"          .---._              ",	//"      �Ρ��Ρ��Ρ��Σ�        "
				"        ��      '.            ",	//"      ��������������          "
				"       ��-߲--   ��           ",	//"       ��_߲__������          "
				"      ����   ��    ��         ",	//"      ����߲�� ����           "4
				"        �ܫϡܦ� �� ��        ",	//"        �ݫϡݦ�����          "5
				"       �� <..>��   ��         ",	//"       ��<..>������           "
				"        ��''\"��  ��           ",	//"        ���� �� ��            "7
				"    ___  ����    ��     __    ",	//"    �Ρ� ����   ��   �Ρ�     "
				"   ��  ����     �� �� ��  ��  ",	//"   ��  ����     ������  ��    "
				"  ��      ��-�� �� �� ��     �� "
			},
			10, 0, 52, 7));
		
		mThrowStoneFrames[0] = {
			"                              ",
			"        ������            ",
			"      �������            ",
			"      �����ˡ��          ",
			"      ��������          ",
			"      �������            ",
			"        �������          ",
			"      ������              ",
			"    ��������            ",
			"   ���������           ",
			"  ����������          "
		};
		mThrowStoneFrames[1] = {
			"                              ",
			"        ������            ",
			"      �������            ",
			"      �����ˡ��          ",
			"      ��������          ",
			"      �������            ",
			"        �������          ",
			"      ������              ",
			"    ��������            ",
			"   ����������         ",
			"  ����������          "
		};
		mThrowStoneFrames[2] = {
			"                              ",
			"        ������            ",
			"      �������            ",
			"      �����ˡ��          ",
			"      ��������          ",
			"      �������            ",
			"        �������          ",
			"      ������      ��      ",
			"    ��������   ��       ",
			"   ����������         ",
			"  ����������          "
		};
		mThrowStoneFrames[3] = {
			"                              ",
			"        ������            ",
			"      �������            ",
			"      �����ˡ��          ",
			"      ��������          ",
			"      �������            ",
			"        �������   ��     ",
			"      ������      ��      ",
			"    ��������   ��       ",
			"   ����������         ",
			"  ����������          "
		};
		mThrowStoneFrames[4] = {
			"                              ",
			"        ������            ",
			"      �������            ",
			"      �����ˡ��          ",
			"      ��������          ",
			"      �������    ��      ",
			"        �������  ��      ",
			"      ������      ��      ",
			"    ��������   ��       ",
			"   ����������         ",
			"  ����������          "
		};
		mThrowStoneFrames[5] = {
			"                              ",
			"        ������            ",
			"      �������            ",
			"      �����ˡ��          ",
			"      ��������  ��      ",
			"      �������    ��      ",
			"        �������  ��      ",
			"      ������      ��      ",
			"    ��������   ��       ",
			"   ����������         ",
			"  ����������          "
		};
		mThrowStoneFrames[6] = {
			"                              ",
			"        ������            ",
			"      �������            ",
			"      �����ˡ��          ",
			"      ��������  ���    ",
			"      �������     ��     ",
			"        �������   ��     ",
			"      ������      ��      ",
			"    ��������   ��       ",
			"   ����������         ",
			"  ����������          "
		};
		mThrowStoneFrames[7] = {
			"                              ",
			"        ������            ",
			"      �������            ",
			"      �����ˡ��          ",
			"      ��������   ���   ",
			"      �������     ��     ",
			"        �������   ��     ",
			"      ������      ��      ",
			"    ��������   ��       ",
			"   ����������         ",
			"  ����������          "
		};
		mThrowStoneFrames[8] = {
			"                              ",
			"        ������            ",
			"      �������            ",
			"      �����ˡ��          ",
			"      ��������    ���  ",
			"      �������      ��    ",
			"        �������   ��     ",
			"      ������      ��      ",
			"    ��������   ��       ",
			"   ����������         ",
			"  ����������          "
		};
		mThrowStoneFrames[9] = {
			"                              ",
			"        ������            ",
			"      �������            ",
			"      �����ˡ��          ",
			"      ��������     ��� ",
			"      �������       ��   ",
			"        �������    ��    ",
			"      ������      ��      ",
			"    ��������   ��       ",
			"   ����������         ",
			"  ����������          "
		};
		mThrowStoneFrames[10] = {
			"                              ",
			"        ������            ",
			"      �������            ",
			"      �����ˡ��          ",
			"      ��������     ��� ",
			"      �������      ��    ",
			"        �������   ��     ",
			"      ������      ��      ",
			"    ��������   ��       ",
			"   ����������         ",
			"  ����������          "
		};
		mThrowStoneFrames[11] = {
			"                              ",
			"        ������            ",
			"      �������            ",
			"      �����ˡ��          ",
			"      ��������      ���",
			"      �������       ��   ",
			"        �������    ��    ",
			"      ������       ��     ",
			"    ��������   ��       ",
			"   ����������         ",
			"  ����������          "
		};
		mThrowStoneFrames[12] = {
			"                              ",
			"        ������            ",
			"      �������            ",
			"      �����ˡ��          ",
			"      ��������          ",
			"      �������         �� ",
			"        �������     ��   ",
			"      ������       ��     ",
			"    ��������   ��       ",
			"   ����������         ",
			"  ����������          "
		};
		mThrowStoneFrames[13] = {
			"                              ",
			"        ������            ",
			"      �������            ",
			"      �����ˡ��          ",
			"      ��������          ",
			"      �������            ",
			"        �������          ",
			"      ������         ��� ",
			"    ��������   ���     ",
			"   ����������         ",
			"  ����������          "
		};
		mThrowStoneFrames[14] = {
			"                              ",
			"        ������            ",
			"      �������            ",
			"      �����ˡ��          ",
			"      ��������          ",
			"      �������            ",
			"        �������          ",
			"      ������              ",
			"    ��������     ���� ",
			"   �����������       ",
			"  ����������          "
		};
		mThrowStoneFrames[15] = {
			"                              ",
			"        ������            ",
			"      �������            ",
			"      �����ˡ��          ",
			"      ��������          ",
			"      �������            ",
			"        �������          ",
			"      ������              ",
			"    ��������            ",
			"   �������������   ",
			"  ����������       �� "
		};

		mMiddleFingerFrames[0] = {
			"                              ",
			"        ������            ",
			"      �������            ",
			"      �����ˡ��          ",
			"      ��������          ",
			"      �������            ",
			"        �������          ",
			"      ������              ",
			"    ��������            ",
			"   ���������           ",
			"  ����������          "
		};
		mMiddleFingerFrames[1] = {
			"                              ",
			"        ������            ",
			"      �������            ",
			"      �����ˡ��          ",
			"      ��������          ",
			"      �������            ",
			"        �������          ",
			"      ������              ",
			"    ��������            ",
			"   ����������         ",
			"  ����������          "
		};
		mMiddleFingerFrames[2] = {
			"                              ",
			"        ������            ",
			"      �������            ",
			"      �����ˡ��          ",
			"      ��������          ",
			"      �������            ",
			"        �������          ",
			"      ������              ",
			"    ��������            ",
			"   �����������       ",
			"  ����������          "
		};
		mMiddleFingerFrames[3] = {
			"                              ",
			"        ������            ",
			"      �������            ",
			"      �����ˡ��          ",
			"      ��������          ",
			"      �������            ",
			"        �������          ",
			"      ������              ",
			"    ��������     ��     ",
			"   �����������       ",
			"  ����������          "
		};
		mMiddleFingerFrames[4] = {
			"                              ",
			"        ������            ",
			"      �������            ",
			"      �����ˡ��          ",
			"      ��������          ",
			"      �������            ",
			"        �������          ",
			"      ������        ��    ",
			"    ��������     ��     ",
			"   �����������       ",
			"  ����������          "
		};
		mMiddleFingerFrames[5] = {
			"                              ",
			"        ������            ",
			"      �������            ",
			"      �����ˡ��          ",
			"      ��������          ",
			"      �������            ",
			"        �������     ��   ",
			"      ������        ��    ",
			"    ��������     ��     ",
			"   �����������       ",
			"  ����������          "
		};
		mMiddleFingerFrames[6] = {
			"                              ",
			"        ������            ",
			"      �������            ",
			"      �����ˡ��          ",
			"      ��������          ",
			"      �������     ���� ",
			"        �������   ���� ",
			"      ������        ��    ",
			"    ��������     ��     ",
			"   �����������       ",
			"  ����������          "
		};
		mMiddleFingerFrames[7] = {
			"                              ",
			"        ������            ",
			"      �������            ",
			"      �����ˡ��          ",
			"      ��������     ��   ",
			"      �������     ���� ",
			"        �������   ���� ",
			"      ������        ��    ",
			"    ��������     ��     ",
			"   �����������       ",
			"  ����������          "
		};
		mMiddleFingerFrames[8] = {
			"                              ",
			"        ������            ",
			"      �������            ",
			"      �����ˡ��     ��   ",
			"      ��������     ��   ",
			"      �������     ���� ",
			"        �������   ���� ",
			"      ������        ��    ",
			"    ��������     ��     ",
			"   �����������       ",
			"  ����������          "
		};

		mFatalAttackImage[0] = "   ����       ";
		mFatalAttackImage[1] = "  �����      ";
		mFatalAttackImage[2] = " ������     ";
		mFatalAttackImage[3] = "  ������    ";
		mFatalAttackImage[4] = "   ������   ";
		mFatalAttackImage[5] = "      �����  ";
		mFatalAttackImage[6] = "        ����  ";
		mFatalAttackImage[7] = "         ���� ";
		mFatalAttackImage[8] = "           ��� ";
		mFatalAttackImage[9] = "           ��� ";
		mFatalAttackImage[10] = "           ��� ";
		mFatalAttackImage[11] = "           ��� ";
		mFatalAttackImage[12] = "          ���  ";
		mFatalAttackImage[13] = "          ���  ";
		mFatalAttackImage[14] = "         ���   ";
		mFatalAttackImage[15] = "        ���    ";
		mFatalAttackImage[16] = "       ���     ";
		mFatalAttackImage[17] = "    ���        ";
		mFatalAttackImage[18] = "���            ";

		mCornShotImage[0] = "      �ˢ�";
		mCornShotImage[1] = "   �ˢˢ�";
		mCornShotImage[2] = " �ˢˢ�";
		mCornShotImage[3] = "�ˢ�";

		mCornImageArea[0] = "          ";
		mCornImageArea[1] = "         ";
		mCornImageArea[2] = "       ";
		mCornImageArea[3] = "    ";

		mPlayerHairImage[0] = "  ���";
		mPlayerHairImage[1] = "��";

		mPlayerHairImageArea[0] = "      ";
		mPlayerHairImageArea[1] = "  ";

		mFlowerImage[0] = "  ��  ";
		mFlowerImage[1] = "�ܡݡ�  ";
		mFlowerImage[2] = " �ܡ�  ";
		mFlowerImage[3] = "  ��  ";
		mFlowerImage[4] = "�Ц� ��  ";

		mFruitImage[0] = "   ��  ";
		mFruitImage[1] = "  �Ρ�  ";
		mFruitImage[2] = "��`��`��  ";
		mFruitImage[3] = "  ��_��  ";

		mGrenadeImage[0] = "   ��  ";
		mGrenadeImage[1] = "   ��  ";
		mGrenadeImage[2] = "  ���  ";
		mGrenadeImage[3] = " ����  ";
		mGrenadeImage[4] = "�����  ";
		mGrenadeImage[5] = "�����  ";
		mGrenadeImage[6] = " ����  ";

		mCornImage[0] = " �� ";
		mCornImage[1] = "�ˢ�";
		mCornImage[2] = "�ˢ�";
		mCornImage[3] = "�ˢ�";
		mCornImage[4] = "�ˢ�";
		mCornImage[5] = " �� ";

		mPlayerHeadImage[0] = "  ������  ";
		mPlayerHeadImage[1] = "�������  ";
		mPlayerHeadImage[2] = "�����ˡ��";
		mPlayerHeadImage[3] = "��������";
		mPlayerHeadImage[4] = "�������  ";
		mPlayerHeadImage[5] = "  �������";
		mPlayerHeadImage[6] = "������  ";

		mItemArea[0] = "     ";
		mItemArea[1] = "     ";
		mItemArea[2] = "      ";
		mItemArea[3] = "       ";
		mItemArea[4] = "        ";
		mItemArea[5] = "        ";
		mItemArea[6] = "       ";

		mPlayerMouthArea[0] = "  ";
		mPlayerMouthArea[1] = "  ";

		mEraser[0] = "            ";
		mEraser[1] = "            ";
		mEraser[2] = "              ";
		mEraser[3] = "              ";
	}

	void GameManager::DisplayCharacterImage(const eCharacterName characterName)
	{
		int16_t x;
		int16_t y;

		if (eCharacterName::Player == characterName)
		{
			x = 3;
			y = 9;
		}
		else
		{
			x = 48;
			y = 3;
		}

		//SetCursorType(eCursorType::Invisible);

		for (int16_t row = 1; row <= Image::MAX_ROW; ++row)
		{
			GotoXY(x, y + row);
			cout << mCharacters[characterName].GetImage().rows[row - 1];
		}

		//SetCursorType(eCursorType::Visible);
	}

	void GameManager::DisplayCharacterImage(const eCharacterName characterName, const int16_t xOffset)
	{
		int16_t x;
		int16_t y;

		if (eCharacterName::Player == characterName)
		{
			x = 3 + xOffset;
			y = 10;
		}
		else
		{
			x = 48 + xOffset;
			y = 4;
		}

		for (int16_t row = 0; row < Image::MAX_ROW; ++row)
		{
			GotoXY(x, y + row);
			cout << mCharacters[characterName].GetImage().rows[row];
		}
	}

	void GameManager::DisplayCharacterState(const eCharacterName characterName)
	{
		int16_t x;
		int16_t y;

		if (characterName == eCharacterName::Player)
		{
			x = 40;
			y = 15;
		}
		else
		{
			x = 5;
			y = 2;
		}

		SetCursorType(eCursorType::Invisible);

		GotoXY(x, y);
		cout << "<" << mCharacters[characterName].GetName() << ">";		
		GotoXY(x, y + 1);
		cout << "ü�� ";
		GotoXY(x, y + 2);
		cout << "           0 /";
		GotoXY(x, y + 3);
		cout << "���ݷ�:  0";

		Sleep(500);

		int16_t hpDisplay = 1;
		int16_t apDisplay = 1;
		for (; hpDisplay <= mCharacters[characterName].GetHealthPoint() || apDisplay <= mCharacters[characterName].GetAttackPoint(); ++hpDisplay, ++apDisplay)
		{
			if (hpDisplay <= mCharacters[characterName].GetHealthPoint())
			{
				GotoXY(x + 4 + hpDisplay, y + 1);
				cout << "|";
				GotoXY(x + 10, y + 2);
				cout << setw(2) << right << hpDisplay;
			}

			if (apDisplay <= mCharacters[characterName].GetAttackPoint())
			{
				GotoXY(x + 8, y + 3);
				cout << setw(2) << right << apDisplay;
			}

			Sleep(15);
		}
		GotoXY(x + 15, y + 2);
		mCharacters[characterName].UpdateMaxHealthPoint(mCharacters[characterName].GetHealthPoint());
		cout << setw(2) << right << mCharacters[characterName].GetMaxHealthPoint();		

		SetCursorType(eCursorType::Visible);
	}

	void GameManager::DisplayUpdatedHealthPoint(const eCharacterName characterName, const int16_t previousHp)
	{
		int16_t x;
		int16_t y;

		if (eCharacterName::Player == characterName)
		{
			x = 40;
			y = 15;
		}
		else
		{
			x = 5;
			y = 2;
		}

		SetCursorType(eCursorType::Invisible);

		for (int16_t hpDisplay = 1; hpDisplay <= abs(mCharacters[characterName].GetHealthPoint() - previousHp); ++hpDisplay)
		{
			if (mCharacters[characterName].GetHealthPoint() <= previousHp - hpDisplay)
			{
				GotoXY(x + 5 + previousHp - hpDisplay, y + 1);
				cout << " ";
			}
			else if (mCharacters[characterName].GetHealthPoint() >= previousHp + hpDisplay)
			{
				GotoXY(x + 4 + previousHp + hpDisplay, y + 1);
				cout << "|";
			}

			GotoXY(x + 10, y + 2);
			if (mCharacters[characterName].GetHealthPoint() <= previousHp - hpDisplay)
			{
				cout << setw(2) << right << previousHp - hpDisplay;
			}
			else if (mCharacters[characterName].GetHealthPoint() >= previousHp + hpDisplay)
			{
				cout << setw(2) << right << previousHp + hpDisplay;
			}

			if (mCharacters[characterName].GetHealthPoint() > previousHp && hpDisplay == abs(mCharacters[characterName].GetHealthPoint() - previousHp))
			{
				GotoXY(x + 15, y + 2);
				mCharacters[characterName].UpdateMaxHealthPoint(mCharacters[characterName].GetHealthPoint());
				cout << setw(2) << right << mCharacters[characterName].GetMaxHealthPoint();
			}			

			Sleep(30);			
		}

		SetCursorType(eCursorType::Visible);
	}

	void GameManager::DisplayUpdatedAttackPoint(const eCharacterName characterName, const int16_t previousAp)
	{
		int16_t x;
		int16_t y;

		if (eCharacterName::Player == characterName)
		{
			x = 40;
			y = 15;
		}
		else
		{
			x = 5;
			y = 2;
		}

		SetCursorType(eCursorType::Invisible);

		for (uint16_t apDisplay = 1; apDisplay <= mCharacters[characterName].GetAttackPoint() - previousAp; ++apDisplay)
		{
			if (mCharacters[characterName].GetAttackPoint() >= previousAp + apDisplay)	//AP ��ġ ����
			{
				GotoXY(x + 8, y + 3);
				printf("%2d", previousAp + apDisplay);
			}

			if (characterName == eCharacterName::Gandhi && mCharacters[characterName].GetAttackPoint() == 444)
			{
				Sleep(1);
			}
			else
			{
				Sleep(30);
			}
		}

		SetCursorType(eCursorType::Visible);
	}

	void GameManager::InitMessageBox()
	{
		GotoXY(1, 21);	//�޼����ڽ� ������ (2, 21)~(77, 24)
		cout << " ����������������������������������������������������������������������������������������������������������������������������������������������������������" << endl;		
		cout << " ��                                                                           ��" << endl;
		cout << " ��                                                                           ��" << endl;	//3(7, 23), (26, 23), (45, 23), (64, 23){70}3 ����72ĭ ����19
		cout << " ����������������������������������������������������������������������������������������������������������������������������������������������������������";
		GotoXY(4, 22);
	}

	void GameManager::DisplayMessageAnimation(const string& message)
	{
		char letters[3];

		for (size_t arr = 0; arr < message.length() / 2; ++arr)
		{
			for (int16_t index = 0; index <= 2; ++index)
			{
				if (index == 2)
				{
					letters[index] = '\0';
				}
				else
				{
					letters[index] = message[index + 2 * arr];
				}
			}
			cout << letters;

			Sleep(50);

			if (_kbhit())
			{
				InitMessageBox();
				_getch();
				cout << message;
				break;
			}
		}
	}

	void GameManager::UpdateMoveList()
	{		
		if (mCharacters[eCharacterName::Player].GetHealthPoint() == 1 && mKilledMonsterCount == eCharacterName::Count - 2)
		{
			GotoXY(60, 23);
			cout << "�ʻ��";
		}
		if (mCharacters[eCharacterName::Stone].IsAlive() == false)
		{
			GotoXY(20, 23);			
			cout << "¯��";
		}
		if (mCharacters[eCharacterName::Flower].IsAlive() == false)
		{
			GotoXY(30, 23);
			cout << mCharacters[eCharacterName::Flower].GetName();
		}
		if (mCharacters[eCharacterName::Grenade].IsAlive() == false)
		{
			GotoXY(40, 23);
			cout << mCharacters[eCharacterName::Grenade].GetName();
		}
		if (mCharacters[eCharacterName::Billy].IsAlive() == false)
		{
			GotoXY(50, 23);
			cout << "����";
		}
	}

	void GameManager::DisplayCharacterAttackAnimation(const eCharacterName characterName)
	{
		SetCursorType(eCursorType::Invisible);

		Sleep(300);

		for (int16_t xOffset = 0; xOffset <= 5; ++xOffset)
		{
			if (characterName == eCharacterName::Player)
			{
				DisplayCharacterImage(characterName, xOffset);
			}
			else
			{
				DisplayCharacterImage(characterName, -xOffset);
			}
			Sleep(15);
		}

		Sleep(100);

		for (int16_t xOffset = 0; xOffset <= 5; ++xOffset)
		{
			if (characterName == eCharacterName::Player)
			{
				DisplayCharacterImage(characterName, 5 - xOffset);
			}
			else
			{
				DisplayCharacterImage(characterName, -5 + xOffset);
			}
			Sleep(15);
		}

		Sleep(300);

		SetCursorType(eCursorType::Visible);
	}

	void GameManager::BlinkCharacterImage(const eCharacterName characterName, const eColor color)
	{
		SetCursorType(eCursorType::Invisible);

		if (characterName == eCharacterName::Player)
		{
			switch (color)
			{
			case eColor::Red:
				mCharacters[characterName].UpdateExpression(Character::eExpression::PlayerDamaged);
				break;
			case eColor::LightBlue:
				mCharacters[characterName].UpdateExpression(Character::eExpression::PlayerPowerUp);
				break;
			case eColor::LightGreen:
				mCharacters[characterName].UpdateExpression(Character::eExpression::PlayerHealthUp);
				break;
			case eColor::LightYellow:
				mCharacters[characterName].UpdateExpression(Character::eExpression::PlayerWhatThe);
				break;
			default:
				break;
			}
		}
		else
		{
			if (color == eColor::Red)
			{
				switch (characterName)
				{
				case eCharacterName::GrassHopper:
					mCharacters[characterName].UpdateExpression(Character::eExpression::GrassHopperDamaged);
					break;
				case eCharacterName::CamelCriket:
					mCharacters[characterName].UpdateExpression(Character::eExpression::CamelCriketDamaged);
					break;
				default:
					break;
				}
			}
		}		

		for (int16_t blinkCount = 0; blinkCount < 20; ++blinkCount)
		{
			if (blinkCount % 2 == 0)
			{
				SetColor(color);
			}
			else
			{
				SetColor(eColor::LightGray);
			}		
			DisplayCharacterImage(characterName);
			Sleep(30);			
		}

		if (characterName == eCharacterName::Player && color != eColor::Red)
		{
			mCharacters[characterName].UpdateExpression(Character::eExpression::PlayerNormal);
			DisplayCharacterImage(characterName);
		}

		SetCursorType(eCursorType::Visible);
	}

	void GameManager::UseMove(eMove move)
	{
		int16_t stoneTargetPointX = mCharacters[mSelectedMonster].GetStoneTargetPointX();
		int16_t offsetX = 0;
		int16_t offsetY = 0;

		SetCursorType(eCursorType::Invisible);

		switch (move)
		{
		case eMove::ThrowStone:			
			for (int16_t frame = 0; frame < eMoveFrameCount::ThrowStoneFrame; ++frame)
			{
				//3, 10 -> +2, -0 | 30 -> 32, 14 -> 14
				for (int16_t row = 0; row < Image::MAX_ROW; ++row)
				{
					GotoXY(3, 10 + row);
					cout << mThrowStoneFrames[frame].rows[row] << endl;
				}
				if (frame == 6)
				{
					Sleep(400);
				}
				else if (frame < 12)
				{
					Sleep(5);
				}
				else
				{
					GotoXY(32 + offsetX, 14 - offsetY);
					cout << "��";					
					Sleep(20);
					GotoXY(32 + offsetX, 14 - offsetY++);
					cout << "  ";
					offsetX += (mCharacters[mSelectedMonster].GetStoneTargetPointX() - 32) / (14 - mCharacters[mSelectedMonster].GetStoneTargetPointY());
				}
			}

			switch (mSelectedMonster)
			{
			case eCharacterName::GrassHopper:
				mCharacters[mSelectedMonster].UpdateExpression(Character::eExpression::GrassHopperDamaged);
				break;
			case eCharacterName::Billy:
				mCharacters[mSelectedMonster].UpdateExpression(Character::eExpression::BillyGozarani);				
				break;
			case eCharacterName::CamelCriket:
				mCharacters[mSelectedMonster].UpdateExpression(Character::eExpression::CamelCriketDamaged);
				break;
			default:
				break;
			}

			DisplayCharacterImage(mSelectedMonster);

			for (; offsetY <= 14 - mCharacters[mSelectedMonster].GetStoneTargetPointY(); ++offsetY)
			{
				cout << "  ";
				if (mSelectedMonster == eCharacterName::Billy)
				{
					DisplayCharacterImage(mSelectedMonster);
				}
				if (offsetY == 14 - mCharacters[mSelectedMonster].GetStoneTargetPointY())
				{
					GotoXY(mCharacters[mSelectedMonster].GetStoneTargetPointX(), 14 - offsetY);
				}
				else
				{
					GotoXY(32 + offsetX, 14 - offsetY);
				}
				cout << "��";
				Sleep(5);
				if (offsetY == 14 - mCharacters[mSelectedMonster].GetStoneTargetPointY())
				{
					GotoXY(mCharacters[mSelectedMonster].GetStoneTargetPointX(), 14 - offsetY);
				}
				else
				{
					GotoXY(32 + offsetX, 14 - offsetY);
				}

				offsetX += (mCharacters[mSelectedMonster].GetStoneTargetPointX() - 32) / (14 - mCharacters[mSelectedMonster].GetStoneTargetPointY());
			}
			
			GotoXY(stoneTargetPointX, mCharacters[mSelectedMonster].GetStoneTargetPointY());//���� �̹��� �� �Ʒ� y��ǥ 13 �衿3 �顿3 ��
			for (offsetY = 1; offsetY <= 2; ++offsetY)
			{
				cout << "  ";
				if (mSelectedMonster == eCharacterName::Billy)
				{
					DisplayCharacterImage(mSelectedMonster);
				}
				GotoXY(--stoneTargetPointX, mCharacters[mSelectedMonster].GetStoneTargetPointY() - offsetY);
				cout << "��";
				Sleep(30);
				GotoXY(stoneTargetPointX, mCharacters[mSelectedMonster].GetStoneTargetPointY() - offsetY);

			}
			for (offsetY = 0; offsetY <= 1; ++offsetY)
			{
				GotoXY(--stoneTargetPointX, mCharacters[mSelectedMonster].GetStoneTargetPointY() - 2);
				cout << "��";
				Sleep(60);
				GotoXY(stoneTargetPointX, mCharacters[mSelectedMonster].GetStoneTargetPointY() - 2);
				cout << "  ";
				if (mSelectedMonster == eCharacterName::Billy)
				{
					DisplayCharacterImage(mSelectedMonster);
				}
			}
			for (offsetY = 2; offsetY >= 0; --offsetY)
			{
				cout << "  ";
				if (mSelectedMonster == eCharacterName::Billy)
				{
					DisplayCharacterImage(mSelectedMonster);
				}
				GotoXY(--stoneTargetPointX, mCharacters[mSelectedMonster].GetStoneTargetPointY() - offsetY);
				cout << "��";
				Sleep(40);
				GotoXY(stoneTargetPointX, mCharacters[mSelectedMonster].GetStoneTargetPointY() - offsetY);
			}
			for (; mCharacters[mSelectedMonster].GetStoneTargetPointY() - offsetY <= 13; --offsetY)
			{
				cout << "  ";
				if (mCharacters[mSelectedMonster].GetStoneTargetPointY() - offsetY <= 10)
				{
					GotoXY(--stoneTargetPointX, mCharacters[mSelectedMonster].GetStoneTargetPointY() - offsetY);
				}
				else
				{
					GotoXY(stoneTargetPointX, mCharacters[mSelectedMonster].GetStoneTargetPointY() - offsetY);
				}
				cout << "��";
				Sleep(5);
				GotoXY(stoneTargetPointX, mCharacters[mSelectedMonster].GetStoneTargetPointY() - offsetY);
			}
			Sleep(200);
			for (offsetY = 0; offsetY <= 9; ++offsetY)
			{
				GotoXY(stoneTargetPointX, 13);
				cout << "��";
				Sleep(30);
				GotoXY(stoneTargetPointX, 13);
				cout << "  ";
				Sleep(30);
			}
			break;
		case eMove::MiddleFinger:
			Sleep(500);
			for (int16_t frame = 0; frame < eMoveFrameCount::MiddleFingerFrame; ++frame)
			{
				for (int16_t row = 0; row < Image::MAX_ROW; ++row)
				{
					GotoXY(3, 10 + row);
					cout << mMiddleFingerFrames[frame].rows[row];
				}
				if (frame == 6)
				{
					Sleep(500);
				}
				else
				{
					Sleep(10);
				}
			}
			Sleep(1000);
			break;
		case eMove::FatalAttack:
			Sleep(500);

			GotoXY(22, eImageRowCount::FatalAttackRow);
			cout << "��";
			Sleep(15);

			for (int16_t row = eImageRowCount::FatalAttackRow; row >= 1; --row)
			{
				if (row == 3 || row == 1)
				{
					GotoXY(10, row);
					for (int16_t hp = 0; hp < mCharacters[mSelectedMonster].GetHealthPoint(); ++hp)
					{
						cout << " ";
					}
					if (row != 1)
					{
						GotoXY(10, row - 2);
						for (int16_t hp = 0; hp < mCharacters[mSelectedMonster].GetHealthPoint(); ++hp)
						{
							cout << "|";
						}
					}
				}
				GotoXY(24, row);
				cout << mFatalAttackImage[row - 1];				

				if ((row + 1) % 2 == 0)
				{
					Sleep(10);
				}				
			}

			for (int16_t frame = 0; frame < 50; ++frame)
			{
				for (int16_t row = 0; row < eImageRowCount::FatalAttackRow - 1; ++row)
				{
					if (frame % 2 == 0)
					{
						GotoXY(24, row + 1);
					}
					else
					{
						GotoXY(23, row + 1);
					}
					cout << mFatalAttackImage[row];					
				}
				Sleep(10);
			}

			for (int16_t row = 1; row <= eImageRowCount::FatalAttackRow; ++row)
			{
				GotoXY(24, row);
				cout << "                ";
				if (row % 2 == 0)
				{
					Sleep(4);
				}
			}

			GotoXY(22, eImageRowCount::FatalAttackRow);
			cout << "  ";
			Sleep(15);
			break;
		case eMove::Corn:
			SetColor(eColor::Yellow);
			for (int16_t y = 0; y <= 5; ++y)
			{
				for (int16_t row = 0; row < eImageRowCount::CornShotRow; ++row)
				{
					GotoXY(43, 10 - y + row);
					cout << mCornShotImage[row];
				}
				if (y == 0)
				{
					Sleep(300);
				}
				else
				{
					Sleep(30);
				}
				for (int16_t row = 0; row < eImageRowCount::CornShotRow; ++row)
				{
					GotoXY(43, 10 - y + row);
					if (y == 5)
					{
						cout << mCornShotImage[row];
					}
					else
					{
						cout << mCornImageArea[row];
					}
				}
			}

			Sleep(1000);

			for (int16_t twinkle = 0; twinkle <= 60; ++twinkle)
			{
				SetColor(eColor::LightWhite);
				for (int16_t row = 0; row < eImageRowCount::CornShotRow; ++row)
				{
					GotoXY(43, 5 + row);
					cout << mCornShotImage[row];
				}
				Sleep(5);
				SetColor(eColor::Yellow);
				for (int16_t row = 0; row < eImageRowCount::CornShotRow; ++row)
				{
					GotoXY(43, 5 + row);
					if (twinkle == 60)
					{
						cout << mCornImageArea[row];
					}
					else
					{
						cout << mCornShotImage[row];
					}
				}
				Sleep(5);
			}

			for (int16_t x = 0, y = 0; x <= 42; x += 2)
			{
				if ((x / 2) % 2 == 0)
				{
					SetColor(eColor::LightWhite);
				}
				else
				{
					SetColor(eColor::Yellow);
				}
				for (int16_t row = 0; row < eImageRowCount::CornShotRow; ++row)
				{
					GotoXY(43 - x, 5 + y + row);
					cout << mCornShotImage[row];
				}
				Sleep(10);
				for (int16_t row = 0; row < eImageRowCount::CornShotRow; ++row)
				{
					GotoXY(43 - x, 5 + y + row);
					cout << mCornImageArea[row];
				}
				if (x != 0 && x % 4 == 0)
				{
					y++;
				}
			}

			Sleep(300);

			SetColor(eColor::LightGray);
			for (int16_t y = 0; y <= 4; ++y)
			{
				for (int16_t row = 0; row <= 1; ++row)
				{
					GotoXY(9, 11 + row + y);
					cout << mPlayerHairImage[row];
				}
				Sleep(30);
				for (int16_t row = 0; row < eImageRowCount::PlayerHairRow; ++row)
				{
					GotoXY(9, 11 + row + y);
					if (y == 4)
					{
						cout << mPlayerHairImage[row];
					}
					else
					{						
						cout << mPlayerHairImageArea[row];
					}
				}
			}
			break;
		default:
			break;
		}

		SetCursorType(eCursorType::Visible);
	}

	void GameManager::DisplayCharacterDownAnimation(const eCharacterName characterName)
	{
		int16_t x;
		int16_t y;

		SetCursorType(eCursorType::Invisible);

		Sleep(300);

		if (characterName == eCharacterName::Player)
		{
			x = 3;
			y = 9;
		}
		else
		{
			x = 48;
			y = 3;
		}			
		
		for (int16_t lineFeed = 0; lineFeed <= Image::MAX_ROW; ++lineFeed)
		{
			for (int16_t row = 1; row <= Image::MAX_ROW; ++row)
			{
				if (row + lineFeed <= Image::MAX_ROW)
				{
					GotoXY(x, y + row + lineFeed);
					cout << mCharacters[characterName].GetImage().rows[row - 1];
				}
			}
			Sleep(15);
		}

		Sleep(300);

		SetCursorType(eCursorType::Visible);
	}

	void GameManager::ShowRewardEvent(const eCharacterName characterName)
	{
		int16_t previousHp = mCharacters[eCharacterName::Player].GetHealthPoint();
		uint16_t previousAp = mCharacters[eCharacterName::Player].GetAttackPoint();

		char nothing[2][22] = { "  ",
							   "  " };

		_getch();
		mCharacters[eCharacterName::Player].UpdateExpression(Character::eExpression::PlayerNormal);
		DisplayCharacterImage(eCharacterName::Player);
		InitMessageBox();

		switch (characterName)
		{
		case eCharacterName::Stone:
			cout << mCharacters[eCharacterName::Player].GetName() << "��(��) ¯���� ȹ���߽��ϴ�.";
			DisplayItemPickUpAnimation(characterName);
			break;
		case eCharacterName::Flower:
			cout << mCharacters[eCharacterName::Player].GetName() << "��(��) " << mCharacters[characterName].GetName() << "�� ȹ���߽��ϴ�.";
			DisplayItemPickUpAnimation(characterName);
			break;
		case eCharacterName::Tree:
			cout << mCharacters[eCharacterName::Player].GetName() << "��(��) " << mCharacters[characterName].GetName() << "���Ÿ� ȹ���߽��ϴ�.";
			DisplayItemPickUpAnimation(characterName);
			_getch();
			InitMessageBox();
			cout << mCharacters[eCharacterName::Player].GetName() << "��(��) " << mCharacters[characterName].GetName() << "���Ÿ� �Ծ����ϴ�.";
			DisplayItemPickUpAnimation(eCharacterName::Fruit);
			InitMessageBox();
			cout << "!?";
			mCharacters[eCharacterName::Player].UpdateExpression(Character::eExpression::PlayerWhatThe);
			DisplayCharacterImage(eCharacterName::Player);
			_getch();
			InitMessageBox();
			cout << mCharacters[eCharacterName::Player].GetName() << "��(��) ��Ż�� ���� ü���� 3 ���������ϴ�.";
			BlinkCharacterImage(eCharacterName::Player, eColor::Red);
			mCharacters[eCharacterName::Player].UpdateHealthPoint(max(mCharacters[eCharacterName::Player].GetHealthPoint() - 3, 0));
			DisplayUpdatedHealthPoint(eCharacterName::Player, previousHp);
			break;
		case eCharacterName::Ant:
			cout << mCharacters[eCharacterName::Player].GetName() << "��(��) " << mCharacters[characterName].GetName() << "�� �Ծ����ϴ�.";
			DisplayPlayerEatingAnimation(eCharacterName::Ant);
			_getch();
			InitMessageBox();
			cout << mCharacters[eCharacterName::Player].GetName() << "�� ü���� 1 ����߽��ϴ�.";
			BlinkCharacterImage(eCharacterName::Player, eColor::LightGreen);
			mCharacters[eCharacterName::Player].UpdateHealthPoint(mCharacters[eCharacterName::Player].GetHealthPoint() + 1);
			DisplayUpdatedHealthPoint(eCharacterName::Player, previousHp);
			break;
		case eCharacterName::GrassHopper:
			cout << mCharacters[eCharacterName::Player].GetName() << "��(��) " << mCharacters[characterName].GetName() << "�� �Ծ����ϴ�.";
			DisplayPlayerEatingAnimation(eCharacterName::Ant);
			_getch();
			InitMessageBox();			
			cout << mCharacters[eCharacterName::Player].GetName() << "�� ü���� 5 ����߽��ϴ�.";
			BlinkCharacterImage(eCharacterName::Player, eColor::LightGreen);
			mCharacters[eCharacterName::Player].UpdateHealthPoint(mCharacters[eCharacterName::Player].GetHealthPoint() + 5);
			DisplayUpdatedHealthPoint(eCharacterName::Player, previousHp);
			_getch();
			InitMessageBox();
			cout << mCharacters[characterName].GetName() << "�� �Ǹ��� �ܹ��� ���޿��̾��� ������";
			GotoXY(4, 23);
			cout << mCharacters[eCharacterName::Player].GetName() << "�� ���ݷ��� 5 ����߽��ϴ�.";
			BlinkCharacterImage(eCharacterName::Player, eColor::LightBlue);
			mCharacters[eCharacterName::Player].UpdateAttackPoint(mCharacters[eCharacterName::Player].GetAttackPoint() + 5);
			DisplayUpdatedAttackPoint(eCharacterName::Player, previousAp);
			break;
		case eCharacterName::InfinitesimalCalculusTextBook:
			cout << mCharacters[eCharacterName::Player].GetName() << "��(��) " << mCharacters[characterName].GetName() << "�� �Ծ����ϴ�.";
			DisplayPlayerEatingAnimation(eCharacterName::Ant);
			_getch();
			InitMessageBox();
			cout << "������ " << mCharacters[eCharacterName::Player].GetName() << "�� ���м������� ��ȭ�� �������ϴ�.";
			mCharacters[eCharacterName::Player].UpdateExpression(Character::eExpression::PlayerDisappointed);
			DisplayCharacterImage(eCharacterName::Player);
			break;
		case eCharacterName::Grenade:
			cout << mCharacters[eCharacterName::Player].GetName() << "��(��) " << mCharacters[characterName].GetName() << "�� ȹ���߽��ϴ�.";
			DisplayItemPickUpAnimation(characterName);
			break;
		case eCharacterName::Billy:
			cout << mCharacters[eCharacterName::Player].GetName() << "��(��) " << mCharacters[characterName].GetName() << "�� �Ծ����ϴ�.";
			DisplayPlayerEatingAnimation(eCharacterName::Ant);
			_getch();
			InitMessageBox();
			cout << mCharacters[eCharacterName::Player].GetName() << "��(��) '����' ����� �����߽��ϴ�.";
			BlinkCharacterImage(eCharacterName::Player, eColor::LightYellow);
			_getch();
			InitMessageBox();
			cout << mCharacters[eCharacterName::Player].GetName() << "�� ü���� 5 ����߽��ϴ�.";
			BlinkCharacterImage(eCharacterName::Player, eColor::LightGreen);
			mCharacters[eCharacterName::Player].UpdateHealthPoint(mCharacters[eCharacterName::Player].GetHealthPoint() + 5);
			DisplayUpdatedHealthPoint(eCharacterName::Player, previousHp);
			_getch();
			InitMessageBox();
			cout << "Oh My Shoulder ~ ��";
			_getch();
			InitMessageBox();
			cout << mCharacters[eCharacterName::Player].GetName() << "�� ���ݷ��� 10 ����߽��ϴ�.";
			BlinkCharacterImage(eCharacterName::Player, eColor::LightBlue);			
			mCharacters[eCharacterName::Player].UpdateAttackPoint(mCharacters[eCharacterName::Player].GetAttackPoint() + 10);
			DisplayUpdatedAttackPoint(eCharacterName::Player, previousAp);
			break;
		case eCharacterName::CamelCriket:
			cout << mCharacters[eCharacterName::Player].GetName() << "��(��) " << mCharacters[characterName].GetName() << "�� �Ծ����ϴ�.";
			DisplayPlayerEatingAnimation(eCharacterName::Ant);
			_getch();
			InitMessageBox();
			cout << mCharacters[eCharacterName::Player].GetName() << "�� ü���� 15 ����߽��ϴ�.";
			BlinkCharacterImage(eCharacterName::Player, eColor::LightGreen);
			mCharacters[eCharacterName::Player].UpdateHealthPoint(mCharacters[eCharacterName::Player].GetHealthPoint() + 15);
			DisplayUpdatedHealthPoint(eCharacterName::Player, previousHp);			
			_getch();
			InitMessageBox();
			cout << mCharacters[characterName].GetName() << "�� �ſ� �Ǹ��� �ܹ��� ���޿��̾��� ������";
			GotoXY(4, 23);
			cout << mCharacters[eCharacterName::Player].GetName() << "�� ���ݷ��� 5 ����߽��ϴ�.";
			BlinkCharacterImage(eCharacterName::Player, eColor::LightBlue);
			mCharacters[eCharacterName::Player].UpdateAttackPoint(mCharacters[eCharacterName::Player].GetAttackPoint() + 5);
			DisplayUpdatedAttackPoint(eCharacterName::Player, previousAp);
			break;
		case eCharacterName::Gandhi:
			cout << mCharacters[eCharacterName::Player].GetName() << "��(��) �������� ȹ���߽��ϴ�.";
			DisplayItemPickUpAnimation(characterName);
			break;
		default:
			break;
		}				
		_getch();
		InitMessageBox();
	}

	void GameManager::DisplayItemPickUpAnimation(const eCharacterName characterName)
	{
		SetCursorType(eCursorType::Invisible);

		DisplayPlayerArm(-1, "��");

		Sleep(300);

		for (int16_t blink = 0; blink <= 15; ++blink)
		{
			if (characterName <= eCharacterName::Gandhi)
			{
				if (blink % 2 == 0)
				{
					SetColor(eColor::Black);
				}
				else
				{
					if (eCharacterName::Gandhi == characterName)
					{
						SetColor(eColor::Yellow);						
					}
					else
					{
						SetColor(eColor::LightGray);
					}
				}
			}
			switch (characterName)
			{
			case eCharacterName::Stone:
				GotoXY(29, 12);
				printf("��");
				break;
			case eCharacterName::Flower:
			case eCharacterName::FlowerEdible:
				for (int16_t row = 0; row < eImageRowCount::FlowerRow; ++row)
				{
					GotoXY(27, 8 + row);
					cout << mFlowerImage[row];
				}				
				break;
			case eCharacterName::Tree:
				for (int16_t row = 0; row < eImageRowCount::FruitRow; ++row)
				{
					GotoXY(26, 9 + row);
					cout << mFruitImage[row];
				}
				break;
			case eCharacterName::Grenade:
			case eCharacterName::GrenadeEdible:
				for (int16_t row = 0; row < eImageRowCount::GrenadeRow; ++row)
				{
					GotoXY(26, 6 + row);
					cout << mGrenadeImage[row];
				}
				break;
			case eCharacterName::Gandhi:
				for (int16_t row = 0; row < eImageRowCount::CornRow; ++row)
				{
					GotoXY(28, 7 + row);
					cout << mCornImage[row];
				}
				break;
			default:
				break;
			}
			Sleep(30);
		}
		SetColor(eColor::LightGray);

		switch (characterName)
		{
		case eCharacterName::FlowerEdible:
		case eCharacterName::Fruit:
			DisplayPlayerEatingAnimation(characterName);
			break;
		case eCharacterName::GrenadeEdible:
			DisplayPlayerEatingAnimation(characterName);
			Sleep(600);
			break;
		default:
			break;
		}

		SetCursorType(eCursorType::Visible);
	}

	void GameManager::DisplayPlayerArm(int16_t frame, const string& pixel)
	{
		int16_t x;
		int16_t y;

		switch (frame)
		{
		case -1:
			for (x = 22, y = 19; y >= 13; --y)
			{
				GotoXY(x, y);
				if (y == 13)
				{
					cout << pixel << pixel;					
				}
				else
				{
					cout << pixel;
				}
				if (y >= 18)
				{
					x += 2;
				}
				else if (y >= 15)
				{
					x++;
				}
				Sleep(15);
			}
			break;
		case 0:
		case 1:
			for (x = 22, y = 19; y >= 13; --y)
			{
				GotoXY(x, y);
				if (y == 13)
				{
					cout << pixel << pixel;
				}
				else
				{
					cout << pixel;
				}
				if (y >= 18)
				{
					x += 2;
				}
				else if (y >= 15)
				{
					x++;
				}
			}
			/*
					   ���
					   ��� yy == 14
					  ��
					 ��
					��
				  ��
				��(22, 19)
				*/
			break;
		case 2:
			for (x = 22, y = 19; y >= 12; --y)
			{
				GotoXY(x, y);
				cout << pixel;
				if (y >= 18)
				{
					x += 2;
				}
				else if (y >= 15)
				{
					x++;
				}
				else if (y == 13)
				{
					x += 2;
				}
			}
			/*           �� addx == 2
					   ��
					   ��� yy == 14
					  ��
					 ��
					��
				  ��
				��
				*/
			break;
		case 3:
			for (x = 22, y = 19; y >= 12; --y)
			{
				GotoXY(x, y);
				cout << pixel;
				if (y >= 18)
				{
					x += 2;
				}
				else if (y >= 15)
				{
					x++;
				}
				else if (y == 13)
				{
					x++;
				}
			}
			/*          ��
					   ��
					   ��� yy == 14
					  ��
					 ��
					��
				  ��
				��
				*/
			break;
		case 4:
			for (x = 22, y = 19; y >= 12; --y)
			{
				GotoXY(x, y);
				cout << pixel;
				if (y >= 18)
				{
					x += 2;
				}
				else if (y >= 15)
				{
					x++;
				}
			}
			/*         ��
					   ��
					   ��� yy == 14
					  ��
					 ��
					��
				  ��
				��
				*/
			break;
		case 5:
			for (x = 22, y = 19; y >= 12; --y)
			{
				GotoXY(x, y);
				cout << pixel;
				if (y >= 18)
				{
					x += 2;
				}
				else if (y >= 15)
				{
					x++;
				}
				else if (y == 13)
				{
					x--;
				}
			}
			/*        ��
					   ��
					   ��� yy == 14
					  ��
					 ��
					��
				  ��
				��
				*/
			break;
		case 6:
			for (x = 22, y = 19; y >= 12; --y)
			{
				GotoXY(x, y);
				cout << pixel;
				if (y >= 18)
				{
					x += 2;
				}
				else if (y >= 15)
				{
					x++;
				}
				else if (y == 13)
				{
					x -= 2;
				}
			}
			/*       ��
					   ��
					   ��� yy == 14
					  ��
					 ��
					��
				  ��
				��
				*/
			break;
		case 7:
			for (x = 22, y = 19; y >= 12; --y)
			{
				GotoXY(x, y);
				cout << pixel;
				if (y >= 18)
				{
					x += 2;
				}
				else if (y >= 15)
				{
					x++;
				}
				else if (y == 14)
				{
					x--;
				}
				else if (y == 13)
				{
					x -= 2;
				}
			}
			/*      ��
					  ��
					   ��� yy == 14
					  ��
					 ��
					��
				  ��
				��
				*/
			break;
		case 8:
			for (x = 22, y = 19; y >= 13; --y)
			{
				GotoXY(x, y);
				if (y == 13)
				{
					cout << pixel << pixel;
				}
				else
				{
					cout << pixel;
				}
				if (y >= 18)
				{
					x += 2;
				}
				else if (y >= 16)
				{
					x++;
				}
				else if (y == 14)
				{
					x -= 4;
				}
			}
			/*
				  ���
					  ��� yy == 14
					  ��
					 ��
					��
				  ��
				��
				*/
			break;
		case 9:
			for (x = 22, y = 19; y >= 13; --y)
			{
				GotoXY(x, y);
				if (y == 13)
				{
					cout << pixel << pixel;
				}
				else
				{
					cout << pixel;
				}
				if (y >= 18)
				{
					x += 2;
				}
				else if (y >= 16)
				{
					x++;
				}
				else if (y == 15)
				{
					x--;
				}
				else if (y == 14)
				{
					x -= 4;
				}
			}
			/*
				 ���
					 ��� yy == 14
					  ��
					 ��
					��
				  ��
				��
				*/
			break;
		case 10:
			for (x = 22, y = 19; y >= 13; --y)
			{
				GotoXY(x, y);
				if (y == 13)
				{
					cout << pixel << pixel;
				}
				else
				{
					cout << pixel;
				}
				if (y >= 18)
				{
					x += 2;
				}
				else if (y == 17)
				{
					x++;
				}
				else if (y == 15)
				{
					x--;
				}
				else if (y == 14)
				{
					x -= 4;
				}
			}
			/*
				���
					��� yy == 14
					 ��
					 ��
					��
				  ��
				��
				*/
			break;
		case 11:
			for (x = 22, y = 19; y >= 14; --y)
			{
				GotoXY(x, y);
				if (y == 14)
				{
					cout << pixel << pixel;
				}
				else
				{
					cout << pixel;
				}
				if (y >= 18)
				{
					x += 2;
				}
				else if (y == 16)
				{
					x--;
				}
				else if (y == 15)
				{
					x -= 4;
				}
			}
			/*

			   ���� yy == 14
				   ��
					��
					��
				  ��
				��
				*/
			break;
		case 12:
			for (x = 22, y = 19; y >= 14; --y)
			{
				GotoXY(x, y);
				if (y == 14)
				{					
					cout << pixel << pixel;
				}
				else
				{
					cout << pixel;
				}
				if (y == 19)
				{
					x += 2;
				}
				if (y == 18)
				{
					x += 1;
				}
				else if (y == 16)
				{
					x -= 1;
					//x -= 2;
				}
				else if (y == 15)
				{
					x -= 4;
				}
			}
			/*

			  ���� 20, 14
				  �� 24, 15
				   �� 25, 16
				   �� 25, 17
				  �� 24, 18
				�� 22, 19
				*/
			break;
		case 13:
			for (x = 22, y = 19; y >= 14; --y)
			{
				GotoXY(x, y);
				if (y == 14)
				{
					cout << pixel << pixel;
				}
				else
				{
					cout << pixel;
				}
				if (y >= 18)
				{
					x += 2;
				}
				else if (y == 17)
				{
					x -= 1;
				}
				else if (y == 16)
				{
					x -= 2;
				}
				else if (y == 15)
				{
					x -= 4;
				}
			}			
			/*

			 ���� 19, 14
				 �� 23, 15
				   �� 25, 16
					�� 26, 17
				  �� 24, 18
				�� 22, 19
				*/
			break;
		default:
			for (x = 22, y = 19; y >= 15; --y)
			{
				GotoXY(x, y);
				if (y == frame)
				{
					cout << pixel;
				}
				if (y == 19)
				{
					x += 2;
				}
				if (y == 18)
				{
					x += 1;
				}
				else if (y == 16)
				{
					x -= 2;
				}
			}
			break;
		}
		/*

			  �� yy == 14

			   ��
			   ��
			  ��
			��
			*/
		/*

			  �� yy == 14


			   ��
			  ��
			��
			*/
		/*

			  �� yy == 14



			  ��
			��
			*/
		/*

			  �� yy == 14




			��
			*/
		/*

			  �� yy == 14





			*/
	}

	void GameManager::DisplayPlayerEatingAnimation(const eCharacterName characterName)
	{
		int16_t x = 0;
		int16_t y = 0;		
		int16_t offsetX = 0;
		int16_t offsetY = 0;
		int16_t maxRow = 0;	
		string* itemImage = nullptr;

		SetCursorType(eCursorType::Invisible);

		if (characterName != eCharacterName::Ant)
		{
			DisplayPlayerMouthOpenCloseImageFrame(1);

			Sleep(300);

			switch (characterName)
			{
			case eCharacterName::FlowerEdible:
				x = 27;
				y = 8;
				maxRow = eImageRowCount::FlowerRow;
				itemImage = mFlowerImage;
				break;
			case eCharacterName::Fruit:
				x = 26;
				y = 9;
				maxRow = eImageRowCount::FruitRow;
				itemImage = mFruitImage;
				break;
			case eCharacterName::GrenadeEdible:
				x = 26;
				y = 6;
				maxRow = eImageRowCount::GrenadeRow;
				itemImage = mGrenadeImage;
				break;
			default:
				break;
			}

			for (offsetX = 0, offsetY = 0; offsetX <= 12; ++offsetX)	//������ ����
			{
				if (offsetX != 0 && offsetX % 3 == 0)
				{
					offsetY++;
				}	
				if (offsetX == 12 && characterName == eCharacterName::Fruit)
				{
					itemImage[2] = "��0��0��";
				}
				for (int16_t row = 0; row < maxRow; ++row)
				{
					GotoXY(x - offsetX, y + offsetY + row);
					cout << itemImage[row];
				}
				for (int16_t row = 0; row < 4; ++row)
				{
					GotoXY(9, 6 + row);
					cout << mPlayerHeadImage[row];
				}				
				for (int16_t row = 15; row >= 10; --row)
				{
					GotoXY(9, row);
					cout << "�����";
				}
				GotoXY(9, 16);
				cout << "  ����";

				if (offsetX == 12 && (characterName == eCharacterName::FlowerEdible || characterName == eCharacterName::Fruit))
				{
					DisplayPlayerArm(13, "��");
				}
				else
				{
					DisplayPlayerArm(offsetX, "��");
				}				

				Sleep(15);

				if (offsetX < 12)
				{					
					for (int16_t row = 0; row < eImageRowCount::ItemAreaRow; ++row)
					{
						GotoXY(26 - offsetX, 6 + offsetY + row);
						cout << mItemArea[row];
					}
					DisplayPlayerArm(offsetX, "  ");
				}
				for (int16_t row = 0; row < 4; ++row)
				{
					GotoXY(9, 6 + row);
					cout << mPlayerHeadImage[row];
				}
			}

			Sleep(300);

			DisplayPlayerMouthOpenCloseImageFrame(2);
		}

		for (int16_t munch = 1; munch <= 5; ++munch)
		{
			DisplayPlayerMouthOpenCloseImageFrame(3);
			Sleep(80);
			DisplayPlayerMouthOpenCloseImageFrame(4);
		}

		if (characterName != eCharacterName::Ant)
		{
			for (int16_t frame = 15; frame <= 19; ++frame)
			{
				DisplayPlayerArm(frame, "  ");
				Sleep(30);
			}
		}

		for (int16_t row = 0; row < Image::MAX_ROW; ++row)
		{
			GotoXY(3, 10 + row);
			cout << mCharacters[eCharacterName::Player].GetImage().rows[row];
		}

		SetCursorType(eCursorType::Visible);
	}

	void GameManager::DisplayPlayerMouthOpenCloseImageFrame(const int16_t frame)
	{
		switch (frame)
		{
		case 1:
			for (int16_t y = 11; y >= 6; --y)	//9 7 6 �� ũ�� ����
			{
				for (int16_t row = 0; row <= 3; ++row)
				{
					GotoXY(9, y + row);
					cout << mPlayerHeadImage[row];
				}
				GotoXY(9, y + 4);
				if (y == 10)
				{
					cout << "�������  ";
				}
				else if (y == 9 || y == 8)
				{
					for (int16_t row = 15; row >= 12; --row)
					{
						GotoXY(9, row);
						cout << "������    ";
					}
				}
				else if (y == 7 || y == 6)
				{
					for (int16_t row = 15; row >= 10; row--)
					{
						GotoXY(9, row);
						cout << "�����      ";
					}
					if (y == 6)
					{
						GotoXY(9, 16);
						cout << "  ����      ";
						GotoXY(9, 17);
						cout << "��������";
					}
				}
				Sleep(30);
			}
			break;
		case 2:
			GotoXY(9, 16);
			cout << "  �������";
			GotoXY(9, 17);
			cout << "������    ";
			for (int16_t y = 6; y <= 12; ++y)	//9 7 6 ũ�� �� �� �ݱ�
			{
				for (int16_t row = 0; row <= 3; ++row)
				{
					GotoXY(9, y + row);
					cout << mPlayerHeadImage[row];
				}
				Sleep(30);
				if (y < 12)
				{
					for (int16_t row = 0; row <= 3; ++row)
					{
						GotoXY(9, y + row);
						cout << mEraser[row];
					}
				}
			}
			break;
		case 3:
			for (int16_t y = 12; y >= 10; --y)	//9 7 6 �� �۰� ����
			{
				for (int16_t row = 0; row <= 3; ++row)
				{
					GotoXY(9, y + row);
					cout << mPlayerHeadImage[row];
				}
				GotoXY(9, y + 4);
				if (y == 10 || y == 11)
				{
					cout << "������    ";
				}
				Sleep(30);
			}
			break;
		case 4:
			for (int16_t y = 10; y <= 12; ++y)	//9 7 6 �۰� �� �� �ݱ�
			{
				for (int16_t row = 0; row <= 3; ++row)
				{
					GotoXY(9, y + row);
					cout << mPlayerHeadImage[row];
				}
				Sleep(30);
				if (y < 12)
				{
					for (int16_t row = 0; row <= 3; ++row)
					{
						GotoXY(9, y + row);
						cout << mEraser[row];
					}
				}
			}
			break;
		default:
			break;
		}
	}

	void GameManager::DisplayPlayerBodyExplosionAnimation()
	{
		string body[5][4] =
		{
			{
				"        ������            ",
				"      ��������          ",
				"     ���������         ",
				"    ����������        "
			},
			{
				"        ������            ",
				"     ���� �� ����         ",
				"    ���� ��� ����        ",
				"   ����� �� �����       "
			},
			{
				"        ������            ",
				"    ��� �� �� �� ���        ",
				"   ��� �� ��� �� ���       ",
				"  ���� �� �� �� ����      "
			},
			{
				"        ������            ",
				"   �� �� �� �� �� �� ��       ",
				"  �� �� �� ��� �� �� ��      ",
				" ��� �� �� �� �� �� ���     "
			},
			{
				"       �� ���� ��           ",
				"   �� �� �� �� �� �� ��       ",
				"  �� �� �� ��� �� �� ��      ",
				"�� �� �� �� �� �� �� �� ��    "
			}
		};

		SetCursorType(eCursorType::Invisible);

		for (int16_t frame = 0; frame <= 8; ++frame)
		{
			for (int16_t row = 0; row <= 3; ++row)
			{
				GotoXY(1, 17 + row);
				if (frame >= 4)
				{
					cout << body[8 - frame][row];
				}
				else
				{
					cout << body[frame][row];
				}
			}
			if (frame == 4)
			{
				Sleep(100);
			}
			else
			{
				Sleep(15);
			}
		}

		Sleep(500);

		for (int16_t frame = 1; frame <= 60; ++frame)
		{
			if (frame % 2 == 0)
			{
				SetColor(eColor::Black);
			}
			else
			{
				SetColor(eColor::LightRed);
			}
			GotoXY(33, 12);
			cout << "��";
			GotoXY(27, 13);
			cout << "�� ��  ��";
			GotoXY(25, 14);
			cout << "�Ƣ� ��   ��";
			GotoXY(21, 15);
			cout << "�ƢƢƢƢ� �� ��";
			GotoXY(25, 16);
			cout << "�Ƣ�  `   ��";
			GotoXY(27, 17);
			cout << "�� ��  `";
			GotoXY(33, 18);
			cout << "`";
			Sleep(10);
		}

		SetColor(eColor::LightGray);

		SetCursorType(eCursorType::Visible);
	}

	void GameManager::InputName()
	{
		string name;

		while (1)
		{
			GotoXY(20, 8);
			cout << "����� �̸��� �Է��ϰ� ���͸� ��������.\n\n";			
			SetColor(eColor::LightRed);
			GotoXY(1, 15);
			cout << "        ���ѱ��̸��� �Է��ߴٸ� ����ġ�� ���� [��/��] Ű�� ��������.\n";
			cout << "        ���̸��� 10byte �̳��� �Է��ϼ���.";
			SetColor(eColor::LightGray);
			GotoXY(20, 10);
			cout << "          �� ";
			
			cin >> name;			

			if (name.length() > 10)
			{
				system("cls");
				SetColor(eColor::LightRed);
				GotoXY(33, 11);
				cout << "�̸��� �ʹ� ����!";
				SetColor(eColor::LightGray);
				GotoXY(33, 10);
				continue;
			}

			mCharacters[0].SetName(name);
			break;
		}

		GotoXY(33, 10);
		BlinkString(mCharacters[0].GetName(), 33, 10, eColor::LightYellow);

		system("cls");
	}
}