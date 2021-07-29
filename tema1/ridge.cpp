#include <bits/stdc++.h>

using namespace std;

ifstream f("ridge.in");
ofstream g("ridge.out");

// Functie pentru citirea din fisier.
void readInput(long long &N, vector< pair <long long, long long> > &vect) {
    long long H, C;
    f >> N;
    for (int i = 0; i < N; i++) {
        f >> H >> C;
        vect.push_back(make_pair(H, C));
    }
    f.close();
}

int main() {
    long long N;
    vector< pair <long long, long long> > vect;
    readInput(N, vect);
    // In vectorul dp retinem solutiile (costul total) pentru fiecare pas
    // daca am alege sa excavam 0, 1 sau 2 unitati. (gneram toate solutile
    // posibile)
    vector < long long > dp(3, 0);
    // Retine costul minim la fiecare pas.
    vector < long long > minimum(3);
    // Verifica daca in urma excavari inaltimea unui munte ajunge sub 0.
    vector < bool > cond(3, false);
    dp[1] = vect[0].second;
    dp[2] = 2 * vect[0].second;
    // Pentru fiecare munte verificam daca acesta are inaltimea diferita de
    // cel precedent.
    for (long long i = 1; i < N; i++) {
        for (int j = 0; j < 3; j++) {
            minimum[j] = LLONG_MAX;
            cond[j] = false;
            // Daca am excavat prea mult si am ajuns la un numar negativ,
            // trecem la urmatorul munte.
            if (vect[i].first - j < 0) {
                cond[j] = true;
                continue;
            }
            // Verificam cat ar trebui sa excavam din muntele curent pentru
            // a fi diferit ca inaltime din muntele precedent si retinem in
            // minimum excavarea cu costul cel mai mic de la pasul curent.
            for (int k = 0; k < 3; k ++) {
                if (vect[i].first - j != vect[i - 1].first - k)
                    minimum[j] = min(minimum[j], dp[k]);
            }
        }
        // Formam din nou vectorul dp adaugand cosul excavarii fiecarui munte.
        for (int j = 0; j < 3; j++) {
            if (cond[j] == false)
                dp[j] = j * vect[i].second + minimum[j];
            else
                dp[j] = minimum[j];
        }
    }
    // Afisam cosul minim cu care se poate obtine creasta dorita.
    g << *min_element(dp.begin(), dp.end());
}
