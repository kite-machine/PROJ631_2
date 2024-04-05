#include <stdio.h>
#include <stdlib.h>
#ifndef _LISTES_H
#define _LISTES_H

// Structure pour une donnée
typedef struct {
    int ID;
    int taille;
} Donnee;

// Structure pour une liste d'ID
typedef struct ListeID {
    int ID;
    int temps;
    struct ListeID *suivant;
} ListeID;

// Structure pour un utilisateur
typedef struct {
    int ID;
    ListeID *donnees_interet; // Liste d'ID de données d'intérêt
    int noeud_accessible; // ID du nœud système accessible
} Utilisateur;

// Structure pour un nœud système
typedef struct {
    int ID;
    int capacite_memoire;
    ListeID *donnees_stockees; // Liste d'ID de données stockées localement
    ListeID *noeuds_accessibles; // Liste d'ID de nœuds système/utilisateurs accessibles
} NoeudSysteme;

ListeID *initListeID();
ListeID *ajouterID(ListeID *liste, int ID, int temps);

#endif /* _LISTES_H */