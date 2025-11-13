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
