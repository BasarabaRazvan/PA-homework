#include <bits/stdc++.h>

using namespace std;

ifstream f("poduri.in");
ofstream g("poduri.out");

// Vectori folositi pebtru directii.
int dir_Orizontal_X[2] = {0, 0};
int dir_Orizontal_Y[2] = {-1, 1};

int dir_Vertical_X[2] = {-1, 1};
int dir_Vertical_Y[2] = {0, 0};

int dir_Dublu_X[4] = {-1, 0, 1, 0};
int dir_Dublu_Y[4] = {0, 1, 0, -1};
int costMin = INT32_MAX;

// Functie pentru citirea din fisier.
void readInput(int &n, int &m, int &x, int &y,
                vector< vector < char > > &vect) {
    f >> n >> m;
    f >> x >> y;
    for (int i = 0; i < n; i++) {
       for (int j = 0; j < m; j++) {
            f >>  vect[i][j];
       }
    }
    f.close();
}

// Functie care verifica daca o pozitie (x, y) se afla in matrice.
bool inInterval(int n, int m, int x, int y) {
    if (x < n && x >= 0 && y < m && y >= 0) {
        return true;
    }
    return false;
}

void lee(int n, int m, vector< vector < char > > &vect,
                queue< pair < pair < int, int >, int > > &q) {
    pair < pair < int, int >, int > curr;
    int x, y, x_nou, y_nou, cost;
    int ok = 0;

    // Cat timp mai avem optiunii de mers si inca nu am ajuns pe margine,
    // scoatem din coada primul element.
    while (!q.empty() && ok == 0) {
        curr = q.front();
        x = curr.first.first;
        y = curr.first.second;
        cost = curr.second;

        // Daca pozitia actuala corespunde unui pod vertical, atunci verificam
        // daca urmatoarea miscare valida nu iasa din interval si daca pe
        // poitia urmatoare nu se afla apa(caz in care adaugam in coada
        // optiunea aleasa).
        if (vect[x][y] == 'V') {
            for (int i = 0; i < 2; i++) {
                x_nou = x + dir_Vertical_X[i];
                y_nou = y + dir_Vertical_Y[i];
                if (inInterval(n, m, x_nou, y_nou)
                            && vect[x_nou][y_nou] != '.') {
                    q.push({{x_nou, y_nou}, cost + 1});
                }
                // Daca Gigel a ajuns la margine, atunci am gasit costul minim.
                if (!inInterval(n, m, x_nou, y_nou)) {
                    costMin = cost + 1;
                    ok = 1;
                    break;
                }
            }
        }

        // Daca pozitia actuala corespunde unui pod orizontal, atunci verificam
        // daca urmatoarea miscare valida nu iasa din interval si daca pe
        // poitia urmatoare nu se afla apa(caz in care adaugam in coada
        // optiunea aleasa).
        if (vect[x][y] == 'O') {
            for (int i = 0; i < 2; i++) {
                x_nou = x + dir_Orizontal_X[i];
                y_nou = y + dir_Orizontal_Y[i];
                if (inInterval(n, m, x_nou, y_nou)
                        && vect[x_nou][y_nou] != '.') {
                    if (cost + 1 < costMin) {
                        costMin = cost + 1;
                    }
                    q.push({{x_nou, y_nou}, cost + 1});
                }
                // Daca Gigel a ajuns la margine, atunci am gasit costul minim.
                if (!inInterval(n, m, x_nou, y_nou)) {
                    costMin = cost + 1;
                    ok = 1;
                    break;
                }
            }
        }

        // Daca pozitia actuala corespunde unui pod dublu, atunci verificam
        // daca urmatoarea miscare valida nu iasa din interval si daca pe
        // poitia urmatoare nu se afla apa(caz in care adaugam in coada
        // optiunea aleasa).
        if (vect[x][y] == 'D') {
            for (int i = 0; i < 4; i++) {
                x_nou = x + dir_Dublu_X[i];
                y_nou = y + dir_Dublu_Y[i];
                if (inInterval(n, m, x_nou, y_nou)
                        && vect[x_nou][y_nou] != '.') {
                    if (cost + 1 < costMin) {
                        costMin = cost + 1;
                    }
                    q.push({{x_nou, y_nou}, cost + 1});
                }
                // Daca Gigel a ajuns la margine, atunci am gasit costul minim.
                if (!inInterval(n, m, x_nou, y_nou)) {
                    costMin = cost + 1;
                    ok = 1;
                    break;
                }
            }
        }
        // Marcam pozitia ca vizitata.
        vect[x][y] = '.';
        q.pop();
    }

    // Daca Gigel a reusit sa ajunga la margine returnam costul gasit, iar daca
    // nu atunci returnam -1.
    if (costMin != INT32_MAX) {
        g <<  costMin;

    } else {
        g << -1;
    }
}

int main() {
    int n, m, x, y;
    vector< vector < char > > vect(2051, vector< char >(2051));
    readInput(n, m, x, y, vect);

    // Folosim o coada de perechi (pozitie si costul necesar sa ajunga pana in
    // pozitia respectiva) pentru a vedea optiuniile pe care le are Gigel.
    queue< pair < pair < int, int >, int > > q;

    // Adaugam in coadapozitia pe care se afla Gigel, care are costul 0.
    q.push({{x - 1, y - 1}, 0});
    lee(n, m, vect, q);
}
