//-------------------------------------------------------------------------------------------------
//HEADER
//-------------------------------------------------------------------------------------------------
#include "Shengming.h"
//-------------------------------------------------------------------------------------------------

int AVATAR_OBJECT::KarakterAtak(void)
{
	int index01;
	int tKi;
	int tStrength;
	int tISValue;
	int tIUValue;
	int tIUEffectValue;
	AVATAR_INFO* tAvatarInfo = &mUSER[mIndex].mAvatarInfo;

	float v34 = 0.0;

	mAttackPower = 0;

	//v71 Atak
	//v75 maan
	// Damage Boost Scrolls
	if (mUSER[mIndex].mAvatarInfo.DamegeBoostScroll > 0)
	{
		mAttackPower *= 1.10f;
	}
	if (LabirentKontrolu() == 1)
	{

		tStrength = tAvatarInfo->aUpradgeValue + TitleAtak() + EkstraOzelOzelliklerAtak((mDATA.aLevel1 + mDATA.aLevel2));
		tKi = tAvatarInfo->aUpradgeValue + TitleMana() + EkstraOzelOzelliklerMana((mDATA.aLevel1 + mDATA.aLevel2));
	}
	else
	{
		tStrength = tAvatarInfo->aUpradgeValue + tAvatarInfo->aStrength + TitleAtak();
		tKi = tAvatarInfo->aUpradgeValue + tAvatarInfo->aKi + TitleMana();
	}

	for (index01 = 0; index01 < MAX_EQUIP_SLOT_NUM; index01++)
	{
		if (mEquipItem[index01] == NULL)
		{
			continue;
		}
		tStrength += mEquipItem[index01]->iStrength;
		tKi += mEquipItem[index01]->iKi;
	}

	if (mDATA.aFashionNumber == 385 || mDATA.aFashionNumber == 386 || mDATA.aFashionNumber == 387)
		tKi += 50;
	if (mDATA.aFashionNumber >= 17140 && mDATA.aFashionNumber <= 17145)
	{
		tStrength += 100;
		tKi += 100;
	}
	if (mDATA.aFashionNumber == 1891 || mDATA.aFashionNumber == 1892 || mDATA.aFashionNumber == 1893)
	{
		tStrength += 100;
		tKi += 100;
	}
	if (mDATA.aFashionNumber == 7702
		|| mDATA.aFashionNumber == 7703
		|| mDATA.aFashionNumber == 7704
		|| mDATA.aFashionNumber == 7705
		|| mDATA.aFashionNumber == 7706
		|| mDATA.aFashionNumber == 7707)
	{
		tStrength += 100;
		tKi += 100;
	}
	if (mDATA.aFashionNumber == 18028
		|| mDATA.aFashionNumber == 18029
		|| mDATA.aFashionNumber == 18030
		|| mDATA.aFashionNumber == 18031
		|| mDATA.aFashionNumber == 18032
		|| mDATA.aFashionNumber == 18033)
	{
		tStrength += 100;
		tKi += 100;
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
		tStrength += 100;
		tKi += 100;
	}
	if (mDATA.aFashionNumber == 2146 || mDATA.aFashionNumber == 2147 || mDATA.aFashionNumber == 2148)
		tStrength += 50;


	tKi += RefineSystem(2);
	tStrength += RefineSystem(3);


	if (mDATA.aAnimalOn == 1)
	{
		tStrength += BinekAbsorbe();
		tKi += BinekAbsorbe();
	}

	if (mEquipItem[7])
	{
		switch (mEquipItem[7]->iSort)
		{
		case 13:
		case 17:
		case 19:
			mAttackPower += (int)((float)tStrength * 2.65f);
			mAttackPower += (int)((float)tKi * 1.43f);
			break;
		case 14:
		case 16:
		case 20:
			mAttackPower += (int)((float)tStrength * 2.80f);
			mAttackPower += (int)((float)tKi * 1.51f);
			break;
		case 15:
		case 18:
		case 21:
			mAttackPower += (int)((float)tStrength * 2.51f);
			mAttackPower += (int)((float)tKi * 1.35f);
			break;
		}
	}
	else
	{
		mAttackPower += (int)((float)tStrength * 1.25f);
		mAttackPower += (int)((float)tKi * 0.67f);
	}



	/** 2009. 11. 18 : ÀåœÄ ÇØ¹æ œÃœºÅÛ (wolf) */
	// ÀåœÄ ÇØ¹æ œÃœºÅÛÀÌ »ç¿ëÁßÀÎ °æ¿ì °ø°Ý·Â Áõ°¡.
	if (IsUsedOrnament() == 1) // ±ÝÀåŒ­ÀÇ °æ¿ì
	{
		mAttackPower += 413;
	}
	else if (IsUsedOrnament() == 2)
	{
		mAttackPower += 275;
	}

	int StatConverterd;//dword_1614C14 
	if (StatConverterd > 0 && LabirentKontrolu() == 1)
	{
		int Level;
		Level = ReturnLevel((mDATA.aLevel1 + mDATA.aLevel2));
		mAttackPower += mLEVEL.ReturnLevelFactorAttackPower(Level);
	}
	else
	{
		mAttackPower += mLEVEL.ReturnLevelFactorAttackPower((mDATA.aLevel1 + mDATA.aLevel2));
	}


	for (index01 = 0; index01 < MAX_EQUIP_SLOT_NUM; ++index01)
	{
		if (mEquipItem[index01] == NULL)
		{
			continue;

		}
		mAttackPower += mEquipItem[index01]->iAttackPower;

		if (index01 != 8)
		{
			switch (ItemTypeSetBonusu)
			{
			case 2:
				mAttackPower += (int)((float)mEquipItem[index01]->iAttackPower * 0.4f);
				break;
			case 4:
			case 12:
			case 17:
				mAttackPower += (int)((float)mEquipItem[index01]->iAttackPower * 0.6f);
				break;
			case 5:
				mAttackPower += (int)((float)mEquipItem[index01]->iAttackPower * 1.0f);
				break;
			case 7:
				mAttackPower += (int)((float)mEquipItem[index01]->iAttackPower * 0.4f);
				break;
			case 9:
				mAttackPower += (int)((float)mEquipItem[index01]->iAttackPower * 0.6f);
				break;
			case 10:
				mAttackPower += (int)((float)mEquipItem[index01]->iAttackPower * 1.0f);
				break;
			case 14:
			case 19:
				mAttackPower += (int)((float)mEquipItem[index01]->iAttackPower * 0.7f);
				break;
			case 15:
			case 20:
				mAttackPower += (int)((float)mEquipItem[index01]->iAttackPower * 1.1f);
				break;
			case 21:
				mAttackPower += (int)((float)mEquipItem[index01]->iAttackPower * 0.2f);
				break;
			case 22:
				mAttackPower += (int)((float)mEquipItem[index01]->iAttackPower * 0.1f);
				break;
			case 30:
				if (index01 == 1 || index01 == 10)
					mAttackPower += (int)((float)mEquipItem[index01]->iAttackPower * 0.55f);
				else if (index01 != 9 && index01 != 11 && index01 != 12)
				{
					if (mItemType[index01] == 1 || mItemType[index01] == 4)
						mAttackPower += (int)((float)mEquipItem[index01]->iAttackPower * 0.55f);
					else
						mAttackPower += (int)((float)mEquipItem[index01]->iAttackPower * 1.1f);
				}
				break;
			case 50:
				mAttackPower += (int)((float)mEquipItem[index01]->iAttackPower * 0.55f);
				break;
			default:
				break;
			}
		}
		if (index01 == 1 && mItemType[index01] != 9 && mEquipItem[index01]->iSort == 29)
		{
			tIUValue = mUTIL.ReturnIUValueWithLevelLimit(tAvatarInfo->aLevel1, mUTIL.ReturnIUValue(mEquipValue[index01]));
			if (tIUValue > 0)
				mAttackPower += 6 * tIUValue;
		}
		if (index01 == 7)
		{
			if (mItemType[index01] == 1 || mItemType[index01] == 4)
			{
				tISValue = mUTIL.ReturnISValueWithLevelLimit(tAvatarInfo->aLevel1, mUTIL.ReturnISValue(mEquipValue[index01]));
				if (tISValue > 0)
				{
					if (tISValue >= 100)
						tISValue -= 100;
					mAttackPower += 1200 * tISValue;
				}
			}
			else if (mEquipItem[index01]->iSetBonus == 2) // 
			{
				mAttackPower += AtakType(index01, mUTIL.ReturnIUValue(mEquipValue[index01]), mEquipItem[1]->iSort);;

				if (mUTIL.ReturnISValueWithLevelLimit(tAvatarInfo->aLevel1, mUTIL.ReturnISValue(mEquipValue[index01])) > 0)
					mAttackPower += (int)((float)mEquipItem[index01]->iAttackPower * (mUTIL.ReturnISValueWithLevelLimit(tAvatarInfo->aLevel1, mUTIL.ReturnISValue(mEquipValue[index01]))) * 0.03f);
			}
			else if (mEquipItem[index01]->iSetBonus == 3)
			{
				mAttackPower += AtakType1(mUTIL.ReturnISValue(mEquipValue[index01]));
			}
			else
			{
				tIUValue = mUTIL.ReturnIUValueWithLevelLimit(tAvatarInfo->aLevel1, mUTIL.ReturnIUValue(mEquipValue[index01]));
				tIUEffectValue = mUTIL.ReturnIUEffectValue(mEquipItem[index01], 1);
				mAttackPower += (tIUValue * tIUEffectValue);
				tISValue = mUTIL.ReturnISValueWithLevelLimit(tAvatarInfo->aLevel1, mUTIL.ReturnISValue(mEquipValue[index01]));
				if (tISValue > 0)
				{
					mAttackPower += (int)((float)(mEquipItem[index01]->iAttackPower + (tIUValue * tIUEffectValue)) * ((float)tISValue * 0.03f));
				}
			}
		}
		if (index01 == 10)
		{

			if (   mEquipItem[index01]->iIndex == 213
				|| mEquipItem[index01]->iIndex == 214
				|| mEquipItem[index01]->iIndex == 215
				|| mEquipItem[index01]->iIndex == 216
				|| mEquipItem[index01]->iIndex == 217
				|| mEquipItem[index01]->iIndex == 218
				|| mEquipItem[index01]->iIndex == 2303
				|| mEquipItem[index01]->iIndex == 2304
				|| mEquipItem[index01]->iIndex == 2305)
			{
				v34 = 23.4;
			}
			else
			{
				v34 = 11.7;
			}
			if (mItemType[index01] == 2)
			{
				mAttackPower += DecoItemOzellik(3, mEquipValue[index01]);
			}
			else
			{
				tISValue = mUTIL.ReturnISValueWithLevelLimit(tAvatarInfo->aLevel1, mUTIL.ReturnISValue(mEquipValue[index01]));
				if (tISValue > 0)
					mAttackPower += (int)((float)(v34 * tISValue));
			}
		}
		if ((index01 == 9 || index01 == 11 || index01 == 12) && mItemType[index01] == 2)
		{
			mAttackPower += DecoItemOzellik(3, mEquipValue[index01]);
		}
			

	}
	//Genious server
	for (index01 = 0; index01 < MAX_EQUIP_SLOT_NUM; ++index01)
	{
		if (mEquipItem[index01] != NULL && index01 != 8)
		{
			int v45;
			v45 = mItemType[index01];
			if (index01 == 1)
			{
				if (v45 == 8)
				{
					mAttackPower += YeniItemAtak(8, index01, mEquipValue[index01], 10);
					if (mAttackPower < 1)
						mAttackPower = 1;
				}
			}
			else if ((!index01 || index01 == 2 || index01 == 3 || index01 == 4 || index01 == 5 || index01 == 7) && (v45 == 1 || v45 == 4))
			{
				mAttackPower += YeniItemAtak(v45, index01, mEquipValue[index01], 10);
				if (mAttackPower < 1)
					mAttackPower = 1;
			}
		}
	}

	if ((!KarakolKontrolu()) || (mSERVER_INFO.mServerNumber >= 319 && mSERVER_INFO.mServerNumber <= 323))
	{
		/* v33 = -1;
		 sub_55A460(dword_1611D1C, dword_1613230, &v33);*/

		int Client = 0;//Cliente avatarinfo2 95 sortlu değeri göndeririyorsun 
		int Client1;//Cliente avatarinfo2 102 sortlu değeri göndeririyorsun 


		if (Client == 1)
		{
			if (Client == tAvatarInfo->aTribe || Client1 == 4)
			{
				if (Client == 10 && tAvatarInfo->StrElx < 10 * Client)
				{
					mAttackPower += 300;
				}
				else if (Client == 20 && tAvatarInfo->StrElx < 10 * Client1)
				{
					mAttackPower += 600;
				}
				else if (Client == 30)
				{
					mAttackPower += 900;
				}
				else
				{
					mAttackPower += 3 * tAvatarInfo->StrElx;
				}
			}
			else
			{
				mAttackPower += 3 * tAvatarInfo->StrElx;
			}
		}
		else
		{
			// mAttackPower += 600;
			mAttackPower += 3 * tAvatarInfo->StrElx;
		}

	}

	if (tAvatarInfo->DamegeBoostScroll > 0 || tAvatarInfo->HeroPill > 0)
	{
		mAttackPower = (int)((float)mAttackPower * ANIMAL_RATE_TWO_GRADE);
	}

	if (tAvatarInfo->FuryState == 1)
	{
		mAttackPower = (int)((float)(FuryAtak(tAvatarInfo->Fury) * mAttackPower));
	}

	switch (mDATA.aAnimalNumber)
	{
	case 1301:
	case 1313:
	case 1317:
		mAttackPower = (int)((float)mAttackPower * ANIMAL_RATE_ONE_GRADE);
		break;
	case 1304:
	case 1314:
	case 1318:
	case 510:
	case 559:
		mAttackPower = (int)((float)mAttackPower * ANIMAL_RATE_TWO_GRADE);
		break;
	case 1307:
	case 1315:
	case 1319:
	case 511:
	case 1329:
	case 814:
	case 818:
	case 820:
		mAttackPower = (int)((float)mAttackPower * ANIMAL_RATE_THREE_GRADE);
		break;
	case 1330:
		mAttackPower = (int)((float)mAttackPower * ANIMAL_RATE_FOUR_GRADE);
		break;
	}

	//YeniBinekler
	if (LegandaryBinekKontrolu(mDATA.aAnimalNumber) == 30)
	{
		mAttackPower += (int)((float)(LegandaryBinekOzellikleri2(1, 10, mUSER[mIndex].mAvatarInfo.AnimalStat[mUSER[mIndex].mAvatarInfo.aAnimalIndex - 10]) / 100.0 * mAttackPower));
		mAttackPower += (int)((float)(LegandaryBinekOzellikleri2(3, 10, mUSER[mIndex].mAvatarInfo.AnimalStat[mUSER[mIndex].mAvatarInfo.aAnimalIndex - 10])));
	}

	if (mUSER[mIndex].mEffectValue[0][0] > 0)
	{
		mAttackPower = (int)((float)(mAttackPower * (mUSER[mIndex].mEffectValue[0][0] + 100)) * 0.01f);
	}


	//Soket Sistemi
	for (index01 = 0; index01 < 13; ++index01)
	{
		if (mEquipItem[index01] == NULL)
		{
			continue;
		}
		mAttackPower += Socket(1, mEquipSocketValue[index01][0], mEquipSocketValue[index01][1], mEquipSocketValue[index01][2]);
	}

	if (tAvatarInfo->aRank == 7)
		mAttackPower += 500;

	//Binek Kasma
	if (tAvatarInfo->aAnimalIndex >= 10 && tAvatarInfo->aAnimalIndex < 20)
	{
		if (mUSER[mIndex].mAvatarInfo.AnimalExp[tAvatarInfo->aAnimalIndex - 10] / 1000000 > 0)
		{
			mAttackPower += 50 * BinekStats(7, mUSER[mIndex].mAvatarInfo.AnimalStat[mUSER[mIndex].mAvatarInfo.aAnimalIndex - 10]);
		}
	}

	if (tAvatarInfo->Bottle[tAvatarInfo->BottleIndex] == 878 && tAvatarInfo->BottleTime > 0)
	{
		mAttackPower += (int)((float)mAttackPower * 0.1);
	}
	if (tAvatarInfo->Bottle[tAvatarInfo->BottleIndex] == 879 && tAvatarInfo->BottleTime > 0)
	{
		mAttackPower -= (int)((float)mAttackPower * 0.2);
	}


	if (mGAME.ReturnTribeRole(&mUSER[mIndex].mAvatarInfo.aName[0], mUSER[mIndex].mAvatarInfo.aTribe) == 1)
	{
		mAttackPower += 200;
	}
	if (mGAME.ReturnTribeRole(&mUSER[mIndex].mAvatarInfo.aName[0], mUSER[mIndex].mAvatarInfo.aTribe) == 2)
	{
		mAttackPower += 100;
	}


	mAttackPower += mPAT.ReturnNewPets(tAvatarInfo->aEquip[8][0], tAvatarInfo->aEquip[8][2], 1);
	mAttackPower += (int)(mPAT.ReturnNewPetCombine(tAvatarInfo->aEquip[8][0], tAvatarInfo->aEquip[8][2], 1));
	mAttackPower += (int)((float)(((YeniItemAtak1(1, 1, tAvatarInfo->aEquip[8][0], tAvatarInfo->aEquip[8][2])) * mAttackPower / 100.0)));
	mAttackPower += (int)(LedandaryCapeUpradge(tAvatarInfo->aEquip[2][0], tAvatarInfo->aEquip[2][2], 1));




	return mAttackPower;
}

int AVATAR_OBJECT::EkstraOzelOzelliklerAtak(int tLevel)
{
	if (tLevel <= 112)
		return 351;
	if (tLevel <= 145)
		return 886;
	if (tLevel > 156)
		return 1;
	return 1411;
}

int AVATAR_OBJECT::TitleAtak(void)
{
	int result;

	if (mUSER[mIndex].mAvatarInfo.Title <= 400)
	{
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
					LABEL_85:
						result = 0;
						break;
					}
				}
				else
				{
					switch (mUSER[mIndex].mAvatarInfo.Title % 100)
					{
					case 1:
						result = 2;
						break;
					case 2:
						result = 6;
						break;
					case 3:
						result = 12;
						break;
					case 4:
						result = 20;
						break;
					case 5:
						result = 30;
						break;
					case 6:
						result = 42;
						break;
					case 7:
						result = 56;
						break;
					case 8:
						result = 72;
						break;
					case 9:
						result = 90;
						break;
					case 10:
						result = 110;
						break;
					case 11:
						result = 134;
						break;
					case 12:
						result = 164;
						break;
					case 13:
						result = 194;
						break;
					case 14:
						result = 224;
						break;
					case 15:
						result = 254;
						break;
					default:
						goto LABEL_85;
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
					goto LABEL_85;
				}
			}
		}
		else
		{
			switch (mUSER[mIndex].mAvatarInfo.Title % 100)
			{
			case 1:
				result = 0;
				break;
			case 2:
				result = 1;
				break;
			case 3:
				result = 3;
				break;
			case 4:
				result = 5;
				break;
			case 5:
				result = 8;
				break;
			case 6:
				result = 11;
				break;
			case 7:
				result = 14;
				break;
			case 8:
				result = 18;
				break;
			case 9:
				result = 23;
				break;
			case 10:
				result = 28;
				break;
			case 11:
				result = 34;
				break;
			case 12:
				result = 41;
				break;
			case 13:
				result = 48;
				break;
			case 14:
				result = 55;
				break;
			case 15:
				result = 62;
				break;
			default:
				goto LABEL_85;
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
			goto LABEL_85;
		}
	}
	return result;
}

int AVATAR_OBJECT::AtakType(int a1, int a2, int a3)
{
	int result;

	if (a1 != 7)
		return 0;
	switch (a2)
	{
	case 1:
		result = 400;
		break;
	case 2:
		result = 800;
		break;
	case 3:
		result = 1200;
		break;
	case 4:
		result = 1600;
		break;
	case 5:
		result = 2000;
		break;
	case 6:
		result = 2400;
		break;
	case 7:
		result = 2800;
		break;
	case 8:
		result = 3200;
		break;
	case 9:
		result = 3600;
		break;
	case 10:
		result = 4000;
		break;
	case 11:
		result = 4400;
		break;
	case 12:
		result = 4800;
		break;
	default:
		result = 0;
		break;
	}
	return result;
}

int AVATAR_OBJECT::AtakType1(int a1)
{
	int result;

	switch (a1)
	{
	case 0:
		result = 0;
		break;
	case 1:
		result = 3500;
		break;
	case 2:
		result = 4500;
		break;
	case 3:
		result = 5500;
		break;
	case 4:
		result = 6500;
		break;
	case 5:
		result = 7500;
		break;
	case 6:
		result = 8000;
		break;
	case 7:
		result = 8500;
		break;
	case 8:
		result = 9000;
		break;
	case 9:
		result = 9500;
		break;
	case 10:
		result = 10000;
		break;
	case 11:
		result = 10500;
		break;
	case 12:
		result = 11000;
		break;
	default:
		result = 0;
		break;
	}
	return result;
}
int AVATAR_OBJECT::YeniPetlerAtak(int a1, int a2, int a3)
{
	int result; // eax
	ITEM_INFO* ItemInfo;
	int v5; // [esp+24h] [ebp-8h]
	int v6; // [esp+28h] [ebp-4h]

	if (a1 == -1 || !a1)
		return 0;
	if (!a2)
		return 0;

	ItemInfo = mITEM.Search(a1);
	if (!ItemInfo)
		return 0.0;
	if (ItemInfo->iSort != 28)
		return 0.0;

	if (a1 == 2253 || a1 == 2254)
		return 0;
	if (a1 == 2261 || a1 == 2262 || a1 == 2300 || a1 == 2301)
		return 0;
	v5 = mUTIL.ReturnISValue(a2);
	if (v5 < 10)
		return 0;
	v6 = v5 % 10;
	if (v5 / 10 != a3)
		return 0;
	switch (a3)
	{
	case 1:
		switch (v6)
		{
		case 0:
			result = 30;
			break;
		case 1:
			result = 60;
			break;
		case 2:
			result = 90;
			break;
		case 3:
			result = 120;
			break;
		case 4:
			result = 150;
			break;
		case 5:
			result = 180;
			break;
		case 6:
			result = 210;
			break;
		case 7:
			result = 240;
			break;
		case 8:
			result = 270;
			break;
		case 9:
			result = 300;
			break;
		default:
			result = 0;
			break;
		}
		break;
	case 2:
		switch (v6)
		{
		case 0:
			result = 200;
			break;
		case 1:
			result = 400;
			break;
		case 2:
			result = 600;
			break;
		case 3:
			result = 800;
			break;
		case 4:
			result = 1000;
			break;
		case 5:
			result = 1200;
			break;
		case 6:
			result = 1400;
			break;
		case 7:
			result = 1600;
			break;
		case 8:
			result = 1800;
			break;
		case 9:
			result = 2000;
			break;
		default:
			result = 0;
			break;
		}
		break;
	case 3:
		switch (v6)
		{
		case 0:
			result = 20;
			break;
		case 1:
			result = 40;
			break;
		case 2:
			result = 60;
			break;
		case 3:
			result = 80;
			break;
		case 4:
			result = 100;
			break;
		case 5:
			result = 120;
			break;
		case 6:
			result = 140;
			break;
		case 7:
			result = 160;
			break;
		case 8:
			result = 180;
			break;
		case 9:
			result = 200;
			break;
		default:
			result = 0;
			break;
		}
		break;
	case 4:
		switch (v6)
		{
		case 0:
			result = 250;
			break;
		case 1:
			result = 500;
			break;
		case 2:
			result = 750;
			break;
		case 3:
			result = 1000;
			break;
		case 4:
			result = 1250;
			break;
		case 5:
			result = 1500;
			break;
		case 6:
			result = 1750;
			break;
		case 7:
			result = 2000;
			break;
		case 8:
			result = 2250;
			break;
		case 9:
			result = 2500;
			break;
		default:
			result = 0;
			break;
		}
		break;
	case 5:
		switch (v6)
		{
		case 0:
			result = 100;
			break;
		case 1:
			result = 200;
			break;
		case 2:
			result = 300;
			break;
		case 3:
			result = 400;
			break;
		case 4:
			result = 500;
			break;
		case 5:
			result = 600;
			break;
		case 6:
			result = 700;
			break;
		case 7:
			result = 800;
			break;
		case 8:
			result = 900;
			break;
		case 9:
			result = 1000;
			break;
		default:
			result = 0;
			break;
		}
		break;
	case 6:
		switch (v6)
		{
		case 0:
			result = 100;
			break;
		case 1:
			result = 200;
			break;
		case 2:
			result = 300;
			break;
		case 3:
			result = 400;
			break;
		case 4:
			result = 500;
			break;
		case 5:
			result = 600;
			break;
		case 6:
			result = 700;
			break;
		case 7:
			result = 800;
			break;
		case 8:
			result = 900;
			break;
		case 9:
			result = 1000;
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

int AVATAR_OBJECT::YeniItemAtak(int a1, int a2, int a3, int a4)
{
	int result; // eax
	int v5; // [esp+5Ch] [ebp-4h]

	v5 = mUTIL.ReturnICValue(a3);
	if (v5 < 1)
		return 0;
	if (v5 > 59)
		return 0;
	if (a1 == 8)
	{
		if (a2 != 1)
			return 0;
		switch (a4)
		{
		case 10:
			switch (v5)
			{
			case 2:
				result = -3600;
				break;
			case 5:
				result = 1200;
				break;
			case 8:
				result = 2400;
				break;
			case 17:
				result = -1200;
				break;
			case 24:
				result = 2400;
				break;
			case 31:
				result = 1200;
				break;
			case 46:
				result = 1200;
				break;
			case 49:
				result = -1200;
				break;
			case 53:
				result = 1200;
				break;
			case 57:
				result = 2400;
				break;
			default:
				result = 0;
				break;
			}
			return result;
		case 20:
			switch (v5)
			{
			case 1:
				result = -3000;
				break;
			case 3:
				result = 2000;
				break;
			case 6:
				result = 1000;
				break;
			case 15:
				result = 1000;
				break;
			case 18:
				result = -1000;
				break;
			case 20:
				result = 3000;
				break;
			case 21:
				result = 1000;
				break;
			case 22:
				result = 1000;
				break;
			case 24:
				result = -1000;
				break;
			case 29:
				result = -2000;
				break;
			case 30:
				result = 1000;
				break;
			case 34:
				result = 3000;
				break;
			case 35:
				result = 1000;
				break;
			case 42:
				result = 1000;
				break;
			case 51:
				result = 1000;
				break;
			case 52:
				result = 2000;
				break;
			case 54:
				result = 1000;
				break;
			case 58:
				result = 1000;
				break;
			default:
				result = 0;
				break;
			}
			return result;
		case 30:
			if (v5 == 10)
				return 1500;
			if (v5 == 41)
				return 1500;
			return 0;
		case 40:
			if (v5 == 9)
				result = 300;
			else
				result = 0;
			return result;
		case 50:
			switch (v5)
			{
			case 7:
				result = -600;
				break;
			case 25:
				result = 200;
				break;
			case 35:
				result = 400;
				break;
			case 36:
				result = 200;
				break;
			case 38:
				result = -200;
				break;
			case 39:
				result = 200;
				break;
			case 44:
				result = 200;
				break;
			case 47:
				result = 200;
				break;
			case 51:
				result = 100;
				break;
			case 55:
				result = 200;
				break;
			default:
				result = 0;
				break;
			}
			return result;
		case 60:
			switch (v5)
			{
			case 21:
				result = 200;
				break;
			case 22:
				result = 200;
				break;
			case 25:
				result = 200;
				break;
			case 37:
				result = 200;
				break;
			case 38:
				result = 200;
				break;
			case 39:
				result = -200;
				break;
			case 45:
				result = 200;
				break;
			case 47:
				result = 200;
				break;
			case 55:
				result = 200;
				break;
			case 58:
				result = 100;
				break;
			default:
				result = 0;
				break;
			}
			return result;
		case 70:
			switch (v5)
			{
			case 11:
				return -3;
			case 28:
				return -3;
			case 40:
				return -3;
			}
			return 0;
		case 80:
			switch (v5)
			{
			case 1:
				result = 2;
				break;
			case 2:
				result = 2;
				break;
			case 3:
				result = -3;
				break;
			case 4:
				result = 2;
				break;
			case 5:
				result = -3;
				break;
			case 6:
				result = 1;
				break;
			case 7:
				result = 2;
				break;
			case 8:
				result = -2;
				break;
			case 9:
				result = 1;
				break;
			case 10:
				result = 1;
				break;
			case 11:
				result = 3;
				break;
			case 12:
				result = 1;
				break;
			case 14:
				result = -3;
				break;
			case 15:
				result = -3;
				break;
			case 16:
				result = 2;
				break;
			case 17:
				result = 2;
				break;
			case 18:
				result = 2;
				break;
			case 19:
				result = -2;
				break;
			case 20:
				result = -2;
				break;
			case 21:
				result = 1;
				break;
			case 23:
				result = 2;
				break;
			case 27:
				result = 1;
				break;
			case 28:
				result = 3;
				break;
			case 29:
				result = 4;
				break;
			case 30:
				result = 2;
				break;
			case 31:
				result = 2;
				break;
			case 32:
				result = 2;
				break;
			case 33:
				result = 3;
				break;
			case 36:
				result = 2;
				break;
			case 37:
				result = 2;
				break;
			case 38:
				result = 3;
				break;
			case 39:
				result = 3;
				break;
			case 40:
				result = 4;
				break;
			case 41:
				result = 4;
				break;
			case 42:
				result = 4;
				break;
			case 43:
				result = 4;
				break;
			case 44:
				result = 4;
				break;
			case 45:
				result = 4;
				break;
			case 46:
				result = 4;
				break;
			case 47:
				result = 4;
				break;
			case 48:
				result = 6;
				break;
			case 49:
				result = 5;
				break;
			case 50:
				result = 5;
				break;
			case 51:
				result = 5;
				break;
			case 52:
				result = 5;
				break;
			case 53:
				result = 5;
				break;
			case 54:
				result = 5;
				break;
			case 55:
				result = 5;
				break;
			case 56:
				result = 5;
				break;
			case 57:
				result = 5;
				break;
			case 58:
				result = 5;
				break;
			case 59:
				result = 6;
				break;
			default:
				result = 0;
				break;
			}
			return result;
		case 90:
			switch (v5)
			{
			case 4:
				result = -3;
				break;
			case 5:
				result = 1;
				break;
			case 9:
				result = -1;
				break;
			case 10:
				result = -1;
				break;
			case 13:
				result = 1;
				break;
			case 14:
				result = 2;
				break;
			case 15:
				result = 1;
				break;
			case 16:
				result = -1;
				break;
			case 19:
				result = 3;
				break;
			case 26:
				result = 2;
				break;
			case 27:
				result = 1;
				break;
			case 32:
				result = 1;
				break;
			case 41:
				result = 1;
				break;
			case 43:
				result = 1;
				break;
			case 48:
				result = -2;
				break;
			case 49:
				result = 1;
				break;
			case 53:
				result = 1;
				break;
			case 54:
				result = 1;
				break;
			case 56:
				result = 2;
				break;
			default:
				result = 0;
				break;
			}
			return result;
		}
		return 0;
	}
	if (a1 != 1 && a1 != 4)
		return 0;
	if (!a2 || a2 == 2 || a2 == 3 || a2 == 4 || a2 == 5)
	{
		switch (a4)
		{
		case 10:
			switch (v5)
			{
			case 2:
				result = -3600;
				break;
			case 8:
				result = -3600;
				break;
			case 17:
				result = -1200;
				break;
			case 24:
				result = -2400;
				break;
			case 49:
				result = -2400;
				break;
			default:
				result = 0;
				break;
			}
			break;
		case 20:
			switch (v5)
			{
			case 1:
				result = -3000;
				break;
			case 3:
				result = 2000;
				break;
			case 5:
				result = 1000;
				break;
			case 6:
				result = 1000;
				break;
			case 8:
				result = 2000;
				break;
			case 9:
				result = -1000;
				break;
			case 10:
				result = -1000;
				break;
			case 13:
				result = 1000;
				break;
			case 15:
				result = 1000;
				break;
			case 16:
				result = -2000;
				break;
			case 18:
				result = -1000;
				break;
			case 19:
				result = 3000;
				break;
			case 20:
				result = 3000;
				break;
			case 21:
				result = 1000;
				break;
			case 22:
				result = 1000;
				break;
			case 24:
				result = 2000;
				break;
			case 26:
				result = 3000;
				break;
			case 27:
				result = 1000;
				break;
			case 29:
				result = -2000;
				break;
			case 30:
				result = 1000;
				break;
			case 31:
				result = 3000;
				break;
			case 34:
				result = 3000;
				break;
			case 42:
				result = 1000;
				break;
			case 48:
				result = -2000;
				break;
			case 49:
				result = 1000;
				break;
			case 51:
				result = 1000;
				break;
			case 52:
				result = 1000;
				break;
			case 53:
				result = 500;
				break;
			case 54:
				result = 1000;
				break;
			case 56:
				result = 1000;
				break;
			default:
				result = 0;
				break;
			}
			break;
		case 30:
			switch (v5)
			{
			case 10:
				result = 1500;
				break;
			case 11:
				result = -4500;
				break;
			case 13:
				result = 1500;
				break;
			case 31:
				result = 1500;
				break;
			case 36:
				result = 1500;
				break;
			case 41:
				result = -1500;
				break;
			case 46:
				result = 1500;
				break;
			case 53:
				result = 1500;
				break;
			default:
				result = 0;
				break;
			}
			break;
		case 40:
			switch (v5)
			{
			case 9:
				result = 300;
				break;
			case 12:
				result = 300;
				break;
			case 15:
				result = 300;
				break;
			case 16:
				result = -300;
				break;
			case 34:
				result = 300;
				break;
			case 37:
				result = 300;
				break;
			case 41:
				result = 600;
				break;
			case 43:
				result = 300;
				break;
			case 54:
				result = 300;
				break;
			default:
				result = 0;
				break;
			}
			break;
		case 50:
			switch (v5)
			{
			case 4:
				result = -600;
				break;
			case 5:
				result = 200;
				break;
			case 25:
				result = 200;
				break;
			case 35:
				result = 200;
				break;
			case 38:
				result = -200;
				break;
			case 39:
				result = 200;
				break;
			case 44:
				result = 200;
				break;
			case 47:
				result = -200;
				break;
			case 51:
				result = 100;
				break;
			case 55:
				result = 100;
				break;
			case 58:
				result = 300;
				break;
			default:
				result = 0;
				break;
			}
			break;
		case 60:
			switch (v5)
			{
			case 7:
				result = -600;
				break;
			case 14:
				result = 400;
				break;
			case 21:
				result = 200;
				break;
			case 22:
				result = 200;
				break;
			case 25:
				result = 200;
				break;
			case 35:
				result = 200;
				break;
			case 38:
				result = 200;
				break;
			case 39:
				result = -200;
				break;
			case 45:
				result = 200;
				break;
			case 47:
				result = -200;
				break;
			case 55:
				result = 100;
				break;
			case 56:
				result = 100;
				break;
			case 57:
				result = 300;
				break;
			default:
				result = 0;
				break;
			}
			break;
		case 70:
			if (v5 == 28)
				return -2;
			if (v5 == 40)
				return -2;
			return 0;
		case 80:
			if (v5 == 19)
				return -2;
			if (v5 == 32)
				return 2;
			return 0;
		case 100:
			switch (v5)
			{
			case 1:
				result = 2000;
				break;
			case 2:
				result = 2000;
				break;
			case 3:
				result = -3000;
				break;
			case 4:
				result = 2000;
				break;
			case 5:
				result = -3000;
				break;
			case 6:
				result = 1000;
				break;
			case 7:
				result = 2000;
				break;
			case 9:
				result = 1000;
				break;
			case 10:
				result = 1000;
				break;
			case 11:
				result = 3000;
				break;
			case 12:
				result = 1000;
				break;
			case 14:
				result = -2000;
				break;
			case 15:
				result = -3000;
				break;
			case 16:
				result = 3000;
				break;
			case 17:
				result = 3000;
				break;
			case 18:
				result = 3000;
				break;
			case 20:
				result = -3000;
				break;
			case 21:
				result = 2000;
				break;
			case 23:
				result = 3000;
				break;
			case 27:
				result = 1000;
				break;
			case 28:
				result = 3000;
				break;
			case 29:
				result = 4000;
				break;
			case 30:
				result = 2000;
				break;
			case 32:
				result = 5000;
				break;
			case 33:
				result = 4000;
				break;
			case 35:
				result = 2000;
				break;
			case 36:
				result = 3000;
				break;
			case 37:
				result = 3000;
				break;
			case 38:
				result = 3000;
				break;
			case 39:
				result = 3000;
				break;
			case 40:
				result = 5000;
				break;
			case 41:
				result = 5000;
				break;
			case 42:
				result = 5000;
				break;
			case 43:
				result = 5000;
				break;
			case 44:
				result = 5000;
				break;
			case 45:
				result = 5000;
				break;
			case 46:
				result = 5000;
				break;
			case 47:
				result = 7000;
				break;
			case 48:
				result = 7000;
				break;
			case 49:
				result = 6000;
				break;
			case 50:
				result = 6000;
				break;
			case 51:
				result = 7000;
				break;
			case 52:
				result = 7000;
				break;
			case 53:
				result = 7000;
				break;
			case 54:
				result = 7000;
				break;
			case 55:
				result = 7000;
				break;
			case 56:
				result = 7000;
				break;
			case 57:
				result = 7000;
				break;
			case 58:
				result = 7000;
				break;
			case 59:
				result = 8000;
				break;
			default:
				result = 0;
				break;
			}
			break;
		default:
			return 0;
		}
	}
	else
	{
		if (a2 != 7)
			return 0;
		switch (a4)
		{
		case 10:
			switch (v5)
			{
			case 1:
				result = 2400;
				break;
			case 2:
				result = 1200;
				break;
			case 3:
				result = -3600;
				break;
			case 4:
				result = 2400;
				break;
			case 5:
				result = 1200;
				break;
			case 6:
				result = -3600;
				break;
			case 8:
				result = -4800;
				break;
			case 13:
				result = -2400;
				break;
			case 16:
				result = 2400;
				break;
			case 17:
				result = 1200;
				break;
			case 18:
				result = -2400;
				break;
			case 19:
				result = 2400;
				break;
			case 20:
				result = 1200;
				break;
			case 21:
				result = -3600;
				break;
			case 23:
				result = -3600;
				break;
			case 28:
				result = -3600;
				break;
			case 29:
				result = -2400;
				break;
			case 30:
				result = 2400;
				break;
			case 32:
				result = 1200;
				break;
			case 33:
				result = -1200;
				break;
			case 34:
				result = 1200;
				break;
			case 35:
				result = 2400;
				break;
			case 36:
				result = 2400;
				break;
			case 37:
				result = -1200;
				break;
			case 38:
				result = 1200;
				break;
			case 39:
				result = 2400;
				break;
			case 42:
				result = 1200;
				break;
			case 45:
				result = -2400;
				break;
			case 46:
				result = -2400;
				break;
			case 47:
				result = -2400;
				break;
			case 48:
				result = -2400;
				break;
			case 49:
				result = 1200;
				break;
			case 52:
				result = 1200;
				break;
			case 55:
				result = 1200;
				break;
			case 57:
				result = 2400;
				break;
			case 58:
				result = 2400;
				break;
			default:
				result = 0;
				break;
			}
			break;
		case 30:
			switch (v5)
			{
			case 1:
				result = -4500;
				break;
			case 6:
				result = 3000;
				break;
			case 7:
				result = 3000;
				break;
			case 10:
				result = -4500;
				break;
			case 11:
				result = -3000;
				break;
			case 12:
				result = -1500;
				break;
			case 14:
				result = -4500;
				break;
			case 15:
				result = 1500;
				break;
			case 16:
				result = -3000;
				break;
			case 21:
				result = 4500;
				break;
			case 22:
				result = 4500;
				break;
			case 25:
				result = -3000;
				break;
			case 26:
				result = -1500;
				break;
			case 27:
				result = -4500;
				break;
			case 30:
				result = -1500;
				break;
			case 32:
				result = -1500;
				break;
			case 36:
				result = 1500;
				break;
			case 38:
				result = 4500;
				break;
			case 40:
				result = 4500;
				break;
			case 41:
				result = 3000;
				break;
			case 43:
				result = 1500;
				break;
			case 46:
				result = 1500;
				break;
			case 49:
				result = -3000;
				break;
			case 51:
				result = 3000;
				break;
			case 52:
				result = 1500;
				break;
			case 53:
				result = 3000;
				break;
			case 56:
				result = 1500;
				break;
			default:
				result = 0;
				break;
			}
			break;
		case 50:
			switch (v5)
			{
			case 2:
				result = -600;
				break;
			case 3:
				result = 600;
				break;
			case 5:
				result = 200;
				break;
			case 7:
				result = -600;
				break;
			case 9:
				result = -600;
				break;
			case 11:
				result = -200;
				break;
			case 12:
				result = -400;
				break;
			case 13:
				result = -600;
				break;
			case 14:
				result = 600;
				break;
			case 15:
				result = 200;
				break;
			case 17:
				result = -400;
				break;
			case 18:
				result = 600;
				break;
			case 20:
				result = 200;
				break;
			case 22:
				result = -600;
				break;
			case 24:
				result = -400;
				break;
			case 26:
				result = -200;
				break;
			case 27:
				result = 200;
				break;
			case 28:
				result = 400;
				break;
			case 32:
				result = 200;
				break;
			case 33:
				result = 200;
				break;
			case 34:
				result = -200;
				break;
			case 35:
				result = 200;
				break;
			case 36:
				result = -400;
				break;
			case 37:
				result = -200;
				break;
			case 39:
				result = -800;
				break;
			case 41:
				result = -200;
				break;
			case 44:
				result = 200;
				break;
			case 45:
				result = 200;
				break;
			case 47:
				result = -400;
				break;
			case 51:
				result = 400;
				break;
			case 54:
				result = 400;
				break;
			case 55:
				result = 200;
				break;
			case 56:
				result = 200;
				break;
			case 58:
				result = 400;
				break;
			default:
				result = 0;
				break;
			}
			break;
		case 70:
			switch (v5)
			{
			case 4:
				result = -6;
				break;
			case 5:
				result = -6;
				break;
			case 8:
				result = 2;
				break;
			case 9:
				result = 1;
				break;
			case 10:
				result = 2;
				break;
			case 11:
				result = 1;
				break;
			case 12:
				result = 1;
				break;
			case 13:
				result = 2;
				break;
			case 15:
				result = -4;
				break;
			case 19:
				result = -4;
				break;
			case 20:
				result = -4;
				break;
			case 23:
				result = 2;
				break;
			case 24:
				result = 1;
				break;
			case 25:
				result = 2;
				break;
			case 26:
				result = 1;
				break;
			case 27:
				result = 1;
				break;
			case 28:
				result = 1;
				break;
			case 29:
				result = 2;
				break;
			case 31:
				result = 1;
				break;
			case 33:
				result = 1;
				break;
			case 34:
				result = 1;
				break;
			case 35:
				result = -2;
				break;
			case 37:
				result = 2;
				break;
			case 38:
				result = -2;
				break;
			case 39:
				result = 1;
				break;
			case 40:
				result = -2;
				break;
			case 41:
				result = 1;
				break;
			case 42:
				result = 1;
				break;
			case 43:
				result = 1;
				break;
			case 44:
				result = 1;
				break;
			case 45:
				result = 2;
				break;
			case 46:
				result = 2;
				break;
			case 47:
				result = 3;
				break;
			case 48:
				result = 3;
				break;
			case 49:
				result = 2;
				break;
			case 50:
				result = 2;
				break;
			case 51:
				result = 1;
				break;
			case 52:
				result = 2;
				break;
			case 53:
				result = 2;
				break;
			case 54:
				result = 2;
				break;
			case 55:
				result = 2;
				break;
			case 56:
				result = 2;
				break;
			case 57:
				result = 2;
				break;
			case 58:
				result = 1;
				break;
			case 59:
				result = 3;
				break;
			default:
				result = 0;
				break;
			}
			break;
		default:
			return 0;
		}
	}
	return result;
}

float AVATAR_OBJECT::YeniItemAtak1(int a1, int a2, int a3, int a4)
{
	double result; // st7
	int v5; // [esp+14h] [ebp-14h]
	int v6; // [esp+18h] [ebp-10h]
	int v7; // [esp+1Ch] [ebp-Ch]
	int v8; // [esp+20h] [ebp-8h]
	int v9; // [esp+24h] [ebp-4h]

	v6 = ItemType(a3);
	if (v6 != 5 && v6 != 6)
		return 0.0;
	switch (a1)
	{
	case 1:
		v9 = mUTIL.ReturnISValue(a4);
		if (a2 == 1)
		{
			switch (v9)
			{
			case 1:
				return 1.0;
			case 2:
				return 2.0;
			case 3:
				return 3.0;
			}
			return 0.0;
		}
		return 0.0;
	case 2:
		v5 = mUTIL.ReturnIUValue(a4);
		if (a2 != 2)
			return 0.0;
		switch (v5)
		{
		case 11:
			result = 1.0;
			break;
		case 12:
			result = 2.0;
			break;
		case 13:
			result = 3.0;
			break;
		default:
			result = 0.0;
			break;
		}
		break;
	case 3:
		v8 = mUTIL.ReturnIBValue(a4);
		if (a2 != 3)
			return 0.0;
		switch (v8)
		{
		case 21:
			result = 1.0;
			break;
		case 22:
			result = 2.0;
			break;
		case 23:
			result = 3.0;
			break;
		default:
			result = 0.0;
			break;
		}
		break;
	case 4:
		v7 = mUTIL.ReturnICValue(a4);
		if (a2 != 3)
			return 0.0;
		switch (v7)
		{
		case 31:
			result = 2.0;
			break;
		case 32:
			result = 4.0;
			break;
		case 33:
			result = 6.0;
			break;
		default:
			result = 0.0;
			break;
		}
		break;
	default:
		return 0.0;
	}
	return result;
}

float AVATAR_OBJECT::FuryAtak(int a1)
{
	double result;

	switch (a1)
	{
	case 1:
		result = 1.05;
		break;
	case 2:
		result = 1.07;
		break;
	case 3:
		result = 1.09;
		break;
	case 4:
		result = 1.11;
		break;
	case 5:
		result = 1.14;
		break;
	case 6:
		result = 1.17;
		break;
	case 7:
		result = 1.2;
		break;
	case 8:
		result = 1.25;
		break;
	case 9:
		result = 1.3;
		break;
	case 10:
		result = 1.4;
		break;
	default:
		result = 1.0;
		break;
	}
	return result;
}