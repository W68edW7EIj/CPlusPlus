#include "evenement.h"

namespace TIME
{

    /* ===== Evt ===== */
    Evt::Evt(const std::string &s) : sujet(s) {}

    Evt::~Evt() = default;

    const std::string &Evt::getDescription() const
    {
        return sujet;
    }

    std::ostream &operator<<(std::ostream &os, const Evt &e)
    {
        e.afficher(os); // 多态关键点：调用虚函数
        return os;
    }

    /* ===== Evt1j ===== */
    Evt1j::Evt1j(const Date &d, const std::string &s)
        : Evt(s), date(d) {}

    Evt1j::~Evt1j() = default;

    const Date &Evt1j::getDate() const { return date; }

    void Evt1j::afficher(std::ostream &f) const
    {
        f << "***** Evt1j *****\n";
        f << "Date=" << date << " sujet=" << getDescription() << "\n";
    }

    /* ===== Evt1jDur ===== */
    Evt1jDur::Evt1jDur(const Date &d,
                       const std::string &s,
                       const Horaire &h,
                       const Duree &du)
        : Evt1j(d, s), debut(h), duree(du) {}

    Evt1jDur::~Evt1jDur() = default;

    const Horaire &Evt1jDur::getHoraire() const { return debut; }
    const Duree &Evt1jDur::getDuree() const { return duree; }

    void Evt1jDur::afficher(std::ostream &f) const
    {
        f << "***** Evt1jDur *****\n";
        f << "Date=" << getDate() << " sujet=" << getDescription() << "\n";
        f << "Debut=" << debut << " Duree=" << duree << "\n";
    }

    /* ===== Rdv ===== */
    Rdv::Rdv(const Date &d,
             const std::string &s,
             const Horaire &h,
             const Duree &du,
             const std::string &pers,
             const std::string &l)
        : Evt1jDur(d, s, h, du), personnes(pers), lieu(l) {}

    Rdv::~Rdv() = default;

    const std::string &Rdv::getPersonnes() const { return personnes; }
    const std::string &Rdv::getLieu() const { return lieu; }

    void Rdv::afficher(std::ostream &f) const
    {
        f << "***** Rdv *****\n";
        f << "Date=" << getDate() << " sujet=" << getDescription() << "\n";
        f << "Debut=" << getHoraire() << " Duree=" << getDuree() << "\n";
        f << "Personnes=" << personnes << " Lieu=" << lieu << "\n";
    }

    /* ===== EvtPj ===== */
    EvtPj::EvtPj(const Date &d1, const Date &d2, const std::string &s)
        : Evt(s), debut(d1), fin(d2)
    {
        // 可选：保证区间合法
        if (fin < debut)
        {
            // 这里简单交换，避免异常依赖
            Date tmp = debut;
            debut = fin;
            fin = tmp;
        }
    }

    EvtPj::~EvtPj() = default;

    const Date &EvtPj::getDebut() const { return debut; }
    const Date &EvtPj::getFin() const { return fin; }

    void EvtPj::afficher(std::ostream &f) const
    {
        f << "***** EvtPj *****\n";
        f << "Debut=" << debut << " Fin=" << fin
          << " sujet=" << getDescription() << "\n";
    }

} // namespace TIME