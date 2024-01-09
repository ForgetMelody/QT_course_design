#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <iostream>
#include <cmath>
#include <stack>
#include <QString>
#include <qmath.h>
using namespace std;

class Calculator
{
public:
    // 数值部分
    double Num[2];
    // 小数缩放
    bool afterPoint[2];
    double scale[2];
    // 是否负数
    int IsNeg[2];
    // 操作数的下标
    int Index;
    double result;
    int maxPrec;    // 最大小数点位数
    QString Opflag; // + - * / .....
    std::string inputexpression;

    Calculator();
    ~Calculator() = default;
    // * EditNum function performs editing operations on a number.
    // *
    // * @param input A QString representing the input value.
    // *
    // * @return void
    // *
    // * @throws None
    void EditNum(QString input);

    // 输入双目运算符
    void EditOp(QString input);
    // 进行计算
    void doCalculation();

    // 计算小数点位数
    int getScale(double input);
};

#endif