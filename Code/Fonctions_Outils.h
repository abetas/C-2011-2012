// BETAS Antoine | BREMER Cédric | GEORGES Alexis
// Année 2011-2012 : 2e quadrimèstre
// Langage de programmation : Projet en C

// Bibliothèque des fonctions outils

int retour_nbCours(int *nbClasses,char fitexte[6]){

    FILE *F;
    int nbCours;

    F=fopen(fitexte,"rt");
    if(F==NULL){
        printf("\n => Fichier texte non pr%csent ! Verifier la pr%csence du fichier !",130,130);
        printf("\n => Le programme va fermer !");
        nbCours=0;
    }
    else{
        fscanf(F,"%d/n",nbClasses);
        fscanf(F,"%d/n",&nbCours);
        printf("\n => Nombre de cours : %d",nbCours);
    }

    fclose(F);
    return(nbCours);

}


// ---- Choix de la classe ----
// La liste des classe se trouvera probablement dans un fichier fourni

 int choix_classe(Tclasse *tabclasses,int nbClasses){

    int i,erreur;
    int nbEtu,annee,chiffre;
    char section,lettre;
    printf("\n");

    for (i=0;i<nbClasses;i++){

        int annee = tabclasses[i].annee;
        char section = tabclasses[i].section;
        char lettre = tabclasses[i].lettre;
        int chiffre = tabclasses[i].chiffre;
        int nbEtu = tabclasses[i].nbEtu;
        if ((nbEtu==0) || (nbEtu == 1) ) {
            printf("\n ID %d : %i%c%c%d - %d %ctudiant",i,annee,section,lettre,chiffre, nbEtu, 130);
        }
        else{printf("\n ID %d : %i%c%c%d - %d %ctudiant(s)",i,annee,section,lettre,chiffre, nbEtu, 130);}

    }

    erreur=1;

    while(erreur==1){

        erreur=0;
        char verichar[5];
        int id;
        printf("\n\n Selectionner l'ID correspondant : ");
        lire(verichar,5);
        if (chaine_vide(verichar)==1) id = -2;
        else id = verif_integer(verichar);
        fflush(stdin);

        if((id>=0)&(id<nbClasses)){
            return(id);
        }
        else{
            if(nbEtu==25){
                erreur=1;
                printf("\n => Classe pleine !");
            }
            else {
                printf("\n => Erreur dans l'identifiant de la classe !");
                erreur=1;
            }
        }
    }
}



int gener_mat(){

    FILE * F;
    F = fopen(META, "rb");
    int mat;
    char temp[8];

    if (F == NULL) {
      F = fopen(META, "rb+");
      mat=200000;}
    else {
      fread(&mat, sizeof(int), 1, F);
      }

    fclose(F);

    mat++;

    F = fopen(META, "wb+");
    fwrite(&mat, sizeof(int), 1, F);
    fclose(F);

    return (mat);

}

// ---- Fonction de recherche par matricule, renvoi un etudiant ----

Tetu recherche_mat(char * matricule, Tclasse * tableau,int nbClasses){

    Tetu etu;
    int i,j;

    matricule[0]=toupper(matricule[0]);
    matricule[1]=toupper(matricule[1]);

    for (i=0;i<nbClasses;i++){
        for (j=0;j<(tableau[i].nbEtu);j++){
                if (strcmp(matricule,tableau[i].liste[j].matricule)==0) {

                        etu=tableau[i].liste[j];
                        return(etu);

                        // Sortie des deux boucles, un seul matricule

                        i=4;
                        j=maxEtu;

                }
                else {

                    strcpy(etu.matricule,"00000000");

                }
        }
    }

    return(etu);
}


// ---- Modification d'une classe ----
// procédure qui retire un element du tableau et qui decremente le nombre d'elements

void modif_classe(char * matricule,Tclasse * tableau,int nbClasses){

    int i,j,indice,classe;

    // recherche de l'étudiant, mémorise la classe et l'indice

    for (i=0;i<nbClasses;i++){
        for (j=0;j<(tableau[i].nbEtu);j++){
            if (strcmp(matricule,tableau[i].liste[j].matricule)==0) {
                indice=j; classe=i;
            }
        }
    }

    // parcours la tableau depuis l'indice de la classe et "remet en ordre"
    // Autrement dit, il comble l'espace vide

    for (i=indice;i<(tableau[classe].nbEtu);i++){
        tableau[classe].liste[i] = tableau[classe].liste[i+1];

    }

    tableau[classe].nbEtu = (tableau[classe].nbEtu)-1;

}


void tri(Tclasse * tableau, int nbClasses){

    int i,j,trie;
    Tetu temp;

    for (i=0;i<nbClasses;i++){

        trie = 0;
        while (trie==0){

            trie = 1;

            for (j=0;j<(tableau[i].nbEtu-1);j++){

                if (strcmp(tableau[i].liste[j].nom, tableau[i].liste[j+1].nom)>0) {

                    temp = tableau[i].liste[j];
                    tableau[i].liste[j] = tableau[i].liste[j+1];
                    tableau[i].liste[j+1] = temp;
                    trie = 0;
                }
                else{

                    if (strcmp(tableau[i].liste[j].nom, tableau[i].liste[j+1].nom)==0){

                            if (strcmp(tableau[i].liste[j].prenom, tableau[i].liste[j+1].prenom)>0){

                                temp = tableau[i].liste[j];
                                tableau[i].liste[j] = tableau[i].liste[j+1];
                                tableau[i].liste[j+1] = temp;
                                trie = 0;

                            }

                    }

                }
            }
        }

    }

}


int chaine_vide(char * chaine){

    if(strlen(chaine)==0) return(1);
    else return(0);

}

// Issu du site Comment Ca Marche - Je ne me souviens plus de l'adresse
int lire(char *chaine, int longueur){
    char *positionEntree = NULL;

    // On lit le texte saisi au clavier
    if (fgets(chaine, longueur, stdin) != NULL)  // Si la saisie se fait sans erreur
    {
        positionEntree = strchr(chaine, '\n'); // On recherche l'"Entrée"
        if (positionEntree != NULL) // Si on a trouvé le retour à la ligne
        {
            *positionEntree = '\0'; // On remplace ce caractère par \0
        }
        return 1; // On renvoie 1 si la fonction s'est déroulée sans erreur
    }
    else
    {
        return 0; // On renvoie 0 s'il y a eu une erreur
    }
}


Tdate encod_date(){

    Tdate datemp;
    char verichar[5];

    // Permet de savoir si la date est bonne ou non.
    int statutdate = 0;

    //On prend l'heure du système qu'on assigne à la variable time
    SYSTEMTIME time;
    GetLocalTime(&time);


    while (statutdate==0) {

        statutdate=1;

        printf("  Entrer le jour : ");
        lire(verichar,5);
        datemp.jour = verif_integer(verichar);
        if (chaine_vide(verichar)==1) {statutdate = 0;}
        fflush(stdin);
        printf("  Entrer le mois : ");
        lire(verichar,5);
        datemp.mois = verif_integer(verichar);
        if (chaine_vide(verichar)==1) {statutdate = 0;}
        fflush(stdin);
        printf("  Entrer l'ann%ce : ", 130);
        lire(verichar,5);
        datemp.annee = verif_integer(verichar);
        if (chaine_vide(verichar)==1) {statutdate = 0;}
        fflush(stdin);

        if (statutdate == 0) {printf("\n Erreur.\n\n");}

        else {

            if ((datemp.annee >= 1900) && (datemp.annee < time.wYear)) {
                if ((datemp.mois == 4) || (datemp.mois == 6) || (datemp.mois == 9) || (datemp.mois == 11)) {
                    if ((datemp.jour>30)||(datemp.jour<0)) {
                        printf("\n Erreur.\n\n");
                        statutdate = 0;
                    }
                }

                if ((datemp.mois == 1) || (datemp.mois == 3) || (datemp.mois == 5) || (datemp.mois == 7) || (datemp.mois == 8) || (datemp.mois == 10) || (datemp.mois == 12)) {
                    if ((datemp.jour>31)||(datemp.jour<0)) {
                        printf("\n Erreur.\n\n");
                        statutdate = 0;
                    }
                }

                if (datemp.mois == 2) {
                    if ((datemp.annee%4)==0) {
                        if ((datemp.annee%100)==0) {

                            if ((datemp.annee%400)==0) {

                                if ((datemp.jour > 29)||(datemp.jour<0)) {
                                    printf("\n Erreur dans le jour. Le mois de f%cvrier %d contient max 29 jours.\n\n", 130, datemp.annee);
                                    statutdate = 0;
                                }

                            }
                            else {

                                if ((datemp.jour>28)||(datemp.jour<0)) {
                                    printf("\n Erreur dans le jour. Le mois de f%cvrier %d contient max 28 jours.\n\n", 130, datemp.annee);
                                    statutdate = 0;
                                }

                            }

                        }
                        else {
                            if ((datemp.jour > 29)||(datemp.jour<0)) {
                            printf("\n Erreur dans le jour. Le mois de f%cvrier %d contient max 29 jours.\n\n", 130, datemp.annee);
                            statutdate = 0;
                            }
                        }
                    }
                    else {
                        if ((datemp.jour>28)||(datemp.jour<0)) {
                            printf("\n Erreur dans le jour. Le mois de f%cvrier %d contient max 28 jours.\n\n", 130, datemp.annee);
                            statutdate = 0;
                        }
                    }
                }
                if ((datemp.mois < 1) || (datemp.mois > 12)) {
                    printf("\n Erreur.\n\n");
                    statutdate = 0;
                }
            }

            if (datemp.annee == time.wYear) {
                if (datemp.mois > time.wMonth) {
                    printf("\n Erreur, la date entr%ce est ult%crieure %c la date actuelle.\n\n", 130, 130, 133);
                    statutdate = 0;
                }

                if (datemp.mois == time.wMonth) {
                    if (datemp.jour > time.wDay) {
                        printf("\n Erreur, la date entr%ce est ult%crieure %c la date actuelle.\n\n", 130, 130, 133);
                        statutdate = 0;
                    }
                }

                if (datemp.mois < time.wMonth) {
                    if ((datemp.mois == 4) || (datemp.mois == 6) || (datemp.mois == 9) || (datemp.mois == 11)) {
                        if ((datemp.jour> 30)||(datemp.jour<0)) {
                            printf("\n Erreur.\n\n");
                            statutdate = 0;
                        }
                    }

                    if ((datemp.mois == 1) || (datemp.mois == 3) || (datemp.mois == 5) || (datemp.mois == 7) || (datemp.mois == 8) || (datemp.mois == 10) || (datemp.mois == 12)) {
                        if ((datemp.jour>31)||(datemp.jour<0)) {
                            printf("\n Erreur.\n\n");
                            statutdate = 0;
                        }
                    }

                    if (datemp.mois == 2) {
                       if ((datemp.annee%4)==0) {
                            if ((datemp.annee%100)==0) {

                                if ((datemp.annee%400)==0) {

                                    if ((datemp.jour > 29)||(datemp.jour<0)) {
                                        printf("\n Erreur dans le jour. Le mois de f%cvrier %d contient max 29 jours.\n\n", 130, datemp.annee);
                                        statutdate = 0;
                                    }

                                }
                                else {

                                    if ((datemp.jour>28)||(datemp.jour<0)) {
                                        printf("\n Erreur dans le jour. Le mois de f%cvrier %d contient max 28 jours.\n\n", 130, datemp.annee);
                                        statutdate = 0;
                                    }

                                }

                            }
                            else {
                                if ((datemp.jour > 29)||(datemp.jour<0)) {
                                printf("\n Erreur dans le jour. Le mois de f%cvrier %d contient max 29 jours.\n\n", 130, datemp.annee);
                                statutdate = 0;
                                }
                            }
                        }
                        else {
                            if ((datemp.jour>28)||(datemp.jour<0)) {
                                printf("\n Erreur dans le jour. Le mois de f%cvrier %d contient max 28 jours.\n\n", 130, datemp.annee);
                                statutdate = 0;
                            }
                        }
                    }
                }
            }

            if ((datemp.annee < 1900) && (datemp.annee != -2)) {

                printf("\n Erreur. L'ann%ce entr%ce est ant%crieure %c 1900.\n\n", 130, 130, 130, 133);
                statutdate = 0;
            }

            if (datemp.annee > time.wYear) {
                printf("\n Erreur, la date entr%ce est ult%crieure %c la date actuelle.\n\n", 130, 130, 133);
                statutdate = 0;
            }

            if ((datemp.annee == -2) || (datemp.mois == -2) || (datemp.jour == -2)) {

                printf("\n Erreur.\n\n");
                statutdate = 0;

            }
        }

    }

    return (datemp);

}


char choix_section(){

    char temp,temp2[3];
    int i,erreur;

    erreur=1;

    while (erreur==1){

        printf("\n  Section : ");
        printf("\n\n   %c C : Comptabilit%c",254,130);
        printf("\n   %c D : Droit",254);
        printf("\n   %c E : Commerce ext%crieur",254,130);
        printf("\n   %c M : Marketing", 254);
        printf("\n   %c T : Informatique", 254);
        printf("\n\n  Choix : ");
        scanf("%s",&temp2);
        fflush(stdin);
        for(i=0;i<strlen(temp2);i++){
            temp2[i]=toupper(temp2[i]);
        }
        fflush(stdin);

        if ((strcmp(temp2,"T")!= 0)&&(strcmp(temp2,"C")!=0)&&(strcmp(temp2,"M")!=0)&&(strcmp(temp2,"D")!=0)&&(strcmp(temp2,"E")!=0)){

            printf("  => Erreur dans la section !\n");
            erreur=1;

        }
        else {
            erreur=0;
            temp = temp2[0];
        }

    }

    fflush(stdin);
    return(temp);

}


int ret_annee(){

    int erreur=1;
    int annee;
    char verichar[5];

    while(erreur==1){

        printf("\n  Ann%ce : ",130);
        lire(verichar, 5);
        if (chaine_vide == 1) {annee = -2;}
        else annee = verif_integer(verichar);
        fflush(stdin);

        if ((annee!=1)&&(annee!=2)&&(annee!=3)){
            printf(" => Erreur, l'ann%ce doit %ctre comprise entre 1 et 3 !",130, 136);
        }
        else erreur=0;
    }
    return(annee);
}

// ---- Renvoi de la classe ----
// Renvoi l'indice de la classe d'un etudiant en entrant le tableau, l'etudiant et le nombre de classes

int renvoi_classe(Tclasse * tableau, Tetu etu, int nbClasses){

    int i,j,classe;

    for (i=0;i<nbClasses;i++){
        for (j=0;j<(tableau[i].nbEtu);j++){
            if (strcmp(etu.matricule,tableau[i].liste[j].matricule)==0) {
                classe=i;
            }
        }
    }

    return(classe);

}


// ---- Génère de nom du fichier binaire ----

void fichierbinaire(char fibinaire[6],int annee,char section){

    char temp=(annee+48);

    fibinaire[0]=temp;
    fibinaire[1]=section;
    fibinaire[2]='.';
    fibinaire[3]='d';
    fibinaire[4]='a';
    fibinaire[5]='t';
    fibinaire[6]='\0';

    fflush(stdin);

}


// ---- Génère le nom du fichier texte ----

void fichiertexte(char *fitexte,int annee,char section){

    char temp=(annee+48);

    fitexte[0]=temp;
    fitexte[1]=section;
    fitexte[2]='.';
    fitexte[3]='t';
    fitexte[4]='x';
    fitexte[5]='t';
    fitexte[6]='\0';

    fflush(stdin);

}


// ---- Calcul de la moyenne ----
// Fait rentrer les cotes, les pondérations et le nombre de cours
// Renvoi une moyenne générale pondérée

float calcul_moyenne(Tcours *tabcours,float *cotes,int nbCours,float *total_ects){

    int i;
    float moyenne=0;
    int erreur=0;

    *total_ects=0;

    for(i=0;i<nbCours;i++){

        if(cotes[i]!=-1){
            if(cotes[i]>=10){
                moyenne=moyenne+(tabcours[i].ECTS*cotes[i]);
                *total_ects=*total_ects+tabcours[i].ECTS;
            }
        }
        else{erreur++;}

    }

    if(erreur==0){
        if(moyenne>0){
            moyenne=(moyenne/(*total_ects))*5;
            return(moyenne);
        }
        else{return(0);}
    }
    else{return(-1);}
}

// ---- Calcul de la moyenne générale ----
// ---- Prend tout les cours y compris ceux en echec ----
// ---- A titre informatif, ne dois pas être utilisé dans le cadre de la réussite !!!! ----

float calcul_moyenne_tout(Tcours *tabcours,float *cotes,int nbCours,float *total_ects){

    int i;
    float moyenne=0;
    int erreur=0;

    *total_ects=0;

    for(i=0;i<nbCours;i++){

        if(cotes[i]!=-1){
            moyenne=moyenne+(tabcours[i].ECTS*cotes[i]);
            *total_ects=*total_ects+tabcours[i].ECTS;
        }
        else{erreur++;}

    }

    if(erreur==0){
        if(moyenne!=0){
            moyenne=(moyenne/(*total_ects))*5;
            return(moyenne);
        }
        else{return(0);}
    }
    else{return(-1);}

}

Tcours* lecture_cours(int nbCours,char fitexte[6]){

    int temp,i;
    float temp2;
    FILE *F;
    Tcours *tableau;

    F=fopen(fitexte,"rt");

    // Elimination du nombre de classes et de cours du fichier txt

    fscanf(F,"%d\n",&temp);
    fscanf(F,"%d\n",&temp);

    tableau=(Tcours*)malloc(nbCours*sizeof(Tcours));

    for(i=0;i<nbCours;i++){

        fscanf(F,"%d\t",&temp);
        fscanf(F,"%f\t",&temp2);
        tableau[i].ECTS=temp2;
        fgets (tableau[i].nom,101,F);
        tableau[i].nom[strlen(tableau[i].nom)-1]='\0';
        fflush(stdin);
    }

    fclose(F);

    return (tableau);
    free(tableau);

}


void tri_moyenne(int nbClasses,Tclasse* tabclasses,Tcours *tabcours,int nbCours){

    int i,j,trie;
    int r1,r2;
    float m1,m2;
    Tetu temp;
    float total_ects1,total_ects2;

    total_ects1=0;
    total_ects2=0;

    for(j=0;j<nbClasses;j++){
        trie=0;
        while(trie==0){
            trie=1;
            for(i=0;i<tabclasses[j].nbEtu-1;i++){

                m1=calcul_moyenne(tabcours,tabclasses[j].liste[i].cotes,nbCours,&total_ects1);
                m2=calcul_moyenne(tabcours,tabclasses[j].liste[i+1].cotes,nbCours,&total_ects2);

                if((m1>=60)&&(total_ects1==60)){r1=1;}
                else{
                    if((m1>=60)&&(total_ects1>=48)){r1=2;}
                    else{r1=3;}
                }

                if((m2>=60)&&(total_ects2==60)){r2=1;}
                else{
                    if((m2>=60)&&(total_ects2>=48)){r2=2;}
                    else{r2=3;}
                }

                if(r1>r2){

                    temp=tabclasses[j].liste[i];
                    tabclasses[j].liste[i]=tabclasses[j].liste[i+1];
                    tabclasses[j].liste[i+1]=temp;
                    trie=0;

                }
                else{
                    if(r1==r2){
                        if(m1<m2){
                            temp=tabclasses[j].liste[i];
                            tabclasses[j].liste[i]=tabclasses[j].liste[i+1];
                            tabclasses[j].liste[i+1]=temp;
                            trie=0;
                        }
                        else{
                            if(m1==m2){
                                if(strcmp(tabclasses[j].liste[i].nom,tabclasses[j].liste[i+1].nom)>0){
                                    temp=tabclasses[j].liste[i];
                                    tabclasses[j].liste[i]=tabclasses[j].liste[i+1];
                                    tabclasses[j].liste[i+1]=temp;
                                    trie=0;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void creation_texte(int annee,char section,Tclasse *tabclasses,int classe,Tcours *tabcours,int nbCours){

    FILE *F;
    char temp=(annee+48);
    char temp2;
    char lettre;
    int chiffre,i;
    float moyenne;
    char fichier[15]={temp,section,'-','-','-','C','o','t','e','s','.','t','x','t','\0'};
    float  total_ects;

    lettre=tabclasses[classe].lettre;
    chiffre=tabclasses[classe].chiffre;
    temp2=(chiffre+48);

    fichier[2]=lettre;
    fichier[3]=temp2;

    printf("\n\n => Nom du fichier : %s",fichier);

    F=fopen(fichier,"wb+");

    fprintf(F,"\n Classement des etudiants par ordre décroissant de ");
    fprintf(F,"%d%c%c%d",tabclasses[classe].annee,tabclasses[classe].section,tabclasses[classe].lettre,tabclasses[classe].chiffre);
    fprintf(F,"\n ------------------------------------------------------\n");

    for(i=0;i<tabclasses[classe].nbEtu;i++){

        moyenne=calcul_moyenne(tabcours,tabclasses[classe].liste[i].cotes,tabclasses[classe].nbCours,&total_ects);

        fprintf(F,"\n %-10s %-15s %-12s",tabclasses[classe].liste[i].matricule,tabclasses[classe].liste[i].nom,tabclasses[classe].liste[i].prenom);
        fprintf(F,"%2d/%2d/%4d",tabclasses[classe].liste[i].ddn.jour,tabclasses[classe].liste[i].ddn.mois,tabclasses[classe].liste[i].ddn.annee);

        if(moyenne==-1){
            fprintf(F,"  Moyenne : ---- !",130);
        }
        else{
            fprintf(F,"  Moyenne : %.2f",moyenne);
            fprintf(F," (%.1f ECTS)",total_ects);
        }

    }

    fclose(F);

}


int verif_integer (char verichar[5]) {

        int tempoInt, i, taille;
        int erreur = 0;
        taille = strlen(verichar);

        for(i=0;i<(taille);i++){

            if((verichar[i]<48) || (verichar[i]>57)){
                erreur = erreur++;
            }
        }

        if(erreur==0){
            tempoInt=atoi(verichar);
        }
        else{tempoInt=-2;}

        fflush(stdin);

        return(tempoInt);

}


// ---- Initialisation ----
// La procédure agit (via des pointeurs) sur l'année et la section en cours de traitement

int initialisation(int*annee,char*section){

    printf("\n 1. Initialisation de l'ann%ce et de la section :",130);
    printf("\n -----------------------------------------------\n");

    *annee = ret_annee();
    fflush(stdin);
    *section = choix_section();
    fflush(stdin);

}


int fichiers_existent(char fibinaire[6],char fitexte[6]){

    FILE *texte;
    FILE *binaire;
    int erreurs=0;

    printf("\n 2. Verification des fichiers :");
    printf("\n ------------------------------");

    printf("\n\n => Fichier binaire : %s",fibinaire);
    printf("\n => Fichier texte : %s",fitexte);

    texte=fopen(fitexte,"rt");
    if (texte!=NULL){
        printf("\n Erreur : fichier texte existant !");
        erreurs=1;
    }
    binaire=fopen(fibinaire,"rt");
    if(binaire!=NULL){
        printf("\n Erreur : fichier binaire existant !");
        erreurs=1;
    }

    if(erreurs==1){
    printf("\n\n => Le programme va s'arr%cter !", 136);
    }

    return(erreurs);

}


int creation_texte_init(int *nbClasses,int *nbCours,char fitexte[6]){

    char verifloat[10];
    char verichar[5];
    FILE *f;
    int i, j,id;
    char nom[255];
    float ects;
    int erreur,taille;
    char section[30], temp;
    temp = fitexte[1];

    switch (temp) {

        case 'T' : {strcpy(section, "Technologie de l'informatique"); break;};
        case 'E' : {strcpy(section, "Commerce exterieur"); break;};
        case 'M' : {strcpy(section, "Marketing"); break;};
        case 'D' : {strcpy(section, "Droit"); break;};
        case 'C' : {strcpy(section, "Comptabilite"); break;};

    }

    taille=strlen(section);


    printf("\n\n 3. Cr%cation de la liste de cours pour la : %ce %s",130, fitexte[0], section);
    printf("\n ----------------------------------------------");

    for(i=0;i<taille;i++){
        printf("-");
    }

    printf("\n");

    f = fopen(fitexte, "wb+");
    fflush(stdin);

    while ((*nbClasses<1) || (*nbClasses>10)) {

        printf("\n Nombre de classes : ");
        lire(verichar,5);
        if (chaine_vide(verichar) == 1) *nbClasses = -2;
        else *nbClasses = verif_integer(verichar);

        if ((*nbClasses < 1) || (*nbClasses > 10)) {printf("\n Erreur dans le nombre entr%c. Veuillez recommencer.", 130);}

    }

    *nbClasses=(*nbClasses)*2;
    fprintf(f,"%d\n",*nbClasses);
    fflush(stdin);
    *nbCours = 0;

    while ((*nbCours<1) || (*nbCours>45)) {

        printf(" Nombre de cours : ");
        lire(verichar,5);
        if (chaine_vide(verichar) == 1) *nbCours = -2;
        *nbCours = verif_integer(verichar);

        if ((*nbCours < 1) || (*nbCours > 45)) {printf("\n Erreur dans le nombre entr%c. Veuillez recommencer.", 130);}

    }

    fflush(stdin);
    fprintf(f,"%d\n",*nbCours);

        for(i=0;i<*nbCours;i++){

           fflush(stdin);

            printf("\n\n Id : %d",i);
            id = i;

            erreur=1;

            while(erreur==1){

                erreur=0;

                printf("\n Nom du cours : ");
                lire (nom,101);
                if(chaine_vide(nom)==1){
                    erreur=1;
                    printf(" => Erreur, nom invalide !");
                }

            }

            erreur = 1;

            while(erreur==1){
                erreur=0;
                printf(" ECTS : ");
                lire(verifloat,10);
                taille=strlen(verifloat);

                for(j=0;j<(taille);j++){

                    if(verifloat[j]==44){verifloat[j]=46;}

                    if((verifloat[j]<46) || (verifloat[j]>57) || (verifloat[j]==47)){
                        if(j==0){
                            if(verifloat[j]!=45){erreur++;}
                        }
                        else {erreur++;}
                    }
                }

                if(erreur==0){
                    ects=atof(verifloat);
                }
                else{ects=-2;}


                if((ects>0)&&(ects<=18)){
                    erreur=0;
                }
                else{
                    printf("    => Erreur ! Cr%cdit compris entre 0.5 et 18 !!\n", 130);
                    erreur = 1;
                }

            fflush(stdin);
            }

            fprintf(f,"%d\t%f\t%s\n", id, ects, nom);
        }

    return(nbClasses);

}


// ---- Création du tableau de classe ----
// Crée un tableau dynamique en fonction du nombre de classe et de cours
// Renvoi ce tableau qui sera fusionné par après

Tclasse *encodage(int nbClasses,int nbCours,int annee,int section){

    int memAll; // Memoire allouée au tableau temporaire
    int i,j,k,l,erreur;
    char classe; // Variable temporaire pour la lettre de la classe
    Tclasse *tabtemp;

    printf("\n\n 3. Cr%cation du tableau de classe(s) :",130);
    printf("\n -------------------------------------");

    printf("\n => Nombre de demi classes (groupes) : %d",nbClasses);
    fflush(stdin);

    // Création du tableau temporaire de classes

    tabtemp = (Tclasse*)malloc(nbClasses*sizeof(Tclasse));

    printf("\n\n => Espace m%cmoire du tableau temporaire : %d octets\n\n",130,(nbClasses*sizeof(Tclasse)));

    k=1;
    for(i=0;i<nbClasses;i++){

        erreur=1;

        while(erreur==1){

            erreur=0;

            printf("  - Classe %d (lettre) : ",k);
            scanf("%c",&classe);
            classe = toupper(classe);
            fflush(stdin);

            if((classe<65)||(classe>90)){

                erreur=1;
                printf("   => Nom de classe invalide !\n");

            }


        }

        // Seul le demi groupe diffère pour 2 classes consécutives !

        for(j=0;j<2;j++){

            tabtemp[i+j].nbCours=nbCours;
            tabtemp[i+j].nbEtu=0;
            tabtemp[i+j].annee=annee;
            tabtemp[i+j].section=section;
            tabtemp[i+j].lettre=classe;
            tabtemp[i+j].chiffre=j+1;

        }
        i++;
        k++;

    }

    return(tabtemp);

}


void recapitulatif(Tclasse *tabtemp,int nbCours,int nbClassesMtn){

    int i;

    printf("\n 4. R%ccapitulatif :",130);
    printf("\n ------------------\n");

    for(i=0;i<nbClassesMtn;i++){

        printf("\n  %d%c%c%d",tabtemp[i].annee,tabtemp[i].section,tabtemp[i].lettre,tabtemp[i].chiffre);
        if ((tabtemp[i].nbEtu == 0) || (tabtemp[i].nbEtu == 1)) {
            printf(" %c %d %ctudiant",254,tabtemp[i].nbEtu,130);
        }
        else{printf(" %c %d %ctudiants",254,tabtemp[i].nbEtu,130);}
        printf(" %c %d cours",254,tabtemp[i].nbCours);

    }

    printf("\n\n Appuyer sur une touche pour continuer...");
}


int renvoi_memoire(int nbCours){

    // Cette fonction permet la bonne sauvegarde du fichier binaire
    // En simulant la présence des tableaux de cotes dans le fichier

    int memAll,temp;

    temp = maxEtu*nbCours*sizeof(float);
    memAll = sizeof(Tclasse)+temp;

    return(memAll);
}
