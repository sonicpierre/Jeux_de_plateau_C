#include"fonction.h"

int main()
{
//------------------------------------------------------------------------TRAVAIL GRAPHIQUE SOLINA------------------------------------------------------
int choixfinal=0;

while(choixfinal!=1){

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    TTF_Init();
    Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );
    SDL_Surface *ecran2 = NULL;                  //On déclare l'espace sur l'écran à allouer pour le jeu
    SDL_Surface *ecran = NULL;                  //On déclare l'espace sur l'écran à allouer pour le jeu
    SDL_Surface *imagefond= NULL;
    //SDL_Surface *personnage= NULL;
    SDL_Surface *text= NULL;
    //SDL_Event event;
    SDL_Surface *rectangle[100]= {NULL};        //On déclare le tableau de rectangles à coller
    SDL_Surface *rectangle3;
    SDL_Rect position;
    SDL_Rect positionimage;
    //SDL_Rect positionperso;
    SDL_Rect positiontext;
    TTF_Font *police = NULL;
    SDL_Color couleurNoire = {158, 14, 64,45};
    Mix_Music *music = NULL;
    Mix_Chunk *placementcorrect = NULL;
    Mix_Chunk *placementincorrect = NULL;



//-------------------------------------------------------------------------TRAVAIL ALGO SOLINA-------------------------------------------------------------
    
    placementcorrect = Mix_LoadWAV( "music/placementcorrect.wav" );
    placementincorrect = Mix_LoadWAV( "music/mauvaisplacement.wav" );
    int taille;
    int x=0;
    int y=1;
    //char entrejouer[3];
    int nbjoueur;
    Joueur* tableaujoueur;
    int joueurhumain;
    char tableautext[1];
    char textefin[50];
    srand(time(NULL));

    SDL_WM_SetIcon(IMG_Load("image/logo.jpg"), NULL);               //On définit le logo de notre jeux
    ecran2 = SDL_SetVideoMode(700, 700, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("menu", NULL);
    SDL_FillRect(ecran2, NULL, SDL_MapRGB(ecran2->format, 0, 0, 102));

    music = Mix_LoadMUS( "music/musicmenu.mp3" );

    //On lance la musique
    Mix_PlayMusic( music, -1 );
    positiontext.x=260;
    positiontext.y=50;
    police = TTF_OpenFont("police/Menu.ttf", 65);
    text = TTF_RenderText_Blended(police, "Solina", couleurNoire);
    SDL_BlitSurface(text, NULL, ecran2, &positiontext); // Blit du texte
    police = TTF_OpenFont("police/options.ttf", 28);
    text = TTF_RenderText_Blended(police, "Quel sera la taille de votre plateau ?", couleurNoire);
    positiontext.x=10;
    positiontext.y=150;
    SDL_BlitSurface(text, NULL, ecran2, &positiontext); // Blit du texte

    taille=choixmenu(ecran2,position,tableautext,150);
    SDL_Flip(ecran2);

    text = TTF_RenderText_Blended(police, "Combien de joueurs ?", couleurNoire);
    positiontext.x=10;
    positiontext.y=300;
    SDL_BlitSurface(text, NULL, ecran2, &positiontext); // Blit du texte
    nbjoueur=choixmenu(ecran2,position,tableautext,300);
    SDL_Flip(ecran2);
    positiontext.x=10;
    positiontext.y=450;
    text = TTF_RenderText_Blended(police, "Combien humains ?", couleurNoire);
    SDL_BlitSurface(text, NULL, ecran2, &positiontext); // Blit du texte
    joueurhumain=choixmenu(ecran2,position,tableautext,450);
    SDL_Flip(ecran2);

    TTF_CloseFont(police); // Doit être avant TTF_Quit() 
    SDL_FreeSurface(text);
    Mix_FreeMusic( music );
    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    TTF_Init();
    Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );

    music = Mix_LoadMUS( "music/musiqueambiance.mp3" );
    Mix_PlayMusic( music, -1 );
    tableaujoueur=(Joueur*) malloc(nbjoueur*sizeof(Joueur));

    char **plateau=(char**) malloc(taille*sizeof(char*));
    for (int i=0;i<taille;i++)
    {
        plateau[i]=(char*) malloc((taille+1)*sizeof(char*));
        plateau[i]=NULL;
    }
    
    init(plateau,taille);
    afficheplateau(plateau,taille);

    ecran = SDL_SetVideoMode(1000, 1000, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);        //On fixe la taille de la fenêtre de départ et après on fait varier la taille des cases après
    imagefond = IMG_Load("image/imagedefond.jpg");
    SDL_WM_SetCaption("Solina", NULL);
    positionimage.x=0;
    positionimage.y=0;
    SDL_BlitSurface(imagefond, NULL, ecran, &positionimage);          //On colle les surfaces créent
    affichegraphique(ecran, taille, position,plateau,rectangle,tableaujoueur,0);
    SDL_Flip(ecran);


    for(int i=1;i!=joueurhumain+1;i++){
        tableaujoueur[i-1].graphrouge=rand()%200+30;
        tableaujoueur[i-1].graphbleu=rand()%200+30;
        tableaujoueur[i-1].graphvert=rand()%200+30;
        y=1;
        x=0;
        printf("Où voulez vous jouer joueur %d ?",i);
        //scanf("%s",entrejouer);
        //coordonnees(entrejouer,&x,&y);
        ecouteurpositioninit(&x,&y,taille,ecran,position,plateau);
        printf("x=%d et y=%d",x,y);
        tableaujoueur[i-1].x=x;
        tableaujoueur[i-1].y=y;
        tableaujoueur[i-1].perdu=0;
        positionnement(plateau,x,y,i);
        afficheplateau(plateau,taille);
        affichegraphique(ecran, taille, position,plateau,rectangle,tableaujoueur, i);
    }

    for(int i=joueurhumain+1; i!=nbjoueur+1; i++){
        tableaujoueur[i-1].graphrouge=rand()%255+1;         //On fait prendre des couleurs pour chaque joueur différent
        tableaujoueur[i-1].graphbleu=rand()%255+1;
        tableaujoueur[i-1].graphvert=rand()%255+1;
        placementIA(plateau,taille,i,tableaujoueur,nbjoueur);
        afficheplateau(plateau, taille);
        affichegraphique(ecran, taille, position,plateau,rectangle,tableaujoueur, i);
        SDL_Flip(ecran);
    }

    int i=0;
    while(finjeux(tableaujoueur,nbjoueur)==1){
        i=(i%nbjoueur)+1;
        if((tableaujoueur[i-1].perdu!=1)&&(i<joueurhumain+1)){
            do{
                y=1;
                x=0;
                printf("Où voulez vous vous déplacer joueur %d ?",i);
                ecouteurpositioninit(&x,&y,taille,ecran,position,plateau);
                
                if(((abs(tableaujoueur[i-1].x-x)!=1)&&(abs(tableaujoueur[i-1].x-x)!=0))||((abs(tableaujoueur[i-1].y-y)!=1)&&(abs(tableaujoueur[i-1].y-y)!=0))){
                    rectangle3 = SDL_CreateRGBSurface(SDL_HWSURFACE, 1000/(taille+2), 1000/(taille+2), 32, 0, 0, 0, 0);
                    position.y=(1000/(taille+2))*(x+1)+10*(x);
                    position.x=(1000/(taille+2))*y+10*(y-1);
                    SDL_FillRect(rectangle3, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
                    SDL_BlitSurface(rectangle3, NULL, ecran, &position);
                    Mix_PlayChannel( -1, placementincorrect, 0 ); //On va jouer le son à chaque placement incorrect
                }
            
            printf("%d %d\n",tableaujoueur[i-1].x-x,tableaujoueur[i-1].y-y);
            }while(((abs(tableaujoueur[i-1].x-x)!=1)&&(abs(tableaujoueur[i-1].x-x)!=0))||((abs(tableaujoueur[i-1].y-y)!=1)&&(abs(tableaujoueur[i-1].y-y)!=0)));
            Mix_PlayChannel( -1, placementcorrect, 0 ); //On va jouer le son à chaque placement correct
            deplacement(plateau,&tableaujoueur[i-1].x,&tableaujoueur[i-1].y,taille,i,x,y);
            tableaujoueur[i-1].x=x;
            tableaujoueur[i-1].y=y;
            afficheplateau(plateau,taille);
            affichegraphique(ecran, taille, position,plateau,rectangle,tableaujoueur, i);
            SDL_Flip(ecran);
            printf("Où voulez-vous placer votre case noire joueur %d ? \n",i);
            //scanf("%s",entrejouer);
            positionnementcasenoire(plateau, taille,ecran,position);
            afficheplateau(plateau,taille);
            affichegraphique(ecran, taille, position,plateau,rectangle,tableaujoueur, i);
            SDL_Flip(ecran);
            for(int i=1; i!=nbjoueur+1; i++){
                agagne(plateau,taille,tableaujoueur[i-1].x,tableaujoueur[i-1].y,i,tableaujoueur);
            }
        }

        else if((tableaujoueur[i-1].perdu!=1)&&(i>joueurhumain)){
            deplacementIA(plateau,taille,tableaujoueur[i-1].x,tableaujoueur[i-1].y,i,tableaujoueur, nbjoueur);
            placementnoirIA(plateau,taille,tableaujoueur,i,nbjoueur);
            afficheplateau(plateau,taille);
            affichegraphique(ecran,taille,position,plateau,rectangle,tableaujoueur,i);
            SDL_Flip(ecran);
            sleep(1);
            for(int i=1; i!=nbjoueur+1; i++){
                agagne(plateau,taille,tableaujoueur[i-1].x,tableaujoueur[i-1].y,i,tableaujoueur);
            }
        }
    }
    int choix=1;
    for(int i=0; i!=nbjoueur; i++){
        if(tableaujoueur[i].perdu==0){
            sprintf(textefin,"Le  joueur  %d  a  gagne",choix);
            break;
        }
        choix++;
    }
    if(choix==nbjoueur-1){
        sprintf(textefin,"Il y a egalite");
    }
    
    positiontext.x=170;
    positiontext.y=15;
    police = TTF_OpenFont("police/textefin.ttf", 65);
    SDL_Color couleur = {158, 150, 0,0};
    text = TTF_RenderText_Blended(police, textefin, couleur);
    SDL_BlitSurface(text, NULL, ecran, &positiontext); // Blit du texte
    SDL_Flip(ecran);
    pause2();

    free(tableaujoueur);
        liberematrice(plateau,taille);
    for(int i=0; i!=100; i++){
        SDL_FreeSurface(rectangle[i]);
    }
    TTF_CloseFont(police); // Doit être avant TTF_Quit() 
    SDL_FreeSurface(text);
    Mix_FreeChunk( placementcorrect );
    Mix_FreeChunk( placementincorrect );
    Mix_FreeMusic( music );
    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();

    printf("Voulez-vous rejouer ? 0 pour oui et 1 pour non\n");
    scanf("%d",&choixfinal);
}

    return 0;
}
