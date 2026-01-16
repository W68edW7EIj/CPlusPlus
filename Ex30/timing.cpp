#include "timing.h"

namespace TIME
{

    /* Date */
    Date::Date(int j, int m, int a) : jour(j), mois(m), annee(a) {}

    int Date::getJour() const { return jour; }
    int Date::getMois() const { return mois; }
    int Date::getAnnee() const { return annee; }

    std::ostream &operator<<(std::ostream &os, const Date &d)
    {
        os << d.jour << "/" << d.mois << "/" << d.annee;
        return os;
    }

    bool Date::operator<(const Date &other) const
    {
        if (annee != other.annee)
            return annee < other.annee;
        if (mois != other.mois)
            return mois < other.mois;
        return jour < other.jour;
    }

    bool Date::operator==(const Date &other) const
    {
        return jour == other.jour && mois == other.mois && annee == other.annee;
    }

    /* Horaire */
    Horaire::Horaire(int h, int m) : heure(h), minute(m) {}

    int Horaire::getHeure() const { return heure; }
    int Horaire::getMinute() const { return minute; }

    std::ostream &operator<<(std::ostream &os, const Horaire &h)
    {
        os << h.heure << "h";
        if (h.minute < 10)
            os << "0";
        os << h.minute;
        return os;
    }

    /* Duree */
    Duree::Duree(int m) : minutes(m) {}

    int Duree::getMinutes() const { return minutes; }

    std::ostream &operator<<(std::ostream &os, const Duree &d)
    {
        os << d.minutes << " min";
        return os;
    }

} // namespace TIME