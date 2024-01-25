#include "Shengming.h"

int AVATAR_OBJECT::Socket(int SocketSort, int Soket1, int Soket2, int Soket3)
{
	char Soket1Index[4]; 
	char Soket2Index[4];
	char Soket3Index[4];
	int  tResult = 0; 
	CopyMemory(&Soket1Index[0], &Soket1, 4);
	CopyMemory(&Soket2Index[0], &Soket2, 4);
	CopyMemory(&Soket3Index[0], &Soket3, 4);
	if (!Soket1Index[1])
		return 0;


	tResult += SocketOzellikler(SocketSort, Soket1Index[2], Soket1Index[3]);
	if (Soket1Index[1] == 1)
		return tResult;

	tResult += SocketOzellikler(SocketSort, Soket2Index[0], Soket2Index[1]);
	if (Soket1Index[1] == 2)
		return tResult;

	tResult += SocketOzellikler(SocketSort, Soket2Index[2], Soket2Index[3]);
	if (Soket1Index[1] == 3)
		return tResult;

	tResult += SocketOzellikler(SocketSort, Soket3Index[0], Soket3Index[1]);
	if (Soket1Index[1] == 4)
		return tResult;

	tResult += SocketOzellikler(SocketSort, Soket3Index[2], Soket3Index[3]);
	if (Soket1Index[1] == 5)
		return tResult;

	return 0;
}

int AVATAR_OBJECT::SocketOzellikler(int SocketSort, int SoketType, int SoketNumber)
{
	int result = 0; // eax
	int Socket = 0; // [esp+10h] [ebp-8h]
	SOCKET_INFO* tSocket_Info; // [esp+14h] [ebp-4h]

	switch (SocketSort)
	{
	case 1:
		if (SoketType == 1)
		{
			if (SoketNumber == 1 || SoketNumber == 6 || SoketNumber == 11)
				Socket = 1;
			goto LABEL_220;
		}
		if (SoketType == 2 || SoketType == 3 || SoketType == 4 || SoketType == 5 || SoketType == 6 || SoketType == 7 || SoketType == 8)
		{
			Socket = 1;
			goto LABEL_220;
		}
		result = 0;
		break;
	case 2:
		switch (SoketType)
		{
		case 1:
			if (SoketNumber == 2 || SoketNumber == 7 || SoketNumber == 12)
				Socket = 1;
			goto LABEL_220;
		case 9:
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
			Socket = 1;
			goto LABEL_220;
		case 2:
			Socket = 2;
			goto LABEL_220;
		}
		result = 0;
		break;
	case 3:
		switch (SoketType)
		{
		case 1:
			if (SoketNumber == 3 || SoketNumber == 8 || SoketNumber == 13)
				Socket = 1;
			goto LABEL_220;
		case 15:
		case 16:
		case 17:
		case 18:
		case 19:
			Socket = 1;
			goto LABEL_220;
		case 3:
		case 9:
			Socket = 2;
			goto LABEL_220;
		}
		result = 0;
		break;
	case 4:
		switch (SoketType)
		{
		case 1:
			if (SoketNumber == 3 || SoketNumber == 8 || SoketNumber == 13)
				Socket = 2;
			goto LABEL_220;
		case 20:
		case 21:
		case 22:
		case 23:
			Socket = 1;
			goto LABEL_220;
		case 4:
		case 10:
		case 15:
			Socket = 2;
			goto LABEL_220;
		}
		result = 0;
		break;
	case 5:
		switch (SoketType)
		{
		case 1:
			if (SoketNumber == 5 || SoketNumber == 10 || SoketNumber == 15)
				Socket = 1;
			goto LABEL_220;
		case 24:
		case 25:
		case 26:
			Socket = 1;
			goto LABEL_220;
		case 5:
		case 11:
		case 16:
		case 20:
			Socket = 2;
			goto LABEL_220;
		}
		result = 0;
		break;
	case 6:
		switch (SoketType)
		{
		case 1:
			if (SoketNumber == 5 || SoketNumber == 10 || SoketNumber == 15)
				Socket = 2;
			goto LABEL_220;
		case 27:
		case 28:
			Socket = 1;
			goto LABEL_220;
		case 6:
		case 12:
		case 17:
		case 21:
		case 24:
			Socket = 2;
			goto LABEL_220;
		}
		result = 0;
		break;
	case 7:
		switch (SoketType)
		{
		case 1:
			if (SoketNumber == 4 || SoketNumber == 9 || SoketNumber == 14)
				Socket = 1;
			goto LABEL_220;
		case 29:
			Socket = 1;
			goto LABEL_220;
		case 7:
		case 13:
		case 18:
		case 22:
		case 25:
		case 27:
			Socket = 2;
			goto LABEL_220;
		}
		result = 0;
		break;
	case 8:
		if (SoketType == 1)
		{
			if (SoketNumber == 4 || SoketNumber == 9 || SoketNumber == 14)
				Socket = 2;
			goto LABEL_220;
		}
		if (SoketType == 8 || SoketType == 14 || SoketType == 19 || SoketType == 23 || SoketType == 26 || SoketType == 28 || SoketType == 29)
		{
			Socket = 2;
			goto LABEL_220;
		}
		result = 0;
		break;
	case 11:
		if (SoketType == 1)
		{
			if (SoketNumber == 16 || SoketNumber == 25)
				Socket = 1;
			goto LABEL_220;
		}
		if (SoketType == 30)
		{
			Socket = 1;
			goto LABEL_220;
		}
		result = 0;
		break;
	case 12:
		if (SoketType == 1)
		{
			if (SoketNumber == 17 || SoketNumber == 26)
				Socket = 1;
			goto LABEL_220;
		}
		if (SoketType == 31)
		{
			Socket = 1;
			goto LABEL_220;
		}
		result = 0;
		break;
	case 13:
		if (SoketType == 1)
		{
			if (SoketNumber == 18 || SoketNumber == 27)
				Socket = 1;
			goto LABEL_220;
		}
		if (SoketType == 32)
		{
			Socket = 1;
			goto LABEL_220;
		}
		result = 0;
		break;
	case 14:
		if (SoketType == 1)
		{
			if (SoketNumber == 19 || SoketNumber == 28)
				Socket = 1;
			goto LABEL_220;
		}
		if (SoketType == 33)
		{
			Socket = 1;
			goto LABEL_220;
		}
		result = 0;
		break;
	case 15:
		if (SoketType == 1)
		{
			if (SoketNumber == 20 || SoketNumber == 29)
				Socket = 1;
			goto LABEL_220;
		}
		if (SoketType == 34)
		{
			Socket = 1;
			goto LABEL_220;
		}
		result = 0;
		break;
	case 16:
		if (SoketType == 1)
		{
			if (SoketNumber == 21 || SoketNumber == 30)
				Socket = 1;
			goto LABEL_220;
		}
		if (SoketType == 35)
		{
			Socket = 1;
			goto LABEL_220;
		}
		result = 0;
		break;
	case 17:
		
		if (SoketType == 1)
		{
			if (SoketNumber == 22 || SoketNumber == 31)
				Socket = 1;
			goto LABEL_220;
		}
		if (SoketType == 36)
		{
			Socket = 1;
			goto LABEL_220;
		}
		result = 0;
		break;
	case 18:
		if (SoketType == 1)
		{
			if (SoketNumber == 23 || SoketNumber == 32)
				Socket = 1;
			goto LABEL_220;
		}
		if (SoketType == 37)
		{
			Socket = 1;
			goto LABEL_220;
		}
		result = 0;
		break;
	case 19:
		if (SoketType == 1)
		{
			if (SoketNumber == 24 || SoketNumber == 33)
				Socket = 1;
			goto LABEL_220;
		}
		if (SoketType == 38)
		{
			Socket = 1;
			goto LABEL_220;
		}
		result = 0;
		break;
	case 20:
		if (SoketType == 39)
		{
			Socket = 1;
			goto LABEL_220;
		}
		if (SoketType == 43)
		{
			Socket = 1;
			goto LABEL_220;
		}
		result = 0;
		break;
	case 21:
		if (SoketType == 40)
		{
			Socket = 1;
			goto LABEL_220;
		}
		if (SoketType == 44)
		{
			Socket = 1;
			goto LABEL_220;
		}
		result = 0;
		break;
	case 22:
		if (SoketType == 41)
		{
			Socket = 1;
			goto LABEL_220;
		}
		if (SoketType == 45)
		{
			Socket = 1;
			goto LABEL_220;
		}
		result = 0;
		break;
	case 23:
		if (SoketType == 42)
		{
			Socket = 1;
			goto LABEL_220;
		}
		if (SoketType == 46)
		{
			Socket = 1;
			goto LABEL_220;
		}
		result = 0;
		break;
	default:
	LABEL_220:
		tSocket_Info = mSocket.Search(SoketType, SoketNumber);
		if (SoketType)
		{
			
			if (Socket == 1)
			{
				result = tSocket_Info->Stat1;
			}
			else if (Socket == 2)
			{
				result = tSocket_Info->Stat2;
			}
			else
			{
				result = 0;
			}
		}
		else
		{
			result = 0;
		}
		break;
	}
	return result;
}

int AVATAR_OBJECT::RefineSystem(int tSort)
{
	int tResult;
	switch (tSort)
	{
	case 1://Can ---- Yüzük
		tResult = 5 * mUTIL.ReturnIBValue(mUSER[mIndex].mAvatarInfo.aEquip[4][2]);
		if (mUTIL.ReturnIBValue(mUSER[mIndex].mAvatarInfo.aEquip[4][2]) == 25)
			tResult += 5;
		return tResult;
	case 2://Mana ----- Silah ve Zýrh
		tResult = 5 * mUTIL.ReturnIBValue(mUSER[mIndex].mAvatarInfo.aEquip[7][2]);
		if (mUTIL.ReturnIBValue(mUSER[mIndex].mAvatarInfo.aEquip[7][2]) == 25)
			tResult += 5;
		tResult = tResult + 5 * mUTIL.ReturnIBValue(mUSER[mIndex].mAvatarInfo.aEquip[2][2]);
		if (mUTIL.ReturnIBValue(mUSER[mIndex].mAvatarInfo.aEquip[2][2]) == 25)
			tResult += 5;
		return tResult;
	case 3://Saldýrý Gücü ------ Týlsým
		tResult = 5 * mUTIL.ReturnIBValue(mUSER[mIndex].mAvatarInfo.aEquip[0][2]);
		if (mUTIL.ReturnIBValue(mUSER[mIndex].mAvatarInfo.aEquip[0][2]) == 25)
			tResult += 5;
		return tResult;
	case 4://Defans ----- Pelerin, Bot ve Eldiven
		tResult = 5 * mUTIL.ReturnIBValue(mUSER[mIndex].mAvatarInfo.aEquip[3][2]);
		if (mUTIL.ReturnIBValue(mUSER[mIndex].mAvatarInfo.aEquip[3][2]) == 25)
			tResult += 5;
		tResult = tResult + 5 * mUTIL.ReturnIBValue(mUSER[mIndex].mAvatarInfo.aEquip[5][2]);
		if (mUTIL.ReturnIBValue(mUSER[mIndex].mAvatarInfo.aEquip[5][2]) == 25)
			tResult += 5;
		tResult = tResult + 5 * mUTIL.ReturnIBValue(mUSER[mIndex].mAvatarInfo.aEquip[1][2]);
		if (mUTIL.ReturnIBValue(mUSER[mIndex].mAvatarInfo.aEquip[1][2]) == 25)
			tResult += 5;
		return tResult;
	case 6://Critik Hasar ----- Silah
		tResult = mUTIL.ReturnIBValue(mUSER[mIndex].mAvatarInfo.aEquip[7][2]);
		return tResult;
	case 7://Kritik Defans ---- Pelerin
		tResult = mUTIL.ReturnIBValue(mUSER[mIndex].mAvatarInfo.aEquip[1][2]);
		return tResult;
	default:
		return 0;
	}
}