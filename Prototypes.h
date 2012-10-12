// BETAS Antoine | BREMER Cédric | GEORGES Alexis
// Année 2011-2012 : 2e quadrimèstre
// Langage de programmation : Projet en C

// Prototypes des fonctions

    // ---- Fonctions utilisateurs ----

    int menu_principal(Tclasse * tabclasses);
    void affichage(Tclasse*tableau, int nbClasses,Tcours *tabcours);
    void affichage_etu(Tclasse * tableau, int nbClasses,int nbCours,Tcours *tabcours);
    void affichage2(Tclasse*tableau, int nbClasses,Tcours *tabcours);
    Tclasse *encodage(int nbClasses,int nbCours,int annee,int section);
    void ajout_cotes(Tclasse * tableau, int nbClasses,int nbCours,Tcours *tabcours);
    void modif_etu(Tclasse * tableau,int nbClasses);
    void suppr_etu(Tclasse * tableau,int nbClasses);

    // ---- Fonctions outils ----

    char choix_section();
    char supp_enter(char * chaine);
    float calcul_moyenne(Tcours *tabcours,float *cotes,int nbCours,float *total_ects);
    float calcul_moyenne_tout(Tcours *tabcours,float *cotes,int nbCours,float *total_ects);
    int chaine_vide(char * chaine);
    int choix_classe(Tclasse *tabclasses,int nbClasses);
    int creation_texte_init(int *nbClasses,int *nbCours,char fitexte[6]);
    int fichiers_existent(char fibinaire[6],char fitexte[6]);
    int gener_mat();
    int initialisation(int*annee,char*section);
    int lire(char *chaine, int longueur);
    int renvoi_classe(Tclasse * tableau, Tetu etu, int nbClasses);
    int renvoi_memoire(int nbCours);
    int ret_annee();
    int retour_nbCours(int *nbClasses,char fitexte[6]);
    int verif_integer (char verichar[10]);
    Tcours* lecture_cours(int nbCours,char fitexte[6]);
    Tdate encod_date();
    Tetu recherche_mat(char * matricule, Tclasse * tableau,int nbClasses);
    void creation_texte(int annee,char section,Tclasse *tabclasses,int classe,Tcours *tabcours,int nbCours);
    void encodage_classe(Tclasse*classes,int nbClasses);
    void fichierbinaire(char fibinaire[6],int annee,char section);
    void fichiertexte(char fitexte[6],int annee,char section);
    void modif_classe(char * matricule,Tclasse * tableau,int nbClasses);
    void modif_etu(Tclasse * tableau,int nbClasses);
    void recapitulatif(Tclasse *tabtemp,int nbCours,int nbClassesMtn);
    void tri(Tclasse * tableau, int nbClasses);
    void tri_moyenne(int nbClasses,Tclasse* tabclasses,Tcours *tabcours,int nbCours);
    void Trim (char * verichar);
