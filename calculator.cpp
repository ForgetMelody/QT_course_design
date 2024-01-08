#include <calculator.h>

Calculator::Calculator()
{
    // init
    Num[0] = 0;
    Num[1] = 0;
    IsNeg[0] = 1;
    IsNeg[1] = 1;
    scale[0] = 1;
    scale[1] = 1;
    afterPoint[0] = false;
    afterPoint[0] = false;
    Index = 0;
    result = 0;
    inputexpression = "";
}
void Calculator::EditNum(QString input)
{
    bool isNum;
    double in = input.toDouble(&isNum);

    if (isNum)
    {
        // 数字输入
        if (!afterPoint[Index])
        {
            // 小数点之前
            Num[Index] = Num[Index] * 10 + IsNeg[Index] * in;
        }

        else
        {
            // 小数点之后
            scale[Index] *= 0.1;
            Num[Index] += IsNeg[Index] * in * scale[Index];
        }
    }
    // 字母
    else if (input == "π")
    {
        Num[Index] *= M_PI;
    }
    else if (input == "e" || input == "E")
    {
        Num[Index] *= M_E;
    }
    else if (input == ".")
    {
        afterPoint[Index] = true;
    }
    // 清除当前数值
    else if (input == "C")
    {
        Num[Index] = 0;
        scale[Index] = 1;
        afterPoint[Index] = false;
        IsNeg[Index] = 1;
    }
    // 清除所有数值
    else if (input == "CE")
    {
        Num[0] = 0;
        Num[1] = 0;
        scale[0] = 1;
        scale[1] = 1;
        IsNeg[0] = false;
        IsNeg[1] = false;
        Index = 0;
    }
    else if (input == "DEL")
    {
        if (scale[Index] < 1)
        {
            scale[Index] *= 10;
            Num[Index] -= fmod(Num[Index], scale[Index]);
        }
        else
        {
            if (afterPoint[Index])
            {
                afterPoint[Index] = false;
            }
            Num[Index] -= int(Num[Index]) % 10;
            Num[Index] /= 10;
        }
    }
    else if (input == "±")
    {
        IsNeg[Index] *= -1;
        Num[Index] *= -1;
    }
}