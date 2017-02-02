#ifndef MENU_H
#define MENU_H
#include "constante.h"
#include "jeu_classique.h"

void choix_mode(SDL_Surface *ecran, int *mode, int *piece_fantome, int *gravite, char chemin[]);
void choix_level(SDL_Surface *ecran, int *level);
void option(SDL_Surface *ecran, int *piece_fantome, int *gravite);
#endif
