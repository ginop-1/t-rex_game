/* Inspired by google, we have created a game similar to the 
 * "T-rex Game" (That little game that comes out with chrome
 * when you are offline) 
 */

/*
 * Use WASD for game -> getch()
 * Use int matrix for script.
 */

#include <iostream>
#include <ctime>
#include <vector>
#include <string>

#define LENGTH_MATRIX 50
#define HEIGHT_MATRIX 10

struct GAME{
    
    /* Il valore dell'int verrà elaborato per dare l'immagine */
    int MATRIX [ HEIGHT_MATRIX ] [ LENGTH_MATRIX ];
    
};

#define CLEAR 0

GAME GRAFICA;

/* wipe */
void clear()
{
    for(int i=0; i != HEIGHT_MATRIX; ++i)
        for(int j=0; j != LENGTH_MATRIX; ++j)
            GRAFICA.MATRIX[i][j]=CLEAR;
}

void print()
{
    for(int i=0; i != HEIGHT_MATRIX; ++i)
    {
        for(int j=0; j != LENGTH_MATRIX; ++j)
            std::cout<<" "<<GRAFICA.MATRIX[i][j];
        std::cout<<"\n";
    }
}

int main ()
{
    clear();
    print();
    
    return 0;
}
