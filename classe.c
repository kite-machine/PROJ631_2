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
bool ID_not_in(ListeID *liste, int ID) {
    while (liste != NULL) {
        if (liste->ID == ID) {
            return false; // L'ID est présent dans la liste
        }
        liste = liste->suivant;
    }
    return true; // L'ID n'est pas présent dans la liste
}

// Fonction pour initialiser une file vide
File* initFile() {
    File *file = malloc(sizeof(File));
    if (file == NULL) {
        fprintf(stderr, "Erreur : allocation mémoire échouée\n");
        exit(EXIT_FAILURE);
    }
    file->debut = NULL;
    file->fin = NULL;
    return file;
}

// Fonction pour enfiler un élément dans la file
File* enfiler(File *file, int valeur) {
    FileElement *nouveau = malloc(sizeof(FileElement));
    if (nouveau == NULL) {
        fprintf(stderr, "Erreur : allocation mémoire échouée\n");
        exit(EXIT_FAILURE);
    }
    nouveau->data = valeur;
    nouveau->suivant = NULL;
    if (file->fin == NULL) {
        file->debut = nouveau;
        file->fin = nouveau;
    } else {
        file->fin->suivant = nouveau;
        file->fin = nouveau;
    }
    return file;
}

// Fonction pour défiler un élément de la file
int defiler(File *file) {
    if (file->debut == NULL) {
        fprintf(stderr, "Erreur : la file est vide\n");
        exit(EXIT_FAILURE);
    }
    FileElement *temp = file->debut;
    int valeur = temp->data;
    file->debut = temp->suivant;
    if (file->debut == NULL) {
        file->fin = NULL;
    }
    free(temp);
    return valeur;
}

// Fonction pour vérifier si la file est vide
bool file_est_vide(File *file) {
    return (file->debut == NULL);
}
// Fonction pour insérer une donnée dans l'environnement
int inserer_donnee(Environnement *env) {
    Environnement *temp = env;

    // Parcours de l'environnement
    while (temp != NULL) {
        if (temp->user != NULL) {
            // Récupération de la liste des données à placer pour cet utilisateur
            ListeID *donnee_a_placer = temp->user->donnees_interet;

            // Parcours de la liste des données à placer
            while (donnee_a_placer != NULL) {
                Donnee *data = get_data_ID(env, donnee_a_placer->ID);

                // Création de la liste des nœuds déjà parcourus pour éviter les cycles
                ListeID *ns_parcourus = initListeID();

                // File pour le parcours en largeur des nœuds accessibles
                File *file_noeuds = initFile();
                file_noeuds = enfiler(file_noeuds, temp->user->noeud_accessible);

                while (!file_est_vide(file_noeuds)) {
                    // Défiler un nœud de la file
                    int ns_id = defiler(file_noeuds);

                    // Récupérer le nœud correspondant à l'ID
                    NoeudSysteme *ns_temp = get_ns_ID(env, ns_id);

                    // Vérifier si le nœud a assez de capacité pour la donnée
                    if (capacite_restant(ns_temp, env) >= data->taille) {
                        // Placer la donnée sur ce nœud
                        ns_temp->donnees_stockees = ajouterID(ns_temp->donnees_stockees, data->ID, 0);
                        break; // Sortir de la boucle while si la donnée est placée
                    }

                    // Ajouter le nœud aux nœuds déjà parcourus
                    ns_parcourus = ajouterID(ns_parcourus, ns_id, 0);

                    // Ajouter les voisins non parcourus à la file
                    ListeID *voisins = ns_temp->noeuds_accessibles;
                    while (voisins != NULL) {
                        if (!ID_not_in(ns_parcourus, voisins->ID)) {
                            file_noeuds = enfiler(file_noeuds, voisins->ID);
                        }
                        voisins = voisins->suivant;
                    }
                }

                // Passer à la donnée suivante
                donnee_a_placer = donnee_a_placer->suivant;
            }
        }
        temp = temp->suivant;
    }

    return 0;
}