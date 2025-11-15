#ifndef SET_H
#define SET_H

#include <iostream>
#include <string>
#include <stdexcept>

// 异常类
class SetException : public std::runtime_error
{
public:
    explicit SetException(const std::string &message) : std::runtime_error(message) {}
};

// 枚举类定义
enum class Couleur
{
    rouge,
    violet,
    vert
};
enum class Nombre
{
    un = 1,
    deux = 2,
    trois = 3
};
enum class Forme
{
    ovale,
    vague,
    losange
};
enum class Remplissage
{
    plein,
    vide,
    hachure
};

// 辅助函数声明
std::ostream &operator<<(std::ostream &os, const Couleur &c);
std::ostream &operator<<(std::ostream &os, const Nombre &n);
std::ostream &operator<<(std::ostream &os, const Forme &f);
std::ostream &operator<<(std::ostream &os, const Remplissage &r);

void printCouleurs();
void printNombres();
void printFormes();
void printRemplissages();

// 问题1: Carte类
class Carte
{
private:
    Couleur couleur;
    Nombre nombre;
    Forme forme;
    Remplissage remplissage;

public:
    // 构造函数
    Carte(Couleur c, Nombre n, Forme f, Remplissage r);

    // Getter方法
    Couleur getCouleur() const { return couleur; }
    Nombre getNombre() const { return nombre; }
    Forme getForme() const { return forme; }
    Remplissage getRemplissage() const { return remplissage; }

    // 输出运算符
    friend std::ostream &operator<<(std::ostream &os, const Carte &carte);

    // 默认拷贝构造和赋值运算符可用（没有动态内存分配）
};

// 问题5: Jeu类 (组合关系 - Jeu拥有所有Carte)
class Jeu
{
private:
    const Carte *cartes[81];

    // 禁止拷贝和赋值
    Jeu(const Jeu &) = delete;
    Jeu &operator=(const Jeu &) = delete;

public:
    // 构造函数 - 创建所有81张不同的卡牌
    Jeu();

    // 析构函数 - 释放所有动态分配的卡牌
    ~Jeu();

    // 方法
    size_t getNbCartes() const { return 81; }
    const Carte &getCarte(size_t i) const;
};

// 问题7: Pioche类 (聚合关系 - Pioche不拥有Carte，只是引用)
class Pioche
{
private:
    const Carte **cartes;
    size_t nb;
    size_t nbMax;

    // 禁止拷贝和赋值
    Pioche(const Pioche &) = delete;
    Pioche &operator=(const Pioche &) = delete;

public:
    // explicit防止隐式转换
    explicit Pioche(const Jeu &j);

    // 析构函数
    ~Pioche();

    // 方法
    size_t getNbCartes() const { return nb; }
    bool estVide() const { return nb == 0; }
    const Carte *piocher();
};

// 问题9: Plateau类 (聚合关系 - Plateau不拥有Carte)
class Plateau
{
private:
    const Carte **cartes;
    size_t nb;
    size_t nbMax;

    // 禁止拷贝和赋值
    Plateau(const Plateau &) = delete;
    Plateau &operator=(const Plateau &) = delete;

    // 扩容方法
    void agrandir();

public:
    // 构造函数
    Plateau();

    // 析构函数
    ~Plateau();

    // 方法
    void ajouter(const Carte *c);
    void retirer(const Carte *c);
    void print(std::ostream &os = std::cout) const;
    size_t getNbCartes() const { return nb; }
    const Carte *getCarte(size_t i) const;
};

// 问题11: Combinaison类 (聚合关系 - 只保存指针)
class Combinaison
{
private:
    const Carte *c1;
    const Carte *c2;
    const Carte *c3;

public:
    // 构造函数
    Combinaison(const Carte *carte1, const Carte *carte2, const Carte *carte3);

    // 默认拷贝构造和赋值可用（只有指针成员）

    // 方法
    bool estUnSET() const;

    // 输出
    friend std::ostream &operator<<(std::ostream &os, const Combinaison &comb);
};

// 问题13: Controleur类 (组合关系)
class Controleur
{
private:
    Jeu jeu;
    Plateau plateau;
    Pioche *pioche;

    // 禁止拷贝和赋值
    Controleur(const Controleur &) = delete;
    Controleur &operator=(const Controleur &) = delete;

public:
    // 构造函数
    Controleur();

    // 析构函数
    ~Controleur();

    // 方法
    void distribuer();
    const Plateau &getPlateau() const { return plateau; }
    Plateau &getPlateau() { return plateau; }
    const Pioche &getPioche() const { return *pioche; }
};

#endif // SET_H
