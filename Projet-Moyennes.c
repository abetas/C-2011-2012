// BETAS Antoine | BREMER Cédric | GEORGES Alexis
// Année 2011-2012 : 2e quadrimèstre
// Langage de programmation : Projet en C

// Programme pour le fichier texte des moyennes

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <wchar.h>
#include <math.h>
#include <time.h>

// Bibliothèques ( A ne pas bouger de place !! )

#include "Structures.h"
#include "Prototypes.h"
#include "Fonctions_Outils.h"
#include "Fonctions_Utilisateurs.h"

int main(){

    char *fitexte[6]; // Nom du fichier texte utilisé
    char *fibinaire[6]; // Nom du fichier binaire utilisé
    int annee,nbCours,nbClasses,temp,i,j;
    char section;
    Tclasse *tabclasses;
    Tcours *tabcours;
    FILE *ftemp;

    system("color f0");

    printf("\n\n Initialisation du programme :");
    printf("\n -----------------------------\n");

    annee=ret_annee();
    section=choix_section();

    fichierbinaire(fibinaire,annee,section);
    fichiertexte(fitexte,annee,section);

    printf("\n\n => Nom du fichier texte : %s",fitexte);
    printf("\n => Nom du fichier binaire : %s",fibinaire);

    nbCours = retour_nbCours(&nbClasses,fitexte);

    if(nbCours!=0){

        printf("\n => Nombre de classes : %d",nbClasses);

        tabcours = (Tcours*)malloc(nbCours*sizeof(Tcours));
        tabcours = lecture_cours(nbCours,fitexte);

        printf("\n\n Appuyer sur une touche pour continuer...");
        getch();

        ftemp=fopen(fibinaire,"rb+");

        if (ftemp == NULL) {
            printf("\n => Fichier binaire non pr%csent, le programme va fermer !",130);
            printf("\n\n Appuyer sur une touche pour terminer...");
            getch();
        }
        else {

            temp=(nbClasses*(sizeof(Tclasse)));
            tabclasses = (Tclasse*)malloc(temp);
            fread(tabclasses,sizeof(Tclasse),nbClasses,ftemp);

            for(i=0;i<nbClasses;i++){
                for(j=0;j<tabclasses[i].nbEtu;j++){
                    tabclasses[i].liste[j].cotes=(float*)malloc(nbCours*sizeof(float));
                    fread(tabclasses[i].liste[j].cotes,sizeof(float),nbCours,ftemp);
                }
            }

            tri_moyenne(nbClasses,tabclasses,tabcours,nbCours);

            affichage2(tabclasses,nbClasses,tabcours);

            printf("\n\n Appuyer sur une touche pour terminer...");
            getch();

            free(tabclasses);
            free(tabcours);
        }

        fclose(ftemp);

    }

}
