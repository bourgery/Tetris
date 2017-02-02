#include "jeu_classique.h"

void init_jeu(SDL_Surface *ecran, SDL_Surface *cases[], int *level, int mode){
  SDL_Surface *menu = NULL, *texte = NULL, *tour = NULL, *tourhtps = NULL, *tourvtps = NULL, *barre = NULL;
  SDL_Rect position;
  SDL_Rect postourtps = {0, 0};
  SDL_Color couleurnoir = {0, 0, 0};
  TTF_Font *police = NULL;
  position.x = 305;
  position.y = 0;
  if(mode == 1)
    choix_level(ecran, level);
  SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
  police = TTF_OpenFont(CHEMIN_POLICE, 40);
  if(mode == 1)
    texte = TTF_RenderText_Blended(police, "Level : ", couleurnoir);
  else
    texte = TTF_RenderText_Blended(police, "Combo : X", couleurnoir);
  menu = SDL_CreateRGBSurface(SDL_HWSURFACE, 400, 600, 32, 0, 0, 0, 0);
  tour = SDL_CreateRGBSurface(SDL_HWSURFACE, 5, 600, 32, 0, 0, 0, 0);
  SDL_FillRect(menu, NULL, SDL_MapRGB(menu->format, 255, 255, 255));
  SDL_FillRect(tour, NULL, SDL_MapRGB(tour->format, 112, 128, 144));
  SDL_BlitSurface(tour, NULL, ecran, &position);
  position.x = 310;
  SDL_BlitSurface(menu, NULL, ecran, &position);
  position.x = 0;
  SDL_BlitSurface(tour, NULL, ecran, &position);
  position.x = 320;
  position.y = 200;
  SDL_BlitSurface(texte, NULL, ecran, &position);
  texte = TTF_RenderText_Blended(police, "Next : ", couleurnoir);
  position.y = 10;
  SDL_BlitSurface(texte, NULL, ecran, &position);
  texte = TTF_RenderText_Blended(police, "Score : ", couleurnoir);
  position.y = 300;
  SDL_BlitSurface(texte, NULL, ecran, &position);
  texte = TTF_RenderText_Blended(police, "Lines : ", couleurnoir);
  position.y = 400;
  SDL_BlitSurface(texte, NULL, ecran, &position);
  texte = TTF_RenderText_Blended(police, "Time : ", couleurnoir);
  position.y = 500;
  SDL_BlitSurface(texte, NULL, ecran, &position);
  if(mode == 2){
    texte = TTF_RenderText_Blended(police, "Joker : ", couleurnoir);
    position.x = 500;
    position.y = 10;
    SDL_BlitSurface(texte, NULL, ecran, &position);
    barre = SDL_CreateRGBSurface(SDL_HWSURFACE, 241, 11, 32, 0, 0, 0, 0);
    tourhtps = SDL_CreateRGBSurface(SDL_HWSURFACE, 240, 1, 32, 0, 0, 0, 0);
    tourvtps = SDL_CreateRGBSurface(SDL_HWSURFACE, 1, 10, 32, 0, 0, 0, 0);
    SDL_FillRect(barre, NULL, SDL_MapRGB(barre->format, 135, 206, 250));
    SDL_BlitSurface(tourvtps, NULL, barre, &postourtps);
    SDL_BlitSurface(tourhtps, NULL, barre, &postourtps);
    postourtps.x = 240;
    SDL_BlitSurface(tourvtps, NULL, barre, &postourtps);
    postourtps.x = 0;
    postourtps.y = 10;
    SDL_BlitSurface(tourhtps, NULL, barre, &postourtps);
    SDL_Flip(barre);
    postourtps.x = 320;
    postourtps.y = 560;
    SDL_BlitSurface(barre, NULL, ecran, &postourtps);
  }
  SDL_Flip(ecran);
  SDL_FreeSurface(menu);
  SDL_FreeSurface(texte);
  SDL_FreeSurface(tourhtps);
  SDL_FreeSurface(tourvtps);
  SDL_FreeSurface(tour);
  TTF_CloseFont(police);
}

void reverse(char s[]){
  int i, j;
  char c;
  for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
    c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}

void itoa(int n, char s[]){
  int i, sign;
  
  if ((sign = n) < 0)  
         n = -n;       
  i = 0;
  do {       
    s[i++] = n % 10 + '0';   
  } while ((n /= 10) > 0);   
  if (sign < 0)
    s[i++] = '-';
  s[i] = '\0';
  reverse(s);
}

void init_cases_couleur(SDL_Surface *cases[]){
  SDL_Rect pos = {0, 0}, posi = {0, TAILLE_CASE - 1}, posit = {TAILLE_CASE - 1, 0};
  for(int i = 0; i < NB_PIECES + 2; i++)
    cases[i] = SDL_CreateRGBSurface(SDL_HWSURFACE, TAILLE_CASE, TAILLE_CASE, 32, 0, 0, 0, 0);
  SDL_FillRect(cases[0], NULL, SDL_MapRGB(cases[0]->format, 0, 0, 0));
  SDL_FillRect(cases[1], NULL, SDL_MapRGB(cases[1]->format, 255, 185, 15));
  SDL_FillRect(cases[2], NULL, SDL_MapRGB(cases[2]->format, 209, 238, 238));
  SDL_FillRect(cases[3], NULL, SDL_MapRGB(cases[3]->format, 102, 205, 0));
  SDL_FillRect(cases[4], NULL, SDL_MapRGB(cases[4]->format, 238, 44, 44));
  SDL_FillRect(cases[5], NULL, SDL_MapRGB(cases[5]->format, 255, 140, 0));
  SDL_FillRect(cases[6], NULL, SDL_MapRGB(cases[6]->format, 65, 105, 225));
  SDL_FillRect(cases[7], NULL, SDL_MapRGB(cases[7]->format, 186, 85, 211));
  SDL_FillRect(cases[8], NULL, SDL_MapRGB(cases[8]->format, 255, 255, 255));
  cases[9] = SDL_CreateRGBSurface(SDL_HWSURFACE, 1, TAILLE_CASE, 32, 0, 0, 0, 0);
  cases[10] = SDL_CreateRGBSurface(SDL_HWSURFACE, TAILLE_CASE, 1, 32, 0, 0, 0, 0);
  for(int i = 1; i < NB_PIECES + 1; i++){
    SDL_BlitSurface(cases[9], NULL, cases[i], &pos);
    SDL_BlitSurface(cases[10], NULL, cases[i], &pos);
    SDL_BlitSurface(cases[9], NULL, cases[i], &posit);
    SDL_BlitSurface(cases[10], NULL, cases[i], &posi);
    SDL_Flip(cases[i]);
  }
}

void init_plateau(int tab[][NB_COLONNES]){
  for(int i = 0; i < NB_LIGNES; i++){
    for(int j = 0; j < NB_COLONNES; j++){
      tab[i][j] = 0;
    }
  }
}

int deplacement_possible(int tab[][NB_COLONNES], Piece *piece, int direction){
  int indice_ligne = piece->posY;
  for(int i = 0; i < TAILLE_PIECE; i++){
    int indice_colonne = piece->posX;
    for(int j = 0; j < TAILLE_PIECE; j++){
      if(piece->mat_piece[i][j]) //Si on a une pièce ou non
	if(tab[indice_ligne][indice_colonne + direction] || indice_colonne + direction >= NB_COLONNES || indice_colonne + direction < 0)//S'il y a une pièce qui gène ou qu'elle sort de la grille
	  return(0);
      indice_colonne ++;
    }
    indice_ligne ++;
  }
  return(1);
}

int arret_defilement(int tab[][NB_COLONNES], Piece *piece){
  int indice_ligne = piece->posY;
  int indice_colonne;
  for(int i = 0; i < TAILLE_PIECE; i++){
    indice_colonne = piece->posX;
    for(int j = 0; j < TAILLE_PIECE; j++){
      if(piece->mat_piece[i][j]) //Si on a une pièce ou non
	if(tab[indice_ligne + 1][indice_colonne] || indice_ligne + 1 >= NB_LIGNES)//S'il y a une pièce qui gène ou qu'elle sort de la grille
	  return(1);
      indice_colonne ++;
    }
    indice_ligne ++;
  }  
  return(0);  
}

int rotation_possible_droite(int tab[][NB_COLONNES], Piece *piece){
  int mat[TAILLE_PIECE][TAILLE_PIECE];
  int indice_ligne = piece->posY;
  int indice_colonne;
  for(int i = 0; i < TAILLE_PIECE; i++)
    for(int j = 0; j < TAILLE_PIECE; j++)
      mat[i][j] = piece->mat_piece[TAILLE_PIECE - 1 - j][i];
  for(int i = 0; i < TAILLE_PIECE; i++){
    indice_colonne = piece->posX;
    for(int j = 0; j < TAILLE_PIECE; j++){
      if(mat[i][j])
	if(tab[indice_ligne][indice_colonne] || indice_colonne >= NB_COLONNES || indice_colonne < 0)
	  return(0);
      indice_colonne ++;
    }
    indice_ligne ++;
  }
  return(1);
}

void effectue_rotation_droite(Piece *piece){
  int mat[TAILLE_PIECE][TAILLE_PIECE];
  for(int i = 0; i < TAILLE_PIECE; i++)
    for(int j = 0; j < TAILLE_PIECE; j++)
      mat[i][j] = piece->mat_piece[TAILLE_PIECE - 1 - j][i];
  copie_mat(mat, piece->mat_piece);	
}

int rotation_possible_gauche(int tab[][NB_COLONNES], Piece *piece){
  int mat[TAILLE_PIECE][TAILLE_PIECE];
  int indice_ligne = piece->posY;
  int indice_colonne;
  for(int i = 0; i < TAILLE_PIECE; i++)
    for(int j = 0; j < TAILLE_PIECE; j++)
      mat[i][j] = piece->mat_piece[j][TAILLE_PIECE - 1 - i];
  for(int i = 0; i < TAILLE_PIECE; i++){
    indice_colonne = piece->posX;
    for(int j = 0; j < TAILLE_PIECE; j++){
      if(mat[i][j])
	if(tab[indice_ligne][indice_colonne] || indice_colonne >= NB_COLONNES || indice_colonne < 0)
	  return(0);
      indice_colonne ++;
    }
    indice_ligne ++;
  }
  return(1);
}

void effectue_rotation_gauche(Piece *piece){
  int mat[TAILLE_PIECE][TAILLE_PIECE];
  for(int i = 0; i < TAILLE_PIECE; i++)
    for(int j = 0; j < TAILLE_PIECE; j++)
     mat[i][j] = piece->mat_piece[j][TAILLE_PIECE - 1 - i];
  copie_mat(mat, piece->mat_piece);	
}

void afficher_plateau(int tab[][NB_COLONNES], SDL_Surface *ecran, SDL_Surface *cases[]){
  SDL_Rect position;
  for(int i = 0; i < NB_LIGNES; i++){
    for(int j = 0; j < NB_COLONNES; j++){
      position.x = j * TAILLE_CASE + 5;
      position.y = i * TAILLE_CASE;
      SDL_BlitSurface(cases[tab[i][j]], NULL, ecran, &position);
    }
  }
}

void descendre_ligne(int ligne_dep, int tab[][NB_COLONNES], SDL_Surface *ecran, SDL_Surface *cases[]){
  for(int i = 0; i < NB_COLONNES; i++)
    tab[ligne_dep][i] = 0;
  for(int i = ligne_dep; i > 0; i--)
    for(int j = 0; j < NB_COLONNES; j++){
      tab[i][j] = tab[i - 1][j];
    }
}

void afficher_anim(SDL_Surface *ecran, int ligne, SDL_Surface *cases[]){
  SDL_Surface *anim = IMG_Load("icone_etoile1.png");
  SDL_Rect pos;
  pos.y = ligne * TAILLE_CASE;
  pos.x = 5;
  for(int i = 0; i < NB_COLONNES; i++){
    SDL_BlitSurface(cases[0], NULL, ecran, &pos);
    SDL_BlitSurface(anim, NULL, ecran, &pos);
    SDL_Flip(ecran);
    SDL_BlitSurface(cases[0], NULL, ecran, &pos);
    pos.x += TAILLE_CASE;
  }
}

int supprimer_ligne_complete(int tab[][NB_COLONNES], SDL_Surface *ecran, SDL_Surface *cases[], int mode){
  int nb_ligne = 0;
  int somme = 0;
  for(int i = NB_LIGNES - 1; i >= 0; i--){
    for(int j = 0; j < NB_COLONNES; j++){
      if(tab[i][j])
	somme ++;
    }
    if(somme == NB_COLONNES){
      if(mode == 1)
	afficher_anim(ecran, i, cases);
      descendre_ligne(i, tab, ecran, cases);
      if(mode == 1)
	afficher_plateau(tab, ecran, cases);
      i ++;
      nb_ligne ++;
    }
    somme = 0;
  }
  return(nb_ligne);
}

void placer_piece(int tab[][NB_COLONNES], Piece piece){
  for(int i = 0; i < TAILLE_PIECE; i++)
    for(int j = 0; j < TAILLE_PIECE; j++)
      if(piece.mat_piece[i][j])
	tab[piece.posY + i][piece.posX + j] = piece.mat_piece[i][j];
}

void afficher_piece(Piece piece, int tab[][NB_COLONNES], SDL_Surface *ecran, SDL_Surface *cases[]){
  SDL_Rect position;
  for(int i = 0; i < TAILLE_PIECE; i++)
    for(int j = 0; j < TAILLE_PIECE; j++){
      position.x = (piece.posX + j) * TAILLE_CASE + 5;
      position.y = (piece.posY + i) * TAILLE_CASE;
      if(position.x <= 305){
	if(piece.mat_piece[i][j]){
	  SDL_BlitSurface(cases[piece.mat_piece[i][j]], NULL, ecran, &position);
	}
      }
      else
	if(piece.posY + i < NB_LIGNES && piece.posX + j < NB_COLONNES && piece.posX + j >= 0)
	  SDL_BlitSurface(cases[tab[piece.posY + i][piece.posX + j]], NULL, ecran, &position);
    }
}

void enlever_piece(Piece piece, int tab[][NB_COLONNES], SDL_Surface *ecran, SDL_Surface *cases[]){
  SDL_Rect position;
  for(int i = 0; i < TAILLE_PIECE; i++)
    for(int j = 0; j < TAILLE_PIECE; j++){
      position.x = (piece.posX + j) * TAILLE_CASE + 5;
      position.y = (piece.posY + i) * TAILLE_CASE;
      if(piece.posY + i < NB_LIGNES && piece.posX + j < NB_COLONNES && piece.posY + i >= 0 && piece.posX + j >= 0)
	SDL_BlitSurface(cases[tab[piece.posY + i][piece.posX + j]], NULL, ecran, &position);
    }
}

void afficher_nouvelle_piece(int piece_suivante, SDL_Surface *ecran, SDL_Surface *cases[]){
  SDL_Rect position;
  Piece piece;
  init_piece(&piece, piece_suivante);
  position.y = 50;
  position.x = 350;
  for(int i = 0; i < TAILLE_PIECE; i++){
    for(int j = 0; j < TAILLE_PIECE; j++){
      position.x = j * TAILLE_CASE + 355;
      position.y = i * TAILLE_CASE + 50;
      if(piece.mat_piece[i][j])
	SDL_BlitSurface(cases[piece.mat_piece[i][j]], NULL, ecran, &position);
      else
	SDL_BlitSurface(cases[8], NULL, ecran, &position);
    }
  }
}

void libere_surface(SDL_Surface *cases[]){
  for(int i = 0; i < NB_PIECES + 4; i++)
    SDL_FreeSurface(cases[i]);
}

void afficher_score(int score, int level, int lines, SDL_Surface *ecran){
  SDL_Surface *texte = NULL, *carre_blanc = NULL;
  SDL_Rect position;
  SDL_Color couleurnoir = {0, 0, 0};
  TTF_Font *police = NULL;
  char c[20];
  carre_blanc = SDL_CreateRGBSurface(SDL_HWSURFACE, 170, 250, 32, 0, 0, 0, 0);
  SDL_FillRect(carre_blanc, NULL, SDL_MapRGB(carre_blanc->format, 255, 255, 255));
  police = TTF_OpenFont(CHEMIN_POLICE, 40);
  position.x = 430;
  position.y = 200;
  SDL_BlitSurface(carre_blanc, NULL, ecran, &position);
  itoa(level, c);
  texte = TTF_RenderText_Blended(police, c, couleurnoir);
  SDL_BlitSurface(texte, NULL, ecran, &position);
  position.y = 300;
  itoa(score, c);
  texte = TTF_RenderText_Blended(police, c, couleurnoir);
  SDL_BlitSurface(texte, NULL, ecran, &position);
  position.y = 400;
  itoa(lines, c);
  texte = TTF_RenderText_Blended(police, c, couleurnoir);
  SDL_BlitSurface(texte, NULL, ecran, &position);
  TTF_CloseFont(police);
  SDL_FreeSurface(texte);
  SDL_FreeSurface(carre_blanc);
}

void afficher_temps(int times, SDL_Surface *ecran, int mode){
  SDL_Surface *texte = NULL, *carre_blanc = NULL, *barre = NULL, *tourhtps = NULL, *tourvtps = NULL, *tourblanc = NULL;
  SDL_Rect position, postourtps;
  SDL_Color couleurnoir = {0, 0, 0};
  TTF_Font *police = NULL;
  int minutes = 0;
  int tim;
  char time[20];
  char seconde[20];
  position.x = 430;
  position.y = 500;
  carre_blanc = SDL_CreateRGBSurface(SDL_HWSURFACE, 170, 50, 32, 0, 0, 0, 0);
  SDL_FillRect(carre_blanc, NULL, SDL_MapRGB(carre_blanc->format, 255, 255, 255));
  SDL_BlitSurface(carre_blanc, NULL, ecran, &position);
  police = TTF_OpenFont(CHEMIN_POLICE, 40);
  if(mode == 1){
    minutes = times / 60;
    itoa(minutes, time);
    itoa(times - (minutes * 60), seconde);
    strcat(time, ":");
    if(times - (minutes * 60) < 10)
      strcat(time, "0");
    strcat(time, seconde);
  }
  else{
    tim = 120 - times;
    minutes = tim / 60;
    itoa(minutes, time);
    itoa(tim - (minutes * 60), seconde);
    strcat(time, ":");
    if(tim - (minutes * 60) < 10)
      strcat(time, "0");
    strcat(time, seconde);
    tourblanc = SDL_CreateRGBSurface(SDL_HWSURFACE, 250, 11, 32, 0, 0, 0, 0);
    SDL_FillRect(tourblanc, NULL, SDL_MapRGB(tourblanc->format, 255, 255, 255));
    barre = SDL_CreateRGBSurface(SDL_HWSURFACE, (tim * 2) + 1, 11, 32, 0, 0, 0, 0);
    tourhtps = SDL_CreateRGBSurface(SDL_HWSURFACE, 240, 1, 32, 0, 0, 0, 0);
    tourvtps = SDL_CreateRGBSurface(SDL_HWSURFACE, 1, 10, 32, 0, 0, 0, 0);
    SDL_FillRect(barre, NULL, SDL_MapRGB(barre->format, 135, 206, 250));
    postourtps.x = 320;
    postourtps.y = 560;
    SDL_BlitSurface(tourblanc, NULL, ecran, &postourtps);
    SDL_BlitSurface(barre, NULL, ecran, &postourtps);
    SDL_BlitSurface(tourvtps, NULL, ecran, &postourtps);
    SDL_BlitSurface(tourhtps, NULL, ecran, &postourtps);
    postourtps.x = 560;
    SDL_BlitSurface(tourvtps, NULL, ecran, &postourtps);
    postourtps.x = 320;
    postourtps.y = 570;
    SDL_BlitSurface(tourhtps, NULL, ecran, &postourtps);
    SDL_Flip(barre);
  }
  texte = TTF_RenderText_Blended(police, time, couleurnoir);
  SDL_BlitSurface(texte, NULL, ecran, &position);
  TTF_CloseFont(police);
  SDL_FreeSurface(texte);
  SDL_FreeSurface(carre_blanc);
  SDL_FreeSurface(barre);
  SDL_FreeSurface(tourblanc);
  SDL_FreeSurface(tourhtps);
  SDL_FreeSurface(tourvtps);
}

int pos_appartient(SDL_Rect pos, SDL_Rect tab[]){
  for(int i = 0; i < 4; i++)
    if(pos.x == tab[i].x && pos.y == tab[i].y)
      return(1);
  return(0);
}

void afficher_piece_fantome(Piece piece, int tab[][NB_COLONNES], SDL_Surface *ecran){
  SDL_Rect pos = {0, 0}, posi = {0, TAILLE_CASE - 1}, posit = {TAILLE_CASE - 1, 0}, po, tab_po[4];
  SDL_Surface *contour = SDL_CreateRGBSurface(SDL_HWSURFACE, TAILLE_CASE, TAILLE_CASE, 32, 0, 0, 0, 0), *bv = SDL_CreateRGBSurface(SDL_HWSURFACE, TAILLE_CASE, 1, 32, 0, 0, 0, 0), *bh = SDL_CreateRGBSurface(SDL_HWSURFACE, 1, TAILLE_CASE, 32, 0, 0, 0, 0);
  int indice = 0;
  for(int i = 0; i < TAILLE_PIECE; i++){
    for(int j = 0; j < TAILLE_PIECE; j++){
      if(piece.mat_piece[i][j]){
	po.x = (piece.posX + j) * TAILLE_CASE + 5;
	po.y = (piece.posY + i) * TAILLE_CASE;
	tab_po[indice].x = po.x;
	tab_po[indice].y = po.y;
	indice ++;
      }
    }
  }	
  SDL_FillRect(bh, NULL, SDL_MapRGB(bh->format, 255, 255, 255));
  SDL_FillRect(bv, NULL, SDL_MapRGB(bv->format, 255, 255, 255));
  SDL_BlitSurface(bh, NULL, contour, &pos);
  SDL_BlitSurface(bv, NULL, contour, &pos);
  SDL_BlitSurface(bv, NULL, contour, &posi);
  SDL_BlitSurface(bh, NULL, contour, &posit);
  SDL_Flip(contour);
  while(!arret_defilement(tab, &piece))
    piece.posY ++;
  for(int i = 0; i < TAILLE_PIECE; i++){
    for(int j = 0; j < TAILLE_PIECE; j++){
      if(piece.mat_piece[i][j]){
	po.x = (piece.posX + j) * TAILLE_CASE + 5;
	po.y = (piece.posY + i) * TAILLE_CASE;
	if(!pos_appartient(po, tab_po))
	  SDL_BlitSurface(contour, NULL, ecran, &po);
      }
    }
  }
  SDL_Flip(ecran);
}

int tetris(SDL_Surface *ecran, int piece_fantome, int gravite){
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
  int tab[NB_LIGNES][NB_COLONNES];
  int grav[NB_LIGNES][NB_COLONNES];
  int score = 0;
  int level = 1;
  int nbline = 0;
  int line = 0;
  int timer;
  int tps = 0;
  int lines;
  int numero_piece_act = 0;
  init_cases_couleur(cases);
  init_plateau(tab);
  init_plateau(grav);
  init_jeu(ecran, cases, &level, 1);
  SDL_EnableKeyRepeat(75, 75);
  timer = SDL_GetTicks();
  while(continuer){
    init_piece(&piece, piece_suivante);
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
    while(!piece_stope){
      if(level < 10)
	if(nbline >= level * 10)
	  level ++;
      temps_act = SDL_GetTicks();
      if(temps_act - timer > 1000){//Temps qui passe
	timer = temps_act;
	tps ++;
	afficher_temps(tps, ecran, 1);
	}
      if((temps_act - temps_prec) > (600 - level*50)){//Chute piece
	if(arret_defilement(tab, &piece)){//Bloque
	  placer_piece(tab, piece);
	  piece_stope = 1;
	  line = supprimer_ligne_complete(tab, ecran, cases, 1);
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
	  score += line * level * (50 * line);
	  nbline += line;
	  afficher_plateau(tab, ecran, cases);
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
	afficher_score(score, level, nbline, ecran);
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
	      if(piece_fantome)
		afficher_plateau(tab, ecran, cases);
	      enlever_piece(piece, tab, ecran, cases);
	      effectue_rotation_gauche(&piece);
	      afficher_piece(piece, tab, ecran, cases);
	      if(piece_fantome)
		afficher_piece_fantome(piece, tab, ecran);
	    }
	    break;
	  case SDLK_SPACE:
	    if(arret_defilement(tab, &piece)){
	      placer_piece(tab, piece);
	      piece_stope = 1;
	      line = supprimer_ligne_complete(tab, ecran, cases, 1);
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
	      score += line * level * (50 * line);
	      nbline += line;
	      afficher_plateau(tab, ecran, cases);
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
	    score += line * level * (50 * line);
	    nbline += line;
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

	   
  
