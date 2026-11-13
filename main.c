#include <stdio.h>

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

void gerer_compte(){
}
void creer_compte(){}
void ajouter_compte(){}
void modifier_compte(){}
void supprimer_compte(){} 
void afficher_comptes(){}
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
    afficherMenuPrincipal();
    printf("saisir votre choix : ");
    int choix;
    do {
        scanf("%d", &choix);
        switch (choix)
        {
        case 1:
            printf("\n--- Gerer les comptes ---\n\n");

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
