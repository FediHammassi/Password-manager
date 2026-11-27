#include <stdio.h>
#include "headers/project.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void afficherMenuPrincipal(void) {
    printf("\n=========================================\n");
    printf("      GESTIONNAIRE DE MOTS DE PASSE      \n");
    printf("=========================================\n");
    printf("1. Gerer les comptes \n");
    printf("2. Generer un mot de passe\n");
    printf("3. Evaluer la robustesse d'un mot de passe\n");
    printf("4. Rechercher un compte\n");
    printf("5. Audit de securite\n");
    printf("6. Quitter\n");
    printf("=========================================\n\n");
}

Compte creer_compte(int num) {
    Compte c;
    c.num = num;

    printf("Site ou service : ");
    scanf(" %99[^\n]", c.site);
    printf("Identifiant : ");
    scanf(" %99[^\n]", c.identifiant);
    printf("Mot de passe : ");
    scanf(" %99[^\n]", c.mot_de_passe);
    printf("Date de creation (JJ/MM/AAAA) : ");
    scanf(" %10[^\n]", c.date_creation);
    printf("Date de modification (JJ/MM/AAAA) : ");
    scanf(" %10[^\n]", c.date_modification);
    evaluer_robustesse(c.mot_de_passe, c.niveau_robustesse, 0);
    chiffrer_cesar(c.mot_de_passe, CLE_CESAR);

    return c;
}

void ajouter_compte(Compte coffre[], int *nb_comptes) {
    if (*nb_comptes >= MAX_COMPTES) {
        printf("Le coffre est plein.\n");
        return;
    }

    int curr_num;
    if (*nb_comptes == 0) {
        curr_num = 1;
    } else {
        curr_num = coffre[*nb_comptes - 1].num + 1;
    }

    coffre[*nb_comptes] = creer_compte(curr_num);
    (*nb_comptes)++;
    printf("Compte ajoute avec succes !\n");
}

void modifier_compte(Compte coffre[], int nb_comptes) {
    if (nb_comptes == 0) {
        printf("Pas de compte a modifier.\n");
        return;
    }

    int target_num;
    printf("Saisir le numero du compte a modifier : ");
    scanf("%d", &target_num);

    for (int i = 0; i < nb_comptes; i++) {
        if (target_num == coffre[i].num) {
            printf("Nouveau Site ou Service : ");
            scanf(" %99[^\n]", coffre[i].site);
            printf("Nouvel identifiant : ");
            scanf(" %99[^\n]", coffre[i].identifiant);
            printf("Nouveau mot de passe : ");
            scanf(" %99[^\n]", coffre[i].mot_de_passe);
            printf("Date actuelle (JJ/MM/AAAA) : ");
            scanf(" %10[^\n]", coffre[i].date_modification);
            evaluer_robustesse(coffre[i].mot_de_passe, coffre[i].niveau_robustesse, 0);
            chiffrer_cesar(coffre[i].mot_de_passe, CLE_CESAR);
            printf("Compte modifie avec succes !\n");
            return;
        }
    }
    printf("Numero inexistant.\n");
}

void supprimer_compte(Compte coffre[], int *nb_comptes) {
    if (*nb_comptes == 0) {
        printf("Il n'y a pas de comptes a supprimer.\n");
        return;
    }

    int n;
    printf("Saisir le num du compte a supprimer : ");
    scanf("%d", &n);

    for (int i = 0; i < *nb_comptes; i++) {
        if (coffre[i].num == n) {
            for (int j = i; j < *nb_comptes - 1; j++) {
                coffre[j] = coffre[j + 1];
            }
            (*nb_comptes)--;
            printf("Compte supprime avec succes.\n");
            return;
        }
    }
    printf("Il n'existe aucun compte avec ce numero.\n");
}

void afficher_comptes(Compte coffre[], int nb_comptes) {
    if (nb_comptes == 0) {
        printf("Aucun compte enregistre dans le coffre.\n");
        return;
    }

    printf("\n--- LISTE DES COMPTES ---\n");
    printf("%-4s | %-20s | %-20s | %-12s | %-12s\n",
           "Num", "Site", "Identifiant", "Mot de passe", "Modifie le");
    printf("----------------------------------------------------------------------------\n");
    for (int i = 0; i < nb_comptes; i++) {
        printf("%-4d | %-20s | %-20s | %-12s | %-12s\n",
               coffre[i].num,
               coffre[i].site,
               coffre[i].identifiant,
               "********",
               coffre[i].date_modification);
    }
    printf("----------------------------------------------------------------------------\n");
}

void gerer_compte(Compte coffre[], int *nb_comptes) {
    int choice;
    do {
        printf("\n1. Ajouter un nouveau compte\n");
        printf("2. Modifier les informations d'un compte\n");
        printf("3. Supprimer un compte\n");
        printf("4. Afficher la liste des comptes\n");
        printf("5. Afficher le mot de passe d'un compte\n");
        printf("0. Retour\n");
        printf("Saisir votre choix : ");

        if (scanf("%d", &choice) != 1) {
            printf("Saisie invalide.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1:
                ajouter_compte(coffre, nb_comptes);
                break;
            case 2:
                modifier_compte(coffre, *nb_comptes);
                break;
            case 3:
                supprimer_compte(coffre, nb_comptes);
                break;
            case 4:
                afficher_comptes(coffre, *nb_comptes);
                break;
            case 5:
                afficher_mot_de_passe(coffre,*nb_comptes);
                break;
            case 0:
                printf("--- Retour ---\n");
                break;
            default:
                printf("Saisie invalide.\n");
                break;
        }
    } while (choice != 0);
}

void rechercher_compte(Compte coffre[], int nb_comptes) {
    if (nb_comptes==0) {
        printf("Pas de comptes à chercher");
        return;
    }
    printf("Veuillez choisir le mode de recherche: \n");
    printf("1. Par identifiant\n");
    printf("2. Par Site ou service\n");
    printf("0. Quitter\n");
    
    int choix;
    char terme[TAILLE_CHAINE];
    int rep;

    do {
        printf("Votre choix : \n");
        if (scanf("%d", &choix) != 1) {
            printf("Saisie invalide.\n");
            while (getchar() != '\n');
            continue;
        }
        switch (choix){
        case 1:
            printf("Saisir l'identifiant a rechercher : ");
            scanf(" %99[^\n]", terme);
            printf("\n--- RESULTATS DE LA RECHERCHE ---\n");
            printf("%-4s | %-20s | %-20s | %-12s | %-12s\n",
                   "Num", "Site", "Identifiant", "Mot de passe", "Modifie le");
            printf("----------------------------------------------------------------------------\n");
            rep=0;
            for (int i=0;i<nb_comptes;i++){
                if(strstr(coffre[i].identifiant,terme)!=NULL){
                    printf("%-4d | %-20s | %-20s | %-12s | %-12s\n",
                           coffre[i].num,coffre[i].site,coffre[i].identifiant,
                           "********", coffre[i].date_modification);
                    rep++;
                }
            }
            if (rep==0){
                printf("Aucun compte ne avec cet identifiant\n");
            }
            printf("----------------------------------------------------------------------------\n");
            break;
        case 2:
            printf("Saisir le site ou service a rechercher : ");
            scanf(" %99[^\n]", terme);
            printf("\n--- RESULTATS DE LA RECHERCHE ---\n");
            printf("%-4s | %-20s | %-20s | %-12s | %-12s\n",
                   "Num", "Site", "Identifiant", "Mot de passe", "Modifie le");
            printf("----------------------------------------------------------------------------\n");
            rep=0;
            for (int i=0;i<nb_comptes;i++){
                if(strstr(coffre[i].site,terme)!=NULL){
                    printf("%-4d | %-20s | %-20s | %-12s | %-12s\n",
                           coffre[i].num,coffre[i].site,coffre[i].identifiant,
                           "********", coffre[i].date_modification);
                    rep++;
                }
            }
            if (rep==0){
                printf("Aucun compte ne avec ce site\n");
            }
            printf("----------------------------------------------------------------------------\n");
            break;
        case 0:
            printf("---Retour au menu principal---\n");
            break;
        default:
            printf("Saisie Invalide\n");
            break;
        }
    } while (choix!=0);
}

void chiffrer_cesar(char pwd[], int dec) {
    for (int i = 0; pwd[i]!='\0'; i++) {
        if (pwd[i]>=33 && pwd[i]<=126) {
            pwd[i]=33+(pwd[i]-33+dec)%94;
        }
    }
}

void dechiffrer_cesar(char pwd[], int dec) {
    for (int i = 0; pwd[i]!='\0'; i++) {
        if (pwd[i] >= 33 && pwd[i] <= 126) {
            pwd[i] = 33 + (pwd[i] - 33 - (dec % 94) + 94) % 94;
        }
    }
}

int evaluer_robustesse(char pwd[], char niveau[], int afficher) {
    /* Niveau de robustesse: score 0 - 100
    0-30   faible
    31-60  moyen
    61-80  fort
    81-100 très fort 
    ---
    ==Formule==
    Longueur                         : 40 pts
    Variété de types                 : 40 pts
    Pas de répitions et seq generique: 20 pts
    Existance mots courants          :-50 pts
    */

    int score=0, maj=0, min=0, chiff=0, symb=0, inter=0, rep=1, seq=1;
    int len=strlen(pwd);
    const char *interdits[] = {"password", "azerty",
    "qwerty", "12345678", "admin", "00000000"};
    size_t len_inter = sizeof(interdits) / sizeof(interdits[0]);

    if (24<len) score+=40;
    else if (16<len) score+=30;
    else if (12<len) score+=20;
    else score+=10;

    for (int i=0; i<len; i++){
        if (isupper((unsigned char)pwd[i])) maj=1;
        else if (islower((unsigned char)pwd[i])) min=1;
        else if (isdigit((unsigned char)pwd[i])) chiff=1;
        else symb=1;
    }
    
    for (int i=0; i<len-2;i++){
        if (pwd[i]==pwd[i+1] && pwd[i]==pwd[i+2]) rep=0;
        if (pwd[i+1]==pwd[i]+1 && pwd[i+2]==pwd[i]+2) seq=0;
    }

    score+=(maj+min+chiff+symb+rep+seq)*10;

    for (int i=0; i<len_inter; i++){
        if (strstr(pwd,interdits[i])!=NULL){
            inter=1;
            break;
        }
    }
    if (inter) score-=50;

    if (score<0) score=0;

    if(80<score) strcpy(niveau,"Très fort");
    else if (60<score) strcpy(niveau,"Fort");
    else if (30<score) strcpy(niveau,"Moyen");
    else strcpy(niveau,"Faible");

    if(afficher){
        printf("----------------------------------------------------------------------------\n");
        printf("Score : %d/100 | Niveau : %s\n", score, niveau);
        printf("---Connseils pour améliorer le niveau de robustesse---\n");
        if (len<12) printf("Utiliser un mot de passe plus long\n");
        if (!maj) printf("Ajoutez des lettres majuscules\n");
        if (!min) printf("Ajoutez des lettres minuscules\n");
        if (!chiff) printf("Ajoutez des chiffres\n");
        if (!symb) printf("Ajoutez des caracteres speciaux (ex: !@#$...)\n");
        if (!rep) printf("Evitez les caracteres identiques consecutifs (ex: aaa)\n");
        if (!seq) printf("Evitez les suites logiques (ex: 123, abc)\n");
        if (inter) printf("Ne pas utiliser des mots de passe courants (ex: 00000000)\n");
        printf("----------------------------------------------------------------------------\n");

    }
    return score;
}


void generer_mot_de_passe(Compte coffre[], int *nb_comptes) {
    int len, min, maj, chiff, symb, base_len, ok;
    char pwd[33];
    char base[100]="";
    do{
        printf("Saisir la longueur du mdp : ");
        scanf("%d", &len);
    } while (len<8 || len>32);

    do
    {
        printf("Inclure des majuscules? (1=OUI, 2=NON) : ");
        scanf("%d", &maj);
        printf("Inclure des miniscules? (1=OUI, 2=NON) : ");
        scanf("%d", &min);
        printf("Inclure des chiffres?   (1=OUI, 2=NON) : ");
        scanf("%d", &chiff);
        printf("Inclure des symboles?   (1=OUI, 2=NON) : ");
        scanf("%d", &symb);
        ok = (maj==1)+(min==1)+(chiff==1)+(symb==1);
        if (!ok) printf("Il faut choisir au moins un de ces types");
    } while (!ok);
    
    if (maj==1) strcat(base, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    if (min==1) strcat(base, "abcdefghijklmnopqrstuvwxyz");
    if (chiff==1) strcat(base, "0123456789");
    if (symb==1) strcat(base, "!@#$%^&*()-_=+[]{}?");

    base_len=strlen(base);
    for (int i=0; i<len; i++){
        pwd[i]=base[rand() % base_len];
    }
    pwd[len] = '\0';

    printf("Mot de passe géneré : %s\n", pwd);
    char niveau[15];
    evaluer_robustesse(pwd, niveau, 1);

    int save;
    printf("Enregistrer dans un compte? ( 1=OUI, 2=NON ) : ");
    scanf("%d", &save);

    if (save==1){
        if (*nb_comptes >= MAX_COMPTES) {
            printf("Le coffre est plein\n");
            return;
        }
        Compte c;
        if (*nb_comptes==0) c.num=1;
        else c.num=coffre[*nb_comptes-1].num+1;

        printf("Site ou service : ");
        scanf(" %99[^\n]", c.site);
        printf("Identifiant : ");
        scanf(" %99[^\n]", c.identifiant);
        printf("Date du jour (JJ/MM/AAAA) : ");
        scanf(" %10[^\n]", c.date_creation);
        strcpy(c.date_modification, c.date_creation);
        strcpy(c.niveau_robustesse, niveau);

        strcpy(c.mot_de_passe, pwd);
        chiffrer_cesar(c.mot_de_passe, CLE_CESAR);

        coffre[*nb_comptes] = c;
        (*nb_comptes)++;
        printf("Compte enregistre avec succes !\n");
    }
}

void afficher_mot_de_passe(Compte coffre[], int nb_comptes) {
    if (nb_comptes==0) {
        printf("Aucun compte enregistre dans le coffre.\n");
        return;
    }

    int target_num;
    printf("Saisir le numero du compte : ");
    if (scanf("%d", &target_num) !=1) {
        printf("Saisie invalide.\n");
        while (getchar() !='\n');
        return;
    }

    for (int i = 0; i < nb_comptes; i++) {
        if (coffre[i].num == target_num) {
            char mdp_clair[TAILLE_CHAINE];
            strcpy(mdp_clair, coffre[i].mot_de_passe);
            dechiffrer_cesar(mdp_clair, CLE_CESAR);

            printf("\nSite : %s | Identifiant : %s\n", coffre[i].site, coffre[i].identifiant);
            printf("Mot de passe : %s (Robustesse : %s)\n", mdp_clair, coffre[i].niveau_robustesse);
            return;
        }
    }
    printf("Aucun compte trouve avec ce numero.\n");
}

void definir_mot_de_passe_maitre(char maitre[]) {
    char niveau[20];
    printf("=== INITIALISATION DU COFFRE ===\n");
    printf("Definissez votre mot de passe maitre : ");
    scanf(" %99[^\n]", maitre);

    evaluer_robustesse(maitre, niveau, 0);
    printf("Mot de passe maitre enregistre (Robustesse : %s).\n", niveau);

    chiffrer_cesar(maitre, CLE_CESAR);
}

int verifier_mot_de_passe_maitre(const char maitre[]) {
    char saisie[TAILLE_CHAINE];
    char maitre_clair[TAILLE_CHAINE];
    int essais = 3;

    strcpy(maitre_clair, maitre);
    dechiffrer_cesar(maitre_clair, CLE_CESAR);

    while (essais > 0) {
        printf("\nEntrez le mot de passe maitre (%d essai(s) restant(s)) : ", essais);
        scanf(" %99[^\n]", saisie);

        if (strcmp(saisie, maitre_clair) == 0) {
            printf("Acces autorise !\n");
            return 1;
        }

        essais--;
        printf("Mot de passe incorrect.\n");
    }

    printf("Nombre maximal de tentatives atteint. Fermeture du programme.\n");
    return 0;
}

void chiffrer_xor(void) {}
void dechiffrer_xor(void) {}

void auditer_coffre(void) {}
void sauvegarder_donnees(void) {}
void charger_donnees(void) {}
