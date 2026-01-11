#include <iostream>
#include <map>
#include <set>
#include <string>
#include <algorithm>
#include <functional>
using namespace std;

// ============================================
// CLASSE GraphG avec itérateurs (Question 2)
// ============================================
template<class Vertex>
class GraphG {
private:
    map<Vertex, set<Vertex>> adj;
    string name;
    
    // Helper pour gérer les sommets inexistants
    const set<Vertex>& getSuccessorSet(const Vertex& v) const {
        static const set<Vertex> emptySet;  // Set vide global
        auto it = adj.find(v);
        if (it != adj.end()) {
            return it->second;
        }
        return emptySet;  // Retourne une référence au set vide
    }
    
public:
    // ============================================
    // ITERATEUR sur les SOMMETS (vertex_iterator)
    // ============================================
    class vertex_iterator {
    private:
        typename map<Vertex, set<Vertex>>::const_iterator it;
        
    public:
        // Typedefs requis pour la compatibilité avec les algorithmes STL
        using iterator_category = std::forward_iterator_tag;
        using value_type = Vertex;
        using difference_type = std::ptrdiff_t;
        using pointer = const Vertex*;
        using reference = const Vertex&;
        
        vertex_iterator(typename map<Vertex, set<Vertex>>::const_iterator map_it = {}) 
            : it(map_it) {}
        
        const Vertex& operator*() const { return it->first; }
        const Vertex* operator->() const { return &(it->first); }
        
        vertex_iterator& operator++() { ++it; return *this; }
        vertex_iterator operator++(int) { vertex_iterator tmp = *this; ++it; return tmp; }
        
        bool operator==(const vertex_iterator& other) const { return it == other.it; }
        bool operator!=(const vertex_iterator& other) const { return it != other.it; }
    };
    
    // ============================================
    // ITERATEUR sur les SUCCESSEURS (successor_iterator)
    // ============================================
    class successor_iterator {
    private:
        typename set<Vertex>::const_iterator it;
        
    public:
        // Typedefs requis pour la compatibilité avec les algorithmes STL
        using iterator_category = std::forward_iterator_tag;
        using value_type = Vertex;
        using difference_type = std::ptrdiff_t;
        using pointer = const Vertex*;
        using reference = const Vertex&;
        
        successor_iterator(typename set<Vertex>::const_iterator set_it = {}) 
            : it(set_it) {}
        
        const Vertex& operator*() const { return *it; }
        const Vertex* operator->() const { return &(*it); }
        
        successor_iterator& operator++() { ++it; return *this; }
        successor_iterator operator++(int) { successor_iterator tmp = *this; ++it; return tmp; }
        
        bool operator==(const successor_iterator& other) const { return it == other.it; }
        bool operator!=(const successor_iterator& other) const { return it != other.it; }
    };
    
    // ============================================
    // CONSTRUCTEUR ET METHODES DE BASE
    // ============================================
    GraphG(const string& n) : name(n) {}
    
    const string& getName() const { return name; }
    size_t getNbVertices() const { return adj.size(); }
    
    size_t getNbEdges() const {
        size_t count = 0;
        for (const auto& pair : adj) {
            count += pair.second.size();
        }
        return count;
    }
    
    void addVertex(const Vertex& i) {
        if (adj.find(i) == adj.end()) {
            adj[i] = set<Vertex>();
        }
    }
    
    void addEdge(const Vertex& i, const Vertex& j) {
        addVertex(i);
        addVertex(j);
        adj[i].insert(j);
    }
    
    void removeEdge(const Vertex& i, const Vertex& j) {
        auto it = adj.find(i);
        if (it != adj.end()) {
            it->second.erase(j);
        }
    }
    
    void removeVertex(const Vertex& i) {
        adj.erase(i);
        for (auto& pair : adj) {
            pair.second.erase(i);
        }
    }
    
    // ============================================
    // METHODES POUR LES ITERATEURS (CORRIGÉES)
    // ============================================
    
    vertex_iterator begin_vertex() const {
        return vertex_iterator(adj.begin());
    }
    
    vertex_iterator end_vertex() const {
        return vertex_iterator(adj.end());
    }
    
    successor_iterator begin_successor(const Vertex& v) const {
        // Utilise getSuccessorSet qui retourne emptySet si le sommet n'existe pas
        const set<Vertex>& successors = getSuccessorSet(v);
        return successor_iterator(successors.begin());
    }
    
    successor_iterator end_successor(const Vertex& v) const {
        // Utilise getSuccessorSet qui retourne emptySet si le sommet n'existe pas
        const set<Vertex>& successors = getSuccessorSet(v);
        return successor_iterator(successors.end());
    }
    
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
};

template<class V>
ostream& operator<<(ostream& f, const GraphG<V>& G) {
    G.print(f);
    return f;
}

// ============================================
// PROGRAMME PRINCIPAL DE TEST (CORRIGÉ)
// ============================================
int main() {
    cout << "=== TEST des itérateurs (Question 2 - CORRIGÉ) ===" << endl << endl;
    
    try {
        cout << "1. TEST - Exemple de l'énoncé" << endl;
        GraphG<char> G2("G2");
        
        G2.addVertex('a'); 
        G2.addVertex('b'); 
        G2.addEdge('a', 'c');
        G2.addEdge('a', 'd'); 
        G2.addEdge('d', 'e'); 
        G2.addEdge('e', 'b');
        
        cout << G2 << endl;
        
        cout << "2. TEST - vertex_iterator" << endl;
        cout << "Sommets de G2 : ";
        for(GraphG<char>::vertex_iterator it = G2.begin_vertex();
            it != G2.end_vertex(); ++it) {
            cout << *it << " ";
        }
        cout << endl << endl;
        
        cout << "3. TEST - successor_iterator" << endl;
        cout << "Successeurs de 'a' : ";
        for(GraphG<char>::successor_iterator it = G2.begin_successor('a');
            it != G2.end_successor('a'); ++it) {
            cout << *it << " ";
        }
        cout << endl;
        
        cout << "Successeurs de 'b' : ";
        bool hasSuccessors = false;
        for(GraphG<char>::successor_iterator it = G2.begin_successor('b');
            it != G2.end_successor('b'); ++it) {
            cout << *it << " ";
            hasSuccessors = true;
        }
        if (!hasSuccessors) {
            cout << "(aucun)";
        }
        cout << endl << endl;
        
        cout << "4. TEST - Sommet inexistant (CORRIGÉ)" << endl;
        cout << "Test avec sommet 'z' qui n'existe pas..." << endl;
        
        // Test 1: Vérification que les itérateurs sont égaux
        GraphG<char>::successor_iterator begin_z = G2.begin_successor('z');
        GraphG<char>::successor_iterator end_z = G2.end_successor('z');
        
        cout << "begin_successor('z') == end_successor('z') ? ";
        cout << (begin_z == end_z ? "OUI (correct)" : "NON (problème)") << endl;
        
        // Test 2: Boucle ne devrait pas s'exécuter
        cout << "Parcours des successeurs de 'z' : ";
        int count = 0;
        for(GraphG<char>::successor_iterator it = G2.begin_successor('z');
            it != G2.end_successor('z'); ++it) {
            cout << *it << " ";
            count++;
        }
        
        if (count == 0) {
            cout << "(aucun - sommet inexistant)";
        }
        cout << endl << endl;
        
        // Test 3: Sommet ajouté puis supprimé
        cout << "5. TEST - Sommet ajouté puis supprimé" << endl;
        G2.addVertex('z');
        G2.addEdge('z', 'a');
        cout << "Après ajout de 'z' avec arc z->a :" << endl;
        cout << "Successeurs de 'z' : ";
        for(GraphG<char>::successor_iterator it = G2.begin_successor('z');
            it != G2.end_successor('z'); ++it) {
            cout << *it << " ";
        }
        cout << endl;
        
        G2.removeVertex('z');
        cout << "Après suppression de 'z' :" << endl;
        cout << "Successeurs de 'z' : ";
        count = 0;
        for(GraphG<char>::successor_iterator it = G2.begin_successor('z');
            it != G2.end_successor('z'); ++it) {
            cout << *it << " ";
            count++;
        }
        if (count == 0) {
            cout << "(aucun - sommet supprimé)";
        }
        cout << endl << endl;
        
        // Test avec strings
        cout << "6. TEST - Graphe avec strings" << endl;
        GraphG<string> G3("Pref");
        G3.addEdge("LO21","IA01"); 
        G3.addEdge("IA02","IA01"); 
        G3.addEdge("IA01","NF17");
        G3.addEdge("IA02","NF16"); 
        G3.addEdge("NF93","NF16");
        
        cout << G3 << endl;
        
        cout << "Sommets de G3 : ";
        for(GraphG<string>::vertex_iterator it = G3.begin_vertex();
            it != G3.end_vertex(); ++it) {
            cout << *it << " ";
        }
        cout << endl << endl;
        
        // Test des successeurs avec vérification
        cout << "Vérification des successeurs :" << endl;
        cout << "Successeurs de 'IA02' : ";
        for(auto it = G3.begin_successor("IA02"); it != G3.end_successor("IA02"); ++it) {
            cout << *it << " ";
        }
        cout << endl;
        
        cout << "Successeurs de 'MATHS' (inexistant) : ";
        count = 0;
        for(auto it = G3.begin_successor("MATHS"); it != G3.end_successor("MATHS"); ++it) {
            cout << *it << " ";
            count++;
        }
        if (count == 0) {
            cout << "(aucun)";
        }
        cout << endl;
        
    } catch(exception& e) { 
        cout << "ERREUR : " << e.what() << "\n"; 
        return 1;
    }
    
    cout << "\n=== TESTS RÉUSSIS ===" << endl;
    return 0;
}