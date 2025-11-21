#include "set.h"
using namespace Set;

class A{
	int x;
};

void f(Plateau& dest, const Plateau& source) {
	dest = source;
}

int main() {
	try {

		printCouleurs();
		printNombres();
		printFormes();
		printRemplissages();

		Carte c1(Couleur::rouge, Nombre::deux, 
			     Forme::vague, Remplissage::vide);

		Carte c2 = c1; // construction d'une carte c1 par recopie
					   // de la carte c2
		c2 = c1; // affectation

		Carte c3(Couleur::rouge, Nombre::un,
			Forme::vague, Remplissage::plein);

		//Carte tab[3]; 
		/* erreur : il faut des initialisateurs
		   car il n'y a pas de constructeur sans argument */
		Carte tab[3] = { c1, c2, c3 };  // ok
			/* les cartes du tableau sont initialisés à partir
		de c1, c2, c3 en utilisant le constructeur par recopie
		de Carte */

		Plateau p1;
		p1.ajouter(c1);

		Plateau p2;
		p2.ajouter(c2);

		p1 = p2;
		f(p1, p1);

		Carte* tab2[3];

		Jeu& j = Jeu::getInstance();
		
		for (size_t i = 0; i < j.getNbCartes(); i++)
			cout << j.getCarte(i) << "\n";

		Jeu::Iterator it = j.first(); // ask to Jeu an iterator 
			// over the first Carte inside Jeu
		while (!it.isDone()) // we loop until the iterator
							// is sayinf it's not finished
		{
			cout << it.currentItem(); // access to the current Carte
			it.next(); // go the next Carte

		}

		for (Jeu::iterator it = j.begin(); it != j.end(); ++it)
			cout << *it << "\n";

		for (const Carte& c : j) cout << c << "\n";

		for (auto it = j.begin(); it != j.end(); ++it)
			cout << *it << "\n";

		for (auto& c : j) cout << c << "\n";



	}
	catch (SetException& e) {
		std::cout << e.getInfo() << "\n";
	}
	
	system("pause");
	return 0;
}