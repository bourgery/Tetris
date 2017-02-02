#include "highscore.h"

int meilleur_score(int score, int tab[]){
  for(int i =0; i < 5; i++)
    if(score > tab[i])
      return(i);
  return(-1);
}

void demander_nom(char joueur[], SDL_Surface *ecran){
  int continuer = 1;
  int indice = 0;
  char lettre[2];
  lettre[1] = 0;
  SDL_Surface *texte = NULL, *carre = NULL;
  TTF_Font *police = NULL;
  SDL_Color couleur = {255, 255, 255};
  SDL_Rect position, pos = {0, 360};
  SDL_Event event;
  position.y = 260;
  police = TTF_OpenFont(CHEMIN_POLICE, 40);
  carre = SDL_CreateRGBSurface(SDL_HWSURFACE, 700, 60, 32, 0, 0, 0, 0);
  SDL_FillRect(carre, NULL, SDL_MapRGB(carre->format, 0, 0, 0));
  SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
  texte = TTF_RenderText_Blended(police, "Votre nom ? ", couleur);
  position.x = ecran->w / 2 - texte->w / 2;  
  SDL_BlitSurface(texte, NULL, ecran, &position);
  SDL_Flip(ecran);
  position.y = 360;
  SDL_EnableKeyRepeat(75, 75);
  while(continuer){
    SDL_WaitEvent(&event);
    if(event.type == SDL_KEYDOWN){
      lettre[0] = event.key.keysym.sym;
      if(lettre[0] >= SDLK_a && lettre[0] <= SDLK_z){
	joueur[indice] = lettre[0];
	joueur[indice + 1] = 0;
	texte = TTF_RenderText_Blended(police, joueur, couleur);
	position.x = ecran->w / 2 - texte->w / 2;  
	SDL_BlitSurface(carre, NULL, ecran, &pos);
	SDL_BlitSurface(texte, NULL, ecran, &position);
	indice ++;
      }
      if(lettre[0] == SDLK_SPACE){
	joueur[indice] = ' ';
	joueur[indice + 1] = 0;
	texte = TTF_RenderText_Blended(police, joueur, couleur);
	position.x = ecran->w / 2 - texte->w / 2;  
	SDL_BlitSurface(carre, NULL, ecran, &pos);
	SDL_BlitSurface(texte, NULL, ecran, &position);
	indice ++;
      }
      if(lettre[0] == SDLK_BACKSPACE && indice){
	joueur[indice - 1] = 0;
	texte = TTF_RenderText_Blended(police, joueur, couleur);
	if(strlen(joueur))
	  position.x = ecran->w / 2 - texte->w / 2;
	SDL_BlitSurface(carre, NULL, ecran, &pos);
	SDL_BlitSurface(texte, NULL, ecran, &position);
	indice --;
      }
      if(lettre[0] == SDLK_RETURN){
	joueur[indice] = 0;
	continuer = 0;
      }
      SDL_Flip(ecran);
    }
  }
  SDL_FreeSurface(carre);
  SDL_FreeSurface(texte);
  TTF_CloseFont(police);
}

void afficher_highscore(char complet[][200], SDL_Surface *ecran){
  TTF_Font *police = NULL;
  SDL_Color couleur = {255, 255, 255};
  SDL_Rect position;
  SDL_Event event;
  int text, num;
  SDL_Surface *texte = NULL, *coupe = NULL;
  int continuer = 1;
  char *c[5] = {"1", "2", "3", "4", "5"};
  ecran = SDL_SetVideoMode(555, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE);
  coupe = IMG_Load(CHEMIN_IMAGE_COUPE);
  SDL_SetColorKey(coupe, SDL_SRCCOLORKEY, SDL_MapRGB(coupe->format, 255, 255, 255));
  police = TTF_OpenFont(CHEMIN_POLICE, 40);
  position.y = 75;
  SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
  texte = TTF_RenderText_Blended(police, "Highscores", couleur);
  position.x = ecran->w / 2 - texte->w / 2;
  SDL_BlitSurface(texte, NULL, ecran, &position);
  position.x += texte->w + 25;
  SDL_BlitSurface(coupe, NULL, ecran, &position);
  position.x -= texte->w + 82;
  SDL_BlitSurface(coupe, NULL, ecran, &position);
  position.x = ecran->w / 2 - texte->w / 2;
  for(int i = 0; i < 5; i++){
    for(int j = 0; j < strlen(complet[i]); j++)
      if(complet[i][j] == '\n')
	complet[i][j] = 0;
  }
  position.y += 50;
  text = ecran->w / 2 - texte->w / 2;
  num = text - 50;
  for(int i = 0; i < 5; i++){
    position.y += 55;
    position.x = num;
    texte = TTF_RenderText_Blended(police, c[i], couleur);
    SDL_BlitSurface(texte, NULL, ecran, &position);
    position.x = text;
    texte = TTF_RenderText_Blended(police, complet[i], couleur);
    SDL_BlitSurface(texte, NULL, ecran, &position);
  }
  SDL_Flip(ecran);
  while(continuer){
    SDL_WaitEvent(&event);
    switch(event.type){
    case SDL_KEYDOWN:
      switch(event.key.keysym.sym){
      case SDLK_ESCAPE:
	continuer = 0;
	break;
      default:
	break;
      }
      break;
    }
    SDL_Flip(ecran);
  }
  TTF_CloseFont(police);
  SDL_FreeSurface(texte);
}

void gerer_highscore(int score, SDL_Surface *ecran, int mode){
  char nom[5][200];
  int scores[5];
  char complet[5][200];
  int rang;
  char chaine[100];
  char joueur[200];
  char score_chaine[20];
  FILE *fichier = NULL;
  FILE *fichaux = NULL;
  if(mode == 1)
    fichier = fopen(CHEMIN_HIGHSCORE_CLASS, "r+");
  else
    fichier = fopen(CHEMIN_HIGHSCORE_SPRINT, "r+");
  fichaux = fopen(CHEMIN_HIGHSCORE_AUX, "r+");
  for(int i = 0; i < 5; i++)
    fscanf(fichier, "%s %d", nom[i], &scores[i]);
  rewind(fichier);
  for(int i = 0; i < 5; i++)
    fgets(complet[i], 200, fichier);
  rewind(fichier);
  rang = meilleur_score(score, scores);
  if(rang != -1){
    demander_nom(joueur, ecran);
    rewind(fichaux);
    for(int i = 0; i < rang ; i++)
      fputs(complet[i], fichaux);
    itoa(score, score_chaine);
    strcat(joueur, " ");
    strcat(joueur, score_chaine);
    strcat(joueur, "\n");
    fputs(joueur, fichaux);
    for(int i = rang; i < 4; i++)
      fputs(complet[i], fichaux);
    rewind(fichier);
    rewind(fichaux);
    for(int i = 0; i < 5; i++){
      fgets(chaine, 100, fichaux);
      fputs(chaine, fichier);
    }
    rewind(fichier);
    for(int i = 0; i < 5; i++)
    fgets(complet[i], 200, fichier);
  }
  afficher_highscore(complet, ecran);
  fclose(fichier);
  fclose(fichaux);
}
