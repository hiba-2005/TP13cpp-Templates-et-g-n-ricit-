#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <cassert>

template<typename T>
struct Asc {
    bool operator()(const T& a, const T& b) const noexcept { return a < b; }
};

template<typename T>
struct Desc {
    bool operator()(const T& a, const T& b) const noexcept { return b < a; }
};

template<typename T, typename Comp = std::less<T>>
void quickSort(std::vector<T>& v, Comp comp = Comp{}) {
    if (v.size() < 2) return;
    auto part = [&](int l, int r) -> int {
        const T& pivot = v[r];
        int i = l - 1;
        for (int j = l; j < r; ++j) {
            if (comp(v[j], pivot)) {
                ++i; std::swap(v[i], v[j]);
            }
        }
        std::swap(v[i + 1], v[r]);
        return i + 1;
    };
    std::function<void(int,int)> qs = [&](int l, int r) {
        if (l >= r) return;
        int p = part(l, r);
        if (p - 1 - l < r - (p + 1)) {
            qs(l, p - 1);
            qs(p + 1, r);
        } else {
            qs(p + 1, r);
            qs(l, p - 1);
        }
    };
    qs(0, static_cast<int>(v.size()) - 1);
}

struct Point {
    int x, y;
    bool operator<(const Point& other) const noexcept {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
};
std::ostream& operator<<(std::ostream& os, const Point& p) {
    return os << "(" << p.x << "," << p.y << ")";
}

template<typename T>
void printVec(const std::vector<T>& v, const char* title) {
    std::cout << title << " [ ";
    for (const auto& e : v) std::cout << e << " ";
    std::cout << "]\n";
}

int main() {
    std::vector<int> vi{42, 5, 17, -3, 17, 0, 9};
    printVec(vi, "Avant (int):   ");
    quickSort<int>(vi);
    printVec(vi, "Après  (int ↑):");
    quickSort<int, Desc<int>>(vi, Desc<int>{});
    printVec(vi, "Après  (int ↓):");

    std::cout << "\n";

    std::vector<std::string> vs{"ouaoufengha", "Anti-Atlas", "Alous", "Akyote", "Amnayo"};
    printVec(vs, "Avant (str):   ");
    quickSort<std::string>(vs);
    printVec(vs, "Après  (str ↑):");
    quickSort<std::string, Desc<std::string>>(vs, Desc<std::string>{});
    printVec(vs, "Après  (str ↓):");

    std::cout << "\n";

    std::vector<Point> vp{{2,5},{0,0},{2,1},{-1,3},{2,1},{1,9}};
    printVec(vp, "Avant (Point): ");
    quickSort<Point, Asc<Point>>(vp, Asc<Point>{});
    printVec(vp, "Après  (Pt ↑): ");
    quickSort<Point, Desc<Point>>(vp, Desc<Point>{});
    printVec(vp, "Après  (Pt ↓): ");

    std::cout << "\nTous les tests sont OK\n";
    return 0;
}
