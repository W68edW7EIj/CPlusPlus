#include "set.h"
#include <cstdlib>
#include <ctime>

// 枚举输出运算符实现
std::ostream &operator<<(std::ostream &os, const Couleur &c)
{
    switch (c)
    {
    case Couleur::rouge:
        os << "rouge";
        break;
    case Couleur::violet:
        os << "violet";
        break;
    case Couleur::vert:
        os << "vert";
        break;
    }
    return os;
}

std::ostream &operator<<(std::ostream &os, const Nombre &n)
{
    os << static_cast<int>(n);
    return os;
}

std::ostream &operator<<(std::ostream &os, const Forme &f)
{
    switch (f)
    {
    case Forme::ovale:
        os << "ovale";
        break;
    case Forme::vague:
        os << "vague";
        break;
    case Forme::losange:
        os << "losange";
        break;
    }
    return os;
}

std::ostream &operator<<(std::ostream &os, const Remplissage &r)
{
    switch (r)
    {
    case Remplissage::plein:
        os << "plein";
        break;
    case Remplissage::vide:
        os << "vide";
        break;
    case Remplissage::hachure:
        os << "hachure";
        break;
    }
    return os;
}

// 辅助打印函数
void printCouleurs()
{
    std::cout << "Couleurs: ";
    for (int i = 0; i < 3; i++)
    {
        std::cout << static_cast<Couleur>(i) << " ";
    }
    std::cout << std::endl;
}

void printNombres()
{
    std::cout << "Nombres: ";
    std::cout << Nombre::un << " " << Nombre::deux << " " << Nombre::trois << std::endl;
}

void printFormes()
{
    std::cout << "Formes: ";
    for (int i = 0; i < 3; i++)
    {
        std::cout << static_cast<Forme>(i) << " ";
    }
    std::cout << std::endl;
}

void printRemplissages()
{
    std::cout << "Remplissages: ";
    for (int i = 0; i < 3; i++)
    {
        std::cout << static_cast<Remplissage>(i) << " ";
    }
    std::cout << std::endl;
}

// ========== Carte类实现 ==========
Carte::Carte(Couleur c, Nombre n, Forme f, Remplissage r)
    : couleur(c), nombre(n), forme(f), remplissage(r)
{
}

std::ostream &operator<<(std::ostream &os, const Carte &carte)
{
    os << "[" << carte.couleur << ", " << carte.nombre << ", "
       << carte.forme << ", " << carte.remplissage << "]";
    return os;
}

// ========== Jeu类实现 ==========
Jeu::Jeu()
{
    // 创建所有81张不同的卡牌
    // 3种颜色 × 3种数量 × 3种形状 × 3种填充 = 81张
    size_t index = 0;

    for (int c = 0; c < 3; c++)
    {
        for (int n = 0; n < 3; n++)
        {
            for (int f = 0; f < 3; f++)
            {
                for (int r = 0; r < 3; r++)
                {
                    cartes[index++] = new Carte(
                        static_cast<Couleur>(c),
                        static_cast<Nombre>(n + 1), // 1, 2, 3
                        static_cast<Forme>(f),
                        static_cast<Remplissage>(r));
                }
            }
        }
    }
}

Jeu::~Jeu()
{
    // 释放所有动态分配的卡牌
    for (size_t i = 0; i < 81; i++)
    {
        delete cartes[i];
    }
}

const Carte &Jeu::getCarte(size_t i) const
{
    if (i >= 81)
    {
        throw SetException("Index de carte invalide");
    }
    return *cartes[i];
}

// ========== Pioche类实现 ==========
Pioche::Pioche(const Jeu &j)
{
    nbMax = j.getNbCartes();
    nb = nbMax;
    cartes = new const Carte *[nbMax];

    // 复制所有卡牌指针
    for (size_t i = 0; i < nbMax; i++)
    {
        cartes[i] = &j.getCarte(i);
    }

    // 初始化随机数生成器
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

Pioche::~Pioche()
{
    delete[] cartes;
}

const Carte *Pioche::piocher()
{
    if (estVide())
    {
        throw SetException("La pioche est vide");
    }

    // 随机选择一张牌
    size_t index = std::rand() % nb;
    const Carte *carte = cartes[index];

    // 将最后一张牌移到被抽走的位置
    cartes[index] = cartes[nb - 1];
    nb--;

    return carte;
}

// ========== Plateau类实现 ==========
Plateau::Plateau() : nb(0), nbMax(12)
{
    cartes = new const Carte *[nbMax];
}

Plateau::~Plateau()
{
    delete[] cartes;
}

void Plateau::agrandir()
{
    nbMax = nbMax * 2;
    const Carte **newCartes = new const Carte *[nbMax];

    for (size_t i = 0; i < nb; i++)
    {
        newCartes[i] = cartes[i];
    }

    delete[] cartes;
    cartes = newCartes;
}

void Plateau::ajouter(const Carte *c)
{
    if (nb >= nbMax)
    {
        agrandir();
    }
    cartes[nb++] = c;
}

void Plateau::retirer(const Carte *c)
{
    for (size_t i = 0; i < nb; i++)
    {
        if (cartes[i] == c)
        {
            // 将最后一张牌移到被移除的位置
            cartes[i] = cartes[nb - 1];
            nb--;
            return;
        }
    }
    throw SetException("Carte non trouvée sur le plateau");
}

void Plateau::print(std::ostream &os) const
{
    os << "Plateau (" << nb << " cartes):" << std::endl;
    for (size_t i = 0; i < nb; i++)
    {
        os << "  " << i << ": " << *cartes[i] << std::endl;
    }
}

const Carte *Plateau::getCarte(size_t i) const
{
    if (i >= nb)
    {
        throw SetException("Index de carte invalide sur le plateau");
    }
    return cartes[i];
}

// ========== Combinaison类实现 ==========
Combinaison::Combinaison(const Carte *carte1, const Carte *carte2, const Carte *carte3)
    : c1(carte1), c2(carte2), c3(carte3)
{
    if (!carte1 || !carte2 || !carte3)
    {
        throw SetException("Pointeurs de carte invalides");
    }
}

bool Combinaison::estUnSET() const
{
    // 检查每个特征：要么3个相同，要么3个不同

    // 检查颜色
    bool couleursSame = (c1->getCouleur() == c2->getCouleur() &&
                         c2->getCouleur() == c3->getCouleur());
    bool couleursDiff = (c1->getCouleur() != c2->getCouleur() &&
                         c2->getCouleur() != c3->getCouleur() &&
                         c1->getCouleur() != c3->getCouleur());

    if (!couleursSame && !couleursDiff)
        return false;

    // 检查数量
    bool nombresSame = (c1->getNombre() == c2->getNombre() &&
                        c2->getNombre() == c3->getNombre());
    bool nombresDiff = (c1->getNombre() != c2->getNombre() &&
                        c2->getNombre() != c3->getNombre() &&
                        c1->getNombre() != c3->getNombre());

    if (!nombresSame && !nombresDiff)
        return false;

    // 检查形状
    bool formesSame = (c1->getForme() == c2->getForme() &&
                       c2->getForme() == c3->getForme());
    bool formesDiff = (c1->getForme() != c2->getForme() &&
                       c2->getForme() != c3->getForme() &&
                       c1->getForme() != c3->getForme());

    if (!formesSame && !formesDiff)
        return false;

    // 检查填充
    bool remplissagesSame = (c1->getRemplissage() == c2->getRemplissage() &&
                             c2->getRemplissage() == c3->getRemplissage());
    bool remplissagesDiff = (c1->getRemplissage() != c2->getRemplissage() &&
                             c2->getRemplissage() != c3->getRemplissage() &&
                             c1->getRemplissage() != c3->getRemplissage());

    if (!remplissagesSame && !remplissagesDiff)
        return false;

    return true;
}

std::ostream &operator<<(std::ostream &os, const Combinaison &comb)
{
    os << "Combinaison:" << std::endl;
    os << "  1: " << *comb.c1 << std::endl;
    os << "  2: " << *comb.c2 << std::endl;
    os << "  3: " << *comb.c3 << std::endl;
    os << "  Est un SET: " << (comb.estUnSET() ? "OUI" : "NON") << std::endl;
    return os;
}

// ========== Controleur类实现 ==========
Controleur::Controleur()
{
    pioche = new Pioche(jeu);
}

Controleur::~Controleur()
{
    delete pioche;
}

void Controleur::distribuer()
{
    if (pioche->estVide())
    {
        return;
    }

    if (plateau.getNbCartes() < 12)
    {
        // 补到12张
        while (plateau.getNbCartes() < 12 && !pioche->estVide())
        {
            plateau.ajouter(pioche->piocher());
        }
    }
    else
    {
        // 只加1张
        plateau.ajouter(pioche->piocher());
    }
}
