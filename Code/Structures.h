// BETAS Antoine | BREMER Cédric | GEORGES Alexis
// Année 2011-2012 : 2e quadrimèstre
// Langage de programmation : Projet en C

// Structures de données pour les 3 programmes

#define tNom 51
#define META "metaProg.dat"
#define maxEtu 25 // Maximum d'étudiants dans une classe

typedef struct{

    int jour;
    int mois;
    int annee;

} Tdate; // Une date, peut toujours être utile

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

} Tetu; // Un étudiant, à complèter éventuellement !

typedef struct{

    int nbCours;
    int nbEtu;
    int annee;
    char section;
    char lettre;
    int chiffre;
    Tetu liste[maxEtu];

} Tclasse; // Une classe
