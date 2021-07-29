#include <bits/stdc++.h>

using namespace std;

ifstream f("stocks.in");
ofstream g("stocks.out");

struct stocks {
    int currValue;
    int minValue;
    int maxValue;
};

// Functie pentru citirea din fisier.
void readInput(int &N, int &B, int &L, vector< stocks > &vect) {
    int currValue, minValue, maxValue;
    stocks stock;
    f >> N >> B >> L;
    for (int i = 0; i < N; i++) {
        f >> currValue >> minValue >> maxValue;
        stock.currValue = currValue;
        stock.minValue = minValue;
        stock.maxValue = maxValue;
        vect.push_back(stock);
    }
    f.close();
}

int main()  {
    int N, B, L, sol = 0;
    vector< stocks > vect;
    readInput(N, B, L, vect);
    // Profitul maxim obtinut folosind doar o parte din primele i
    // elemente avand pierderea maxima L.
    // Daca nu alegem obiecte profitul maxim este 0.
    int dp[501][501];
    for (int i = 0; i <= B; ++i) {
        for (int j = 0; j <= L; ++j) {
            dp[i][j] = 0;
        }
    }
    // Luand in considerare ca suma de bani trebuie sa fie mai mare ca 0
    // (deci putem alege doar actiunile care au un pret mai mic decat suma
    // de bani pe care o mai are la dispozitie Gigel) si faptul ca el nu
    // trebuie sa piarda mai mult de L (deci poate sa aleaga doar actiunile
    // in care pierderea totala e mai mica ca L), trebuie sa alegem cea mai
    // buna solutie (va fi stocata in sol).
    for (int i = 0; i < N; i++) {
        for (int j = B; j >= vect[i].currValue; j--) {
            for (int k = L; k >= vect[i].currValue - vect[i].minValue; k--) {
        dp[j][k] = max(dp[j][k],
            dp[j - vect[i].currValue][k - vect[i].currValue + vect[i].minValue]
                    + vect[i].maxValue - vect[i].currValue);
                sol = max(sol, dp[j][k]);
            }
        }
    }
    g << sol;
    return 0;
}
