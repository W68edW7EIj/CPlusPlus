#include <iostream>
#include <algorithm>
#include <string>
#include <iterator>

// ==================== VECTOR ====================
template<typename T>
class Vector {
private:
    T* data;
    size_t capacity;
    size_t vecSize;

public:
    // Classe iterator imbriquée - version simplifiée pour l'exercice
    class iterator {
    private:
        T* ptr;
    
    public:
        // Types requis pour la compatibilité (simplifiés)
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using difference_type = std::ptrdiff_t;
        
        // Constructeur
        explicit iterator(T* p = nullptr) : ptr(p) {}
        
        // Opérateur de déréférencement
        T& operator*() const {
            return *ptr;
        }
        
        // Opérateur de pré-incrémentation
        iterator& operator++() {
            ++ptr;
            return *this;
        }
        
        // Opérateur de post-incrémentation
        iterator operator++(int) {
            iterator temp = *this;
            ++ptr;
            return temp;
        }
        
        // Opérateurs de comparaison
        bool operator==(const iterator& other) const {
            return ptr == other.ptr;
        }
        
        bool operator!=(const iterator& other) const {
            return ptr != other.ptr;
        }
        
        // Pour la compatibilité avec l'arithmétique
        iterator operator+(int n) const {
            return iterator(ptr + n);
        }
        
        difference_type operator-(const iterator& other) const {
            return ptr - other.ptr;
        }
        
        T* operator->() const {
            return ptr;
        }
    };
    
    // Constructeurs
    Vector() : data(nullptr), capacity(0), vecSize(0) {}
    
    Vector(size_t initialSize) : capacity(initialSize), vecSize(initialSize) {
        data = new T[capacity];
        for (size_t i = 0; i < vecSize; ++i) {
            data[i] = T();
        }
    }
    
    ~Vector() {
        delete[] data;
    }
    
    // Méthodes d'accès
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
    
    bool empty() const {
        return vecSize == 0;
    }
    
    // Méthodes begin() et end() pour l'itération
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
        // Types (simplifiés)
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using difference_type = std::ptrdiff_t;
        
        explicit iterator(Node* node = nullptr) : current(node) {}
        
        // Opérateur de déréférencement
        T& operator*() const {
            return current->data;
        }
        
        // Opérateur de pré-incrémentation
        iterator& operator++() {
            if (current) {
                current = current->next;
            }
            return *this;
        }
        
        // Opérateur de post-incrémentation
        iterator operator++(int) {
            iterator temp = *this;
            if (current) {
                current = current->next;
            }
            return temp;
        }
        
        // Opérateurs de comparaison
        bool operator==(const iterator& other) const {
            return current == other.current;
        }
        
        bool operator!=(const iterator& other) const {
            return current != other.current;
        }
        
        // Opérateur flèche
        T* operator->() const {
            return &(current->data);
        }
    };
    
    // Constructeur
    Stack() : topNode(nullptr), stackSize(0) {}
    
    ~Stack() {
        clear();
    }
    
    // Méthodes de la pile
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
    
    // Méthodes begin() et end() pour l'itération
    iterator begin() {
        return iterator(topNode);
    }
    
    iterator end() {
        return iterator(nullptr);
    }
};

// ==================== FONCTIONS DE TEST ====================
void testVectorBasics() {
    std::cout << "\n=== TEST VECTOR BASICS ===" << std::endl;
    
    Vector<int> vec;
    
    // Test push_back
    std::cout << "1. Test push_back: ";
    for (int i = 1; i <= 5; i++) {
        vec.push_back(i * 10);
        std::cout << i * 10 << " ";
    }
    std::cout << std::endl;
    
    // Test accès avec []
    std::cout << "2. Test operator[]: ";
    for (size_t i = 0; i < vec.size(); i++) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
    
    // Test avec itérateur personnalisé
    std::cout << "3. Test avec iterateur personnalise: ";
    for (Vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // Test avec range-based for loop (C++11)
    std::cout << "4. Test range-based for loop: ";
    for (int val : vec) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    // Test modification via itérateur
    std::cout << "5. Modification via iterateur: ";
    for (Vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
        *it = *it + 5;
    }
    for (int val : vec) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

void testStackBasics() {
    std::cout << "\n=== TEST STACK BASICS ===" << std::endl;
    
    Stack<int> stack;
    
    // Test push
    std::cout << "1. Test push: ";
    for (int i = 1; i <= 5; i++) {
        stack.push(i * 3);
        std::cout << i * 3 << " ";
    }
    std::cout << std::endl;
    
    // Test top
    std::cout << "2. Top element: " << stack.top() << std::endl;
    
    // Test itérateur personnalisé (parcours haut → bas)
    std::cout << "3. Parcours avec iterateur (haut->bas): ";
    for (Stack<int>::iterator it = stack.begin(); it != stack.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // Test avec range-based for loop
    std::cout << "4. Range-based for loop: ";
    for (int val : stack) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    // Test LIFO
    std::cout << "5. Test LIFO (pop 2 elements):" << std::endl;
    std::cout << "   Before pop: top = " << stack.top();
    stack.pop();
    std::cout << ", after first pop: top = " << stack.top();
    stack.pop();
    std::cout << ", after second pop: top = " << stack.top() << std::endl;
    
    // Test pile de strings
    Stack<std::string> strStack;
    strStack.push("Hello");
    strStack.push("World");
    strStack.push("!");
    
    std::cout << "6. Stack of strings: ";
    for (const auto& str : strStack) {
        std::cout << str << " ";
    }
    std::cout << std::endl;
}

void testIteratorOperations() {
    std::cout << "\n=== TEST ITERATOR OPERATIONS ===" << std::endl;
    
    Vector<int> vec;
    for (int i = 0; i < 10; i++) {
        vec.push_back(i * 2);
    }
    
    std::cout << "Vector content: ";
    for (int val : vec) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    // Test opérateur de comparaison
    Vector<int>::iterator it1 = vec.begin();
    Vector<int>::iterator it2 = vec.begin() + 3;
    
    std::cout << "1. Comparison operators:" << std::endl;
    std::cout << "   it1 == it2? " << (it1 == it2 ? "true" : "false") << std::endl;
    std::cout << "   it1 != it2? " << (it1 != it2 ? "true" : "false") << std::endl;
    
    // Test arithmétique d'itérateur
    std::cout << "2. Iterator arithmetic:" << std::endl;
    std::cout << "   *it1 = " << *it1 << std::endl;
    std::cout << "   *it2 = " << *it2 << std::endl;
    std::cout << "   Difference it2 - it1 = " << (it2 - it1) << std::endl;
    
    // Test opérateur flèche avec structures
    struct Person {
        std::string name;
        int age;
    };
    
    Vector<Person> people;
    people.push_back({"Alice", 30});
    people.push_back({"Bob", 25});
    people.push_back({"Charlie", 35});
    
    std::cout << "3. Operator -> test:" << std::endl;
    for (Vector<Person>::iterator it = people.begin(); it != people.end(); ++it) {
        std::cout << "   " << it->name << " (" << it->age << ")" << std::endl;
    }
}

void testAlgorithmManually() {
    std::cout << "\n=== TEST ALGORITHMS (MANUAL IMPLEMENTATION) ===" << std::endl;
    
    Vector<int> numbers;
    numbers.push_back(42);
    numbers.push_back(17);
    numbers.push_back(89);
    numbers.push_back(23);
    numbers.push_back(56);
    
    std::cout << "Numbers: ";
    for (int n : numbers) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
    
    // Implémentation manuelle de find
    int target = 89;
    Vector<int>::iterator found = numbers.end();
    for (Vector<int>::iterator it = numbers.begin(); it != numbers.end(); ++it) {
        if (*it == target) {
            found = it;
            break;
        }
    }
    
    if (found != numbers.end()) {
        std::cout << "Found " << target << " in vector" << std::endl;
    } else {
        std::cout << target << " not found in vector" << std::endl;
    }
    
    // Implémentation manuelle de count_if
    int countEven = 0;
    for (Vector<int>::iterator it = numbers.begin(); it != numbers.end(); ++it) {
        if (*it % 2 == 0) {
            countEven++;
        }
    }
    std::cout << "Number of even elements: " << countEven << std::endl;
    
    // Implémentation manuelle de max_element
    if (!numbers.empty()) {
        Vector<int>::iterator maxIt = numbers.begin();
        for (Vector<int>::iterator it = numbers.begin(); it != numbers.end(); ++it) {
            if (*it > *maxIt) {
                maxIt = it;
            }
        }
        std::cout << "Maximum element: " << *maxIt << std::endl;
    }
}

int main() {
    std::cout << "=========================================" << std::endl;
    std::cout << "EXERCICE 37 - DESIGN PATTERN ITERATOR" << std::endl;
    std::cout << "=========================================" << std::endl;
    
    testVectorBasics();
    testStackBasics();
    testIteratorOperations();
    testAlgorithmManually();
    
    // Démonstration finale
    std::cout << "\n=== FINAL DEMONSTRATION ===" << std::endl;
    
    std::cout << "1. Vector demonstration:" << std::endl;
    Vector<std::string> words;
    words.push_back("Design");
    words.push_back("Pattern");
    words.push_back("Iterator");
    words.push_back("Implementation");
    
    std::cout << "   Words: ";
    for (const auto& word : words) {
        std::cout << word << " ";
    }
    std::cout << std::endl;
    
    std::cout << "2. Stack demonstration:" << std::endl;
    Stack<double> values;
    values.push(3.14159);
    values.push(2.71828);
    values.push(1.61803);
    
    std::cout << "   Values (top to bottom): ";
    for (double val : values) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    std::cout << "\n=== EXERCICE COMPLET AVEC SUCCES ===" << std::endl;
    std::cout << "Points demontres:" << std::endl;
    std::cout << "✓ Pattern Iterator implemente" << std::endl;
    std::cout << "✓ Operateurs *, ++, ==, != surcharges" << std::endl;
    std::cout << "✓ Methodes begin() et end()" << std::endl;
    std::cout << "✓ Compatible avec range-based for loop" << std::endl;
    std::cout << "✓ Deux implementations differentes (Vector et Stack)" << std::endl;
    
    return 0;
}