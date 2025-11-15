#include "set.h"
#include <iostream>

int main()
{
    try
    {
        std::cout << "=== Test des enumerations ===" << std::endl;
        printCouleurs();
        printNombres();
        printFormes();
        printRemplissages();
        std::cout << std::endl;

        // Test Carte
        std::cout << "=== Test de la classe Carte ===" << std::endl;
        Carte c1(Couleur::rouge, Nombre::deux, Forme::ovale, Remplissage::plein);
        std::cout << "Carte 1: " << c1 << std::endl;

        Carte c2(Couleur::vert, Nombre::un, Forme::vague, Remplissage::vide);
        std::cout << "Carte 2: " << c2 << std::endl;
        std::cout << std::endl;

        // Test Jeu
        std::cout << "=== Test de la classe Jeu ===" << std::endl;
        Jeu jeu;
        std::cout << "Nombre de cartes dans le jeu: " << jeu.getNbCartes() << std::endl;
        std::cout << "Premiere carte: " << jeu.getCarte(0) << std::endl;
        std::cout << "Derniere carte: " << jeu.getCarte(80) << std::endl;
        std::cout << std::endl;

        // Test Pioche
        std::cout << "=== Test de la classe Pioche ===" << std::endl;
        Pioche pioche(jeu);
        std::cout << "Cartes dans la pioche: " << pioche.getNbCartes() << std::endl;
        std::cout << "La pioche est vide? " << (pioche.estVide() ? "OUI" : "NON") << std::endl;

        const Carte *carte1 = pioche.piocher();
        std::cout << "Carte piochee: " << *carte1 << std::endl;
        std::cout << "Cartes restantes: " << pioche.getNbCartes() << std::endl;
        std::cout << std::endl;

        // Test Plateau
        std::cout << "=== Test de la classe Plateau ===" << std::endl;
        Plateau plateau;
        plateau.ajouter(carte1);

        for (int i = 0; i < 5; i++)
        {
            plateau.ajouter(pioche.piocher());
        }

        plateau.print();
        std::cout << std::endl;

        // Test Combinaison
        std::cout << "=== Test de la classe Combinaison ===" << std::endl;

        // Créer un SET valide (toutes les propriétés différentes)
        const Carte *sc1 = new Carte(Couleur::rouge, Nombre::un, Forme::ovale, Remplissage::plein);
        const Carte *sc2 = new Carte(Couleur::vert, Nombre::deux, Forme::vague, Remplissage::vide);
        const Carte *sc3 = new Carte(Couleur::violet, Nombre::trois, Forme::losange, Remplissage::hachure);

        Combinaison comb1(sc1, sc2, sc3);
        std::cout << comb1 << std::endl;

        // Créer un SET invalide
        const Carte *sc4 = new Carte(Couleur::rouge, Nombre::un, Forme::ovale, Remplissage::plein);
        const Carte *sc5 = new Carte(Couleur::rouge, Nombre::deux, Forme::vague, Remplissage::vide);
        const Carte *sc6 = new Carte(Couleur::vert, Nombre::trois, Forme::losange, Remplissage::hachure);

        Combinaison comb2(sc4, sc5, sc6);
        std::cout << comb2 << std::endl;

        delete sc1;
        delete sc2;
        delete sc3;
        delete sc4;
        delete sc5;
        delete sc6;

        // Test Controleur
        std::cout << "=== Test de la classe Controleur ===" << std::endl;
        Controleur controleur;

        std::cout << "Distribution initiale (12 cartes):" << std::endl;
        controleur.distribuer();
        controleur.getPlateau().print();
        std::cout << std::endl;

        std::cout << "Distribution supplementaire (1 carte):" << std::endl;
        controleur.distribuer();
        controleur.getPlateau().print();
        std::cout << std::endl;

        std::cout << "Cartes restantes dans la pioche: " << controleur.getPioche().getNbCartes() << std::endl;

        // Test d'un vrai SET depuis le plateau
        std::cout << "\n=== Recherche d'un SET dans le plateau ===" << std::endl;
        bool setTrouve = false;
        const Plateau &p = controleur.getPlateau();

        for (size_t i = 0; i < p.getNbCartes() && !setTrouve; i++)
        {
            for (size_t j = i + 1; j < p.getNbCartes() && !setTrouve; j++)
            {
                for (size_t k = j + 1; k < p.getNbCartes() && !setTrouve; k++)
                {
                    Combinaison test(p.getCarte(i), p.getCarte(j), p.getCarte(k));
                    if (test.estUnSET())
                    {
                        std::cout << "SET trouve aux positions " << i << ", " << j << ", " << k << ":" << std::endl;
                        std::cout << test << std::endl;
                        setTrouve = true;
                    }
                }
            }
        }

        if (!setTrouve)
        {
            std::cout << "Aucun SET trouve dans le plateau actuel." << std::endl;
        }

        std::cout << "\n=== Tous les tests sont reussis! ===" << std::endl;
    }
    catch (const SetException &e)
    {
        std::cerr << "Erreur SET: " << e.what() << std::endl;
        return 1;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Erreur: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
