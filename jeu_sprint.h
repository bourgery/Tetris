#ifndef JEU_SPRINT_H
#define JEU_SPRINT_H
#include "jeu_classique.h"

void placer_piece_tab_grav(int tab[][NB_COLONNES], Piece piece, int num);
int grav_possible(int grav[][NB_COLONNES], int i, int j);
void effectue_grav(int grav[][NB_COLONNES], int tab[][NB_COLONNES], SDL_Surface *ecran, SDL_Surface *cases[]);
void afficher_piece_garder(int pieces, SDL_Surface *ecran, SDL_Surface *cases[]);
int tetris_gravite(SDL_Surface *ecran, int piece_fantome, int gravite);
#endif
