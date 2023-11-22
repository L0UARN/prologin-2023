#include <iostream>
#include <istream>
#include <string>
#include <stack>
#include <list>
#include <deque>

enum Direction {
    HORAIRE,
    ANTIHORAIRE,
};

/// \param n le nombre de villes autour de Midgard
/// \param m le nombre d'années avant le Ragnarök
/// \param villes le nom des villes autour de Midgard, en partant de la queue de Jörmungandr
/// \param actions la liste des actions prochaines de Jörmungandr
void situation_finale(int n, int m, std::list<std::string>& villes, const std::list<char>& actions) {
    /* TODO Afficher, sur une ligne par ville, la liste des villes qui seront
    rencontrées lors du Ragnarök, dans l'ordre, en partant de la queue de
    Jörmungandr jusqu'à sa tête.  */
    Direction direction = HORAIRE;
    std::stack<std::string> villes_mangees;
    std::deque<std::string> villes_libres(villes.begin(), villes.end());

    for (const char& action : actions) {
        switch (action) {
            case 'A':
                // Avancer
                if (direction == HORAIRE) {
                    villes_libres.push_back(villes_libres.front());
                    villes_libres.pop_front();
                } else {
                    villes_libres.push_front(villes_libres.back());
                    villes_libres.pop_back();
                }
                break;
            case 'M':
                // Manger
                if (villes_libres.empty()) {
                    break;
                }

                if (direction == HORAIRE) {
                    villes_mangees.push(villes_libres.front());
                    villes_libres.pop_front();
                } else {
                    villes_mangees.push(villes_libres.back());
                    villes_libres.pop_back();
                }
                break;
            case 'R':
                // Se retourner
                direction = direction == HORAIRE ? ANTIHORAIRE : HORAIRE;
                break;
            case 'C':
                // Recracher
                if (villes_mangees.empty()) {
                    break;
                }

                if (direction == HORAIRE) {
                    villes_libres.push_front(villes_mangees.top());
                    villes_mangees.pop();
                } else {
                    villes_libres.push_back(villes_mangees.top());
                    villes_mangees.pop();
                }
                break;
            default:
                break;
        }
    }

    if (direction == HORAIRE) {
        for (auto i = villes_libres.cbegin(); i != villes_libres.cend(); i++) {
            std::cout << *i << '\n';
        }
    } else {
        for (auto i = villes_libres.crbegin(); i != villes_libres.crend(); i++) {
            std::cout << *i << '\n';
        }
    }
}

int main() {
    int n; ///< le nombre de villes autour de Midgard
    std::cin >> n;
    int m; ///< le nombre d'années avant le Ragnarök
    std::cin >> m;
    std::list<std::string> villes(n); ///< le nom des villes autour de Midgard, en partant de la queue de Jörmungandr

    for (std::string& i : villes) {
        std::getline(std::cin >> std::ws, i);
    }
    std::list<char> actions(m); ///< la liste des actions prochaines de Jörmungandr
    for (char& i : actions)
        std::cin >> i;
    situation_finale(n, m, villes, actions);
}
