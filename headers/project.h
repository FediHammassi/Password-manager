#define PROJECT_H

#define MAX_COMPTES 100
#define TAILLE_CHAINE 100

typedef struct {
    int num;
    char site[TAILLE_CHAINE];
    char identifiant[TAILLE_CHAINE];
    char mot_de_passe[TAILLE_CHAINE];
    char date_creation[11];
    char date_modification[11];
    char niveau_robustesse[11];
} Compte;


void afficherMenuPrincipal(void);
void gerer_compte(Compte coffre[], int *nb_comptes);


Compte creer_compte(int num);
void ajouter_compte(Compte coffre[], int *nb_comptes);
void modifier_compte(Compte coffre[], int nb_comptes);
void supprimer_compte(Compte coffre[], int *nb_comptes);
void afficher_comptes(Compte coffre[], int nb_comptes);
void afficher_mot_de_passe(void);


void generer_mot_de_passe(void);
void chiffrer_cesar(void);
void dechiffrer_cesar(void);
void chiffrer_xor(void);
void dechiffrer_xor(void);
void evaluer_robustesse(void);
void rechercher_compte(void);
void auditer_coffre(void);
void sauvegarder_donnees(void);
void charger_donnees(void);

