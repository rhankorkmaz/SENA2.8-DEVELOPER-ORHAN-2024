#include "Shengming.h"

int AVATAR_OBJECT::AttackBlock(void)
{
	int index01;
	AVATAR_INFO* tAvatarInfo = &mUSER[mIndex].mAvatarInfo;
	int tVitality;
	int tKi;
	int tStrength;
	int tWisdom;
	int tISValue;
	int tIUValue;
	int tIUEffectValue;
	mAttackBlock = 0;

	if (LabirentKontrolu() == 1)
	{

		tWisdom = tAvatarInfo->aUpradgeValue + TitleAtak() + 1;
		tVitality = tAvatarInfo->aUpradgeValue + TitleMana() + EkstraOzelOzelliklerCan((mDATA.aLevel1 + mDATA.aLevel2));
	}
	else
	{
		tWisdom = tAvatarInfo->aUpradgeValue + tAvatarInfo->aWisdom + TitleDef();
		tVitality = tAvatarInfo->aUpradgeValue + tAvatarInfo->aVitality + TitleCan();
	}


	for (index01 = 0; index01 < MAX_EQUIP_SLOT_NUM; index01++)
	{
		if (mEquipItem[index01] == NULL)
		{
			continue;
		}
		tWisdom += mEquipItem[index01]->iWisdom;
		tVitality += mEquipItem[index01]->iVitality;
	}

	if (mDATA.aFashionNumber == 385 || mDATA.aFashionNumber == 386 || mDATA.aFashionNumber == 387)
		tWisdom += 50;
	if (mDATA.aFashionNumber >= 17140 && mDATA.aFashionNumber <= 17145)
	{
		tVitality += 100;
		tWisdom += 100;
	}
	if (mDATA.aFashionNumber == 1891 || mDATA.aFashionNumber == 1892 || mDATA.aFashionNumber == 1893)
	{
		tVitality += 100;
		tWisdom += 100;
	}
	if (mDATA.aFashionNumber == 7702
		|| mDATA.aFashionNumber == 7703
		|| mDATA.aFashionNumber == 7704
		|| mDATA.aFashionNumber == 7705
		|| mDATA.aFashionNumber == 7706
		|| mDATA.aFashionNumber == 7707)
	{
		tVitality += 100;
		tWisdom += 100;
	}
	if (mDATA.aFashionNumber == 18028
		|| mDATA.aFashionNumber == 18029
		|| mDATA.aFashionNumber == 18030
		|| mDATA.aFashionNumber == 18031
		|| mDATA.aFashionNumber == 18032
		|| mDATA.aFashionNumber == 18033)
	{
		tVitality += 100;
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
		tVitality += 100;
		tWisdom += 100;
	}

	tWisdom += RefineSystem(4);
	tVitality += RefineSystem(1);

	if (mDATA.aAnimalOn == 1)
	{
		tWisdom += BinekAbsorbe();
		tVitality += BinekAbsorbe();
	}

	mAttackBlock += (int)((float)tWisdom * 1.67f);
	mAttackBlock += (int)((float)tVitality * 0.90f);

	int StatConverterd;//dword_1614C14 
	if (StatConverterd > 0 && LabirentKontrolu() == 1)
	{
		mAttackBlock += mLEVEL.ReturnLevelFactorAttackBlock(ReturnLevel((mDATA.aLevel1 + mDATA.aLevel2)));
	}
	else
	{
		mAttackBlock += mLEVEL.ReturnLevelFactorAttackBlock((mDATA.aLevel1 + mDATA.aLevel2));
	}

	for (index01 = 0; index01 < 13; ++index01)
	{
		if (mEquipItem[index01] == NULL)
		{
			continue;
		}
		mAttackBlock += mEquipItem[index01]->iAttackBlock;
		if (index01 != 8)
		{
			switch (ItemTypeSetBonusu)
			{
			case 3:
				mAttackBlock += (int)((float)(mEquipItem[index01]->iAttackBlock * 0.6f));
				break;
			case 4:
				mAttackBlock += (int)((float)(mEquipItem[index01]->iAttackBlock * 0.6f));
				break;
			case 5:
				mAttackBlock += (int)((float)(mEquipItem[index01]->iAttackBlock * 1.0f));
				break;
			case 8:
				mAttackBlock += (int)((float)(mEquipItem[index01]->iAttackBlock * 0.4));
				break;
			case 9:
				mAttackBlock += (int)((float)(mEquipItem[index01]->iAttackBlock * 0.6f));
				break;
			case 10:
				mAttackBlock += (int)((float)(mEquipItem[index01]->iAttackBlock * 1.0f));
				break;
			case 13:
			case 14:
			case 18:
			case 19:
				mAttackBlock += (int)((float)(mEquipItem[index01]->iAttackBlock * 0.7f));
				break;
			case 15:
			case 20:
				mAttackBlock += (int)((float)(mEquipItem[index01]->iAttackBlock * 1.1f));
				break;
			case 21:
				mAttackBlock += (int)((float)(mEquipItem[index01]->iAttackBlock * 0.2f));
				break;
			case 22:
				mAttackBlock += (int)((float)(mEquipItem[index01]->iAttackBlock * 0.1f));
				break;
			case 30:
				if (index01 == 1 || index01 == 10)
				{
					mAttackBlock += (int)((float)(mEquipItem[index01]->iAttackBlock * 0.5f));
				}
				else if (index01 != 9 && index01 != 11 && index01 != 12)
				{
					if (mItemType[index01] == 1 || mItemType[index01] == 4)
						mAttackBlock += (int)((float)(mEquipItem[index01]->iAttackBlock * 0.55f));
					else
						mAttackBlock += (int)((float)(mEquipItem[index01]->iAttackBlock * 1.1f));
				}
				break;
			case 50:
				mAttackBlock += (int)((float)(mEquipItem[index01]->iAttackBlock * 0.55f));
				break;
			default:
				break;
			}
			switch (index01)
			{
			case 2:
				if (mEquipItem[index01]->iSetBonus == 2)
				{
					mAttackBlock += AtakBlockEkstra(index01, mUTIL.ReturnIUValue(mEquipValue[index01]), ItemTypeSetBonusu);
				}
				else
				{
					tIUValue = mUTIL.ReturnIUValueWithLevelLimit(tAvatarInfo->aLevel1, mUTIL.ReturnIUValue(mEquipValue[index01]));
					tIUEffectValue = mUTIL.ReturnIUEffectValue(mEquipItem[index01], 4);
					mAttackBlock += (tIUValue * tIUEffectValue);
				}
				break;
			case 5:
				if (mItemType[index01] == 1 || mItemType[index01] == 4)
				{
					tISValue = mUTIL.ReturnISValue(mEquipValue[index01]);
					if (tISValue > 0)
					{
						if (tISValue >= 100)
							tISValue -= 100;
						mAttackBlock += 300 * tISValue;
					}
				}
				else if (mEquipItem[index01]->iSetBonus == 2)
				{
					mAttackBlock += AtakBlockEkstra(index01, mUTIL.ReturnIUValue(mEquipValue[index01]), ItemTypeSetBonusu);
					tISValue = mUTIL.ReturnISValueWithLevelLimit(tAvatarInfo->aLevel1, mUTIL.ReturnISValue(mEquipValue[index01]));
					if (tISValue > 0)
						mAttackBlock += (int)((float)(mEquipItem[index01]->iAttackBlock * ((float)tISValue * 0.03f)));
				}
				else
				{
					tIUValue = mUTIL.ReturnIUValueWithLevelLimit(tAvatarInfo->aLevel1, mUTIL.ReturnIUValue(mEquipValue[index01]));
					tIUEffectValue = mUTIL.ReturnIUEffectValue(mEquipItem[index01], 4);
					mAttackBlock += (tIUValue * tIUEffectValue);
					tISValue = mUTIL.ReturnISValueWithLevelLimit(tAvatarInfo->aLevel1, mUTIL.ReturnISValue(mEquipValue[index01]));
					if (tISValue > 0)
					{
						mAttackBlock += (int)((float)(mEquipItem[index01]->iAttackBlock + (tIUValue * tIUEffectValue)) * ((float)tISValue * 0.03f));
					}
				}
				break;
			case 9:
			case 10:
			case 11:
			case 12:
				if (mItemType[index01] == 2)
					mAttackBlock += DecoItemOzellik(6, mEquipValue[index01]);
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
			int v26;
			v26 = mItemType[index01];
			if (index01 == 1)
			{
				if (v26 == 8)
				{
					mAttackBlock += YuzdelikOzellikler2(mItemType[index01], index01, mEquipValue[index01], 40);
					if (mAttackBlock < 1)
						mAttackBlock = 1;
				}
			}
			else if ((!index01 || index01 == 2 || index01 == 3 || index01 == 4 || index01 == 5 || index01 == 7) && (v26 == 1 || v26 == 4))
			{
				mAttackBlock += YuzdelikOzellikler2(v26, index01, mEquipValue[index01], 40);
				if (mAttackBlock < 1)
					mAttackBlock = 1;
			}
		}
	}

	if ((!KarakolKontrolu()) || (mSERVER_INFO.mServerNumber >= 319 && mSERVER_INFO.mServerNumber <= 323))
	{
		/*v19 = -1;
		sub_55A460((unsigned __int16)dword_1611D1C, &unk_1613230, &v19);
		if ((!v19 || v19 == 1 || v19 == 2) && dword_16141F4 == 1)
		{
			v30 += 400;
		}*/
		int Client = 0;//Cliente avatarinfo2 95 sortlu deðeri göndeririyorsun 
		int Client1=0;//Cliente avatarinfo2 102 sortlu deðeri göndeririyorsun 
		if (Client == 1)
		{
			if (Client == tAvatarInfo->aTribe || Client == 4)
			{
				if (Client1 == 10 && tAvatarInfo->AgiElx < 10 * Client1)
				{
					mAttackBlock += 200;
				}
				else if (Client1 == 20 && tAvatarInfo->AgiElx < 10 * Client1)
				{
					mAttackBlock += 400;
				}
				else if (Client1 == 30)
				{
					mAttackBlock += 600;
				}
				else
				{
					mAttackBlock += 2 * tAvatarInfo->AgiElx;
				}
			}
		}
		else
		{
			mAttackBlock += 2 * tAvatarInfo->AgiElx;
		}
	}
	if (mDATA.aGuildBuff[0] == 1 && mDATA.aGuildBuff[1] == 1)
		mAttackBlock = (int)((float)(mAttackBlock * ANIMAL_RATE_ONE_GRADE));


	switch (mDATA.aAnimalNumber)
	{
	case 1323:
	case 1326:
		mAttackBlock = (int)((float)(ANIMAL_RATE_ONE_GRADE * mAttackBlock));
		break;
	case 1324:
	case 1327:
		mAttackBlock = (int)((float)(ANIMAL_RATE_TWO_GRADE * mAttackBlock));
		break;
	case 1325:
	case 1328:
	case 815:
	case 816:
		mAttackBlock = (int)((float)(ANIMAL_RATE_THREE_GRADE * mAttackBlock));
		break;
	}
	//Yeni Binekler
	if (LegandaryBinekKontrolu(mDATA.aAnimalNumber) == 30)
	{
		mAttackBlock += (int)((float)(LegandaryBinekOzellikleri2(3, 20, mUSER[mIndex].mAvatarInfo.AnimalStat[mUSER[mIndex].mAvatarInfo.aAnimalIndex - 10])));
	}

	if (mUSER[mIndex].mEffectValue[3][0] > 0)
	{
		mAttackBlock = (int)((float)(mAttackBlock * (mUSER[mIndex].mEffectValue[3][0] + 100)) * 0.01f);
	}
	if (mUSER[mIndex].mEffectValue[18][0] > 0)
	{
		mAttackBlock = (int)((float)(mAttackBlock * (mUSER[mIndex].mEffectValue[18][0] + 100)) * 0.01f);
	}

	for (index01 = 0; index01 < 13; ++index01)
	{
		if (mEquipItem[index01] == NULL)
		{
			continue;
		}
		mAttackBlock += Socket(6, mEquipSocketValue[index01][0], mEquipSocketValue[index01][1], mEquipSocketValue[index01][2]);
	}

	if (tAvatarInfo->aRank == 4)
		mAttackBlock += 1000;

	//Binek Kasma
	if (tAvatarInfo->aAnimalIndex >= 10 && tAvatarInfo->aAnimalIndex < 20)
	{
		//Binek Kýsmý
		//Binek Kýsmý
		if (mUSER[mIndex].mAvatarInfo.AnimalExp[tAvatarInfo->aAnimalIndex - 10] / 1000000 > 0)
		{
			mAttackBlock += 100 * BinekStats(2, mUSER[mIndex].mAvatarInfo.AnimalStat[mUSER[mIndex].mAvatarInfo.aAnimalIndex - 10]);
		}
	}
	mAttackBlock += mPAT.ReturnNewPets(tAvatarInfo->aEquip[8][0], tAvatarInfo->aEquip[8][2], 3);


	return mAttackBlock;
}
int AVATAR_OBJECT::AtakBlockEkstra(int a1, int a2, int a3)
{
	int result; // eax

	if (a1 == 2)
	{
		switch (a2)
		{
		case 1:
			result = 20;
			break;
		case 2:
			result = 40;
			break;
		case 3:
			result = 60;
			break;
		case 4:
			result = 80;
			break;
		case 5:
			result = 100;
			break;
		case 6:
			result = 120;
			break;
		case 7:
			result = 140;
			break;
		case 8:
			result = 160;
			break;
		case 9:
			result = 180;
			break;
		case 10:
			result = 200;
			break;
		case 11:
			result = 220;
			break;
		case 12:
			result = 240;
			break;
		default:
			result = 0;
			break;
		}
	}
	else if (a1 == 5)
	{
		switch (a2)
		{
		case 1:
			result = 80;
			break;
		case 2:
			result = 160;
			break;
		case 3:
			result = 240;
			break;
		case 4:
			result = 320;
			break;
		case 5:
			result = 400;
			break;
		case 6:
			result = 480;
			break;
		case 7:
			result = 560;
			break;
		case 8:
			result = 640;
			break;
		case 9:
			result = 720;
			break;
		case 10:
			result = 800;
			break;
		case 11:
			result = 880;
			break;
		case 12:
			result = 960;
			break;
		default:
			result = 0;
			break;
		}
	}
	else
	{
		result = 0;
	}
	return result;
}
int AVATAR_OBJECT::ElementPower(void)
{
	int index01;
	AVATAR_INFO* tAvatarInfo = &mUSER[mIndex].mAvatarInfo;
	int tVitality;
	int tKi;
	int tStrength;
	int tWisdom;
	int tISValue;
	int tIUValue;
	int tIUEffectValue;
	float v13;
	mElementAttackPower = 0;

	for (index01 = 0; index01 < 13; ++index01)
	{
		if (mEquipItem[index01] == NULL)
		{
			continue;
		}
		mElementAttackPower += mEquipItem[index01]->iElementAttackPower;
		if (index01 != 8)
		{
			switch (ItemTypeSetBonusu)
			{
			case 1:
				mElementAttackPower += (int)((float)mEquipItem[index01]->iElementAttackPower * 0.4f);
				break;
			case 5:
				mElementAttackPower += (int)((float)mEquipItem[index01]->iElementAttackPower * 1.0f);
				break;
			case 6:
				mElementAttackPower += (int)((float)mEquipItem[index01]->iElementAttackPower * 0.4f);
				break;
			case 10:
				mElementAttackPower += (int)((float)mEquipItem[index01]->iElementAttackPower * 1.0f);
				break;
			case 11:
			case 16:
				mElementAttackPower += (int)((float)mEquipItem[index01]->iElementAttackPower * 0.6f);
				break;
			case 15:
			case 20:
				mElementAttackPower += (int)((float)mEquipItem[index01]->iElementAttackPower * 1.1f);
				break;
			case 21:
				mElementAttackPower += (int)((float)mEquipItem[index01]->iElementAttackPower * 0.2f);
				break;
			case 22:
				mElementAttackPower += (int)((float)mEquipItem[index01]->iElementAttackPower * 0.1f);
				break;
			case 30:
				if (index01 == 1 || index01 == 10)
				{
					mElementAttackPower += (int)((float)mEquipItem[index01]->iElementAttackPower * 0.55f);
				}
				else if (index01 != 9 && index01 != 11 && index01 != 12)
				{
					if (mItemType[index01] == 1 || mItemType[index01] == 4)
						mElementAttackPower += (int)((float)mEquipItem[index01]->iElementAttackPower * 0.55f);
					else
						mElementAttackPower += (int)((float)mEquipItem[index01]->iElementAttackPower * 1.1f);
				}
				break;
			case 50:
				mElementAttackPower += (int)((float)mEquipItem[index01]->iElementAttackPower * 0.55f);
				break;
			default:
				break;
			}
			if (index01 == 4)
			{
				if (mItemType[index01] == 1 || mItemType[index01] == 4)
				{
					tISValue = mUTIL.ReturnISValue(mEquipValue[index01]);
					if (tISValue > 0)
					{
						if (tISValue > 100)
							tISValue -= 100;
						mElementAttackPower += 200 * tISValue;
					}
				}
				else if (mEquipItem[index01]->iSetBonus == 2)
				{
					mElementAttackPower += ElementPower1(index01, mUTIL.ReturnIUValue(mEquipValue[index01]), ItemTypeSetBonusu);
				}
				else
				{
					tIUValue = mUTIL.ReturnIUValueWithLevelLimit(tAvatarInfo->aLevel1, mUTIL.ReturnIUValue(mEquipValue[index01]));
					tIUEffectValue = mUTIL.ReturnIUEffectValue(mEquipItem[index01], 5);
					mElementAttackPower += (tIUValue * tIUEffectValue);
				}
				
			}
			else if (index01 == 10)
			{
				if (mUSER[mIndex].mAvatarInfo.aEquip[10][0] == 210
					|| mUSER[mIndex].mAvatarInfo.aEquip[10][0] == 211
					|| mUSER[mIndex].mAvatarInfo.aEquip[10][0] == 212
					|| mUSER[mIndex].mAvatarInfo.aEquip[10][0] == 216
					|| mUSER[mIndex].mAvatarInfo.aEquip[10][0] == 217
					|| mUSER[mIndex].mAvatarInfo.aEquip[10][0] == 218
					|| mUSER[mIndex].mAvatarInfo.aEquip[10][0] == 2303
					|| mUSER[mIndex].mAvatarInfo.aEquip[10][0] == 2304
					|| mUSER[mIndex].mAvatarInfo.aEquip[10][0] == 2305)
				{
					v13 = 7.8;
				}
				else
				{
					v13 = 3.9;
				}
				if (mItemType[index01] != 2)
				{
					tISValue = mUTIL.ReturnISValueWithLevelLimit(tAvatarInfo->aLevel1, mUTIL.ReturnISValue(mEquipValue[index01]));
					if (tISValue > 0)
						mElementAttackPower += (int)((float)tISValue * v13);
				}
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
					mElementAttackPower += YuzdelikOzellikler2(mItemType[index01], index01, mEquipValue[index01], 50);
					if (mElementAttackPower < 1)
						mElementAttackPower = 1;
				}
			}
			else if ((!index01 || index01 == 2 || index01 == 3 || index01 == 4 || index01 == 5 || index01 == 7) && (mItemType[index01] == 1 || mItemType[index01] == 4))
			{
				mElementAttackPower += YuzdelikOzellikler2(mItemType[index01], index01, mEquipValue[index01], 50);
				if (mElementAttackPower < 1)
					mElementAttackPower = 1;
			}
		}
	}
	int StatConverterd;//dword_1614C14 
	if (StatConverterd > 0 && LabirentKontrolu() == 1)
	{
		int Level;
		Level = ReturnLevel((mDATA.aLevel1 + mDATA.aLevel2));
		mElementAttackPower += mLEVEL.ReturnLevelFactorElementAttack(Level);
	}
	else
	{
		mElementAttackPower += mLEVEL.ReturnLevelFactorElementAttack((mDATA.aLevel1 + mDATA.aLevel2));
	}

	if ((!KarakolKontrolu()) || (mSERVER_INFO.mServerNumber >= 319 && mSERVER_INFO.mServerNumber <= 323))
	{
		if (mSERVER_INFO.mServerNumber != 84)
		{
			mElementAttackPower += 10 * (tAvatarInfo->YeniElx / 1000);
		}
	}

	switch (mDATA.aAnimalNumber)
	{
	case 1301:
	case 1303:
	case 1320:
		mElementAttackPower = (int)((float)(ANIMAL_RATE_ONE_GRADE * mElementAttackPower));
		break;
	case 1304:
	case 1306:
	case 1321:
	case 559:
		mElementAttackPower = (int)((float)(ANIMAL_RATE_TWO_GRADE * mElementAttackPower));
		break;
	case 1307:
	case 1309:
	case 1322:
	case 814:
	case 817:
	case 821:
		mElementAttackPower = (int)((float)(ANIMAL_RATE_THREE_GRADE * mElementAttackPower));
		break;
	}
	//Yeni Binekler
	if (LegandaryBinekKontrolu(mDATA.aAnimalNumber) == 30)
	{
		mElementAttackPower += (int)((float)(LegandaryBinekOzellikleri(1, mDATA.aAnimalNumber) / 100.0 * mElementAttackPower));
		mElementAttackPower += (int)((float)(LegandaryBinekOzellikleri2(1, 70, mUSER[mIndex].mAvatarInfo.AnimalStat[mUSER[mIndex].mAvatarInfo.aAnimalIndex - 10]) / 100.0 * mElementAttackPower));
		mElementAttackPower += (int)((float)(LegandaryBinekOzellikleri2(3, 30, mUSER[mIndex].mAvatarInfo.AnimalStat[mUSER[mIndex].mAvatarInfo.aAnimalIndex - 10])));
	}

	if (mUSER[mIndex].mEffectValue[4][0] > 0)
	{
		mElementAttackPower = (int)((float)(mElementAttackPower * (mUSER[mIndex].mEffectValue[4][0] + 100)) * 0.01f);
	}

	if (tAvatarInfo->Title > 0)
		mElementAttackPower = (int)((float)(mElementAttackPower * (float)(tAvatarInfo->Title % 100 + 100)) * 0.01f);

	if (ItemTypeSetBonusu == 19)
		mElementAttackPower += 500;
	//Socket sistemi
	for (index01 = 0; index01 < 13; ++index01)
	{
		if (mEquipItem[index01] == NULL)
		{
			continue;
		}
		mElementAttackPower += Socket(7, mEquipSocketValue[index01][0], mEquipSocketValue[index01][1], mEquipSocketValue[index01][2]);
	}
	if (tAvatarInfo->aRank == 3)
		mElementAttackPower += 1000;

	//Binek Kasma sistemi
	if (tAvatarInfo->aAnimalIndex >= 10 && tAvatarInfo->aAnimalIndex < 20)
	{
		//Binek Kýsmý
		if (mUSER[mIndex].mAvatarInfo.AnimalExp[tAvatarInfo->aAnimalIndex - 10] / 1000000 > 0)
		{
			mElementAttackPower += 50 * BinekStats(1, mUSER[mIndex].mAvatarInfo.AnimalStat[tAvatarInfo->aAnimalIndex - 10]);
		}
	}

	mElementAttackPower += mPAT.ReturnNewPets(tAvatarInfo->aEquip[8][0], tAvatarInfo->aEquip[8][2], 5);

	mElementAttackPower += (int)(mPAT.ReturnNewPetCombine(tAvatarInfo->aEquip[8][0], tAvatarInfo->aEquip[8][2], 3));

	if (tAvatarInfo->Bottle[tAvatarInfo->BottleIndex] == 882 && tAvatarInfo->BottleTime > 0)
	{
		mElementAttackPower += (int)((float)mElementAttackPower * 0.3);
	}

	mElementAttackPower += (int)(LedandaryCapeUpradge(tAvatarInfo->aEquip[2][0], tAvatarInfo->aEquip[2][2], 5));


	return mElementAttackPower;
}
int AVATAR_OBJECT::ElementPower1(int a1, int a2, int a3)
{
	int result; // eax

	if (a1 != 4)
		return 0;
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
		result = 480;
		break;
	default:
		result = 0;
		break;
	}
	return result;
}
int AVATAR_OBJECT::ElementDef(void)
{
	int index01;
	AVATAR_INFO* tAvatarInfo = &mUSER[mIndex].mAvatarInfo;
	int tVitality;
	int tKi;
	int tStrength;
	int tWisdom;
	int tISValue;
	int tIUValue;
	int tIUEffectValue;
	float v12;
	mElementDefensePower = 0;
	for (index01 = 0; index01 < 13; ++index01)
	{
		if (mEquipItem[index01] == NULL)
		{
			continue;
		}
		mElementDefensePower += mEquipItem[index01]->iElementDefensePower;
		if (index01 != 8)
		{
			switch (ItemTypeSetBonusu)
			{
			case 1:
				mElementDefensePower += (int)((float)mEquipItem[index01]->iElementDefensePower * 0.4f);
				break;
			case 5:
				mElementDefensePower += (int)((float)mEquipItem[index01]->iElementDefensePower * 1.0f);
				break;
			case 6:
				mElementDefensePower += (int)((float)mEquipItem[index01]->iElementDefensePower * 0.4f);
				break;
			case 10:
				mElementDefensePower += (int)((float)mEquipItem[index01]->iElementDefensePower * 1.0f);
				break;
			case 11:
			case 16:
				mElementDefensePower += (int)((float)mEquipItem[index01]->iElementDefensePower * 0.6f);
				break;
			case 15:
			case 20:
				mElementDefensePower += (int)((float)mEquipItem[index01]->iElementDefensePower * 1.1f);
				break;
			case 21:
				mElementDefensePower += (int)((float)mEquipItem[index01]->iElementDefensePower * 0.2f);
				break;
			case 22:
				mElementDefensePower += (int)((float)mEquipItem[index01]->iElementDefensePower * 0.1f);
				break;
			case 30:
				if (index01 == 1 || index01 == 10)
				{
					mElementDefensePower += (int)((float)mEquipItem[index01]->iElementDefensePower * 0.55f);
				}
				else if (index01 != 9 && index01 != 11 && index01 != 12)
				{
					if (mItemType[index01] == 1 || mItemType[index01] == 4)
						mElementDefensePower += (int)((float)mEquipItem[index01]->iElementDefensePower * 0.55f);
					else
						mElementDefensePower += (int)((float)mEquipItem[index01]->iElementDefensePower * 1.1f);
				}
				break;
			case 50:
				mElementDefensePower += (int)((float)mEquipItem[index01]->iElementDefensePower * 0.55f);
				break;
			default:
				break;
			}
			switch (index01)
			{
			case 0:
				if (mItemType[index01] != 1 && mItemType[index01] != 4)
				{
					if (mEquipItem[index01]->iSetBonus == 2)
					{
						mElementDefensePower += ElementalDef(index01, mUTIL.ReturnIUValue(mEquipValue[index01]), ItemTypeSetBonusu);
					}
					else
					{
						tIUValue = mUTIL.ReturnIUValueWithLevelLimit(tAvatarInfo->aLevel1, mUTIL.ReturnIUValue(mEquipValue[index01]));
						tIUEffectValue = mUTIL.ReturnIUEffectValue(mEquipItem[index01], 6);
						mElementDefensePower += (tIUValue * tIUEffectValue);
					}
				}
				break;
			case 4:
				if (mItemType[index01] == 1 || mItemType[index01] == 4)
				{
					tISValue = mUTIL.ReturnISValue(mEquipValue[index01]);
					if (tISValue > 0)
					{
						if (tISValue > 100)
							tISValue -= 100;
						mElementDefensePower += 200 * tISValue;
					}
				}
				break;
			case 9:
			case 11:
			case 12:
				if (mItemType[index01] == 2)
					mElementDefensePower += DecoItemOzellik(8, mEquipValue[index01]);
				break;
			case 10:
				if (mEquipItem[index01]->iIndex == 207
					|| mEquipItem[index01]->iIndex == 208
					|| mEquipItem[index01]->iIndex == 209
					|| mEquipItem[index01]->iIndex == 216
					|| mEquipItem[index01]->iIndex == 217
					|| mEquipItem[index01]->iIndex == 218
					|| mEquipItem[index01]->iIndex == 2303
					|| mEquipItem[index01]->iIndex == 2304
					|| mEquipItem[index01]->iIndex == 2305)
				{
					v12 = 7.8;
				}
				else
				{
					v12 = 3.9;
				}
				if (mItemType[index01] == 2)
				{
					mElementDefensePower += DecoItemOzellik(8, mEquipValue[index01]);
				}
				else
				{
					tISValue = mUTIL.ReturnISValue(mEquipValue[index01]);
					if (tISValue > 0)
						mElementDefensePower += (int)((float)tISValue * v12);
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
					mElementDefensePower += YuzdelikOzellikler2(mItemType[index01], index01, mEquipValue[index01], 60);
					if (mElementDefensePower < 1)
						mElementDefensePower = 1;
				}
			}
			else if ((!index01 || index01 == 2 || index01 == 3 || index01 == 4 || index01 == 5 || index01 == 7) && (mItemType[index01] == 1 || mItemType[index01] == 4))
			{
				mElementDefensePower += YuzdelikOzellikler2(mItemType[index01], index01, mEquipValue[index01], 60);
				if (mElementDefensePower < 1)
					mElementDefensePower = 1;
			}
		}
	}

	if ((!KarakolKontrolu()) || (mSERVER_INFO.mServerNumber >= 319 && mSERVER_INFO.mServerNumber <= 323))
	{
		if (mSERVER_INFO.mServerNumber != 84)
		{
			mElementDefensePower += 10 * (tAvatarInfo->YeniElx % 1000);
		}
	}

	switch (mDATA.aAnimalNumber)
	{
	case 1302:
	case 1317:
		mElementDefensePower = (int)((float)(ANIMAL_RATE_ONE_GRADE * mElementDefensePower));
		break;
	case 1305:
	case 1318:
		mElementDefensePower = (int)((float)(ANIMAL_RATE_TWO_GRADE * mElementDefensePower));
		break;
	case 1308:
	case 1319:
	case 818:
	case 819:
		mElementDefensePower = (int)((float)(ANIMAL_RATE_THREE_GRADE * mElementDefensePower));
		break;
	}
	//Yeni Binekler
	if (LegandaryBinekKontrolu(mDATA.aAnimalNumber) == 30)
	{
		//Binek Stat Kýsýmlar legandry       
		mElementDefensePower += (int)((float)(LegandaryBinekOzellikleri(2, mDATA.aAnimalNumber) / 100.0 * mElementDefensePower));
		mElementDefensePower += (int)((float)(LegandaryBinekOzellikleri2(1, 80, mUSER[mIndex].mAvatarInfo.AnimalStat[mUSER[mIndex].mAvatarInfo.aAnimalIndex - 10]) / 100.0 * mElementDefensePower));
		mElementDefensePower += (int)((float)(LegandaryBinekOzellikleri2(3, 60, mUSER[mIndex].mAvatarInfo.AnimalStat[mUSER[mIndex].mAvatarInfo.aAnimalIndex - 10])));
	}

	if (mUSER[mIndex].mEffectValue[5][0] > 0)
	{
		mElementDefensePower = (int)((float)(mElementDefensePower * (mUSER[mIndex].mEffectValue[5][0] + 100)) * 0.01f);
	}

	if (tAvatarInfo->Title > 0)
		mElementDefensePower = (int)((float)(mElementDefensePower * (float)(tAvatarInfo->Title % 100 + 100)) * 0.01f);

	//Socket Sitemi
	for (index01 = 0; index01 < 13; ++index01)
	{
		if (mEquipItem[index01] == NULL)
		{
			continue;
		}
		mElementDefensePower += Socket(8, mEquipSocketValue[index01][0], mEquipSocketValue[index01][1], mEquipSocketValue[index01][2]);
	}

	if (tAvatarInfo->aRank == 2)
		mElementDefensePower += 1000;

	//Binek Kasma
	if (tAvatarInfo->aAnimalIndex >= 10 && tAvatarInfo->aAnimalIndex < 20)
	{
		//Binek Kýsmý
		if (mUSER[mIndex].mAvatarInfo.AnimalExp[tAvatarInfo->aAnimalIndex - 10] / 1000000 > 0)
		{
			mElementDefensePower += 50 * BinekStats(0, mUSER[mIndex].mAvatarInfo.AnimalStat[tAvatarInfo->aAnimalIndex - 10]);
		}
	}

	mElementDefensePower += mPAT.ReturnNewPets(tAvatarInfo->aEquip[8][0], tAvatarInfo->aEquip[8][2], 6);
	mElementDefensePower += (int)(mPAT.ReturnNewPetCombine(tAvatarInfo->aEquip[8][0], tAvatarInfo->aEquip[8][2], 4));

	if (tAvatarInfo->Bottle[tAvatarInfo->BottleIndex] == 882 && tAvatarInfo->BottleTime > 0)
	{
		mElementDefensePower -= (int)((float)mElementDefensePower * 0.5);
	}

	mElementDefensePower += (int)(LedandaryCapeUpradge(tAvatarInfo->aEquip[2][0], tAvatarInfo->aEquip[2][2], 6));

	return mElementDefensePower;
}
int AVATAR_OBJECT::ElementalDef(int a1, int a2, int a3)
{
	int result; // eax

	if (a1)
		return 0;
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
		result = 480;
		break;
	default:
		result = 0;
		break;
	}
	return result;
}
int AVATAR_OBJECT::Criticial(void)
{
	int index01;
	AVATAR_INFO* tAvatarInfo = &mUSER[mIndex].mAvatarInfo;
	int tVitality;
	int tKi;
	int tStrength;
	int tWisdom;
	int tISValue;
	int tIUValue;
	int tIUEffectValue;
	mCritical = 2;


	for (index01 = 0; index01 < 13; ++index01)
	{
		if (mEquipItem[index01] == NULL)
		{
			continue;
		}
		mCritical += mEquipItem[index01]->iCritical;
		if (index01 != 8)
		{
			switch (ItemTypeSetBonusu)
			{
			case 5:
			case 9:
			case 10:
			case 21:
				mCritical += (int)((float)mEquipItem[index01]->iCritical * 0.05f);
				break;
			case 22:
				mCritical += (int)((float)mEquipItem[index01]->iCritical * 0.04f);
				break;
			default:
				break;
			}
			if (index01 == 4 && mItemType[index01] != 1 && mItemType[index01] != 4)
			{
				tISValue = mUTIL.ReturnISValueWithLevelLimit(tAvatarInfo->aLevel1, mUTIL.ReturnISValue(mEquipValue[index01]));
				if (tISValue > 0)
					mCritical += tISValue / 4;
			}
		}

	}

	for (index01 = 0; index01 < 13; ++index01)
	{
		if (mEquipItem[index01] == NULL)
		{
			continue;
		}
		int v21;
		v21 = mItemType[index01];
		if (index01 != 8)
		{
			if (index01 == 1)
			{
				if (v21 == 8)
				{
					mCritical += YuzdelikOzellikler2(v21, index01, mEquipValue[index01], 70);
					if (mCritical < 1)
						mCritical = 1;
				}
			}
			else if ((!index01 || index01 == 2 || index01 == 3 || index01 == 4 || index01 == 5 || index01 == 7) && (v21 == 1 || v21 == 4))
			{
				mCritical += YuzdelikOzellikler2(v21, index01, mEquipValue[index01], 70);
				if (mCritical < 1)
					mCritical = 1;
			}
		}
	}

	switch (mDATA.aAnimalNumber)
	{
	case 1303:
	case 1323:
		mCritical = (int)((float)(ANIMAL_RATE_ONE_GRADE * mCritical));
		break;
	case 1306:
	case 510:
	case 1324:
		mCritical = (int)((float)(ANIMAL_RATE_TWO_GRADE * mCritical));
		break;
	case 1309:
	case 511:
	case 1325:
	case 815:
	case 817:
		mCritical = (int)((float)(ANIMAL_RATE_THREE_GRADE * mCritical));
		break;
	}

	//Yeni Binekler

	if (LegandaryBinekKontrolu(mDATA.aAnimalNumber) == 30)
	{
		//Binek Stat Kýsýmlar legandry       
		mCritical += (int)((float)(LegandaryBinekOzellikleri(3, mDATA.aAnimalNumber) / 100.0 * mCritical));
		mCritical += (int)((float)(LegandaryBinekOzellikleri2(2, 130, mUSER[mIndex].mAvatarInfo.AnimalStat[mUSER[mIndex].mAvatarInfo.aAnimalIndex - 10])));
	}

	if (mUSER[mIndex].mEffectValue[10][0] > 0)
	{
		mCritical = (int)((float)(mCritical * (mUSER[mIndex].mEffectValue[10][0] + 100)) * 0.01f);
	}
	if (tAvatarInfo->SkillIncreaseCritHit <= 6 || tAvatarInfo->SkillIncreaseCritHit >= 12)
	{
		if (tAvatarInfo->SkillIncreaseCritHit == 12)
			mCritical += 8;
	}
	else
	{
		mCritical = mCritical + tAvatarInfo->SkillIncreaseCritHit - 6;
	}

	switch (ItemTypeSetBonusu)
	{
	case 11:
	case 15:
	case 16:
		mCritical += 2;
		break;
	case 19:
		mCritical += 5;
		break;
	case 20:
	case 30:
	case 50:
		mCritical += 7;
		break;
	default:
		break;
	}

	if (mDATA.aGuildBuff[0] == 1 && mDATA.aGuildBuff[1] == 2)
		++mCritical;

	mCritical += (int)((float)(RefineSystem(6) * 0.01f * mCritical));

	if (mGAME.ReturnTribeRole(&mUSER[mIndex].mAvatarInfo.aName[0], mUSER[mIndex].mAvatarInfo.aTribe) == 1)
	{
		mCritical += 2;
	}

	mCritical += (int)(mPAT.ReturnNewPetCombine(tAvatarInfo->aEquip[8][0], tAvatarInfo->aEquip[8][2], 5));

	if (tAvatarInfo->Bottle[tAvatarInfo->BottleIndex] == 880 && tAvatarInfo->BottleTime > 0)
	{
		mCritical += (int)((float)mCritical * 0.05);
	}

	mCritical += (int)(LedandaryCapeUpradge(tAvatarInfo->aEquip[2][0], tAvatarInfo->aEquip[2][2], 7));


	return mCritical;
}
