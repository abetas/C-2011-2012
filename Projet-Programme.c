// BETAS Antoine | BREMER Cédric | GEORGES Alexis
// Année 2011-2012 : 2e quadrimèstre
// Langage de programmation : Projet en C

// Programme principal

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
    int i,j;
    Tclasse *tabclasses;
    Tcours *tabcours;
    int nbClasses,annee,nbCours,tailleClasse,temp;
    char section;
    FILE*F;
    FILE * ftemp;
    int quitter = 1;
    int sauvegarde = 1;
    int fin = 2;

    system ("color f0");

    // ---- Debut de l'initalisation du programme ----

    printf("\n\n Initialisation du programme :");
    printf("\n -----------------------------");

    printf("\n\n  Attention : Gestion d'une seule ann%ce/section !!\n",130);

    annee=ret_annee();
    section=choix_section();

    fichierbinaire(fibinaire,annee,section);
    fichiertexte(fitexte,annee,section);

    printf("\n\n => Nom du fichier texte : %s",fitexte);
    printf("\n => Nom du fichier binaire : %s",fibinaire);

    F = fopen(fitexte,"rt+");

    if(F!=NULL){

        nbCours = retour_nbCours(&nbClasses,fitexte);

        if((nbCours<0)||(nbCours>45)){

            printf("\n => Fichier texte non valide ! Supprimer manuellement le fichier !");
            fin=0;

        }
        else{

            printf("\n => Nombre de classes : %d",nbClasses);
            tabcours = (Tcours*)malloc(nbCours*sizeof(Tcours));
            tabcours = lecture_cours(nbCours,fitexte);

        }

    }
    else{

        printf("\n => Fichier texte non pr%csent !",130);
        fin=0;

    }

    fclose(F);

    // ---- Fin de l'initialisation ----

    ftemp = fopen(fibinaire, "rb+");

    if (ftemp == NULL) {
      printf("\n => Fichier binaire non pr%csent, le programme va fermer !",130);
      fin=0;}
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
    }

    fclose(ftemp);
    printf("\n\n Appuyer sur une touche pour continuer...");
    getch();

    while (fin!=0){

        system("cls");

        tri(tabclasses,nbClasses);
        fin = menu_principal(tabclasses);
        switch(fin){

            case 0:{break;};
            case 1:{encodage_classe(tabclasses,nbClasses); break;};
            case 2:{affichage(tabclasses,nbClasses,tabcours); break;};
            case 3:{affichage_etu(tabclasses,nbClasses,nbCours,tabcours); break;};
            case 4:{modif_etu(tabclasses,nbClasses);break;};
            case 5:{suppr_etu(tabclasses,nbClasses);break;};
            case 6:{ajout_cotes(tabclasses,nbClasses,nbCours,tabcours);break;};

        }

        if (fin!=0){
            printf("\n\n  Appuyer sur une touche pour revenir au menu...");
            fflush(stdin);
            getch();
        }

        if (fin==0){
            ftemp = fopen(fibinaire, "wb+");

            // ---- Sauvegarde binaire ----

            fwrite(tabclasses,sizeof(Tclasse),nbClasses,ftemp);
            for(i=0;i<nbClasses;i++){
                for(j=0;j<tabclasses[i].nbEtu;j++){
                    fwrite(tabclasses[i].liste[j].cotes,sizeof(float),nbCours,ftemp);
                }
            }

            // ---- Fin sauvegarde binaire ----

            quitter = 2;
            printf("\n\n  OK : Fichier sauvegard%c !",130);
            printf("\n\n  Appuyer sur une touche pour terminer...");

            fclose(ftemp);
            free(tabclasses);
            free(tabcours);

            getch();

        }
    }
}
