#include "gaussianelimination.h"
#include <cstdlib>

int* GaussianElimination::solve(int **A, int *b, int N, int seed, int mod) {
    int x[N], inverse[mod];
    if(isPrime(mod)) {
        for(int i = 1; i < mod; i++)
            inverse[i] = inv(i, mod);
        for(int p = 0; p < N; p++) {
            //find pivot row and swap
            int max = p;
            for (int i = p; i < N; i++)
                if (A[i][p] > A[max][p])
                    max = i;
            std::swap(A[p], A[max]);
            std::swap(b[p], b[max]);

            // pivot within A and b
            for (int i = p + 1; i < N; i++) {
                int factor = A[i][p] * inverse[A[p][p]];
                b[i] = ((b[i] - factor * b[p]) % mod + mod) % mod;
                for (int j = p; j < N; j++)
                    A[i][j] = ((A[i][j] - factor * A[p][j]) % mod + mod) % mod;
            }
        }

        // back substitution
        int count = 0;
        for(int i = N - 1; i >= 0; i--) {
            if(A[i][i] == 0) {
                x[i] = (seed % mod + mod) % mod;
                seed /= mod;
                count++;
                continue;
            }
            int sum = 0;
            for(int j = i + 1; j < N; j++)
                sum = (sum + A[i][j] * x[j]) % mod;
            x[i] = (((b[i] - sum) * inverse[A[i][i]]) % mod + mod) % mod;
        }
        qDebug() << count;
    }else {
        std::set<std::pair<int, int> > pfact = primeFact(mod);
        int z[N][pfact.size()];
        int rem[pfact.size()];
        int idx = 0;
        int **A2 = (int**) malloc(N * sizeof(int*));
        int *b2 = (int*) malloc(N * sizeof(int));
        for(int i = 0; i < N; i++) {
            A2[i] = (int*) malloc(N * sizeof(int));
        }
        for(std::set<std::pair<int, int> >::iterator it = pfact.begin(); it != pfact.end(); it++) {
            rem[idx] = (*it).first;
            for(int i = 0; i < N; i++) {
                for(int j = 0; j < N; j++) {
                    A2[i][j] = A[i][j] % (*it).first;
                }
                b2[i] = b[i] % (*it).first;
            }
            for(int i = 1; i < (*it).first; i++)
                inverse[i] = inv(i, (*it).first);

            for(int p = 0; p < N; p++) {
                //find pivot row and swap
                int max = p;
                for (int i = p; i < N; i++)
                    if (A2[i][p] > A2[max][p])
                        max = i;
                std::swap(A2[p], A2[max]);
                std::swap(b2[p], b2[max]);

                // pivot within A2 and b2
                for (int i = p + 1; i < N; i++) {
                    int factor = A2[i][p] * inverse[A2[p][p]];
                    b2[i] = ((b2[i] - factor * b2[p]) % (*it).first + (*it).first) % (*it).first;
                    for (int j = p; j < N; j++)
                        A2[i][j] = ((A2[i][j] - factor * A2[p][j]) % (*it).first + (*it).first) % (*it).first;
                }
            }

            // back substitution
            for(int i = N - 1; i >= 0; i--) {
                int sum = 0;
                for(int j = i + 1; j < N; j++)
                    sum = (sum + A2[i][j] * z[j][idx]) % (*it).first;
                z[i][idx] = (((b2[i] - sum) * inverse[A2[i][i]]) % (*it).first + (*it).first) % (*it).first;
            }
            idx++;
        }
        for(int i = 0; i < N; i++) {
            x[i] = crt(rem, z[i], pfact.size());
        }
        for(int i = 0; i < N; i++) {
            free(A[i]);
        }
        free(A);
        free(b);
    }
    free(inverse);
    return x;
}

int GaussianElimination::xgcd(int a, int b, int *x, int *y) {
    if(a == 0) {
        *x = 0, *y = 1;
        return b;
    }
    int x1, y1;
    int gcd = xgcd(b % a, a, &x1, &y1);
    *x = y1 - (b / a) * x1;
    *y = x1;
    return gcd;
}

int GaussianElimination::inv(int a, int m) {
    int x, y;
    int g = xgcd(a, m, &x, &y);
    if(g != 1)
        return -1;
    return (x % m + m) % m;
}

int GaussianElimination::crt(int num[], int rem[], int len) {
    int prod = 1;
    for(int i = 0; i < len; i++)
        prod *= num[i];
    int result = 0;
    for(int i = 0; i < len; i++) {
        int pp = prod / num[i];
        result += rem[i] * inv(pp, num[i]) * pp;
    }
    return result % prod;
}

bool GaussianElimination::isPrime(int n) {
    if(n <= 1)
        return false;
    else if(n <= 3)
        return true;
    else if(n % 2 == 0 || n % 3 == 0)
        return false;
    for(int i = 5; i * i <= n; i += 6) {
        if(n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    return true;
}

std::set<std::pair<int, int> > GaussianElimination::primeFact(int num) {
    std::set<std::pair<int, int> > res;
    for(int i = 2; i <= num; i++) {
        int mult = 0;
        while(num % i == 0) {
            num /= i;
            mult++;
        }
        if(mult)
            res.insert(std::make_pair(i, mult));
    }
    return res;
}
