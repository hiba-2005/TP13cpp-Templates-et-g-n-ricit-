#include <iostream>
#include <initializer_list>
#include <stdexcept>
#include <iomanip>
using namespace std;

template <typename T, size_t N, size_t M>
class Matrice {
public:
    T data[N][M];

    Matrice() {
        for (size_t i = 0; i < N; ++i)
            for (size_t j = 0; j < M; ++j)
                data[i][j] = T{};
    }


    Matrice(initializer_list<initializer_list<T>> rows) : Matrice() {
        if (rows.size() > N) throw runtime_error("Trop de lignes");
        size_t i = 0;
        for (auto& r : rows) {
            if (r.size() > M) throw runtime_error("Trop de colonnes");
            size_t j = 0;
            for (auto& v : r) data[i][j++] = v;
            ++i;
        }
    }


    T& operator()(size_t i, size_t j) {
        if (i >= N || j >= M) throw out_of_range("Index hors bornes");
        return data[i][j];
    }
    const T& operator()(size_t i, size_t j) const {
        if (i >= N || j >= M) throw out_of_range("Index hors bornes");
        return data[i][j];
    }


    Matrice<T,N,M> operator+(const Matrice<T,N,M>& other) const {
        Matrice<T,N,M> r;
        for (size_t i = 0; i < N; ++i)
            for (size_t j = 0; j < M; ++j)
                r.data[i][j] = data[i][j] + other.data[i][j];
        return r;
    }


    Matrice<T,N,M> operator-(const Matrice<T,N,M>& other) const {
        Matrice<T,N,M> r;
        for (size_t i = 0; i < N; ++i)
            for (size_t j = 0; j < M; ++j)
                r.data[i][j] = data[i][j] - other.data[i][j];
        return r;
    }


    template <size_t P>
    Matrice<T,N,P> operator*(const Matrice<T,M,P>& rhs) const {
        Matrice<T,N,P> r;
        for (size_t i = 0; i < N; ++i) {
            for (size_t k = 0; k < P; ++k) {
                T acc{};
                for (size_t j = 0; j < M; ++j) {
                    acc += data[i][j] * rhs.data[j][k];
                }
                r.data[i][k] = acc;
            }
        }
        return r;
    }


    friend ostream& operator<<(ostream& os, const Matrice& A) {
        for (size_t i = 0; i < N; ++i) {
            os << "[ ";
            for (size_t j = 0; j < M; ++j) {
                os << setw(8) << A.data[i][j] << (j+1<M ? " " : "");
            }
            os << " ]\n";
        }
        return os;
    }
};

int main() {
    cout << fixed << setprecision(2);

    Matrice<int,2,3> A{{ {1, 2, 3}, {4, 5, 6} }};
    Matrice<int,3,2> B{{ {7, 8}, {9, 10}, {11, 12} }};

    cout << "A (2x3):\n" << A;
    cout << "B (3x2):\n" << B;

    auto C = A * B;
    cout << "C = A * B (2x2):\n" << C << "\n";

    Matrice<int,2,3> A2{{ {10, 10, 10}, {1, 1, 1} }};
    cout << "A2 (2x3):\n" << A2;
    cout << "A + A2:\n" << (A + A2);
    cout << "A2 - A:\n" << (A2 - A) << "\n";


    Matrice<double,2,2> D1{{ {1.5, 2.0}, {3.25, -0.5} }};
    Matrice<double,2,2> D2{{ {0.5, -1.0}, {2.0, 4.0} }};

    cout << "D1 (2x2):\n" << D1;
    cout << "D2 (2x2):\n" << D2;
    cout << "D1 + D2:\n" << (D1 + D2);
    cout << "D1 - D2:\n" << (D1 - D2);
    cout << "D1 * D2:\n" << (D1 * D2);

    return 0;
}
