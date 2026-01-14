#include "evenement.h"

namespace TIME
{

    /* =======================
     * Evt1j
     * ======================= */
    Evt1j::Evt1j(const Date &d, const std::string &s)
        : date(d), sujet(s)
    {
        std::cout << "construction d'un objet de la classe Evt1j\n";
    }

    Evt1j::~Evt1j()
    {
        std::cout << "destruction d'un objet de la classe Evt1j\n";
    }

    const Date &Evt1j::getDate() const
    {
        return date;
    }

    const std::string &Evt1j::getDescription() const
    {
        return sujet;
    }

    void Evt1j::afficher(std::ostream &f) const
    {
        f << "***** Evt ********\n";
        f << "Date=" << date << " sujet=" << sujet << "\n";
    }

    /* =======================
     * Evt1jDur
     * ======================= */
    Evt1jDur::Evt1jDur(const Date &d,
                       const std::string &s,
                       const Horaire &h,
                       const Duree &du)
        : Evt1j(d, s), debut(h), duree(du)
    {
        std::cout << "construction d'un objet de la classe Evt1jDur\n";
    }

    Evt1jDur::~Evt1jDur()
    {
        std::cout << "destruction d'un objet de la classe Evt1jDur\n";
    }

    const Horaire &Evt1jDur::getHoraire() const
    {
        return debut;
    }

    const Duree &Evt1jDur::getDuree() const
    {
        return duree;
    }

    void Evt1jDur::afficher(std::ostream &f) const
    {
        Evt1j::afficher(f);
        f << "Debut=" << debut << " Duree=" << duree << "\n";
    }

    /* =======================
     * Rdv
     * ======================= */
    Rdv::Rdv(const Date &d,
             const std::string &s,
             const Horaire &h,
             const Duree &du,
             const std::string &pers,
             const std::string &l)
        : Evt1jDur(d, s, h, du), personnes(pers), lieu(l)
    {
        std::cout << "construction d'un objet de la classe Rdv\n";
    }

    Rdv::~Rdv()
    {
        std::cout << "destruction d'un objet de la classe Rdv\n";
    }

    const std::string &Rdv::getPersonnes() const
    {
        return personnes;
    }

    const std::string &Rdv::getLieu() const
    {
        return lieu;
    }

    void Rdv::afficher(std::ostream &f) const
    {
        Evt1jDur::afficher(f);
        f << "Personnes=" << personnes
          << " Lieu=" << lieu << "\n";
    }

} // namespace TIME