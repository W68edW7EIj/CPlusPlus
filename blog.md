

>下载练习册题面以及想要拉到本地跑代码可以去 [CPlus 仓库](https://github.com/ceilf6/CPlusPlus)
或者终端输入命令
```
git clone https://github.com/ceilf6/CPlusPlus
```
> 如果翻不了墙也可以用国内平替 [CPlus 仓库（国内）](https://gitee.com/ceilf6/SHU_CPlus)
# README
> ⚠️ 由于时间紧迫，这是我在回校后一周内同时复习多门课程、抽空完成的，如有不合理之处，欢迎随时交流，或直接在仓库提 Issue / PR。
```
## 🧠 关于算法的一些浅见（快速入门向）

算法是基于计算机思想对数据进行管理和高效操作的艺术。它往往源于我们对问题结构的观察和抽象：

- **分治思想** → 催生了归并排序、快速排序等；
- **树形结构** → 发展出了深度优先搜索（DFS）、字典树、线段树等；
- **懒更新** → 解决了高频动态区间修改的问题（如线段树懒标记）；
- **重叠子问题** → 促成了动态规划，借助状态转移 + 递归回溯降低复杂度。

💬 顺带一提：  
算法思想也广泛应用于其他领域。例如在前端开发中，理解"树形结构"的逻辑，可以：

- 清晰描述 UI 组件的层级关系；
- 在"分叉节点"复用公共组件；
- 通过 `props` 注入差异化逻辑，实现**高度复用**和**低耦合工程**。

---

## 🤝 一起进步！

欢迎各位大佬一起探讨与交流，互相学习，持续成长 🚀  
👉 有问题随时提 Issue，或者发起 PR～

---

> 在做完算法册题目后我发现本门课更加注重对 C++ 基础特性的把握以及工程化中的安全实践，对同学们后面工作有很大帮助
```
# Ex01
```cpp
// 仓库地址：https://github.com/ceilf6/CPlusPlus

#include <iostream> // 导入输入输出数据流
#include <string>

// #include<bits/stdc++.h>
// 上面两行还可以用万能头进行替换，优点是不需要记忆各个功能需要的库的名称，但是缺点有不是C++的标准头文件、编译速度慢

using namespace std; // 使用std的命名空间（不使用也可以，就是下面得用std::cout、std::cin，比较麻烦
void bonjour()
{
    cout << "输入您的名字";             // 输入
    string name;                        // 定义变量类型
    cin >> name;                        // 输入
    cout << "bonjour " << name << '\n'; // 格式化输出
}

int main()
{ // 主函数调用上面定义的功能函数实现模块化区分、代码的松耦合
    bonjour();
    return 0;
}
```


# Ex02
```cpp
/*
感觉算法这门课主要的难点在于理解法语题面doge

这道题主要的意思是在前一个文件的基础上添加一个头文件
然后将文件填入头文件
会发现语法错误
因为C++的头文件是用于被导入到使用文件中为使用文件规范类型、枚举，声明函数等等
（有点像TS）
所以C++的头文件本质还是需要用C++去写（也可以兼容 extend "C"）
如果用自然语言就会报错
*/```


# Ex03
```cpp
/*
这道题目是用于进一步理解C++的工程文件架构的以及C++作为编译静态语言的编译特性
首先按照题目的要求创建项目并进行编译会报错无法找到bonjour这个文件 error: use of undeclared identifier 'function'
因为从主main.cpp入口进入后直接运行了bonjour但是并没有引入这个文件的声明

改正方案有两种:（可以看Ex03文件夹）
- 1.直接在main.cpp上面声明 void function(); 即可
- 2.通过自定义头文件 decFunction.h 中统一进行声明管理，然后在 main.cpp 中进行导入即可
    （有点像一个文件夹中通过多个小文件去实现一个个功能函数，然后设置一个 index 去统一进行导出管理）

下面通过C++的编译过程理解是为什么：
1. 预处理阶段：从主头main进入后会查看有哪些声明，然后通过这些声明稍后在链接阶段去其他文件中寻找
    #include 就是相当于将整个文件拷贝过来，所以推荐的方法是写一个统一声明管理的头文件后导入
2. 编译阶段：将每个 .cpp 文件进行独立编译
3. 链接阶段：根据预处理阶段的”我需要...函数“的引用，当前项目中 -> 静态库 -> 动态库 中去寻找（所以是有优先级的）
*/
```


# Ex03 文件夹
## decFunction.h
```h
#ifndef DECFUNCTION_H // 命名规范：大写化头文件名称
#define DECFUNCTION_H
// 头文件保护，用于头文件其他文件被多次导入时不会重复声明

void function();

#endif
```

## function.cpp
```cpp
#include<iostream>
using namespace std;

void function(){
    cout<<"成功调用函数"<<endl;
}
```

## main.cpp
```cpp
// void function();
#include "decFunction.h"

int main(){
    function();
    return 0;
}
```


# Ex04
```cpp
/*
题目的意思是在 A.h 中引用 B.h ，然后又在 B.h 中引用 A.h
这会导致循环引用的问题
因为在C++的预处理阶段中#include是 纯文本替换 ，所以会无限展开
（像JS、py这些动态语言在执行循环导入的报错是导入未完全、导入时模块体还未执行完全）
*/
```


# Ex05
```cpp
/*
reecrire re-ecrire 重新写
ne faisant appel. qu’aux nouvelles possibilites d’entrees-sorties du C++ : 只使用 C++ 的新输入输出功能
使用 const 定义常量而不是 #define
*/

#include <iostream>

constexpr double PI = 3.14159;
// constexpr指编译期已知，可以直接在编译期使用，而不用像const得在运行时去内存里面拿，比const性能更优

void calculateCircle()
{
    std::cout << "请输入圆的半径: ";
    double r;

    if (!(std::cin >> r) || r < 0)
    {
        std::cout << "输入错误！半径必须为非负数。" << std::endl;
        return;
    }

    double circumference = 2 * PI * r;
    // double area = PI * r * r;
    double area = PI * std::pow(r, 2);

    std::cout << "圆的周长: " << circumference << '\n';
    std::cout << "圆的面积: " << area << '\n';
}

int main()
{
    calculateCircle();
    return 0;
}
```


# Ex06
```cpp
#include <iostream>

int main()
{
    double x = 3.14;
    std::cout << x << std::endl;
    double y;
    std::cout << y << std::endl;
    y = 3.14;
    std::cout << y << std::endl;
    return 0;
}

/*
这道题是用于区分 声明、定义、初始化、赋值
声明用于告诉编译器这个该变量存在且其类型是什么，方便在内存中开一片区域
像局部变量的定义就不会给初始值，但是如果是全局的话编辑器会默认初始化为0
初始化就是在声明的时候通过 = 赋值符号给其一个初值
但是也不一定需要在声明的时候赋初值，也可以先声明在后面再调用这个变量进行赋值
注意如果在一个变量没有值之前去cout输出，就会输出随机数，例如这块内存可能残留着之前程序或操作系统的数据
*/
```


# Ex07
```cpp
/*
这道题目是教学常量不可变：
一旦你声明前有 const 的时候如果后面想尝试对该变量赋值就会报错，一般用于编译器的性能优化
（插一嘴：一般常量命名用大写规则，这样其他仓库管理者就知道这是个常量了）
 */

int main()
{
    const double PI = 3.14;
    // PI = 314;
    return 0;
}
```


# Ex08
```cpp
/*
这道题主要展示了命名空间的用途：随着仓库的越来越大、模块越来越多，
命名相同的情况可能会发生，例如 py 的不同库中可能有相同名称的方法，py是通过 库名. 进行区分，
还有常见的通过详细命名、大驼峰小驼峰等方式去区分，
但是C++中有namespace就允许了同名，和py的 类. 相似的通过 :: 进行引用从而区分
详情请看Ex08文件夹:
- decFunction.h 头文件声明
- function.cpp 函数实现文件
- main.cpp 主逻辑、调用文件
*/```


# Ex08 文件夹
## decFunction.h
```h
#ifndef DECFUNCTION_H
#define DECFUNCTION_H

#include <iostream> // 用于各个子成员，在这里统一导入就不用一个个去写了

namespace French
{
    void sayhi();
}

namespace China
{
    void sayhi();
}

namespace English
{
    void sayhi();
}

#endif```

## function.cpp
```cpp
#include "decFunction.h"
// 导入头文件中的命名空间用于区分，并且iostream也是在头文件统一导入了

void French::sayhi()
{
    std::cout << "bonjour" << std::endl;
}

void English::sayhi()
{
    std::cout << "hi" << std::endl;
}

void China::sayhi()
{
    std::cout << "你好" << std::endl;
}```

## main.cpp
```cpp
#include "decFunction.h"
// 只需要导入包含声明的头文件即可，至于实现部分到时候编译器自己会去找（但是别忘记编译实现的function文件）

int main()
{
    French::sayhi();
    English::sayhi();
    China::sayhi();
    return 0;
}
```


# Ex09
```cpp
/*
这道题主要考察了重载、内联函数

- 在编译期处理哪个函数签名最匹配
- 重载：同名但是不同参数列表（返回类型不参与、形参顶层的const不参与）
    - 编译器内部对重载的解析：
        - 1. 候选集：找到所有同名函数;
        - 2. 可行集：能通过隐式转换把实参转换为形参的函数
        - 3. 最佳可行函数：比较每个参数的转换“优劣”，选整体更优的那个；若无唯一更优 => 二义性报错
    - 优劣排序：
        - 1. 精准匹配：类型完全相同、或仅限底层cv的调整
        - 2. 提升：
            - a. 提升整型：bool/char/signed char/unsigned char/short => int（或 unsigned int）
            - b. 提升浮点：float => double
        - 3. 转换：int <=> float、double => float、double => int、unsigned <=> signed、派生 => 基类等
    - 消歧修正：
        - 1. 显式类型转换：调用 (float)i 等
        - 2. 添加后缀字面量：如 3.0f （有点像TS里的 i as float )

- 如果在需要将函数体写在头文件中，而且这个头文件被多次导入，那么由于 include 会相当于嵌入代码会导致在链接期头文件中函数体被多次定义
- 为了处理 ODR（One Definition Rule）：
    - !Important: 最推荐的做法就是在功能头文件中写函数声明，将功能函数的函数体在单独的 cpp 中实现，那么其他地方要使用的时候只需要导入这个功能函数的声明头文件、相当于使用的是同一个
    - 1. 头文件static：（有点像闭包、类里面的静态私有函数）只能在定义其文件内部使用，控制了作用域，各 TU 各有一份函数体；可避免重定义，但可能导致重复代码
    // - 2. 宏 #define：无类型/作用域检查，不要用来替代函数；inline 是更安全的宏替代品
    // - 3. constexpr：隐含 inline；要求函数在编译期可求值（满足限制）
    - 4. inline 内联：编译器会将内联函数的代码直接插入到调用点，避免函数调用的压栈、跳转、返回等操作（比如 DFS 不当常常会导致爆栈，但是递归也没法用inline会导致代码膨胀的问题，可以通过自己维护栈显式使用来优化）

详细内容看 Ex9 文件夹
*/```


# Ex09 文件夹
## decFunction.h
```h
// #ifndef DECFUNCTION_H
// #define DECFUNCTION_H

// #include <string>
// // #include <iostream>

// void func(int a);
// void func(int a2, std::string b2);
// void func(int a3, std::string b3, float c3);
// // int func(int a);
// // float func(int a);
// // 报错: 无法重载仅按返回类型区分的函数，因为返回类型不参与重载
// int func(double a);

// #endif

#ifndef DECFUNCTION_H
#define DECFUNCTION_H

#include <string>
#include <iostream>

inline void func(int a) // 注意inline必须要将函数体也一起写出来不能只是声明（因为到时候是直接粘贴过去的）
{
    std::cout << "成功调用函数1" << a << std::endl;
}

inline void func(int a2, std::string b2)
{
    std::cout << "成功调用函数2" << a2 << ' ' << b2 << std::endl;
}

inline void func(int a3, std::string b3, float c3)
{
    std::cout << "成功调用函数3" << a3 << ' ' << b3 << ' ' << c3 << std::endl;
}
// int func(int a);
// float func(int a);
// 报错: 无法重载仅按返回类型区分的函数，因为返回类型不参与重载

inline int func(double a)
{
    std::cout << "成功调用形参为double类型的参数" << a << std::endl;
}

#endif```

## usePlace2.h
```h
#ifndef USEPLACE2_H
#define USEPLACE2_H

int test();

#endif```

## functions.cpp
```cpp
/*

这是我首推的功能函数单独文件写法，为了展示 inline 就先注释掉了

#include <iostream>

void func(int A)
{
    std::cout << "成功调用函数1" << A << std::endl;
}

void func(int A2, std::string B2)
{
    std::cout << "成功调用函数2" << A2 << ' ' << B2 << std::endl;
}

void func(int A3, std::string B3, float C3)
{
    std::cout << "成功调用函数3" << A3 << ' ' << B3 << ' ' << C3 << std::endl;
}

int func(double A)
{
    std::cout << "成功调用形参为double类型的参数" << A << std::endl;
}
*/```

## main.cpp
```cpp
#include "decFunction.h"
#include "usePlace2.h"

int main()
{
    func(1);
    func(1, "2");
    func(1, "2", 3.0);
    func(1.0000000000000000000000); // 精准匹配优先级大于提升整型的优先级

    std::cout << '\n'
              << "尝试调用第二个使用相同头文件函数体的函数" << std::endl
              << '\n';

    test();

    return 0;
}```

## usePlace2.cpp
```cpp
#include "decFunction.h"
#include "usePlace2.h"

int test()
{
    func(12);
    func(12, "22");
    func(12, "22", 23.0);
    func(12.0000000000000000000000); // 精准匹配优先级大于提升整型的优先级
    return 0;
}

/*
如果没有在 dec头文件 中使用inline会发现报错:
1 warning generated.
duplicate symbol '_${函数名}' in:
    多个文件路径
ld: 1 duplicate symbol for architecture arm64
clang: error: linker command failed with exit code 1 (use -v to see invocation)
*/
```


# Ex10
```cpp
#include <iostream>

int main()
{
    /*
        * : 1. 声明指针;2. 解引用取值
        1. int* ptr; // 表示声明了一个指向整型类型的指针
        2. int value = *ptr; // 解指针拿到了 ptr 指针指向的值并赋值给另一个变量
    */
    /*
        & : 1. 声明引用;2. 取地址
        1. int& ref = var; // 声明了 ref 指向的和 var 同一个内存地址
        2. int* ptr = &ref; // ptr 指向的是变量 ref 的内存地址
    */

    double *pt0 = 0;              // 0 可以是 int,double,float,long,char,空指针：这里用到的就是 double 类型
    double *pt1;                  // = 4096; // 变量和指针的类型必须相同：4096是 int 类型
    double *pt2 = (double *)4096; // 将指针进行了显式转换。但这是危险的，如果解引用就会导致undefined行为
    void *pt3 = pt1;              // 任意对象类型的指针，都可以隐式转换给 void*
    // pt1 = pt3;                 // 但是 void* 类型赋给其他的必须进行显式转换：如下面一行
    pt1 = (double *)pt3;

    // const 类型 *ptr ：指针指向的值不能变
    // 类型 const *ptr ：和上面一样都是值不能变

    // 类型 * const ptr ：const紧接ptr - 指针为常量不能变

    double d1 = 36;
    const double d2 = 36;
    double *pt4 = &d1;
    const double *pt5 = &d1;
    std::cout << "--d1: " << d1 << std::endl;
    *pt4 = 2.1; // 通过 d1 的指针 pt4 来修改 d1 的值
    std::cout << "--d1: " << d1 << std::endl;
    // *pt5 = 2.1; // 上面加了 const 导致这个指针无法改变
    // pt4 = &d2; // 不能将值赋给指针变量
    pt5 = &d2;
    double *const pt6 = &d1;
    // pt6 = &d1; // 上面定义了不可变指针
    *pt6 = 2.78;
    // double *const pt6b = &d2; // 注意 pt6b 是指针不可变，但是 d2 是值不可变
    const double *const pt6b = &d2; // 自身更严格的可以指向（双const可指1const，1const可以指0const，但是1对1的时候就需要判断是否是同一个const）
    const double *const pt7 = &d1;
    // pt7 = &d1; // pt7的值和指针都不可变
    // *pt7 = 2.78;
    double const *pt8 = &d1; // 注意不是类型紧接，所以是值不能变
    pt8 = &d2;               // 都是值const
    pt8 = &d1;
    // *pt8 = 3.14;          // 值不能变

    return 0;
}
```


# Ex11
```cpp
#include <iostream>

int main()
{
    /*
    const引用：引用指向的值是常量
    const 类型& ref
    类型 const& ref
    */

    // double &d1 = 36; // 非 const 的引用不能被赋临时量（这里的36会被临时隐式转换double，但是生命周期马上到头所以不能被引用）
    double d2 = 36;
    double &ref = d2;
    std::cout << "--d2: " << ref << std::endl;
    ref = 4; // 不是 const 可以直接更改
    std::cout << "--d2: " << ref << std::endl;

    const double d3 = 36;
    const double &d4 = 36; // 这里的 36 的生命周期会被延长到 d4 的作用域结束
    const double &d5 = d2;
    // d5 = 21; // 无法更改 const
    const double &d6 = d3;
    // double &ref2 = d6; // 自身得更严格，d6为const那么左边也必须得const
    int i = 4;
    // double &d7 = i; // 在需要隐式类型转换的时候赋值给引用的是中间的临时变量，比如这里就是static_cast<double>(i)，那么就和上面的非 const 引用不能被赋值临时变量一样了
    const double &d7 = i; // const 类型的可以赋值临时变量/字面量，会产生临时对象并延长其生命周期
    const double &d8 = i;
    // d8 = 3; // const了

    return 0;
}
```


# Ex12 文件夹
## dec.h
```h
#ifndef DEC_H
#define DEC_H

void inverseByPtr(int *a, int *b);
void inverseByRef(int &a, int &b);

#endif
```

## functions.cpp
```cpp
#include <iostream>

// 利用地址或者引用、通过中间变量或者解构等方法进行交换
// 如果不用地址或引用而是直接传(int a,int b)会导致传入的只是a和b的值拷贝，无法改变内存层面的值
// 而像python、JS、Java这些语言不需要指针也能成功改变的原因是这些语言封了一层使得传入的其实是一个引用对象，那么使用者就不需要考虑内存的细节了
// 但正是因为 C++ 的颗粒度小所以在性能上非常有优势，且会避免语言开发者出于好意的封装导致的使用者在调用API时被无意篡改了数据

void inverseByPtr(int *a, int *b)
{
    std::cout << "指针传递前a,b值: " << *a << ',' << *b << std::endl;
    int temp = *a;
    *a = *b;
    *b = temp;
    std::cout << "指针传递后a,b值: " << *a << ',' << *b << std::endl;
}
void inverseByRef(int &a, int &b)
{
    std::cout << "引用传递前a,b值: " << a << ',' << b << std::endl;
    // int temp = a;
    // a = b;
    // b = temp;
    std::tie(a, b) = std::make_tuple(b, a); // 通过元组解构的方式
    std::cout << "引用传递后a,b值: " << a << ',' << b << std::endl;
}
```

## main.cpp
```cpp
#include "dec.h"

int main()
{
    int A = 100;
    int B = -100;

    int *strA = &A;
    int *strB = &B;

    int &refA = A;
    int &refB = B;

    inverseByPtr(strA, strB);
    inverseByRef(refA, refB);

    return 0;
}
```


# Ex12
```cpp
// 题目要求用 指针传递 和 引用传递 两种方式交换两个变量的值
// 详情见 Ex12 文件夹
```


# Ex13
```cpp
#include <iostream>
/*
题面：编写一个名为raz的函数，用于将传入参数中的此类结构体中两个字段重置为零。
使用地址参数执行一次，使用引用参数执行一次。在这两种情况下，都需要编写一个简单的函数测试程序。该程序在调用此函数后会显示此类结构体的值
*/

struct essai
{
    int n;
    float x;
};

// 利用重载性质（虽然在其他语言中最好是通过详细名字区分函数，但是C++可以利用重载自动分流优化性能）
/**
 * 此处是函数说明，用于仓库代码的维护，本课程不需要，但是工程化最好多注明方便他人进一步贡献
 * @brief Reset fields of essai to zero (pass by address)
 * @param e Pointer to essai struct
 */
void raz(struct essai *e) noexcept // noexcept 是为了防止处理 const 的时候编译抛错误
{
    // 拿到结构体指针需要先解引用再拿元素值 (*p).n ，那么有一个等价语法糖就是 p->n （如果是引用的话就像下面一样直接 . 去拿即可）
    e->n = 0;
    e->x = 0.0f; // 给 float 加 f 否则数字默认是 double 会有一次隐式转换
}
/**
 * @brief Reset fields of essai to zero (pass by reference)
 * @param e Reference to essai struct
 */
void raz(struct essai &e) noexcept
{
    e.n = 0;
    e.x = 0.0f;
}

int main()
{
    essai E{100, -100.0f};
    std::cout << "--通过指针重置前对象中的n,x值:" << E.n << ',' << E.x << std::endl;
    raz(&E);
    std::cout << "--通过指针重置后对象中的n,x值:" << E.n << ',' << E.x << std::endl;

    // ----------
    E = {-100, 100.0f}; // 等价于下面两句
    // E.n = -100;
    // E.x = 100.0f;
    std::cout << "--通过引用重置前对象中的n,x值:" << E.n << ',' << E.x << std::endl;
    raz(E);
    std::cout << "--通过引用重置后对象中的n,x值:" << E.n << ',' << E.x << std::endl;

    return 0;
}
```


# Ex14 文件夹
## dec.h
```h
#ifndef DEC_H
#define DEC_H

// #include <optional>

struct point
{
    int x;
    int y;
    int z;

    // 默认构造函数（不写也默认）
    point() : x(0), y(0), z(0) {}

    // 可选参数构造函数
    point(int xVal, int yVal = 0, int zVal = 0)
        : x(xVal), y(yVal), z(zVal) {}

    // 法2: 通过成员函数：重置
    void reset(int a = 0, int b = 0, int c = 0)
    {
        x = a;
        y = b;
        z = c;
    }
};

// 法1: 这道题想要实现多参数的初始化，第一想法就是通过可选参数，像JS中可以直接通过 ?: 来实现，
// C++的话可以通过设置默认参数来降级实现，或者利用 std::optional 来实现（注意需要 C++17 up）
// void init(point *p, std::optional<int> x = std::nullopt, std::optional<int> y = std::nullopt, std::optional<int> z = std::nullopt);
void init(point *p, int x = 0, int y = 0, int z = 0) noexcept;

#endif
```

## init.cpp
```cpp
#include "dec.h"

void init(point *p, int x, int y, int z) noexcept // 注意在声明的时候写了默认参数后在定义不需要再写一遍
{
    p->x = x;
    p->y = y;
    p->z = z;
}
```

## main.cpp
```cpp
#include "dec.h"
#include <iostream>

int main()
{
    point p{100, 200, 300};
    std::cout << "--重置x为1000前x,y,z值: " << p.x << ',' << p.y << ',' << p.z << std::endl;
    init(&p, 1000);
    std::cout << "--重置后x,y,z值: " << p.x << ',' << p.y << ',' << p.z << std::endl;
    std::cout << '\n';

    p = {100, 200, 300};
    std::cout << "--重置x为1000、y为2000前x,y,z值: " << p.x << ',' << p.y << ',' << p.z << std::endl;
    init(&p, 1000, 2000);
    std::cout << "--重置后x,y,z值: " << p.x << ',' << p.y << ',' << p.z << std::endl;
    std::cout << '\n';

    p = {100, 200, 300};
    std::cout << "--重置x为1000、y为2000、z为3000前x,y,z值: " << p.x << ',' << p.y << ',' << p.z << std::endl;
    init(&p, 1000, 2000, 3000);
    std::cout << "--重置后x,y,z值: " << p.x << ',' << p.y << ',' << p.z << std::endl;
    std::cout << '\n';

    //----------------
    point p2(100, 200, 300);
    std::cout << "--法2通过成员函数重置x为1000、y为2000、z为3000前x,y,z值: " << p2.x << ',' << p2.y << ',' << p2.z << std::endl;
    p2.reset(1000, 2000, 3000);
    std::cout << "--重置后x,y,z值: " << p2.x << ',' << p2.y << ',' << p2.z << std::endl;

    return 0;
}
```


# Ex14
```cpp
/*
这道题主要考察多参数的结构体重置，详情看 Ex14 文件夹
*/
```


# Ex15
```cpp
#include <iostream>

/*
考察内存管理
C++中 new 只需要知道类型，不需要sizeof去拿到内存该类型的大小再告知 malloc；清理的话从 C 的 free 变成了 delete（如果是数组的话还得加上[]）
*/

void essai_alloc()
{
    int *pt_int = new int;
    double *pt_double = new double[100];

    pt_double[0] = 1.0;
    pt_double[1] = 2.0;
    std::cout << "--删除前数组内容" << *pt_double << std::endl;

    delete pt_int;
    delete[] pt_double;

    // 上面 delete 悬空后下面输出的是存残留位模式按 double 解释产生的“垃圾值”
    std::cout << "--删除后数组内容" << *pt_double << std::endl;
}

int main()
{
    essai_alloc();

    return 0;
}
```


# Ex16
```cpp
#include <stdio.h>
#include <iostream> // 性能比stdio更佳但是格式化比较麻烦
struct personne
{
    char nom[30];
    unsigned int age;
};

void raz(struct personne *p)
{
    p->nom[0] = '\0'; // 直接在字符串数组第一个设置终止符号即可优雅清空
    p->age = 0;
}

void affiche_struct(const struct personne *p)
{
    // if (p->nom[0] != '\0')
    // {
    printf("Nom : %s, Age : %u\n", p->nom, p->age);
    // }
    // else
    // {
    //     printf("Nom : Null, Age : %u\n", p->age);
    // }
}

void affiche_tab(const struct personne *p, int n = -1) // 传p[]会自动退化为指向首元素的指针
{
    if (n == -1)
    {
        // n = sizeof(*p); 这样拿到的只是首元素的大小，C++无法推测数组的结束（除非用 vector 或者有标识符）
        std::cout << "请传入数组长度" << std::endl;
    }
    for (int i = 0; i < n; i++)
    {
        affiche_struct(&p[i]);
    }
}

// 这个函数也可以直接写在 struct 里面作为构造函数（函数名必须要和结构体名相同，而且注意设置默认值）
void init_struct(struct personne *p, const char *name, unsigned int age)
{
    // 题目要求不能用 strcpy 函数，且字符串是用 char[] 就只能一个个循环过去迁移
    int i = 0;
    while (name[i] != '\0' && i < 29)
    {
        p->nom[i] = name[i];
        i++;
    }
    p->nom[i] = '\0';
    p->age = age;
}

void copy_struct(const struct personne *src, struct personne *dest)
{
    // 由于用的 char[] 所以得解构赋值，string 的话直接 = 即可
    int i = 0;
    while (src->nom[i] != '\0' && i < 29)
    {
        dest->nom[i] = src->nom[i];
        i++;
    }
    dest->nom[i] = '\0';
    dest->age = src->age;
}

void copy_tab(const struct personne *src, struct personne *dest, int n)
{
    for (int i = 0; i < n; i++)
    {
        copy_struct(&src[i], &dest[i]);
    }
}

int main()
{
    struct personne a, b;
    struct personne tab1[2];
    struct personne tab2[2];

    init_struct(&a, "Alice", 20);
    init_struct(&b, "Bob", 25);

    printf("== init_struct + affiche_struct ==\n");
    affiche_struct(&a);
    affiche_struct(&b);

    printf("\n== raz ==\n");
    raz(&a);
    affiche_struct(&a);

    init_struct(&tab1[0], "Charlie", 22);
    init_struct(&tab1[1], "David", 30);

    printf("\n== affiche_tab ==\n");
    affiche_tab(tab1, 2);

    printf("\n== copy_tab ==\n");
    copy_tab(tab1, tab2, 2);
    affiche_tab(tab2, 2);
}
```


# Ex17
```cpp
#include <string>
#include <iostream>

// 题目要求在 16 的基础上用更优雅的 string，且我进一步用 16 中提到的内置函数写法，如果不习惯的只需要将 16 中的 char 都替换为 std::string 即可，同时不需要循环赋值字符串、直接 = 即可,以及字符串的清除 clear() API

struct personne
{
    std::string nom;
    unsigned int age;

    // 默认构造 + 带参构造
    personne(const std::string &name = "", unsigned int a = 0)
        : nom(name), age(a) {}

    // 清空
    void raz()
    {
        nom.clear(); //
        age = 0;
    }

    // 输出自身信息
    void affiche() const
    {
        std::cout << "Nom : " << nom << ", Age : " << age << std::endl;
    }
};

// 打印数组
void affiche_tab(const personne *p, int n)
{
    for (int i = 0; i < n; i++)
        p[i].affiche();
}

// 复制数组
void copy_tab(const personne *src, personne *dest, int n)
{
    for (int i = 0; i < n; i++)
        dest[i] = src[i];
}

int main()
{
    personne a("Alice", 20);
    personne b("Bob", 25);

    std::cout << "== constructeur + affiche ==\n";
    a.affiche();
    b.affiche();

    std::cout << "\n== raz ==\n";
    a.raz();
    a.affiche();

    personne tab1[2] = {personne("Charlie", 22), personne("David", 30)};
    personne tab2[2];

    std::cout << "\n== affiche_tab ==\n";
    affiche_tab(tab1, 2);

    std::cout << "\n== copy_tab ==\n";
    copy_tab(tab1, tab2, 2);
    affiche_tab(tab2, 2);

    return 0;
}```


# Ex17Pro 文件夹
## Person.hpp
```h
#ifndef PERSON_HPP
#define PERSON_HPP

#include <string>
#include <iostream>

// 个体管理

class Person
{
private:
    std::string name_; // 变量名后加 _ 用于表示这是类的成员变量（防止重名）
    unsigned int age_;

public:
    Person(std::string name = "", unsigned int age = 0)
        : name_(std::move(name)), age_(age) {}

    // 由于本代码中的成员属性是私有的，而外部需要打印，就像外暴露 getter 函数
    const std::string &name() const { return name_; } // 通过 const 确保安全性
    unsigned int age() const { return age_; }

    void reset()
    {
        name_.clear(); // string 直接 clear 即可
        age_ = 0;
    }

    // 重载运算符：operator加运算符
    friend std::ostream &operator<<(std::ostream &os, const Person &p) // os以非常量引用接受输出流
    // friend 表示该函数是类的朋友就能直接访问类的私有成员了
    {
        return os << p.name_ << " (" << p.age_ << ")";
        // 利用重载输出运算直接返回数据流，调用该函数的时候直接接到 std::cout 上即可
    }
};

#endif```

## PersonManager.hpp
```h
#ifndef PERSONMANAGER_HPP
#define PERSONMANAGER_HPP

#include "Person.hpp"
#include <vector>

// 多个体数组管理

class PersonManager
{
private:
    std::vector<Person> persons_;

public:
    // 如果插入已有对象用 push_back ；直接传参数用 emplace_back
    void add(const Person &p)
    {
        persons_.push_back(p); // vector 用 push_back 动态管理数组
    }

    template <typename... Args>  // 可变参数模版，表示可以接受任意数量、任意类型的参数
    void emplace(Args &&...args) // &&是万能引用，... 和JS一样都用于展开
    {
        persons_.emplace_back(std::forward<Args>(args)...);
        /*
        emplace_back 是vector更高效的插入方式，
        直接在容器内部原地构造对象，而不是先构造一个对象再移动进去
        */
    }

    void clear()
    {
        persons_.clear();
    }

    void print() const
    {
        if (!persons_.size())
        {
            std::cout << "== Null == NoBody ==" << std::endl;
            return;
        }
        for (const auto &p : persons_)
        {
            std::cout << p << std::endl;
        }
    }
};

#endif```

## main.cpp
```cpp
#include "PersonManager.hpp"

int main()
{
    PersonManager pm;

    pm.emplace("Alice", 20);
    pm.emplace("Bob", 25);
    pm.add(Person("Bobby", 100));

    std::cout << "== People List ==" << std::endl;
    pm.print();

    std::cout << "\n== After reset ==" << std::endl;
    pm.clear();
    pm.print();

    return 0;
}
```


# Ex17Pro
```cpp
/*
选看
但是 17 还是不够优雅和现在，
最好是用 vector 并结合 面向对象OOP 范式，将数据 & 行为一体化
详情请看 Ex17Pro 文件夹
*/
```


# Ex18
```cpp
#include <string>
#include <iostream>
struct compte
{
    std::string id;
    int solde;
};

// 注意函数得返回引用 & 否则后续不能对返回进行操作
int &operation(struct compte *p, std::string id, int n)
{
    for (int i = 0; i < n; i++) // 题目要求，否则用 map + contains 判断更快
        if (p[i].id == id)
            return p[i].solde; // 当函数签名有 & 时返回数组[i]是直接返回的引用
                               // 函数内部不需要操作，直接返回就好

    throw std::runtime_error("Not found!");
};

int main()
{
    compte tab[4] = {{"courant", 0}, {"codevi", 1500}, {"epargne", 200}, {"cel", 300}};
    std::cout << "== 操作前各账户数据 ==\n";
    for (int i = 0; i < 4; i++)
        std::cout << tab[i].id << " : " << tab[i].solde << "\n";

    operation(tab, "courant", 4) = 100; // courant 账户余额设为 100
    operation(tab, "codevi", 4) += 100; // codevi 账户余额 +100
    operation(tab, "cel", 4) -= 50;     // cel 账户余额 -50

    std::cout << "\n== 操作后各账户数据 ==\n";
    for (int i = 0; i < 4; i++)
        std::cout << tab[i].id << " : " << tab[i].solde << "\n";

    std::cout << "\n== 尝试不存在的key ==\n";
    operation(tab, "ceilf6", 4) += 10000;
    std::cout << "\n== 操作后各账户数据 ==\n";
    for (int i = 0; i < 4; i++)
        std::cout << tab[i].id << " : " << tab[i].solde << "\n";

    return 0;
}
```


# Ex19
```cpp
/*
知识点：
析构
类的学习

析构看起来有点像垃圾回收机制但两者是不一样的
垃圾回收机制是自动管理堆内存进行回收的，例如在JS中体现为闭包延长生命周期，实现防抖节流等等

而在C++中
当栈内存的对象离开作用域时，会自动调用析构函数，且由编译器自动pop弹出内存空间
而堆内存（new实例）是在执行 delete 的时候会调用析构函数，然后释放堆内存
所以析构函数不管理内存，而是管理该对象拥有的外部资源，它是 RAII资源获取即初始化 的一部分，用于对象生命周期结束的瞬间，例如释放数组、关闭文件、释放互斥锁等等

详情请看 Ex19 文件夹
*/
```


# Ex19&20&21 文件夹
## fraction.hpp
```h
#ifndef FRACTION_H
#define FRACTION_H

#include <iostream>
#include "fractionException.hpp"

namespace MATH
{
    class Fraction
    {
    private:
        int numerateur_;
        int denominateur_;
        void simplification(); // 私有化简函数

    public:
        // 重载构造函数
        Fraction(int n = 0, int d = 1); // 默认值构造
        Fraction(const Fraction &f);    // 拷贝构造

        ~Fraction();

        // 私有属性getter函数
        // getter 函数推荐写成 inline ，首先getter只需要返回属性值即可开销很小，而且大项目中类一般会在多处复用
        inline int getNumerateur() const { return numerateur_; }
        inline int getDenominateur() const { return denominateur_; }

        // setter 函数，修改私有属性
        void setFraction(int n, int d);

        // 加法
        Fraction somme(const Fraction &f) const;

        // 输出
        void afficher() const;
    };
}

#endif
```

## fractionException.hpp
```h
#ifndef FRACTION_EXCEPTION_HPP
#define FRACTION_EXCEPTION_HPP

#include <cstring>

// 前向声明，避免循环依赖（用于下面设置 badValue ）
namespace MATH
{
    class Fraction; // 前向声明
}

// 自定义异常类从而个性化、精准的区分错误
// 例如本题只需要输出错误信息字符串就好，但是现在我有需要得到报错的来源对象，于是我可以加一个 badValue

namespace MATH
{
    class FractionException
    {
    private:
        char info_[256];
        int numerateur_;   // 分子
        int denominateur_; // 分母

    public:
        // 题目基本要求：接受字符串创建异常对象
        FractionException(const char *message)
            : numerateur_(0), denominateur_(1)
        {
            strncpy(info_, message, 255);
            info_[255] = '\0'; // 确保字符串以 null 结尾
        }

        // 进阶个性化：在基础上接收分数值创建异常对象
        FractionException(const char *message, int n, int d)
            : numerateur_(n), denominateur_(d)
        {
            strncpy(info_, message, 255);
            info_[255] = '\0';
        }

        // 获取错误信息
        const char *getInfo() const
        {
            return info_;
        }

        // 获取导致异常的分子
        int getNumerateur() const
        {
            return numerateur_;
        }

        // 获取导致异常的分母
        int getDenominateur() const
        {
            return denominateur_;
        }
    };
}

#endif
```

## fractionPatch.hpp
```h
#ifndef FRACTION_PATCH_H
#define FRACTION_PATCH_H

#include "fraction.hpp"
#include <iostream>

namespace MATH
{
    Fraction operator+(const Fraction &f1, const Fraction &f2);

    Fraction operator+(const Fraction &f, int n);
    Fraction operator+(int n, const Fraction &f);

    // 前缀版本 ++f (返回引用，因为返回自身)
    Fraction &operator++(Fraction &f);
    // 后缀版本 f++ (参数 int 是哑元，用于重载)
    Fraction operator++(Fraction &f, int); // 当编译器看到 ++ 在后面的时候，实际调用的是 operator++(f, 0) 从而区分前后缀

    std::ostream &operator<<(std::ostream &os, const Fraction &f);
}

#endif
```

## fraction.cpp
```cpp
#include "fraction.hpp"

// C++的this 和 py的self 更像，是指向当前对象的指针、内存地址
// （只不过 py的self 更加显式）（和 JS的this 差远，JS的this的四条规则更加动态）

namespace MATH // namespace 不是全局生效所以如果空间分散在多处的话得多次 namespace
{
    // 类也是一种作用域，像 namespace 一样需要 :: 来访问
    // 这样就告诉了编译器 这个函数是属于类的
    Fraction::Fraction(int n, int d) : numerateur_(n), denominateur_(d)
    // 类的成员名(参数) ：将参数赋值给类的成员
    {
        std::cout << "+ 构造 Fraction 对象: " << this << " => "
                  << numerateur_ << "/" << denominateur_ << std::endl;
        simplification();
    }
    // 拷贝构造
    Fraction::Fraction(const Fraction &f)
        : numerateur_(f.numerateur_), denominateur_(f.denominateur_)
    {
        std::cout << "+ 拷贝构造 Fraction: " << this << " <= " << &f << std::endl;
    }

    // ~加类名：析构函数，当栈内存的对象离开作用域时或者堆内存对象delete时自动调用
    Fraction::~Fraction()
    {
        // Fraction 类没有我在 Ex19 中提到的数组、文件、互斥锁等，所以 Fraction 类的析构函数只用于展示
        std::cout << "- 析构 Fraction 对象: " << this << " => "
                  << numerateur_ << "/" << denominateur_ << std::endl;
    }

    // setter
    void Fraction::setFraction(int n, int d)
    {
        numerateur_ = n;
        denominateur_ = d;
        simplification();
    }

    // 简化函数
    void Fraction::simplification()
    {
        // 由于所有构造以及操作后都会汇总到简化函数，所以在简化函数里面处理异常就能实现广覆盖
        if (denominateur_ == 0)
        {
            // throw 之后的代码不会执行，因为程序流程立即跳转到 catch 块
            throw FractionException("错误：分母不能为0！", numerateur_, denominateur_);
        }

        if (numerateur_ == 0)
        {
            denominateur_ = 1;
            return;
        }

        int a = (numerateur_ > 0) ? numerateur_ : -numerateur_;
        int b = (denominateur_ > 0) ? denominateur_ : -denominateur_;

        /*
        // 通过欧几里得算法找最大公约数
        while (a != b)
        {
            if (a > b)
                a -= b;
            else
                b -= a;
        }
        */
        // 辗转取余法更快
        while (b != 0)
        {
            int temp = b;
            b = a % b;
            a = temp;
        }

        numerateur_ /= a;
        denominateur_ /= a;

        if (denominateur_ < 0)
        {
            denominateur_ = -denominateur_;
            numerateur_ = -numerateur_;
        }
    }

    // 加法
    Fraction Fraction::somme(const Fraction &f) const
    {
        return Fraction(
            numerateur_ * f.denominateur_ + denominateur_ * f.numerateur_,
            denominateur_ * f.denominateur_);
        // 这里不需要简化，因为 Fraction 构造函数内部最后会调用
    }

    // 展示
    void Fraction::afficher() const
    {
        std::cout << numerateur_ << "/" << denominateur_;
    }
}
```

## fractionPatch.cpp
```cpp
#include "fractionPatch.hpp"

namespace MATH
{
    Fraction operator+(const Fraction &f1, const Fraction &f2)
    {
        // 利用已有的 somme 方法
        return f1.somme(f2);

        // 或者直接实现：
        // return Fraction(
        //     f1.getNumerateur() * f2.getDenominateur() +
        //     f1.getDenominateur() * f2.getNumerateur(),
        //     f1.getDenominateur() * f2.getDenominateur()
        // );
    }

    Fraction operator+(const Fraction &f, int n)
    {
        // int n 可以看作 n/1
        return Fraction(
            f.getNumerateur() + n * f.getDenominateur(),
            f.getDenominateur());
    }

    Fraction operator+(int n, const Fraction &f)
    {
        // 加法满足交换律，直接调用上面的函数
        return f + n;
    }

    // 前缀版本：先递增，再返回
    Fraction &operator++(Fraction &f)
    {
        // 分子加上分母，相当于 +1
        f.setFraction(
            f.getNumerateur() + f.getDenominateur(),
            f.getDenominateur());
        return f;
    }

    // 后缀版本：先返回旧值，再递增（由下面可以看出需要拷贝构造并析构临时对象，过慢，所以实际还是推荐前缀++）
    Fraction operator++(Fraction &f, int)
    {
        // 保存当前值
        Fraction temp(f);

        // 递增当前对象
        ++f; // 调用前缀版本

        // 返回旧值
        return temp;
    }

    std::ostream &operator<<(std::ostream &os, const Fraction &f)
    {
        os << f.getNumerateur() << "/" << f.getDenominateur();
        return os; // 返回流引用，支持链式调用如 cout << f1 << f2
    }
}
```

## main.cpp
```cpp
#include <iostream>
#include "fraction.hpp"
#include "fractionPatch.hpp"

using namespace std;
using namespace MATH;

Fraction *myFunction()
{
    Fraction fx(7, 8);
    Fraction *pfy = new Fraction(2, 3);
    return pfy;
}

int main()
{
    Fraction f1(3, 4);
    Fraction f2(1, 6);
    Fraction *pf3 = new Fraction(1, 2);

    cout << "\n---- 进入一个作用域 ----\n";
    Fraction *pf6;
    {
        Fraction f4(3, 8);
        Fraction f5(4, 6);
        pf6 = new Fraction(1, 3);
    }
    cout << "---- 离开作用域 ----\n";

    // 函数作用域
    cout << "\n---- 进入函数 ----\n";
    Fraction *pf7 = myFunction();
    cout << "---- 离开函数 ----\n";

    cout << "\n---- 手动释放内存 ----\n";
    delete pf6;
    delete pf7;
    delete pf3;

    cout << "\n---- 测试加法 ----\n";
    cout << f1.getNumerateur() << '/' << f1.getDenominateur() << " + " << f2.getNumerateur() << '/' << f2.getDenominateur() << endl;
    Fraction r = f1.somme(f2);
    r.afficher();
    cout << endl;

    // Ex20 =================================

    cout << "\n==== E20 - 测试运算符重载 ====\n";
    cout << "\n---- 测试 f1 + f2 (Fraction + Fraction) ----\n";
    Fraction f8(1, 2);
    Fraction f9(1, 3);
    cout << "f8 = " << f8 << ", f9 = " << f9 << endl;
    Fraction f10 = f8 + f9;
    cout << "f8 + f9 = " << f10 << endl;

    cout << "\n---- 测试 Fraction + int 和 int + Fraction ----\n";
    Fraction f11(2, 3);
    cout << "f11 = " << f11 << endl;
    Fraction f12 = f11 + 2;
    cout << "f11 + 2 = " << f12 << endl;
    Fraction f13 = 3 + f11;
    cout << "3 + f11 = " << f13 << endl;

    cout << "\n---- 测试 ++f 和 f++ ----\n";
    Fraction f14(3, 4);
    cout << "原始值 f14 = " << f14 << endl;

    cout << "前缀 ++f14 = " << ++f14 << endl;
    cout << "执行后 f14 = " << f14 << endl;

    Fraction f15(5, 6);
    cout << "\n原始值 f15 = " << f15 << endl;
    cout << "后缀 f15++ = " << f15++ << " (返回旧值)" << endl;
    cout << "执行后 f15 = " << f15 << endl;

    cout << "\n---- 测试 cout << f (已在上面使用) ----\n";
    cout << "链式输出测试: " << f8 << " + " << f9 << " = " << f10 << endl;

    // Ex21 =================================
    cout << "\n==== E21 - 测试异常处理 ====\n";

    cout << "\n---- 构造函数中分母为0 ----\n";
    try
    {
        Fraction f16(1, 0);
        cout << "f16 = " << f16 << endl; // 不会执行
    }
    catch (const FractionException &e)
    {
        cout << "捕获到 FractionException 异常: " << e.getInfo() << endl;
        cout << "  错误的分数值: " << e.getNumerateur() << "/" << e.getDenominateur() << endl;
    }

    cout << "\n---- setFraction 中分母为0 ----\n";
    try
    {
        Fraction f17(3, 4);
        cout << "创建 f17 = " << f17 << endl;
        cout << "尝试将 f17 设置为 5/0..." << endl;
        f17.setFraction(5, 0);
        cout << "f17 = " << f17 << endl;
    }
    catch (const FractionException &e)
    {
        cout << "捕获到 FractionException 异常: " << e.getInfo() << endl;
        cout << "  错误的分数值: " << e.getNumerateur() << "/" << e.getDenominateur() << endl;
    }

    cout << "\n---- 正常的分数运算 ----\n";
    try
    {
        Fraction f18(1, 2);
        Fraction f19(1, 3);
        Fraction f20 = f18 + f19;
        cout << f18 << " + " << f19 << " = " << f20 << " ✓" << endl;
    }
    catch (const FractionException &e)
    {
        cout << "捕获到 FractionException 异常: " << e.getInfo() << endl;
    }

    cout << "\n---- 程序结束 ----\n";

    return 0;
}

/*
Ex19结果：

+ 构造 Fraction 对象: 0x16b5e2fb4 => 3/4
+ 构造 Fraction 对象: 0x16b5e2fac => 1/6
+ 构造 Fraction 对象: 0x120606140 => 1/2

---- 进入一个作用域 ----
+ 构造 Fraction 对象: 0x16b5e2f80 => 3/8
+ 构造 Fraction 对象: 0x16b5e2f78 => 4/6
+ 构造 Fraction 对象: 0x120605fd0 => 1/3
- 析构 Fraction 对象: 0x16b5e2f78 => 2/3（p5化简后的结果）
- 析构 Fraction 对象: 0x16b5e2f80 => 3/8
---- 离开作用域 ----

---- 进入函数 ----
+ 构造 Fraction 对象: 0x16b5e2eb8 => 7/8
+ 构造 Fraction 对象: 0x120605fe0 => 2/3
- 析构 Fraction 对象: 0x16b5e2eb8 => 7/8
---- 离开函数 ----

---- 手动释放内存 ----
- 析构 Fraction 对象: 0x120605fd0 => 1/3
- 析构 Fraction 对象: 0x120605fe0 => 2/3
- 析构 Fraction 对象: 0x120606140 => 1/2

---- 测试加法 ----
3/4 + 1/6
+ 构造 Fraction 对象: 0x16b5e2f68 => 22/24
11/12

---- 程序结束 ----
- 析构 Fraction 对象: 0x16b5e2f68 => 11/12
- 析构 Fraction 对象: 0x16b5e2fac => 1/6
- 析构 Fraction 对象: 0x16b5e2fb4 => 3/4
*/

/*
Ex20结果：

==== E20 - 测试运算符重载 ====

---- 测试 f1 + f2 (Fraction + Fraction) ----
+ 构造 Fraction 对象: 0x16d45ef60 => 1/2
+ 构造 Fraction 对象: 0x16d45ef58 => 1/3
f8 = 1/2, f9 = 1/3
+ 构造 Fraction 对象: 0x16d45ef50 => 5/6
f8 + f9 = 5/6

---- 测试 Fraction + int 和 int + Fraction ----
+ 构造 Fraction 对象: 0x16d45ef48 => 2/3
f11 = 2/3
+ 构造 Fraction 对象: 0x16d45ef40 => 8/3
f11 + 2 = 8/3
+ 构造 Fraction 对象: 0x16d45ef38 => 11/3
3 + f11 = 11/3

---- 测试 ++f 和 f++ ----
+ 构造 Fraction 对象: 0x16d45ef30 => 3/4
原始值 f14 = 3/4
前缀 ++f14 = 7/4
执行后 f14 = 7/4
+ 构造 Fraction 对象: 0x16d45ef28 => 5/6

原始值 f15 = 5/6
后缀 f15++ = + 拷贝构造 Fraction: 0x16d45ef20 <= 0x16d45ef28
5/6 (返回旧值)
- 析构 Fraction 对象: 0x16d45ef20 => 5/6
执行后 f15 = 11/6

---- 测试 cout << f (已在上面使用) ----
链式输出测试: 1/2 + 1/3 = 5/6
*/

/*
Ex21结果

==== E21 - 测试异常处理 ====

---- 构造函数中分母为0 ----
+ 构造 Fraction 对象: 0x16f606f18 => 1/0
捕获到 FractionException 异常: 错误：分母不能为0！
  错误的分数值: 1/0

---- setFraction 中分母为0 ----
+ 构造 Fraction 对象: 0x16f606f08 => 3/4
创建 f17 = 3/4
尝试将 f17 设置为 5/0...
- 析构 Fraction 对象: 0x16f606f08 => 5/0
捕获到 FractionException 异常: 错误：分母不能为0！
  错误的分数值: 5/0

---- 正常的分数运算 ----
+ 构造 Fraction 对象: 0x16f606ef8 => 1/2
+ 构造 Fraction 对象: 0x16f606ef0 => 1/3
+ 构造 Fraction 对象: 0x16f606ee8 => 5/6
1/2 + 1/3 = 5/6 ✓
- 析构 Fraction 对象: 0x16f606ee8 => 5/6
- 析构 Fraction 对象: 0x16f606ef0 => 1/3
- 析构 Fraction 对象: 0x16f606ef8 => 1/2
*/
```


# Ex20
```cpp
/*
请看 Ex19&20 文件夹的 Patch 补丁
*/
```


# Ex21
```cpp
/*
知识点：错误类个性化

详细看Ex19&20&21/fractionException.hpp 以及 Ex19&20&21/fraction.cpp 中的简化函数
*/
```


# Ex22
```cpp
/*
要实现一个SET游戏，主要内容就是对卡牌数据进行管理
直接在老师的代码上做了配置优化、注释等（详情请看 Ex22 文件夹）

下面是一些概念：
- 关联关系：
    - 单向关联：比如 A知道，但是B不知道 ，那么就在 A 的public中声明 B* ptr_to_b
    - 双向关联：通过 vector或其他容器来实现多对多 std::vector<对方*>
- 组合关系：两个类比如 A拥有B 时，那么 A 全权对 B 的实例进行生命周期管理（例如本题中的 Jeu 和 Carte）
- 聚合关系：A类对象中包含B类对象的引用或者指针，但是 A不管理B的生命周期 ，是一种弱拥有的关系，包含对象A销毁了不影响聚合对象B（例如本题中的 Carte 和 Pioche）
*/
```


# Ex22&23 文件夹
## config.hpp
```h
#ifndef SET_CONFIG_H
#define SET_CONFIG_H

#include <cstddef> // 引入 size_t 类型定义

/**
 * ============================================================================
 * 配置文件说明 (Configuration File Documentation)
 * ============================================================================
 *
 * 设计理念：
 * 之前的代码是直接在类中使用魔法数字（如 81、3 等）来表示卡牌数量和配置。
 * 这种方式虽然直观，但存在以下问题：
 * 1. 可维护性差：修改配置需要在多处查找和替换
 * 2. 易出错：不同地方的数字可能不一致
 * 3. 可读性差：数字本身无法表达其含义
 *
 * 改进方案：
 * 使用配置文件统一管理所有常量，遵循"单一数据源"原则。
 * 优势：
 * - 集中管理：所有配置在一个地方定义
 * - 类型安全：使用 constexpr 在编译期确定值
 * - 易于扩展：添加新配置无需修改核心代码
 * - 语义清晰：常量名称表达了其用途
 *
 * 数学基础：
 * SET 游戏的卡牌总数 = 3^4 = 81
 * （4 个特征，每个特征有 3 种可能）
 */

namespace config
{
    // ========================================================================
    // 游戏核心配置 (Game Core Configuration)
    // ========================================================================

    /**
     * NB_CARTES: 游戏中卡牌的总数
     * 计算公式: NB_COULEURS × NB_NOMBRES × NB_FORMES × NB_REMPLISSAGES
     *          = 3 × 3 × 3 × 3 = 81
     * 这是 SET 游戏的固定规则，每张卡牌都是唯一的
     */
    constexpr size_t NB_CARTES = 81;

    /**
     * NB_COULEURS: 卡牌颜色的种类数
     * 可选值：rouge (红), mauve (紫), vert (绿)
     */
    constexpr size_t NB_COULEURS = 3;

    /**
     * NB_NOMBRES: 卡牌上符号的数量种类
     * 可选值：1, 2, 3
     */
    constexpr size_t NB_NOMBRES = 3;

    /**
     * NB_FORMES: 卡牌符号的形状种类数
     * 可选值：ovale (椭圆), vague (波浪), losange (菱形)
     */
    constexpr size_t NB_FORMES = 3;

    /**
     * NB_REMPLISSAGES: 卡牌符号的填充方式种类数
     * 可选值：plein (实心), vide (空心), hachure (阴影)
     */
    constexpr size_t NB_REMPLISSAGES = 3;

    // ========================================================================
    // 游戏规则配置 (Game Rules Configuration)
    // ========================================================================

    /**
     * PLATEAU_MIN_CARTES: 游戏桌面上最少应保持的卡牌数
     * 根据 SET 游戏规则，正常情况下桌面应有 12 张卡牌
     */
    constexpr size_t PLATEAU_MIN_CARTES = 12;

    /**
     * PLATEAU_INITIAL_CAPACITY: Plateau 动态数组的初始容量
     * 避免频繁扩容，提高性能
     */
    constexpr size_t PLATEAU_INITIAL_CAPACITY = 5;

    /**
     * PLATEAU_INCREMENT: Plateau 扩容时每次增加的容量
     * 当数组满时，以此值为增量进行扩容
     */
    constexpr size_t PLATEAU_INCREMENT = 5;

    // ========================================================================
    // 显示配置 (Display Configuration)
    // ========================================================================

    /**
     * PLATEAU_CARTES_PER_LINE: 打印 Plateau 时每行显示的卡牌数
     * 用于格式化输出，让显示更整齐
     */
    constexpr size_t PLATEAU_CARTES_PER_LINE = 3;
}

#endif // SET_CONFIG_H
```

## set.h
```h
#ifndef _SET_H
#define _SET_H

#include "config.hpp"
#include <iostream>
#include <string>
#include <initializer_list>
#include <array>
#include <cstdlib>

using namespace std;

/**
 * ============================================================================
 * SET 游戏命名空间 (SET Game Namespace)
 * ============================================================================
 *
 * 本文件实现了 SET 纸牌游戏的核心数据结构和类。
 * SET 是一款观察力游戏，玩家需要从桌面上的卡牌中找出满足特定规则的三张卡组合。
 *
 * 主要类的关系：
 * - Carte: 表示单张卡牌（组合关系 - 由 Jeu 创建和拥有）
 * - Jeu: 单例模式，管理所有 81 张卡牌（组合关系 - 拥有所有 Carte）
 * - Pioche: 牌堆，管理待发的卡牌（聚合关系 - 指向 Carte，不拥有）
 * - Plateau: 桌面，显示当前可见的卡牌（聚合关系 - 指向 Carte，不拥有）
 * - Combinaison: 三张卡的组合（聚合关系 - 指向 Carte，不拥有）
 * - Controleur: 游戏控制器（组合关系 - 拥有 Jeu、Pioche、Plateau）
 */
namespace Set
{
	// ========================================================================
	// 异常处理类 (Exception Handling)
	// ========================================================================

	/**
	 * SetException: SET 游戏中的异常类
	 *
	 * 设计说明：
	 * - 用于处理游戏中的各种异常情况（如牌堆为空、索引越界等）
	 * - 存储错误信息字符串，便于调试和错误提示
	 *
	 * 使用场景：
	 * - 访问不存在的卡牌索引
	 * - 从空牌堆中抽牌
	 * - 迭代器越界
	 */
	class SetException
	{
	public:
		// 构造函数：接收错误信息
		SetException(const string &i) : info(i) {}

		// 获取错误信息
		string getInfo() const { return info; }

	private:
		string info; // 存储错误描述信息
	};

	// ========================================================================
	// 卡牌特征枚举 (Card Characteristics Enumerations)
	// ========================================================================

	/**
	 * 设计理念：使用强类型枚举（enum class）
	 *
	 * 为什么使用 enum class 而不是普通 enum？
	 * 1. 类型安全：不会隐式转换为整数，避免误用
	 * 2. 作用域限定：枚举值在枚举类型内部，避免命名冲突
	 * 3. 前向声明：可以前向声明，提高编译效率
	 *
	 * 例如：Couleur::rouge 而不是 rouge（避免与其他地方的 rouge 冲突）
	 */

	/**
	 * Couleur: 卡牌符号的颜色
	 * - rouge: 红色
	 * - mauve: 紫色（或称紫红色）
	 * - vert: 绿色
	 */
	enum class Couleur
	{
		rouge, // 红色
		mauve, // 紫色
		vert   // 绿色
	};

	/**
	 * Nombre: 卡牌上符号的数量
	 * - un: 1 个符号
	 * - deux: 2 个符号
	 * - trois: 3 个符号
	 *
	 * 注意：显式指定值便于后续逻辑判断和输出
	 */
	enum class Nombre
	{
		un = 1,	  // 1 个
		deux = 2, // 2 个
		trois = 3 // 3 个
	};

	/**
	 * Forme: 卡牌符号的形状
	 * - ovale: 椭圆形
	 * - vague: 波浪形
	 * - losange: 菱形
	 */
	enum class Forme
	{
		ovale,	// 椭圆形
		vague,	// 波浪形
		losange // 菱形
	};

	/**
	 * Remplissage: 卡牌符号的填充方式
	 * - plein: 实心填充
	 * - vide: 空心（只有轮廓）
	 * - hachure: 阴影填充（斜线纹理）
	 */
	enum class Remplissage
	{
		plein,	// 实心
		vide,	// 空心
		hachure // 阴影
	};

	// ========================================================================
	// 枚举转换与输出函数 (Enum Conversion and Output Functions)
	// ========================================================================

	/**
	 * toString 系列函数：将枚举值转换为字符串表示
	 * 用途：便于调试和显示卡牌信息
	 */
	string toString(Couleur c);
	string toString(Nombre v);
	string toString(Forme f);
	string toString(Remplissage v);

	/**
	 * operator<< 重载：支持直接输出枚举值到流
	 * 使用方式：cout << Couleur::rouge << endl;
	 */
	ostream &operator<<(ostream &f, Couleur c);
	ostream &operator<<(ostream &f, Nombre v);
	ostream &operator<<(ostream &f, Forme x);
	ostream &operator<<(ostream &f, Remplissage r);

	// ========================================================================
	// 枚举值列表 (Enum Value Lists)
	// ========================================================================

	/**
	 * 全局常量列表：包含每个特征的所有可能值
	 *
	 * 设计说明：
	 * - 使用 initializer_list 允许在循环中遍历所有可能的值
	 * - extern 声明表示在 set.cpp 中定义
	 *
	 * 用途：
	 * 1. 生成所有 81 张卡牌（4 层嵌套循环）
	 * 2. 显示所有可能的特征值
	 * 3. 验证和测试
	 */
	extern std::initializer_list<Couleur> Couleurs;
	extern std::initializer_list<Nombre> Nombres;
	extern std::initializer_list<Forme> Formes;
	extern std::initializer_list<Remplissage> Remplissages;

	/**
	 * print 系列函数：打印所有可能的特征值
	 * 参数 f: 输出流，默认为标准输出 cout
	 */
	void printCouleurs(std::ostream &f = cout);
	void printNombres(std::ostream &f = cout);
	void printFormes(std::ostream &f = cout);
	void printRemplissages(std::ostream &f = cout);

	// ========================================================================
	// Carte 类：表示单张卡牌 (Card Class)
	// ========================================================================

	/**
	 * Carte: 代表游戏中的一张卡牌
	 *
	 * 设计要点（回答题目问题1）：
	 *
	 * 1. 为什么构造函数是私有的？
	 *    - 封装性：只有 Jeu 类能创建卡牌，外部无法随意创建
	 *    - 单一职责：卡牌的生命周期由 Jeu 统一管理
	 *    - 避免重复：确保每张卡牌唯一，不会有重复创建
	 *
	 * 2. 为什么使用 = default？
	 *    - Carte 只包含基本类型成员（4个枚举值）
	 *    - 没有动态分配的资源（指针、数组等）
	 *    - 编译器生成的默认版本已经足够（浅拷贝即可）
	 *    - = default 明确表达设计意图，提高代码可读性
	 *
	 * 3. 何时需要自定义这些函数？
	 *    - 当类包含指针成员时（需要深拷贝）
	 *    - 当类管理外部资源时（文件、内存等）
	 *    - 遵循"三五法则"：如果需要自定义析构函数，
	 *      通常也需要自定义拷贝构造函数和赋值运算符
	 *
	 * 类间关系：
	 * - Carte 与 Jeu：组合关系（Composition）
	 *   Jeu 创建并拥有所有 Carte 对象，负责其生命周期
	 */
	class Carte
	{
	private:
		// ====================================================================
		// 私有成员变量 (Private Member Variables)
		// ====================================================================

		Couleur couleur;		 // 卡牌符号的颜色
		Nombre nombre;			 // 卡牌上符号的数量
		Forme forme;			 // 卡牌符号的形状
		Remplissage remplissage; // 卡牌符号的填充方式

		// ====================================================================
		// 私有构造函数 (Private Constructor)
		// ====================================================================

		/**
		 * 构造函数：初始化卡牌的四个特征
		 *
		 * 为什么私有？
		 * - 只允许 Jeu 类创建卡牌实例
		 * - 防止外部代码随意创建卡牌
		 * - 确保所有卡牌都由 Jeu 统一管理
		 *
		 * 使用初始化列表的好处：
		 * - 直接初始化成员，效率高于赋值
		 * - 对于 const 成员和引用成员，必须使用初始化列表
		 */
		Carte(Couleur c, Nombre n, Forme f, Remplissage r)
			: couleur(c), nombre(n), forme(f), remplissage(r) {}

		// ====================================================================
		// 特殊成员函数 (Special Member Functions)
		// ====================================================================

		/**
		 * 拷贝构造函数：使用默认实现
		 *
		 * 为什么 = default 足够？
		 * - Carte 的所有成员都是枚举类型（值类型）
		 * - 没有指针或动态分配的内存
		 * - 编译器生成的成员逐个拷贝已经满足需求
		 */
		Carte(const Carte &) = default;

		/**
		 * 赋值运算符：使用默认实现
		 *
		 * 默认行为：逐成员赋值
		 * 对于 Carte 来说已经足够
		 */
		Carte &operator=(const Carte &) = default;

		/**
		 * 析构函数：使用默认实现
		 *
		 * 为什么不需要自定义？
		 * - Carte 没有管理任何需要手动释放的资源
		 * - 没有动态分配的内存
		 * - 没有打开的文件或网络连接
		 * - 枚举类型的销毁由编译器自动处理
		 */
		~Carte() = default;

		// ====================================================================
		// 友元声明 (Friend Declaration)
		// ====================================================================

		/**
		 * 友元类：允许 Jeu 访问 Carte 的私有成员
		 *
		 * 为什么需要？
		 * - Jeu 需要调用 Carte 的私有构造函数来创建卡牌
		 * - 体现了 Carte 与 Jeu 之间的紧密组合关系
		 * - Jeu 负责 Carte 的整个生命周期
		 */
		friend class Jeu;

	public:
		// ====================================================================
		// 公有访问器方法 (Public Accessor Methods)
		// ====================================================================

		/**
		 * Getter 方法：获取卡牌的各个特征
		 *
		 * 设计说明：
		 * - const 成员函数：不修改对象状态
		 * - 返回值类型：直接返回枚举值（值类型，开销小）
		 * - 命名规范：遵循 getCamelCase 风格
		 */
		Couleur getCouleur() const { return couleur; }
		Nombre getNombre() const { return nombre; }
		Forme getForme() const { return forme; }
		Remplissage getRemplissage() const { return remplissage; }
	};

	/**
	 * 输出运算符重载：支持直接输出 Carte 对象
	 * 格式：[颜色形状数量填充]，例如 [RO2P] 表示红色椭圆2个实心
	 */
	ostream &operator<<(ostream &f, const Carte &c);

	// ========================================================================
	// Jeu 类：管理所有卡牌的单例类 (Game Singleton Class)
	// ========================================================================

	/**
	 * Jeu: 游戏类，管理所有 81 张卡牌
	 *
	 * 设计要点（回答题目问题2、3、4、5）：
	 *
	 * 问题2：关于数组初始化
	 * - Carte cartes[81]; 如果是对象数组就必须有初始化器，否则编译器不知道该如何创建这个数组
	 *   ru提供初始化器：Carte cartes[3] = {c1, c2, c3};
	 * - const Carte* cartes[81]; 指针数组可以不初始化
	 *   指针本身可以稍后赋值
	 *
	 * 问题3：Carte 与 Jeu 的关系
	 * - 组合关系（Composition，实心菱形）
	 * - Jeu 拥有并管理所有 Carte 对象的生命周期
	 * - Carte 不能独立于 Jeu 存在
	 * - UML表示：Jeu ◆——> Carte (1对81的组合)
	 *
	 * 问题4：为什么使用 const Carte*？
	 * - 常量指针保护：防止意外修改卡牌内容
	 * - 卡牌一旦创建就不应该改变（符合 SET 游戏规则）
	 * - 类型安全：编译器会阻止通过指针修改 Carte
	 * - 对比：Carte* 允许修改，const Carte* 只读
	 *
	 * 问题5：为什么禁止拷贝？
	 * - 单例模式：全局只应该有一个 Jeu 实例
	 * - 资源管理：避免多个 Jeu 对象管理同一批卡牌
	 * - 防止悬空指针：拷贝会导致指针管理混乱
	 *
	 * 单例模式说明：
	 * - 保证全局只有一个 Jeu 实例
	 * - 通过 getInstance() 获取实例
	 * - 私有构造函数防止外部创建
	 */
	class Jeu
	{
	private:
		// ====================================================================
		// 私有成员变量 (Private Member Variables)
		// ====================================================================

		/**
		 * cartes: 存储所有 81 张卡牌的指针数组
		 *
		 * 设计细节：
		 * - const Carte*：指向常量 Carte 的指针，卡牌内容不可修改
		 * - 固定大小数组：81 = 3^4（4个特征各3种可能）
		 * - 使用配置常量：config::NB_CARTES，便于统一管理
		 *
		 * 为什么是指针数组而不是对象数组？
		 * 1. Carte 构造函数私有，无法直接创建对象数组
		 * 2. 指针允许动态分配（new），在运行时创建
		 * 3. 灵活性：可以在构造函数中逐个创建卡牌
		 */
		const Carte *cartes[config::NB_CARTES];

		// ====================================================================
		// 禁用拷贝和赋值 (Deleted Copy and Assignment)
		// ====================================================================

		/**
		 * 拷贝构造函数：已删除
		 *
		 * 为什么删除？
		 * - 单例模式：不允许创建多个 Jeu 实例
		 * - 资源管理：避免多个对象管理同一批动态分配的 Carte
		 * - 防止错误：拷贝会导致两个 Jeu 对象指向相同的 Carte，
		 *   销毁时会重复释放内存（double free）
		 */
		Jeu(const Jeu &) = delete;

		/**
		 * 赋值运算符：已删除
		 * 原因同上，维护单例模式
		 */
		Jeu &operator=(const Jeu &) = delete;

		// ====================================================================
		// 私有构造和析构函数 (Private Constructor and Destructor)
		// ====================================================================

		/**
		 * 构造函数：创建所有 81 张卡牌
		 *
		 * 为什么私有？
		 * - 单例模式要求：外部无法直接创建实例
		 * - 只能通过 getInstance() 获取唯一实例
		 *
		 * 为什么不用 = default？
		 * - 需要自定义逻辑：生成所有 81 张不同的卡牌
		 * - 4层嵌套循环遍历所有特征组合
		 * - 为每张卡牌分配内存（new Carte(...)）
		 */
		Jeu();

		/**
		 * 析构函数：释放所有卡牌的内存
		 *
		 * 为什么不用 = default？
		 * - 需要自定义清理：释放 81 张动态分配的 Carte
		 * - 遵循"谁分配谁释放"原则
		 * - 防止内存泄漏：必须 delete 每个 new 出来的 Carte
		 */
		~Jeu();

	public:
		// ====================================================================
		// 单例访问方法 (Singleton Access Method)
		// ====================================================================

		/**
		 * getInstance: 获取 Jeu 的唯一实例（单例模式）
		 *
		 * 实现原理：
		 * - static 局部变量：在第一次调用时创建，程序结束时销毁
		 * - 线程安全：C++11 保证 static 局部变量的初始化是线程安全的
		 * - 延迟初始化：只有在第一次调用时才创建实例
		 *
		 * 单例模式的优点：
		 * - 全局访问点：任何地方都可以获取 Jeu 实例
		 * - 资源共享：所有代码共享同一套卡牌数据
		 * - 内存高效：只创建一次，避免重复创建
		 *
		 * 使用方式：
		 *   Jeu& jeu = Jeu::getInstance();
		 *   const Carte& card = jeu.getCarte(0);
		 */
		static Jeu &getInstance()
		{
			static Jeu instance; // 局部静态变量，只初始化一次
			return instance;	 // 返回引用，避免拷贝
		}

		// ====================================================================
		// 公有访问方法 (Public Access Methods)
		// ====================================================================

		/**
		 * getCarte: 获取指定索引的卡牌
		 *
		 * 参数：
		 * - i: 卡牌索引（0-80）
		 *   size_t 是无符号整数类型，表示大小和索引
		 *   在 64 位系统上通常是 unsigned long (8 字节)
		 *   在 32 位系统上通常是 unsigned int (4 字节)
		 *
		 * 返回值：const Carte&
		 * - 引用：避免拷贝，提高效率
		 * - const：保证外部无法修改卡牌
		 *
		 * 异常：如果 i >= 81，抛出 SetException
		 *
		 * const 成员函数：不修改 Jeu 对象的状态
		 */
		const Carte &getCarte(size_t i) const;

		/**
		 * getNbCartes: 获取卡牌总数
		 *
		 * 返回值：81（通过配置文件统一管理）
		 *
		 * 设计优势：
		 * - 使用 config::NB_CARTES 而不是硬编码 81
		 * - 集中管理常量，便于维护和修改
		 * - 提高代码可读性和可维护性
		 */
		size_t getNbCartes() const { return config::NB_CARTES; }

		// ================================================================
		// 迭代器类：遍历所有卡牌 (Iterator Classes)
		// ================================================================

		/**
		 * Iterator: 基于指针的迭代器（方式一）
		 *
		 * 设计模式：迭代器模式 (Iterator Pattern)
		 * 目的：提供一种方法顺序访问聚合对象中的元素，
		 *      而不暴露其内部表示
		 *
		 * 实现方式：使用指向指针的指针
		 * - currentCarte: 指向 cartes 数组中当前元素的指针
		 * - nb: 剩余可迭代的元素数量
		 *
		 * 为什么是 const Carte**？
		 * - cartes 是 const Carte* 类型的数组
		 * - currentCarte 需要指向数组元素（指针的指针）
		 * - 保持 const 约束，防止修改卡牌
		 *
		 * 使用示例：
		 *   Jeu::Iterator it = jeu.first();
		 *   while (!it.isDone()) {
		 *       cout << it.getCurrentItem();
		 *       it.next();
		 *   }
		 */
		class Iterator
		{
		private:
			const Carte **currentCarte; // 指向当前卡牌指针的指针
			size_t nb;					// 剩余待遍历的卡牌数量

			/**
			 * 私有构造函数：只允许 Jeu 创建迭代器
			 *
			 * 参数：
			 * - c: 指向数组起始位置的指针
			 * - n: 可迭代的元素数量
			 */
			Iterator(const Carte **c, size_t n) : currentCarte(c), nb(n) {}

			friend class Jeu; // 允许 Jeu 访问私有构造函数

		public:
			/**
			 * next: 移动到下一张卡牌
			 *
			 * 操作：
			 * 1. currentCarte++ : 指针向后移动一位
			 * 2. nb-- : 剩余数量减一
			 */
			void next()
			{
				currentCarte++; // 移动指针到下一个元素
				nb--;			// 减少剩余计数
			}

			/**
			 * isDone: 检查是否遍历完成
			 *
			 * 返回：true 表示已遍历完所有元素
			 */
			bool isDone() const { return nb == 0; }

			/**
			 * getCurrentItem: 获取当前卡牌
			 *
			 * 返回：当前指向的 Carte 对象的引用
			 *
			 * 为什么是 **currentCarte？
			 * - currentCarte 是指向指针的指针（Carte**）
			 * - *currentCarte 得到 Carte*（指向 Carte 的指针）
			 * - **currentCarte 得到 Carte 对象本身
			 */
			const Carte &getCurrentItem() const
			{
				return **currentCarte; // 双重解引用获取 Carte 对象
			}
		};

		/**
		 * first: 创建指向第一张卡牌的迭代器
		 *
		 * 返回：指向数组开头的 Iterator
		 *
		 * 实现细节：
		 * - &cartes[0] 获取数组第一个元素的地址
		 * - 初始化 nb 为总卡牌数
		 */
		Iterator first()
		{
			const Carte **c = &cartes[0]; // 获取数组首地址
			return Iterator(c, config::NB_CARTES);
		}

		/**
		 * IteratorBis: 基于索引的迭代器（方式二）
		 *
		 * 对比 Iterator 的不同：
		 * - Iterator 使用指针遍历：currentCarte++
		 * - IteratorBis 使用索引遍历：i++
		 *
		 * 优缺点对比：
		 * Iterator（指针方式）：
		 *   优点：直接操作指针，效率略高
		 *   缺点：需要理解指针的指针，较复杂
		 *
		 * IteratorBis（索引方式）：
		 *   优点：逻辑更清晰，易于理解
		 *   缺点：每次需要通过 getCarte(i) 访问，多一次函数调用
		 *
		 * 设计意图：
		 * 展示两种不同的迭代器实现方式，让学习者理解：
		 * - 迭代器模式的本质是提供统一的遍历接口
		 * - 底层实现可以有多种方式
		 */
		class IteratorBis
		{
		private:
			Jeu &instance; // Jeu 实例的引用
			size_t i;	   // 当前卡牌的索引

			/**
			 * 构造函数：初始化迭代器
			 *
			 * 参数：
			 * - j: Jeu 对象的引用
			 * - index: 起始索引
			 */
			IteratorBis(Jeu &j, size_t index) : instance(j), i(index) {}

			friend class Jeu;

		public:
			/**
			 * next: 移动到下一张卡牌
			 *
			 * 安全检查：如果已经遍历完成，抛出异常
			 * 这是一种防御性编程的体现
			 */
			void next()
			{
				if (isDone())
					throw SetException("end of iteration");
				i++; // 索引递增
			}

			/**
			 * isDone: 检查是否遍历完成
			 *
			 * 判断：当前索引是否达到总数
			 */
			bool isDone() const { return i == instance.getNbCartes(); }

			/**
			 * getCurrentItem: 获取当前卡牌
			 *
			 * 实现：通过索引调用 getCarte(i)
			 * 包含安全检查，防止越界访问
			 */
			const Carte &getCurrentItem() const
			{
				if (isDone())
					throw SetException("end of iteration");
				return instance.getCarte(i); // 通过索引获取卡牌
			}
		};

		/**
		 * firstBis: 创建指向第一张卡牌的 IteratorBis
		 *
		 * 参数：*this 传递当前 Jeu 对象的引用
		 * 索引从 0 开始
		 */
		IteratorBis firstBis()
		{
			return IteratorBis(*this, 0);
		}

		/**
		 * const_iterator: 符合 C++ 标准库风格的迭代器
		 *
		 * 设计目标：
		 * - 兼容 C++11 的 range-based for 循环
		 * - 遵循 STL 容器的迭代器接口规范
		 *
		 * 必须实现的操作符：
		 * - operator++: 前缀递增运算符
		 * - operator!=: 不等于比较运算符
		 * - operator*: 解引用运算符
		 *
		 * 配合 begin() 和 end()，支持以下语法：
		 *   for (const Carte& c : jeu) {
		 *       cout << c << endl;
		 *   }
		 *
		 * 为什么叫 const_iterator？
		 * - 返回的是 const Carte&，不允许修改卡牌
		 * - 对应 STL 中的 const_iterator 概念
		 * - 与 iterator（非 const）区分开
		 */
		class const_iterator
		{
		private:
			const Jeu &instance; // Jeu 实例的 const 引用
			size_t i;			 // 当前索引

			/**
			 * 构造函数：初始化迭代器位置
			 *
			 * 参数：
			 * - j: const Jeu 引用（保证不修改 Jeu）
			 * - index: 起始索引
			 */
			const_iterator(const Jeu &j, size_t index) : instance(j), i(index) {}

			friend class Jeu;

		public:
			/**
			 * operator++: 前缀递增运算符
			 *
			 * 用法：++it
			 *
			 * 为什么不返回值？
			 * - 简化实现，满足基本 range-based for 需求
			 * - 标准实现应返回 const_iterator&
			 */
			void operator++()
			{
				i++;
			}

			/**
			 * operator!=: 不等于比较运算符
			 *
			 * 用途：range-based for 循环判断是否到达 end()
			 *
			 * 实现：比较索引是否不同
			 *
			 * 注意：通常还应该检查是否比较的是同一个容器的迭代器
			 *      这里简化处理，只比较索引
			 */
			bool operator!=(const_iterator other) const
			{
				return i != other.i;
			}

			/**
			 * operator*: 解引用运算符
			 *
			 * 用法：*it 或 auto& card = *it
			 *
			 * 返回：当前位置的 Carte 引用
			 *
			 * 模拟指针行为：就像 *ptr 获取指针指向的值
			 */
			const Carte &operator*() const
			{
				return instance.getCarte(i);
			}
		};

		/**
		 * begin: 返回指向第一个元素的迭代器
		 *
		 * 必须是 const 成员函数，配合 range-based for
		 */
		const_iterator begin() const { return const_iterator(*this, 0); }

		/**
		 * end: 返回指向"最后一个元素之后"的迭代器
		 *
		 * 注意：end() 不指向有效元素，仅用于判断结束
		 * 经典的"哨兵"模式，[begin, end) 左闭右开区间
		 */
		const_iterator end() const { return const_iterator(*this, config::NB_CARTES); }

		/**
		 * FormeIterator: 条件过滤迭代器
		 *
		 * 设计目的：
		 * - 只遍历特定形状（Forme）的卡牌
		 * - 展示迭代器的扩展应用：带过滤条件的遍历
		 *
		 * 应用场景：
		 * - 需要查找所有椭圆形卡牌
		 * - 需要查找所有波浪形卡牌
		 * - 任何基于形状的过滤查询
		 *
		 * 实现原理：
		 * - 在 next() 中跳过不符合条件的卡牌
		 * - 持续递增索引直到找到匹配的形状或遍历完成
		 *
		 * 扩展思路：
		 * - 可以实现 CouleurIterator（按颜色过滤）
		 * - 可以实现 NombreIterator（按数量过滤）
		 * - 可以实现通用的 FilterIterator（传入谓词函数）
		 *
		 * 使用示例：
		 *   // 遍历所有椭圆形卡牌
		 *   FormeIterator it = jeu.firstFormeIterator(Forme::ovale);
		 *   while (!it.isDone()) {
		 *       cout << it.getCurrentItem();
		 *       it.next();
		 *   }
		 */
		class FormeIterator
		{
		private:
			Forme forme;   // 要过滤的形状
			Jeu &instance; // Jeu 实例引用
			size_t i;	   // 当前索引

			/**
			 * 构造函数：初始化过滤迭代器
			 *
			 * 参数：
			 * - j: Jeu 对象引用
			 * - index: 起始索引
			 * - f: 要过滤的形状
			 */
			FormeIterator(Jeu &j, size_t index, Forme f)
				: forme(f), instance(j), i(index) {}

			friend class Jeu;

		public:
			/**
			 * next: 移动到下一张符合条件的卡牌
			 *
			 * 算法：
			 * 1. 先递增索引（i++）
			 * 2. 如果未完成且当前卡牌形状不匹配，继续递增
			 * 3. 直到找到匹配的卡牌或遍历完成
			 *
			 * 时间复杂度：
			 * - 最坏 O(n)，需要遍历所有卡牌
			 * - 平均 O(1)，因为每种形状约占 1/3
			 */
			void next()
			{
				i++; // 移动到下一张卡
				// 跳过不符合条件的卡牌
				while (!isDone() &&
					   instance.getCarte(i).getForme() != forme)
					i++;
			}

			/**
			 * isDone: 检查是否遍历完成
			 */
			bool isDone() const { return i == instance.getNbCartes(); }

			/**
			 * getCurrentItem: 获取当前卡牌
			 *
			 * 前提：当前索引指向的卡牌形状匹配 forme
			 */
			const Carte &getCurrentItem() const
			{
				return instance.getCarte(i);
			}
		};

		/**
		 * firstFormeIterator: 创建形状过滤迭代器
		 *
		 * 参数：
		 * - f: 要过滤的形状
		 *
		 * 返回：指向第一张该形状卡牌的迭代器
		 *
		 * 注意：如果第一张卡不是目标形状，
		 *      用户需要先调用 next() 才能找到第一张匹配的卡
		 */
		FormeIterator firstFormeIterator(Forme f)
		{
			return FormeIterator(*this, 0, f);
		}
	}; // end of class Jeu

	// ========================================================================
	// Pioche 类：牌堆管理类 (Draw Pile Class)
	// ========================================================================

	/**
	 * Pioche: 管理待发的卡牌（牌堆）
	 *
	 * 设计要点（回答题目问题6、7）：
	 *
	 * 问题6：Carte 与 Pioche 的关系
	 * - 聚合关系（Aggregation，空心菱形）
	 * - Pioche 持有指向 Carte 的指针，但不拥有 Carte
	 * - Carte 的生命周期由 Jeu 管理，不受 Pioche 影响
	 * - Pioche 销毁时不应该删除 Carte 对象
	 * - UML表示：Pioche ◇——> Carte (1对多的聚合)
	 *
	 * 组合 vs 聚合的区别：
	 * - Jeu ◆——> Carte: 组合，Jeu 拥有 Carte，负责创建和销毁
	 * - Pioche ◇——> Carte: 聚合，Pioche 引用 Carte，不负责生命周期
	 *
	 * 问题7：explicit 关键字的意义
	 * - 防止隐式类型转换
	 * - explicit Pioche(const Jeu& j) 禁止：Pioche p = jeu;
	 * - 必须显式调用：Pioche p(jeu);
	 * - 避免意外的类型转换导致的错误
	 *
	 * 为什么禁止拷贝？
	 * - 资源管理：避免多个 Pioche 管理同一个动态数组
	 * - 防止悬空指针：拷贝会导致两个对象共享指针数组
	 * - 明确语义：一个游戏只应该有一个牌堆
	 *
	 * 功能说明：
	 * - 初始化时包含所有 81 张卡牌
	 * - piocher() 随机抽取一张卡并将其从牌堆移除
	 * - 支持查询剩余卡牌数量和是否为空
	 */
	class Pioche
	{
	private:
		// ====================================================================
		// 私有成员变量 (Private Member Variables)
		// ====================================================================

		/**
		 * cartes: 指向卡牌指针的动态数组
		 *
		 * 类型分析：const Carte**
		 * - 最内层：Carte 对象
		 * - 中间层：const Carte* （指向 Carte 的常量指针）
		 * - 外层：const Carte** （指向指针的指针，即指针数组）
		 *
		 * 为什么是动态数组？
		 * - 初始化时从 Jeu 复制所有卡牌的地址
		 * - 需要可修改的数组来实现"抽牌"操作
		 * - 抽到的牌会从数组中移除（交换到末尾）
		 */
		const Carte **cartes;

		/**
		 * nb: 当前牌堆中剩余的卡牌数量
		 *
		 * 初始值：81（所有卡牌）
		 * 每次 piocher() 后递减
		 * 当 nb == 0 时牌堆为空
		 */
		size_t nb;

	public:
		// ====================================================================
		// 构造函数 (Constructor)
		// ====================================================================

		/**
		 * 构造函数：从 Jeu 创建牌堆
		 *
		 * 参数：
		 * - j: Jeu 对象的引用（不是 const，因为可能需要获取非 const 引用）
		 *
		 * 注意：虽然参数不是 explicit，但建议加上以防止隐式转换
		 *
		 * 初始化步骤：
		 * 1. 分配大小为 NB_CARTES 的指针数组
		 * 2. 将 Jeu 中所有卡牌的地址复制到数组
		 * 3. 初始化 nb 为总卡牌数
		 *
		 * 时间复杂度：O(n)，n = 81
		 * 空间复杂度：O(n)，分配 81 个指针
		 */
		Pioche(Jeu &j) : nb(config::NB_CARTES)
		{
			// 动态分配指针数组
			cartes = new const Carte *[config::NB_CARTES];

			// 复制所有卡牌的地址
			// 注意：这里只复制地址（浅拷贝），不复制 Carte 对象
			for (size_t i = 0; i < j.getNbCartes(); i++)
				cartes[i] = &j.getCarte(i);
		}

		// ====================================================================
		// 析构函数 (Destructor)
		// ====================================================================

		/**
		 * 析构函数：释放动态分配的指针数组
		 *
		 * 重要：只删除数组本身，不删除 Carte 对象
		 *
		 * 为什么不删除 Carte？
		 * - 聚合关系：Pioche 不拥有 Carte
		 * - Carte 的生命周期由 Jeu 管理
		 * - 删除 Carte 会导致 Jeu 中的指针悬空（dangling pointer）
		 *
		 * 对比：
		 * - delete[] cartes;     ✅ 删除指针数组
		 * - delete[] cartes[i];  ❌ 错误！不应该删除 Carte
		 */
		~Pioche()
		{
			delete[] cartes; // 只释放指针数组，不删除 Carte 对象
		}

		// ====================================================================
		// 公有方法 (Public Methods)
		// ====================================================================

		/**
		 * piocher: 随机抽取一张卡牌
		 *
		 * 算法：
		 * 1. 检查牌堆是否为空，空则抛出异常
		 * 2. 生成随机索引 i（0 到 nb-1）
		 * 3. 保存 cartes[i]（要返回的卡牌）
		 * 4. 将 cartes[nb-1]（最后一张）移到位置 i
		 * 5. nb--（减少牌堆大小）
		 * 6. 返回被抽中的卡牌
		 *
		 * 时间复杂度：O(1)
		 *
		 * 为什么交换而不是删除？
		 * - 避免数组元素移动（O(n)操作）
		 * - 利用"最后一张卡填补空位"技巧
		 * - 保持剩余卡牌在数组前 nb 个位置
		 *
		 * 实现在 set.cpp 中
		 */
		const Carte &piocher();

		/**
		 * getNbCartes: 获取剩余卡牌数量
		 */
		size_t getNbCartes() const { return nb; }

		/**
		 * estVide: 检查牌堆是否为空
		 */
		bool estVide() const { return nb == 0; }

		// ====================================================================
		// 禁用拷贝和赋值 (Deleted Copy and Assignment)
		// ====================================================================

		/**
		 * 拷贝构造函数：已删除
		 *
		 * 为什么禁止？
		 * - 避免浅拷贝问题：两个 Pioche 会共享同一个 cartes 数组
		 * - 防止双重释放：两个对象的析构函数会删除同一个数组
		 * - 语义不明：复制牌堆的意义不清晰
		 */
		Pioche(const Pioche &p) = delete;

		/**
		 * 赋值运算符：已删除
		 * 原因同上
		 */
		Pioche &operator=(const Pioche &p) = delete;
	};

	// ========================================================================
	// Plateau 类：游戏桌面类 (Game Board Class)
	// ========================================================================

	/**
	 * Plateau: 表示游戏桌面，存放当前可见的卡牌
	 *
	 * 设计要点（回答题目问题8、9）：
	 *
	 * 问题8：Carte 与 Plateau 的关系
	 * - 聚合关系（Aggregation，空心菱形）
	 * - Plateau 持有指向 Carte 的指针，但不拥有 Carte
	 * - Carte 的生命周期由 Jeu 管理
	 * - Plateau 销毁时不删除 Carte 对象
	 * - UML表示：Plateau ◇——> Carte (1对多的聚合)
	 *
	 * 问题9：为什么需要自定义拷贝构造和赋值运算符？
	 *
	 * 如果使用默认版本会发生什么？
	 * - 浅拷贝：两个 Plateau 对象的 cartes 指针指向同一个数组
	 * - 修改一个会影响另一个
	 * - 析构时会双重释放同一块内存（double free）→ 崩溃
	 *
	 * 正确做法：
	 * - 深拷贝：分配新的数组，复制所有指针
	 * - 每个 Plateau 拥有独立的数组
	 * - 但数组中的指针仍指向 Jeu 中的 Carte（聚合关系）
	 *
	 * 动态数组设计：
	 * - cartes: 动态分配的指针数组
	 * - nbMax: 数组的容量（已分配的大小）
	 * - nb: 当前实际使用的元素数量
	 * - 当 nb == nbMax 时需要扩容
	 *
	 * 扩容策略：
	 * - 每次增加固定大小（如 5）
	 * - 类似于 std::vector 的动态增长
	 * - 也可以采用倍增策略（如 *2）以均摊 O(1)
	 */
	class Plateau
	{
	private:
		// ====================================================================
		// 私有成员变量 (Private Member Variables)
		// ====================================================================

		/**
		 * cartes: 指向卡牌指针的动态数组
		 *
		 * 类型：const Carte**
		 * - 动态分配，支持扩容
		 * - 存储指向 Carte 的指针（聚合）
		 */
		const Carte **cartes;

		/**
		 * nbMax: 数组的最大容量
		 *
		 * 表示当前已分配的数组大小
		 * 当 nb 达到 nbMax 时需要扩容
		 */
		size_t nbMax;

		/**
		 * nb: 当前桌面上的卡牌数量
		 *
		 * 表示数组中实际使用的元素数量
		 * 范围：0 <= nb <= nbMax
		 */
		size_t nb;

	public:
		// ====================================================================
		// 构造函数 (Constructor)
		// ====================================================================

		/**
		 * 默认构造函数：创建空的桌面
		 *
		 * 初始化策略：
		 * - 分配初始容量（5 个位置）
		 * - 初始时没有卡牌（nb = 0）
		 *
		 * 为什么初始容量是 5？
		 * - 避免频繁扩容
		 * - 不要太大（浪费内存）
		 * - 可以通过配置文件调整
		 */
		Plateau()
		{
			cartes = new const Carte *[5]; // 分配初始数组
			nbMax = 5;					   // 设置容量
			nb = 0;						   // 初始为空
		}

		// ====================================================================
		// 析构函数 (Destructor)
		// ====================================================================

		/**
		 * 析构函数：释放动态分配的数组
		 *
		 * 注意：只删除指针数组，不删除 Carte 对象
		 * 原因：聚合关系，Carte 由 Jeu 管理
		 */
		~Plateau() { delete[] cartes; }

		// ====================================================================
		// 公有方法 (Public Methods)
		// ====================================================================

		/**
		 * getNbCartes: 获取桌面上的卡牌数量
		 */
		size_t getNbCartes() const { return nb; }

		/**
		 * ajouter: 向桌面添加一张卡牌
		 *
		 * 参数：c - 要添加的卡牌引用
		 *
		 * 算法：
		 * 1. 检查是否需要扩容（nb == nbMax）
		 * 2. 如果需要，分配更大的数组并复制
		 * 3. 将卡牌指针添加到数组末尾
		 * 4. nb++
		 *
		 * 扩容策略：
		 * - 创建大小为 (nbMax + 5) 的新数组
		 * - 复制所有现有指针
		 * - 删除旧数组
		 * - 更新 cartes 和 nbMax
		 *
		 * 时间复杂度：
		 * - 不扩容：O(1)
		 * - 扩容：O(n)
		 *
		 * 实现在 set.cpp 中
		 */
		void ajouter(const Carte &c);

		/**
		 * retirer: 从桌面移除一张卡牌
		 *
		 * 参数：c - 要移除的卡牌引用
		 *
		 * 算法：
		 * 1. 遍历数组查找卡牌地址
		 * 2. 如果找到，用最后一张卡填补空位
		 * 3. nb--
		 * 4. 如果未找到，抛出异常
		 *
		 * 时间复杂度：O(n)
		 *
		 * 实现在 set.cpp 中
		 */
		void retirer(const Carte &c);

		/**
		 * 拷贝构造函数：深拷贝 Plateau
		 *
		 * 为什么需要？
		 * - 避免浅拷贝导致的双重释放
		 * - 每个 Plateau 需要独立的数组
		 *
		 * 实现：
		 * 1. 分配新的数组（大小为 p.nbMax）
		 * 2. 复制所有卡牌指针
		 * 3. 复制 nb 和 nbMax
		 *
		 * 实现在 set.cpp 中
		 */
		Plateau(const Plateau &p);

		/**
		 * 赋值运算符：深拷贝赋值
		 *
		 * 必须处理：
		 * 1. 自赋值检查（if (this != &p)）
		 * 2. 释放当前资源或重用现有数组
		 * 3. 复制新数据
		 *
		 * 实现策略：
		 * - 清空当前内容（nb = 0）
		 * - 逐个添加源对象的卡牌（调用 ajouter）
		 * - 利用 ajouter 的扩容机制
		 *
		 * 实现在 set.cpp 中
		 */
		Plateau &operator=(const Plateau &p);

		/**
		 * print: 打印桌面上的所有卡牌
		 *
		 * 参数：f - 输出流
		 *
		 * 格式：每行显示若干张卡牌，便于阅读
		 *
		 * 实现在 set.cpp 中
		 */
		void print(ostream &f) const;

		// ====================================================================
		// Ex23: STL 风格迭代器 (STL-style Iterator)
		// ====================================================================

		/**
		 * const_iterator: 符合 C++ 标准库风格的迭代器
		 *
		 * 设计目标：
		 * - 兼容 C++11 的 range-based for 循环
		 * - 遵循 STL 容器的迭代器接口规范
		 *
		 * 使用示例：
		 *   for(Plateau::const_iterator it = plateau.begin(); it != plateau.end(); ++it)
		 *       std::cout << *it << "\n";
		 *
		 *   // 或使用 range-based for
		 *   for(const Carte& c : plateau)
		 *       std::cout << c << "\n";
		 */
		class const_iterator
		{
		private:
			const Plateau &plateau; // Plateau 实例的 const 引用
			size_t index;			// 当前索引

			/**
			 * 构造函数：初始化迭代器位置
			 */
			const_iterator(const Plateau &p, size_t i) : plateau(p), index(i) {}

			friend class Plateau;

		public:
			/**
			 * operator++: 前缀递增运算符
			 *
			 * 用法：++it
			 * 返回：引用支持链式操作
			 */
			const_iterator &operator++()
			{
				index++;
				return *this;
			}

			/**
			 * operator!=: 不等于比较运算符
			 *
			 * 用途：range-based for 循环判断是否到达 end()
			 */
			bool operator!=(const const_iterator &other) const
			{
				return index != other.index;
			}

			/**
			 * operator==: 等于比较运算符
			 */
			bool operator==(const const_iterator &other) const
			{
				return index == other.index;
			}

			/**
			 * operator*: 解引用运算符
			 *
			 * 用法：*it
			 * 返回：当前位置的 Carte 引用
			 */
			const Carte &operator*() const
			{
				if (index >= plateau.nb)
					throw SetException("Iterator out of bounds");
				return *plateau.cartes[index];
			}
		};

		/**
		 * begin: 返回指向第一个元素的迭代器
		 */
		const_iterator begin() const { return const_iterator(*this, 0); }

		/**
		 * end: 返回指向"最后一个元素之后"的迭代器
		 */
		const_iterator end() const { return const_iterator(*this, nb); }

		/**
		 * cbegin: 返回 const 迭代器（C++11 标准）
		 */
		const_iterator cbegin() const { return begin(); }

		/**
		 * cend: 返回 const 迭代器（C++11 标准）
		 */
		const_iterator cend() const { return end(); }
	};

	/**
	 * 输出运算符重载：支持直接输出 Plateau 对象
	 * 使用方式：cout << plateau << endl;
	 */
	ostream &operator<<(ostream &f, const Plateau &c);

	// ========================================================================
	// Combinaison 类：三卡组合类 (Three-Card Combination Class)
	// ========================================================================

	/**
	 * Combinaison: 表示玩家选择的三张卡牌组合
	 *
	 * 设计要点（回答题目问题10、11）：
	 *
	 * 问题10：Carte 与 Combinaison 的关系
	 * - 聚合关系（Aggregation，空心菱形）
	 * - Combinaison 持有指向 Carte 的指针，但不拥有 Carte
	 * - Carte 的生命周期由 Jeu 管理
	 * - UML表示：Combinaison ◇——> Carte (1对3的聚合)
	 *
	 * 问题11：为什么可以使用 = default？
	 *
	 * 成员变量分析：
	 * - c1, c2, c3: 三个指针（const Carte*）
	 * - 指针是基本类型，可以安全地浅拷贝
	 * - 没有动态分配的资源需要管理
	 *
	 * = default 适用条件：
	 * - 所有成员都是值类型或指针
	 * - 不需要深拷贝（没有拥有的资源）
	 * - 编译器生成的版本满足需求
	 *
	 * 对比 Plateau：
	 * - Plateau 有动态数组，需要深拷贝
	 * - Combinaison 只有三个指针，浅拷贝即可
	 *
	 * 核心功能：
	 * - 存储三张卡牌的引用
	 * - 判断这三张卡是否构成有效的 SET
	 *
	 * SET 规则回顾：
	 * 对于每个特征（颜色、数量、形状、填充）：
	 * - 要么三张卡完全相同
	 * - 要么三张卡完全不同
	 * - 不允许"两同一异"的情况
	 */
	class Combinaison
	{
	private:
		// ====================================================================
		// 私有成员变量 (Private Member Variables)
		// ====================================================================

		/**
		 * c1, c2, c3: 指向三张卡牌的指针
		 *
		 * 类型：const Carte*
		 * - const: 不能通过指针修改卡牌
		 * - 指针: 不拥有卡牌，只是引用
		 *
		 * 为什么不用引用（const Carte&）？
		 * - 引用必须在构造时初始化，无法重新赋值
		 * - 指针更灵活，支持后续修改（虽然这里不需要）
		 * - 指针可以为 nullptr（虽然这里不会）
		 */
		const Carte *c1;
		const Carte *c2;
		const Carte *c3;

	public:
		// ====================================================================
		// 构造函数 (Constructor)
		// ====================================================================

		/**
		 * 构造函数：从三张卡牌创建组合
		 *
		 * 参数：C1, C2, C3 - 三张卡牌的引用
		 *
		 * 实现：使用初始化列表
		 * - c1(&C1): 获取 C1 的地址并赋给 c1
		 * - 存储的是地址，不是拷贝对象
		 *
		 * 设计选择：
		 * - 参数是引用：避免不必要的拷贝
		 * - 成员是指针：支持后续可能的修改
		 */
		Combinaison(const Carte &C1, const Carte &C2, const Carte &C3)
			: c1(&C1), c2(&C2), c3(&C3) {}

		// ====================================================================
		// 访问器方法 (Accessor Methods)
		// ====================================================================

		/**
		 * getCarte 系列：获取各张卡牌的引用
		 *
		 * 返回：*c1 解引用指针得到 Carte 对象
		 */
		const Carte &getCarte1() const { return *c1; }
		const Carte &getCarte2() const { return *c2; }
		const Carte &getCarte3() const { return *c3; }

		/**
		 * estUnSet: 判断这三张卡是否构成有效的 SET
		 *
		 * 规则：对于每个特征（颜色、形状、数量、填充）
		 * - 要么三个完全相同
		 * - 要么三个完全不同
		 *
		 * 数学表达：
		 * 对于特征 X：
		 * - 全同：X1 == X2 && X1 == X3
		 * - 全异：X1 != X2 && X1 != X3 && X2 != X3
		 *
		 * 实现算法：
		 * 1. 对四个特征分别检查
		 * 2. 每个特征返回 true/false
		 * 3. 四个结果进行 AND 运算
		 *
		 * 时间复杂度：O(1)（固定的4个特征检查）
		 *
		 * 实现在 set.cpp 中
		 */
		bool estUnSet() const;

		// ====================================================================
		// 特殊成员函数 (Special Member Functions)
		// ====================================================================

		/**
		 * 析构函数：使用默认实现
		 *
		 * 为什么 = default 足够？
		 * - 只有三个指针成员
		 * - 不拥有任何需要手动释放的资源
		 * - 指针指向的 Carte 由 Jeu 管理
		 */
		~Combinaison() = default;

		/**
		 * 拷贝构造函数：使用默认实现
		 *
		 * 默认行为：逐成员拷贝（浅拷贝）
		 * - c1, c2, c3 是指针，拷贝指针值
		 * - 两个 Combinaison 会指向相同的 Carte
		 * - 这是合理的，因为不拥有 Carte
		 */
		Combinaison(const Combinaison &c) = default;

		/**
		 * 赋值运算符：使用默认实现
		 *
		 * 默认行为：逐成员赋值
		 * 对于 Combinaison 来说已经足够
		 */
		Combinaison &operator=(const Combinaison &c) = default;
	};

	/**
	 * 输出运算符重载：格式化输出组合
	 * 格式：[卡1 ; 卡2 ; 卡3]
	 */
	ostream &operator<<(ostream &f, const Combinaison &c);

	// ========================================================================
	// Controleur 类：游戏控制器类 (Game Controller Class)
	// ========================================================================

	/**
	 * Controleur: 游戏控制器，管理游戏流程
	 *
	 * 设计要点（回答题目问题12、13）：
	 *
	 * 问题12：Controleur 与其他类的关系
	 *
	 * 1. Controleur ——> Jeu: 关联关系（引用）
	 *    - jeu 是引用成员，指向单例
	 *    - 不拥有 Jeu，Jeu 是全局单例
	 *    - UML: Controleur -----> Jeu
	 *
	 * 2. Controleur ◆——> Plateau: 组合关系
	 *    - plateau 是值成员（不是指针）
	 *    - Controleur 拥有并管理 Plateau 的生命周期
	 *    - Plateau 随 Controleur 创建和销毁
	 *    - UML: Controleur ◆——> Plateau
	 *
	 * 3. Controleur ◆——> Pioche: 组合关系
	 *    - pioche 是指针，指向动态分配的对象
	 *    - Controleur 负责 Pioche 的创建（new）和销毁（delete）
	 *    - Pioche 的生命周期完全由 Controleur 管理
	 *    - UML: Controleur ◆——> Pioche
	 *
	 * 为什么 Plateau 是值，Pioche 是指针？
	 * - Plateau: 可以在栈上创建，构造简单，无需指针
	 * - Pioche: 需要 Jeu 引用来初始化，构造函数调用在 Controleur
	 *          构造函数体内，必须用指针
	 *
	 * 问题13：为什么禁止拷贝？
	 * - 资源管理：pioche 是动态分配的，拷贝会导致问题
	 * - 语义不明：复制游戏控制器的含义不清
	 * - 单一控制：一个游戏应该只有一个控制器
	 *
	 * 职责说明：
	 * - 初始化游戏（创建牌堆、桌面）
	 * - 管理游戏流程（发牌等）
	 * - 提供访问游戏状态的接口
	 */
	class Controleur
	{
	private:
		// ====================================================================
		// 私有成员变量 (Private Member Variables)
		// ====================================================================

		/**
		 * jeu: Jeu 单例的引用
		 *
		 * 类型：Jeu& （引用）
		 * - 必须在初始化列表中初始化
		 * - 引用一旦绑定就不能改变
		 * - 指向全局唯一的 Jeu 实例
		 *
		 * 关系类型：关联（Association）
		 * - Controleur 使用 Jeu，但不拥有它
		 * - Jeu 的生命周期独立于 Controleur
		 */
		Jeu &jeu;

		/**
		 * plateau: 游戏桌面对象
		 *
		 * 类型：Plateau （值成员）
		 * - 不是指针，直接嵌入在 Controleur 中
		 * - 随 Controleur 自动创建和销毁
		 * - 使用 Plateau 的默认构造函数初始化
		 *
		 * 关系类型：组合（Composition）
		 * - Controleur 拥有 Plateau
		 * - Plateau 的生命周期与 Controleur 相同
		 * - Plateau 不能独立于 Controleur 存在
		 */
		Plateau plateau;

		/**
		 * pioche: 牌堆对象的指针
		 *
		 * 类型：Pioche* （指针）
		 * - 指向动态分配的 Pioche 对象
		 * - 在构造函数体内创建（new Pioche(jeu)）
		 * - 在析构函数中销毁（delete pioche）
		 *
		 * 为什么是指针而不是值？
		 * 1. Pioche 构造函数需要 jeu 参数
		 * 2. jeu 在初始化列表中才能获取
		 * 3. plateau 可以默认构造，所以可以是值
		 * 4. pioche 需要参数，必须在构造函数体内 new
		 *
		 * 关系类型：组合（Composition）
		 * - Controleur 拥有并管理 Pioche
		 * - Controleur 负责创建和销毁 Pioche
		 * - Pioche 的生命周期由 Controleur 控制
		 */
		Pioche *pioche;

	public:
		// ====================================================================
		// 构造函数 (Constructor)
		// ====================================================================

		/**
		 * 构造函数：初始化游戏控制器
		 *
		 * 初始化顺序：
		 * 1. 初始化列表：jeu(Jeu::getInstance())
		 *    - 获取 Jeu 单例的引用
		 *    - 必须在此处初始化（引用成员的要求）
		 *
		 * 2. 隐式调用：plateau 的默认构造函数
		 *    - Plateau() 会自动调用
		 *    - 创建空的桌面
		 *
		 * 3. 构造函数体：pioche = new Pioche(jeu)
		 *    - 动态分配 Pioche 对象
		 *    - 传入 jeu 引用初始化牌堆
		 *
		 * 为什么这样设计？
		 * - jeu 必须先初始化（引用的要求）
		 * - pioche 依赖 jeu（需要 jeu 作为参数）
		 * - plateau 独立，可以自动初始化
		 *
		 * 内存布局：
		 * - jeu: 引用（8字节，64位系统）
		 * - plateau: Plateau 对象（直接嵌入）
		 * - pioche: 指针（8字节，64位系统）
		 */
		Controleur() : jeu(Jeu::getInstance())
		{
			pioche = new Pioche(jeu); // 动态创建牌堆
		}

		// ====================================================================
		// 访问器方法 (Accessor Methods)
		// ====================================================================

		/**
		 * getPlateau: 获取桌面的常量引用
		 *
		 * 返回：const Plateau&
		 * - 避免拷贝
		 * - 保护桌面不被外部修改（const）
		 */
		const Plateau &getPlateau() const { return plateau; }

		/**
		 * getPioche: 获取牌堆的常量引用
		 *
		 * 返回：const Pioche&
		 * - *pioche 解引用指针得到对象
		 * - 返回引用避免拷贝
		 */
		const Pioche &getPioche() const { return *pioche; }

		// ====================================================================
		// 游戏逻辑方法 (Game Logic Methods)
		// ====================================================================

		/**
		 * distribuer: 将牌堆中的卡牌发到桌面
		 *
		 * 游戏规则：
		 * - 如果桌面卡牌数 < 12：补到 12 张
		 * - 如果桌面卡牌数 >= 12：只加 1 张
		 * - 如果牌堆为空：不做任何操作
		 *
		 * 算法：
		 * 1. 检查牌堆是否为空
		 * 2. 如果桌面 < 12，循环抽牌直到达到 12 或牌堆空
		 * 3. 否则，只抽一张牌
		 *
		 * 实现在 set.cpp 中
		 */
		void distribuer();

		// ====================================================================
		// 析构函数 (Destructor)
		// ====================================================================

		/**
		 * 析构函数：清理资源
		 *
		 * 必须做的事：
		 * - delete pioche: 释放动态分配的 Pioche 对象
		 *
		 * 自动完成的事：
		 * - plateau 的析构函数自动调用（值成员）
		 * - jeu 是引用，不需要销毁
		 *
		 * 三五法则（Rule of Three/Five）：
		 * - 如果需要自定义析构函数（因为 pioche）
		 * - 通常也需要自定义拷贝构造和赋值运算符
		 * - 这里选择禁用拷贝和赋值（= delete）
		 */
		~Controleur() { delete pioche; }

		// ====================================================================
		// 禁用拷贝和赋值 (Deleted Copy and Assignment)
		// ====================================================================

		/**
		 * 拷贝构造函数：已删除
		 *
		 * 为什么禁止？
		 * 1. pioche 是指针，浅拷贝会导致两个对象共享同一个 Pioche
		 * 2. 析构时会双重释放（double free）
		 * 3. jeu 是引用，拷贝后仍指向同一个 Jeu（可能不是问题）
		 * 4. plateau 可以拷贝，但整体语义不明确
		 * 5. 游戏控制器应该唯一，不应该复制
		 */
		Controleur(const Controleur &c) = delete;

		/**
		 * 赋值运算符：已删除
		 * 原因同上
		 */
		Controleur &operator=(const Controleur &c) = delete;
	};

}; // end of namespace Set

#endif // _SET_H
```

## main.cpp
```cpp
#include "set.h"
#include <vector>
#include <algorithm>
using namespace Set;

void f(Plateau &dest, const Plateau &source)
{
	dest = source;
}

// ============================================================================
// Ex23 功能函数 (Ex23 Functions)
// ============================================================================

/**
 * 题目 4：使用传统迭代器遍历所有卡牌
 */
void afficherCartes()
{
	Jeu &jeu = Jeu::getInstance();
	cout << "\n=== 使用 Iterator 遍历所有卡牌 ===" << endl;
	int count = 0;
	for (Jeu::Iterator it = jeu.first(); !it.isDone(); it.next())
	{
		cout << it.getCurrentItem() << " ";
		if (++count % 9 == 0)
			cout << "\n";
	}
	cout << "\n总共 " << count << " 张卡牌\n"
		 << endl;
}

/**
 * 题目 5：使用形状过滤迭代器遍历特定形状的卡牌
 */
void afficherCartes(Forme f)
{
	Jeu &jeu = Jeu::getInstance();
	cout << "\n=== 使用 FormeIterator 遍历形状为 " << f << " 的卡牌 ===" << endl;

	// 需要先找到第一张匹配的卡牌
	Jeu::FormeIterator it = jeu.firstFormeIterator(f);

	// 找到第一张匹配的卡牌
	while (!it.isDone() && it.getCurrentItem().getForme() != f)
		it.next();

	int count = 0;
	while (!it.isDone())
	{
		cout << it.getCurrentItem() << " ";
		if (++count % 9 == 0)
			cout << "\n";
		it.next();
	}
	cout << "\n总共 " << count << " 张 " << f << " 形状的卡牌\n"
		 << endl;
}

/**
 * 题目 6：使用 STL 风格迭代器遍历 Plateau
 */
void afficherCartes(const Plateau &p)
{
	cout << "\n=== 使用 STL 风格迭代器遍历 Plateau ===" << endl;
	int count = 0;
	for (Plateau::const_iterator it = p.begin(); it != p.end(); ++it)
	{
		cout << *it << " ";
		if (++count % 6 == 0)
			cout << "\n";
	}
	cout << "\n总共 " << count << " 张卡牌在 Plateau 上\n"
		 << endl;
}

/**
 * 查找 Plateau 中所有有效的 SET 组合
 */
std::vector<Combinaison> trouverTousSets(const Plateau &p)
{
	std::vector<Combinaison> sets;
	size_t n = p.getNbCartes();

	// 使用迭代器遍历所有三张卡的组合
	std::vector<const Carte *> cartes;
	for (Plateau::const_iterator it = p.begin(); it != p.end(); ++it)
	{
		cartes.push_back(&(*it));
	}

	// 三重循环检查所有可能的三张卡组合
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = i + 1; j < n; j++)
		{
			for (size_t k = j + 1; k < n; k++)
			{
				Combinaison combo(*cartes[i], *cartes[j], *cartes[k]);
				if (combo.estUnSet())
				{
					sets.push_back(combo);
				}
			}
		}
	}

	return sets;
}

/**
 * 题目 7：完整的 SET 游戏
 */
void jouerSet()
{
	cout << "\n";
	cout << "========================================" << endl;
	cout << "       欢迎来到 SET 纸牌游戏！         " << endl;
	cout << "========================================" << endl;
	cout << "\nSET 规则：" << endl;
	cout << "找出三张卡牌，对于每个特征（颜色、形状、数量、填充）" << endl;
	cout << "这三张卡必须全相同或全不同\n"
		 << endl;

	Controleur ctrl;
	ctrl.distribuer();

	cout << "当前桌面：" << endl;
	cout << ctrl.getPlateau() << endl;

	// 自动查找所有 SET
	cout << "正在查找所有可能的 SET 组合..." << endl;
	std::vector<Combinaison> sets = trouverTousSets(ctrl.getPlateau());

	if (sets.empty())
	{
		cout << "❌ 当前桌面上没有有效的 SET 组合！" << endl;
		cout << "需要从牌堆再发牌..." << endl;
	}
	else
	{
		cout << "✓ 找到 " << sets.size() << " 个有效的 SET 组合：\n"
			 << endl;
		for (size_t i = 0; i < sets.size(); i++)
		{
			cout << "SET #" << (i + 1) << ": " << sets[i] << endl;
		}
	}

	cout << "\n剩余牌堆卡牌数: " << ctrl.getPioche().getNbCartes() << endl;
}

int main()
{
	try
	{
		// Test 1: Display all possible values
		cout << "=== Test 1: Display characteristic values ===" << endl;
		printCouleurs();
		printNombres();
		printFormes();
		printRemplissages();
		cout << endl;

		// Test 2: Get Jeu instance and display some cards
		cout << "=== Test 2: Display some cards from Jeu ===" << endl;
		Jeu &j = Jeu::getInstance();
		for (size_t i = 0; i < 10; i++)
			cout << j.getCarte(i) << "\n";
		cout << endl;

		// Test 3: Use Iterator
		cout << "=== Test 3: Iterate using Iterator ===" << endl;
		Jeu::Iterator it = j.first();
		int count = 0;
		while (!it.isDone() && count < 10)
		{
			cout << it.getCurrentItem();
			it.next();
			count++;
		}
		cout << "\n"
			 << endl;

		// Test 4: Use const_iterator with range-based for loop
		cout << "=== Test 4: Range-based for loop ===" << endl;
		count = 0;
		for (const Carte &c : j)
		{
			cout << c << "\n";
			if (++count >= 10)
				break;
		}
		cout << endl;

		// Test 5: Test Plateau operations
		cout << "=== Test 5: Plateau operations ===" << endl;
		Plateau p1;
		p1.ajouter(j.getCarte(0));
		p1.ajouter(j.getCarte(1));
		p1.ajouter(j.getCarte(2));
		cout << "Plateau p1:" << endl;
		cout << p1;

		Plateau p2;
		p2.ajouter(j.getCarte(3));
		p2.ajouter(j.getCarte(4));
		cout << "Plateau p2:" << endl;
		cout << p2;

		// Test copy constructor
		Plateau p3(p1);
		cout << "Plateau p3 (copy of p1):" << endl;
		cout << p3;

		// Test assignment operator
		p2 = p1;
		cout << "Plateau p2 after p2 = p1:" << endl;
		cout << p2;
		cout << endl;

		// Test 6: Combinaison and estUnSet
		cout << "=== Test 6: Test Combinaison ===" << endl;
		Combinaison combo1(j.getCarte(0), j.getCarte(1), j.getCarte(2));
		cout << "Combinaison: " << combo1 << endl;
		cout << "Est un SET? " << (combo1.estUnSet() ? "Oui" : "Non") << endl;
		cout << endl;

		// Test 7: Controleur
		cout << "=== Test 7: Test Controleur ===" << endl;
		Controleur ctrl;
		ctrl.distribuer();
		cout << ctrl.getPlateau();
		cout << "Nombre de cartes dans la pioche: " << ctrl.getPioche().getNbCartes() << endl;
		cout << endl;

		// ====================================================================
		// Ex23 测试：单例模式和迭代器模式
		// ====================================================================
		cout << "\n";
		cout << "============================================================" << endl;
		cout << "               Ex23: 单例模式与迭代器模式测试               " << endl;
		cout << "============================================================" << endl;

		// 题目 1-3: 单例模式测试
		cout << "\n=== 题目 1-3: 单例模式测试 ===" << endl;
		Jeu &jeu1 = Jeu::getInstance();
		Jeu &jeu2 = Jeu::getInstance();
		cout << "Jeu 单例测试：" << endl;
		cout << "  jeu1 地址: " << &jeu1 << endl;
		cout << "  jeu2 地址: " << &jeu2 << endl;
		cout << "  是否为同一实例: " << (&jeu1 == &jeu2 ? "是 ✓" : "否 ✗") << endl;
		cout << "  总卡牌数: " << jeu1.getNbCartes() << endl;

		// 题目 4: 传统迭代器
		afficherCartes();

		// 题目 5: 形状过滤迭代器
		afficherCartes(Forme::ovale);
		afficherCartes(Forme::vague);
		afficherCartes(Forme::losange);

		// 题目 6: STL 风格迭代器 - Jeu
		cout << "\n=== STL 风格迭代器遍历 Jeu（前 20 张）===" << endl;
		int count2 = 0;
		for (const Carte &c : Jeu::getInstance())
		{
			cout << c << " ";
			if (++count2 >= 20)
				break;
			if (count2 % 10 == 0)
				cout << "\n";
		}
		cout << "\n"
			 << endl;

		// 题目 6: STL 风格迭代器 - Plateau
		Plateau testPlateau;
		Jeu &jeu = Jeu::getInstance();
		for (size_t i = 0; i < 12; i++)
		{
			testPlateau.ajouter(jeu.getCarte(i));
		}
		afficherCartes(testPlateau);

		// 使用 range-based for 遍历 Plateau
		cout << "\n=== 使用 range-based for 遍历 Plateau ===" << endl;
		int count3 = 0;
		for (const Carte &c : testPlateau)
		{
			cout << c << " ";
			if (++count3 % 6 == 0)
				cout << "\n";
		}
		cout << "\n"
			 << endl;

		// 题目 7: 完整的 SET 游戏
		cout << "\n";
		cout << "============================================================" << endl;
		cout << "                  题目 7: 完整的 SET 游戏                   " << endl;
		cout << "============================================================" << endl;
		jouerSet();

		// 额外测试：多次发牌直到找到 SET
		cout << "\n\n=== 额外测试：多次尝试找到 SET ===" << endl;
		Controleur ctrl2;
		int attempts = 0;
		const int maxAttempts = 5;

		while (attempts < maxAttempts)
		{
			attempts++;
			ctrl2.distribuer();

			cout << "\n第 " << attempts << " 次尝试：" << endl;
			cout << "桌面卡牌数: " << ctrl2.getPlateau().getNbCartes() << endl;

			std::vector<Combinaison> foundSets = trouverTousSets(ctrl2.getPlateau());

			if (!foundSets.empty())
			{
				cout << "✓ 找到 " << foundSets.size() << " 个 SET！" << endl;
				cout << "显示第一个 SET: " << foundSets[0] << endl;
				break;
			}
			else
			{
				cout << "✗ 未找到 SET，继续发牌..." << endl;
			}

			if (ctrl2.getPioche().getNbCartes() == 0)
			{
				cout << "牌堆已空，游戏结束。" << endl;
				break;
			}
		}

		cout << "\n";
		cout << "============================================================" << endl;
		cout << "                    Ex23 测试完成！                         " << endl;
		cout << "============================================================" << endl;
	}
	catch (SetException &e)
	{
		std::cout << "Exception: " << e.getInfo() << "\n";
	}

	return 0;
}
```

## set.cpp
```cpp
/**
 * ============================================================================
 * SET 游戏实现文件 (SET Game Implementation)
 * ============================================================================
 *
 * 本文件包含 set.h 中声明的所有类和函数的实现。
 *
 * 主要内容：
 * 1. 枚举值列表的定义
 * 2. 枚举类型的转换和输出函数
 * 3. Carte、Jeu、Pioche、Plateau 等类的方法实现
 * 4. SET 判断逻辑的实现
 */

#include "set.h"
#include <cstdlib> // 提供 rand() 函数用于随机抽牌

namespace Set
{
	// ========================================================================
	// 全局常量列表定义 (Global Constant Lists Definition)
	// ========================================================================

	/**
	 * 特征值列表：定义每个特征的所有可能值
	 *
	 * 使用 initializer_list 的好处：
	 * - 可以在 range-based for 循环中遍历
	 * - 类型安全，编译期检查
	 * - 常量存储，不可修改
	 *
	 * 这些列表用于：
	 * 1. 生成所有 81 张卡牌（4 层嵌套循环）
	 * 2. 打印所有可能的特征值
	 * 3. 测试和验证
	 */
	std::initializer_list<Couleur> Couleurs = {Couleur::rouge, Couleur::mauve, Couleur::vert};
	std::initializer_list<Nombre> Nombres = {Nombre::un, Nombre::deux, Nombre::trois};
	std::initializer_list<Forme> Formes = {Forme::ovale, Forme::vague, Forme::losange};
	std::initializer_list<Remplissage> Remplissages = {Remplissage::plein, Remplissage::vide, Remplissage::hachure};

	string toString(Couleur c)
	{
		switch (c)
		{
		case Couleur::rouge:
			return "R";
		case Couleur::mauve:
			return "M";
		case Couleur::vert:
			return "V";
		default:
			throw SetException("Couleur inconnue");
		}
	}

	string toString(Nombre v)
	{
		switch (v)
		{
		case Nombre::un:
			return "1";
		case Nombre::deux:
			return "2";
		case Nombre::trois:
			return "3";
		default:
			throw SetException("Nombre inconnue");
		}
	}

	string toString(Forme f)
	{
		switch (f)
		{
		case Forme::ovale:
			return "O";
		case Forme::vague:
			return "~";
		case Forme::losange:
			return "\004";
		default:
			throw SetException("Forme inconnue");
		}
	}

	string toString(Remplissage r)
	{
		switch (r)
		{
		case Remplissage::plein:
			return "P";
		case Remplissage::vide:
			return "_";
		case Remplissage::hachure:
			return "H";
		default:
			throw SetException("Remplissage inconnu");
		}
	}

	std::ostream &operator<<(std::ostream &f, Couleur c)
	{
		f << toString(c);
		return f;
	}
	std::ostream &operator<<(std::ostream &f, Nombre v)
	{
		f << toString(v);
		return f;
	}
	std::ostream &operator<<(std::ostream &f, Forme x)
	{
		f << toString(x);
		return f;
	}
	std::ostream &operator<<(std::ostream &f, Remplissage r)
	{
		f << toString(r);
		return f;
	}

	void printCouleurs(std::ostream &f)
	{
		for (auto c : Couleurs)
			f << c << " ";
		f << "\n";
	}

	void printNombres(std::ostream &f)
	{
		for (auto v : Nombres)
			f << v << " ";
		f << "\n";
	}

	void printFormes(std::ostream &f)
	{
		for (auto x : Formes)
			f << x << " ";
		f << "\n";
	}

	void printRemplissages(std::ostream &f)
	{
		for (auto r : Remplissages)
			f << r << " ";
		f << "\n";
	}

	ostream &operator<<(ostream &f, const Carte &c)
	{
		f << "[" << c.getCouleur() << c.getForme()
		  << c.getNombre() << c.getRemplissage() << "]";
		return f;
	}

	Jeu::Jeu()
	{
		size_t i = 0;
		for (auto c : Couleurs)
			for (auto n : Nombres)
				for (auto f : Formes)
					for (auto r : Remplissages)
						cartes[i++] = new Carte(c, n, f, r);
	}

	const Carte &Jeu::getCarte(size_t i) const
	{
		if (i >= 81)
			throw SetException("carte iexistante");
		return *cartes[i];
	}

	Jeu::~Jeu()
	{
		for (size_t i = 0; i < 81; i++)
			delete cartes[i];
	}

	const Carte &Pioche::piocher()
	{ // get a random carte from the pioche
		// test if the pioche is not empty
		if (estVide())
			throw SetException("empty pioche");
		// choose a carte
		size_t i = rand() % nb; // get a random number between 0 and nb
		const Carte *chosenCarte = cartes[i];
		// remove the card from the array
		cartes[i] = cartes[nb - 1]; // replace carte i by the last carte of the pioche
		nb--;
		return *chosenCarte; // returns a reference over the chosen carte
	}

	/**
	 * 向游戏台添加一张卡牌 (Add a card to the plateau)
	 *
	 * @param c 要添加的卡牌的常量引用
	 *
	 * 实现要点：
	 * 1. 动态扩容机制
	 *    - 当数组满时，自动扩容（增加 5 个位置）
	 *    - 将旧数组内容复制到新数组
	 *    - 释放旧数组内存
	 *
	 * 2. 为什么存储指针而不是对象？
	 *    - 卡牌对象由 Jeu 类管理（81 张固定卡牌）
	 *    - 避免重复创建和销毁卡牌对象
	 *    - 节省内存，提高性能
	 *
	 * 3. 扩容步长为什么是 5？
	 *    - 平衡内存使用和分配次数
	 *    - SET 游戏通常每次添加 3 张牌
	 *    - 5 是合理的小步长
	 */
	void Plateau::ajouter(const Carte &c)
	{
		// 检查数组是否已满
		if (nb == nbMax)
		{
			// 数组所有位置都已使用，需要扩容

			// 创建一个更大的数组（增加 5 个位置）
			const Carte **newarray = new const Carte *[nbMax + 5];

			// 将所有卡牌的地址复制到新数组
			for (size_t i = 0; i < nb; i++)
				newarray[i] = cartes[i];

			// 保存旧数组的指针以便后续释放
			const Carte **old = cartes;

			// 将新数组设置为当前使用的数组
			cartes = newarray;

			// 更新最大容量
			nbMax += 5;

			// 释放旧数组的内存（注意：只释放数组本身，不释放卡牌对象）
			delete[] old;
		}

		// 现在可以确定有足够的空间来存储更多卡牌
		// 将新卡牌的地址存储到数组末尾
		cartes[nb] = &c;

		// 增加已存储卡牌的数量
		nb++;
	}

	/**
	 * 从游戏台移除一张卡牌 (Remove a card from the plateau)
	 *
	 * @param c 要移除的卡牌的常量引用
	 * @throws SetException 如果卡牌不存在于游戏台
	 *
	 * 实现策略：
	 * 1. 线性搜索要移除的卡牌（比较指针地址）
	 * 2. 用最后一张卡牌替换要移除的卡牌（避免移动大量元素）
	 * 3. 减少卡牌计数
	 *
	 * 时间复杂度：O(n) - 需要搜索卡牌
	 * 优点：移除操作本身是 O(1)
	 * 缺点：不保持卡牌顺序（但 SET 游戏不需要保持顺序）
	 */
	void Plateau::retirer(const Carte &c)
	{
		// 在数组中搜索要移除的卡牌
		size_t i = 0;
		while (i < nb && cartes[i] != &c) // 比较指针地址
			i++;

		// 如果遍历完整个数组都没找到，说明卡牌不存在
		if (i == nb)
			throw SetException("this card does not exist");

		// 用最后一张卡牌替换要移除的卡牌（高效的移除方法）
		cartes[i] = cartes[nb - 1];

		// 减少卡牌计数（原来的最后一张卡牌现在不再有效）
		nb--;
	}

	/**
	 * 拷贝构造函数 (Copy Constructor)
	 *
	 * @param p 要拷贝的源 Plateau 对象
	 *
	 * 为什么需要自定义拷贝构造函数？
	 * =====================================
	 * 如果使用默认拷贝构造函数（编译器自动生成）：
	 * - 会执行浅拷贝：只复制指针 cartes 的值
	 * - 结果：两个 Plateau 对象的 cartes 指向同一个数组
	 * - 问题：修改一个对象会影响另一个对象
	 * - 更严重：析构时会导致双重释放（double free）错误
	 *
	 * 深拷贝实现：
	 * ===========
	 * 1. 为新对象分配独立的数组
	 * 2. 复制所有卡牌指针（注意：复制的是指针，不是卡牌对象）
	 * 3. 复制容量和大小信息
	 *
	 * 结果：每个 Plateau 有自己的数组，但指向相同的卡牌对象
	 */
	Plateau::Plateau(const Plateau &p)
	{
		// 为新 Plateau 分配独立的数组（深拷贝）
		cartes = new const Carte *[p.nbMax];

		// 复制源对象的容量和大小信息
		nb = p.nb;
		nbMax = p.nbMax;

		// 复制所有卡牌指针
		for (size_t i = 0; i < p.nb; i++)
			cartes[i] = p.cartes[i];

		// 现在每个 Plateau 都有自己的数组，但包含相同的卡牌
	}

	/**
	 * 赋值运算符重载 (Assignment Operator)
	 *
	 * @param p 要赋值的源 Plateau 对象
	 * @return 返回当前对象的引用（支持链式赋值）
	 *
	 * 实现要点：
	 * =========
	 * 1. 自赋值检查：if (this != &p)
	 *    - 防止 a = a 这样的操作导致问题
	 *    - 提高性能（避免不必要的操作）
	 *
	 * 2. 赋值策略：
	 *    - 清空当前 Plateau（设置 nb = 0）
	 *    - 保留现有数组容量（避免重新分配）
	 *    - 使用 ajouter() 逐个添加卡牌
	 *    - ajouter() 会在需要时自动扩容
	 *
	 * 3. 为什么不直接复制数组？
	 *    - 利用现有的 ajouter() 逻辑
	 *    - 自动处理扩容
	 *    - 代码复用，减少错误
	 *
	 * 4. 返回 *this 的作用：
	 *    - 支持链式赋值：a = b = c
	 *    - 符合 C++ 赋值运算符的惯例
	 */
	Plateau &Plateau::operator=(const Plateau &p)
	{
		// 检查是否为自赋值（a = a）
		if (this != &p)
		{
			// 注意：此时 *this 和 p 都有各自的数组

			// 清空当前数组（但保留容量）
			nb = 0;
			// 我们认为数组中不再有卡牌
			// 但保留数组的容量，可以继续存储新的指针

			// 从源对象复制所有卡牌
			for (size_t i = 0; i < p.nb; i++)
				ajouter(*p.cartes[i]); // 添加 p 中的每张卡牌
									   // 如果需要，ajouter 会自动扩容
		}

		// 返回当前对象的引用（支持链式赋值）
		return *this;
	}

	/**
	 * 判断三张卡牌是否构成一个 SET (Check if three cards form a SET)
	 *
	 * @return true 如果三张卡牌构成 SET，false 否则
	 *
	 * SET 游戏规则：
	 * =============
	 * 三张卡牌构成一个 SET 当且仅当：
	 * 对于每个特征（颜色、形状、数量、填充），这三张卡牌要么：
	 * - 完全相同（3 张都一样）
	 * - 完全不同（3 张都不一样）
	 *
	 * 示例：
	 * ------
	 * ✓ 合法 SET：[R◇1P] [M◇2P] [V◇3P]
	 *   - 颜色：R, M, V（全不同）✓
	 *   - 形状：◇, ◇, ◇（全相同）✓
	 *   - 数量：1, 2, 3（全不同）✓
	 *   - 填充：P, P, P（全相同）✓
	 *
	 * ✗ 非法组合：[R◇1P] [R◇2P] [V◇3P]
	 *   - 颜色：R, R, V（两同一异）✗
	 *
	 * 实现逻辑：
	 * =========
	 * 对于每个特征，检查：
	 * - 条件1：c1 == c2 && c1 == c3  （全相同）
	 * - 条件2：c1 != c2 && c1 != c3 && c2 != c3  （全不同）
	 *
	 * 原先代码中好像最后一个写错了
	 * 当前条件2写的是：c1 != c2 && c1 != c3 && c2 == c3
	 * 这实际上允许"两同一异"的情况，违反了 SET 规则
	 * 正确的应该是：c1 != c2 && c1 != c3 && c2 != c3
	 */
	bool Combinaison::estUnSet() const
	{
		// 测试颜色：全相同 或 全不同
		// ⚠️ BUG：第二个条件允许 c2 == c3，应该是三者都不同
		bool test1 = (c1->getCouleur() == c2->getCouleur() && c1->getCouleur() == c3->getCouleur()) ||
					 (c1->getCouleur() != c2->getCouleur() && c1->getCouleur() != c3->getCouleur() && c2->getCouleur() != c3->getCouleur());

		// 测试形状：全相同 或 全不同
		bool test2 = (c1->getForme() == c2->getForme() && c1->getForme() == c3->getForme()) ||
					 (c1->getForme() != c2->getForme() && c1->getForme() != c3->getForme() && c2->getForme() != c3->getForme());

		// 测试数量：全相同 或 全不同
		bool test3 = (c1->getNombre() == c2->getNombre() && c1->getNombre() == c3->getNombre()) ||
					 (c1->getNombre() != c2->getNombre() && c1->getNombre() != c3->getNombre() && c2->getNombre() != c3->getNombre());

		// 测试填充：全相同 或 全不同
		bool test4 = (c1->getRemplissage() == c2->getRemplissage() && c1->getRemplissage() == c3->getRemplissage()) ||
					 (c1->getRemplissage() != c2->getRemplissage() && c1->getRemplissage() != c3->getRemplissage() && c2->getRemplissage() != c3->getRemplissage());

		// 所有四个特征都必须满足规则
		return test1 && test2 && test3 && test4;
	}

	/**
	 * 从牌堆向游戏台分发卡牌 (Distribute cards from pioche to plateau)
	}

	/**
	 * 从牌堆向游戏台分发卡牌 (Distribute cards from pioche to plateau)
	 *
	 * 分发规则：
	 * =========
	 * 1. 如果游戏台少于 12 张牌：
	 *    - 尝试补齐到 12 张
	 *    - 从牌堆抽取卡牌，直到达到 12 张或牌堆为空
	 *
	 * 2. 如果游戏台已有 12 张或更多牌：
	 *    - 只添加 1 张牌
	 *    - 用于玩家找不到 SET 时增加选择
	 *
	 * 3. 如果牌堆为空：
	 *    - 什么都不做
	 *    - 游戏可能即将结束
	 *
	 * 实现细节：
	 * =========
	 * - 先添加一张牌（确保至少尝试添加一次）
	 * - 然后检查是否需要继续补充（少于 12 张）
	 * - 使用 while 循环持续抽牌，直到达到条件
	 *
	 * 为什么是 12 张？
	 * ==============
	 * - SET 游戏标准规则：游戏台应始终有 12 张牌
	 * - 12 = 3×4，便于视觉布局（3 行 4 列或 4 行 3 列）
	 * - 统计上，12 张牌中存在 SET 的概率很高
	 */
	void Controleur::distribuer()
	{
		// 如果牌堆不为空，先添加一张牌
		if (!pioche->estVide())
			plateau.ajouter(pioche->piocher());

		// 如果游戏台少于 12 张牌，继续补充
		while (!pioche->estVide() && plateau.getNbCartes() < 12)
			plateau.ajouter(pioche->piocher());
	}

	/**
	 * Combinaison 类的输出运算符重载 (Output operator for Combinaison)
	 *
	 * @param f 输出流对象（如 cout, ofstream 等）
	 * @param c 要输出的组合对象
	 * @return 返回输出流对象（支持链式输出）
	 *
	 * 输出格式：[卡牌1 ; 卡牌2 ; 卡牌3]
	 * 示例：[[R◇1P] ; [M◇2P] ; [V◇3P]]
	 */
	ostream &operator<<(ostream &f, const Combinaison &c)
	{
		f << "[" << c.getCarte1() << " ; " << c.getCarte2() << " ; " << c.getCarte3() << "]";
		return f;
	}

	/**
	 * 打印游戏台的所有卡牌 (Print all cards on the plateau)
	 *
	 * @param f 输出流对象
	 *
	 * 显示格式：
	 * =================== PLATEAU ===================
	 * [卡牌1][卡牌2][卡牌3]
	 * [卡牌4][卡牌5][卡牌6]
	 * ...
	 * ===============================================
	 *
	 * 布局规则：
	 * - 每 3 张卡牌换行
	 * - 便于玩家观察和寻找 SET
	 * - 上下装饰线使输出更清晰
	 */
	void Plateau::print(ostream &f) const
	{
		f << "=================== PLATEAU ===================\n";

		// 遍历并打印所有卡牌
		for (size_t i = 0; i < nb; i++)
		{
			// 每 3 张卡牌换行（创建类似网格的布局）
			if (i % 3 == 0)
				f << "\n";

			// 打印卡牌（自动调用 Carte 的 operator<<）
			f << *cartes[i];
		}

		f << "\n===============================================\n";
	}

	/**
	 * Plateau 类的输出运算符重载 (Output operator for Plateau)
	 *
	 * @param f 输出流对象
	 * @param c Plateau 对象
	 * @return 返回输出流对象（支持链式输出）
	 *
	 * 委托给 print() 方法实现
	 * 使用方法：cout << plateau;
	 */
	ostream &operator<<(ostream &f, const Plateau &c)
	{
		c.print(f);
		return f;
	}

}
```


# Ex23
```cpp
/*
要求实现单例模式和迭代器模式
详情请看 Ex22&23 文件夹中的 const_iterator 类
*/```

