#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void copier_tableau(int n, const int* original, int* destination) {
    for (int i = 0; i < n; i++) {
        destination[i] = original[i];
    }
}

void tri_selection(int n, int* tailles) {
    for (int i = 0; i < n - 1; i++) {
        int plus_petit = i;
        for (int j = i; j < n; j++) {
            if (tailles[j] < tailles[plus_petit]) {
                plus_petit = j;
            }
        }

        int temp = tailles[i];
        tailles[i] = tailles[plus_petit];
        tailles[plus_petit] = temp;
    }
}

/// \param k le nombre magique
/// \param n le nombre de personnes
/// \param tailles la liste des tailles de chaque personne
void ordre(int k, int n, int* tailles) {
    /* TODO Afficher **OUI** s'il est possible de trier les personnes par
    taille ou **NON** si ce n'est pas possible. */
    int* tailles_triees = malloc(n * sizeof(int));
    copier_tableau(n, tailles, tailles_triees);
    tri_selection(n, tailles_triees);

    bool possible = true;
    for (int i = 0; i < n; i++) {
        int nombre_bonnes_positions = 0;

        for (int j = 0; j < n; j++) {
            if (tailles[i] != tailles_triees[j]) {
                continue;
            }

            const int distance = i - j;
            if ((distance % k) != 0) {
                continue;
            }

            nombre_bonnes_positions++;
        }

        if (nombre_bonnes_positions == 0) {
            possible = false;
            break;
        }
    }

    if (possible) {
        printf("OUI");
    } else {
        printf("NON");
    }

    free(tailles_triees);
}

int main() {
    int k;
    scanf("%d", &k);
    int n;
    scanf("%d", &n);
    int* tailles = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i)
        scanf("%d", &tailles[i]);
    ordre(k, n, tailles);

    return 0;
}