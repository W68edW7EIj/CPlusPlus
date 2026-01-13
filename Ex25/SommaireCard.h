// 如果只有 Card 那么只能顺序跳转，不能直接跳到某一章

#ifndef SOMMAIRECARD_H
#define SOMMAIRECARD_H

#include "Card.h"
#include <vector>

class SommaireCard : public Card
{
    std::vector<Card *> chapitres; // 维护索引表
    // 如果这个索引表放到了 Card 里面的话每张卡都知道了互相的存在，所以需要剥离到 SommaireCard 中

public:
    void addChapitre(Card *c);
    void handleClick(const std::string &intitule) override;
};

#endif