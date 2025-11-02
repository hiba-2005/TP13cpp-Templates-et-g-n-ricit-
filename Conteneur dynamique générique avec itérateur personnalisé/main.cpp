#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;


template <typename T>
class ArrayDyn {
private:
    T* data;
    int taille;
    int capacite;

public:

    ArrayDyn(int cap = 5) {
        capacite = cap;
        taille = 0;
        data = new T[capacite];
    }

    ~ArrayDyn() {
        delete[] data;
    }


    void push_back(const T& valeur) {
        if (taille >= capacite) {

            capacite *= 2;
            T* temp = new T[capacite];
            for (int i = 0; i < taille; i++) temp[i] = data[i];
            delete[] data;
            data = temp;
        }
        data[taille++] = valeur;
    }


    void pop_back() {
        if (taille > 0) taille--;
    }


    int size() const { return taille; }

    T& operator[](int i) {
        if (i < 0 || i >= taille)
            throw out_of_range("Index hors bornes !");
        return data[i];
    }


    class Iterator {
        T* ptr;
    public:
        Iterator(T* p) : ptr(p) {}
        T& operator*() const { return *ptr; }
        Iterator& operator++() { ++ptr; return *this; }
        bool operator!=(const Iterator& other) const { return ptr != other.ptr; }
    };


    Iterator begin() { return Iterator(data); }
    Iterator end() { return Iterator(data + taille); }
};


struct Produit {
    string nom;
    double prix;
    Produit(string n = "", double p = 0) : nom(n), prix(p) {}
};


int main() {
    cout << "=== TP13 : Templates et generacite (version simple) ===\n\n";


    ArrayDyn<int> A;
    A.push_back(10);
    A.push_back(20);
    A.push_back(30);
    cout << "[int] Contenu : ";
    for (auto &x : A) cout << x << " ";
    cout << endl;

    ArrayDyn<string> B;
    B.push_back("Anti-Atlas");
    B.push_back("Ouaoufengha");
    B.push_back("Alous");
    cout << "[string] Contenu : ";
    for (auto &s : B) cout << s << " ";
    cout << endl;

    ArrayDyn<Produit> C;
    C.push_back(Produit("PC", 7500));
    C.push_back(Produit("Imprimante", 1800));

    cout << "[Produit] Contenu :\n";
    for (auto &p : C)
        cout << "- " << p.nom << " (" << p.prix << " DH)\n";

    cout << "\nTaille du tableau Produit : " << C.size() << endl;

    return 0;
}
