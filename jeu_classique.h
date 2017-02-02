#ifndef JEU_CLASSIQUE_H
#define JEU_CLASSIQUE_H
#include "piece.h"
#include "highscore.h"
#include "menu.h"
#include "jeu_sprint.h"

void init_jeu(SDL_Surface *ecran, SDL_Surface *cases[], int *level, int mode);
void reverse(char s[]);
void itoa(int n, char s[]);
void init_cases_couleur(SDL_Surface *cases[]);
void init_plateau(int tab[][NB_COLONNES]);
int deplacement_possible(int tab[][NB_COLONNES], Piece *piece, int direction);
int arret_defilement(int tab[][NB_COLONNES], Piece *piece);
int rotation_possible_droite(int tab[][NB_COLONNES], Piece *piece);
void effectue_rotation_droite(Piece *piece);
int rotation_possible_gauche(int tab[][NB_COLONNES], Piece *piece);
void effectue_rotation_gauche(Piece *piece);
void afficher_plateau(int tab[][NB_COLONNES], SDL_Surface *ecran, SDL_Surface *cases[]);
void descendre_ligne(int ligne_dep, int tab[][NB_COLONNES], SDL_Surface *ecran, SDL_Surface *cases[]);
void afficher_anim(SDL_Surface *ecran, int ligne, SDL_Surface *cases[]);
int supprimer_ligne_complete(int tab[][NB_COLONNES], SDL_Surface *ecran, SDL_Surface *cases[], int mode);
void placer_piece(int tab[][NB_COLONNES], Piece piece);
void afficher_piece(Piece piece, int tab[][NB_COLONNES], SDL_Surface *ecran, SDL_Surface *cases[]);
void enlever_piece(Piece piece, int tab[][NB_COLONNES], SDL_Surface *ecran, SDL_Surface *cases[]);
void afficher_nouvelle_piece(int piece_suivante, SDL_Surface *ecran, SDL_Surface *cases[]);
void libere_surface(SDL_Surface *cases[]);
void afficher_score(int score, int level, int lines, SDL_Surface *ecran);
void afficher_temps(int times, SDL_Surface *ecran, int mode);
void afficher_piece_fantome(Piece piece, int tab[][NB_COLONNES], SDL_Surface *ecran);
int tetris(SDL_Surface *ecran, int piece_fantome, int gravite);
#endif
