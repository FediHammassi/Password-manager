#include <stdio.h>
#include "headers/project.h"
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

int main(void) {
    int nb_comptes = 0;
    Compte coffre[MAX_COMPTES];
    int choix;
    srand((unsigned int)time(NULL));

    do {
        afficherMenuPrincipal();
        printf("Saisir votre choix : ");

        if (scanf("%d", &choix) != 1) {
            printf("Saisie invalide.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choix) {
            case 1:
                printf("\n--- Gerer les comptes ---\n\n");
                gerer_compte(coffre, &nb_comptes);
                break;
            case 2:
                printf("\n--- Generer un mot de passe ---\n\n");
                generer_mot_de_passe(coffre, &nb_comptes);
                break;
            case 3: {
            char mdp_test[TAILLE_CHAINE];
            char niveau[20];
            printf("\n--- Evaluer la robustesse d'un mot de passe ---\n");
            printf("Saisir le mot de passe a evaluer : ");
            scanf(" %99[^\n]", mdp_test);
            evaluer_robustesse(mdp_test, niveau, 1);
            break;
            }
            case 4:
                printf("\n--- Rechercher un compte ---\n\n");
                rechercher_compte(coffre, nb_comptes);
                break;
            case 5:
                printf("\n--- Audit de securite ---\n\n");
                break;
            case 6:
                printf("\n--- Fermeture du gestionnaire de mots de passe ---\n\n");
                break;
            default:
                printf("Saisie invalide.\n");
                break;
        }
    } while (choix != 6);

    return 0;
}
