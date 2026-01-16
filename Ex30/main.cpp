#include <iostream>
#include "agenda.h"

int main()
{
    using namespace TIME;

    // 1) 验证抽象类不可实例化（取消注释会编译失败）
    // Evt e("test"); // error: cannot declare variable 'e' to be of abstract type 'Evt'

    Evt1j e1(Date(4, 10, 1957), "Spoutnik");
    Evt1jDur e2(Date(11, 6, 2013), "Lancement Longue Marche", Horaire(17, 38), Duree(10));
    Rdv e3(Date(12, 11, 2013), "reunion UV", Horaire(17, 30), Duree(60), "Intervenants UV", "bureau");
    EvtPj e4(Date(1, 5, 2026), Date(3, 5, 2026), "Festival 3 jours");

    Agenda ag;
    ag << e1 << e2 << e3 << e4;

    ag.afficher();

    std::cout << "\n===== operator<< polymorphe =====\n";
    Evt *p = &e4;
    std::cout << *p;

    return 0;
}