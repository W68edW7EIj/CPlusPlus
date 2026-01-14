/*
timing 模块的存在是为了封装所有与“时间表示与操作”相关的概念，使事件类只关注业务语义而不关心时间细节
防止时间相关的管理分散、提高内聚
*/

#ifndef TIMING_H
#define TIMING_H

#include <iostream>

namespace TIME
{

    /* =======================
     * Classe Date
     * ======================= */
    class Date
    {
    private:
        int jour;
        int mois;
        int annee;

    public:
        Date(int j = 1, int m = 1, int a = 1970);

        int getJour() const;
        int getMois() const;
        int getAnnee() const;

        friend std::ostream &operator<<(std::ostream &os, const Date &d);
    };

    /* =======================
     * Classe Horaire
     * ======================= */
    class Horaire
    {
    private:
        int heure;
        int minute;

    public:
        Horaire(int h = 0, int m = 0);

        int getHeure() const;
        int getMinute() const;

        friend std::ostream &operator<<(std::ostream &os, const Horaire &h);
    };

    /* =======================
     * Classe Duree
     * ======================= */
    class Duree
    {
    private:
        int minutes; // durée en minutes

    public:
        explicit Duree(int m = 0);

        int getMinutes() const;

        friend std::ostream &operator<<(std::ostream &os, const Duree &d);
    };

} // namespace TIME

#endif