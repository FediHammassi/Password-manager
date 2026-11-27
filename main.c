#include <stdio.h>
#include "headers/project.h"
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

int main(void) {
    int nb_comptes ;
    Compte coffre[MAX_COMPTES];
    int choix;
    srand((unsigned int)time(NULL));
    
    /*
    Compte prototypes[5] = {
        {1, "Facebook", "yassine.dev@gmail.com", "password111", "10/11/2026", "10/11/2026", ""},
        {2, "Spotify", "yassine_music", "Musiq123", "12/11/2026", "15/11/2026", ""},
        {3, "Google Mail", "yassine.dev@gmail.com", "MonCompteGma2026", "14/11/2026", "20/11/2026", ""},
        {4, "GitHub", "yassine-git", "K9#mP2$vL8@xQ4!zR", "18/11/2026", "25/11/2026", ""},
        {5, "Google Drive", "pro.contact@univ.tn", "Driv@Stock_9874", "21/11/2026", "27/11/2026", ""}
    };
    for (int i = 0; i < 5; i++) {
        evaluer_robustesse(prototypes[i].mot_de_passe, prototypes[i].niveau_robustesse, 0);
        chiffrer_cesar(prototypes[i].mot_de_passe, CLE_CESAR);
        coffre[i] = prototypes[i];
    }
    nb_comptes = 5;
    */
    char maitre[TAILLE_CHAINE];
    definir_mot_de_passe_maitre(maitre);
    if (!verifier_mot_de_passe_maitre(maitre)) {
        return 0;
    }
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
                printf("\n--- Gerer les comptes ---\n");
                gerer_compte(coffre, &nb_comptes);
                break;
            case 2:
                printf("\n--- Generer un mot de passe ---\n");
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
                printf("\n--- Rechercher un compte ---\n");
                rechercher_compte(coffre, nb_comptes);
                break;
            case 5:
                printf("\n--- Audit de securite ---\n");
                break;
            case 6:
                printf("\n--- Fermeture du gestionnaire de mots de passe ---\n");
                break;
            default:
                printf("Saisie invalide.\n");
                break;
        }
    } while (choix != 6);

    return 0;
}
