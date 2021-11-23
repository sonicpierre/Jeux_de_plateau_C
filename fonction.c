#include"fonction.h"


/**
 * \file fonction.c
 * \brief Recense toutes les fonctions utiles au jeux Solina
 * \author Virgaux Pierre
 * \version 0.1
 * \date Lundi 16 Decembre 2019
 */



/**
 * \fn char* geneligne(int taille)
 * \brief Permet d'initialiser les lignes qui composeront le tableau
 * \param taille donne la taille et par conséquent le nombre de lignes à générer
 * \return Les lignes de caractère crééent qui composeront le tableau
 */


char* geneligne(int taille){
    char *ligne=(char*)malloc((taille*2+1)*sizeof(char));
    for(int i=0; i!=taille*2+4; i++){
        ligne[i]=' ';           //On initialise le tableau comme on la juste alloué
    }

    for(int i=0; i<=taille*2; i++){
        if(i%2==0){
            ligne[i]='|';           //corespond aux séparateurs
        }
        else{
            ligne[i]='_';               //corespond à chacunes des cases
        }
    }
    return ligne;
}



/**
 * \fn void afficheplateau(char** plateau, int taille)
 * \brief Permet d'initialiser un plateau
 * \param taille donne la taille et par conséquent le nombre de lignes à insérer dans le plateau
 * \return Rien, mais à changer la valeur du tableau
 */

void init(char** plateau, int taille){
    for(int i=0; i<taille; i++){
        plateau[i]=geneligne(taille);
    }
}

/**
 * \fn void afficheplateau(char** plateau, int taille)
 * \brief Permet d'afficher le plateau
 * \param taille donne la taille et par conséquent le nombre de lignes à afficher
 * \param plateau donne le plateau à afficher
 * \return Rien, mais à afficher le plateau
 */


void afficheplateau(char** plateau, int taille){
    system("clear");                                //Nettoie l'affichage du terminal
    printf("\n");
    printf("%c",' ');
    for(int i=0; i<(taille*2); i++){            //affiche les chifres de la première ligne
        if(i%2==0){                    
            printf("%c",' ');
        }
        if(i%2==1){
            printf("%d",(i/2)+1);
        }
    }
    printf("\n");
    for(int i=0; i<taille; i++){                //affiche les lettres correspondantes à chacunes des lignes
        printf("%c",65+i);
        printf("%s",plateau[i]);
        printf("\n");
    }
}

/**
 * \fn void coordonnees(char* chaineentree, int* x, int* y)
 * \brief Permet de transcrire la chaine de caractères rentrés en coordonnées entières
 * \param chaineentree permet de récupérer la chaine entré par l'utilisateur
 * \param x donne la coordonnée x à modifier
 * \param y donne la coordonnée y à modifier
 * \return Rien, mais à changé les valeurs de x et y
 */


void coordonnees(char* chaineentree, int* x, int* y){
    if(strlen(chaineentree)!=2){
        printf("Votre entrez n'est pas valide recommencez\n");
    }
    else{
        *x=toupper(chaineentree[0])-65;         //correspond au caractère de la table ASCII de A=65
        *y=chaineentree[1]-48;                  //correspond au caractère de la table ASCII de 1=49
    }
}

/**
 * \fn void positionnement(char** plateau,int x,int y, int typecoup)
 * \brief Permet de positionner le coup dans le plateau
 * \param plateau donne le plateau à modifier
 * \param typecoup permet de savoir comment modifier le tableau en connaissant le type de coup ou le joueurjouant
 * \param x donne la coordonnée x à modifier
 * \param y donne la coordonnée y à modifier
 * \return Rien, mais à changé les valeurs de x et y
 */


void positionnement(char** plateau,int x,int y, int typecoup){              //joueur 1 : 1  joueur2 : 2 casenoire : 3
    char* table=malloc(sizeof(char));
    sprintf(table,"%d",typecoup);           //permet de rentrer dans une chaîne de caractère un entier
    if(typecoup<10){
        y=(y*2)-1;
        if(plateau[x][y]!='X'){
            plateau[x][y]=table[0];
        }
    }
    if(typecoup==11){               //permettra de faire avancer le perso
        y=(y*2)-1;
        plateau[x][y]='_';
    }
    free(table);                    //on libère le tableau
}

/**
 * \fn int deplacementvalide(char** plateau,int taille, int xnouveau, int ynouveau, int x, int y)
 * \brief Permet de savoir si un déplacement est possible
 * \param plateau donne le plateau à modifier
 * \param taille correspond à la taille du plateau
 * \param x donne la coordonnée x 
 * \param y donne la coordonnée y
 * \param xnouveau donne la coordonnée x à modifier
 * \param ynouveau donne la coordonnée y à modifier
 * \return Un entier 1 si c'est ok et 0 sinon
 */


int deplacementvalide(char** plateau,int taille, int xnouveau, int ynouveau, int x, int y){

    //printf("xnouv = %d, ynouveau = %d, x=%d, y=%d", xnouveau, ynouveau, x,y);

    if((xnouveau<0)||(ynouveau<1)||(xnouveau>taille)||(ynouveau>taille+1)){                     //Hors limite
        //printf("Hors limite 1\n");
        return 0;
    }
    else if((xnouveau+x>2*taille-2)||(ynouveau+y>2*taille)){                                    //Hors limite
       //printf("Hors limite 2\n");
        return 0;
    }
    else if(plateau[xnouveau][(ynouveau*2)-1]=='_'){                                            //Permet de savoir si la case est pas déjà occupé
        //printf("C'est libre !!\n");
        return 1;
    }
    else{
        //printf("C'est occupé \n");
        return 0;
    }
    //printf("C'est bizarre \n");
    return 0;

}

/**
 * \fn void deplacement(char** plateau, int *x, int *y, int taille, int joueurjouant, int xnouveau, int ynouveau)
 * \brief Permet de savoir si un déplacement est possible
 * \param plateau donne le plateau à modifier
 * \param taille correspond à la taille du plateau
 * \param x donne la coordonnée x 
 * \param y donne la coordonnée y
 * \param xnouveau donne la coordonnée x à modifier
 * \param ynouveau donne la coordonnée y à modifier
 * \return Rien mais à changer le plateau et modifie les coordonnées de x et y
 */

void deplacement(char** plateau, int *x, int *y, int taille, int joueurjouant, int xnouveau, int ynouveau){

    if(deplacementvalide(plateau,taille,xnouveau,ynouveau,*x,*y)==1){       //vérifie que le déplacement est valide
    
        positionnement(plateau,xnouveau,ynouveau,joueurjouant);         //positionne le pion en fonction des nouvelles coordonnées
        positionnement(plateau,*x,*y,11);                   //efface son ancienne position

    }
    *x=xnouveau;
    *y=ynouveau;
}

/**
 * \fn void positionnementcasenoire(char** plateau, int taille,SDL_Surface *ecran, SDL_Rect position)
 * \brief Permet de savoir si un déplacement est possible
 * \param plateau donne le plateau à modifier
 * \param taille correspond à la taille du plateau
 * \param ecran correspond à la fenêtre d'affichage
 * \param position corespond à la position du rectangle à coller sur la fenêtre
 * \return Rien mais à modifier l'affichage de l'écran
 */

void positionnementcasenoire(char** plateau, int taille,SDL_Surface *ecran, SDL_Rect position){
    //int x=toupper(entree[0])-65;
    //int y=entree[1]-48;
    int x=0;
    int y=1;
    ecouteurpositioninit(&x,&y,taille,ecran,position,plateau);              //permet de récupérer les mouvements de l'utilisateur et les traduire en coordonnées
    y=(y*2)-1;
    if(plateau[x][y]=='_'){
        printf("Placement valide \n");
        plateau[x][y]='X';                      //On remplace la case pouar une case noire 
    }
    else{
        printf("Placement de case noire invalide");     //Si le placement est invalide c'est la faute du joueur et on passe direct à l'action suivante
                                                        //En réalité graphe à l'interface graphique on rentre jamais dans ce cas
    }
}

/**
 * \fn int agagne(char** plateau,int taille, int xjoueur, int yjoueur,int joueurjouant, Joueur* tableaujoueur)
 * \brief Permet de savoir si un joueur a gagné
 * \param plateau donne le plateau à modifier
 * \param taille correspond à la taille du plateau
 * \param xjoueur correspond à la position x du joueur
 * \param yjoueur correspond à la position y du joueur
 * \param position corespond au rectangle à coller sur la fenêtre
 * \param tableaujoueur correspond au tableau résumant la position et l'état des joueurs 
 * \return Un entier pour savoir si le joueur a gagné ou non
 */

int agagne(char** plateau,int taille, int xjoueur, int yjoueur,int joueurjouant, Joueur* tableaujoueur){
    //On teste toutes les cases autour pour savoir si elles sont libres
    for(int i=xjoueur-1; i!=xjoueur+2; i++){
        for(int j=yjoueur-1; j!=yjoueur+2;j++){
            if(deplacementvalide(plateau,taille,i,j,xjoueur,yjoueur)==1){       //On teste la case pour savoir si elle est libre
                tableaujoueur[joueurjouant-1].perdu=0;              //si elle est libre le joueur n'a pas perdu encore 
                return 0;                   //On sort de la fonction
            }
        }
    }
    tableaujoueur[joueurjouant-1].perdu=1;          //Si on est pas sorti alors ça veut dire que le joueur à perdu on change l'indicateur correspondant
    return 0;
}

/**
 * \fn int finjeux(Joueur* tableaujoueur, int nbjoueur)
 * \brief Permet de savoir si on est arrivé à la fin du jeux
 * \param tableaujoueur donne un tableau de joueur pour savoir les coordonnées x et y de chacuns des joueurs et savoir si ils ont gagné ou perdu
 * \param nbjoueur donne le nombre de joueurs qui jouent
 * \return Un entier qui est égale à 1 si le jeux n'est pas terminé et 0 sinon
 */

int finjeux(Joueur* tableaujoueur, int nbjoueur){
    int compteur=0;
    int agagne;
    for(int i=0; i!=nbjoueur; i++){                     //On regarde combien de joueurs sont encore en jeux
        if(tableaujoueur[i].perdu==1){
            compteur++;
        }
        if(tableaujoueur[i].perdu==0){                  //On récupère le numéro du joueur qui a gagné
            agagne=i+1;
        }
    }
    if(compteur==nbjoueur-1){                           //Si on a plus qu'un seul joueur libre alors il a gagné
        printf("Le joueur %d a gagné\n",agagne);
        return 0;
    }
    if(compteur==nbjoueur){                             //On a le cas où tout le monde a perdu, on a alors égalité
        printf("Il y a égalité !!\n");
        return 0;
    }
    return 1;
}

/**
 * \fn void placementIA(char** plateau, int taille, int numerosbot, Joueur* tableaujoueur, int nbjoueur)
 * \brief Permet à l'ordinateur de placer un pion sur une place non occupé
 * \param plateau donne le plateau à modifier
 * \param taille donne la taille du plateau
 * \param tableaujoueur donne un tableau de joueur pour savoir les coordonnées x et y de chacuns des joueurs et savoir si ils ont gagné ou perdu
 * \param nbjoueur donne le nombre de joueurs qui jouent
 * \param numerosbot donne le numéros du bot à placer
 * \return Rien mais a modifier le plateau
 */

void placementIA(char** plateau, int taille, int numerosbot, Joueur* tableaujoueur, int nbjoueur){
    int x;
    int y;
    int compteur;
    int sauv=0;
    int indice=0;
    Joueur tableau[100];
    if(numerosbot==1){
        do{
        x=rand()%taille;                    //regarde une case aléatoire vide et place le premier pion dedans
        y=rand()%taille+1;
        }while(plateau[x][(y*2)-1]!='_');
    }
    else{                                   //Passe tout les joueurs et regarde autour
        for(int i=0; i!=taille; i++){
            for(int j=1; j!=taille; j++){
                compteur=regard(plateau,taille,i,j);        //On a un compteur pour savoir combien de déplacement seront possible en fonction de chaque case
                if(compteur==sauv){
                    tableau[indice].x=i;                    //On rentre les cases avec le plus grand nombre de possibilités dans un tableau
                    tableau[indice].y=j;
                    indice++;
                }
                else if(compteur>sauv){
                    videtableau(tableau,100);               //On vide le tableau si on trouve une case avec plus de possibilités que celles dans le tableau
                    indice=0;
                    tableau[indice].x=i;                    //On rentre les nouvelles coordonnées
                    tableau[indice].y=j;
                    sauv=compteur;
                }
            }
        }

        int i=0;
        double distance;
        double sauv2=0;
        while((tableau[i].x!=-1)&&(tableau[i].y!=-1)){
            for(int a=0; a!=nbjoueur; a++){                 //On calcule la distance avec les autres joueurs et on se place pour être le plus loin des autres joueurs en gardant beaucoup de possibilités pour bouger 
                if(a!=numerosbot-1){
                    distance=sqrt((pow(tableau[i].x + tableaujoueur[i].x,2))+(pow(tableau[i].y + tableaujoueur[i].y,2))); //On calcule la distance entre les joueurs
                }
                if(distance>sauv2){
                    x=tableau[i].x;
                    y=tableau[i].y;
                    sauv2=distance;
                }
            }
            i++;
        }
    }

    tableaujoueur[numerosbot-1].x=x;
    tableaujoueur[numerosbot-1].y=y;
    tableaujoueur[numerosbot-1].perdu=0;
    positionnement(plateau,x,y,numerosbot);             //On place le pion avec les coordonnées choisies
}

int regard(char** plateau, int taille, int x, int y){
    int compteur=0;
    for(int xnouveau=x-1; xnouveau!=x+2; xnouveau++){
        for(int ynouveau=y-1; ynouveau!=y+2; ynouveau++){
            if(deplacementvalide(plateau,taille,xnouveau,ynouveau,x,y)==1){
                compteur++;
            }
        }
    }
    return compteur;
}

void deplacementIA(char** plateau, int taille, int x, int y, int botjouant, Joueur* tableaujoueur, int nbjoueur){
    int compteurcasevide=0;
    int xsauv;
    int ysauv;
    int indice=0;
    Joueur placementoptimaux[10];
    for(int xnouveau=x-1; xnouveau!=x+2; xnouveau++){                                           //On regarde les cases qui nous donneront le plus de possibilités au tour suivant
        for(int ynouveau=y-1; ynouveau!=y+2; ynouveau++){
            if(compteurcasevide<=regard(plateau,taille,xnouveau,ynouveau)&&(deplacementvalide(plateau,taille,xnouveau,ynouveau,x,y))){
                if(plateau[xnouveau][(ynouveau*2)-1]=='_'){

                    if(compteurcasevide==regard(plateau,taille,xnouveau,ynouveau)){
                        placementoptimaux[indice].x=xnouveau;
                        placementoptimaux[indice].y=ynouveau;
                        compteurcasevide=regard(plateau,taille,xnouveau,ynouveau);
                        indice++;
                    }
                    else if(compteurcasevide<regard(plateau,taille,xnouveau,ynouveau)){
                        indice=0;
                        videtableau(placementoptimaux,10);
                        placementoptimaux[indice].x=xnouveau;
                        placementoptimaux[indice].y=ynouveau;
                        compteurcasevide=regard(plateau,taille,xnouveau,ynouveau);
                    }
                }
            }
        }
    }
    int i=0;
    double distance;
    double sauv=0;
    while((placementoptimaux[i].x!=-1)&&(placementoptimaux[i].y!=-1)){
        for(int a=0; a!=nbjoueur; a++){
            if(a!=botjouant-1){
                distance=sqrt((pow(placementoptimaux[i].x + tableaujoueur[i].x,2))+(pow(placementoptimaux[i].y + tableaujoueur[i].y,2))); //On calcule la distance entre les joueurs
            }
            if(distance>sauv){
                xsauv=placementoptimaux[i].x;
                ysauv=placementoptimaux[i].y;
                sauv=distance;
            }
        }
        i++;
    }
    positionnement(plateau,xsauv,ysauv,botjouant);
    tableaujoueur[botjouant-1].x=xsauv;
    tableaujoueur[botjouant-1].y=ysauv;
    positionnement(plateau,x,y,11);
}

void placementnoirIA(char** plateau, int taille, Joueur* tableaujoueur, int botjouant, int nbjoueur){
    int optimal=0;
    int xsauv=0;
    int ysauv=0;
    int indice=0;
    Joueur tableaualliance[1000]; // On va placer les cases noires pour bloquer le plus possible les joueurs humains
    for(int i=1; i!=nbjoueur+1; i++){
        if(i!=botjouant){
            for(int xnouveau=tableaujoueur[i-1].x-1; xnouveau!=tableaujoueur[i-1].x+2; xnouveau++){
                for(int ynouveau=tableaujoueur[i-1].y-1; ynouveau!=tableaujoueur[i-1].y+2; ynouveau++){
                    if(optimal<=regard(plateau,taille,xnouveau,ynouveau)&&deplacementvalide(plateau,taille,xnouveau,ynouveau,tableaujoueur[i-1].x,tableaujoueur[i-1].y)){
                        if(plateau[xnouveau][(ynouveau*2)-1]=='_'){
                            if(optimal==regard(plateau,taille,xnouveau,ynouveau)){
                                optimal=regard(plateau,taille,xnouveau,ynouveau);
                                tableaualliance[indice].x=xnouveau;
                                tableaualliance[indice].y=ynouveau;
                            }
                            else if(optimal<regard(plateau,taille,xnouveau,ynouveau)){
                                indice=0;
                                videtableau(tableaualliance,1000);
                                tableaualliance[indice].x=xnouveau;
                                tableaualliance[indice].y=ynouveau;
                                optimal=regard(plateau,taille,xnouveau,ynouveau);
                            }
                        }
                    }
                }
            }
        }
    }

    int i=0;
    double distance;
    double sauv=0;
    while((tableaualliance[i].x!=-1)&&(tableaualliance[i].y!=-1)){
        for(int a=0; a!=nbjoueur; a++){
            if(a!=botjouant-1){
                distance=sqrt((pow(tableaualliance[i].x + tableaujoueur[i].x,2))+(pow(tableaualliance[i].y + tableaujoueur[i].y,2))); //On calcule la distance entre les joueurs
            }
            if(distance>sauv){              //On prend la case noire qui va
                xsauv=tableaualliance[i].x;
                ysauv=tableaualliance[i].y;
                sauv=distance;
            }
        }
        i++;
    }

    plateau[xsauv][(ysauv*2)-1]='X';
}

void videtableau(Joueur* tab, int taille){
    for(int i=0; i!=taille; i++){
        tab[i].x=-1;
        tab[i].y=-1;
    }
}


void liberematrice(char **plateau, int taille){
	int i;
	for (i=0;i<taille;i++)
	{
		free(plateau[i]);
	}
	free(plateau);
}

void pause2()
{
    int continuer = 1;
    SDL_Event event;
 
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE: /* Appui sur la touche Echap, on arrête le programme */
                        continuer = 0;
                        break;
                    case SDLK_RETURN:
                        continuer = 0;
                        break;
                    default:
                    break;

                }
            default:
            break;
        }
    }
}

void affichegraphique(SDL_Surface *ecran, int taille, SDL_Rect position, char** plateau,SDL_Surface ** rectangle2, Joueur* tableaujoueur ,int joueurjouant){
    position.x=1000/(taille+2);
    position.y=1000/(taille+2);
    for(int a=0; a!=taille; a++){
        for(int i=1; i!=(taille*2)-1; i++){
            rectangle2[i] = SDL_CreateRGBSurface(SDL_HWSURFACE, 1000/(taille+2), 1000/(taille+2), 32, 0, 0, 0, 0);
            if(plateau[a][(i*2)-1]=='X'){
                SDL_FillRect(rectangle2[i], NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
                SDL_BlitSurface(rectangle2[i], NULL, ecran, &position);
            }
            else if(plateau[a][(i*2)-1]=='_'){
                SDL_FillRect(rectangle2[i], NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
                SDL_BlitSurface(rectangle2[i], NULL, ecran, &position);
            }
            else if((plateau[a][(i*2)-1]>48)&&(plateau[a][(i*2)-1]<60)&&(plateau[a][(i*2)-1]-48==joueurjouant)){

                SDL_FillRect(rectangle2[i], NULL, SDL_MapRGB(ecran->format, tableaujoueur[joueurjouant-1].graphbleu, tableaujoueur[joueurjouant-1].graphvert, tableaujoueur[joueurjouant-1].graphrouge));
                SDL_BlitSurface(rectangle2[i], NULL, ecran, &position);
            }
            position.x+=(1000/(taille+2))+10;
        }
        position.x=(1000/(taille+2));
        position.y+=(1000/(taille+2))+10;
        
    }
}

void ecouteurpositioninit(int *x, int *y, int taille, SDL_Surface *ecran, SDL_Rect position, char** plateau){
    int continuer=1;
    int xsauv=*x;
    int ysauv=*y;
    SDL_Surface *rectangle;
    position.x=1000/(taille+2);
    position.y=1000/(taille+2);
    rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, 1000/(taille+2), 1000/(taille+2), 32, 0, 0, 0, 0);
    //faire gaffe si y a déjà qqn!!!!
    if(plateau[*x][(*y*2)-1]=='_'){
        SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, 0, 255, 0));
        SDL_BlitSurface(rectangle, NULL, ecran, &position);
    }
    SDL_Flip(ecran);
    SDL_Event event;
        while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {

            case SDL_QUIT:
                continuer = 0;
                Mix_CloseAudio();
                TTF_Quit();
                SDL_Quit();
                exit(1);
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_RETURN:
                        if(plateau[*x][(*y*2)-1]=='_'){
                            continuer =0;
                        }
                        break;

                    case SDLK_RIGHT:
                        if(*y<taille){                      //on gère le déplacement hors tabeau
                            *y+=1;
                            if(plateau[*x][(*y*2)-1]=='_'){
                                if(plateau[xsauv][(ysauv*2)-1]=='_'){
                                    SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
                                    SDL_BlitSurface(rectangle, NULL, ecran, &position);
                                }
                                position.x+=(1000/(taille+2))+10;
                                SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, 0, 255, 0));
                                SDL_BlitSurface(rectangle, NULL, ecran, &position);
                                SDL_Flip(ecran);
                            }
                            else if((plateau[*x][(*y*2)-1]=='X')||((plateau[*x][(*y*2)-1]>48)&&(plateau[*x][(*y*2)-1]<60))){
                                if(plateau[xsauv][(ysauv*2)-1]=='_'){
                                    SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
                                    SDL_BlitSurface(rectangle, NULL, ecran, &position);
                                }
                                position.x+=(1000/(taille+2))+10;
                                SDL_Flip(ecran);
                            }
                            else{
                                *y-=1;
                            }
                        }
                        break;
                    case SDLK_LEFT:
                        if(*y>1){
                            *y-=1;
                            if(plateau[*x][(*y*2)-1]=='_'){
                                if(plateau[xsauv][(ysauv*2)-1]=='_'){
                                    SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
                                    SDL_BlitSurface(rectangle, NULL, ecran, &position);
                                }
                                position.x-=(1000/(taille+2))+10;
                                SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, 0, 255, 0));
                                SDL_BlitSurface(rectangle, NULL, ecran, &position);
                                SDL_Flip(ecran);
                            }
                            else if((plateau[*x][(*y*2)-1]=='X')||((plateau[*x][(*y*2)-1]>48)&&(plateau[*x][(*y*2)-1]<60))){
                                if(plateau[xsauv][(ysauv*2)-1]=='_'){
                                    SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
                                    SDL_BlitSurface(rectangle, NULL, ecran, &position);
                                }
                                position.x-=(1000/(taille+2))+10;
                                SDL_Flip(ecran);
                            }
                            else{
                                *y+=1;
                            }
                        }
                        break;
                    case SDLK_UP:
                        if(*x>0){
                            *x-=1;
                            if(plateau[*x][(*y*2)-1]=='_'){
                                if(plateau[xsauv][(ysauv*2)-1]=='_'){
                                    SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
                                    SDL_BlitSurface(rectangle, NULL, ecran, &position);
                                }
                                position.y-=(1000/(taille+2))+10;
                                SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, 0, 255, 0));
                                SDL_BlitSurface(rectangle, NULL, ecran, &position);
                                SDL_Flip(ecran);
                            }
                            else if((plateau[*x][(*y*2)-1]=='X')||((plateau[*x][(*y*2)-1]>48)&&(plateau[*x][(*y*2)-1]<60))){
                                if(plateau[xsauv][(ysauv*2)-1]=='_'){
                                    SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
                                    SDL_BlitSurface(rectangle, NULL, ecran, &position);
                                }
                                position.y-=(1000/(taille+2))+10;
                                SDL_Flip(ecran);
                            }
                            else{
                                *x+=1;
                            }
                        }
                        break;
                    case SDLK_DOWN:
                        if(*x<taille-1){
                            *x+=1;
                            if(plateau[*x][(*y*2)-1]=='_'){
                                if(plateau[xsauv][(ysauv*2)-1]=='_'){
                                    SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
                                    SDL_BlitSurface(rectangle, NULL, ecran, &position);
                                }
                                position.y+=(1000/(taille+2))+10;
                                SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, 0, 255, 0));
                                SDL_BlitSurface(rectangle, NULL, ecran, &position);
                                SDL_Flip(ecran);
                                
                            }
                            else if((plateau[*x][(*y*2)-1]=='X')||((plateau[*x][(*y*2)-1]>48)&&(plateau[*x][(*y*2)-1]<60))){
                                if(plateau[xsauv][(ysauv*2)-1]=='_'){
                                    SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
                                    SDL_BlitSurface(rectangle, NULL, ecran, &position);
                                }
                                position.y+=(1000/(taille+2))+10;
                                SDL_Flip(ecran);
                            }
                            else{
                                *x-=1;
                            }
                        }
                        break;

                    default:
                    break;

                }
            default:
            break;
        }
        xsauv=*x;
        ysauv=*y;
    }
    SDL_FreeSurface(rectangle);
}

int choixmenu(SDL_Surface *ecran, SDL_Rect position, char tableautexte[1], int hauteur){
    int choix = 0;
    SDL_Surface *rectangle;
    rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE,20,20, 32, 0, 0, 0, 0);
    SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, 0, 0, 102));
    int continuer=1;
    position.x=30;
    position.y = hauteur + 60;
    SDL_Surface *text= NULL;
    TTF_Font *police = NULL;
    SDL_Color couleurNoire = {158, 14, 64,45};
    police = TTF_OpenFont("police/numeros.ttf", 23);
    for(int i=0 ; i!=10; i++){
        sprintf(tableautexte,"%d",i);
        text = TTF_RenderText_Blended(police, tableautexte, couleurNoire);
        SDL_BlitSurface(text, NULL, ecran, &position); // Blit du texte
        position.x=position.x+70;
    }
    

    tableautexte[0]='*';
    position.x=30;
    position.y = hauteur + 90;
    text = TTF_RenderText_Blended(police, tableautexte, couleurNoire);
    SDL_BlitSurface(text, NULL, ecran, &position); // Blit du texte
    SDL_Flip(ecran);

    SDL_Event event;
        while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                Mix_CloseAudio();
                TTF_Quit();
                SDL_Quit();
                exit(2);
                break;
            
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_RETURN:
                        continuer=0;
                    break;

                    case SDLK_RIGHT:
                    if(choix<9){
                            SDL_BlitSurface(rectangle, NULL, ecran, &position); // Blit du texte
                            position.x=position.x+70;
                            text = TTF_RenderText_Blended(police, tableautexte, couleurNoire);
                            SDL_BlitSurface(text, NULL, ecran, &position); // Blit du texte
                            choix+=1;
                        }
                        break;
                    case SDLK_LEFT:
                        if(choix>0){
                        SDL_BlitSurface(rectangle, NULL, ecran, &position); // Blit du texte
                        position.x=position.x-70;
                        text = TTF_RenderText_Blended(police, tableautexte, couleurNoire);
                        SDL_BlitSurface(text, NULL, ecran, &position); // Blit du texte
                        choix-=1;
                        }
                        break;

                    default:
                    break;

                }
            default:
            break;
        }
        SDL_Flip(ecran);
    }
    SDL_FreeSurface(text);
    return choix;
}