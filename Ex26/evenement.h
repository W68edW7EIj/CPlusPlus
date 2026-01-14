/*
Evt1j、Evt1jDur、Rdv 三个类构成一条清晰的继承层次结构（inheritance hierarchy），
使用 public 继承，并通过 方法重定义（polymorphism） 实现事件的特化。

        Evt1j
---------------------
- date : Date
- sujet : string
---------------------
+ afficher()

          ▲
          │
      Evt1jDur
---------------------
- debut : Horaire
- duree : Duree
---------------------
+ afficher()

          ▲
          │
          Rdv
---------------------
- personnes : string
- lieu : string
---------------------
+ afficher()
*/

#ifndef EVENEMENT_H
#define EVENEMENT_H

#include <iostream>
#include <string>
#include "timing.h"

namespace TIME
{

    /* =======================
     * Classe Evt1j
     * ======================= */
    class Evt1j
    {
    private:
        Date date;
        std::string sujet;

    public:
        Evt1j(const Date &d, const std::string &s);
        virtual ~Evt1j();

        const Date &getDate() const;
        const std::string &getDescription() const;

        virtual void afficher(std::ostream &f = std::cout) const;
    };

    /* =======================
     * Classe Evt1jDur
     * ======================= */
    class Evt1jDur : public Evt1j
    {
    private:
        Horaire debut;
        Duree duree;

    public:
        Evt1jDur(const Date &d,
                 const std::string &s,
                 const Horaire &h,
                 const Duree &du);

        virtual ~Evt1jDur();

        const Horaire &getHoraire() const;
        const Duree &getDuree() const;

        void afficher(std::ostream &f = std::cout) const override;
    };

    /* =======================
     * Classe Rdv
     * ======================= */
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

        virtual ~Rdv();

        const std::string &getPersonnes() const;
        const std::string &getLieu() const;

        void afficher(std::ostream &f = std::cout) const override;
    };

} // namespace TIME

#endif