#include "Shengming.h"


int AVATAR_OBJECT::KarakterAtakSucces(void)
{
	int index01;
	int tStrength;
	int tISValue;
	int tIUValue;
	int tIUEffectValue;
	AVATAR_INFO* tAvatarInfo = &mUSER[mIndex].mAvatarInfo;

	mAttackSuccess = 0;

	if (LabirentKontrolu() == 1)//dword_1614C14 > 0 && Bilinmeyen Özellik
	{

		tStrength = TitleSucess() + tAvatarInfo->aUpradgeValue + EkstraOzelOzelliklerCan((mDATA.aLevel1 + mDATA.aLevel2)) + tAvatarInfo->aStrength;
	}
	else
	{
		tStrength = TitleSucess() + tAvatarInfo->aStrength + tAvatarInfo->aUpradgeValue;
	}

	for (index01 = 0; index01 < MAX_EQUIP_SLOT_NUM; index01++)
	{
		if (mEquipItem[index01] == NULL)
		{
			continue;
		}
		tStrength += mEquipItem[index01]->iStrength;
	}

	if (mDATA.aFashionNumber >= 17140 && mDATA.aFashionNumber <= 17145)
		tStrength += 100;
	if (mDATA.aFashionNumber == 1891 || mDATA.aFashionNumber == 1892 || mDATA.aFashionNumber == 1893)
		tStrength += 100;
	if (mDATA.aFashionNumber == 7702
		|| mDATA.aFashionNumber == 7703
		|| mDATA.aFashionNumber == 7704
		|| mDATA.aFashionNumber == 7705
		|| mDATA.aFashionNumber == 7706
		|| mDATA.aFashionNumber == 7707)
	{
		tStrength += 100;
	}
	if (mDATA.aFashionNumber == 18028
		|| mDATA.aFashionNumber == 18029
		|| mDATA.aFashionNumber == 18030
		|| mDATA.aFashionNumber == 18031
		|| mDATA.aFashionNumber == 18032
		|| mDATA.aFashionNumber == 18033)
	{
		tStrength += 100;
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
	}
	if (mDATA.aFashionNumber == 2146 || mDATA.aFashionNumber == 2147 || mDATA.aFashionNumber == 2148)
		tStrength += 50;

	tStrength += RefineSystem(3);

	if (mDATA.aAnimalOn == 1)
		tStrength += BinekAbsorbe();

	mAttackSuccess += (int)((float)tStrength * 1.71f);

	int StatConverterd;//dword_1614C14 
	if (StatConverterd > 0 && LabirentKontrolu() == 1)
	{
		int Level;
		Level = ReturnLevel((mDATA.aLevel1 + mDATA.aLevel2));
		mAttackSuccess += mLEVEL.ReturnLevelFactorAttackSuccess(Level);
	}
	else
	{
		mAttackSuccess += mLEVEL.ReturnLevelFactorAttackSuccess((mDATA.aLevel1 + mDATA.aLevel2));
	}

	for (index01 = 0; index01 < 13; ++index01)
	{
		if (mEquipItem[index01] == NULL)
		{
			continue;
		}
		mAttackSuccess += mEquipItem[index01]->iAttackSucess;
		if (index01 != 8)
		{
			switch (ItemTypeSetBonusu)
			{
			case 3:
				mAttackSuccess += (int)((float)mEquipItem[index01]->iAttackSucess * 0.6f);
				break;
			case 5:
				mAttackSuccess += (int)((float)mEquipItem[index01]->iAttackSucess * 1.0f);
				break;
			case 8:
				mAttackSuccess += (int)((float)mEquipItem[index01]->iAttackSucess * 0.4f);
				break;
			case 9:
				mAttackSuccess += (int)((float)mEquipItem[index01]->iAttackSucess * 0.6f);
				break;
			case 10:
				mAttackSuccess += (int)((float)mEquipItem[index01]->iAttackSucess * 1.0f);
				break;
			case 13:
			case 18:
			case 19:
				mAttackSuccess += (int)((float)mEquipItem[index01]->iAttackSucess * 0.7f);
				break;
			case 15:
			case 20:
				mAttackSuccess += (int)((float)mEquipItem[index01]->iAttackSucess * 1.1f);
				break;
			case 21:
				mAttackSuccess += (int)((float)mEquipItem[index01]->iAttackSucess * 0.2f);
				break;
			case 22:
				mAttackSuccess += (int)((float)mEquipItem[index01]->iAttackSucess * 0.1f);
				break;
			case 30:
				if (index01 == 1 || index01 == 10)
				{
					mAttackSuccess += (int)((float)mEquipItem[index01]->iAttackSucess * 0.55f);
				}
				else if (index01 != 9 && index01 != 11 && index01 != 12)
				{
					if (mItemType[index01] == 1 || mItemType[index01] == 4)
						mAttackSuccess += (int)((float)mEquipItem[index01]->iAttackSucess * 0.55f);
					else
						mAttackSuccess += (int)((float)mEquipItem[index01]->iAttackSucess * 1.1f);
				}
				break;
			case 50:
				mAttackSuccess += (int)((float)mEquipItem[index01]->iAttackSucess * 0.55f);
				break;
			default:
				break;
			}
			if (index01 == 3)
			{
				if (mItemType[index01] == 1 || mItemType[index01] == 4)
				{
					tISValue = mUTIL.ReturnISValue(mEquipValue[index01]);
					if (tISValue > 0)
					{
						if (tISValue >= 100)
							tISValue -= 100;
						mAttackSuccess += 1500 * tISValue;
					}
				}
				else if (mEquipItem[index01]->iSetBonus == 2)
				{
					mAttackSuccess += SucessAtak1(index01, mUTIL.ReturnIUValue(mEquipValue[index01]), ItemTypeSetBonusu);
					tISValue = mUTIL.ReturnISValueWithLevelLimit(tAvatarInfo->aLevel1, mUTIL.ReturnISValue(mEquipValue[index01]));
					if (tISValue > 0)
						mAttackSuccess += (int)((float)mEquipItem[index01]->iAttackSucess * tISValue * 0.03f);
				}
				else
				{
					tIUValue = mUTIL.ReturnIUValueWithLevelLimit(tAvatarInfo->aLevel1, mUTIL.ReturnIUValue(mEquipValue[index01]));
					tIUEffectValue = mUTIL.ReturnIUEffectValue(mEquipItem[index01], 3);
					mAttackSuccess += (tIUValue * tIUEffectValue);
					tISValue = mUTIL.ReturnISValueWithLevelLimit(tAvatarInfo->aLevel1, mUTIL.ReturnISValue(mEquipValue[index01]));
					if (tISValue > 0)
					{
						mAttackSuccess += (int)((float)(mEquipItem[index01]->iAttackSucess + (tIUValue * tIUEffectValue)) * ((float)tISValue * 0.03f));
					}
				}
			}
			else if (index01 == 7)
			{
				if (mEquipItem[index01]->iSetBonus == 2)
				{
					mAttackSuccess += SucessAtak1(index01, mUTIL.ReturnIUValue(mEquipValue[index01]), ItemTypeSetBonusu);
				}
				else
				{
					tIUValue = mUTIL.ReturnIUValueWithLevelLimit(tAvatarInfo->aLevel1, mUTIL.ReturnIUValue(mEquipValue[index01]));
					tIUEffectValue = mUTIL.ReturnIUEffectValue(mEquipItem[index01], 3);
					mAttackSuccess += (tIUValue * tIUEffectValue);
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
			int v24;
			v24 = mItemType[index01];
			if (index01 == 1)
			{
				if (v24 == 8)
				{
					mAttackSuccess += YuzdelikOzellikler2(mItemType[index01], index01, mEquipValue[index01], 30);
					if (mAttackSuccess < 1)
						mAttackSuccess = 1;
				}
			}
			else if ((!index01 || index01 == 2 || index01 == 3 || index01 == 4 || index01 == 5 || index01 == 7) && (v24 == 1 || v24 == 4))
			{
				mAttackSuccess += YuzdelikOzellikler2(mItemType[index01], index01, mEquipValue[index01], 30);
				if (mAttackSuccess < 1)
					mAttackSuccess = 1;
			}
		}
	}

	if ((!KarakolKontrolu()) || (mSERVER_INFO.mServerNumber >= 319 && mSERVER_INFO.mServerNumber <= 323))
	{
		/*v16 = -1;
		sub_55A460((unsigned __int16)dword_1611D1C, &unk_1613230, &v16);
		if ((!v16 || v16 == 1 || v16 == 2) && dword_16141F4 == 1)
		{
			v28 += 400;
		}*/
		//dword_1614C0C
		//dword_1614C00
		int Client=0;//Cliente avatarinfo2 95 sortlu deðeri göndeririyorsun 
		int Client1=0;//Cliente avatarinfo2 102 sortlu deðeri göndeririyorsun 
		if (Client == 1)
		{
			if (Client == tAvatarInfo->aTribe || Client1 == 4)
			{
				if (Client1 == 10 && tAvatarInfo->StrElx < 10 * Client1)
				{
					mAttackSuccess += 200;
				}
				else if (Client1 == 20 && tAvatarInfo->StrElx < 10 * Client1)
				{
					mAttackSuccess += 400;
				}
				else if (Client1 == 30)
				{
					mAttackSuccess += 600;
				}
				else
				{
					mAttackSuccess += 2 * tAvatarInfo->AgiElx;
				}
			}
		}
		else
		{
			 mAttackSuccess += 2 * tAvatarInfo->AgiElx;
		}
	}

	if (mDATA.aGuildBuff[0] == 1 && mDATA.aGuildBuff[1] == 4)
	{
		mAttackSuccess = (int)((float)mAttackSuccess * ANIMAL_RATE_TWO_GRADE);
	}

	switch (mDATA.aAnimalNumber)
	{
	case 1313:
		mAttackSuccess = (int)((float)mAttackSuccess * ANIMAL_RATE_ONE_GRADE);
		break;
	case 1314:
	case 510:
		mAttackSuccess = (int)((float)mAttackSuccess * ANIMAL_RATE_TWO_GRADE);
		break;
	case 1315:
	case 511:
	case 820:
		mAttackSuccess = (int)((float)mAttackSuccess * ANIMAL_RATE_THREE_GRADE);
		break;
	}
	//yENÝ BÝNEKLER
	if (LegandaryBinekKontrolu(mDATA.aAnimalNumber) == 30)
	{
		mAttackSuccess += (int)((float)(LegandaryBinekOzellikleri2(3, 20, mUSER[mIndex].mAvatarInfo.AnimalStat[mUSER[mIndex].mAvatarInfo.aAnimalIndex - 10])));
	}

	


	if (mUSER[mIndex].mEffectValue[2][0] > 0)
	{
		mAttackSuccess = (int)((float)(mAttackSuccess * (mUSER[mIndex].mEffectValue[2][0] + 100)) * 0.01f);
	}
	if (mUSER[mIndex].mEffectValue[17][0] > 0)
	{
		mAttackSuccess = (int)((float)(mAttackSuccess * (mUSER[mIndex].mEffectValue[17][0] + 100)) * 0.01f);
	}

	if (ItemTypeSetBonusu == 14)
		mAttackSuccess += 100;
	//Socket Sistemi
	for (index01 = 0; index01 < 13; ++index01)
	{
		if (mEquipItem[index01] == NULL)
		{
			continue;
		}
		mAttackSuccess += Socket(5, mEquipSocketValue[index01][0], mEquipSocketValue[index01][1], mEquipSocketValue[index01][2]);
	}

	if (tAvatarInfo->aRank == 5)
		mAttackSuccess += 1000;

	//Rank Kasma
	if (tAvatarInfo->aAnimalIndex >= 10 && tAvatarInfo->aAnimalIndex < 20)
	{
		//Binek Kýsmý
		if (mUSER[mIndex].mAvatarInfo.AnimalExp[tAvatarInfo->aAnimalIndex - 10] / 1000000 > 0)
		{
			mAttackSuccess += 100 * BinekStats(3, mUSER[mIndex].mAvatarInfo.AnimalStat[mUSER[mIndex].mAvatarInfo.aAnimalIndex - 10]);
		}
	}


	mAttackSuccess += mPAT.ReturnNewPets(tAvatarInfo->aEquip[8][0], tAvatarInfo->aEquip[8][2], 3);

	if (tAvatarInfo->Bottle[tAvatarInfo->BottleIndex] == 881 && tAvatarInfo->BottleTime > 0)
	{
		mAttackSuccess -= (int)((float)mAttackSuccess * 0.2);
	}

	return mAttackSuccess;
}

int AVATAR_OBJECT::TitleSucess(void)
{
	int result; // eax

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


int AVATAR_OBJECT::SucessAtak1(int a1, int a2, int a3)
{
	int result; // eax

	if (a1 == 3)
	{
		switch (a2)
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
		case 5:
			result = 1000;
			break;
		case 6:
			result = 1200;
			break;
		case 7:
			result = 1400;
			break;
		case 8:
			result = 1600;
			break;
		case 9:
			result = 1800;
			break;
		case 10:
			result = 2000;
			break;
		case 11:
			result = 2200;
			break;
		case 12:
			result = 2400;
			break;
		default:
			result = 0;
			break;
		}
	}
	else if (a1 == 7)
	{
		switch (a2)
		{
		case 1:
			result = 60;
			break;
		case 2:
			result = 120;
			break;
		case 3:
			result = 180;
			break;
		case 4:
			result = 240;
			break;
		case 5:
			result = 300;
			break;
		case 6:
			result = 360;
			break;
		case 7:
			result = 420;
			break;
		case 8:
			result = 480;
			break;
		case 9:
			result = 540;
			break;
		case 10:
			result = 600;
			break;
		case 11:
			result = 660;
			break;
		case 12:
			result = 720;
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