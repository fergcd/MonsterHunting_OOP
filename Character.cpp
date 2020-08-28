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
			mImage.rows[3] = "      �����ˡ��          ";
			break;
		case eExpression::PlayerDisappointed:
			mImage.rows[3] = "      ����᦬ ���         ";
			break;
		case eExpression::PlayerDamaged:
			mImage.rows[3] = "      ����᣾���          ";
			break;
		case eExpression::PlayerDead:
			mImage.rows[3] = "      ����᡿���          ";
			break;
		case eExpression::PlayerFatalKilled:
			mImage.rows[1] = "                              ";
			mImage.rows[2] = "                              ";
			mImage.rows[3] = "                              ";
			mImage.rows[4] = "                  ��          ";
			mImage.rows[5] = "        ���  ���            ";
			mImage.rows[6] = "      ��  ������          ";
			break;
		case eExpression::PlayerPowerUp:
			mImage.rows[3] = "      �����ڡ��          ";
			break;
		case eExpression::PlayerHealthUp:
			mImage.rows[3] = "      �����ܡ��          ";
			break;
		case eExpression::PlayerWhatThe:
			mImage.rows[3] = "      ���������          ";
			break;
		case eExpression::BillyGozarani:
			mImage.rows[1] = "         Ҭ  ������           ";
			mImage.rows[2] = "        �Σ���������Ҭ        ";
			mImage.rows[6] = "          ����������          ";
			break;
		case eExpression::BillyNormalDead:
			mImage.rows[2] = "        �Σ�����x�� Ҭ        ";
			mImage.rows[6] = "          �����ա���          ";
			break;
		case eExpression::BillyGozaDead:
			mImage.rows[2] = "        �Σ���������Ҭ        ";
			mImage.rows[6] = "          ����������          ";
			break;
		case eExpression::GrassHopperNormal:
			mImage.rows[5] = "   ���� ���ΥΡ�Ρ��ΡУ�_   ";
			break;
		case eExpression::GrassHopperDamaged:
			mImage.rows[5] = "   ���� ���ΥΡ�Ρ��ΡУ�_   ";
			break;
		case eExpression::GrassHopperDead:
			mImage.rows[5] = "   ���� ���ΥΡ�Ρ��ΡУ�_   ";
			break;
		case eExpression::CamelCriketNormal:
			mImage.rows[7] = "  ���� �ܡ��� �� ��  /�� ��   ��";
			break;
		case eExpression::CamelCriketDamaged:
			mImage.rows[7] = "  ���� ������ �� ��  /�� ��   ��";
			break;
		case eExpression::CamelCriketDead:
			mImage.rows[7] = "  ���� �䡬�� �� ��  /�� ��   ��";
			break;
		case eExpression::GandhiPissedOff:
			mImage.rows[4] = "      ����  ��   ��           ";
			mImage.rows[5] = "        ���Ϣ��� �� ��        ";
			mImage.rows[7] = "        ���� ��  ��           ";
			break;
		case eExpression::GandhiSuperSaiyan:
			mImage.rows[1] = "      �����Ρ��Σ��Σ�        ";
			mImage.rows[2] = "     �������� �Σ��Σ�        ";
			mImage.rows[3] = "     ����_߲__�Σ��Σ�        ";
			mImage.rows[4] = "      ����߲��   �Σ�         ";
			mImage.rows[5] = "        �ݫϡݦ� �� ��        ";
			mImage.rows[6] = "       �� <..>��   ��         ";
			mImage.rows[7] = "        ���� ��  ��           ";
			mImage.rows[8] = "   ����  ����    ��     �Σ�  ";
			mImage.rows[9] = "   ��  ����     �� �� ��  ��  ";			
			break;
		case eExpression::GandhiDead:
			mImage.rows[4] = "      ����  ��   ��           ";
			mImage.rows[5] = "        ��Ϩ䦡 �� ��        ";
			mImage.rows[7] = "        ��''\"��  ��           ";
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