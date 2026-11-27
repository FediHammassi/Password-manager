#ifndef PROJECT_H
#define PROJECT_H

#define MAX_COMPTES 100
#define TAILLE_CHAINE 100
#define CLE_CESAR 3

typedef struct {
    int num;
    char site[TAILLE_CHAINE];
    char identifiant[TAILLE_CHAINE];
    char mot_de_passe[TAILLE_CHAINE];
    char date_creation[11];
    char date_modification[11];
    char niveau_robustesse[15];
} Compte;



void afficherMenuPrincipal(void);
void gerer_compte(Compte coffre[], int *nb_comptes);


Compte creer_compte(int num);
void ajouter_compte(Compte coffre[], int *nb_comptes);
void modifier_compte(Compte coffre[], int nb_comptes);
void supprimer_compte(Compte coffre[], int *nb_comptes);
void afficher_comptes(Compte coffre[], int nb_comptes);
void afficher_mot_de_passe(Compte coffre[], int nb_comptes);


void generer_mot_de_passe(Compte coffre[], int *nb_comptes);
void chiffrer_cesar(char pwd[], int dec);
void dechiffrer_cesar(char pwd[], int dec);
void chiffrer_xor(void);
void dechiffrer_xor(void);
int evaluer_robustesse(char pwd[], char *niveau, int afficher);
void rechercher_compte(Compte coffre[], int nb_comptes);
void auditer_coffre(void);
void sauvegarder_donnees(void);
void charger_donnees(void);

void definir_mot_de_passe_maitre(char maitre[]);
int verifier_mot_de_passe_maitre(const char maitre[]);


#endif
