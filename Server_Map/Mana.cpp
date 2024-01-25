#include "Shengming.h"

int AVATAR_OBJECT::KarakterManasi(void)
{
	int index01;
	int tKi;
	AVATAR_INFO* tAvatarInfo = &mUSER[mIndex].mAvatarInfo;
	mMaxMana = 1;

	if (LabirentKontrolu() == 1)
	{		
		tKi = tAvatarInfo->aUpradgeValue + TitleMana() + 1 + tAvatarInfo->aKi;
	}
	else
	{
		tKi = tAvatarInfo->aUpradgeValue + tAvatarInfo->aKi + TitleMana();
	}


	for (index01 = 0; index01 < MAX_EQUIP_SLOT_NUM; index01++)
	{
		if (mEquipItem[index01] == NULL)
		{
			continue;
		}
		tKi += mEquipItem[index01]->iKi;
	}

    if (mDATA.aFashionNumber == 385 || mDATA.aFashionNumber == 386 || mDATA.aFashionNumber == 387)
        tKi += 50;
    if (mDATA.aFashionNumber >= 17140 && mDATA.aFashionNumber <= 17145)
        tKi += 100;
    if (mDATA.aFashionNumber == 1891 || mDATA.aFashionNumber == 1892 || mDATA.aFashionNumber == 1893)
        tKi += 100;
    if (mDATA.aFashionNumber == 7702
        || mDATA.aFashionNumber == 7703
        || mDATA.aFashionNumber == 7704
        || mDATA.aFashionNumber == 7705
        || mDATA.aFashionNumber == 7706
        || mDATA.aFashionNumber == 7707)
    {
        tKi += 100;
    }
    if (mDATA.aFashionNumber == 18028
        || mDATA.aFashionNumber == 18029
        || mDATA.aFashionNumber == 18030
        || mDATA.aFashionNumber == 18031
        || mDATA.aFashionNumber == 18032
        || mDATA.aFashionNumber == 18033)
    {
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
        tKi += 100;
    }

    tKi += RefineSystem(2);

    if (mDATA.aAnimalOn == 1)
        tKi += BinekAbsorbe();

	mMaxMana = (int)((float)tKi * 15.31f);

   
	if (IsUsedOrnament() == 1) 
	{
		mMaxMana += 750;
	}
	else if (IsUsedOrnament() == 2) 
	{
		mMaxMana += 500; 
	}

    for (index01 = 9; index01 < 13; ++index01)
    {
        if (mEquipItem[index01] == NULL)
        {
            continue;
        }
        if (mItemType[index01] == 2)
        {
            mMaxMana += DecoItemOzellik(2, mEquipValue[index01]);
            if (mMaxMana < 0)
                mMaxMana = 0;
        }
    }

    if ((!KarakolKontrolu()) || (mSERVER_INFO.mServerNumber >= 319 && mSERVER_INFO.mServerNumber <= 323))
    {
        /*v16 = -1;
        sub_55A460(byte_161E4B8, dword_1611D1C, (int)&unk_1613230, &v16);
        if ((!v16 || v16 == 1 || v16 == 2 || v16 == 3) && dword_16141EC[0] == 1)
        {
            v23 += 5000;
        }*/
        int Client;//Cliente avatarinfo2 95 sortlu değeri göndeririyorsun 
        int Client1;//Cliente avatarinfo2 102 sortlu değeri göndeririyorsun 

        if (Client1 == tAvatarInfo->aTribe || Client1 == 4)
        {
            if (Client == 10 && tAvatarInfo->aEatManaPotion < 10 * Client)
            {
                mMaxMana += 2500;
            }
            else if (Client == 20 && tAvatarInfo->aEatManaPotion < 10 * Client)
            {
                mMaxMana += 5000;
            }
            else if (Client == 30)
            {
                mMaxMana += 7500;
            }
            else
            {
                mMaxMana += 25 * tAvatarInfo->aEatManaPotion;
            }
        }
        else
        {
            mMaxMana += (tAvatarInfo->aEatManaPotion * 25);
        }
    }
    int StatConverterd;//dword_1614C14 
    if (StatConverterd > 0 && LabirentKontrolu() == 1)
    {
        int Level;
        Level = ReturnLevel((mDATA.aLevel1 + mDATA.aLevel2));
        mMaxMana += mLEVEL.ReturnLevelFactorMana(Level);
    }
    else
    {
        mMaxMana += mLEVEL.ReturnLevelFactorMana((mDATA.aLevel1 + mDATA.aLevel2));
    }

    switch (mDATA.aAnimalNumber)
    {
    case 1301:
    case 1302:
    case 1303:
    case 1313:
    case 1317:
    case 1320:
    case 1323:
    case 1326:
        mMaxMana = (int)((float)mMaxMana * ANIMAL_RATE_ONE_GRADE);
        break;
    case 1304:
    case 1305:
    case 1306:
    case 1314:
    case 1318:
    case 1321:
    case 1324:
    case 1327:
    case 559:
        mMaxMana = (int)((float)mMaxMana * ANIMAL_RATE_TWO_GRADE);
        break;
    case 1307:
    case 1308:
    case 1309:
    case 1315:
    case 1319:
    case 1322:
    case 1325:
    case 1328:
    case 814:
    case 815:
    case 816:
    case 817:
    case 818:
    case 819:
    case 820:
    case 821:
        mMaxMana = (int)((float)mMaxMana * ANIMAL_RATE_THREE_GRADE);
        break;
    }
	if (mMaxMana < (int)mPAT.ReturnManaValue(tAvatarInfo->aEquip[8][0], tAvatarInfo->aEquip[8][2]))
	{
		mMaxMana += mMaxMana;
	}
	else
	{
		mMaxMana += (int)mPAT.ReturnManaValue(tAvatarInfo->aEquip[8][0], tAvatarInfo->aEquip[8][2]);
	}

    if (ItemTypeSetBonusu == 12)
    {
        mMaxMana += 1000;
    }
    else if (ItemTypeSetBonusu == 17)
    {
        mMaxMana += 1100;
    }

    //socket
    for (index01 = 0; index01 < 13; ++index01)
    {
        if (mEquipItem[index01] == NULL)
        {
            continue;
        }
        mMaxMana += Socket(4, mEquipSocketValue[index01][0], mEquipSocketValue[index01][1], mEquipSocketValue[index01][2]);    
    }

    //Binek kASMA
    if (tAvatarInfo->aAnimalIndex >= 10 && tAvatarInfo->aAnimalIndex < 20)
    {
        //Binek Kısmı
        if (mUSER[mIndex].mAvatarInfo.AnimalExp[tAvatarInfo->aAnimalIndex - 10] / 1000000 > 0)
        {
            mMaxMana += 200 * BinekStats(4, mUSER[mIndex].mAvatarInfo.AnimalStat[mUSER[mIndex].mAvatarInfo.aAnimalIndex - 10]);
        }
    }

    //BirKaç yer eksik
    mMaxMana += (int)(PetMana(tAvatarInfo->aEquip[8][0]));

    mMaxMana += mPAT.ReturnNewPets(tAvatarInfo->aEquip[8][0], tAvatarInfo->aEquip[8][2], 4);

    mMaxMana += (int)(PetMana1(tAvatarInfo->aEquip[8][0]));

    mMaxMana += (int)(LedandaryCapeUpradge(tAvatarInfo->aEquip[2][0], tAvatarInfo->aEquip[2][2], 4));

    mDATA.aMaxManaValue = mMaxMana;
    return mDATA.aMaxManaValue;
}

int AVATAR_OBJECT::EkstraOzelOzelliklerMana(int tLevel)
{
    if (tLevel <= 112)
        return 351;
    if (tLevel <= 145)
        return 886;
    if (tLevel > 156)
        return 1;
    return 1411;
}

int AVATAR_OBJECT::TitleMana(void)
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
    return result;
}

float AVATAR_OBJECT::PetMana(int PetKodu)
{
    double result; // st7
    ITEM_INFO* ItemInfo;

    ItemInfo = mITEM.Search(PetKodu);
    if (!ItemInfo)
        return 0.0;
    if (ItemInfo->iSort != 28)
        return 0.0;
    if (PetKodu > 2410)
    {
        switch (PetKodu)
        {
        case 2411:
            result = 3400.0;
            break;
        case 2412:
            result = 3300.0;
            break;
        case 2413:
            result = 3500.0;
            break;
        case 2414:
            result = 3400.0;
            break;
        case 2415:
            result = 3300.0;
            break;
        case 2416:
            result = 4000.0;
            break;
        case 2417:
            result = 3800.0;
            break;
        case 2418:
            result = 3600.0;
            break;
        case 2419:
            result = 3000.0;
            break;
        case 2420:
            result = 3000.0;
            break;
        case 2421:
            result = 3000.0;
            break;
        default:
        LABEL_60:
            result = 0.0;
            break;
        }
    }
    else if (PetKodu == 2410)
    {
        result = 3500.0;
    }
    else
    {
        switch (PetKodu)
        {
        case 2151:
            result = 3500.0;
            break;
        case 2152:
            result = 4000.0;
            break;
        case 2153:
            result = 3500.0;
            break;
        case 2154:
            result = 3000.0;
            break;
        case 2174:
            result = 3400.0;
            break;
        case 2175:
            result = 3300.0;
            break;
        case 2176:
            result = 3200.0;
            break;
        case 2177:
            result = 3100.0;
            break;
        case 2178:
            result = 3800.0;
            break;
        case 2179:
            result = 3600.0;
            break;
        case 2180:
            result = 3400.0;
            break;
        case 2181:
            result = 3200.0;
            break;
        case 2182:
            result = 3400.0;
            break;
        case 2183:
            result = 3300.0;
            break;
        case 2184:
            result = 3200.0;
            break;
        case 2185:
            result = 3100.0;
            break;
        case 2186:
            result = 3000.0;
            break;
        case 2187:
            result = 3000.0;
            break;
        case 2188:
            result = 3000.0;
            break;
        case 2189:
            result = 3000.0;
            break;
        case 2195:
            result = 4500.0;
            break;
        case 2196:
            result = 4400.0;
            break;
        case 2197:
            result = 4300.0;
            break;
        case 2198:
            result = 4500.0;
            break;
        case 2199:
            result = 4400.0;
            break;
        case 2200:
            result = 4300.0;
            break;
        case 2201:
            result = 5000.0;
            break;
        case 2202:
            result = 4800.0;
            break;
        case 2203:
            result = 4600.0;
            break;
        case 2204:
            result = 4000.0;
            break;
        case 2205:
            result = 4000.0;
            break;
        case 2206:
            result = 4000.0;
            break;
        case 2253:
            result = 2000.0;
            break;
        case 2254:
            result = 4000.0;
            break;
        case 2261:
            result = 2000.0;
            break;
        case 2262:
            result = 4000.0;
            break;
        case 2300:
            result = 2000.0;
            break;
        case 2301:
            result = 4000.0;
            break;
        case 2302:
            result = 3500.0;
            break;
        default:
            goto LABEL_60;
        }
    }
    return result;
}

float AVATAR_OBJECT::PetMana1(int PetKodu)
{
    double result; // st7
    ITEM_INFO* ItemInfo;

    ItemInfo = mITEM.Search(PetKodu);
    if (!ItemInfo)
        return 0.0;
    if (ItemInfo->iSort != 31 && ItemInfo->iSort != 32)
        return 0.0;
    if (PetKodu > 1889)
    {
        if (PetKodu == 1890)
        {
            result = 8000.0;
        }
        else if (PetKodu == 17204)
        {
            result = 8000.0;
        }
        else
        {
        LABEL_19:
            result = 0.0;
        }
    }
    else if (PetKodu == 1889)
    {
        result = 8000.0;
    }
    else
    {
        switch (PetKodu)
        {
        case 1839:
            result = 8000.0;
            break;
        case 1840:
            result = 8000.0;
            break;
        case 1841:
            result = 8000.0;
            break;
        case 1842:
            result = 8000.0;
            break;
        default:
            goto LABEL_19;
        }
    }
    return result;
}
