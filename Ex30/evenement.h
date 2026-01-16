#ifndef EVENEMENT_H
#define EVENEMENT_H

#include <iostream>
#include <string>
#include "timing.h"

namespace TIME
{

    /* =======================
     * Classe abstraite Evt
     * ======================= */
    class Evt
    {
    private:
        std::string sujet; // Ex30：把 sujet 上移到 Evt

    public:
        explicit Evt(const std::string &s);
        virtual ~Evt(); // 多态删除必须 virtual

        const std::string &getDescription() const;

        // Ex30：纯虚函数 → Evt 不可实例化
        virtual void afficher(std::ostream &f = std::cout) const = 0;
    };

    /* operator<< 用于“任意事件”输出（靠 afficher 的多态） */
    std::ostream &operator<<(std::ostream &os, const Evt &e);

    /* =======================
     * Evt1j : événement d'un jour
     * ======================= */
    class Evt1j : public Evt
    {
    private:
        Date date;

    public:
        Evt1j(const Date &d, const std::string &s);
        ~Evt1j() override;

        const Date &getDate() const;

        void afficher(std::ostream &f = std::cout) const override;
    };

    /* =======================
     * Evt1jDur : événement d'un jour avec horaire et durée
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

        ~Evt1jDur() override;

        const Horaire &getHoraire() const;
        const Duree &getDuree() const;

        void afficher(std::ostream &f = std::cout) const override;
    };

    /* =======================
     * Rdv : rendez-vous (Evt1jDur + lieu + personnes)
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

        ~Rdv() override;

        const std::string &getPersonnes() const;
        const std::string &getLieu() const;

        void afficher(std::ostream &f = std::cout) const override;
    };

    /* =======================
     * EvtPj : événement de plusieurs jours (nouveau)
     * ======================= */
    class EvtPj : public Evt
    {
    private:
        Date debut;
        Date fin;

    public:
        EvtPj(const Date &d1, const Date &d2, const std::string &s);
        ~EvtPj() override;

        const Date &getDebut() const;
        const Date &getFin() const;

        void afficher(std::ostream &f = std::cout) const override;
    };

} // namespace TIME

#endif