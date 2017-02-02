#include "jeu_classique.h"
#include "jeu_sprint.h"
#include "menu.h"
#include "constante.h"

char CHEMIN_POLICE[300];
char CHEMIN_HIGHSCORE_CLASS[300];
char CHEMIN_HIGHSCORE_SPRINT[300];
char CHEMIN_HIGHSCORE_AUX[300];
char CHEMIN_IMAGE_COUPE[300];
char CHEMIN_IMAGE_BTN_FLECHE_GAUCHE[300];
char CHEMIN_IMAGE_BTN_FLECHE_DROITE[300];

void init_constante(char chemin[]){
  strcpy(CHEMIN_POLICE, chemin);
  strcat(CHEMIN_POLICE, "angelina.TTF");
  strcpy(CHEMIN_HIGHSCORE_CLASS, chemin);
  strcat(CHEMIN_HIGHSCORE_CLASS, "highscore_class.txt");
  strcpy(CHEMIN_HIGHSCORE_SPRINT, chemin);
  strcat(CHEMIN_HIGHSCORE_SPRINT, "highscore_sprint.txt");
  strcpy(CHEMIN_IMAGE_COUPE, chemin);
  strcat(CHEMIN_IMAGE_COUPE, "coupe.png");
  strcpy(CHEMIN_IMAGE_BTN_FLECHE_DROITE, chemin);
  strcat(CHEMIN_IMAGE_BTN_FLECHE_DROITE, "bouton_fleche_droite.png");
  strcpy(CHEMIN_IMAGE_BTN_FLECHE_GAUCHE, chemin);
  strcat(CHEMIN_IMAGE_BTN_FLECHE_GAUCHE, "bouton_fleche_gauche.png");
  strcpy(CHEMIN_HIGHSCORE_AUX, chemin);
  strcat(CHEMIN_HIGHSCORE_AUX, "aux.txt");
}

void mettre_chemin(char chemin[], char argv[]){
  int indice = 0;
  int last_slash = 0;
  while(argv[indice]){
    if(argv[indice] == '/')
      last_slash = indice;
    chemin[indice] = argv[indice];	
    indice ++;
  }
  chemin[last_slash + 1] = 0;
}

int main(int argc, char *argv[]){
  SDL_Surface *ecran = NULL;
  int score;
  int mode;
  int drapeau = 1;
  int piece_fantome = 1;
  int gravite = 1;
  char chemin[300];
  mettre_chemin(chemin, argv[0]);
  init_constante(chemin);
  SDL_Init(SDL_INIT_VIDEO);
  TTF_Init();
  ecran = SDL_SetVideoMode(555, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE);
  do{
    choix_mode(ecran, &mode, &piece_fantome, &gravite, chemin);
  if(mode == 1){
    score = tetris(ecran, piece_fantome, gravite);
    gerer_highscore(score, ecran, 1);
  }
  else if(mode == 2){
    score = tetris_gravite(ecran, piece_fantome, gravite);
    gerer_highscore(score, ecran, 2);
  }
  else if(mode == 3){
    option(ecran, &piece_fantome, &gravite);
    choix_mode(ecran, &mode, &piece_fantome, &gravite, chemin);
  }
  else
    drapeau = 0;
  }while(drapeau);
  SDL_Quit();
  return(0);
}
