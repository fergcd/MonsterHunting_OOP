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
			mImage.rows[3] = "      ¡á¡á¡á¡á¥Ë¡á¡á          ";
			break;
		case eExpression::PlayerDisappointed:
			mImage.rows[3] = "      ¡á¡á¡á¡á¦¬ ¡á¡á         ";
			break;
		case eExpression::PlayerDamaged:
			mImage.rows[3] = "      ¡á¡á¡á¡á£¾¡á¡á          ";
			break;
		case eExpression::PlayerDead:
			mImage.rows[3] = "      ¡á¡á¡á¡á¡¿¡á¡á          ";
			break;
		case eExpression::PlayerFatalKilled:
			mImage.rows[1] = "                              ";
			mImage.rows[2] = "                              ";
			mImage.rows[3] = "                              ";
			mImage.rows[4] = "                  ¡á          ";
			mImage.rows[5] = "        ¡á¡á  ¡á¡á            ";
			mImage.rows[6] = "      ¡á  ¡á¡á¡á¡á¡á          ";
			break;
		case eExpression::PlayerPowerUp:
			mImage.rows[3] = "      ¡á¡á¡á¡á¡Ú¡á¡á          ";
			break;
		case eExpression::PlayerHealthUp:
			mImage.rows[3] = "      ¡á¡á¡á¡á¡Ü¡á¡á          ";
			break;
		case eExpression::PlayerWhatThe:
			mImage.rows[3] = "      ¡á¡á¡á¡á¢Á¡á¡á          ";
			break;
		case eExpression::BillyGozarani:
			mImage.rows[1] = "         Ò¬  §¦§¦§¦           ";
			mImage.rows[2] = "        «Î£©£¨¬¥¢ª£©Ò¬        ";
			mImage.rows[6] = "          £¨¢ª¬¥¢ª£©          ";
			break;
		case eExpression::BillyNormalDead:
			mImage.rows[2] = "        «Î£©£¨¬Õx£© Ò¬        ";
			mImage.rows[6] = "          £¨¡¿¬Õ¡¿£©          ";
			break;
		case eExpression::BillyGozaDead:
			mImage.rows[2] = "        «Î£©£¨¬¥¢³£©Ò¬        ";
			mImage.rows[6] = "          £¨¢³¬¥¢³£©          ";
			break;
		case eExpression::GrassHopperNormal:
			mImage.rows[5] = "   ¡¬¡Ý ¡¬¥Î¥Î¡ó¥Î¡«¥Î¡Ð£ß_   ";
			break;
		case eExpression::GrassHopperDamaged:
			mImage.rows[5] = "   ¡¬£¼ ¡¬¥Î¥Î¡ó¥Î¡«¥Î¡Ð£ß_   ";
			break;
		case eExpression::GrassHopperDead:
			mImage.rows[5] = "   ¡¬¨ä ¡¬¥Î¥Î¡ó¥Î¡«¥Î¡Ð£ß_   ";
			break;
		case eExpression::CamelCriketNormal:
			mImage.rows[7] = "  £¯¦­ ¡Ü¡¬¦­ ¦­ ¦­  /¦­ ¦­   ¤Ó";
			break;
		case eExpression::CamelCriketDamaged:
			mImage.rows[7] = "  £¯¦­ £¼¡¬¦­ ¦­ ¦­  /¦­ ¦­   ¤Ó";
			break;
		case eExpression::CamelCriketDead:
			mImage.rows[7] = "  £¯¦­ ¨ä¡¬¦­ ¦­ ¦­  /¦­ ¦­   ¤Ó";
			break;
		case eExpression::GandhiPissedOff:
			mImage.rows[4] = "      £¨«Ø  «Ø   ¦¢           ";
			mImage.rows[5] = "        ¢Á«Ï¢Á¦¡ ¦¡ ©¬        ";
			mImage.rows[7] = "        ¡¬«¸ ¦­  «Î           ";
			break;
		case eExpression::GandhiSuperSaiyan:
			mImage.rows[1] = "      £¨¡¬«Î¡¬«Î£©«Î£©        ";
			mImage.rows[2] = "     £¨¡¬£¨¡¬ «Î£©«Î£©        ";
			mImage.rows[3] = "     £¨¡¬_ß²__«Î£©«Î£©        ";
			mImage.rows[4] = "      £¨«Îß²«Ø   «Î£©         ";
			mImage.rows[5] = "        ¡Ý«Ï¡Ý¦¡ ¦¡ ©¬        ";
			mImage.rows[6] = "       ¦¼ <..>¦¯   ¡ò         ";
			mImage.rows[7] = "        ¡¬ìÌ ¦­  «Î           ";
			mImage.rows[8] = "   £¨¡¬  ¦¦¦¡    ¦¢     «Î£©  ";
			mImage.rows[9] = "   £¯  ¡¬¦¥     ¦¦ ¦¡ «Î  ¡¬  ";			
			break;
		case eExpression::GandhiDead:
			mImage.rows[4] = "      £¨«Î  «Ø   ¦¢           ";
			mImage.rows[5] = "        ¨ä«Ï¨ä¦¡ ¦¡ ©¬        ";
			mImage.rows[7] = "        ¡¬''\"¦­  «Î           ";
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