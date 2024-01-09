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
    maxPrec = 10;
    inputexpression = "";
}
/**
 * EditNum function performs editing operations on a number.
 *
 * @param input A QString representing the input value.
 *
 * @return void
 *
 * @throws None
 */
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
        IsNeg[0] = 1;
        IsNeg[1] = 1;
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

void Calculator::EditOp(QString input)
{
    // 更改编辑操作数
    if (Index == 0)
    {
        // 记录运算符
        Opflag = input;
        Index = 1;
    }
    else if (Index == 1)
    {
        // 连续运算
        doCalculation();

        Opflag = input;
        // 重新记录Num{1}
        Index = 1;
    }
}
void Calculator::doCalculation()
{
    if (Opflag == "+")
    {
        result = Num[0] + Num[1];
    }
    else if (Opflag == "-")
    {
        result = Num[0] - Num[1];
    }
    else if (Opflag == "×")
    {
        result = Num[0] * Num[1];
    }
    else if (Opflag == "÷")
    {
        result = Num[0] / Num[1];
    }

    // 将运算结果存入Num[0]
    Num[0] = result;
    qDebug() << "result: " << result;
    // 更新运算结果信息
    if (result >= 0)
        IsNeg[0] = 1;
    else
        IsNeg[0] = -1;
    if (int(Num[0]) == Num[0])
        afterPoint[0] = false;
    else
    {
        afterPoint[0] = true;
        // 判断Num[0]有多少位小数,并更新到scale[0]
        scale[0] = pow(10, -getScale(Num[0]));
    }
    // 重新记录Num{1}
    Num[1] = 0;
    scale[1] = 1;
    afterPoint[1] = false;
    IsNeg[1] = 1;
    Index = 0;
}

int Calculator::getScale(double input)
{
    // 计算小数点位数
    int n = 0;
    // qDebug() << "scale: " << c.scale[c.Index];
    while (input != int(input))
    {
        n++;
        input *= 10;
        if (n >= maxPrec)
            break;
    }
    return n;
}