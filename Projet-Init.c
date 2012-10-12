// BETAS Antoine | BREMER C�dric | GEORGES Alexis
// Ann�e 2011-2012 : 2e quadrim�stre
// Langage de programmation : Projet en C

// Programme d'initialisation des classes

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <wchar.h>
#include <math.h>
#include <time.h>

// Biblioth�ques ( A ne pas bouger de place !! )

#include "Structures.h"
#include "Prototypes.h"
#include "Fonctions_Outils.h"
#include "Fonctions_Utilisateurs.h"


int main(){

    Tclasse *tabtemp;
    char *fitexte[6]; // Nom du fichier texte utilis�
    char *fibinaire[6]; // Nom du fichier binaire utilis�
    char section; // Section de la classe
    int annee,nbCours; // Ann�e de la classe, Nombre de cours de l'ann�e/section
    int nbClassesMtn; // Nombre de classe � l'ouverture et en traitement
    int i,j;

    system("color f0");

    initialisation(&annee,&section);

    // Cr�ation des noms des fichiers utiles pour la suite du programme

    fichierbinaire(fibinaire,annee,section);
    fichiertexte(fitexte,annee,section);

    if(fichiers_existent(fibinaire,fitexte)==0){

        creation_texte_init(&nbClassesMtn,&nbCours,fitexte);
        printf("\n\n => NbClassesMtn : %d",nbClassesMtn);

        tabtemp = encodage(nbClassesMtn,nbCours,annee,section);
        recapitulatif(tabtemp,nbCours,nbClassesMtn);

        // Essai ecriture sur fichier binaire

        FILE *F;
        F=fopen(fibinaire,"wb+");
        // fwrite(tabtemp,renvoi_memoire(nbCours),nbClassesMtn,F);

        fwrite(tabtemp,sizeof(Tclasse),nbClassesMtn,F);

        fclose(F);
        getch();
        free(tabtemp);

    }


}
