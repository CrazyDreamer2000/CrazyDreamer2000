#include <stdio.h>
#include <stdlib.h>
#include "Chaine.h"

// Exercice1 – Manipulation d’une instance de “Liste de Chaınes”

//Q1.1)

// Lit un fichier et renvoie une structure Chaines correspondante

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Chaine.h"
#include "SVGwriter.h"

#define BUFFER_SIZE 256 // Taille maximale d'une ligne dans le fichier

Chaines* lectureChaines(FILE *f) {
    char buffer[BUFFER_SIZE]; // Buffer pour lire les lignes
    Chaines *chs = malloc(sizeof(Chaines)); // Allouer la structure Chaines
    if (!chs || !f) return NULL; // Vérification de l'allocation et du fichier

    // Lire l'entête
    if (!fgets(buffer, BUFFER_SIZE, f)) return NULL; // Lire NbChain
    sscanf(buffer, "NbChain: %d", &chs->nbChaines); // Extraire le nombre de chaînes

    if (!fgets(buffer, BUFFER_SIZE, f)) return NULL; // Lire Gamma
    sscanf(buffer, "Gamma: %d", &chs->gamma); // Extraire gamma

    chs->chaines = NULL; // Initialiser la liste des chaînes à NULL

    // Lire chaque chaîne
    for (int l = 0; l < chs->nbChaines; l++) { // Pour chaque chaîne
        if (!fgets(buffer, BUFFER_SIZE, f)) break; // Lire la ligne de la chaîne

        int numero, nbCoords, n = 0; // Variables temporaires
        char *cur = buffer; // Pointeur pour parcourir la ligne

        sscanf(cur, "%d %d%n", &numero, &nbCoords, &n); // Extraire numéro et nbCoords
        cur += n; // Avancer le pointeur

        CellChaine *cch = malloc(sizeof(CellChaine)); // Allouer une nouvelle cellule de chaîne
        cch->numero = numero; // Initialiser le numéro
        cch->points = NULL; // Initialiser la liste des points à NULL
        cch->suiv = chs->chaines; // Insérer en tête de la liste des chaînes
        chs->chaines = cch; // Mettre à jour la tête de la liste

        for (int i = 0; i < nbCoords; i++) { // Pour chaque coordonnée
            double x, y; // Variables pour les coordonnées
            sscanf(cur, "%lf %lf%n", &x, &y, &n); // Extraire x et y
            cur += n; // Avancer le pointeur

            CellPoint *pt = malloc(sizeof(CellPoint)); // Allouer une nouvelle cellule de point
            pt->x = x; pt->y = y; // Initialiser les coordonnées
            pt->suiv = cch->points; // Insérer en tête de la liste des points
            cch->points = pt; // Mettre à jour la tête de la liste des points
        }
    }
    return chs; // Retourner la structure Chaines
}

//Q1.2)

void ecrireChaines(Chaines *C, FILE *f) { 
    if (!C || !f) return; 
    fprintf(f, "NbChain: %d\n", C->nbChaines);
    fprintf(f, "Gamma: %d\n", C->gamma);

    CellChaine *cch = C->chaines;
    while (cch) {
        // Compter le nombre de points
        int nbPts = 0;
        CellPoint *pt = cch->points;
        while(pt){ nbPts++; pt=pt->suiv; }
        fprintf(f, "%d %d", cch->numero, nbPts);

        pt = cch->points;
        while (pt) {
            fprintf(f, " %.2lf %.2lf", pt->x, pt->y);
            pt = pt->suiv;
        }
        fprintf(f, "\n");
        cch = cch->suiv;
    }
}

//Q1.3)

void afficheChainesSVG(Chaines *C, char* nomInstance){
    int i;
    double maxx=0,maxy=0,minx=1e6,miny=1e6;
    CellChaine *ccour;
    CellPoint *pcour;
    double precx,precy;
    SVGwriter svg;
    ccour=C->chaines;
    while (ccour!=NULL){
        pcour=ccour->points;
        while (pcour!=NULL){
            if (maxx<pcour->x) maxx=pcour->x;
            if (maxy<pcour->y) maxy=pcour->y;
            if (minx>pcour->x) minx=pcour->x;
            if (miny>pcour->y) miny=pcour->y;  
            pcour=pcour->suiv;
        }
    ccour=ccour->suiv;
    }
    SVGinit(&svg,nomInstance,500,500);
    ccour=C->chaines;
    while (ccour!=NULL){
        pcour=ccour->points;
        SVGlineRandColor(&svg);
        SVGpoint(&svg,500*(pcour->x-minx)/(maxx-minx),500*(pcour->y-miny)/(maxy-miny)); 
        precx=pcour->x;
        precy=pcour->y;  
        pcour=pcour->suiv;
        while (pcour!=NULL){
            SVGline(&svg,500*(precx-minx)/(maxx-minx),500*(precy-miny)/(maxy-miny),500*(pcour->x-minx)/(maxx-minx),500*(pcour->y-miny)/(maxy-miny));
            SVGpoint(&svg,500*(pcour->x-minx)/(maxx-minx),500*(pcour->y-miny)/(maxy-miny));
            precx=pcour->x;
            precy=pcour->y;    
            pcour=pcour->suiv;
        }
        ccour=ccour->suiv;
    }
    SVGfinalize(&svg);
}




    

