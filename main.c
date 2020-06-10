#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

SDL_Renderer *renderer = NULL;
int player = 1;
int next_turn = 1;
int static morpion [3][3];
//Gestion des erreurs
void SDL_ExitWithError(char* message)
{
    SDL_Log("ERREUR : %s > %s\n", message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}
//Affiche du morpion vide.
void Draw_Morpion()
{
    SDL_RenderDrawLine(renderer, 300, 100, 300, 550);
    SDL_RenderDrawLine(renderer, 500, 100, 500, 550);
    SDL_RenderDrawLine(renderer, 100, 250, 700, 250);
    SDL_RenderDrawLine(renderer, 100, 400, 700, 400);
    SDL_RenderPresent(renderer);
}
//Affiche une croix aux coordonnées x et y.
void Draw_Cross(int x, int y)
{
    SDL_RenderDrawLine(renderer, x, y, x + 75, y + 75);
    SDL_RenderDrawLine(renderer, x + 75, y, x, y + 75);
}
//Affiche un cercle de rayon radius aux coordonnées x et y.
void Draw_Circle(int centreX, int centreY, int radius)
{
   const int diameter = (radius * 2);
   int x = (radius - 1);
   int y = 0;
   int tx = 1;
   int ty = 1;
   int error = (tx - diameter);

   while (x >= y)
   {
      //  Each of the following renders an octant of the circle
      SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
      SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
      SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
      SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
      SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
      SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
      SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
      SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

      if (error <= 0)
      {
         ++y;
         error += ty;
         ty += 2;
      }

      if (error > 0)
      {
         --x;
         tx += 2;
         error += (tx - diameter);
      }
   }
}
//Affiche soit une croix, soit un cercle aux cordonnées de la case.
void Draw_Cell(int crossx, int crossy, int circlex, int circley)
{
    if (player == 1)
        Draw_Cross(crossx, crossy);
    if (player == 2)
        Draw_Circle(circlex, circley, 50);
    SDL_RenderPresent(renderer);
}
//Mets la case dans le morpion et l'affiche.
void Put_Cell(int x, int y, int crossx, int crossy, int circlex, int circley)
{
    if (morpion[x][y] == 0)
        {
            morpion[x][y] = player;
            Draw_Cell(crossx, crossy, circlex, circley);
            next_turn = 0;
        }
    else
        printf("Cette case est deja occupee.\n");
}
//Check sur une case si elle fait partie d'une ligne
int CheckMove(int player, int i, int j)
{
    if (morpion[i][j] == player)
    {
        if (i == 0)
        {
            //Bas-Droite
            if (j == 0)
            {
                if (morpion[i + 1][j + 1] == player)
                {
                    if (morpion[i + 2][j + 2] == player)
                        return 0;
                }
            }
            //Haut-Droite 
            if (j == 2)
            { 
                if (morpion[i + 1][j - 1] == player)
                {
                    if (morpion[i + 2][j - 2] == player)
                        return 0;
                }
            }
            //Milieu-Droite
            if (morpion[i + 1][j] == player)
            {
                if (morpion[i + 2][j] == player)
                    return 0;
            } 
        }
        if (i == 2)
        {
            //Bas-Gauche
            if (j == 0)
            {
                if (morpion[i - 1][j + 1] == player)
                {
                    if (morpion[i - 2][j + 2] == player)
                        return 0;
                }
            }
            //Haut-Gauche
            if (j == 2)
            {
                if (morpion[i - 1][j + 1] == player)
                {
                    if (morpion[i - 2][j + 2] == player)
                        return 0;
                }
            }
            //Milieu-Gauche
            if (morpion[i - 1][j] == player)
            {
                if (morpion[i - 2][j] == player)
                    return 0;
            }
        }
        //Milieu-Bas
        if (j == 0)
        {
            if (morpion[i][j + 1] == player)
            {
                if (morpion[i][j + 2] == player)
                    return 0;
            }
        }
        //Milieu-Haut
        if (j == 2)
        {
            if (morpion[i][j - 1] == player)
            {
                if (morpion[i][j - 2] == player)
                    return 0;
            }
        }
    }
    return 1;
}
//Check si le jeu est gagné par un joueur
int CheckGame(int player)
{
    int i, j;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            if (CheckMove(player, i, j) == 0)
                return 0;
        }
    }
    return 1;
}
//Check si la partie finie sur une égalité
int IsTie()
{
    int i, j;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            if (morpion[i][j] == 0)
                return 1;
        }
    }
    return 0;
}
int main(int argc, char **argv) 
{
    SDL_Window *window = NULL;
    //Lancement de la SDL
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
        SDL_ExitWithError("Initialisation SDL.");
    //Création de la fenêtre et du rendu
    if (SDL_CreateWindowAndRenderer(800, 600, 0, &window, &renderer) != 0)
        SDL_ExitWithError("Creation de la fenêtre et du rendu echouee.");
    if (SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE) != 0)
        SDL_ExitWithError("Impossible de changer la couleur pour le rendu.");
    Draw_Morpion(renderer);
    printf("Morpion de Steve \nJoueur 1, cliquez sur la case ou vous voulez jouer.\n");
    //TODO: Afficher le tour du joueur
    //Gestion des events
    SDL_bool program_launched = SDL_TRUE;
    while (program_launched)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT)
                    {
                        if (event.button.y <= 250)
                        {
                            //Boite 1
                            if (event.button.x <= 300)
                                Put_Cell(0, 0, 160, 135, 190, 160);
                            //Boite 2
                            else if (event.button.x <= 500)
                                Put_Cell(0, 1, 360, 135, 400, 160);
                            //Boite 3
                            else
                                Put_Cell(0, 2, 560, 135, 600, 160);
                        }
                        else if (event.button.y <= 400)
                        {
                            //Boite 4
                            if (event.button.x <= 300)
                                Put_Cell(1, 0, 160, 285, 190, 320);
                            //Boite 5
                            else if (event.button.x <= 500)
                                Put_Cell(1, 1, 360, 285, 400, 320);
                            //Boite 6
                            else
                                Put_Cell(1, 2, 560, 285, 600, 320);
                        }
                        else
                        {
                            //Boite 7
                            if (event.button.x <= 300)
                                Put_Cell(2, 0, 160, 435, 190, 470);
                            //Boite 8
                            else if (event.button.x <= 500)
                                Put_Cell(2, 1, 360, 435, 400, 470);
                            //Boite 9
                            else
                                Put_Cell(2, 2, 560, 435, 600, 470);
                        }
                        if (CheckGame(1) == 0 || CheckGame(2) == 0 || IsTie() == 0)
                        {
                            if (CheckGame(1) == 0 || CheckGame(2) == 0) 
                                printf("Joueur %d a gagne !\n", player);
                            else
                                printf("Egalite !\n");     
                            int i, j;
                            for (i = 0; i < 3; i++)
                            {
                                for (j = 0; j < 3; j++)
                                {
                                    morpion[i][j] = 0;
                                }
                            }
                            SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                            SDL_RenderFillRect(renderer, NULL);
                            SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
                            Draw_Morpion(renderer);
                            printf("Morpion de Steve \nJoueur 1, cliquez sur la case ou vous voulez jouer.\n");
                        }                   
                        if (next_turn == 0)
                        {
                            if (player == 1)
                            {
                                printf("Tour du Joueur 2\n");
                                player++;
                            }
                            else
                            {
                                printf("Tour du Joueur 1\n");
                                player--;
                            }
                        }  
                    }
                    continue;
                case SDL_QUIT:
                    program_launched = SDL_FALSE;
                    break;
                default:
                    break;
            }
        }
    }
    //Fin de programme
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}