#include <bits/stdc++.h>

using namespace std;

ifstream f("valley.in");
ofstream g("valley.out");

// Functie pentru citirea din fisier.
void readInput(int &N, vector< long long > &h) {
    long long a;
    f >> N;
    for (int i = 0; i < N; i++) {
        f >> a;
        h.push_back(a);
    }
    f.close();
}

int main() {
    int N, i;
    vector< long long > h;
    readInput(N, h);
    // In vectorul cresc retin cat ar trebui sa excavez din fiecare
    // element din vector pentru ca acesta sa fie crescator.
    // In vectorul descresc retin cat ar trebui sa excavez din fiecare
    // element din vector pentru ca acesta sa fie descrescator.
    vector< long long > cresc, descresc;
    // Retin cat excavez din vector pt ca acesta sa fie descrescator.
    descresc.push_back(0);
    int j = 0;
    for (i = 1; i < N; i++) {
        if (h[i] > h[j]) {
            descresc.push_back(h[i] - h[j]);
        }
        if (h[i] <= h[j]) {
            j = i;
            descresc.push_back(0);
        }
    }
      // Retin cat excavez din vector pt ca acesta sa fie crescator.
    cresc.push_back(0);
    j = N - 1;
    for (i = N - 2; i >= 0; i--) {
        if (h[i] > h[j]) {
            cresc.push_back(h[i] - h[j]);
        }
        if (h[i] <= h[j]) {
            j = i;
            cresc.push_back(0);
        }
    }
    reverse(cresc.begin(), cresc.end());
    // In variabila sol am retinut timpul minim necesar excavarii
    // pentru a obtine o vale.
    // Am parcurs din nou cei 2 vectori si am format solutia astfel incat
    // prefixul sa fie descrescator, iar sufixul crescator.
    long long sol = 0;
    for (i = 1; i < N - 1; i++) {
        if (N == 3) {
            sol += max(cresc[i], descresc[i]);
            break;
        }
        if (i == 1 && h[i - 1] < h[i]) {
            sol += descresc[i];
            continue;
        }
        if (i == N - 2 && h[i] > h[i + 1]) {
            sol += cresc[i];
            continue;
        }
        sol += min(cresc[i], descresc[i]);
    }
    g << sol;
}
