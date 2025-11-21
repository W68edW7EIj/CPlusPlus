#ifndef _SET_H
#define _SET_H

#include <iostream>
#include <string>
#include <initializer_list>
#include <array>
#include <cstdlib>
using namespace std;

namespace Set
{
	// classe pour g�rer les exceptions dans le set
	class SetException
	{
	public:
		SetException(const string &i) : info(i) {}
		string getInfo() const { return info; }

	private:
		string info;
	};

	// caract�ristiques
	enum class Couleur
	{
		rouge,
		mauve,
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

	// conversion d'une caract�ristique en string
	string toString(Couleur c);
	string toString(Nombre v);
	string toString(Forme f);
	string toString(Remplissage v);

	// �criture d'une caract�ristique sur un flux ostream
	ostream &operator<<(ostream &f, Couleur c);
	ostream &operator<<(ostream &f, Nombre v);
	ostream &operator<<(ostream &f, Forme x);
	ostream &operator<<(ostream &f, Remplissage r);

	// listes contenant les valeurs possibles pour chacune des caract�ristiques
	extern std::initializer_list<Couleur> Couleurs;
	extern std::initializer_list<Nombre> Nombres;
	extern std::initializer_list<Forme> Formes;
	extern std::initializer_list<Remplissage> Remplissages;

	// affichage des valeurs possibles pour chaque caract�ristiques
	void printCouleurs(std::ostream &f = cout);
	void printNombres(std::ostream &f = cout);
	void printFormes(std::ostream &f = cout);
	void printRemplissages(std::ostream &f = cout);

	class Carte
	{
		Couleur couleur;
		Nombre nombre;
		Forme forme;
		Remplissage remplissage;

	public:
		Carte(Couleur c, Nombre n, Forme f, Remplissage r) : couleur(c), nombre(n), forme(f), remplissage(r) {}
		Couleur getCouleur() const { return couleur; }
		Nombre getNombre() const { return nombre; }
		Forme getForme() const { return forme; }
		Remplissage getRemplissage() const { return remplissage; }

		// les op�rations g�n�r�es par d�faut conviennent:
		~Carte() = default;
		Carte(const Carte &) = default;
		Carte &operator=(const Carte &) = default;
	};
	ostream &operator<<(ostream &f, const Carte &c);

	class Jeu
	{
		const Carte *cartes[81]; // tableau de 81 pointeurs const
		// d�sactivation de la construction par recopie et l'affectation
		Jeu(const Jeu &) = delete;
		Jeu &operator=(const Jeu &) = delete;
		// transformation into a singleton
		Jeu();
		~Jeu();

	public:
		static Jeu &getInstance()
		{
			static Jeu instance;
			return instance;
		}
		const Carte &getCarte(size_t i) const;
		size_t getNbCartes() const { return 81; }

		class Iterator
		{
			/* I need some information to implement the different
			methods : these informations have to be initialized
			inside a constructor*/
			Jeu &instance; // r�f�rence sur l'instance jeu
			size_t i;	   // indice sur la carte courante
			// constructor inside the private part to give
			// the exclusivity of its use to the instance of Jeu
			Iterator(Jeu &j, size_t x) : instance(j), i(x) {}
			friend class Jeu; // to provide access to the constructor
		public:
			const Carte &currentItem() { return instance.getCarte(i); } // access to the current Carte
			bool isDone() const { return i == instance.getNbCartes(); } // finished or not ?
			void next() { i++; }										// go to the next Carte
		}; // a class declared inside Jeu in the public part
		Iterator first() { return Iterator(*this, 0); } // provide the first Iterator

		class const_iterator
		{				   // comme dans les classes standards
			Jeu &instance; // r�f�rence sur l'instance jeu
			size_t i;	   // indice sur la carte courante
			// constructor inside the private part to give
			// the exclusivity of its use to the instance of Jeu
			const_iterator(const Jeu &j, size_t x) : instance(j), i(x) {}
			friend class Jeu; // to provide access to the constructor
		public:
			const Carte &operator*() { return instance.getCarte(i); } // access to the current Carte
			bool operator!=(const_iterator other) const
			{
				return i != other.i;
			}
			void operator++() { i++; } // go to the next Carte
		}; // a class declared inside Jeu in the public part
		const_iterator begin() const { return const_iterator(*this, 0); }  // provide the first Iterator
		const_iterator end() const { return const_iterator(*this, 81); }   // provide the first Iterator
		const_iterator cbegin() const { return const_iterator(*this, 0); } // provide the first Iterator
		const_iterator cend() const { return const_iterator(*this, 81); }  // provide the first Iterator

		class IteratorForme
		{
			// to iterate over Cartes of specific given forme
			Forme forme;   // the form of the Cartes i want to see
			Jeu &instance; // r�f�rence sur l'instance jeu
			size_t i;	   // indice sur la carte courante
			// constructor inside the private part to give
			// the exclusivity of its use to the instance of Jeu
			IteratorForme(Jeu &j, size_t x, Forme f) : instance(j), i(x), forme(f) {}
			friend class Jeu; // to provide access to the constructor
		public:
			const Carte &currentItem() { return instance.getCarte(i); } // access to the current Carte
			bool isDone() const { return i == instance.getNbCartes(); } // finished or not ?
			void next()
			{		 // go to the next Carte with the good forme
				i++; // we increment at least once
				// but we must iterate until we reach the Carte
				// with the good forme
				while (!isDone() &&
					   instance.getCarte(i).getForme() != forme)
					i++;
			}
		}; // a class declared inside Jeu in the public part
		IteratorForme first(Forme f)
		{
			return IteratorForme(*this, 0, f);
		} // provide the first Iterator

		class IteratorBis
		{
			const Carte **current; // point to the current pointer
								   // of Carte inside the array of pointers which is
								   // in Jeu
			size_t nb;			   // number of Cartes it remains to see
			IteratorBis(const Carte **c, size_t n) : current(c), nb(n) {}
			friend Jeu;

		public:
			const Carte &currentItem() { return **current; } // access to the current Carte
			bool isDone() const { return nb == 0; }			 // finished or not ?
			void next()
			{
				current++;
				nb--;
			} // go to the next Carte
		}; // a class declared inside Jeu in the public part
		IteratorBis firstBis() { return IteratorBis(&cartes[0], 81); } // provide the first Iterator

	}; // end of class Jeu

	class Pioche
	{
		const Carte **cartes; /* pointe sur un tableau allou�
			dynamiquement de pointeurs const Carte* */
		size_t nb;			  // nombre de cartes restant dans la pioche
	public:
		Pioche(const Pioche &) = delete;
		Pioche &operator=(const Pioche &) = delete;
		// interdiction de la conversion implicite Jeu->Pioche
		explicit Pioche(const Jeu &j);
		const Carte &piocher(); // tire une carte (la retire de la pioche)
		size_t getNbCartes() const { return nb; }
		bool estVide() { return nb == 0; }
		~Pioche()
		{
			/* le tableau doit �tre d�sallou� car l'objet Pioche
			en est responsable */
			delete[] cartes;
		}
	};

	class Plateau
	{									// contient les cartes visibles
		const Carte **cartes = nullptr; // tableau de pointeurs allou� dynamiquement
		size_t nbMax = 0;				// taille r�elle du tableau allou�
		size_t nb = 0;					// nombre de cases du tableau d�j� utilis�
	public:
		~Plateau() { delete[] cartes; }
		Plateau() = default;

		void ajouter(const Carte &c); // ajoute la carte c
		void retirer(const Carte &c); // retire la carte c
		void print(ostream &f) const;
		Plateau(const Plateau &p);
		Plateau &operator=(const Plateau &p);
		class const_iterator
		{
			const Carte **current;
			size_t i;
			const_iterator(const Carte **c, size_t x) : current(c), i(x) {}
			friend class Plateau;

		public:
			const Carte &operator*() const { return **current; }
			void operator++() { i++; }
			bool operator!=(const_iterator other) const
			{
				return i != other.i;
			}
		};
		const_iterator begin() const { return const_iterator(cartes, 0); }
		const_iterator end() const { return const_iterator(cartes, nb); }
		const_iterator cbegin() const { return const_iterator(cartes, 0); }
		const_iterator cend() const { return const_iterator(cartes, nb); }
	};

}; // fin namespace Set

#endif
