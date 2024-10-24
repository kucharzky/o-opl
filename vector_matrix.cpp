#include <iostream>
#include <vector>
#include <random>
#include <iomanip>

using std::cin, std::cout, std::endl;
using std::vector, std::string;

int main(){
    cout.precision(2);
    using DVec = vector<int>;
    using DMat = vector<DVec>;
    DMat m1(4,DVec(5, 1.0));
    DMat m2(5,DVec(4,1.0));
    int w1{ m1.size() };
    int w2{ m2.size() };
    int k1{ m1[0].size() };
    int k2{ m2[0].size() };

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 5);

    for (auto &r : m1) {
        for (auto &e : r)
            e = dist(gen);
    }

    for (auto &r : m2) {
        for (auto &e : r)
            e = dist(gen);
    }

    cout << "m1" << endl;
    for (const auto &r : m1) {
        cout << endl;
        for (const auto &e : r)
            cout << e << "\t";
    }
    cout << "\nm2" << endl;
    for (const auto &r : m2) {
        cout << endl;
        for (const auto &e : r)
            cout << e << "\t";
    }

    if (m1[0].size() != m2.size()) {
        cout << "nope" << endl;
        return 1;
    }

    DMat mw(m1.size(), DVec(m2[0].size(), 0.0));

    for (size_t i = 0; i < m1.size(); ++i) {
        for (size_t j = 0; j < m2[0].size(); ++j) {
            for (size_t k = 0; k < m1[0].size(); ++k) {
                mw[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }

    cout << "\nmw m1*m2:" << endl;
    for (const auto &r : mw) {
        for (const auto &e : r)
            cout << e << "\t";
        cout << endl;
    }

    return 0;

}