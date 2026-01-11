#include <iostream>
#include <string>
#include <cassert>

// ==================== VECTOR ====================
template<typename T>
class Vector {
private:
    T* data;
    size_t capacity;
    size_t vecSize;

public:
    // Classe iterator imbriquée
    class iterator {
    private:
        T* ptr;
    
    public:
        using value_type = T;
        
        explicit iterator(T* p = nullptr) : ptr(p) {}
        
        T& operator*() const {
            return *ptr;
        }
        
        iterator& operator++() {
            ++ptr;
            return *this;
        }
        
        iterator operator++(int) {
            iterator temp = *this;
            ++ptr;
            return temp;
        }
        
        bool operator==(const iterator& other) const {
            return ptr == other.ptr;
        }
        
        bool operator!=(const iterator& other) const {
            return ptr != other.ptr;
        }
        
        // Ajout de l'opérateur + pour pouvoir faire begin() + n
        iterator operator+(int n) const {
            return iterator(ptr + n);
        }
        
        // Ajout de l'opérateur - pour la différence
        int operator-(const iterator& other) const {
            return ptr - other.ptr;
        }
        
        T* operator->() const {
            return ptr;
        }
    };
    
    Vector() : data(nullptr), capacity(0), vecSize(0) {}
    
    ~Vector() {
        delete[] data;
    }
    
    void push_back(const T& value) {
        if (vecSize >= capacity) {
            capacity = (capacity == 0) ? 1 : capacity * 2;
            T* newData = new T[capacity];
            for (size_t i = 0; i < vecSize; ++i) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
        }
        data[vecSize++] = value;
    }
    
    T& operator[](size_t index) {
        return data[index];
    }
    
    size_t size() const {
        return vecSize;
    }
    
    iterator begin() {
        return iterator(data);
    }
    
    iterator end() {
        return iterator(data + vecSize);
    }
};

// ==================== STACK ====================
template<typename T>
class Stack {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& val) : data(val), next(nullptr) {}
    };
    
    Node* topNode;
    size_t stackSize;

public:
    // Itérateur pour Stack
    class iterator {
    private:
        Node* current;
    
    public:
        using value_type = T;
        
        explicit iterator(Node* node = nullptr) : current(node) {}
        
        T& operator*() const {
            return current->data;
        }
        
        iterator& operator++() {
            if (current) {
                current = current->next;
            }
            return *this;
        }
        
        iterator operator++(int) {
            iterator temp = *this;
            if (current) {
                current = current->next;
            }
            return temp;
        }
        
        bool operator==(const iterator& other) const {
            return current == other.current;
        }
        
        bool operator!=(const iterator& other) const {
            return current != other.current;
        }
        
        T* operator->() const {
            return &(current->data);
        }
    };
    
    Stack() : topNode(nullptr), stackSize(0) {}
    
    ~Stack() {
        clear();
    }
    
    void push(const T& value) {
        Node* newNode = new Node(value);
        newNode->next = topNode;
        topNode = newNode;
        ++stackSize;
    }
    
    void pop() {
        if (topNode) {
            Node* temp = topNode;
            topNode = topNode->next;
            delete temp;
            --stackSize;
        }
    }
    
    T& top() {
        return topNode->data;
    }
    
    bool empty() const {
        return topNode == nullptr;
    }
    
    size_t size() const {
        return stackSize;
    }
    
    void clear() {
        while (!empty()) {
            pop();
        }
    }
    
    iterator begin() {
        return iterator(topNode);
    }
    
    iterator end() {
        return iterator(nullptr);
    }
};

// ==================== FONCTION minimum_element ====================
template<typename Iterator>
Iterator minimum_element(Iterator first, Iterator last) {
    // Vérifier que la plage n'est pas vide
    if (first == last) {
        return last;
    }
    
    // Initialiser l'itérateur du minimum au premier élément
    Iterator min_it = first;
    ++first;
    
    // Parcourir les éléments restants
    for (; first != last; ++first) {
        if (*first < *min_it) {
            min_it = first;
        }
    }
    
    return min_it;
}

// ==================== TESTS ====================

void testMinimumElementVectorInt() {
    std::cout << "\n=== Test minimum_element avec Vector<int> ===" << std::endl;
    
    Vector<int> vec;
    vec.push_back(42);
    vec.push_back(17);
    vec.push_back(89);
    vec.push_back(23);
    vec.push_back(56);
    vec.push_back(5);
    vec.push_back(72);
    
    std::cout << "Contenu du vector: ";
    for (int val : vec) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    // Test 1: Plage complète
    Vector<int>::iterator min_it = minimum_element(vec.begin(), vec.end());
    if (min_it != vec.end()) {
        std::cout << "Minimum sur plage complete: " << *min_it << std::endl;
        assert(*min_it == 5);
    }
    
    // Test 2: Sous-plage (éléments 2 à 5, indice 2 exclu)
    Vector<int>::iterator start = vec.begin();
    for (int i = 0; i < 2; ++i) ++start; // Avancer 2 fois
    Vector<int>::iterator stop = vec.begin();
    for (int i = 0; i < 5; ++i) ++stop;  // Avancer 5 fois
    min_it = minimum_element(start, stop);
    if (min_it != stop) {
        std::cout << "Minimum entre positions 2 et 5: " << *min_it << std::endl;
        assert(*min_it == 23);
    }
    
    // Test 3: Plage d'un seul élément
    Vector<int>::iterator single_start = vec.begin();
    for (int i = 0; i < 3; ++i) ++single_start;
    Vector<int>::iterator single_end = single_start;
    ++single_end;
    min_it = minimum_element(single_start, single_end);
    if (min_it != single_end) {
        std::cout << "Minimum sur un seul element (23): " << *min_it << std::endl;
        assert(*min_it == 23);
    }
    
    // Test 4: Plage vide
    Vector<int>::iterator empty_it = minimum_element(vec.end(), vec.end());
    std::cout << "Test plage vide: " << (empty_it == vec.end() ? "OK" : "ERREUR") << std::endl;
    assert(empty_it == vec.end());
}

void testMinimumElementVectorString() {
    std::cout << "\n=== Test minimum_element avec Vector<string> ===" << std::endl;
    
    Vector<std::string> vec;
    vec.push_back("orange");
    vec.push_back("pomme");
    vec.push_back("banane");
    vec.push_back("abricot");
    vec.push_back("kiwi");
    
    std::cout << "Fruits: ";
    for (const auto& fruit : vec) {
        std::cout << fruit << " ";
    }
    std::cout << std::endl;
    
    // Test avec strings (comparaison lexicographique)
    auto min_it = minimum_element(vec.begin(), vec.end());
    if (min_it != vec.end()) {
        std::cout << "Premier fruit alphabetique: " << *min_it << std::endl;
        assert(*min_it == "abricot");
    }
    
    // Test sous-plage - avancer manuellement
    auto start = vec.begin();
    ++start; // "pomme"
    auto end = vec.begin();
    for (int i = 0; i < 4; ++i) ++end; // Après "kiwi"
    min_it = minimum_element(start, end);
    if (min_it != end) {
        std::cout << "Minimum entre pomme et kiwi: " << *min_it << std::endl;
        assert(*min_it == "banane");
    }
}

void testMinimumElementStackInt() {
    std::cout << "\n=== Test minimum_element avec Stack<int> ===" << std::endl;
    
    Stack<int> stack;
    stack.push(100);
    stack.push(45);
    stack.push(200);
    stack.push(30);
    stack.push(150);
    
    std::cout << "Contenu de la pile (haut->bas): ";
    for (int val : stack) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    // Test plage complète
    Stack<int>::iterator min_it = minimum_element(stack.begin(), stack.end());
    if (min_it != stack.end()) {
        std::cout << "Minimum dans la pile: " << *min_it << std::endl;
        assert(*min_it == 30);
    }
    
    // Test sous-plage (3 premiers éléments)
    Stack<int>::iterator start = stack.begin();     // Premier élément (100)
    Stack<int>::iterator stop = stack.begin();
    for (int i = 0; i < 3; ++i) ++stop;            // Après le 3ème élément
    
    min_it = minimum_element(start, stop);
    if (min_it != stop) {
        std::cout << "Minimum dans les 3 premiers elements: " << *min_it << std::endl;
        assert(*min_it == 45);
    }
}

// Structure personnalisée pour tester operator<
struct Point {
    int x, y;
    
    // Surcharge de operator< pour la comparaison
    bool operator<(const Point& other) const {
        // Comparaison d'abord par x, puis par y
        if (x != other.x) {
            return x < other.x;
        }
        return y < other.y;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Point& p) {
        os << "(" << p.x << "," << p.y << ")";
        return os;
    }
};

void testMinimumElementCustomType() {
    std::cout << "\n=== Test minimum_element avec type personnalise ===" << std::endl;
    
    Vector<Point> points;
    points.push_back({5, 3});
    points.push_back({2, 7});
    points.push_back({2, 5});
    points.push_back({8, 1});
    points.push_back({2, 3});
    
    std::cout << "Points: ";
    for (const auto& p : points) {
        std::cout << p << " ";
    }
    std::cout << std::endl;
    
    // Test minimum selon operator< défini
    auto min_it = minimum_element(points.begin(), points.end());
    if (min_it != points.end()) {
        std::cout << "Point minimum: " << *min_it << std::endl;
        assert(min_it->x == 2 && min_it->y == 3);
    }
    
    // Test sous-plage - avancer manuellement
    auto start = points.begin();
    ++start; // Point {2, 7}
    auto end = points.begin();
    for (int i = 0; i < 4; ++i) ++end; // Après le point {2, 3}
    min_it = minimum_element(start, end);
    if (min_it != end) {
        std::cout << "Minimum entre positions 1 et 4: " << *min_it << std::endl;
        assert(min_it->x == 2 && min_it->y == 5);
    }
}

void testEdgeCases() {
    std::cout << "\n=== Test cas limites ===" << std::endl;
    
    // Test 1: Vector avec un seul élément
    {
        Vector<int> single;
        single.push_back(42);
        
        auto min_it = minimum_element(single.begin(), single.end());
        std::cout << "Vector avec un element: ";
        if (min_it != single.end()) {
            std::cout << *min_it << std::endl;
            assert(*min_it == 42);
        }
    }
    
    // Test 2: Vector avec éléments égaux
    {
        Vector<int> equal;
        equal.push_back(10);
        equal.push_back(10);
        equal.push_back(10);
        
        auto min_it = minimum_element(equal.begin(), equal.end());
        std::cout << "Vector avec elements egaux: ";
        if (min_it != equal.end()) {
            std::cout << *min_it << std::endl;
            assert(*min_it == 10);
        }
    }
    
    // Test 3: Plage décroissante
    {
        Vector<int> descending;
        for (int i = 10; i > 0; --i) {
            descending.push_back(i);
        }
        
        auto min_it = minimum_element(descending.begin(), descending.end());
        std::cout << "Vector decroissant: ";
        if (min_it != descending.end()) {
            std::cout << *min_it << std::endl;
            assert(*min_it == 1);
        }
    }
    
    // Test 4: Pile vide
    {
        Stack<int> emptyStack;
        auto min_it = minimum_element(emptyStack.begin(), emptyStack.end());
        std::cout << "Pile vide: " << (min_it == emptyStack.end() ? "OK" : "ERREUR") << std::endl;
        assert(min_it == emptyStack.end());
    }
}

void testAlgorithmCompatibility() {
    std::cout << "\n=== Test compatibilite algorithme ===" << std::endl;
    
    // Tester que minimum_element fonctionne avec différents conteneurs
    {
        Vector<double> doubles;
        doubles.push_back(3.14);
        doubles.push_back(2.71);
        doubles.push_back(1.41);
        doubles.push_back(1.62);
        
        auto min_it = minimum_element(doubles.begin(), doubles.end());
        std::cout << "Minimum de doubles: ";
        if (min_it != doubles.end()) {
            std::cout << *min_it << std::endl;
            assert(*min_it == 1.41);
        }
    }
    
    {
        Stack<char> chars;
        chars.push('z');
        chars.push('m');
        chars.push('a');
        chars.push('d');
        chars.push('b');
        
        auto min_it = minimum_element(chars.begin(), chars.end());
        std::cout << "Minimum de chars: ";
        if (min_it != chars.end()) {
            std::cout << *min_it << std::endl;
            assert(*min_it == 'a');
        }
    }
}

void testWithArithmetic() {
    std::cout << "\n=== Test avec arithmetique d'iterateurs (si disponible) ===" << std::endl;
    
    Vector<int> vec;
    for (int i = 0; i < 10; ++i) {
        vec.push_back((i * 7) % 13);
    }
    
    std::cout << "Vecteur: ";
    for (int val : vec) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    // Méthode 1: Utiliser ++ pour avancer
    auto start1 = vec.begin();
    for (int i = 0; i < 3; ++i) ++start1;
    auto end1 = vec.begin();
    for (int i = 0; i < 8; ++i) ++end1;
    
    auto min1 = minimum_element(start1, end1);
    if (min1 != end1) {
        std::cout << "Minimum positions 3-8 (avec ++): " << *min1 << std::endl;
    }
    
    // Méthode 2: Si l'itérateur supporte l'arithmétique (Vector<int>::iterator le fait maintenant)
    // Note: On utilise begin() + n seulement si l'opérateur + est défini
    auto start2 = vec.begin() + 2; // Grâce à operator+(int)
    auto end2 = vec.begin() + 7;
    
    auto min2 = minimum_element(start2, end2);
    if (min2 != end2) {
        std::cout << "Minimum positions 2-7 (avec +): " << *min2 << std::endl;
    }
}

int main() {
    std::cout << "=========================================" << std::endl;
    std::cout << "EXERCICE 37 - QUESTION 2" << std::endl;
    std::cout << "Fonction minimum_element" << std::endl;
    std::cout << "=========================================" << std::endl;
    
    try {
        testMinimumElementVectorInt();
        testMinimumElementVectorString();
        testMinimumElementStackInt();
        testMinimumElementCustomType();
        testEdgeCases();
        testAlgorithmCompatibility();
        testWithArithmetic();
        
        std::cout << "\n=========================================" << std::endl;
        std::cout << "TOUS LES TESTS ONT REUSSI !" << std::endl;
        std::cout << "=========================================" << std::endl;
        
        // Démonstration finale
        std::cout << "\n=== DEMONSTRATION FINALE ===" << std::endl;
        
        Vector<int> demo;
        for (int i = 0; i < 10; ++i) {
            demo.push_back((i * 7) % 13); // Valeurs variées
        }
        
        std::cout << "Vecteur demo: ";
        for (int val : demo) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
        
        // Trouver le minimum dans différentes plages
        auto min_all = minimum_element(demo.begin(), demo.end());
        std::cout << "Minimum global: " << *min_all << std::endl;
        
        // Pour la première moitié, on avance avec ++
        auto start_first = demo.begin();
        auto end_first = demo.begin();
        for (int i = 0; i < 5; ++i) ++end_first;
        auto min_first_half = minimum_element(start_first, end_first);
        std::cout << "Minimum premiere moitie: " << *min_first_half << std::endl;
        
        // Pour la seconde moitié, on utilise l'opérateur + (si disponible)
        auto start_second = demo.begin() + 5;
        auto min_second_half = minimum_element(start_second, demo.end());
        std::cout << "Minimum seconde moitie: " << *min_second_half << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Erreur: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}