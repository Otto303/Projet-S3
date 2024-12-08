#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure pour représenter une coordonnée avec un caractère
typedef struct {
    int x;
    int y;
    char c;
} Coord;

// Fonction pour lire les coordonnées et trouver les limites
int lireCoordonnees(const char *nomFichier, Coord **coords, int *taille, int *x_min, int *x_max, int *y_min, int *y_max) {
    FILE *fichier = fopen(nomFichier, "r");
    if (!fichier) {
        printf("Erreur : Impossible d'ouvrir le fichier %s\n", nomFichier);
        return 0;
    }

    *x_min = *y_min = 2147483647;
    *x_max = *y_max = -2147483648;

    *taille = 0;
    *coords = NULL;

    while (!feof(fichier)) {
        Coord temp;
        if (fscanf(fichier, "%d %d %c", &temp.x, &temp.y, &temp.c) == 3) {
            if (temp.x < *x_min) *x_min = temp.x;
            if (temp.x > *x_max) *x_max = temp.x;
            if (temp.y < *y_min) *y_min = temp.y;
            if (temp.y > *y_max) *y_max = temp.y;

            *coords = realloc(*coords, sizeof(Coord) * (*taille + 1));
            (*coords)[*taille] = temp;
            (*taille)++;
        }
    }

    fclose(fichier);
    return 1;
}

// Fonction pour compacter chaque ligne de la matrice
void compactLignes(char **tableau, int hauteur, int largeur) {
    for (int i = 0; i < hauteur; i++) {
        int write_pos = 0;
        for (int j = 0; j < largeur; j++) {
            if (tableau[i][j] != '.') {
                tableau[i][write_pos++] = tableau[i][j];
            }
        }
        for (int j = write_pos; j < largeur; j++) {
            tableau[i][j] = '.';
        }
    }
}

// Fonction pour trier les lettres sur une même ligne par ordre croissant de x
void trierCoordonneesParLigne(Coord *coords, int taille) {
    for (int i = 0; i < taille - 1; i++) {
        for (int j = 0; j < taille - i - 1; j++) {
            if (coords[j].y == coords[j + 1].y && coords[j].x > coords[j + 1].x) {
                Coord temp = coords[j];
                coords[j] = coords[j + 1];
                coords[j + 1] = temp;
            }
        }
    }
}

// Fonction pour organiser et afficher les caractères
void construireTableau(Coord *coords, int taille, int x_min, int x_max, int y_min, int y_max) {
    int largeur = x_max - x_min + 1;
    int hauteur = y_max - y_min + 1;

    char **tableau = malloc(hauteur * sizeof(char *));
    for (int i = 0; i < hauteur; i++) {
        tableau[i] = malloc(largeur * sizeof(char));
        for (int j = 0; j < largeur; j++) {
            tableau[i][j] = '.'; // Espace vide
        }
    }

    for (int i = 0; i < taille; i++) {
        tableau[coords[i].y][coords[i].x] = coords[i].c;
    }

    compactLignes(tableau, hauteur, largeur);

    FILE *fichier = fopen("grille_compacte.txt", "w");
    if (!fichier) {
        printf("Erreur : Impossible de créer le fichier compact.\n");
        return;
    }

    for (int i = 0; i < hauteur; i++) {
        for (int j = 0; j < largeur; j++) {
            if (tableau[i][j] != '.') {
                fputc(tableau[i][j], fichier);
                putchar(tableau[i][j]);
            }
        }
        fputc('\n', fichier);
        putchar('\n');
    }
    fclose(fichier);

    for (int i = 0; i < hauteur; i++) {
        free(tableau[i]);
    }
    free(tableau);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage : %s <fichier.txt>\n", argv[0]);
        return 1;
    }

    Coord *coords;
    int taille;
    int x_min, x_max, y_min, y_max;

    if (!lireCoordonnees(argv[1], &coords, &taille, &x_min, &x_max, &y_min, &y_max)) {
        return 1;
    }

    trierCoordonneesParLigne(coords, taille); // Trier les lettres sur une même ligne
    construireTableau(coords, taille, x_min, x_max, y_min, y_max);

    free(coords);
    return 0;
}
