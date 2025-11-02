#include <iostream>
#include <memory>
#include <stdexcept>
#include <iterator>
#include <vector>
#include <string>
using namespace std;


struct StackOverflow  : runtime_error { StackOverflow()  : runtime_error("Stack overflow")  {} };
struct StackUnderflow : runtime_error { StackUnderflow() : runtime_error("Stack underflow") {} };


template <typename T>
class Stack {
private:
    unique_ptr<T[]> data_;
    size_t capacity_;
    size_t top_;

public:

    explicit Stack(size_t capacity = 16)
        : data_(make_unique<T[]>(capacity)), capacity_(capacity), top_(0) {}


    template <typename It>
    Stack(It first, It last) {
        size_t n = static_cast<size_t>(distance(first, last));
        capacity_ = (n == 0 ? 1 : n);
        data_ = make_unique<T[]>(capacity_);
        top_ = 0;
        for (auto it = first; it != last; ++it) push(*it);
    }

    // Empiler
    void push(const T& value) {
        if (top_ >= capacity_) throw StackOverflow();
        data_[top_++] = value;
    }

    // Dépiler (retourne l'élément du haut)
    T pop() {
        if (top_ == 0) throw StackUnderflow();
        return data_[--top_];
    }

    // Voir l'élément du haut (sans dépiler)
    const T& peek() const {
        if (top_ == 0) throw StackUnderflow();
        return data_[top_ - 1];
    }

    // Utilitaires
    bool   empty()    const noexcept { return top_ == 0; }
    size_t size()     const noexcept { return top_; }
    size_t capacity() const noexcept { return capacity_; }
};

struct Produit {
    string nom;
    double prix;
};

int main() {


    Stack<int> s1(3);
    s1.push(10); s1.push(20); s1.push(30);
    cout << "[int] size=" << s1.size() << ", top=" << s1.peek() << "\n";
    cout << "pop -> " << s1.pop() << ", new top=" << s1.peek() << ", size=" << s1.size() << "\n\n";

    try {
        s1.push(40);
        s1.push(50);
    } catch (const StackOverflow& e) {
        cout << "Overflow OK: " << e.what() << "\n";
    }
    try {
        Stack<int> empty(1);
        empty.pop();
    } catch (const StackUnderflow& e) {
        cout << "Underflow OK: " << e.what() << "\n\n";
    }

    vector<string> noms = {"Anti-Atlas", "Ouaoufengha", "Alous"};
    Stack<string> s2(noms.begin(), noms.end());
    cout << "[string] size=" << s2.size() << ", top=\"" << s2.peek() << "\"\n";
    cout << "pop -> \"" << s2.pop() << "\" ; new top=\"" << s2.peek() << "\" ; size=" << s2.size() << "\n\n";


    Stack<Produit> s3(2);
    s3.push({"PC", 7500});
    s3.push({"Imprimante", 1800});
    auto p = s3.peek();
    cout << "[Produit] top=" << p.nom << " (" << p.prix << " DH)\n\n";


    {
        const size_t N = 100000;
        Stack<int> big(N);
        for (size_t i = 0; i < N; ++i) big.push(static_cast<int>(i));
        cout << "[volume] size=" << big.size() << ", top=" << big.peek() << "\n";

        for (int i = 0; i < 3; ++i) (void)big.pop();
        cout << "[volume] size apres pops=" << big.size() << ", top=" << big.peek() << "\n";
    }

    cout << "\nOK — demo terminee. (unique_ptr => pas de delete[] a ecrire)\n";
    return 0;
}
