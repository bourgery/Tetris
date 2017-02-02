#include "jeu_sprint.h"

void placer_piece_tab_grav(int tab[][NB_COLONNES], Piece piece, int num){
  for(int i = 0; i < TAILLE_PIECE; i++)
    for(int j = 0; j < TAILLE_PIECE; j++)
      if(piece.mat_piece[i][j])
	tab[piece.posY + i][piece.posX + j] = num;
}

int grav_possible(int grav[][NB_COLONNES], int i, int j){
  int num = grav[i][j];
  if(grav[i + 1][j])
    return(0);
  if(j + 1 < NB_COLONNES){
    if(grav[i][j + 1] == num)
      if(i - 1 <= 0 && !grav[i - 1][j + 1])
	return(0);
  }
  if(j + 1 < NB_COLONNES - 1 && grav[i][j + 1] == num && !grav[i + 1][j + 1])
      return(0);
    if(j - 1 <= 0 && grav[i - 1][j - 1] == num && !grav[i][j - 1])
      return(0);
  return(1);
}

void effectue_grav(int grav[][NB_COLONNES], int tab[][NB_COLONNES], SDL_Surface *ecran, SDL_Surface *cases[]){
  for(int i = NB_LIGNES - 2; i >= 0; i--){
    for(int j = 0; j < NB_COLONNES; j++){
      if(grav[i][j])
	if(grav_possible(grav, i, j)){
	  tab[i + 1][j] = tab[i][j];
	  tab[i][j] = 0;
	  grav[i + 1][j] = grav[i][j];
	  grav[i][j] = 0;
	  if(i < NB_LIGNES - 2)
	    i ++;
	  j --;
	}
    }
  }
  afficher_plateau(tab, ecran, cases);
  SDL_Flip(ecran);  
}

void afficher_piece_garder(int pieces, SDL_Surface *ecran, SDL_Surface *cases[]){
  Piece piece;
  init_piece(&piece, pieces);
  SDL_Rect position;
  position.y = 50;
  position.x = 550;
  for(int i = 0; i < TAILLE_PIECE; i++){
    for(int j = 0; j < TAILLE_PIECE; j++){
      position.x = j * TAILLE_CASE + 550;
      position.y = i * TAILLE_CASE + 50;
      if(piece.mat_piece[i][j])
	SDL_BlitSurface(cases[piece.mat_piece[i][j]], NULL, ecran, &position);
      else
	SDL_BlitSurface(cases[8], NULL, ecran, &position);
    }
  }
}

int tetris_gravite(SDL_Surface *ecran, int piece_fantome, int gravite){
  srand(time(NULL));
  SDL_Surface *cases[11] = {NULL};
  Piece piece;
  int pause;
  int continuer = 1;
  int piece_stope = 0;
  SDL_Event event;
  int temps_prec;
  int temps_act;
  int piece_suivante = (rand() % NB_PIECES) + 1;
  int piece_act;
  int piece_garde = 0;
  int tab[NB_LIGNES][NB_COLONNES];
  int grav[NB_LIGNES][NB_COLONNES];
  int numero_piece_act = 0;
  int score = 0;
  int level = 5;
  int combo = 1;
  int nbline = 0;
  int line = 0;
  int lines = 0;
  int timer;
  int drapeau = 0;
  int tps = 0;
  int tmp;
  init_cases_couleur(cases);
  init_plateau(tab);
  init_plateau(grav);
  ecran = SDL_SetVideoMode(705, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE);
  init_jeu(ecran, cases, &level, 2);
  SDL_EnableKeyRepeat(75, 75);
  timer = SDL_GetTicks();
  while(continuer && tps <= 120){
    init_piece(&piece, piece_suivante);
    piece_act = piece_suivante;
    piece_suivante = (rand() % NB_PIECES) + 1;
    numero_piece_act ++; 
    afficher_nouvelle_piece(piece_suivante, ecran, cases);
    if(tab[0][5] || tab[0][6] || tab[0][7])
      continuer = 0;
    else{
      piece_stope = 0;
      afficher_piece(piece, tab, ecran, cases);
    }
    if(piece_fantome)
      afficher_piece_fantome(piece, tab, ecran);
    temps_prec = SDL_GetTicks();
    while(!piece_stope && tps <= 120){
      temps_act = SDL_GetTicks();
      if(temps_act - timer > 1000){//Temps qui passe
	timer = temps_act;
	tps ++;
	afficher_temps(tps, ecran, 2);
	}
      if((temps_act - temps_prec) > (600 - level*50)){//Chute piece
	if(arret_defilement(tab, &piece)){//Bloque
	  placer_piece(tab, piece);
	  piece_stope = 1;
	  line = supprimer_ligne_complete(tab, ecran, cases, 1);
	  if(gravite){
	    placer_piece_tab_grav(grav, piece, numero_piece_act);
	    supprimer_ligne_complete(grav, ecran, cases, 2);
	    lines = line;
	    while(lines){ 
	      effectue_grav(grav, tab, ecran, cases);
	      lines = supprimer_ligne_complete(tab, ecran, cases, 1);
	      line += lines;
	      supprimer_ligne_complete(grav, ecran, cases, 2);
	      afficher_plateau(tab, ecran, cases);
	    }
	  }
	  if(line){
	    drapeau = 0;
	    combo += line;
	  }
	  else{
	    drapeau ++;
	    if(drapeau == 3){
	      if(combo != 1)
		combo /= 2;
	      drapeau = 0;
	    }
	  }
	  score += line * level * (50 * line) * combo;
	  nbline += line;
	}
	else{//Non bloque
	  if(piece_fantome)
	    afficher_plateau(tab, ecran, cases);
	  enlever_piece(piece, tab, ecran, cases);
	  piece.posY ++;
	  afficher_piece(piece, tab, ecran, cases);
	  if(piece_fantome)
	    afficher_piece_fantome(piece, tab, ecran);
	}
	afficher_score(score, combo, nbline, ecran);
	temps_prec = temps_act;
      }
      if(SDL_PollEvent(&event)){
	switch(event.type){
	case SDL_KEYDOWN:
	  switch(event.key.keysym.sym){
	  case SDLK_RIGHT:
	    if(deplacement_possible(tab, &piece, 1)){
	      if(piece_fantome)
		afficher_plateau(tab, ecran, cases);
	      enlever_piece(piece, tab, ecran, cases);
	      piece.posX ++;
	      afficher_piece(piece, tab, ecran, cases);
	      if(piece_fantome)
		afficher_piece_fantome(piece, tab, ecran);
	    }
	    break;
	  case SDLK_LEFT:
	    if(deplacement_possible(tab, &piece, -1)){
	      if(piece_fantome)
		afficher_plateau(tab, ecran, cases);
	      enlever_piece(piece, tab, ecran, cases);
	      piece.posX --;
	      afficher_piece(piece, tab, ecran, cases);
	      if(piece_fantome)
		afficher_piece_fantome(piece, tab, ecran);
	    }
	    break;
	  case SDLK_UP:
	    if(rotation_possible_droite(tab, &piece)){
	      if(piece_fantome)
		afficher_plateau(tab, ecran, cases);
	      enlever_piece(piece, tab, ecran, cases);
	      effectue_rotation_droite(&piece);
	      afficher_piece(piece, tab, ecran, cases);
	      if(piece_fantome)
		afficher_piece_fantome(piece, tab, ecran);
	    }
	    break;
	  case SDLK_DOWN:
	    if(rotation_possible_gauche(tab, &piece)){
	      afficher_plateau(tab, ecran, cases);
	      enlever_piece(piece, tab, ecran, cases);
	      effectue_rotation_gauche(&piece);
	      afficher_piece(piece, tab, ecran, cases);
	      afficher_piece_fantome(piece, tab, ecran);
	    }
	    break;
	  case SDLK_SPACE:
	    if(arret_defilement(tab, &piece)){
	      placer_piece(tab, piece);
	      piece_stope = 1;
	      line = supprimer_ligne_complete(tab, ecran, cases, 1);
	      if(gravite){
		placer_piece_tab_grav(grav, piece, numero_piece_act);
		lines = line;
		supprimer_ligne_complete(grav, ecran, cases, 2);
		while(lines){ 
		  effectue_grav(grav, tab, ecran, cases);
		  lines = supprimer_ligne_complete(tab, ecran, cases, 1);
		  line += lines;
		  supprimer_ligne_complete(grav, ecran, cases, 2);
		  afficher_plateau(tab, ecran, cases);
		}
	      }
	      if(line){
		drapeau = 0;
		combo += line;
	      }
	      else{
		drapeau ++;
		if(drapeau == 3){
		  if(combo != 1)
		    combo /= 2;
		  drapeau = 0;
		}
	      }
	      score += line * level * (50 * line) * combo;
	      nbline += line;
	    }
	    else{
	      if(piece_fantome)
		afficher_plateau(tab, ecran, cases);
	      enlever_piece(piece, tab, ecran, cases);
	      piece.posY ++;
	      afficher_piece(piece, tab, ecran, cases);
	      if(piece_fantome)
		afficher_piece_fantome(piece, tab, ecran);
	    }
	    break;
	  case SDLK_RETURN:
	    while(!arret_defilement(tab, &piece))
	      piece.posY ++;
	    placer_piece(tab, piece);
	    piece_stope = 1;
	    line = supprimer_ligne_complete(tab, ecran, cases, 1);
	    if(piece_fantome)
	      afficher_plateau(tab, ecran, cases);
	    if(gravite){
	      supprimer_ligne_complete(grav, ecran, cases, 2);
	      placer_piece_tab_grav(grav, piece, numero_piece_act);
	      lines = line;
	      while(lines){ 
		effectue_grav(grav, tab, ecran, cases);
		lines = supprimer_ligne_complete(tab, ecran, cases, 1);
		line += lines;
		supprimer_ligne_complete(grav, ecran, cases, 2);
		afficher_plateau(tab, ecran, cases);
	      }
	    }
	    if(line){
	      drapeau = 0;
	      combo += line;
	    }
	      else{
		drapeau ++;
		if(drapeau == 3){
		  if(combo != 1)
		    combo /= 2;
		  drapeau = 0;
		}
	      }
	    score += line * level * (50 * line) * combo;
	    nbline += line;
	    break;
	  case SDLK_RSHIFT:
	    if(!piece_garde){
	      piece_garde = piece_act;
	      piece_stope = 1;
	    }
	    else{
	      tmp = piece_act;
	      piece_act = piece_garde;
	      piece_garde = tmp;
	      init_piece(&piece, piece_act);
	    }
	    afficher_piece_garder(piece_garde, ecran, cases);
	    afficher_plateau(tab, ecran, cases);
	    break;
	  case SDLK_ESCAPE:
	    piece_stope = 1;
	    continuer = 0;
	    break;
	  case SDLK_p:
	    pause = 1;
	    while(pause){
	      SDL_WaitEvent(&event);
	      switch(event.type){
	      case SDL_KEYDOWN:
		switch(event.key.keysym.sym){
		case SDLK_r:
		  pause = 0;
		  break;
		default:
		  break;
		}
		break;
	      }
	    }
	    break;
	  default:
	    break;
	  }
	  break;
	}
      }
      SDL_Flip(ecran);
    }
  }
  libere_surface(cases);
  SDL_EnableKeyRepeat(0, 0);
  return(score);
}
