#include "evenement2.h"

namespace TIME
{
    // 拷贝构造函数
    Rdv::Rdv(const Rdv &other)
        : Evt1jDur(other),
          personnes(other.personnes),
          lieu(other.lieu)
    {
        std::cout << "copie d'un objet de la classe Rdv\n";
    }

    // 赋值运算
    Rdv &Rdv::operator=(const Rdv &other)
    {
        if (this != &other)
        {
            Evt1jDur::operator=(other); // appel à l'opérateur d'affectation de la classe de base
            personnes = other.personnes;
            lieu = other.lieu;
        }
        return *this;
    }

    // 析构
    Rdv::~Rdv()
    {
        std::cout << "destruction d'un objet de la classe Rdv\n";
    }
}