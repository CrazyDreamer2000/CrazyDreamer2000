#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Chaine.h"

#define BUFFER_SIZE 256

int main() {
    FILE * f = fopen("00014_burma.cha", "r");
    char buffer[BUFFER_SIZE];

    // Init Chaines
     Chaines * chs = (Chaines *)malloc(sizeof(Chaines));
     fgets(buffer, BUFFER_SIZE, f);
     sscanf(buffer, "NbChain: %d", &chs->nbChaines);
     fgets(buffer, BUFFER_SIZE, f);
     sscanf(buffer, "Gamma: %d", &chs->gamma);
     chs->chaines = NULL; 

    // Parcours des lignes
    CellChaine * new_cell_ch; 
    CellPoint * new_coord;
    int nb_coords;
    for (int ligne = 0; ligne < chs->nbChaines; ligne++) {
        // Creation CellChaine et ajout en tête
        new_cell_ch = (CellChaine *)malloc(sizeof(CellChaine));
        fgets(buffer, BUFFER_SIZE, f);
        sscanf(buffer, "%d %d %[^\n]", &new_cell_ch->numero, &nb_coords, buffer);
        new_cell_ch->points = NULL;
        new_cell_ch->suiv = chs->chaines;
        chs->chaines = new_cell_ch;


        printf("%d %d ", new_cell_ch->numero, nb_coords);
        // printf("%s", buffer);
        // putchar('\n');
        for (int i_coord = 0; i_coord < nb_coords; i_coord++) {
            // Creation et ajout en tete de coordonnee.
            new_coord = (CellPoint *)malloc(sizeof(CellPoint));
            sscanf(buffer, "%lf %lf %[^\n]", &new_coord->x, &new_coord->y, buffer);
            printf("%lf %lf ", new_coord->x, new_coord->y);
            new_coord->suiv = new_cell_ch->points;
            new_cell_ch->points = new_coord;
        }
        putchar('\n');
    }

    // Free

    // free(chs->chaines);

    return 0;
}
