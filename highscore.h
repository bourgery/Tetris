#ifndef HIGHSCORE_H
#define HIGHSCORE_H
#include "constante.h"
#include "jeu_classique.h"

int meilleur_score(int score, int tab[]);
void demander_nom(char joueur[], SDL_Surface *ecran);
void afficher_highscore(char complet[][200], SDL_Surface *ecran);
void gerer_highscore(int score, SDL_Surface *ecran, int mode);
#endif
