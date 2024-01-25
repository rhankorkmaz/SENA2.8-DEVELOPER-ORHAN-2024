#include "Shengming.h"

int AVATAR_OBJECT::ItemTypeSetBonus(void)
{
    int result; // eax
    int j; // [esp+4h] [ebp-E0h]
    int i; // [esp+8h] [ebp-DCh]
    int a5;
    int a4;
    int index01;
    int ItemType[MAX_EQUIP_SLOT_NUM];

    //0 týlsým
    //1 cape 
    //2 zýrh
    //3 Eldiven
    //4 yüzük
    //5 bot 
    //6 Pet
    //7 Pala
    //8 Pet
    result = 0;
    for (index01 = 0; index01 < MAX_EQUIP_SLOT_NUM; index01++)
    {
        ItemType[index01] = mUSER[mIndex].mAvatarInfo.aEquip[index01][0];
    }
 
    if (ItemType1(mUSER[mIndex].mAvatarInfo.aEquip[4][0], mUSER[mIndex].mAvatarInfo.aEquip[0][0]))
        return 1;
    if (ItemType2(mUSER[mIndex].mAvatarInfo.aEquip[7][0], mUSER[mIndex].mAvatarInfo.aEquip[2][0]))
        return 2;
    if (ItemType3(mUSER[mIndex].mAvatarInfo.aEquip[2][0], mUSER[mIndex].mAvatarInfo.aEquip[3][0], mUSER[mIndex].mAvatarInfo.aEquip[5][0]))
        return 3;
    if (ItemType4(mUSER[mIndex].mAvatarInfo.aEquip[7][0], mUSER[mIndex].mAvatarInfo.aEquip[5][0]))
        return 4;
    if (ItemType5(
        mUSER[mIndex].mAvatarInfo.aEquip[7][0],
        mUSER[mIndex].mAvatarInfo.aEquip[2][0],
        mUSER[mIndex].mAvatarInfo.aEquip[3][0],
        mUSER[mIndex].mAvatarInfo.aEquip[5][0],
        mUSER[mIndex].mAvatarInfo.aEquip[4][0],
        mUSER[mIndex].mAvatarInfo.aEquip[0][0]))
    {
        return 5;
    }
    if (ItemType6(mUSER[mIndex].mAvatarInfo.aEquip[4][0], mUSER[mIndex].mAvatarInfo.aEquip[0][0]))
        return 6;
    if (ItemType7(mUSER[mIndex].mAvatarInfo.aEquip[7][0], mUSER[mIndex].mAvatarInfo.aEquip[2][0]))
        return 7;
    if (ItemType8(mUSER[mIndex].mAvatarInfo.aEquip[3][0], mUSER[mIndex].mAvatarInfo.aEquip[5][0]))
        return 8;
    if (ItemType9(mUSER[mIndex].mAvatarInfo.aEquip[7][0], mUSER[mIndex].mAvatarInfo.aEquip[2][0], mUSER[mIndex].mAvatarInfo.aEquip[3][0], mUSER[mIndex].mAvatarInfo.aEquip[5][0]))
    {
        if (   mUSER[mIndex].mAvatarInfo.aEquip[4][0] == 88007
            || mUSER[mIndex].mAvatarInfo.aEquip[4][0] == 88015
            || mUSER[mIndex].mAvatarInfo.aEquip[4][0] == 88023
            || mUSER[mIndex].mAvatarInfo.aEquip[4][0] == 88031
            || mUSER[mIndex].mAvatarInfo.aEquip[4][0] == 88039
            || mUSER[mIndex].mAvatarInfo.aEquip[4][0] == 88047
            || mUSER[mIndex].mAvatarInfo.aEquip[0][0] == 88008
            || mUSER[mIndex].mAvatarInfo.aEquip[0][0] == 88016
            || mUSER[mIndex].mAvatarInfo.aEquip[0][0] == 88024
            || mUSER[mIndex].mAvatarInfo.aEquip[0][0] == 88032
            || mUSER[mIndex].mAvatarInfo.aEquip[0][0] == 88040
            || mUSER[mIndex].mAvatarInfo.aEquip[0][0] == 88048)
        {
            result = 0;
        }
        else
        {
            result = 9;
        }
    }
    else if (ItemType10(
        mUSER[mIndex].mAvatarInfo.aEquip[7][0],
        mUSER[mIndex].mAvatarInfo.aEquip[2][0],
        mUSER[mIndex].mAvatarInfo.aEquip[3][0],
        mUSER[mIndex].mAvatarInfo.aEquip[5][0],
        mUSER[mIndex].mAvatarInfo.aEquip[4][0],
        mUSER[mIndex].mAvatarInfo.aEquip[0][0]))
    {
        result = 10;
    }
    else if (ItemType21(
        mUSER[mIndex].mAvatarInfo.aEquip[7][0],
        mUSER[mIndex].mAvatarInfo.aEquip[2][0],
        mUSER[mIndex].mAvatarInfo.aEquip[3][0],
        mUSER[mIndex].mAvatarInfo.aEquip[5][0],
        mUSER[mIndex].mAvatarInfo.aEquip[4][0],
        mUSER[mIndex].mAvatarInfo.aEquip[0][0]))
    {
        result = 21;
    }
    else if (ItemType22(
        mUSER[mIndex].mAvatarInfo.aEquip[7][0],
        mUSER[mIndex].mAvatarInfo.aEquip[2][0],
        mUSER[mIndex].mAvatarInfo.aEquip[3][0],
        mUSER[mIndex].mAvatarInfo.aEquip[5][0],
        mUSER[mIndex].mAvatarInfo.aEquip[4][0],
        mUSER[mIndex].mAvatarInfo.aEquip[0][0]))
    {
        result = 22;
    }
    else if (ItemType15(
        mUSER[mIndex].mAvatarInfo.aEquip[7][0],
        mUSER[mIndex].mAvatarInfo.aEquip[2][0],
        mUSER[mIndex].mAvatarInfo.aEquip[5][0],
        mUSER[mIndex].mAvatarInfo.aEquip[3][0],
        mUSER[mIndex].mAvatarInfo.aEquip[4][0],
        mUSER[mIndex].mAvatarInfo.aEquip[0][0]))
    {
        result = 15;
    }
    else
    {         
        for (index01 = 0; index01 < 13; ++index01)
             ItemType[index01] -= 129;

        if (ItemType1(ItemType[4], ItemType[0]) == 1)
        {
            result = 11;
        }
        else if (ItemType2(ItemType[7], ItemType[2]) == 1)
        {
            result = 12;
        }
        else if (ItemType3(ItemType[3], ItemType[5], ItemType[2]) == 1)
        {
            result = 13;
        }
        else if (ItemType4(ItemType[7], ItemType[5]) == 1)
        {
            result = 14;
        }
        else if (ItemType5(ItemType[7], ItemType[2], ItemType[3], ItemType[5], ItemType[4], ItemType[0]) == 1)
        {
            result = 15;
        }
        else if (ItemType6(ItemType[4], ItemType[0]) == 1)
        {
            result = 16;
        }
        else if (ItemType7(ItemType[7], ItemType[2]) == 1)
        {
            result = 17;
        }
        else if (ItemType8(ItemType[3], ItemType[5]) == 1)
        {
            result = 18;
        }
        else if (ItemType19(mUSER[mIndex].mAvatarInfo.aEquip[7][0], mUSER[mIndex].mAvatarInfo.aEquip[2][0], mUSER[mIndex].mAvatarInfo.aEquip[3][0], mUSER[mIndex].mAvatarInfo.aEquip[5][0]) == 1)
        {
            if (mUSER[mIndex].mAvatarInfo.aEquip[4][0] == 88007
                || mUSER[mIndex].mAvatarInfo.aEquip[4][0] == 88015
                || mUSER[mIndex].mAvatarInfo.aEquip[4][0] == 88023
                || mUSER[mIndex].mAvatarInfo.aEquip[4][0] == 88031
                || mUSER[mIndex].mAvatarInfo.aEquip[4][0] == 88039
                || mUSER[mIndex].mAvatarInfo.aEquip[4][0] == 88047
                || mUSER[mIndex].mAvatarInfo.aEquip[0][0] == 88008
                || mUSER[mIndex].mAvatarInfo.aEquip[0][0] == 88016
                || mUSER[mIndex].mAvatarInfo.aEquip[0][0] == 88024
                || mUSER[mIndex].mAvatarInfo.aEquip[0][0] == 88032
                || mUSER[mIndex].mAvatarInfo.aEquip[0][0] == 88040
                || mUSER[mIndex].mAvatarInfo.aEquip[0][0] == 88048)
            {
                result = 0;
            }
            else
            {
                result = 19;
            }
        }
        else
        {
            a5 = 0;
            a4 = 0;
            for (j = 0; j < 13; ++j)
            {
                if (&mUSER[mIndex].mAvatarInfo.aEquip[j][0] && (!j || j == 2 || j == 3 || j == 4 || j == 5 || j == 7))
                {
                    if (ItemType150(mUSER[mIndex].mAvatarInfo.aEquip[j][0]) == 1)
                        ++a5;
                    if (mItemType[j] == 1 || mItemType[j] == 4)
                        ++a4;
                }
            }
            if (a4 == 6)
            {
                result = 50;
            }
            else if (a5 == 6)
            {
                result = 20;
            }
            else if (a5 + a4 == 6)
            {
                result = 30;
            }
            else
            {
                result = 0;
            }
        }
    }
    return result;
}

BOOL AVATAR_OBJECT::ItemType1(int Yuzuk, int Tilsim)
{
    if (Yuzuk == 87000 && Tilsim == 87001)
        return 1;
    if (Yuzuk == 87021 && Tilsim == 87022)
        return 1;
    if (Yuzuk == 87042 && Tilsim == 87043)
        return 1;
    if (Yuzuk == 87500 && Tilsim == 87501)
        return 1;
    if (Yuzuk == 87521 && Tilsim == 87522)
        return 1;
    if (Yuzuk == 87542 && Tilsim == 87543)
        return 1;
    return 0;
}

BOOL  AVATAR_OBJECT::ItemType2(int Silah, int Zirh)
{
    if (Silah == 87002 && Zirh == 87005)
        return 1;
    if (Silah == 87003 && Zirh == 87005)
        return 1;
    if (Silah == 87004 && Zirh == 87005)
        return 1;
    if (Silah == 87023 && Zirh == 87026)
        return 1;
    if (Silah == 87024 && Zirh == 87026)
        return 1;
    if (Silah == 87025 && Zirh == 87026)
        return 1;
    if (Silah == 87044 && Zirh == 87047)
        return 1;
    if (Silah == 87045 && Zirh == 87047)
        return 1;
    if (Silah == 87046 && Zirh == 87047)
        return 1;
    if (Silah == 87502 && Zirh == 87505)
        return 1;
    if (Silah == 87503 && Zirh == 87505)
        return 1;
    if (Silah == 87504 && Zirh == 87505)
        return 1;
    if (Silah == 87523 && Zirh == 87526)
        return 1;
    if (Silah == 87524 && Zirh == 87526)
        return 1;
    if (Silah == 87525 && Zirh == 87526)
        return 1;
    if (Silah == 87544 && Zirh == 87547)
        return 1;
    if (Silah == 87545 && Zirh == 87547)
        return 1;
    if (Silah == 87546 && Zirh == 87547)
        return 1;
    return 0;
}

BOOL  AVATAR_OBJECT::ItemType3(int Zirh, int Eldiven, int Bot)
{
    if (Zirh == 87006 && Eldiven == 87007 && Bot == 87008)
        return 1;
    if (Zirh == 87027 && Eldiven == 87028 && Bot == 87029)
        return 1;
    if (Zirh == 87048 && Eldiven == 87049 && Bot == 87050)
        return 1;
    if (Zirh == 87506 && Eldiven == 87507 && Bot == 87508)
        return 1;
    if (Zirh == 87527 && Eldiven == 87528 && Bot == 87529)
        return 1;
    if (Zirh == 87548 && Eldiven == 87549 && Bot == 87550)
        return 1;
    return 0;
}

BOOL  AVATAR_OBJECT::ItemType4(int Pala, int Bot)
{
    if (Pala == 87009 && Bot == 87012)
        return 1;
    if (Pala == 87010 && Bot == 87012)
        return 1;
    if (Pala == 87011 && Bot == 87012)
        return 1;
    if (Pala == 87030 && Bot == 87033)
        return 1;
    if (Pala == 87031 && Bot == 87033)
        return 1;
    if (Pala == 87032 && Bot == 87033)
        return 1;
    if (Pala == 87051 && Bot == 87054)
        return 1;
    if (Pala == 87052 && Bot == 87054)
        return 1;
    if (Pala == 87053 && Bot == 87054)
        return 1;
    if (Pala == 87509 && Bot == 87512)
        return 1;
    if (Pala == 87510 && Bot == 87512)
        return 1;
    if (Pala == 87511 && Bot == 87512)
        return 1;
    if (Pala == 87530 && Bot == 87533)
        return 1;
    if (Pala == 87531 && Bot == 87533)
        return 1;
    if (Pala == 87532 && Bot == 87533)
        return 1;
    if (Pala == 87551 && Bot == 87554)
        return 1;
    if (Pala == 87552 && Bot == 87554)
        return 1;
    if (Pala == 87553 && Bot == 87554)
        return 1;
    return 0;
}

BOOL  AVATAR_OBJECT::ItemType5(int Pala, int Zirh, int Eldiven, int Bot, int Yuzuk, int Tilsim)
{
    //Ticarete Açýk
    if (Pala == 87013 && Zirh == 87016 && Eldiven == 87017 && Bot == 87018 && Yuzuk == 87019 && Tilsim == 87020)
        return 1;
    //Ticarete Açýk
    if (Pala == 87014 && Zirh == 87016 && Eldiven == 87017 && Bot == 87018 && Yuzuk == 87019 && Tilsim == 87020)
        return 1;
    //Ticarete Açýk
    if (Pala == 87015 && Zirh == 87016 && Eldiven == 87017 && Bot == 87018 && Yuzuk == 87019 && Tilsim == 87020)
        return 1;
    //Pala Ticarete Kapalý
    if (Pala == 86816 && Zirh == 87016 && Eldiven == 87017 && Bot == 87018 && Yuzuk == 87019 && Tilsim == 87020)
        return 1;
    //Ticarete Açýk
    if (Pala == 87034 && Zirh == 87037 && Eldiven == 87038 && Bot == 87039 && Yuzuk == 87040 && Tilsim == 87041)
        return 1;
    //Ticarete Açýk
    if (Pala == 87035 && Zirh == 87037 && Eldiven == 87038 && Bot == 87039 && Yuzuk == 87040 && Tilsim == 87041)
        return 1;
    //Ticarete Açýk
    if (Pala == 87036 && Zirh == 87037 && Eldiven == 87038 && Bot == 87039 && Yuzuk == 87040 && Tilsim == 87041)
        return 1;
    //Pala Ticarete Kapalý
    if (Pala == 86817 && Zirh == 87037 && Eldiven == 87038 && Bot == 87039 && Yuzuk == 87040 && Tilsim == 87041)
        return 1;
    //Ticarete Açýk
    if (Pala == 87055 && Zirh == 87058 && Eldiven == 87059 && Bot == 87060 && Yuzuk == 87061 && Tilsim == 87062)
        return 1;
    //Ticarete Açýk
    if (Pala == 87056 && Zirh == 87058 && Eldiven == 87059 && Bot == 87060 && Yuzuk == 87061 && Tilsim == 87062)
        return 1;
    //Ticarete Açýk
    if (Pala == 87057 && Zirh == 87058 && Eldiven == 87059 && Bot == 87060 && Yuzuk == 87061 && Tilsim == 87062)
        return 1;
    //Pala Ticarete Kapalý
    if (Pala == 86818 && Zirh == 87058 && Eldiven == 87059 && Bot == 87060 && Yuzuk == 87061 && Tilsim == 87062)
        return 1;
    if (Pala == 87513 && Zirh == 87516 && Eldiven == 87517 && Bot == 87518 && Yuzuk == 87519 && Tilsim == 87520)
        return 1;
    if (Pala == 87514 && Zirh == 87516 && Eldiven == 87517 && Bot == 87518 && Yuzuk == 87519 && Tilsim == 87520)
        return 1;
    if (Pala == 87515 && Zirh == 87516 && Eldiven == 87517 && Bot == 87518 && Yuzuk == 87519 && Tilsim == 87520)
        return 1;
    if (Pala == 86816 && Zirh == 87516 && Eldiven == 87517 && Bot == 87518 && Yuzuk == 87519 && Tilsim == 87520)
        return 1;
    if (Pala == 87534 && Zirh == 87537 && Eldiven == 87538 && Bot == 87539 && Yuzuk == 87540 && Tilsim == 87541)
        return 1;
    if (Pala == 87535 && Zirh == 87537 && Eldiven == 87538 && Bot == 87539 && Yuzuk == 87540 && Tilsim == 87541)
        return 1;
    if (Pala == 87536 && Zirh == 87537 && Eldiven == 87538 && Bot == 87539 && Yuzuk == 87540 && Tilsim == 87541)
        return 1;
    if (Pala == 86817 && Zirh == 87537 && Eldiven == 87538 && Bot == 87539 && Yuzuk == 87540 && Tilsim == 87541)
        return 1;
    if (Pala == 87555 && Zirh == 87558 && Eldiven == 87559 && Bot == 87560 && Yuzuk == 87561 && Tilsim == 87562)
        return 1;
    if (Pala == 87556 && Zirh == 87558 && Eldiven == 87559 && Bot == 87560 && Yuzuk == 87561 && Tilsim == 87562)
        return 1;
    if (Pala == 87557 && Zirh == 87558 && Eldiven == 87559 && Bot == 87560 && Yuzuk == 87561 && Tilsim == 87562)
        return 1;
    if (Pala == 86818 && Zirh == 87558 && Eldiven == 87559 && Bot == 87560 && Yuzuk == 87561 && Tilsim == 87562)
        return 1;
    return 0;
}

BOOL  AVATAR_OBJECT::ItemType6(int a1, int a2)
{
    if (a1 == 87063 && a2 == 87064)
        return 1;
    if (a1 == 87085 && a2 == 87086)
        return 1;
    if (a1 == 87107 && a2 == 87108)
        return 1;
    return 0;
}

BOOL  AVATAR_OBJECT::ItemType7(int a1, int a2)
{  
    if (a1 == 87065 && a2 == 87068)
        return 1;
    if (a1 == 87066 && a2 == 87068)
        return 1;
    if (a1 == 87067 && a2 == 87068)
        return 1;
    if (a1 == 87087 && a2 == 87090)
        return 1;
    if (a1 == 87088 && a2 == 87090)
        return 1;
    if (a1 == 87089 && a2 == 87090)
        return 1;
    if (a1 == 87109 && a2 == 87112)
        return 1;
    if (a1 == 87110 && a2 == 87112)
        return 1;
    if (a1 == 87111 && a2 == 87112)
        return 1;
    return 0;
}

BOOL  AVATAR_OBJECT::ItemType8(int a1, int a2)
{  
    if (a1 == 87069 && a2 == 87070)
        return 1;
    if (a1 == 87091 && a2 == 87092)
        return 1;
    if (a1 == 87113 && a2 == 87114)
        return 1;
    return 0;
}

BOOL  AVATAR_OBJECT::ItemType9(int a1, int a2, int a3, int a4)
{  
    if (a1 == 87071 && a2 == 87074 && a3 == 87075 && a4 == 87076)
        return 1;
    if (a1 == 87072 && a2 == 87074 && a3 == 87075 && a4 == 87076)
        return 1;
    if (a1 == 87073 && a2 == 87074 && a3 == 87075 && a4 == 87076)
        return 1;
    if (a1 == 87093 && a2 == 87096 && a3 == 87097 && a4 == 87098)
        return 1;
    if (a1 == 87094 && a2 == 87096 && a3 == 87097 && a4 == 87098)
        return 1;
    if (a1 == 87095 && a2 == 87096 && a3 == 87097 && a4 == 87098)
        return 1;
    if (a1 == 87115 && a2 == 87118 && a3 == 87119 && a4 == 87120)
        return 1;
    if (a1 == 87116 && a2 == 87118 && a3 == 87119 && a4 == 87120)
        return 1;
    if (a1 == 87117 && a2 == 87118 && a3 == 87119 && a4 == 87120)
        return 1;
    return 0;
}

BOOL  AVATAR_OBJECT::ItemType10(int a1, int a2, int a3, int a4, int a5, int a6)
{   
    if (a1 == 87077 && a2 == 87080 && a3 == 87081 && a4 == 87082 && a5 == 87083 && a6 == 87084)
        return 1;
    if (a1 == 87078 && a2 == 87080 && a3 == 87081 && a4 == 87082 && a5 == 87083 && a6 == 87084)
        return 1;
    if (a1 == 87079 && a2 == 87080 && a3 == 87081 && a4 == 87082 && a5 == 87083 && a6 == 87084)
        return 1;
    if (a1 == 87099 && a2 == 87102 && a3 == 87103 && a4 == 87104 && a5 == 87105 && a6 == 87106)
        return 1;
    if (a1 == 87100 && a2 == 87102 && a3 == 87103 && a4 == 87104 && a5 == 87105 && a6 == 87106)
        return 1;
    if (a1 == 87101 && a2 == 87102 && a3 == 87103 && a4 == 87104 && a5 == 87105 && a6 == 87106)
        return 1;
    if (a1 == 87121 && a2 == 87124 && a3 == 87125 && a4 == 87126 && a5 == 87127 && a6 == 87128)
        return 1;
    if (a1 == 87122 && a2 == 87124 && a3 == 87125 && a4 == 87126 && a5 == 87127 && a6 == 87128)
        return 1;
    if (a1 == 87123 && a2 == 87124 && a3 == 87125 && a4 == 87126 && a5 == 87127 && a6 == 87128)
        return 1;
    return 0;
}

BOOL  AVATAR_OBJECT::ItemType21(int a1, int a2, int a3, int a4, int a5, int a6)
{    
    if (a1 == 88001 && a2 == 88004 && a3 == 88005 && a4 == 88006 && a5 == 88007 && a6 == 88008)
        return 1;
    if (a1 == 88002 && a2 == 88004 && a3 == 88005 && a4 == 88006 && a5 == 88007 && a6 == 88008)
        return 1;
    if (a1 == 88003 && a2 == 88004 && a3 == 88005 && a4 == 88006 && a5 == 88007 && a6 == 88008)
        return 1;
    if (a1 == 88009 && a2 == 88012 && a3 == 88013 && a4 == 88014 && a5 == 88015 && a6 == 88016)
        return 1;
    if (a1 == 88010 && a2 == 88012 && a3 == 88013 && a4 == 88014 && a5 == 88015 && a6 == 88016)
        return 1;
    if (a1 == 88011 && a2 == 88012 && a3 == 88013 && a4 == 88014 && a5 == 88015 && a6 == 88016)
        return 1;
    if (a1 == 88017 && a2 == 88020 && a3 == 88021 && a4 == 88022 && a5 == 88023 && a6 == 88024)
        return 1;
    if (a1 == 88018 && a2 == 88020 && a3 == 88021 && a4 == 88022 && a5 == 88023 && a6 == 88024)
        return 1;
    if (a1 == 88019 && a2 == 88020 && a3 == 88021 && a4 == 88022 && a5 == 88023 && a6 == 88024)
        return 1;
    return 0;
}

BOOL  AVATAR_OBJECT::ItemType22(int a1, int a2, int a3, int a4, int a5, int a6)
{
    if (a1 == 88025 && a2 == 88028 && a3 == 88029 && a4 == 88030 && a5 == 88031 && a6 == 88032)
        return 1;
    if (a1 == 88026 && a2 == 88028 && a3 == 88029 && a4 == 88030 && a5 == 88031 && a6 == 88032)
        return 1;
    if (a1 == 88027 && a2 == 88028 && a3 == 88029 && a4 == 88030 && a5 == 88031 && a6 == 88032)
        return 1;
    if (a1 == 88033 && a2 == 88036 && a3 == 88037 && a4 == 88038 && a5 == 88039 && a6 == 88040)
        return 1;
    if (a1 == 88034 && a2 == 88036 && a3 == 88037 && a4 == 88038 && a5 == 88039 && a6 == 88040)
        return 1;
    if (a1 == 88035 && a2 == 88036 && a3 == 88037 && a4 == 88038 && a5 == 88039 && a6 == 88040)
        return 1;
    if (a1 == 88041 && a2 == 88044 && a3 == 88045 && a4 == 88046 && a5 == 88047 && a6 == 88048)
        return 1;
    if (a1 == 88042 && a2 == 88044 && a3 == 88045 && a4 == 88046 && a5 == 88047 && a6 == 88048)
        return 1;
    if (a1 == 88043 && a2 == 88044 && a3 == 88045 && a4 == 88046 && a5 == 88047 && a6 == 88048)
        return 1;
    return 0;
}

BOOL  AVATAR_OBJECT::ItemType15(int a1, int a2, int a3, int a4, int a5, int a6)
{
    if (a1 == 89515 && a2 == 89516 && a3 == 89517 && a4 == 89518 && a5 == 89519 && a6 == 89520)
        return 1;
    if (a1 == 89536 && a2 == 89537 && a3 == 89538 && a4 == 89539 && a5 == 89540 && a6 == 89541) 
        return 1;    
    if (a1 == 89557 && a2 == 89558 && a3 == 89559 && a4 == 89560 && a5 == 89561 && a6 == 89562)
        return 1;
    return 0;
}

BOOL  AVATAR_OBJECT::ItemType19(int a1, int a2, int a3, int a4)
{
    if (a1 == 87200 && a2 == 87203 && a3 == 87204 && a4 == 87205)
        return 1;
    if (a1 == 87201 && a2 == 87203 && a3 == 87204 && a4 == 87205)
        return 1;
    if (a1 == 87202 && a2 == 87203 && a3 == 87204 && a4 == 87205)
        return 1;
    if (a1 == 87222 && a2 == 87225 && a3 == 87226 && a4 == 87227)
        return 1;
    if (a1 == 87223 && a2 == 87225 && a3 == 87226 && a4 == 87227)
        return 1;
    if (a1 == 87224 && a2 == 87225 && a3 == 87226 && a4 == 87227)
        return 1;
    if (a1 == 87244 && a2 == 87247 && a3 == 87248 && a4 == 87249)
        return 1;
    if (a1 == 87245 && a2 == 87247 && a3 == 87248 && a4 == 87249)
        return 1;
    if (a1 == 87246 && a2 == 87247 && a3 == 87248 && a4 == 87249)
        return 1;
    return 0;
}

BOOL  AVATAR_OBJECT::ItemType150(int a1)
{
    if (a1 >= 87206 && a1 <= 87213)
        return 1;
    if (a1 >= 87228 && a1 <= 87235)
        return 1;
    if (a1 >= 87250 && a1 <= 87257)
        return 1;

    return 0;
}
int AVATAR_OBJECT::BinekStats(int tSort, int BinekStat)
{
    int result; // eax
    int BinekOzellik[8]; // [esp+4h] [ebp-24h]
    int index01; // [esp+24h] [ebp-4h]

    if (BinekStat == 0)
    {
        return 0;
    }
    for (index01 = 0; index01 < 8; ++index01)
    {
        BinekOzellik[index01] = 0;
    }
    for (index01 = 0; index01 < 8; ++index01)
    {
        (BinekOzellik[index01]) = BinekStat % 10;
        BinekStat = BinekStat / 10;
    }
    result = BinekOzellik[tSort];
    return result;
}
int AVATAR_OBJECT::YeniOzellikCan(int a1, DWORD* a2, DWORD* a3)
{
    int v4; // [esp+8h] [ebp-4h]
    switch (a1)
    {
    case 11:
        v4 = 1;
        *a2 = 1000;
        *a3 = 2;
        break;
    case 12:
        v4 = 1;
        *a2 = 1000;
        *a3 = 4;
        break;
    case 13:
        v4 = 1;
        *a2 = 1000;
        *a3 = 6;
        break;
    case 14:
        v4 = 1;
        *a2 = 1000;
        *a3 = 8;
        break;
    case 15:
        v4 = 1;
        *a2 = 1000;
        *a3 = 10;
        break;
    case 21:
        v4 = 1;
        *a2 = 2000;
        *a3 = 2;
        break;
    case 22:
        v4 = 1;
        *a2 = 2000;
        *a3 = 4;
        break;
    case 23:
        v4 = 1;
        *a2 = 2000;
        *a3 = 6;
        break;
    case 24:
        v4 = 1;
        *a2 = 2000;
        *a3 = 8;
        break;
    case 25:
        v4 = 1;
        *a2 = 2000;
        *a3 = 10;
        break;
    case 31:
        v4 = 1;
        *a2 = 3000;
        *a3 = 2;
        break;
    case 32:
        v4 = 1;
        *a2 = 3000;
        *a3 = 4;
        break;
    case 33:
        v4 = 1;
        *a2 = 3000;
        *a3 = 6;
        break;
    case 34:
        v4 = 1;
        *a2 = 3000;
        *a3 = 8;
        break;
    case 35:
        v4 = 1;
        *a2 = 3000;
        *a3 = 10;
        break;
    case 41:
        v4 = 1;
        *a2 = 4000;
        *a3 = 2;
        break;
    case 42:
        v4 = 1;
        *a2 = 4000;
        *a3 = 4;
        break;
    case 43:
        v4 = 1;
        *a2 = 4000;
        *a3 = 6;
        break;
    case 44:
        v4 = 1;
        *a2 = 4000;
        *a3 = 8;
        break;
    case 45:
        v4 = 1;
        *a2 = 4000;
        *a3 = 10;
        break;
    case 51:
        v4 = 1;
        *a2 = 5000;
        *a3 = 2;
        break;
    case 52:
        v4 = 1;
        *a2 = 5000;
        *a3 = 4;
        break;
    case 53:
        v4 = 1;
        *a2 = 5000;
        *a3 = 6;
        break;
    case 54:
        v4 = 1;
        *a2 = 5000;
        *a3 = 8;
        break;
    case 55:
        v4 = 1;
        *a2 = 5000;
        *a3 = 10;
        break;
    default:
        v4 = 0;
        *a2 = 0;
        *a3 = 0;
        break;
    }
    return v4;
}
int AVATAR_OBJECT::EnIyi4Aile(int tTribe,int* Siralama)
{
    int result; // eax
    int i; // [esp+4h] [ebp-4h]

    if (tTribe <= 3)
    {
        for (i = 0; i < 4; ++i)
        {
            if (strcmp(mGAME.mWorldInfo.Top4Guild[tTribe][i], mUSER[mIndex].mAvatarInfo.aGuildName) == 0)
            {
                *Siralama = i;
                return 1;
            }
        }
        *Siralama = -1;
        result = 0;
    }
    else
    {
        *Siralama = -1;
        result = 0;
    }
    return result;
}