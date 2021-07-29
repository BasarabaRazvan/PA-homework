#include <bits/stdc++.h>

using namespace std;

ifstream f("crypto.in");
ofstream g("crypto.out");

// Functie pentru citirea din fisier.
void readInput(int &N, int &B, vector< pair <int, int> > &vect) {
    int P, U;
    f >> N >> B;
    for (int i = 0; i < N; i++) {
        f >> P >> U;
        vect.push_back(make_pair(P, U));
    }
    f.close();
}

int main() {
    int N, B, i;
    vector< pair <int, int> > vect;
    readInput(N, B, vect);
    // Sortam vectorul cresactor dupa numarul de monede pe care le poate mina.
    sort(vect.begin(), vect.end());
    // In variabila sol retinem numarul de monede care pot fi minate dupa
    // upgrade.
    // In variabila minimum tinem nuamrul de monede care pot fi minate pana in
    // acel moment.
    // In variabila suma retinem suma costurilor pana in momentul i.
    // Variabila complet este folosit sa verific daca am reusit sa upgradez
    // toate calculatoarele
    int sol = 0;
    int minimum = vect[0].first;
    int suma = 0;
    bool complet = false;
    for (i = 0; i < N; i++) {
        // Daca costul pentru a upgrada calculatorul i este mai mare ca banii
        // ramasi, inseamna ca nu mai putem upgrada niciun calculator.
        if (B - vect[i].second < 0) {
            break;
        }
        // Daca elementul curent este egal cu minimum, adunam la suma costul
        // acestuia.
        if (vect[i].first == minimum && (B - vect[i].second >= 0)) {
            suma += vect[i].second;
        }
        // Daca elementul curent e mai mare ca minimum, atunci trbuie sa
        // upgradam toate calculatoarele pana la acesta. Verificam daca avem
        // suficienti bani, iar in caz ca nu upgradam doar cat se poate. Daca
        // avem suficienti bani, facem upgrade la calculatoare, scadem suma
        // necesara de bani si actualizam minimum ca fiind elementul curent.
        if (vect[i].first > minimum) {
            if ((minimum + B / suma) < vect[i].first) {
                sol = minimum + B / suma;
                break;
            }
            sol = min(vect[i].first, minimum + B / suma);
            B -= (sol - minimum) * suma;
            minimum = vect[i].first;
            suma += vect[i].second;
        }
        // Daca am ajuns la ultimul calculator, atunci solutia este minimum.
        if (i == N - 1) {
            complet = true;
            sol = minimum;
        }
    }
    // Daca au mai ramas bani, adunam la solutie cate upgraduri mai
    // pot sa mai fac.
    if (B > 0 && complet == true) {
        sol += B / suma;
    }
    g << sol;
}
