// 窗口类、抽象类，用于表示卡片中所有可视对象的公共父类
// 如果没有它 Card 就会知道太多UI细节，UML就不干净。通过 Widget，Card 能通过多态方式管理不同类型的界面元素，而不依赖于其具体实现，从而保证系统的可扩展性和职责分离。

#ifndef WIDGET_H
#define WIDGET_H

class Widget
{
public:
    virtual void afficher() = 0;
    virtual ~Widget() = default;
};

#endif