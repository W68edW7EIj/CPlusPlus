#ifndef DECFUNCTION_H
#define DECFUNCTION_H

#include <string>
// #include <iostream>

void func(int a);
void func(int a2, std::string b2);
void func(int a3, std::string b3, float c3);
// int func(int a);
// float func(int a);
// 报错: 无法重载仅按返回类型区分的函数
int func(double a);

#endif