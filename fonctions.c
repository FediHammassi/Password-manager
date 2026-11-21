#include <stdio.h>
#include "headers/project.h"

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
    printf("Niveau de robustesse : ");
    scanf(" %10[^\n]", c.niveau_robustesse);

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
                afficher_mot_de_passe();
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
    int rep=0;

    do {
        printf("Votre choix : \n");
        if (scanf("%d", &choix) != 1) {
            printf("Saisie invalide.\n");
            while (getchar() != '\n');
            continue;
        }
        switch (choix){
        case 1:
            printf("Saisir l'identifiant a rechercher");
            scanf(" %99[^\n]", terme);
            printf("\n--- RESULTATS DE LA RECHERCHE ---\n");
            printf("%-4s | %-20s | %-20s | %-12s | %-12s\n",
                   "Num", "Site", "Identifiant", "Mot de passe", "Modifie le");
            printf("----------------------------------------------------------------------------\n");
            for (int i=0;i<nb_comptes;i++){
                if(strstr(coffre[i].identifiant,choix)!=NULL){
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
            printf("Saisir le site ou service a rechercher");
            scanf(" %99[^\n]", terme);
            printf("\n--- RESULTATS DE LA RECHERCHE ---\n");
            printf("%-4s | %-20s | %-20s | %-12s | %-12s\n",
                   "Num", "Site", "Identifiant", "Mot de passe", "Modifie le");
            printf("----------------------------------------------------------------------------\n");
            for (int i=0;i<nb_comptes;i++){
                if(strstr(coffre[i].site,choix)!=NULL){
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


void afficher_mot_de_passe(void) {}
void generer_mot_de_passe(void) {}
void chiffrer_cesar(void) {}
void dechiffrer_cesar(void) {}
void chiffrer_xor(void) {}
void dechiffrer_xor(void) {}
void evaluer_robustesse(void) {}

void auditer_coffre(void) {}
void sauvegarder_donnees(void) {}
void charger_donnees(void) {}
