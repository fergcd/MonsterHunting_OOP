#include <cstring>
#include "Character.h"

namespace monsterhunting
{
	Character::Character(string name, const Image& image, const int16_t maxHealthPoint, const int16_t attackPoint, const int16_t stoneTargetPointX, const int16_t stoneTargetPointY)
		: mName(name)
		, mImage(image)
		, mHealthPoint(maxHealthPoint)
		, mMaxHealthPoint(maxHealthPoint)
		, mAttackPoint(attackPoint)
		, mStoneTargetPointX(stoneTargetPointX)
		, mStoneTargetPointY(stoneTargetPointY)
	{
	}

	void Character::UpdateExpression(const eExpression expression)
	{
		switch (expression)
		{
		case eExpression::PlayerNormal:
			mImage.rows[3] = "      ﹥﹥﹥﹥瓦﹥﹥          ";
			break;
		case eExpression::PlayerDisappointed:
			mImage.rows[3] = "      ﹥﹥﹥﹥收 ﹥﹥         ";
			break;
		case eExpression::PlayerDamaged:
			mImage.rows[3] = "      ﹥﹥﹥﹥ˇ﹥﹥          ";
			break;
		case eExpression::PlayerDead:
			mImage.rows[3] = "      ﹥﹥﹥﹥▼﹥﹥          ";
			break;
		case eExpression::PlayerFatalKilled:
			mImage.rows[1] = "                              ";
			mImage.rows[2] = "                              ";
			mImage.rows[3] = "                              ";
			mImage.rows[4] = "                  ﹥          ";
			mImage.rows[5] = "        ﹥﹥  ﹥﹥            ";
			mImage.rows[6] = "      ﹥  ﹥﹥﹥﹥﹥          ";
			break;
		case eExpression::PlayerPowerUp:
			mImage.rows[3] = "      ﹥﹥﹥﹥≠﹥﹥          ";
			break;
		case eExpression::PlayerHealthUp:
			mImage.rows[3] = "      ﹥﹥﹥﹥≒﹥﹥          ";
			break;
		case eExpression::PlayerWhatThe:
			mImage.rows[3] = "      ﹥﹥﹥﹥Ⅸ﹥﹥          ";
			break;
		case eExpression::BillyGozarani:
			mImage.rows[1] = "         珙  圻圻圻           ";
			mImage.rows[2] = "        屋ㄘㄗ洛◥ㄘ珙        ";
			mImage.rows[6] = "          ㄗ◥洛◥ㄘ          ";
			break;
		case eExpression::BillyNormalDead:
			mImage.rows[2] = "        屋ㄘㄗ盈xㄘ 珙        ";
			mImage.rows[6] = "          ㄗ▼盈▼ㄘ          ";
			break;
		case eExpression::BillyGozaDead:
			mImage.rows[2] = "        屋ㄘㄗ洛４ㄘ珙        ";
			mImage.rows[6] = "          ㄗ４洛４ㄘ          ";
			break;
		case eExpression::GrassHopperNormal:
			mImage.rows[5] = "   ′≡ ′用用☉用‵用－�絻   ";
			break;
		case eExpression::GrassHopperDamaged:
			mImage.rows[5] = "   ′ˉ ′用用☉用‵用－�絻   ";
			break;
		case eExpression::GrassHopperDead:
			mImage.rows[5] = "   ′其 ′用用☉用‵用－�絻   ";
			break;
		case eExpression::CamelCriketNormal:
			mImage.rows[7] = "  ㄞ早 ≒′早 早 早  /早 早   太";
			break;
		case eExpression::CamelCriketDamaged:
			mImage.rows[7] = "  ㄞ早 ˉ′早 早 早  /早 早   太";
			break;
		case eExpression::CamelCriketDead:
			mImage.rows[7] = "  ㄞ早 其′早 早 早  /早 早   太";
			break;
		case eExpression::GandhiPissedOff:
			mImage.rows[4] = "      ㄗ建  建   弛           ";
			mImage.rows[5] = "        Ⅸ峙Ⅸ式 式 帕        ";
			mImage.rows[7] = "        ′姜 早  屋           ";
			break;
		case eExpression::GandhiSuperSaiyan:
			mImage.rows[1] = "      ㄗ′屋′屋ㄘ屋ㄘ        ";
			mImage.rows[2] = "     ㄗ′ㄗ′ 屋ㄘ屋ㄘ        ";
			mImage.rows[3] = "     ㄗ′_葀__屋ㄘ屋ㄘ        ";
			mImage.rows[4] = "      ㄗ屋葀建   屋ㄘ         ";
			mImage.rows[5] = "        ≡峙≡式 式 帕        ";
			mImage.rows[6] = "       汝 <..>旬   ♁         ";
			mImage.rows[7] = "        ′壏 早  屋           ";
			mImage.rows[8] = "   ㄗ′  戌式    弛     屋ㄘ  ";
			mImage.rows[9] = "   ㄞ  ′戎     戌 式 屋  ′  ";			
			break;
		case eExpression::GandhiDead:
			mImage.rows[4] = "      ㄗ屋  建   弛           ";
			mImage.rows[5] = "        其峙其式 式 帕        ";
			mImage.rows[7] = "        ′''\"早  屋           ";
			break;
		default:
			break;
		}		
	}

	void Character::Attack(Character& character)
	{
		character.UpdateHealthPoint(max(character.GetHealthPoint() - mAttackPoint, 0));
	}
}