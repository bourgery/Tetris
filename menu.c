#include "menu.h"

void choix_mode(SDL_Surface *ecran, int *mode, int *piece_fantome, int *gravite,char chemin[]){
  SDL_Surface *texte = NULL;
  SDL_Rect position;
  SDL_Color couleurnoir = {0, 0, 0};
  SDL_Event event;
  TTF_Font *police = NULL;
  int continuer = 1;
  police = TTF_OpenFont(CHEMIN_POLICE, 40);
  ecran = SDL_SetVideoMode(555, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE);
  SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
  position.x = 200;
  position.y = 100;
  texte = TTF_RenderText_Blended(police, "Tetris classique", couleurnoir);
  SDL_BlitSurface(texte, NULL, ecran, &position);
  position.y = 250;
  texte = TTF_RenderText_Blended(police, "Tetris sprint", couleurnoir);
  SDL_BlitSurface(texte, NULL, ecran, &position);
  position.y = 400;
  texte = TTF_RenderText_Blended(police, "Options", couleurnoir);
  SDL_BlitSurface(texte, NULL, ecran, &position);
  SDL_Flip(ecran);
  while(continuer){
    SDL_WaitEvent(&event);
    switch(event.type){
    case SDL_MOUSEBUTTONUP:
      if(event.button.y >= 100 && event.button.y <= 140 && event.button.x >= 200 && event.button.x <= 500){
	*mode = 1;
	continuer = 0;
	break;
      }
      if(event.button.y >= 250 && event.button.y <= 290 && event.button.x >= 200 && event.button.x <= 500){
	*mode = 2;
	continuer = 0;
	break;
      }
      if(event.button.y >= 400 && event.button.y <= 440 && event.button.x >= 200 && event.button.x <= 500){
	*mode = 3;
	continuer = 0;
	break;
      }
      break;
    case SDL_QUIT:
      *mode = 4;
      continuer = 0;
      break;
    }
    SDL_Flip(ecran);
  }
  SDL_FreeSurface(texte);
}

void choix_level(SDL_Surface *ecran, int *level){
  SDL_Surface *bouton_droit = NULL, *bouton_gauche = NULL, *texte = NULL, *carre =NULL;
  SDL_Rect position;
  SDL_Color couleurnoir = {0, 0, 0};
  SDL_Event event;
  int continuer = 1;
  char c[20];
  TTF_Font *police = NULL;
  police = TTF_OpenFont(CHEMIN_POLICE, 40);
  itoa(*level, c);
  SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
  bouton_droit = IMG_Load(CHEMIN_IMAGE_BTN_FLECHE_DROITE);
  bouton_gauche = IMG_Load(CHEMIN_IMAGE_BTN_FLECHE_GAUCHE);
  carre = SDL_CreateRGBSurface(SDL_HWSURFACE, 50, 50, 32, 0, 0, 0, 0);
  SDL_FillRect(carre, NULL, SDL_MapRGB(carre->format, 255, 255, 255));
  position.y = 200;
  position.x = 120;
  SDL_BlitSurface(bouton_gauche, NULL, ecran, &position);
  position.x = 320;
  SDL_BlitSurface(bouton_droit, NULL, ecran, &position);
  SDL_Flip(ecran);
  position.x = 235;
  while(continuer){
    SDL_WaitEvent(&event);
    switch(event.type){
    case SDL_KEYDOWN:
      switch(event.key.keysym.sym){
      case SDLK_RETURN:
	continuer = 0;
	break;
      default:
	break;
      }
      break;
    case SDL_MOUSEBUTTONUP:
      if(event.button.y >= 200 && event.button.y <= 250 && event.button.x >= 100 && event.button.x <= 160 && *level > 1)
	*level = *level - 1;
      if(event.button.y >= 200 && event.button.y <= 250 && event.button.x >= 300 && event.button.x <= 360 && *level < 10)
	*level = *level + 1;
      break;
    }
    itoa(*level, c);
    texte = TTF_RenderText_Blended(police, c, couleurnoir);
    SDL_BlitSurface(carre, NULL, ecran, &position);
    SDL_BlitSurface(texte, NULL, ecran, &position);
    SDL_Flip(ecran);
  }
  SDL_FreeSurface(bouton_droit);
  SDL_FreeSurface(bouton_gauche);
  SDL_FreeSurface(texte);
  TTF_CloseFont(police);
}

void option(SDL_Surface *ecran, int *a, int *b){
  SDL_Surface *texte = NULL, *carre = NULL;
  SDL_Rect position = {50, 150};
  SDL_Color couleurnoir = {0, 0, 0};
  SDL_Event event;
  TTF_Font *police = NULL;
  int continuer = 1;
  char *c[2] = {"NON", "OUI"};
  carre = SDL_CreateRGBSurface(SDL_HWSURFACE, 200, 50, 32, 0, 0, 0, 0);
  SDL_FillRect(carre, NULL, SDL_MapRGB(carre->format, 255, 255, 255));
  police = TTF_OpenFont(CHEMIN_POLICE, 50);
  texte = TTF_RenderText_Blended(police, "Piece fantome : ", couleurnoir);
  SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
  SDL_BlitSurface(texte, NULL, ecran, &position);
  texte = TTF_RenderText_Blended(police, "Gravite : ", couleurnoir);
  position.y += 150;
  SDL_BlitSurface(texte, NULL, ecran, &position);
  texte = TTF_RenderText_Blended(police, "Retour", couleurnoir);
  position.y += 150;
  SDL_BlitSurface(texte, NULL, ecran, &position);
  texte = TTF_RenderText_Blended(police, c[*a], couleurnoir);
  position.x = 350;
  position.y = 150;
  SDL_BlitSurface(texte, NULL, ecran, &position);
  texte = TTF_RenderText_Blended(police, c[*b], couleurnoir);
  position.x = 350;
  position.y = 300;
  SDL_BlitSurface(texte, NULL, ecran, &position);
  while(continuer){
    SDL_WaitEvent(&event);
    switch(event.type){
    case SDL_MOUSEBUTTONUP:
      if(event.button.y >= 150 && event.button.y <= 200 && event.button.x >= 50 && event.button.x <= 500){
	*a = *a ^ 1;
	texte = TTF_RenderText_Blended(police, c[*a], couleurnoir);
	position.x = 350;
	position.y = 150;
	SDL_BlitSurface(carre, NULL, ecran, &position);
	SDL_BlitSurface(texte, NULL, ecran, &position);
      }
      if(event.button.y >= 300 && event.button.y <= 350 && event.button.x >= 50 && event.button.x <= 500){
	*b = *b ^ 1;
	texte = TTF_RenderText_Blended(police, c[*b], couleurnoir);
	position.x = 350;
	position.y = 300;
	SDL_BlitSurface(carre, NULL, ecran, &position);
	SDL_BlitSurface(texte, NULL, ecran, &position);
      }
       if(event.button.y >= 450 && event.button.y <= 500 && event.button.x >= 50 && event.button.x <= 500)
	 continuer = 0;
       break;
    }
    SDL_Flip(ecran);
  }
}
