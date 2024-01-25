#include "Shengming.h"

int AVATAR_OBJECT::KarakterDefence(void)
{
	int index01;
	int tWisdom;
	int tISValue;
	int tIUValue;
	int tIUEffectValue;
	AVATAR_INFO* tAvatarInfo = &mUSER[mIndex].mAvatarInfo;
	mDefensePower = 0;
	float v26 = 0.0;


	if (LabirentKontrolu() == 1)//dword_1614C14 > 0 && Bilinmeyen Özellik
	{

		tWisdom = TitleDef() + tAvatarInfo->aUpradgeValue + EkstraOzelOzelliklerCan((mDATA.aLevel1 + mDATA.aLevel2)) + tAvatarInfo->aWisdom;
	}
	else
	{
		tWisdom = TitleDef() + tAvatarInfo->aWisdom + tAvatarInfo->aUpradgeValue;
	}

	for (index01 = 0; index01 < MAX_EQUIP_SLOT_NUM; index01++)
	{
		if (mEquipItem[index01] == NULL)
		{
			continue;
		}
		tWisdom += mEquipItem[index01]->iWisdom;
	}

	if (mDATA.aFashionNumber == 385 || mDATA.aFashionNumber == 386 || mDATA.aFashionNumber == 387)
		tWisdom += 50;
	if (mDATA.aFashionNumber >= 17140 && mDATA.aFashionNumber <= 17145)
		tWisdom += 100;
	if (mDATA.aFashionNumber == 1891 || mDATA.aFashionNumber == 1892 || mDATA.aFashionNumber == 1893)
		tWisdom += 100;
	if (mDATA.aFashionNumber == 7702
		|| mDATA.aFashionNumber == 7703
		|| mDATA.aFashionNumber == 7704
		|| mDATA.aFashionNumber == 7705
		|| mDATA.aFashionNumber == 7706
		|| mDATA.aFashionNumber == 7707)
	{
		tWisdom += 100;
	}
	if (mDATA.aFashionNumber == 18028
		|| mDATA.aFashionNumber == 18029
		|| mDATA.aFashionNumber == 18030
		|| mDATA.aFashionNumber == 18031
		|| mDATA.aFashionNumber == 18032
		|| mDATA.aFashionNumber == 18033)
	{
		tWisdom += 100;
	}
	if (mDATA.aFashionNumber == 18034
		|| mDATA.aFashionNumber == 18035
		|| mDATA.aFashionNumber == 18036
		|| mDATA.aFashionNumber == 18037
		|| mDATA.aFashionNumber == 18038
		|| mDATA.aFashionNumber == 18039
		|| mDATA.aFashionNumber == 18040
		|| mDATA.aFashionNumber == 18041
		|| mDATA.aFashionNumber == 18042)
	{
		tWisdom += 100;
	}

	tWisdom += RefineSystem(4);

	if (mDATA.aAnimalOn == 1)
		tWisdom += BinekAbsorbe();

	mDefensePower += (int)((float)tWisdom * 1.63f);

	if (IsUsedOrnament() == 1)
	{
		mDefensePower += 825;
	}
	else if (IsUsedOrnament() == 2)
	{
		mDefensePower += 550;
	}

	int StatConverterd;//dword_1614C14 
	if (StatConverterd > 0 && LabirentKontrolu() == 1)
	{
		int Level;
		Level = ReturnLevel((mDATA.aLevel1 + mDATA.aLevel2));
		mDefensePower += mLEVEL.ReturnLevelFactorDefensePower(Level);
	}
	else
	{
		mDefensePower += mLEVEL.ReturnLevelFactorDefensePower((mDATA.aLevel1 + mDATA.aLevel2));
	}

	for (index01 = 0; index01 < 13; ++index01)
	{
		if (mEquipItem[index01] == NULL)
		{
			continue;
		}

		mDefensePower += mEquipItem[index01]->iDefensePower;
		if (index01 != 8)
		{

			switch (ItemTypeSetBonusu)
			{
			case 2:
				mDefensePower += (int)((float)(mEquipItem[index01]->iDefensePower * 0.4f));
				break;
			case 3:
			case 12:
			case 17:
				mDefensePower += (int)((float)(mEquipItem[index01]->iDefensePower * 0.6f));
				break;
			case 5:
				mDefensePower += (int)((float)(mEquipItem[index01]->iDefensePower * 1.0f));
				break;
			case 7:
				mDefensePower += (int)((float)(mEquipItem[index01]->iDefensePower * 0.4f));
				break;
			case 9:
				mDefensePower += (int)((float)(mEquipItem[index01]->iDefensePower * 0.6f));
				break;
			case 10:
				mDefensePower += (int)((float)(mEquipItem[index01]->iDefensePower * 1.0f));
				break;
			case 13:
			case 19:
				mDefensePower += (int)((float)(mEquipItem[index01]->iDefensePower * 0.7f));
				break;
			case 15:
			case 20:
				mDefensePower += (int)((float)(mEquipItem[index01]->iDefensePower * 1.1f));
				break;
			case 21:
				mDefensePower += (int)((float)(mEquipItem[index01]->iDefensePower * 0.2f));
				break;
			case 22:
				mDefensePower += (int)((float)(mEquipItem[index01]->iDefensePower * 0.1f));
				break;
			case 30:
				if (index01 == 1 || index01 == 10)
				{
					mDefensePower += (int)((float)(mEquipItem[index01]->iDefensePower * 0.55f));
				}
				if (index01 != 9 && index01 != 11 && index01 != 12)
				{
					if (mItemType[index01] == 1 || mItemType[index01] == 4)
					mDefensePower += (int)((float)(mEquipItem[index01]->iDefensePower * 0.55f));
					else
					mDefensePower += (int)((float)(mEquipItem[index01]->iDefensePower * 1.1f));
				}
			case 50:
				mDefensePower += (int)((float)(mEquipItem[index01]->iDefensePower * 0.55f));
				break;
			default:
				break;
			}
			switch (index01)
			{
			case 1:
					if (mEquipItem[index01]->iSort == 29)
					{
						tISValue = mUTIL.ReturnISValueWithLevelLimit(tAvatarInfo->aLevel1, mUTIL.ReturnISValue(mEquipValue[index01]));
						if (tISValue > 0)
							mDefensePower += 6 * tISValue;
					}
					else if (mEquipItem[index01]->iSetBonus == 2)
					{
						tIUValue = mUTIL.ReturnIUValueWithLevelLimit(tAvatarInfo->aLevel1, mUTIL.ReturnIUValue(mEquipValue[index01]));
						mDefensePower += DefYeniItem(index01, tIUValue, ItemTypeSetBonusu);
						tISValue = mUTIL.ReturnISValueWithLevelLimit(tAvatarInfo->aLevel1, mUTIL.ReturnISValue(mEquipValue[index01]));
						if (tISValue > 0)
							mDefensePower += 6 * tISValue;
					}
					else
					{
						tIUValue = mUTIL.ReturnIUValue(mEquipValue[index01]);
						tIUEffectValue = mUTIL.ReturnIUEffectValue(mEquipItem[index01], 2);
						mDefensePower += (tIUValue * tIUEffectValue);
						tISValue = mUTIL.ReturnISValue(mEquipValue[index01]);
						if (tISValue > 0)
							mDefensePower += 6 * tISValue;
					}
				break;
			case 2:
				if (mItemType[index01] == 1 || mItemType[index01] == 4)
				{
					tISValue = mUTIL.ReturnISValue(mEquipValue[index01]);
					if (tISValue > 0)
					{
						if (tISValue >= 100)
							tISValue -= 100;
						mDefensePower += 1000 * tISValue;
					}
				}
				else if (mEquipItem[index01]->iSetBonus == 2)
				{
					tIUValue = mUTIL.ReturnIUValue(mEquipValue[index01]);
					mDefensePower += DefYeniItem(index01, tIUValue, ItemTypeSetBonusu);
					tISValue = mUTIL.ReturnISValue(mEquipValue[index01]);
					if (tISValue > 0)
					{
						mDefensePower += (int)((float)(mEquipItem[index01]->iDefensePower) * ((float)tISValue * 0.03f));
					}
				}
				else
				{
					tIUValue = mUTIL.ReturnIUValueWithLevelLimit(tAvatarInfo->aLevel1, mUTIL.ReturnIUValue(mEquipValue[index01]));
					tIUEffectValue = mUTIL.ReturnIUEffectValue(mEquipItem[index01], 2);
					mDefensePower += (tIUValue * tIUEffectValue);
					tISValue = mUTIL.ReturnISValueWithLevelLimit(tAvatarInfo->aLevel1, mUTIL.ReturnISValue(mEquipValue[index01]));
					if (tISValue > 0)
					{
						mDefensePower += (int)((float)(mEquipItem[index01]->iDefensePower) * ((float)tISValue * 0.03f));
					}
				}
				break;
			case 3:
				if (mEquipItem[index01]->iSetBonus == 2)
				{
					tIUValue = mUTIL.ReturnIUValueWithLevelLimit(tAvatarInfo->aLevel1, mUTIL.ReturnIUValue(mEquipValue[index01]));
					mDefensePower += DefYeniItem(index01, tIUValue, ItemTypeSetBonusu);
				}
				else
				{
					tIUValue = mUTIL.ReturnIUValueWithLevelLimit(tAvatarInfo->aLevel1, mUTIL.ReturnIUValue(mEquipValue[index01]));
					tIUEffectValue = mUTIL.ReturnIUEffectValue(mEquipItem[index01], 2);
					mDefensePower += (tIUValue * tIUEffectValue);
				}
				break;
			case 5:
				if (mEquipItem[index01]->iSetBonus == 2)
				{
					tIUValue = mUTIL.ReturnIUValueWithLevelLimit(tAvatarInfo->aLevel1, mUTIL.ReturnIUValue(mEquipValue[index01]));
					mDefensePower += DefYeniItem(index01, tIUValue, ItemTypeSetBonusu);
				}
				else
				{
					tIUValue = mUTIL.ReturnIUValueWithLevelLimit(tAvatarInfo->aLevel1, mUTIL.ReturnIUValue(mEquipValue[index01]));
					tIUEffectValue = mUTIL.ReturnIUEffectValue(mEquipItem[index01], 2);
					mDefensePower += (tIUValue * tIUEffectValue);
				}
				break;
			case 9:
			case 11:
			case 12:
				if (mItemType[index01] == 2)
					mDefensePower += DecoItemOzellik(4, mEquipValue[index01]);
				break;
			case 10:
				if (mEquipItem[index01]->iIndex == 204
					|| mEquipItem[index01]->iIndex == 205
					|| mEquipItem[index01]->iIndex == 206
					|| mEquipItem[index01]->iIndex == 216
					|| mEquipItem[index01]->iIndex == 217
					|| mEquipItem[index01]->iIndex == 218
					|| mEquipItem[index01]->iIndex == 2303
					|| mEquipItem[index01]->iIndex == 2304
					|| mEquipItem[index01]->iIndex == 2305)
				{
					v26 = 48.75f;
				}
				else
				{
					v26 = 24.35f;
				}
				if (mItemType[index01] == 2)
				{
					mDefensePower += DecoItemOzellik(4, mEquipValue[index01]);
				}
				else
				{
					tISValue = mUTIL.ReturnISValueWithLevelLimit(tAvatarInfo->aLevel1, mUTIL.ReturnISValue(mEquipValue[index01]));
					if (tISValue > 0)
						mDefensePower += (int)(float)(tISValue * v26);
				}
				break;
			default:
				continue;
			}
		}
	}

	for (index01 = 0; index01 < 13; ++index01)
	{
		if (mEquipItem[index01] == NULL)
		{
			continue;
		}
		if (index01 != 8)
		{
			if (index01 == 1)
			{
				if (mItemType[index01] == 8)
				{
					mDefensePower += YuzdelikOzellikler2(mItemType[index01], index01, mEquipValue[index01], 20);
					if (mDefensePower < 1)
						mDefensePower = 1;
				}
			}
			else if ((!index01 || index01 == 2 || index01 == 3 || index01 == 4 || index01 == 5 || index01 == 7) && mItemType[index01] == 1 || mItemType[index01] == 4)
			{
				mDefensePower += YuzdelikOzellikler2(mItemType[index01], index01, mEquipValue[index01], 20);
				if (mDefensePower < 1)
					mDefensePower = 1;
			}
		}
	}

	switch (mDATA.aAnimalNumber)
	{
	case 1326:
		mDefensePower = (int)((float)mDefensePower * ANIMAL_RATE_ONE_GRADE);
		break;
	case 1327:
		mDefensePower = (int)((float)mDefensePower * ANIMAL_RATE_TWO_GRADE);
		break;
	case 1328:
	case 816:
		mDefensePower = (int)((float)mDefensePower * ANIMAL_RATE_THREE_GRADE);
		break;
	}


	if (LegandaryBinekKontrolu(mDATA.aAnimalNumber) == 30)
	{
		mDefensePower += (int)((float)(LegandaryBinekOzellikleri2(1, 20, mUSER[mIndex].mAvatarInfo.AnimalStat[mUSER[mIndex].mAvatarInfo.aAnimalIndex - 10]) / 100.0 * mDefensePower));
		mDefensePower += (int)((float)(LegandaryBinekOzellikleri2(3, 50, mUSER[mIndex].mAvatarInfo.AnimalStat[mUSER[mIndex].mAvatarInfo.aAnimalIndex - 10])));
	}

	if (mDATA.aGuildBuff[0] == 1 && mDATA.aGuildBuff[1] == 4)
	{
		if (mDefensePower >= 500)
			mDefensePower += 500;
		else
			mDefensePower *= 2;
	}

	if (mUSER[mIndex].mEffectValue[1][0] > 0)
	{
		mDefensePower = (int)((float)(mDefensePower * (mUSER[mIndex].mEffectValue[1][0] + 100)) * 0.01f);
	}

	//Soket Kýsmý
	for (index01 = 0; index01 < 13; ++index01)
	{
		if (mEquipItem[index01] == NULL)
		{
			continue;
		}
		mDefensePower += Socket(2, mEquipSocketValue[index01][0], mEquipSocketValue[index01][1], mEquipSocketValue[index01][2]);
	}

	if (tAvatarInfo->aRank == 1)
		mDefensePower += 1000;

	//Binek Kasma
	if (tAvatarInfo->aAnimalIndex >= 10 && tAvatarInfo->aAnimalIndex < 20)
	{
		//Binek Kýsmý
		if (mUSER[mIndex].mAvatarInfo.AnimalExp[tAvatarInfo->aAnimalIndex - 10] / 1000000 > 0)
		{
			mDefensePower += 100 * BinekStats(6, mUSER[mIndex].mAvatarInfo.AnimalStat[mUSER[mIndex].mAvatarInfo.aAnimalIndex - 10]);
		}
	}

	if (tAvatarInfo->Bottle[tAvatarInfo->BottleIndex] == 879 && tAvatarInfo->BottleTime > 0)
	{
		mDefensePower *= 2;
	}


	if (mGAME.ReturnTribeRole(&mUSER[mIndex].mAvatarInfo.aName[0], mUSER[mIndex].mAvatarInfo.aTribe) == 1)
	{
		mDefensePower += 200;
	}

	if (mGAME.ReturnTribeRole(&mUSER[mIndex].mAvatarInfo.aName[0], mUSER[mIndex].mAvatarInfo.aTribe) == 2)
	{
		mDefensePower += 100;
	}

	mDefensePower += (int)(LedandaryCapeUpradge(tAvatarInfo->aEquip[2][0], mEquipValue[2], 2));



	return mDefensePower;
}

int AVATAR_OBJECT::TitleDef(void)
{
	int result; // eax

	if (mUSER[mIndex].mAvatarInfo.Title <= 300)
	{
		if (mUSER[mIndex].mAvatarInfo.Title <= 200)
		{
			if (mUSER[mIndex].mAvatarInfo.Title <= 100)
			{
				switch (mUSER[mIndex].mAvatarInfo.Title % 100)
				{
				case 1:
					result = 1;
					break;
				case 2:
					result = 3;
					break;
				case 3:
					result = 6;
					break;
				case 4:
					result = 10;
					break;
				case 5:
					result = 15;
					break;
				case 6:
					result = 21;
					break;
				case 7:
					result = 28;
					break;
				case 8:
					result = 36;
					break;
				case 9:
					result = 45;
					break;
				case 10:
					result = 55;
					break;
				case 11:
					result = 67;
					break;
				case 12:
					result = 82;
					break;
				case 13:
					result = 97;
					break;
				case 14:
					result = 112;
					break;
				case 15:
					result = 127;
					break;
				default:
				LABEL_68:
					result = 0;
					break;
				}
			}
			else
			{
				switch (mUSER[mIndex].mAvatarInfo.Title % 100)
				{
				case 1:
					result = 1;
					break;
				case 2:
					result = 2;
					break;
				case 3:
					result = 3;
					break;
				case 4:
					result = 5;
					break;
				case 5:
					result = 7;
					break;
				case 6:
					result = 10;
					break;
				case 7:
					result = 14;
					break;
				case 8:
					result = 18;
					break;
				case 9:
					result = 22;
					break;
				case 10:
					result = 27;
					break;
				case 11:
					result = 33;
					break;
				case 12:
					result = 41;
					break;
				case 13:
					result = 49;
					break;
				case 14:
					result = 57;
					break;
				case 15:
					result = 65;
					break;
				default:
					goto LABEL_68;
				}
			}
		}
		else
		{
			switch (mUSER[mIndex].mAvatarInfo.Title % 100)
			{
			case 1:
				result = 3;
				break;
			case 2:
				result = 8;
				break;
			case 3:
				result = 15;
				break;
			case 4:
				result = 25;
				break;
			case 5:
				result = 37;
				break;
			case 6:
				result = 52;
				break;
			case 7:
				result = 70;
				break;
			case 8:
				result = 90;
				break;
			case 9:
				result = 112;
				break;
			case 10:
				result = 137;
				break;
			case 11:
				result = 167;
				break;
			case 12:
				result = 205;
				break;
			case 13:
				result = 243;
				break;
			case 14:
				result = 281;
				break;
			case 15:
				result = 319;
				break;
			default:
				goto LABEL_68;
			}
		}
	}
	else
	{
		switch (mUSER[mIndex].mAvatarInfo.Title % 100)
		{
		case 1:
			result = 1;
			break;
		case 2:
			result = 2;
			break;
		case 3:
			result = 3;
			break;
		case 4:
			result = 5;
			break;
		case 5:
			result = 7;
			break;
		case 6:
			result = 10;
			break;
		case 7:
			result = 14;
			break;
		case 8:
			result = 18;
			break;
		case 9:
			result = 22;
			break;
		case 10:
			result = 27;
			break;
		case 11:
			result = 33;
			break;
		case 12:
			result = 41;
			break;
		case 13:
			result = 49;
			break;
		case 14:
			result = 57;
			break;
		case 15:
			result = 65;
			break;
		default:
			goto LABEL_68;
		}
	}
	return result;
}
int AVATAR_OBJECT::DefYeniItem(int a1, int a2, int a3)
{
	int result; // eax

	switch (a1)
	{
	case 1:
		switch (a2)
		{
		case 1:
			result = 40;
			break;
		case 2:
			result = 80;
			break;
		case 3:
			result = 120;
			break;
		case 4:
			result = 160;
			break;
		case 5:
			result = 200;
			break;
		case 6:
			result = 240;
			break;
		case 7:
			result = 280;
			break;
		case 8:
			result = 320;
			break;
		case 9:
			result = 360;
			break;
		case 10:
			result = 400;
			break;
		case 11:
			result = 440;
			break;
		case 12:
			result = 520;
			break;
		default:
			result = 0;
			break;
		}
		break;
	case 2:
		switch (a2)
		{
		case 1:
			result = 300;
			break;
		case 2:
			result = 600;
			break;
		case 3:
			result = 900;
			break;
		case 4:
			result = 1200;
			break;
		case 5:
			result = 1500;
			break;
		case 6:
			result = 1800;
			break;
		case 7:
			result = 2100;
			break;
		case 8:
			result = 2400;
			break;
		case 9:
			result = 2700;
			break;
		case 10:
			result = 3000;
			break;
		case 11:
			result = 3300;
			break;
		case 12:
			result = 3600;
			break;
		default:
			result = 0;
			break;
		}
		break;
	case 3:
		switch (a2)
		{
		case 1:
			result = 50;
			break;
		case 2:
			result = 100;
			break;
		case 3:
			result = 150;
			break;
		case 4:
			result = 200;
			break;
		case 5:
			result = 250;
			break;
		case 6:
			result = 300;
			break;
		case 7:
			result = 350;
			break;
		case 8:
			result = 400;
			break;
		case 9:
			result = 450;
			break;
		case 10:
			result = 500;
			break;
		case 11:
			result = 550;
			break;
		case 12:
			result = 600;
			break;
		default:
			result = 0;
			break;
		}
		break;
	case 5:
		switch (a2)
		{
		case 1:
			result = 30;
			break;
		case 2:
			result = 60;
			break;
		case 3:
			result = 90;
			break;
		case 4:
			result = 120;
			break;
		case 5:
			result = 150;
			break;
		case 6:
			result = 180;
			break;
		case 7:
			result = 210;
			break;
		case 8:
			result = 240;
			break;
		case 9:
			result = 270;
			break;
		case 10:
			result = 300;
			break;
		case 11:
			result = 330;
			break;
		case 12:
			result = 360;
			break;
		default:
			result = 0;
			break;
		}
		break;
	default:
		result = 0;
		break;
	}
	return result;
}