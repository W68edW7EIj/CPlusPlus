#include <iostream>
#include <map>
#include <set>
#include <string>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

// Forward declaration pour les types
template<class V> class GraphG;

template<class Vertex>
class GraphG {
private:
    // Structure de données : map qui associe à chaque sommet l'ensemble de ses successeurs
    map<Vertex, set<Vertex>> adj;
    string name;
    
public:
    // Constructeur
    GraphG(const string& n) : name(n) {}
    
    // Accesseurs
    const string& getName() const { return name; }
    
    size_t getNbVertices() const { return adj.size(); }
    
    size_t getNbEdges() const {
        size_t count = 0;
        for (const auto& pair : adj) {
            count += pair.second.size();
        }
        return count;
    }
    
    // Ajoute un sommet (s'il n'existe pas déjà)
    void addVertex(const Vertex& i) {
        // Si le sommet n'existe pas, on crée une entrée avec un ensemble vide de successeurs
        if (adj.find(i) == adj.end()) {
            adj[i] = set<Vertex>();
        }
    }
    
    // Ajoute un arc i -> j
    void addEdge(const Vertex& i, const Vertex& j) {
        // Assure que les sommets existent
        addVertex(i);
        addVertex(j);
        
        // Ajoute j à l'ensemble des successeurs de i
        adj[i].insert(j);
    }
    
    // Supprime un arc i -> j
    void removeEdge(const Vertex& i, const Vertex& j) {
        // Vérifie si le sommet i existe
        auto it = adj.find(i);
        if (it != adj.end()) {
            // Supprime j de l'ensemble des successeurs de i
            it->second.erase(j);
        }
        // Note: on ne supprime pas les sommets même s'ils n'ont plus d'arcs
    }
    
    // Supprime un sommet et tous les arcs liés
    void removeVertex(const Vertex& i) {
        // Supprime le sommet de la map
        adj.erase(i);
        
        // Supprime le sommet de tous les ensembles de successeurs
        for (auto& pair : adj) {
            pair.second.erase(i);
        }
    }
    
    // Affichage du graphe
    void print(ostream& f) const {
        f << "graph " << name << " (" << getNbVertices() 
          << " vertices and " << getNbEdges() << " edges)" << endl;
        
        for (const auto& pair : adj) {
            f << pair.first << ":";
            for (const auto& successor : pair.second) {
                f << " " << successor;
            }
            f << endl;
        }
    }
    
    // Méthodes pour accéder aux données (utiles pour les tests)
    bool hasVertex(const Vertex& v) const {
        return adj.find(v) != adj.end();
    }
    
    bool hasEdge(const Vertex& from, const Vertex& to) const {
        auto it = adj.find(from);
        if (it != adj.end()) {
            return it->second.find(to) != it->second.end();
        }
        return false;
    }
    
    const set<Vertex>& getSuccessors(const Vertex& v) const {
        static const set<Vertex> emptySet;
        auto it = adj.find(v);
        if (it != adj.end()) {
            return it->second;
        }
        return emptySet;
    }
    
    // Pour Question 2 (à compléter)
    class vertex_iterator;
    class successor_iterator;
    
    vertex_iterator begin_vertex() const;
    vertex_iterator end_vertex() const;
    
    successor_iterator begin_successor(const Vertex& v) const;
    successor_iterator end_successor(const Vertex& v) const;
};

// Opérateur de sortie (version basique pour Question 1)
template<class V>
ostream& operator<<(ostream& f, const GraphG<V>& G) {
    G.print(f);
    return f;
}

// Fonction principale de test
int main() {
    cout << "=== Test de la classe GraphG (Question 1) ===" << endl << endl;
    
    // Test 1: Construction et méthodes de base
    cout << "Test 1: Construction et ajout de sommets" << endl;
    GraphG<char> G1("G1");
    cout << "Graphe G1 cree: " << G1.getName() << endl;
    cout << "Nombre de sommets: " << G1.getNbVertices() << " (attendu: 0)" << endl;
    cout << "Nombre d'arcs: " << G1.getNbEdges() << " (attendu: 0)" << endl << endl;
    
    G1.addVertex('a');
    G1.addVertex('b');
    G1.addVertex('c');
    cout << "Apres ajout de 3 sommets:" << endl;
    cout << "Nombre de sommets: " << G1.getNbVertices() << " (attendu: 3)" << endl;
    cout << "a existe? " << (G1.hasVertex('a') ? "oui" : "non") << endl;
    cout << "d existe? " << (G1.hasVertex('d') ? "oui" : "non") << " (attendu: non)" << endl << endl;
    
    // Test 2: Ajout d'arcs
    cout << "Test 2: Ajout d'arcs" << endl;
    G1.addEdge('a', 'b');
    G1.addEdge('a', 'c');
    G1.addEdge('b', 'c');
    cout << "Apres ajout de 3 arcs:" << endl;
    cout << "Nombre d'arcs: " << G1.getNbEdges() << " (attendu: 3)" << endl;
    cout << "Arc a->b existe? " << (G1.hasEdge('a', 'b') ? "oui" : "non") << endl;
    cout << "Arc b->a existe? " << (G1.hasEdge('b', 'a') ? "oui" : "non") << " (attendu: non)" << endl << endl;
    
    // Test 3: addEdge crée automatiquement les sommets
    cout << "Test 3: addEdge crée automatiquement les sommets manquants" << endl;
    G1.addEdge('c', 'd'); // 'd' n'existe pas encore
    cout << "Apres addEdge('c', 'd'):" << endl;
    cout << "Nombre de sommets: " << G1.getNbVertices() << " (attendu: 4)" << endl;
    cout << "d existe? " << (G1.hasVertex('d') ? "oui" : "non") << endl;
    cout << "Arc c->d existe? " << (G1.hasEdge('c', 'd') ? "oui" : "non") << endl << endl;
    
    // Test 4: Suppression d'arcs
    cout << "Test 4: Suppression d'arcs" << endl;
    G1.removeEdge('a', 'b');
    cout << "Apres removeEdge('a', 'b'):" << endl;
    cout << "Arc a->b existe? " << (G1.hasEdge('a', 'b') ? "oui" : "non") << " (attendu: non)" << endl;
    cout << "Nombre d'arcs: " << G1.getNbEdges() << " (attendu: 3)" << endl;
    cout << "a existe toujours? " << (G1.hasVertex('a') ? "oui" : "non") << " (attendu: oui)" << endl << endl;
    
    // Test 5: Suppression de sommets
    cout << "Test 5: Suppression de sommets" << endl;
    cout << "Avant suppression de 'b':" << endl;
    cout << "Successeurs de 'a': ";
    for (char s : G1.getSuccessors('a')) cout << s << " ";
    cout << endl;
    
    G1.removeVertex('b');
    cout << "Apres removeVertex('b'):" << endl;
    cout << "Nombre de sommets: " << G1.getNbVertices() << " (attendu: 3)" << endl;
    cout << "b existe? " << (G1.hasVertex('b') ? "oui" : "non") << " (attendu: non)" << endl;
    cout << "Arc b->c existe? " << (G1.hasEdge('b', 'c') ? "oui" : "non") << " (attendu: non)" << endl << endl;
    
    // Test 6: Affichage
    cout << "Test 6: Affichage du graphe" << endl;
    cout << G1 << endl;
    
    // Test 7: Exemple de l'énoncé
    cout << "Test 7: Exemple de l'énoncé" << endl;
    try {
        GraphG<char> G2("G2");
        G2.addVertex('a'); 
        G2.addVertex('b'); 
        G2.addEdge('a','c');
        G2.addEdge('a','d'); 
        G2.addEdge('d','e'); 
        G2.addEdge('e','b');
        cout << G2;
        
        cout << "Nombre de sommets de G2: " << G2.getNbVertices() 
             << " (attendu: 5)" << endl;
        cout << "Nombre d'arcs de G2: " << G2.getNbEdges() 
             << " (attendu: 4)" << endl << endl;
    } catch(exception& e) { 
        cout << "Erreur: " << e.what() << "\n"; 
    }
    
    // Test 8: Graphe avec strings
    cout << "Test 8: Graphe avec des strings" << endl;
    GraphG<string> G3("Pref");
    G3.addEdge("LO21","IA01"); 
    G3.addEdge("IA02","IA01"); 
    G3.addEdge("IA01","NF17");
    G3.addEdge("IA02","NF16"); 
    G3.addEdge("NF93","NF16");
    cout << G3;
    
    cout << "Test des arcs:" << endl;
    cout << "LO21 -> IA01? " << (G3.hasEdge("LO21", "IA01") ? "oui" : "non") << endl;
    cout << "IA01 -> LO21? " << (G3.hasEdge("IA01", "LO21") ? "oui" : "non") << " (attendu: non)" << endl;
    
    return 0;
}