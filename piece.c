#include "piece.h"

int PIECE_TAB[NB_PIECES][TAILLE_PIECE][TAILLE_PIECE] =
  { // O
    {
      {0, 0, 0, 0},
      {0, 1, 1, 0},
      {0, 1, 1, 0},
      {0, 0, 0, 0}
    },
    // I
    {
      {0, 0, 0, 0},
      {2, 2, 2, 2},
      {0, 0, 0, 0},
      {0, 0, 0, 0}
    },
    // S
    {
      {0, 0, 0, 0},
      {0, 0, 3, 3},
      {0, 3, 3, 0},
      {0, 0, 0, 0}
    }, 
    // Z
    {
      {0, 0, 0, 0},
      {0, 4, 4, 0},
      {0, 0, 4, 4},
      {0, 0, 0, 0}
    },
 
    // L
    {
      {0, 0, 0, 0},
      {0, 5, 5, 5},
      {0, 5, 0, 0},
      {0, 0, 0, 0}
    },
    
    // J
    {
      {0, 0, 0, 0},
      {0, 6, 6, 6},
      {0, 0, 0, 6},
      {0, 0, 0, 0}
    },
 
    // T
    {
      {0, 0, 0, 0},
      {0, 7, 7, 7},
      {0, 0, 7, 0},
      {0, 0, 0, 0}
    },
  };

void copie_mat(int const src[][TAILLE_PIECE], int dst[][TAILLE_PIECE]){
  for(int i = 0; i < TAILLE_PIECE; i++)
    for(int j = 0; j < TAILLE_PIECE; j++)
      dst[i][j] = src[i][j];
}
  
void init_piece(Piece *piece, enum Forme forme){
  piece->posX = (NB_COLONNES - 1)/ 2;
  piece->posY = -1;    
  switch(forme){
  case(1):
    copie_mat(PIECE_TAB[0], piece->mat_piece);
    piece->forme = 1;
    break;
  case(2):
    copie_mat(PIECE_TAB[1], piece->mat_piece);
    piece->forme = 2;
    break;
  case(3):
    copie_mat(PIECE_TAB[2], piece->mat_piece);
    piece->forme = 3;
    break;
  case(4):
    copie_mat(PIECE_TAB[3], piece->mat_piece);
    piece->forme = 4;
    break;
  case(5):
    copie_mat(PIECE_TAB[4], piece->mat_piece);
    piece->forme = 5;
    break;
  case(6):
    copie_mat(PIECE_TAB[5], piece->mat_piece);
    piece->forme = 6;
    break;
  case(7):
    copie_mat(PIECE_TAB[6], piece->mat_piece);
    piece->forme = 7;
    break;
  }
}
