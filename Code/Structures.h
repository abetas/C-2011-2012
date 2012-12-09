// BETAS Antoine | BREMER C�dric | GEORGES Alexis
// Ann�e 2011-2012 : 2e quadrim�stre
// Langage de programmation : Projet en C

// Structures de donn�es pour les 3 programmes

#define tNom 51
#define META "metaProg.dat"
#define maxEtu 25 // Maximum d'�tudiants dans une classe

typedef struct{

    int jour;
    int mois;
    int annee;

} Tdate; // Une date, peut toujours �tre utile

typedef struct{

    char nom[101];
    float ECTS;

} Tcours;  // Un cours

typedef struct{

    char matricule[9];
    char nom[tNom];
    char prenom[tNom];
    Tdate ddn;
    float *cotes;

} Tetu; // Un �tudiant, � compl�ter �ventuellement !

typedef struct{

    int nbCours;
    int nbEtu;
    int annee;
    char section;
    char lettre;
    int chiffre;
    Tetu liste[maxEtu];

} Tclasse; // Une classe
