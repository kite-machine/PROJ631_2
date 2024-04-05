#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "classe.h"


void init_liste_data(liste_data* l){
    l->tete = NULL;
}

int ajouter_queue_data(liste_data* L, data d) {
    element_data *new = malloc(sizeof(element_data));
    new->suivant = NULL;
    new->data = d;
    element_data *temp;
    temp = L->tete;
    if (temp == NULL)
    {
        L->tete = new;
        return 0;
    }
    while (temp->suivant != NULL)
    {
        temp = temp->suivant;
    }
    temp->suivant = new;
    return 0;
}

void init_liste_sn(liste_sn* l){
    l->tete = NULL;
}

int ajouter_queue_data(liste_sn* L, syst_node sn, double temps) {
    element_voisin *new = malloc(sizeof(element_voisin));
    new->suivant = NULL;
    new->syst_node = sn;
    new->temps = temps;
    element_voisin *temp;
    temp = L->tete;
    if (temp == NULL)
    {
        L->tete = new;
        return 0;
    }
    while (temp->suivant != NULL)
    {
        temp = temp->suivant;
    }
    temp->suivant = new;
    return 0;
}
