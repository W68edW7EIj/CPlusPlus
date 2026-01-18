#include <iostream>
#include <typeinfo>
#include "evenement.h" // 含 Evt1j / Evt1jDur / Rdv
using namespace TIME;

int main()
{
    Evt1j e1(Date(4, 10, 1957), "Spoutnik");
    Evt1j e2(Date(11, 6, 2013), "Shenzhou");
    Evt1jDur e3(Date(11, 6, 2013), "Lancement de Longue Marche",
                Horaire(17, 38), Duree(10));
    Rdv e4(Date(11, 4, 2013), "reunion UV",
           Horaire(17, 30), Duree(60), "Intervenants UV", "bureau");

    Evt1j *pt1 = &e1;
    Evt1j *pt2 = &e2;
    Evt1j *pt3 = &e3;
    Evt1j *pt4 = &e4;

    Evt1j &ref1 = e1;
    Evt1j &ref2 = e2;
    Evt1j &ref3 = e3;
    Evt1j &ref4 = e4;

    std::cout << "=== Down-cast via pointeurs ===\n";
    Evt1j *pts[] = {pt1, pt2, pt3, pt4};
    for (int i = 0; i < 4; ++i)
    {
        Rdv *p = dynamic_cast<Rdv *>(pts[i]);
        if (p)
        {
            std::cout << "pt" << (i + 1) << " est un Rdv:\n";
            p->afficher();
        }
        else
        {
            std::cout << "pt" << (i + 1) << " n'est pas un Rdv\n";
        }
    }

    std::cout << "\n=== Down-cast via references ===\n";
    Evt1j *refs[] = {&ref1, &ref2, &ref3, &ref4};
    for (int i = 0; i < 4; ++i)
    {
        try
        {
            Rdv &r = dynamic_cast<Rdv &>(*refs[i]);
            std::cout << "ref" << (i + 1) << " est un Rdv:\n";
            r.afficher();
        }
        catch (const std::bad_cast &)
        {
            std::cout << "ref" << (i + 1) << " n'est pas un Rdv\n";
        }
    }

    return 0;
}