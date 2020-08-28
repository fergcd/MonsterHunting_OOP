#pragma once
#include <cstdint>
#include <string>
#include "Image.h"

using namespace std;

namespace monsterhunting
{
	class Character final
	{
	public:
		enum class eExpression
		{
			PlayerNormal,
			PlayerDisappointed,
			PlayerDamaged,
			PlayerDead,
			PlayerFatalKilled,
			PlayerPowerUp,
			PlayerHealthUp,
			PlayerWhatThe,
			BillyGozarani,
			BillyNormalDead,
			BillyGozaDead,
			GrassHopperNormal,
			GrassHopperDamaged,
			GrassHopperDead,
			CamelCriketNormal,
			CamelCriketDamaged,
			CamelCriketDead,
			GandhiPissedOff,
			GandhiSuperSaiyan,
			GandhiDead
		};
	public:		
		Character(string name, const Image& image, const int16_t maxHealthPoint, const int16_t attackPoint, const int16_t stoneTargetPointX, const int16_t stoneTargetPointY);
		const string& GetName() { return mName; }
		void SetName(const string& name) { mName = name; }
		Image& GetImage() { return mImage; }
		const int16_t GetHealthPoint() { return mHealthPoint; }
		void UpdateHealthPoint(const int16_t healthPoint) { mHealthPoint = healthPoint; }
		const int16_t GetMaxHealthPoint() { return mMaxHealthPoint; }
		void UpdateMaxHealthPoint(const int16_t maxHealthPoint) { mMaxHealthPoint = maxHealthPoint; }
		const uint16_t GetAttackPoint() { return mAttackPoint; }
		void UpdateAttackPoint(const uint16_t attackPoint) { mAttackPoint = attackPoint; }
		const bool IsAlive() { return mHealthPoint > 0; }
		const int16_t GetStoneTargetPointX() { return mStoneTargetPointX; }
		const int16_t GetStoneTargetPointY() { return mStoneTargetPointY; }
		void UpdateExpression(const eExpression expression);
		void Attack(Character& character);
	private:		
		string mName;
		Image mImage;
		int16_t mHealthPoint;
		int16_t mMaxHealthPoint;
		uint16_t mAttackPoint;
		const int16_t mStoneTargetPointX;
		const int16_t mStoneTargetPointY;
	};
}