#ifndef CONSTANTE_H
#define CONSTANTE_H
//Bibliothèque SDL 
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//Definition des constantes
#define NB_PIECES 7
#define TAILLE_PIECE 4
#define COULEUR_O 255, 0, 0
#define COULEUR_I 0, 255, 0
#define COULEUR_S 0, 0, 255
#define NB_LIGNES 20
#define NB_COLONNES 10
#define TAILLE_CASE 30
char CHEMIN_POLICE[300];
char CHEMIN_HIGHSCORE_CLASS[300];
char CHEMIN_HIGHSCORE_SPRINT[300];
char CHEMIN_HIGHSCORE_AUX[300];
char CHEMIN_IMAGE_COUPE[300];
char CHEMIN_IMAGE_BTN_FLECHE_GAUCHE[300];
char CHEMIN_IMAGE_BTN_FLECHE_DROITE[300];
#endif
