#ifndef AGENDA_H
#define AGENDA_H

#include <vector>
#include <iostream>
#include "evenement.h"

namespace TIME
{

    class Agenda
    {
    private:
        std::vector<Evt *> evenements; // Ex30：存 Evt*（不再是 Evt1j*）

        Agenda(const Agenda &) = delete;            // 禁止复制
        Agenda &operator=(const Agenda &) = delete; // 禁止赋值

    public:
        Agenda() = default;
        ~Agenda() = default; // 不拥有对象：不 delete

        Agenda &operator<<(Evt &e); // Ex30：参数改为 Evt&

        void afficher(std::ostream &f = std::cout) const;
    };

} // namespace TIME

#endif