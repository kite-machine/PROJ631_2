#define CLASSE_H

struct element_voisin {
    syst_node syst_node;
    double temps;
    struct element_voisin *suivant;
};
typedef struct element_voisin element_voisin;

struct liste_voisin
{
    element_voisin *tete
};
typedef struct liste_voisin liste_sn;

struct element_data {
    data data;
    struct element *suivant;
};
typedef struct element_data element_data;

struct liste_data
{
    element_data *tete
};
typedef struct liste_data liste_data;

struct donnee {
    double taille;
};
typedef struct donnee data;

struct utilisateur {
    liste_data donnees;
    syst_node syst_node;
    double temps;
};
typedef struct utilisateur user;

struct noeud_systeme {
    double capacite;
    liste_data donnees;
    liste_sn voisins;
};
typedef struct noeud_systeme syst_node;

void init_liste_data(liste_data* l);

int ajouter_queue_data(liste_data* l,data d);

void init_liste_sn(liste_sn* l);

int ajouter_queue_sn(liste_sn* l,syst_node sn, double temps);

void add_acces(syst_node *sn,double id,double temps);