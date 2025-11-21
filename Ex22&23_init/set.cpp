#include "set.h"
#include<cstdlib>

namespace Set {
	
	std::initializer_list<Couleur> Couleurs = { Couleur::rouge, Couleur::mauve, Couleur::vert };
	std::initializer_list<Nombre> Nombres = { Nombre::un, Nombre::deux, Nombre::trois };
	std::initializer_list<Forme> Formes = { Forme::ovale, Forme::vague, Forme::losange };
	std::initializer_list<Remplissage> Remplissages = { Remplissage::plein, Remplissage::vide, Remplissage::hachure };

	string toString(Couleur c) {
		switch (c) { 
		case Couleur::rouge: return "R";
		case Couleur::mauve: return "M";
		case Couleur::vert: return "V";
		default: throw SetException("Couleur inconnue");
		}
	}

	string toString(Nombre v) {
		switch (v) {
		case Nombre::un: return "1";
		case Nombre::deux: return "2";
		case Nombre::trois: return "3";
		default: throw SetException("Nombre inconnue");
		}
	}

	string toString(Forme f) {
		switch (f) {
		case Forme::ovale: return "O";
		case Forme::vague: return "~";
		case Forme::losange: return "\004";
		default: throw SetException("Forme inconnue");
		}
	}

	string toString(Remplissage r) {
		switch (r) {
		case Remplissage::plein: return "P";
		case Remplissage::vide: return "_";
		case Remplissage::hachure: return "H";
		default: throw SetException("Remplissage inconnu");
		}
	}

	std::ostream& operator<<(std::ostream& f, Couleur c) { f << toString(c); return f; }
	std::ostream& operator<<(std::ostream& f, Nombre v) {	f << toString(v); return f; }
	std::ostream& operator<<(std::ostream& f, Forme x) { f << toString(x);  return f; }
	std::ostream& operator<<(std::ostream& f, Remplissage r) { f << toString(r); return f; }

	void printCouleurs(std::ostream& f) {
		for (auto c : Couleurs) f << c << " ";
		f << "\n";
	}

	void printNombres(std::ostream& f) {
		for (auto v : Nombres) f << v << " ";
		f << "\n";
	}

	void printFormes(std::ostream& f) {
		for (auto x : Formes) f << x << " ";
		f << "\n";
	}

	void printRemplissages(std::ostream& f) {
		for (auto r : Remplissages) f << r << " ";
		f << "\n";
	}

	ostream& operator<<(ostream& f, const Carte& c) {
		f << "[" << c.getCouleur() << c.getForme() << c.getNombre()
			<< c.getRemplissage() << "]";
		return f;
	}

	Jeu::Jeu() {
		size_t i = 0;
		for (auto c : Couleurs)
			for (auto n : Nombres)
				for (auto f : Formes)
					for (auto r : Remplissages)
						cartes[i++] = new Carte(c, n, f, r);
	}

	const Carte& Jeu::getCarte(size_t i) const {
		if (i >= 81) throw SetException("carte inexistante");
		return *cartes[i];
	}

	Jeu::~Jeu() {
		// on désalloue chacune des cartes car
		// l'objet Jeu est responsable de leur cycle de vie
		for (size_t i = 0; i < getNbCartes(); i++) 
			delete cartes[i];
	}

	Pioche::Pioche(const Jeu& j):cartes(new const Carte*[81]) {
		for (size_t i = 0; i < j.getNbCartes(); i++)
			cartes[i] = &j.getCarte(i);
	}

	const Carte& Pioche::piocher() { // tire une carte (la retire de la pioche)
		if (estVide()) throw SetException("pioche vide");
		size_t i = rand() % nb; /* permet d'obtenir un nb
			aléatoire entre 0 et nb-1 */
		const Carte* tmp = cartes[i];
		cartes[i] = cartes[--nb]; /* on remplace la carte i
			pat la dernière carte du tableau*/
		return *tmp;
	}

	void Plateau::ajouter(const Carte& c) { // ajoute la carte c
		if (nb == nbMax) { // il n'y a plus de place
			// il faut agrandir le tableau
			// création d'un nouveau tableau
			const Carte** newtab = 
				new const Carte * [(nbMax + 1)*2];
			// recopie des adresses de cartes dans newtab
			for (size_t i = 0; i < nb; i++) newtab[i] = cartes[i];
			// mise à jour des attributs
			nbMax = (nbMax + 1) * 2;
			auto old = cartes;
			cartes = newtab; // cartes est remplacé par newtab
			delete[] old; // destruction de l'ancien tableau
			//delete[] cartes;
			//cartes = newtab;
		}
		cartes[nb++] = &c;
	} 
	
	void Plateau::retirer(const Carte& c) { // retire la carte c
		size_t i = 0;
		while (i < nb && cartes[i] != &c) i++;
		if (i == nb) throw SetException("carte inexistante");
		cartes[i] = cartes[--nb]; /* on écrase la carte i
			avec la dernière carte tout en décrémentant*/
	}
	
	void Plateau::print(ostream& f) const{
		f << "== PLATEAU ==";
		for (size_t i = 0; i < nb; i++) {
			if (i % 4 == 0) f << "\n"; // 
			f << cartes[i];
		}
		f << "\n";
	}
	
	Plateau::Plateau(const Plateau& p):
		cartes(new const Carte*[p.nb]),nb(p.nb),nbMax(p.nb) {
		for (size_t i = 0; i < p.nb; i++)
			cartes[i] = p.cartes[i];
	}
	
	Plateau& Plateau::operator=(const Plateau& p){
		if (this != &p) { // on se protèe contre l'autoaffectation
			nb = 0; // on considère qu'il n'y a plus de carte
					// sur le plateau
			for (size_t i = 0; i < p.nb; i++)
				ajouter(*p.cartes[i]); // on ajoute chaque carte de p
			/* ajouter agrandira le tableau si besoin*/
		}
		return *this;
	}

}