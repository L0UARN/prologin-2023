#include <stdio.h>
#include <stdlib.h>

/// \param n le nombre de villes
/// \param r le nombre de mouvements du serpent
/// \param k le nombre de villes impliquées dans chaque mouvement
/// \param villes le nombre de bâtiments cassés dans chaque ville
void batiments(int n, int r, int k, int* villes) {
    /* TODO Afficher le nombre de bâtiments cassés à chaque ville après les $R$
    mouvements sous la forme d'une suite d'entiers séparés par des espaces.  */
    for (int i = 0; i < r; i++) {
        int max_parmi_affectees = villes[i % n];
        for (int j = i; j < i + k; j++) {
            if (villes[j % n] > max_parmi_affectees) {
                max_parmi_affectees = villes[j % n];
            }
        }

        villes[i % n] = max_parmi_affectees;
    }

    for (int i = 0; i < n; i++) {
        printf("%d", villes[i]);
        if (i != n - 1) {
            printf(" ");
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    int r;
    scanf("%d", &r);
    int k;
    scanf("%d", &k);
    int* villes = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i)
        scanf("%d", &villes[i]);
    batiments(n, r, k, villes);

    return 0;
}
