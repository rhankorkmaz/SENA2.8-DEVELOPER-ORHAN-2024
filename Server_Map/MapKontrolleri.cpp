#include "Shengming.h"

int AVATAR_OBJECT::LabirentKontrolu(void)
{
    int result;

    switch (mSERVER_INFO.mServerNumber)
    {
    case 19:
    case 20:
    case 21:
    case 34:
    case 49:
    case 120:
    case 154:
    case 175:
    case 176:
    case 177:
    case 190:
    case 191:
    case 192:
    case 193:
        result = 1;
        break;
    default:
        result = 0;
        break;
    }
    return result;
}
int AVATAR_OBJECT::KarakolKontrolu(void)
{
    int result;

    if (mSERVER_INFO.mServerNumber > 122)
    {
        switch (mSERVER_INFO.mServerNumber)
        {
        case 146:
        case 147:
        case 148:
        case 149:
        case 150:
        case 151:
        case 152:
        case 153:
        case 154:
        case 155:
        case 156:
        case 157:
        case 158:
        case 159:
        case 160:
        case 161:
        case 162:
        case 163:
        case 164:
        case 295:
        case 296:
        case 319:
        case 320:
        case 321:
        case 322:
        case 323:
            result = 1;
            return result;
        }
    }
    if (mSERVER_INFO.mServerNumber == 250 || (mSERVER_INFO.mServerNumber > 266 && mSERVER_INFO.mServerNumber <= 269))
    {
        return 1;
    }
    if (mSERVER_INFO.mServerNumber == 120 || mSERVER_INFO.mServerNumber == 121 || mSERVER_INFO.mServerNumber == 122 || mSERVER_INFO.mServerNumber == 49 || mSERVER_INFO.mServerNumber == 51 || mSERVER_INFO.mServerNumber == 53)
    result = 1;
    else
    result = 0;
    return result;
}
