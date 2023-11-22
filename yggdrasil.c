#include <stdio.h>
#include <stdlib.h>

/// \param n le nombre de branches de l'arbre moins 1
/// \param differences la liste des différences en hauteur des branches consécutives
void le_plus_grand_saut(int n, int* differences) {
    int hauteur_actuelle = 1;
    int hauteur_maximale = 1;
    int index_saut_vers_maximum = 0;
    for (int i = 0; i < n; i++) {
        hauteur_actuelle += differences[i];
        if (hauteur_actuelle > hauteur_maximale) {
            index_saut_vers_maximum = i;
            hauteur_maximale = hauteur_actuelle;
        }
    }

    int saut_le_plus_grand = differences[0];
    for (int i = 0; i < index_saut_vers_maximum + 1; i++) {
        if (differences[i] > saut_le_plus_grand) {
            saut_le_plus_grand = differences[i];
        }
    }

    printf("%d", saut_le_plus_grand);
}

int main() {
    int n;
    scanf("%d", &n);
    int* differences = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i)
        scanf("%d", &differences[i]);
    le_plus_grand_saut(n, differences);

    return 0;
}