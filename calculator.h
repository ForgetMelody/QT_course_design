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
    std::string inputexpression;

    Calculator();
    ~Calculator() = default;
    void EditNum(QString input);
};

#endif