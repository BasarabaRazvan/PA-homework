#include <bits/stdc++.h>

using namespace std;

ifstream f("adrese.in");
ofstream g("adrese.out");

struct user {
    pair < string, int> id;
    set < string > emails;
};

vector < vector < int > > graph(1001);
vector< user > users, realUsers;
map < string, int > emails;

// Comparator pentru a sorta utilistaorii dupa numarul de emailuri
// primite, iar daca acestea sunt egale, lexicografic dupa nume.
bool compareSize(user u1, user u2) {
    if (u1.emails.size() == u2.emails.size()) {
        return u1.id.first < u2.id.first;
    }
    return (u1.emails.size() < u2.emails.size());
}

// Functie pentru citirea din fisier.
void readInput(int &n) {
    f >> n;
    for (int i = 0; i < n; i++) {
        user newUser;
        f >> newUser.id.first >> newUser.id.second;
        string email;
        // Bagam email-uri intr-un set pentru a fi sortate si unice.
        for (int j = 0; j < newUser.id.second; j++) {
            f >> email;
            newUser.emails.insert(email);
        }
        users.push_back(newUser);
    }
    f.close();
}

void dfs(int i, vector< bool > &visited, string &name, set< string > &mails) {
    visited[i] = true;

    // Alegem numele minim lexicografic.
    if (name > users[i].id.first) {
        name = users[i].id.first;
    }
    for (auto j : graph[i]) {
        if (!visited[j]) {
            for (auto k : users[j].emails) {
                mails.insert(k);
            }
            dfs(j, visited, name, mails);
        }
    }
}

void connectedComponents(int n, int &count) {
    // Variabila count reprezinta numarul de elemente conexe (utilizatori
    // reali).
    vector< bool > visited(n, false);
    string name;
    set< string > mails;
    for (int i = 0; i < n; i++) {
        if (visited[i] == false) {
            // Daca nodul nu a fost vizitat insemna ca avem un user nou si
            // parcurgem lista lui de adiacenta pentru a lua toate mailurile
            // diferite (folosim un set -> mailuri unicem sortate lexicografic)
            name = users[i].id.first;
            mails = users[i].emails;
            dfs(i, visited, name, mails);
            count++;

            // Creem vectorul de realUsers.
            user newUser;
            newUser.id.first = name;
            newUser.id.second = mails.size();
            for (auto em : mails) {
                newUser.emails.insert(em);
            }
            realUsers.push_back(newUser);
        }
    }
}

int main() {
    int n;
    readInput(n);

    // Pentru a vedea care users sunt unici adaugam email-urile intr-un map
    // (daca emailul deja exista in map adaugam legatura intre cei 2 users cu
    // email-ul comun).
    for (int i = 0; i < n; i++) {
        for (auto pr : users[i].emails) {
            if (emails.find(pr) == emails.end()) {
                emails[pr] = i;
            } else {
                graph[i].push_back(emails[pr]);
                graph[emails[pr]].push_back(i);
            }
        }
    }

    int count = 0;
    connectedComponents(n, count);
    g << count << endl;

    // Sortam vectoul de realUsers.
    sort(realUsers.begin(), realUsers.end(), compareSize);
    for (auto us : realUsers) {
        g << us.id.first << " " << us.id.second << endl;
        for (auto em : us.emails) {
            g << em << endl;
        }
    }
}
