#include <iostream>
#include "evenement.h"

int main()
{
    using namespace TIME;

    {
        Rdv e(
            Date(11, 11, 2013),
            "reunion UV",
            Horaire(17, 30),
            Duree(60),
            "Intervenants UV",
            "bureau");

        std::cout << "RDV:\n";
        e.afficher();
    }

    return 0;
}