#include "classe.h"
// Fonction pour initialiser une liste d'ID
ListeID *initListeID() {
    return NULL;
}

Environnement *initListeENV() {
    return NULL;
}

// Fonction pour ajouter un ID à une liste d'ID
ListeID *ajouterID(ListeID *liste, int ID, int temps) {
    ListeID *nouveau = malloc(sizeof(ListeID));
    if (nouveau == NULL) {
        fprintf(stderr, "Erreur : allocation mémoire échouée\n");
        exit(EXIT_FAILURE);
    }
    nouveau->ID = ID;
    nouveau->temps = temps;
    nouveau->suivant = NULL;
    if (liste == NULL) {
        return nouveau;
    } else {
        ListeID *temp = liste;
        while (temp->suivant != NULL) {
            temp = temp->suivant;
        }
        temp->suivant = nouveau;
        return liste;
    }
}
// fonction qui permet d'aggrandir notre environnement, il permettra la conversion ID élément
Environnement *agrandir_env(Environnement *env, Donnee *data, NoeudSysteme *ns, Utilisateur *user){
    Environnement *nouveau = malloc(sizeof(Environnement));
    if (nouveau == NULL) {
        fprintf(stderr, "Erreur : allocation mémoire échouée\n");
        exit(EXIT_FAILURE);
    }
    int ID;
    if (data)
    {
        ID = data->ID;
    }
    if (ns){
        ID = ns->ID;
    }
    if (user){
        ID = user->ID;
    }
    nouveau->data = data;
    nouveau->ns = ns;
    nouveau->user = user;
    nouveau->ID = ID;
    if (env == NULL)
    {
        return nouveau;
    }
    else
    {
        Environnement *temp = env;
        while (temp->suivant != NULL) {
            temp = temp->suivant;
        }
        temp->suivant = nouveau;
        return env;
    }
}
Donnee *get_data_ID(Environnement *env, int ID){
    while (env->ID != ID)
    {
        env = env->suivant;
    }
    return (env->data);
}
Utilisateur *get_user_ID(Environnement *env, int ID){
    while(env->ID != ID){
        env = env->suivant;
    }
    return (env->user);
}
NoeudSysteme *get_ns_ID(Environnement *env, int ID){
    while(env->ID != ID){
        env = env->suivant;
    }
    return (env->ns);
}
int capacite_restant(NoeudSysteme *ns, Environnement *env){
    ListeID *temp = ns->donnees_stockees;
    if (temp == NULL){
        return (ns->capacite_memoire);
    }
    Donnee *d = get_data_ID(env, temp->ID);
    int somme_data = d->taille;
    while (temp->suivant != NULL){
        d = get_data_ID(env, temp->ID);
        somme_data = somme_data + d->taille;
        temp = temp->suivant;
    }
    return (ns->capacite_memoire - somme_data);
}