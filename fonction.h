#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

typedef struct Joueur Joueur;
struct Joueur{
    int x;
    int y;
    int perdu;
    int graphrouge;
    int graphbleu;
    int graphvert;
};


void afficheplateau(char** plateau, int taille);
void init(char** plateau, int taille);
char* geneligne(int taille);
void coordonnees(char* chaineentree, int* x, int* y);
void positionnement(char** plateau,int x,int y, int typecoup);
int deplacementvalide(char** plateau,int taille, int xnouveau, int ynouveau, int x, int y);
void deplacement(char** plateau, int *x, int *y, int taille, int joueurjouant, int xnouveau, int ynouveau);
int agagne(char** plateau,int taille, int xjoueur, int yjoueur, int joueurjouant, Joueur* tableaujoueur);
int finjeux(Joueur* tableaujoueur, int nbjoueur);
void positionnementcasenoire(char** plateau, int taille,SDL_Surface *ecran, SDL_Rect position);
void liberematrice(char **plateau, int taille);
void placementIA(char** plateau, int taille, int numerosbot, Joueur* tableaujoueur, int nbjoueur);
int regard(char** plateau, int taille, int x, int y);
void deplacementIA(char** plateau, int taille, int x, int y, int botjouant, Joueur* tableaujoueur, int nbjoueur);
void placementnoirIA(char** plateau, int taille, Joueur* tableaujoueur, int botjouant, int nbjoueur);
void videtableau(Joueur* tab, int taille);
void pause2();
void affichegraphique(SDL_Surface *ecran, int taille, SDL_Rect position, char** plateau,SDL_Surface ** rectangle2, Joueur* tableaujoueur, int joueurjouant);
void ecouteurpositioninit(int *x, int *y, int taille, SDL_Surface *ecran, SDL_Rect position, char** plateau);
int choixmenu(SDL_Surface *ecran, SDL_Rect position, char tableautexte[1], int hauteur);