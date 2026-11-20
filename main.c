#include <stdio.h>

#define COMPTE_H
#define MAX_COMPTES 100
#define TAILLE_CHAINE 100

typedef struct{
    int num;
    char site[TAILLE_CHAINE];
    char identifiant[TAILLE_CHAINE];
    char mot_de_passe[TAILLE_CHAINE];
    char date_creation[11];
    char date_modification[11];
    char niveau_robustesse[11];
} Compte;

void afficher_mot_de_passe(void);

void afficherMenuPrincipal(){
    printf("=========================================\n");
    printf("      GESTIONNAIRE DE MOTS DE PASSE      \n");
    printf("=========================================\n");
    printf("1. Gérer les comptes \n");
    printf("2. Generer un mot de passe\n");
    printf("3. Evaluer la robustesse d'un mot de passe\n");
    printf("4. Rechercher un compte\n");
    printf("5. Audit de securite\n");
    printf("6. Quitter\n");
    printf("=========================================\n\n");
}

Compte creer_compte(int num){
    Compte c;
    c.num=num;

    printf("Site ou service : ");
    scanf(" %99[^\n]", c.site);
    printf("identifiant : ");
    scanf(" %99[^\n]", c.identifiant);
    printf("mot_de_passe : ");
    scanf(" %99[^\n]", c.mot_de_passe);
    printf("date_modification : ");
    scanf(" %10[^\n]", c.date_modification);
    printf("date_creation : ");
    scanf(" %10[^\n]", c.date_creation);
    printf("niveau_robustesse : ");
    scanf(" %10[^\n]", c.niveau_robustesse);

    return c;
}

void ajouter_compte(Compte coffre[], int *nb_comptes){
    int curr_num;
    if (*nb_comptes == 0) curr_num=1;
    else curr_num+=coffre[*nb_comptes-1].num;
    (*nb_comptes)++;
    coffre[*nb_comptes]=creer_compte(curr_num);
}

void modifier_compte(Compte coffre[], int nb_comptes){
    if (nb_comptes==0) {
        printf("pas de compte a modifier");
        return;
    }
    int target_num;
    printf("saisir le numéro du compte a modifier");
    scanf("%d",&target_num);
        for (int i = 0; i < nb_comptes; i++){
            if (target_num==coffre[i].num){
                printf("Nouveau Site ou Service : ");
                scanf(" %99[^\n]", coffre[i].site);
                printf("Nouvel identifiant : ");
                scanf(" %99[^\n]", coffre[i].identifiant);
                printf("Nouveau mot de passe : ");
                scanf(" %99[^\n]", coffre[i].mot_de_passe);
                printf("Date actuelle");
                scanf(" %10[^\n]");
                printf("Compte modifié avec succés! \n");
                return;
            }
        }
        printf("Numéro inexistant");  
}

void supprimer_compte(Compte coffre[],int *nb_comptes){
    if (*nb_comptes==0){
        printf ("y'a pas de comptes a supprimer");
        return;
    }
    int n;
    printf("saisir le num du compte a supprimer");
    scanf("%d",&n);
    for (int i=0;i<*nb_comptes;i++){
        if (coffre[i].num==n){
            for (int j = i; j < *nb_comptes - 1; j++) {
                coffre[j] = coffre[j + 1];
            }
            (*nb_comptes)--;
            printf("compte supprimé avec succés");
            return;
        }
    }
    printf("Il n'existe aucun compte avec ce numero");
}


void afficher_comptes(Compte coffre[], int nb_comptes){
    if (nb_comptes == 0) {
        printf("Aucun compte enregistre dans le coffre\n");
        return;
    }
    printf("--- LISTE DES COMPTES---");
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

void gerer_compte(Compte coffre[],int *nb_comptes){
    printf("1.Ajouter un nouveau compte\n");
    printf("2.Modifier les informations d’un compte\n");
    printf("3.Supprimer un compte\n");
    printf("4.Afficher la liste des comptes\n");
    printf("5.Afficher le mot de passe d’un compte\n");
    printf("0.Retour\n");

    int choice;
    do{
        printf("saisir votre choix");
        scanf("%d",&choice);
        switch (choice)
        {
        case 1 :
            ajouter_compte(coffre, nb_comptes);
            break;
        case 2 :
            modifier_compte(coffre, *nb_comptes);
            break;
        case 3 :
            supprimer_compte(coffre, nb_comptes);
            break;
        case 4 :
            afficher_comptes(coffre, *nb_comptes);
            break;
        case 5 :
            afficher_mot_de_passe();
            break;
        case 0 :
            printf("---Retour---");
            break;
        default:
            printf("saisi invalide");
            break;
        }
    } while (choice!=0);
}





void afficher_mot_de_passe(){}
void generer_mot_de_passe(){
}

void chiffrer_cesar(){} 
void dechiffrer_cesar(){}
void chiffrer_xor(){}
void dechiffrer_xor(){
}

void evaluer_robustesse(){
}

void rechercher_compte(){
}

void auditer_coffre(){
}

void sauvegarder_donnees(){}
void charger_donnees(){}


int main(){
    int nb_comptes=0;
    Compte coffre[MAX_COMPTES];
    
    int choix;
    do {
        afficherMenuPrincipal();
        printf("saisir votre choix : ");

        scanf("%d", &choix);
        switch (choix)
        {
        case 1:
            printf("\n--- Gerer les comptes ---\n\n");
            gerer_compte(coffre, &nb_comptes);

            break;
        case 2:
            printf("\n--- Generer un mot de passe ---\n\n");

            break;
        case 3:
            printf("\n--- Evaluer la robustesse d'un mot de passe ---\n\n");

            break;
        case 4:
            printf("\n--- Rechercher un compte ---\n\n");

            break;
        case 5:
            printf("\n--- Audit de securite ---\n\n");

            break;
        case 6:
            printf("\n--- Fermeture du gestionnaire de mots de passe ---\n\n");

            break;
        default:
            printf("saisi invalide");
            break;
        }
    } while (choix != 6);
    return 0;
}
