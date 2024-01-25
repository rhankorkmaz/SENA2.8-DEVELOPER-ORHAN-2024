#include "Shengming.h"

int AVATAR_OBJECT::KarakterCani(void)
{
	int index01;
	int tVitality;
	AVATAR_INFO* tAvatarInfo = &mUSER[mIndex].mAvatarInfo;
	int v43 = 0;
	int v46 = 0;
	mMaxLife = 1;

	if (LabirentKontrolu() == 1)//dword_1614C14 > 0 && Bilinmeyen Özellik
	{

		tVitality = TitleCan() + tAvatarInfo->aUpradgeValue + EkstraOzelOzelliklerCan((mDATA.aLevel1 + mDATA.aLevel2)) + tAvatarInfo->aVitality;
	}
	else
	{
		tVitality = TitleCan() + tAvatarInfo->aVitality + tAvatarInfo->aUpradgeValue;
	}


	for (index01 = 0; index01 < MAX_EQUIP_SLOT_NUM; index01++)
	{
		if (mEquipItem[index01] == NULL)
		{
			continue;
		}
		tVitality += mEquipItem[index01]->iVitality;
	}

	if (mDATA.aFashionNumber >= 17140 && mDATA.aFashionNumber  <= 17145)
		tVitality += 100;
	if (mDATA.aFashionNumber  == 1891 || mDATA.aFashionNumber  == 1892 || mDATA.aFashionNumber  == 1893)
		tVitality += 100;
	if (mDATA.aFashionNumber  == 7702
		|| mDATA.aFashionNumber  == 7703
		|| mDATA.aFashionNumber  == 7704
		|| mDATA.aFashionNumber  == 7705
		|| mDATA.aFashionNumber  == 7706
		|| mDATA.aFashionNumber  == 7707)
	{
		tVitality += 100;
	}
	if (mDATA.aFashionNumber  == 18028
		|| mDATA.aFashionNumber  == 18029
		|| mDATA.aFashionNumber  == 18030
		|| mDATA.aFashionNumber  == 18031
		|| mDATA.aFashionNumber  == 18032
		|| mDATA.aFashionNumber  == 18033)
	{
		tVitality += 100;
	}
	if (mDATA.aFashionNumber  == 18034
		|| mDATA.aFashionNumber  == 18035
		|| mDATA.aFashionNumber  == 18036
		|| mDATA.aFashionNumber  == 18037
		|| mDATA.aFashionNumber  == 18038
		|| mDATA.aFashionNumber  == 18039
		|| mDATA.aFashionNumber  == 18040
		|| mDATA.aFashionNumber  == 18041
		|| mDATA.aFashionNumber  == 18042)
	{
		tVitality += 100;
	}
	tVitality += RefineSystem(1);

	if (mDATA.aAnimalOn == 1)
		tVitality += BinekAbsorbe();

	mMaxLife = (int)((float)tVitality * 20.00f);

	if (IsUsedOrnament() == 1)
	{
		mMaxLife += 825;
	}
	else if (IsUsedOrnament() == 2)
	{
		mMaxLife += 550;
	}

	for (index01 = 9; index01 < MAX_EQUIP_SLOT_NUM; ++index01)
	{

		if (mEquipItem[index01] == NULL)
		{
			continue;
		}
		if (mItemType[index01] == 2)
		{
			mMaxLife += DecoItemOzellik(1, mEquipValue[index01]);
			if (mMaxLife < 0)
				mMaxLife = 0;
		}
	}

	//Genious Client Yeni kore Clientleri
	for (index01 = 0; index01 < 13; ++index01)
	{
		if (mEquipItem[index01] == NULL)
		{
			continue;
		}

		if (!index01 || index01 == 2 || index01 == 3 || index01 == 4 || index01 == 5 || index01 == 7)
		{
			if (mItemType[index01] == 1 || mItemType[index01] == 4)
				mMaxLife += YuzdelikOzellikler2(mItemType[index01], index01, mEquipValue[index01], 100);
			if (mMaxLife < 0)
				mMaxLife = 0;
		}

	}

	if ((!KarakolKontrolu()) || (mSERVER_INFO.mServerNumber >= 319 && mSERVER_INFO.mServerNumber <= 323))
	{

		//Bu kısım en iyi 4 aile sıralaması için
		int v39;
		int unk1 = 0;
		//dword_1614C0C
		//dword_1614C00
		int Client;//Cliente avatarinfo2 95 sortlu değeri göndeririyorsun 
		int Client1;//Cliente avatarinfo2 102 sortlu değeri göndeririyorsun 
		v39 = -1;
		EnIyi4Aile(tAvatarInfo->aTribe,&v39);
		if ((!v39 || v39 == 1) && unk1 == 1)
		{
			mMaxLife += 4000;
		}
		else if (Client1 == tAvatarInfo->aTribe || Client1 == 4)
		{
			if (Client == 10 && (tAvatarInfo->aEatLifePotion < 10 * Client))
			{
				mMaxLife += 2000;
			}
			else if (Client == 20 && (tAvatarInfo->aEatLifePotion < 10 * Client))
			{
				mMaxLife += 4000;
			}
			else if (Client == 30)
			{
				mMaxLife += 6000;
			}
			else
			{
				mMaxLife += (tAvatarInfo->aEatLifePotion * 20);
			}
		}
		else
		{
			mMaxLife += (tAvatarInfo->aEatLifePotion * 20);
		}
	}

	int StatConverterd;//dword_1614C14 
	if (StatConverterd > 0 && LabirentKontrolu() == 1)
	{

		mMaxLife += mLEVEL.ReturnLevelFactorLife(ReturnLevel((mDATA.aLevel1 + mDATA.aLevel2)));
	}
	else
	{
		mMaxLife += mLEVEL.ReturnLevelFactorLife((mDATA.aLevel1 + mDATA.aLevel2));
	}

	if (tAvatarInfo->HealtBoostScroll > 0 || tAvatarInfo->HeroPill > 0)
	{

		mMaxLife = (int)((float)mMaxLife * ANIMAL_RATE_FOUR_GRADE);
	}

	//Binek Can Veriyrore
	switch (mDATA.aAnimalNumber)
	{
	case 1302:
	case 1320:
		mMaxLife = (int)((float)mMaxLife * ANIMAL_RATE_ONE_GRADE);
		break;
	case 1305:
	case 17045:
	case 1321:
	case 17049:
		mMaxLife = (int)((float)mMaxLife * ANIMAL_RATE_TWO_GRADE);
		break;
	case 1308:
	case 1322:
	case 17058:
	case 1329:
	case 17059:
	case 819:
	case 821:
		mMaxLife = (int)((float)mMaxLife * ANIMAL_RATE_THREE_GRADE);
		break;
	case 1331:
	case 17061:
		mMaxLife = (int)((float)mMaxLife * ANIMAL_RATE_FOUR_GRADE);
		break;
	}

	if (LegandaryBinekKontrolu(mDATA.aAnimalNumber) == 30)
	{
		//Binek Stat Kısımlar legandry       
		mMaxLife += (LegandaryBinekOzellikleri(5, mDATA.aAnimalNumber) / 100.0 * mMaxLife);
		mMaxLife += (int)((LegandaryBinekOzellikleri2(2, 30, mUSER[mIndex].mAvatarInfo.AnimalStat[mUSER[mIndex].mAvatarInfo.aAnimalIndex - 10]) / 100.0 * mMaxLife));
		mMaxLife += (int)((LegandaryBinekOzellikleri2(3, 40, mUSER[mIndex].mAvatarInfo.AnimalStat[mUSER[mIndex].mAvatarInfo.aAnimalIndex - 10])));
	}

	//Pet Can veriyore
	if (mMaxLife < (int)mPAT.ReturnLifeValue(tAvatarInfo->aEquip[8][0], tAvatarInfo->aEquip[8][2]))
	{
		mMaxLife += mMaxLife;
	}
	else
	{
		mMaxLife += (int)mPAT.ReturnLifeValue(tAvatarInfo->aEquip[8][0], tAvatarInfo->aEquip[8][2]);
	}

	if (ItemTypeSetBonusu == 13)
	{
		mMaxLife += 1000;
	}
	else if (ItemTypeSetBonusu == 18)
	{
		mMaxLife += 1100;
	}



	for (index01 = 0; index01 < 13; ++index01)
	{
		if (mEquipItem[index01] == NULL)
		{
			continue;
		}
		if (mItemType[index01] == 1 || mItemType[index01] == 4)
		{
			v43 = 1;
			if (!index01)
			{
				v46 = mUTIL.ReturnISValue(mEquipValue[index01]);
				if (v46 > 0)
				{
					if (v46 > 100)
						v46 -= 100;
						mMaxLife += 500 * v46;
				}
			}
		}
		//SoketKısmı
		mMaxLife += Socket(3, mEquipSocketValue[index01][0], mEquipSocketValue[index01][1], mEquipSocketValue[index01][2]);
	}


	if (v43 == 1)
		mMaxLife += 30000;

	//Zırh Döküm
	mMaxLife += 400 * mUTIL.ReturnIBValue(mUSER[mIndex].mAvatarInfo.aEquip[2][2]);

	if (tAvatarInfo->aRank == 6)
		mMaxLife += 1000;




	if (tAvatarInfo->aAnimalIndex >= 10 && tAvatarInfo->aAnimalIndex < 20)
	{
		//Binek Kısmı
		if (mUSER[mIndex].mAvatarInfo.AnimalExp[tAvatarInfo->aAnimalIndex - 10] / 1000000 > 0)
		{
			mMaxLife += 100 * BinekStats(5, mUSER[mIndex].mAvatarInfo.AnimalStat[tAvatarInfo->aAnimalIndex - 10]);
		}
	}

	mMaxLife += YeniOzellikler3232();
	mMaxLife += (int)(mPAT.ReturnEpicPets(tAvatarInfo->aEquip[8][0]));
	mMaxLife += mPAT.ReturnNewPets(tAvatarInfo->aEquip[8][0], tAvatarInfo->aEquip[8][2], 2);
	mMaxLife += (int)(mPAT.ReturnNewPetCombine(tAvatarInfo->aEquip[8][0], tAvatarInfo->aEquip[8][2], 2));
	mMaxLife += (int)(mPAT.ReturnLegandryPets(tAvatarInfo->aEquip[8][0]));
	mMaxLife += (int)(LedandaryCapeUpradge(tAvatarInfo->aEquip[2][0], tAvatarInfo->aEquip[2][2], 3));


	DWORD v28;
	DWORD v33;
	for (index01 = 0; index01 < 8; ++index01)
	{
		if (index01 != 1 && index01 != 6)
		{
			if (mEquipItem[index01] == NULL)
			{
				continue;
			}

			if (mItemType[index01] == 1)
			{
				int v29;
				v29 = mUTIL.ReturnIUValue(mEquipValue[index01]);
				if (v29 > 0 && YeniOzellikCan(v29, &v28, &v33) == 1)
					mMaxLife += v28;
			}

		}
	}
	// Health Boost Scrolls
	if (mUSER[mIndex].mAvatarInfo.HealtBoostScroll > 0)
	{
		mMaxLife *= 1.20f;
	}
	if (mMaxLife < (int)mPAT.ReturnLifeValue(tAvatarInfo->aEquip[8][0], tAvatarInfo->aEquip[8][2]))
	{
		mMaxLife += mMaxLife;
	}
	else
	{
		mMaxLife += (int)mPAT.ReturnLifeValue(tAvatarInfo->aEquip[8][0], tAvatarInfo->aEquip[8][2]);
	}
	if (tAvatarInfo->VigilanteScroll > 0)
		mMaxLife += 500;

	if (tAvatarInfo->Bottle[tAvatarInfo->BottleIndex] == 878 && tAvatarInfo->BottleTime > 0)
	{
		mMaxLife -= (int)((float)mMaxLife * 0.1);
	}
	mDATA.aMaxLifeValue = mMaxLife;
	return mDATA.aMaxLifeValue;
}
int AVATAR_OBJECT::TitleCan(void)
{
	int TitleVitality;

	if (mUSER[mIndex].mAvatarInfo.Title <= 400)
	{
		if (mUSER[mIndex].mAvatarInfo.Title <= 300)
		{
			if (mUSER[mIndex].mAvatarInfo.Title <= 100)
			{
				switch (mUSER[mIndex].mAvatarInfo.Title % 100)
				{
				case 1:
					TitleVitality = 1;
					break;
				case 2:
					TitleVitality = 3;
					break;
				case 3:
					TitleVitality = 6;
					break;
				case 4:
					TitleVitality = 10;
					break;
				case 5:
					TitleVitality = 15;
					break;
				case 6:
					TitleVitality = 21;
					break;
				case 7:
					TitleVitality = 28;
					break;
				case 8:
					TitleVitality = 36;
					break;
				case 9:
					TitleVitality = 45;
					break;
				case 10:
					TitleVitality = 55;
					break;
				case 11:
					TitleVitality = 67;
					break;
				case 12:
					TitleVitality = 82;
					break;
				case 13:
					TitleVitality = 97;
					break;
				case 14:
					TitleVitality = 112;
					break;
				case 15:
					TitleVitality = 127;
					break;
				default:
				LABEL_68:
					TitleVitality = 0;
					break;
				}
			}
			else
			{
				switch (mUSER[mIndex].mAvatarInfo.Title % 100)
				{
				case 1:
					TitleVitality = 0;
					break;
				case 2:
					TitleVitality = 1;
					break;
				case 3:
					TitleVitality = 3;
					break;
				case 4:
					TitleVitality = 5;
					break;
				case 5:
					TitleVitality = 8;
					break;
				case 6:
					TitleVitality = 11;
					break;
				case 7:
					TitleVitality = 14;
					break;
				case 8:
					TitleVitality = 18;
					break;
				case 9:
					TitleVitality = 23;
					break;
				case 10:
					TitleVitality = 28;
					break;
				case 11:
					TitleVitality = 34;
					break;
				case 12:
					TitleVitality = 41;
					break;
				case 13:
					TitleVitality = 48;
					break;
				case 14:
					TitleVitality = 55;
					break;
				case 15:
					TitleVitality = 62;
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
				TitleVitality = 2;
				break;
			case 2:
				TitleVitality = 6;
				break;
			case 3:
				TitleVitality = 12;
				break;
			case 4:
				TitleVitality = 20;
				break;
			case 5:
				TitleVitality = 30;
				break;
			case 6:
				TitleVitality = 42;
				break;
			case 7:
				TitleVitality = 56;
				break;
			case 8:
				TitleVitality = 72;
				break;
			case 9:
				TitleVitality = 90;
				break;
			case 10:
				TitleVitality = 110;
				break;
			case 11:
				TitleVitality = 134;
				break;
			case 12:
				TitleVitality = 164;
				break;
			case 13:
				TitleVitality = 194;
				break;
			case 14:
				TitleVitality = 224;
				break;
			case 15:
				TitleVitality = 254;
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
			TitleVitality = 0;
			break;
		case 2:
			TitleVitality = 1;
			break;
		case 3:
			TitleVitality = 3;
			break;
		case 4:
			TitleVitality = 5;
			break;
		case 5:
			TitleVitality = 8;
			break;
		case 6:
			TitleVitality = 11;
			break;
		case 7:
			TitleVitality = 14;
			break;
		case 8:
			TitleVitality = 18;
			break;
		case 9:
			TitleVitality = 23;
			break;
		case 10:
			TitleVitality = 28;
			break;
		case 11:
			TitleVitality = 34;
			break;
		case 12:
			TitleVitality = 41;
			break;
		case 13:
			TitleVitality = 48;
			break;
		case 14:
			TitleVitality = 55;
			break;
		case 15:
			TitleVitality = 62;
			break;
		default:
			goto LABEL_68;
		}
	}
	return TitleVitality;
}
int AVATAR_OBJECT::BinekAbsorbe(void)
{
	int ArtıStat;

	if (mDATA.aAnimalOn == 0)
		return 0;

	if (mDATA.aAnimalNumber <= 1303)
	{
		if (mDATA.aAnimalNumber >= 1301)
			return 30;
		if (mDATA.aAnimalNumber == 559)
			return 20;
		if (mDATA.aAnimalNumber <= 813 || mDATA.aAnimalNumber > 821)
			return 0;
		return 10;
	}
	if (mDATA.aAnimalNumber > 1936)
	{
		if (mDATA.aAnimalNumber > 2441)
		{
			if (mDATA.aAnimalNumber < 19002 || mDATA.aAnimalNumber > 19021)
				return 0;
		}
		else if (mDATA.aAnimalNumber < 2422)
		{
			switch (mDATA.aAnimalNumber)
			{
			case 2266:
			case 2267:
			case 2268:
			case 2269:
			case 2270:
			case 2271:
			case 2272:
			case 2273:
			case 2274:
			case 2275:
			case 2276:
			case 2277:
			case 2278:
			case 2279:
			case 2280:
			case 2281:
			case 2282:
			case 2283:
			case 2284:
			case 2285:
			case 2316:
			case 2317:
				return 10;
			default:
				return 0;
			}
		}
		return 10;
	}
	if (mDATA.aAnimalNumber >= 1917)
		return 10;
	switch (mDATA.aAnimalNumber)
	{
	case 1304:
	case 1305:
	case 1306:
	case 1314:
	case 1318:
	case 1321:
	case 1324:
	case 1327:
		return 20;
	case 1307:
	case 1308:
	case 1309:
	case 1315:
	case 1319:
	case 1322:
	case 1325:
	case 1328:
		return 10;
	case 1313:
	case 1317:
	case 1320:
	case 1323:
	case 1326:
		return 30;
	case 1329:
	case 1330:
	case 1331:
		ArtıStat = 15;
		break;
	default:
		return 0;
	}
	return ArtıStat;
}
int AVATAR_OBJECT::EkstraOzelOzelliklerCan(int tLevel)
{
	if (tLevel <= 112)
		return 336;
	if (tLevel <= 145)
		return 842;
	if (tLevel > 156)
		return 1;
	return 1420;
}
int AVATAR_OBJECT::ItemType(int ItemKodu)
{

	ITEM_INFO* ItemInfo;

	ItemInfo = mITEM.Search(ItemKodu);
	if (ItemInfo == NULL)
	{
		return -1;
	}
	if (ItemInfo->iType == 5)
	{
		if (ItemInfo->iEquipInfo[1] == 2 || ItemInfo->iEquipInfo[1] == 4 || ItemInfo->iEquipInfo[1] == 5 || ItemInfo->iEquipInfo[1] == 6 || ItemInfo->iEquipInfo[1] == 7 || ItemInfo->iEquipInfo[1] == 9)
			return 1;
		if (ItemInfo->iEquipInfo[1] == 11 || ItemInfo->iEquipInfo[1] == 12 || ItemInfo->iEquipInfo[1] == 13 || ItemInfo->iEquipInfo[1] == 14)
			return 2;
		switch (ItemInfo->iSort)
		{
		case 31:
			return 5;
		case 32:
			return 6;
		case 8:
			return 8;
		case 29:
			return 9;
		}
	}
	else
	{
		if (ItemInfo->iType == 6)
			return 4;
		if ((ItemInfo->iIndex >= 201 && ItemInfo->iIndex <= 218) || (ItemInfo->iIndex >= 2303 && ItemInfo->iIndex <= 2305))
			return 3;
		if (ItemInfo->iSort == 28)
			return 7;
	}
	return 0;
}
int AVATAR_OBJECT::ReturnLevel(int tLevel)
{
	if (tLevel <= 112)
		return 112;
	if (tLevel <= 145)
		return 145;
	if (tLevel > 156)
		return tLevel;
	return 156;
}
int AVATAR_OBJECT::LegandaryBinekKontrolu(int BinekKodu)
{
	ITEM_INFO* ItemInfo;

	ItemInfo = mITEM.Search(BinekKodu);

	if (!ItemInfo)
		return 0;
	if (ItemInfo->iSort == 30)
		return 30;
	return 3;
}
int AVATAR_OBJECT::LegandaryBinekOzellikleri(int tSort, int BinekKodu)
{
	double result; // st7

	switch (tSort)
	{
	case 1:
		if (BinekKodu < 2266 || BinekKodu > 2275)
		{
			if (BinekKodu < 2422 || BinekKodu > 2431)
				result = 0.0;
			else
				result = (BinekKodu - 2411);
		}
		else
		{
			result = (BinekKodu - 2255);
		}
		break;
	case 2:
		if (BinekKodu < 2276 || BinekKodu > 2285)
		{
			if (BinekKodu < 2432 || BinekKodu > 2441)
				result = 0.0;
			else
				result = (BinekKodu - 2421);
		}
		else
		{
			result = (BinekKodu - 2265);
		}
		break;
	case 3:
		if (BinekKodu == 2316)
			result = 15;
		else
			result = 0.0;
		break;
	case 4:
		if (BinekKodu == 2317)
			result = 15;
		else
			result = 0;
		break;
	case 5:
		if (BinekKodu < 1917 || BinekKodu > 1926)
		{
			if (BinekKodu < 1927 || BinekKodu > 1936)
			{
				if (BinekKodu < 19002 || BinekKodu > 19011)
				{
					if (BinekKodu < 19012 || BinekKodu > 19021)
						result = 0;
					else
						result = (BinekKodu - 19001);
				}
				else
				{
					result = (BinekKodu - 18991);
				}
			}
			else
			{
				result = (BinekKodu - 1916);
			}
		}
		else
		{
			result = (BinekKodu - 1906);
		}
		break;
	default:
		result = 0;
		break;
	}
	return result;
}
float AVATAR_OBJECT::LegandaryBinekOzellikleri2(int a1, int a2, int a3)
{
	double result; // st7
	int v4; // [esp+44h] [ebp-8h]
	int v5; // [esp+44h] [ebp-8h]
	int v6; // [esp+44h] [ebp-8h]
	int v7; // [esp+48h] [ebp-4h]
	int v8; // [esp+48h] [ebp-4h]
	int v9; // [esp+48h] [ebp-4h]

	switch (a1)
	{
	case 1:
		v7 = a3 / 1000000 % 10;
		v4 = a3 / 1000000 - v7;
		switch (a2)
		{
		case 10:
			if (v4 != 10)
				goto LABEL_48;
			result = (v7 + 11);
			break;
		case 20:
			if (v4 != 20)
				goto LABEL_48;
			result = (v7 + 11);
			break;
		case 70:
			if (v4 != 70)
				goto LABEL_48;
			result = (v7 + 11);
			break;
		case 80:
			if (v4 != 80)
				goto LABEL_48;
			result = (v7 + 11);
			break;
		default:
			result = 0.0;
			break;
		}
		break;
	case 2:
		v8 = a3 % 1000000 / 1000 % 10;
		v5 = a3 % 1000000 / 1000 - v8;
		if (a2 == 30)
		{
			if (v5 == 30)
				return (v8 + 11);
		}
		else
		{
			if (a2 != 130)
				return 0.0;
			if (v5 == 130)
				return (v8 + 11);
		}
	LABEL_48:
		result = 0.0;
		break;
	case 3:
		v9 = a3 % 1000 % 10;
		v6 = a3 % 1000 - v9;
		switch (a2)
		{
		case 10:
			if (v6 != 10)
				goto LABEL_48;
			result = (30 * (v9 + 1));
			break;
		case 20:
			if (v6 != 20)
				goto LABEL_48;
			result = (20 * (v9 + 1));
			break;
		case 30:
			if (v6 != 30)
				goto LABEL_48;
			result = (100 * (v9 + 1));
			break;
		case 40:
			if (v6 != 40)
				goto LABEL_48;
			result = (200 * (v9 + 1));
			break;
		case 50:
			if (v6 != 50)
				goto LABEL_48;
			result = (200 * (v9 + 1));
			break;
		case 60:
			if (v6 != 60)
				goto LABEL_48;
			result = (100 * (v9 + 1));
			break;
		default:
			result = 0.0;
			break;
		}
		break;
	default:
		result = 0.0;
		break;
	}
	return result;
}
int  AVATAR_OBJECT::DecoItemOzellik(int tSort, int mEquipValue)
{
	int ItemBirlestirme; // [esp+4h] [ebp-14h]
	int v4; // [esp+8h] [ebp-10h]
	int v5; // [esp+8h] [ebp-10h]
	int v6; // [esp+8h] [ebp-10h]
	int v7; // [esp+Ch] [ebp-Ch]
	int ItemDokum; // [esp+10h] [ebp-8h]
	int ItemYuzdesi; // [esp+14h] [ebp-4h]
	int v10;

	if (!mEquipValue)
		return 0;
	ItemYuzdesi = mUTIL.ReturnISValue(mEquipValue);
	ItemBirlestirme = mUTIL.ReturnIUValue(mEquipValue);
	ItemDokum = mUTIL.ReturnIBValue(mEquipValue);
	v7 = mUTIL.ReturnICValue(mEquipValue);
	v4 = YuzdelikOzellikler1(1, tSort, ItemYuzdesi);
	v5 = v4 + YuzdelikOzellikler1(1, tSort, ItemBirlestirme);
	v6 = v5 + YuzdelikOzellikler1(1, tSort, ItemDokum);
	v10 = (v6 + YuzdelikOzellikler1(2, tSort, v7));
	return v10;
}
int  AVATAR_OBJECT::YuzdelikOzellikler1(int a1, int a2, int a3)
{
	int result; // eax

	if (a1 == 1)
	{
		switch (a2)
		{
		case 1:
			if (a3 < 41 || a3 > 60)
				goto LABEL_81;
			result = 100 * (a3 - 40);
			break;
		case 2:
			if (a3 < 61 || a3 > 80)
				goto LABEL_81;
			result = 125 * (a3 - 60);
			break;
		case 4:
			if (a3 < 1 || a3 > 20)
				goto LABEL_81;
			result = 50 * a3;
			break;
		case 6:
			if (a3 < 21 || a3 > 40)
				goto LABEL_81;
			result = 20 * (a3 - 20);
			break;
		case 8:
			if (a3 < 81 || a3 > 100)
				goto LABEL_81;
			result = 50 * (a3 - 80);
			break;
		default:
			result = 0;
			break;
		}
	}
	else if (a1 == 2)
	{
		switch (a2)
		{
		case 1:
			if ((a3 < 1 || a3 > 5) && (a3 < 26 || a3 > 30))
			{
				if ((a3 < 6 || a3 > 10) && (a3 < 31 || a3 > 35))
				{
					if ((a3 < 11 || a3 > 15) && (a3 < 36 || a3 > 40))
					{
						if ((a3 < 16 || a3 > 20) && (a3 < 41 || a3 > 45))
						{
							if ((a3 < 21 || a3 > 25) && (a3 < 46 || a3 > 50))
								goto LABEL_81;
							result = 2000;
						}
						else
						{
							result = 1600;
						}
					}
					else
					{
						result = 1200;
					}
				}
				else
				{
					result = 800;
				}
			}
			else
			{
				result = 400;
			}
			break;
		case 2:
			result = 0;
			break;
		case 4:
			if (a3 < 1 || a3 > 25)
				goto LABEL_81;
			switch (a3 % 5)
			{
			case 1:
				result = 200;
				break;
			case 2:
				result = 400;
				break;
			case 3:
				result = 600;
				break;
			case 4:
				result = 800;
				break;
			default:
				if (a3 % 5)
					goto LABEL_81;
				result = 1000;
				break;
			}
			break;
		case 6:
			result = 0;
			break;
		case 8:
			if (a3 < 26 || a3 > 50)
				goto LABEL_81;
			switch (a3 % 5)
			{
			case 1:
				result = 200;
				break;
			case 2:
				result = 400;
				break;
			case 3:
				result = 600;
				break;
			case 4:
				result = 800;
				break;
			default:
				if (a3 % 5)
					goto LABEL_81;
				result = 1000;
				break;
			}
			break;
		default:
			result = 0;
			break;
		}
	}
	else
	{
	LABEL_81:
		result = 0;
		return result;
	}
	return result;
}
int  AVATAR_OBJECT::YuzdelikOzellikler2(int a1, int a2, int a3, int a4)
{
	int result = 0;; // eax
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
int  AVATAR_OBJECT::YeniOzellikler3232(void)
{
	int v3; // [esp+4h] [ebp-14h]
	int i; // [esp+8h] [ebp-10h]
	int v5; // [esp+Ch] [ebp-Ch]
	int v6; // [esp+10h] [ebp-8h]
	int v7; // [esp+14h] [ebp-4h]
	ITEM_INFO* ItemInfo;

	v6 = 0;
	v5 = 0;
	v7 = 0;

	for (i = 0; i < 8; ++i)
	{
		if (mUSER[mIndex].mAvatarInfo.aEquip[i][0] == NULL)
		{
			continue;
		}

		ItemInfo = mITEM.Search(mUSER[mIndex].mAvatarInfo.aEquip[i][0]);

		if (i != 1
			&& i != 6
			&& ItemInfo->iIndex
			&& ItemInfo->iMartialLevel == 12
			&& mItemType[i] != 1
			&& mItemType[i] != 4)
		{
			v3 = mUTIL.ReturnIUValue(mUSER[mIndex].mAvatarInfo.aEquip[i][2]);
			if (v3 >= 6)
				++v5;
			if (v3 >= 12)
				++v7;
		}
	}
	if (v5 >= 6)
		v6 = 5000;
	if (v7 >= 6)
		v6 += 15000;
	return v6;
}

float AVATAR_OBJECT::LedandaryCapeUpradge(int CapeKodu, int CapeBsi, int a3)
{
	float result; // st7
	float v4; // [esp+0h] [ebp-54h]
	float v5; // [esp+8h] [ebp-4Ch]
	float v6; // [esp+10h] [ebp-44h]
	float v7; // [esp+18h] [ebp-3Ch]
	float v8; // [esp+20h] [ebp-34h]
	float v9; // [esp+28h] [ebp-2Ch]
	float v10; // [esp+30h] [ebp-24h]
	float v11; // [esp+38h] [ebp-1Ch]
	int v12; // [esp+48h] [ebp-Ch]
	int v13; // [esp+4Ch] [ebp-8h]
	int v14; // [esp+50h] [ebp-4h]

	ITEM_INFO* ItemInfo;
	if (CapeKodu == -1 || !CapeKodu)
		return 0.0;
	if (!CapeBsi)
		return 0.0;
	ItemInfo = mITEM.Search(CapeKodu);
	if (!ItemInfo)
		return 0.0;
	if (ItemInfo->iSort != 29)
		return 0.0;
	v13 = mUTIL.ReturnIUValue(CapeBsi);
	if (v13 < 10)
		return 0.0;
	v14 = v13 % 10;
	if (v13 / 10 != a3)
		return 0.0;
	switch (a3)
	{
	case 1:
		v11 = (float)(v14 + 1) * 50.0;
		result = v11;
		break;
	case 2:
		v10 = (float)(v14 + 1) * 50.0;
		result = v10;
		break;
	case 3:
		v9 = (float)(v14 + 1) * 200.0;
		result = v9;
		break;
	case 4:
		v8 = (float)(v14 + 1) * 250.0;
		result = v8;
		break;
	case 5:
		v7 = (float)(v14 + 1) * 100.0;
		result = v7;
		break;
	case 6:
		v6 = (float)(v14 + 1) * 100.0;
		result = v6;
		break;
	case 7:
		v5 = (float)(v14 + 1) * 0.5;
		result = v5;
		break;
	case 8:
		v4 = (float)(v14 + 1) * 0.5;
		result = v4;
		break;
	default:
		result = 0.0;
		break;
	}
	return result;
}
