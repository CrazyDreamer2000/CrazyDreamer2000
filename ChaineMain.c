#include <stdio.h>
#include <stdlib.h>
#include "Chaine.h"  // Ton fichier d'entête avec struct et prototypes
#include "SVGwriter.h"

int main(int argc, char *argv[]) {
    // Vérification des arguments
    if (argc < 3) {
        printf("Usage : %s fichier_entree.cha fichier_sortie.cha\n", argv[0]);
        return 1;
    }

    // Lecture du fichier d'entrée
    FILE *fin = fopen(argv[1], "r");
    if (!fin) {
        printf("Impossible d'ouvrir le fichier %s en lecture.\n", argv[1]);
        return 1;
    }
    Chaines *C = lectureChaines(fin);
    fclose(fin);

    // Écriture du fichier de sortie
    FILE *fout = fopen(argv[2], "w");
    if (!fout) {
        printf("Impossible d'ouvrir le fichier %s en écriture.\n", argv[2]);
        return 1;
    }
    ecrireChaines(C, fout);
    fclose(fout);

    printf("Lecture et écriture réussies.\n");
    return 0;

    afficheChainesSVG(C, "maSortie.html");

}

