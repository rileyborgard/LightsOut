#ifndef GAUSSIANELIMINATION_H
#define GAUSSIANELIMINATION_H

#include <algorithm>
#include <QDebug>
#include <set>
#include <utility>
#include <algorithm>

class GaussianElimination {
public:
    static int* solve(int **A, int *b, int N, int seed, int mod);
private:
    static int xgcd(int b, int n, int *x, int *y);
    static int inv(int b, int n);
    static int crt(int num[], int rem[], int len);
    static bool isPrime(int num);
    static std::set<std::pair<int, int> > primeFact(int num);
};

#endif // GAUSSIANELIMINATION_H
