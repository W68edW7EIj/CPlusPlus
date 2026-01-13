#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include "Widget.h"

class Card; // 前向声明：只使用指针、不需要完整定义
// 如果是 #include "Card.h" 的话，由于后者也引用了前者，那么就循环依赖了

class Button : public Widget
{
protected:
    std::string intitule;
    Card *owner;

public:
    Button(const std::string &i, Card *c);

    void onClick();
    void afficher() override;

    std::string getIntitule() const;
};

#endif