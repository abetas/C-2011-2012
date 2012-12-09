// BETAS Antoine | BREMER Cédric | GEORGES Alexis
// Année 2011-2012 : 2e quadrimèstre
// Langage de programmation : Projet en C

// Bibliothèque des fonctions outils

// Permet la gestion d'une partie de l'ecole préalablement choisie

int menu_principal(Tclasse * tabclasses){

    int erreur = 1;
    int choix;
    char section[30], temp;
    int taille, i;
    char verichar[5];

    while (erreur==1){

        system("cls");
        erreur = 0;

        printf("\n________________________________________________________________________________");
        printf("\n             %c BETAS Antoine | BREMER C%cdric | GEORGES Alexis %c",1, 130,1);
        printf("\n________________________________________________________________________________");


        temp = tabclasses[0].section;

        switch (temp) {

            case 'T' : {strcpy(section, "Technologie de l'informatique"); break;};
            case 'E' : {strcpy(section, "Commerce exterieur"); break;};
            case 'M' : {strcpy(section, "Marketing"); break;};
            case 'D' : {strcpy(section, "Droit"); break;};
            case 'C' : {strcpy(section, "Comptabilite"); break;};

        }

        taille=strlen(section);

        printf("\n Gestion des %ctudiants : %de %s", 130, tabclasses[0].annee, section);
        printf("\n ---------------------------");

        for(i=0;i<taille;i++){
        printf("-");
        }
        printf("\n");

        printf("\n 1. Encodage d'un %ctudiant", 130);
        printf("\n 2. Affichage des listes");
        printf("\n 3. Affichage d'un %ctudiant", 130);
        printf("\n 4. Modification d'un %ctudiant", 130);
        printf("\n 5. Suppression d'un %ctudiant", 130);
        printf("\n 6. Ajout de cotes\n");
        printf("\n 0. Sauvegarder et quitter");

        printf("\n\n Votre choix : ");
        lire(verichar, 5);
        if (chaine_vide(verichar)==1) {choix = -2;}
        else choix = verif_integer(verichar);
        fflush(stdin);

        if (choix<0 || choix > 6){
            printf("\n\n => Erreur dans le choix de l'entr%ce (0 - 6) !!!", 130);
            erreur = 1;
            getch();
        }

    }

    return (choix);

}

// ---- Encodage d'un etudiant ----
// Uniquement l'encodage et le choix de la classe

void encodage_classe(Tclasse*tabclasses,int nbClasses){

    int choixOK = 0;
    int choix2 = 1;
    char verif[2] = "HE";
    Tetu result;
    Tetu temp;
    Tetu controle;
    int i, erreur;

    while (choix2 !=0){

    system ("cls");
    printf("\n Encodage d'un %ctudiant :", 130);
    printf("\n ---------------------");


        printf("\n\n Taper %c!%c dans le nom pour arr%cter l'encodage.",34,34,136);
        erreur = 1;
        while (erreur == 1) {
            erreur = 0;
            printf("\n\n Nom : ");
            lire(temp.nom,tNom);

            if (chaine_vide(temp.nom) == 1) {

                printf("\n    Erreur dans le nom.");
                erreur= 1;}
        }
        // Majuscule du nom
        for(i=0;i<strlen(temp.nom);i++){
            temp.nom[i]=toupper(temp.nom[i]);
        }

        //Fonctionnalité permettant de quitter l'encodage au cas d'une entrée par erreur


        if (strcmp(temp.nom, "!")!=0) {

            fflush(stdin);
            erreur = 1;
            while (erreur == 1) {
                //fflush(stdin);
                erreur = 0;
                printf(" Pr%cnom : ", 130);
                lire(temp.prenom,tNom);
                if (chaine_vide(temp.prenom)==1) {
                    printf("\n     Erreur dans le pr%cnom.\n\n", 130);
                    erreur =1;
                }
            }
            temp.prenom[0]=toupper(temp.prenom[0]); // Majuscule de la 1ère lettre
            fflush(stdin);
            printf(" Date de naissance : \n");

            temp.ddn=encod_date();

            sprintf((char *) temp.matricule,"HE%6d", gener_mat());
            printf("\n => Matricule attribu%c : %s",130,temp.matricule);

            printf("\n\n Etudiant %c inscrire en :", 133);
            printf("\n ------------------------");

            int id;

            if(choixOK==1){

                if(choix2==1){

                    printf("\n\n Classe attribu%ce (en fonction du choix pr%cc%cdent : ",130,130,130);

                    if (tabclasses[id].nbEtu == 25) {
                        printf("\n Erreur, la classe contient d%cj%c 25 %ctudiants !", 130, 133, 130);
                        choixOK = 0;
                    }

                }
                else{
                    id=choix_classe(tabclasses,nbClasses);
                    printf("\n ----------------------------------------------------\n");
                }

            }

            while (choixOK == 0) {

                id=choix_classe(tabclasses,nbClasses);

                if (tabclasses[id].nbEtu == 25) {
                    printf("\n Erreur, la classe contient d%cj%c 25 %ctudiants !", 130, 133, 130);
                    choixOK = 0;
                }
                else choixOK = 1;

                if(choixOK==1){
                    printf("\n ----------------------------------------------------\n");
                }
            }

            // On séléctionne l'id de la classe et on y met l'etudiant
            // Ensuite on ajoute un etudiant dans notre classe en faisant nbEtu + 1

            tabclasses[id].liste[tabclasses[id].nbEtu]=temp;
            tabclasses[id].liste[tabclasses[id].nbEtu].cotes= malloc (tabclasses[id].nbCours*sizeof(float));

            for (i=0;i<(tabclasses[id].nbCours);i++){

                    tabclasses[id].liste[tabclasses[id].nbEtu].cotes[i]=-1;

            }
            (tabclasses[id].nbEtu)++;

        printf("\n Quitter l'encodage :\n");
        printf("\n   1. Non, poursuivre avec la classe actuelle");
        printf("\n   2. Non, changer de classe");
        printf("\n   0. OUI");
        printf("\n => Choix : ");
        scanf("%d", &choix2);
        fflush(stdin);

        }
        else {choix2 = 0; fflush(stdin);}

    }

}



// ---- Affichage d'une liste d'étudiants ----
// Les paramètres d'affichage devront peut-être devenir plus précis...

void affichage(Tclasse*tableau, int nbClasses,Tcours *tabcours){

    char verichar[5];
    int i;
    int choix,id;
    float moyenne;
    float total_ects=0;

    system("cls");

    printf("\n Affichage des listes :");
    printf("\n ----------------------");
    printf("\n\n Affichage de la liste des classes :");
    printf("\n -----------------------------------");

    printf("\n\n  => Nombre de classes : %d\n",nbClasses);

    for(i=0;i<nbClasses;i++){

        printf("\n ID %d - %d%c%c%d",i,tableau[i].annee,tableau[i].section,tableau[i].lettre,tableau[i].chiffre);
        if ((tableau[i].nbEtu == 0) || (tableau[i].nbEtu == 1)) {printf(" %c %d %ctudiant",254,tableau[i].nbEtu, 130);}
        else {printf(" %c %d %ctudiants",254,tableau[i].nbEtu, 130);}
        printf(" %c %d cours",254,tableau[i].nbCours);

    }

    printf("\n\n --------------\n");

    fflush(stdin);

    printf("\n 1. Afficher une classe");
    printf("\n 0. Revenir au menu principal");
    printf("\n => Choix : ");
    lire(verichar, 5);
    if (chaine_vide(verichar)==1) {choix = -2;}
    else choix = verif_integer(verichar);
    fflush(stdin);

    while ((choix!=0) && (choix!=1)) {

        choix=1;
        printf("\n Erreur. Veuillez r%centrer votre choix. (0 ou 1).", 130);
        printf("\n => Choix : ");
        lire (verichar, 5);
        if (chaine_vide(verichar)==1) {choix = -2;}
        else choix = verif_integer(verichar);
        fflush(stdin);}

    if(choix==1){

        system("cls");

        printf("\n\n Affichage d'une classe :");
        printf("\n ------------------------");

        id=choix_classe(tableau,nbClasses);

        printf("\n\n Liste des %ctudiants de la classe :",130);
        printf("\n ----------------------------------\n");



        if(tableau[id].nbEtu==0){printf("\n => Il n'y a pas d'%ctudiant dans cette classe !",130);}

        else {

            printf("\n  Concernant les moyennes : moyenne cr%cdits r%cussi, moyenne g%cn%crale !\n",130,130,130,130);
            printf("\n Mat.    ");
            printf(" Nom          ");
            printf(" Pr%cnom       ",130);
            printf("Date n.  ");
            printf("   Moyenne pond%cr%ce et g%cn%crale",130,130,130,130);
            printf("\n");
        }

        for(i=0;i<tableau[id].nbEtu;i++){

            moyenne=calcul_moyenne(tabcours,tableau[id].liste[i].cotes,tableau[id].nbCours,&total_ects);

            printf("\n %-8s %-13s %-12s",tableau[id].liste[i].matricule,tableau[id].liste[i].nom,tableau[id].liste[i].prenom);
            printf(" %2d/%2d/%4d",tableau[id].liste[i].ddn.jour,tableau[id].liste[i].ddn.mois,tableau[id].liste[i].ddn.annee);

            if(moyenne==-1){
                printf("  -----",130);
            }
            else{
                printf("  %5.2f (%4.1f ECTS)",moyenne,total_ects);

                if((moyenne>=60)&&(total_ects==60)){printf(" => R  ");}
                else{
                    if((moyenne>=60)&&(total_ects>=48)){printf(" => RCR");}
                    else{printf(" => E  ");}
                }

                moyenne=calcul_moyenne_tout(tabcours,tableau[id].liste[i].cotes,tableau[id].nbCours,&total_ects);
                printf(" %5.2f",moyenne);

            }
        }
    }
}


// ---- Modification d'un étudiant ----

void modif_etu(Tclasse * tableau,int nbClasses){

    char matricule[9];
    char controle[9] = "00000000";
    Tetu temp;
    Tetu etu;
    int i,j,classe,id,indice,modif_date;
    char lettre;

    system ("cls");

    printf("\n Modification d'un %ctudiant :", 130);
    printf("\n ----------------------------");
    printf("\n\n Entrer un matricule (HExxxxxx) : ");
    scanf("%s", matricule);

    temp = recherche_mat(matricule, tableau,nbClasses);

    if (strcmp(temp.matricule,controle)==0){

        printf("\n => Etudiant non pr%csent !", 130);

    }
    else{

        printf("\n  Matricule : %s",temp.matricule);
        printf("\n  Nom : %s",temp.nom);
        printf("\n  Pr%cnom : %s", 130, temp.prenom);
        printf("\n  Date de naissance : %d/%d/%d",temp.ddn.jour, temp.ddn.mois,temp.ddn.annee);

        printf("\n\n Attention, vous ne pouvez pas modifier le matricule");
        printf("\n Ne rien entrer correspond %c aucune modification !", 133);

        strcpy(etu.matricule,temp.matricule);
        etu.cotes=temp.cotes;

        fflush(stdin);

        printf("\n\n Nom : ");
        lire(etu.nom,tNom);
        if (chaine_vide(etu.nom)==1) strcpy(etu.nom,temp.nom);
        else {

            for(i=0;i<strlen(etu.nom);i++){
            etu.nom[i]=toupper(etu.nom[i]);
            }

        }
        fflush(stdin);
        printf(" Pr%cnom : ", 130);
        lire(etu.prenom,tNom);
        if (chaine_vide(etu.prenom)==1) strcpy(etu.prenom,temp.prenom);
        else {etu.prenom[0]=toupper(etu.prenom[0]);}
        fflush(stdin);

        printf(" \n Modifier la date (1=OUI 2=NON) : ");
        scanf("%d", &modif_date);
        fflush(stdin);

        if (modif_date==1){

            printf("\n Date de naissance :\n");
            etu.ddn = encod_date();

        }
        else {

            etu.ddn.jour = temp.ddn.jour;
            etu.ddn.mois = temp.ddn.mois;
            etu.ddn.annee = temp.ddn.annee;

        }

        for (i=0;i<nbClasses;i++){
            for (j=0;j<(tableau[i].nbEtu);j++){
                if (strcmp(matricule,tableau[i].liste[j].matricule)==0) {
                    indice=i;
                }
            }
        }

        fflush(stdin);
        printf("\n Classe de l'%ctudiant :", 130);
        printf("\n ----------------------");

        classe = choix_classe(tableau,nbClasses);

        modif_classe(etu.matricule,tableau,nbClasses);

        tableau[classe].liste[(tableau[classe].nbEtu)] = etu;
        (tableau[classe].nbEtu)++;

    }

}


void suppr_etu(Tclasse * tableau,int nbClasses){

    char verichar[5];
    char matricule[9];
    int sauvegarde = 1;
    int i,j;
    int trouve,confirm;
    Tetu temp;
    char controle[9]="00000000";

    system("cls");

    printf("\n Suppression d'un %ctudiant :", 130);
    printf("\n ----------------------------");
    printf("\n\n Entrer un matricule (HExxxxxx) : ");
    scanf("%s", matricule);

    temp = recherche_mat(matricule,tableau,nbClasses);

    if (strcmp(temp.matricule,controle)==0){

        printf("\n  => Etudiant non pr%csent !!!", 130);

    }
    else{

    fflush(stdin);
    printf("\n\n  => Voulez-vous supprimer %s %s (1=OUI, 2=NON) : ", temp.nom, temp.prenom);
    lire(verichar, 5);

    if (chaine_vide(verichar)==1) {confirm = -2;}
    else confirm = verif_integer(verichar);
    fflush(stdin);

    while ((confirm != 1) && (confirm != 2)) {

        printf("\n Erreur. Veuillez recommencer en introduisant une des valeurs indiqu%ces", 130);
        printf("\n  => Voulez-vous supprimer %s %s (1=OUI, 2=NON) : ", temp.nom, temp.prenom);
        lire(verichar, 5);
        if (chaine_vide(verichar)==1) {confirm = -2;}
        else confirm = verif_integer(verichar);
        fflush(stdin);

    }

    if (confirm==1) modif_classe(matricule,tableau,nbClasses);
    else printf(" \n\n Etudiant non supprim%c !", 130);

    }

}


void affichage_etu(Tclasse * tableau, int nbClasses,int nbCours,Tcours *tabcours){

    int classe,i,j,annee,temp;
    float temp2,moyenne;
    char section;
    Tetu etu;
    char matricule[9];
    char controle[9]="00000000";
    FILE *F;
    float total_ects=0;

    system ("cls");

    printf("\n Affichage d'un %ctudiant",130);
    printf("\n ------------------------\n");

    printf("\n  Recherche d'un %ctudiant :",130);
    printf("\n  -------------------------");

    printf("\n\n  => Matricule de l'%ctudiant correspondant : ", 130);
    scanf("%s", matricule);

    etu = recherche_mat(matricule,tableau,nbClasses);

    if(strcmp(etu.matricule,controle)==0){

        printf("\n\n  => Etudiant non pr%csent !",130);

    }
    else{

        system("cls");

        printf("\n Fiche signal%ctique :",130);
        printf("\n --------------------");

        classe = renvoi_classe(tableau,etu,nbClasses);


        printf("\n\n Matricule : %s - Classe : %d%c%c%d",etu.matricule,tableau[classe].annee,tableau[classe].section,tableau[classe].lettre,tableau[classe].chiffre);
        printf("\n Nom : %s",etu.nom);
        printf("\n Pr%cnom : %s", 130, etu.prenom);
        printf("\n N%c le %d/%d/%d",130,etu.ddn.jour,etu.ddn.mois,etu.ddn.annee);

        printf("\n\n Cotes :");
        printf("\n -------\n");

        for (i=0;i<nbCours;i++){

            if(etu.cotes[i]==-1){printf("\n  %-48s (%.1f ECTS) : Non initialis%c",tabcours[i].nom,tabcours[i].ECTS,130);}
            else{
                printf("\n  %-48s (%.1f ECTS) : %5.2f / 20",tabcours[i].nom,tabcours[i].ECTS,etu.cotes[i]);
                if(etu.cotes[i]<10){printf(" (E)");}
                else{printf(" (R)");}
            }

        }

        moyenne=calcul_moyenne(tabcours,etu.cotes,nbCours,&total_ects);

        if(moyenne==-1){printf("\n\n  => Moyenne : Toutes les cotes ne sont pas initialis%ce(s)",130);}
        else {
            printf("\n\n  => Moyenne : %.2f",moyenne);
            printf(" (sur un total de %.1f cr%cdits)",total_ects,130);

            if((moyenne>=60)&&(total_ects==60)){printf("\n  => Statut : R%cussite de plein droit !",130);}
            else{
                if((moyenne>=60)&&(total_ects>=48)){
                printf("\n  => Statut : R%cussite avec cr%cdits r%csiduels",130,130,130);
                }
                else{printf("\n  => Statut : Echec !");}
            }
        }

        moyenne=calcul_moyenne_tout(tabcours,etu.cotes,nbCours,&total_ects);

        if(moyenne==-1){
            printf("\n\n  => Moyenne g%cn%crale : Non initialis%ce !",130,130,130);
        }
        else{
            printf("\n\n  => Moyenne g%cn%crale : %.2f",130,130,moyenne);
        }

    }

}


// ---- Ajoute les cotes ----
// Par après, utilisation du tableau de cours importé depuis le fichier txt (cf programme précédent)

void ajout_cotes(Tclasse * tableau, int nbClasses,int nbCours,Tcours *tabcours){

    char verifloat[10];
    char matricule[9];
    Tetu temp;
    char controle[9]="00000000";
    int i,j,classe,erreur,taille;
    char temp3;
    float moyenne,temp2,total_ects;

    total_ects=0;

    system("cls");
    printf("\n\n Ajout de cotes :");
    printf("\n ----------------");

    printf("\n\n Matricule de l'%ctudiant : ",130);
    lire(matricule,9);

    temp = recherche_mat(matricule,tableau,nbClasses);
    classe = renvoi_classe(tableau,temp,nbClasses);

    if(strcmp(temp.matricule,controle)!=0){

        printf("\n  => Nombre de cours : %d",nbCours);
        printf("\n  => Etudiant : %s %s",temp.nom,temp.prenom);
        printf(" - %d%c%c%d",tableau[classe].annee,tableau[classe].section,tableau[classe].lettre,tableau[classe].chiffre);

        printf("\n\n Cotes actuelles de l'%ctudiant :",130);
        printf("\n -------------------------------\n");

        for(i=0;i<nbCours;i++){

            printf("\n %-48s(%.1f ECTS) : ",tabcours[i].nom,tabcours[i].ECTS);
            if(temp.cotes[i]==-1){printf("Non initialis%c",130);}
            else{printf("%5.2f / 20",temp.cotes[i]);}
        }

        moyenne=calcul_moyenne(tabcours,temp.cotes,nbCours,&total_ects);

        if(moyenne==-1){printf("\n\n => Moyenne : Toutes les cotes ne sont pas initialis%ce(s)",130);}
        else {
            printf("\n\n => Moyenne : %.2f",moyenne);
            printf(" (sur un total de %.1f cr%cdits)",total_ects,130);}

        printf("\n\n Ajout de cotes :");
        printf("\n ----------------");

        printf("\n\n Entrer -1 pour ne pas initialiser ou laisser comme tel \n");
        //temp.cotes=(float*)malloc(nbCours*sizeof(float));

        fflush(stdin);

        for(j=0;j<nbCours;j++){

            // Verification : Cote entre 0 et 20
            erreur=1;
            while(erreur==1){
                erreur=0;
                printf("\n  %c %s (%.1f ECTS) : ",254,tabcours[j].nom,tabcours[j].ECTS);

                lire(verifloat,10);
                if (chaine_vide(verifloat) == 1) {erreur = 1;}

                taille=strlen(verifloat);

                for(i=0;i<(taille);i++){

                    if(verifloat[i]==44){verifloat[i]=46;}

                    if((verifloat[i]<46) || (verifloat[i]>57) || (verifloat[i] == 47)){
                        if(i==0){
                            if(verifloat[i]!=45){erreur++;}
                        }
                        else {erreur++;}
                    }

                }

                if(erreur==0){
                    temp2=atof(verifloat);
                }
                else{temp2=-2;}

                if((temp2>=0)&&(temp2<=20)||(temp2==-1)){
                    if(temp2==-1){
                        if(temp.cotes[j]==-1){temp.cotes[j]=-1;}
                    }
                    else{
                        temp.cotes[j]=temp2;
                    }
                }
                else{
                    printf("    => Erreur ! Cote comprise entre 0 et 20 (ou -1) !!\n");
                    erreur = 1;
                }

                fflush(stdin);
            }
        }

        moyenne=calcul_moyenne(tabcours,temp.cotes,nbCours,&total_ects);

        if(moyenne==-1){printf("\n\n => Moyenne : Toutes les cotes ne sont pas initialis%ce(s)",130);}
        else {
            printf("\n\n => Moyenne : %.2f",moyenne);
            printf(" (sur un total de %.1f cr%cdits)",total_ects,130);
        }

    }
    else{

    printf("\n\n Erreur, %ctudiant non pr%csent !!",130,130);

    }

}


void affichage2(Tclasse*tableau, int nbClasses,Tcours *tabcours){

    char verichar[5];
    int i;
    int choix1, choix2,id;
    float moyenne;
    float total_ects=0;

    system("cls");

    printf("\n Affichage de la liste des classes :");
    printf("\n -----------------------------------");

    printf("\n\n  => Nombre de classes : %d\n",nbClasses);

    for(i=0;i<nbClasses;i++){

        printf("\n ID %d - %d%c%c%d",i,tableau[i].annee,tableau[i].section,tableau[i].lettre,tableau[i].chiffre);
        printf(" %c %d etudiant(s)",254,tableau[i].nbEtu);
        printf(" %c %d cours",254,tableau[i].nbCours);

    }

    printf("\n\n --------------\n");

    fflush(stdin);
    choix1 = 1;
    printf("\n 1. Afficher une classe");
    printf("\n 0. Quitter le programme");

    while (choix1 !=0) {

        printf("\n => Choix : ");
        lire(verichar, 5);
        if (chaine_vide(verichar)==1) {choix1 = -2;}
        else choix1 = verif_integer(verichar);

        fflush(stdin);

        if(choix1==1){

            system("cls");

            printf("\n\n Affichage d'une classe :");
            printf("\n ------------------------");

            id=choix_classe(tableau,nbClasses);

            printf("\n\n Liste des %cttudiants de la classe :",130);
            printf("\n -------------------------------------\n");

            if(tableau[id].nbEtu==0){printf("\n => Il l'y a pas d'%ctudiant dans cette classe !",130);}

            printf("\n Mat.    ");
            printf(" Nom          ");
            printf(" Pr%cnom       ",130);
            printf("Date n.  ");
            printf("   Moyenne pond%cr%ce et g%cn%crale",130,130,130,130);
            printf("\n");

            for(i=0;i<tableau[id].nbEtu;i++){

                moyenne=calcul_moyenne(tabcours,tableau[id].liste[i].cotes,tableau[id].nbCours,&total_ects);

                printf("\n %-8s %-13s %-12s",tableau[id].liste[i].matricule,tableau[id].liste[i].nom,tableau[id].liste[i].prenom);
                printf(" %2d/%2d/%4d",tableau[id].liste[i].ddn.jour,tableau[id].liste[i].ddn.mois,tableau[id].liste[i].ddn.annee);

                if(moyenne==-1){
                    printf("  -----",130);
                }
                else{
                    printf("  %5.2f (%4.1f ECTS)",moyenne,total_ects);

                    if((moyenne>=60)&&(total_ects==60)){printf(" => R  ");}
                    else{
                        if((moyenne>=60)&&(total_ects>=48)){printf(" => RCR");}
                        else{printf(" => E  ");}
                    }

                    moyenne=calcul_moyenne_tout(tabcours,tableau[id].liste[i].cotes,tableau[id].nbCours,&total_ects);
                    printf(" %5.2f",moyenne);

                }
            }

            printf("\n\n Voulez-vous cr%cer un fichier texte :",130);
            printf("\n\n  1. OUI");
            printf("\n  0. NON");
            choix2 = -2;
            while ((choix2 !=0) && (choix2 != 1)) {

                printf("\n\n Choix : ");
                lire(verichar, 5);
                if (chaine_vide(verichar) == 1) {choix2 = -2;}
                else choix2 = verif_integer(verichar);
                fflush(stdin);

                if(choix2==1){
                    creation_texte(tableau[id].annee,tableau[id].section,tableau,id,tabcours,tableau[id].nbCours);
                    choix1=0;}

                if ((choix2 !=0) && (choix2 != 1)) {

                    printf("\n Erreur. Le choix entr%c est incorrect.", 130);
                    printf("\n Veuillez recommencer. (1 = Oui, 0 = Non)");

                }
            }
        }
        if ((choix1 !=0) && (choix1 != 1)) {

            printf("\n Erreur. Le choix entr%c est incorrect.", 130);
            printf("\n Veuillez recommencer. (1 = Afficher, 0 = Quitter)");

        }

    }
}
