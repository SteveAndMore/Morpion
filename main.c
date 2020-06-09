#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

int static morpion [3][3];
//Gestion des erreurs
void SDL_ExitWithError(char* message)
{
    SDL_Log("ERREUR : %s > %s\n", message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}
//Affichage du morpion
void Draw_Morpion(SDL_Renderer *renderer)
{
    SDL_RenderDrawLine(renderer, 300, 100, 300, 550);
    SDL_RenderDrawLine(renderer, 500, 100, 500, 550);
    SDL_RenderDrawLine(renderer, 100, 250, 700, 250);
    SDL_RenderDrawLine(renderer, 100, 400, 700, 400);
    SDL_RenderPresent(renderer);
}
void Draw_Cross(SDL_Renderer *renderer, int x, int y)
{
    SDL_RenderDrawLine(renderer, x, y, x + 75, y + 75);
    SDL_RenderDrawLine(renderer, x + 75, y, x, y + 75);
}

void Draw_Circle(SDL_Renderer * renderer, int centreX, int centreY, int radius)
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


//Affiche soit une croix, soit un cercle sur les coordonnées de la case
void Draw_Cell(int player, SDL_Renderer *renderer, int crossx, int crossy, int circlex, int circley)
{
    if (player == 1)
        Draw_Cross(renderer, crossx, crossy);
    if (player == 2)
        Draw_Circle(renderer, circlex, circley, 50);
    SDL_RenderPresent(renderer);
}


int main(int argc, char **argv) 
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

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
    int player = 1;
    int next_turn = 1;
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
                        //Boite 1
                        if (event.button.x >= 100 && event.button.x <= 300 && event.button.y >= 100 && event.button.y <= 250)
                        {
                            if (morpion[0][0] == 0)
                            {
                                morpion[0][0] = player;
                                Draw_Cell(player, renderer, 160, 135, 190, 160);
                                next_turn = 0;
                            }
                            else
                            {
                                printf("Cette case est deja occupee.\n");
                            }
                        }
                        //Boite 2
                        else if (event.button.x >= 300 && event.button.x <= 500 && event.button.y >= 100 && event.button.y <= 250)
                        {
                            if (morpion[0][1] == 0)
                            {
                                morpion[0][1] = player;
                                Draw_Cell(player, renderer, 360, 135, 400, 160);
                                next_turn = 0;
                            }
                            else
                            {
                                printf("Cette case est deja occupee.\n");
                            }
                        }
                        //Boite 3
                        else if (event.button.x >= 500 && event.button.x <= 700 && event.button.y >= 100 && event.button.y <= 250)
                        {
                            if (morpion[0][2] == 0)
                            {
                                morpion[0][2] = player;
                                Draw_Cell(player, renderer, 560, 135, 600, 160);
                                next_turn = 0;
                            }
                            else
                            {
                                printf("Cette case est deja occupee.\n");
                            }
                        }
                        //Boite 4
                        else if (event.button.x >= 100 && event.button.x <= 300 && event.button.y >= 250 && event.button.y <= 400)
                        {
                            if (morpion[1][0] == 0)
                            {
                                morpion[1][0] = player;
                                Draw_Cell(player, renderer, 160, 285, 190, 320);
                                next_turn = 0;
                            }
                            else
                            {
                                printf("Cette case est deja occupee.\n");
                            }
                        }
                        //Boite 5
                        else if (event.button.x >= 300 && event.button.x <= 500 && event.button.y >= 250 && event.button.y <= 400)
                        {
                            if (morpion[1][1] == 0)
                            {
                                morpion[1][1] = player;
                                Draw_Cell(player, renderer, 360, 285, 400, 320);
                                next_turn = 0;
                            }
                            else
                            {
                                printf("Cette case est deja occupee.\n");
                            }
                        }
                        //Boite 6
                        else if (event.button.x >= 500 && event.button.x <= 700 && event.button.y >= 250 && event.button.y <= 400)
                        {
                            if (morpion[1][2] == 0)
                            {
                                morpion[1][2] = player;
                                Draw_Cell(player, renderer, 560, 285, 600, 320);
                                next_turn = 0;
                            }
                            else
                            {
                                printf("Cette case est deja occupee.\n");
                            }
                        }
                        //Boite 7
                        else if (event.button.x >= 100 && event.button.x <= 300 && event.button.y >= 400 && event.button.y <= 550)
                        {
                            if (morpion[2][0] == 0)
                            {
                                morpion[2][0] = player;
                                Draw_Cell(player, renderer, 160, 435, 190, 470);
                                next_turn = 0;
                            }
                            else
                            {
                                printf("Cette case est deja occupee.\n");
                            }
                        }
                        //Boite 8
                        else if (event.button.x >= 300 && event.button.x <= 500 && event.button.y >= 400 && event.button.y <= 550)
                        {
                            if (morpion[2][1] == 0)
                            {
                                morpion[2][1] = player;
                                Draw_Cell(player, renderer, 360, 435, 400, 470);
                                next_turn = 0;
                            }
                            else
                            {
                                printf("Cette case est deja occupee.\n");
                            }
                        }
                        //Boite 9
                        else if (event.button.x >= 500 && event.button.x <= 700 && event.button.y >= 400 && event.button.y <= 550)
                        {
                            if (morpion[2][2] == 0)
                            {
                                morpion[2][2] = player;
                                Draw_Cell(player, renderer, 560, 435, 600, 470);
                                next_turn = 0;
                            }
                            else
                            {
                                printf("Cette case est deja occupee.\n");
                            }
                        }
                        else
                        {
                            printf("Vous devez cliquer dans les cases.\n");
                        }
                        if (IsTie() == 0 || CheckGame(1) == 0 || CheckGame(2) == 0)
                        {
                            if (IsTie() == 0)
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

//Check sur une case si elle fait partie d'une ligne
int CheckMove(int player, int i, int j)
{
    if (morpion[i][j] == player)
        {
            //Diagonales
            //Bas-Droite
            if (i == 0 && j == 0)
                if (morpion[i + 1][j + 1] == player)
                {
                    if (morpion[i + 2][j + 2] == player)
                    {
                        return 0;
                    }
                }
            //Haut-Droite  
            if (i == 0 && j == 2)
                if (morpion[i + 1][j - 1] == player)
                {
                    if (morpion[i + 2][j - 2] == player)
                    {
                        return 0;
                    }
                }
            //Bas-Gauche
            if (i == 2 && j == 0)
                if (morpion[i - 1][j + 1] == player)
                {
                    if (morpion[i - 2][j + 2] == player)
                    {
                        return 0;
                    }
                }  
            //Haut-Gauche
            if (i == 2 && j == 2)
                if (morpion[i - 1][j - 1] == player)
                {
                    if (morpion[i - 2][j - 2] == player)
                    {
                        return 0;
                    }
                }   
            //Droites
            if (i == 0)
                if (morpion[i + 1][j] == player)
                {
                    if (morpion[i + 2][j] == player)
                    {
                        return 0;
                    }
                }          
            if (j == 0)
                if (morpion[i][j + 1] == player)
                {
                    if (morpion[i][j + 2] == player)
                    {
                        return 0;
                    }
                }   
            if (i == 2)
                if (morpion[i - 1][j] == player)
                {
                    if (morpion[i - 2][j] == player)
                    {
                        return 0;
                    }
                }  
            if (j == 2)
                if (morpion[i][j - 1] == player)
                {
                    if (morpion[i][j - 2] == player)
                    {
                        return 0;
                    }
                }
            return 1; 
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
            {
                printf("Joueur %d a gagne !\n", player);
                return 0;
            }
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