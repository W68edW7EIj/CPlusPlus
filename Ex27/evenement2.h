#ifndef EVENEMENT_H2
#define EVENEMENT_H2

#include <iostream>
#include <string>
#include "timing.h"
#include "evenement.h"

namespace TIME
{
    class Rdv : public Evt1jDur
    {
    private:
        std::string personnes;
        std::string lieu;

    public:
        Rdv(const Date &d,
            const std::string &s,
            const Horaire &h,
            const Duree &du,
            const std::string &pers,
            const std::string &l);

        // === Exercice 27 ===
        Rdv(const Rdv &other);            // constructeur de copie
        Rdv &operator=(const Rdv &other); // opérateur d'affectation

        ~Rdv();

        void afficher(std::ostream &f = std::cout) const override;
    };

} // namespace TIME

#endif