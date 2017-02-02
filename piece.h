#ifndef PIECE_H
#define PIECE_H
#include "constante.h"

enum Forme{
  O = 1, I, S, Z, L, J, T
};

typedef struct Piece{
  int mat_piece[TAILLE_PIECE][TAILLE_PIECE];
  Uint32 couleur;
  enum Forme forme;
  int posX;
  int posY;
} Piece;

void copie_mat(int const src[][TAILLE_PIECE], int dst[][TAILLE_PIECE]);
void init_piece(Piece *piece, enum Forme forme);
#endif
  
