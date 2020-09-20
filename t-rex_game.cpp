/* Inspired by google, we have created a game similar to the 
 * "T-rex Game" (That little game that comes out with chrome
 * when you are offline) 
 * 
 * By Peppe289
 *
 *
 * Use WASD for game -> getch()
 * Use int matrix for script.
 * 
*/

// ATTUALMENTE IL PROGETTO E' IN FASE SPERIMENTALE, IL LAVORO TERMINATO SARA' DIVERSO 

#include <iostream>
#include <time.h>
#include <vector>
#include <stdio.h>
#include <termios.h>
#include <string.h>
#include <stdlib.h>
#include <chrono>
#include <thread>

#define LENGTH_MATRIX 50    // lunghezza d'azione 
#define HEIGHT_MATRIX 10     // altezza d'azione  
#define SIZE_VET 5          // limite massimo di ostacoli 

struct GAME{
    // Il valore dell'int verrà elaborato per dare l'immagine 
    int MATRIX [ HEIGHT_MATRIX ] [ LENGTH_MATRIX ];                           // use WASD 
    // incrementa ad ogni passo, ed incrementa la velocità ad ogni soglia 
        int input[2] = {0 ,4}; 
    int punti = 0;
    int riposiziona[ HEIGHT_MATRIX ];                   //Memorizza le posizioni per lo spostamento
};

// Valore della matrice dell'int 
#define CLEAR 0     // vuoto 
#define t_rex 1     // personaggio 
#define OST 2       // ostacolo 
#define START 0     // posizione di inizio 

//Color set
const std::string blue("\033[0;34m");
const std::string red("\033[0;31m");
const std::string green("\033[0;32m");
const std::string reset("\033[0m");

GAME GRAFICA;

// Prototipo di funzione 
void clear();                   // pulisce la matrice
char interprete(int, int);      // elabora char 
void clearCONSOLE();            // clean previous console output for creating a single game
void print();                   // stampa la grafica 
int ostacolo();                 // crea l'ostacolo 
void scorrimento();             // rialloca le celle della matrice per lo scorrimento 

// Velocità di scorrimento (da creare)
void sistem_pause_low();
void sistem_pause_medium();
void sistem_pause_long();

// Posiziona il personaggio nel posizione iniziale 
void inizializza_matrix();
void input_WASD();              // Acquisisci input 

void firma()
{
    clearCONSOLE();
    std::string name;
    name="By Peppe289 and Ginop";
    std::cout<<blue<<"\t*******************************\n\t*    ";
    for(int i=0; i!=name.size(); ++i)
        std::cout<<name[i];
    std::cout<<"    *\n\t*******************************"<<reset<<"\n ";
    std::cout<<green<<"\tUse W and S to move up and down" <<reset<<"\n\t";
    std::this_thread::sleep_for(std::chrono::seconds(3));
}

//***********************************************************

int main()
{
    firma();
    clear();
    while(true)
    {
        inizializza_matrix();
        print();
        std::cout<<"\n";
        scorrimento();
    }

    std::cout<<"\n";
    return 0;
}

/*
 * Fixed scorrimento.
 * Clear matrice, interprete, print, scorrimento, posiziona l'ostacolo.
 */

void scorrimento()
{
    int temp;
    int rand;
    ++GRAFICA.punti; //Punteggio

    // Altezza (10) 
    for(int i = 0; i != HEIGHT_MATRIX; ++i)
    {
        // Lunghezza (50)
        for(int j = 0; j != LENGTH_MATRIX; ++j)
        {
            temp = GRAFICA.MATRIX[i][j];
            GRAFICA.MATRIX[i][j-1] = temp;
        }
    }
    
    //Wipe dell'ultima cella per allorcazione dell'ostacolo
    for(int i = 0; i != HEIGHT_MATRIX; ++i)
        GRAFICA.MATRIX[ i ][ LENGTH_MATRIX -1 ] = CLEAR ;

    rand = ostacolo();
    if(rand<9) GRAFICA.MATRIX[ rand ][ LENGTH_MATRIX-1 ] = OST;
}

int ostacolo()   
{
    srand(time(0));
    return rand()%15+1;
}

// wipe 
void clear()
{
    for(int i=0; i != HEIGHT_MATRIX; ++i)
        for(int j=0; j != LENGTH_MATRIX; ++j)
            GRAFICA.MATRIX[i][j]=CLEAR;
}

//*********** Elabora il print ***********
char interprete(int x, int y)
{
    if( GRAFICA.MATRIX[x][y] == CLEAR)
        return ' '; // spazi bianchi 
    
    if( GRAFICA.MATRIX[x][y] == t_rex )
        return 'X'; // crea il trex 
    
    if( GRAFICA.MATRIX[x][y] == OST )
        return '|'; // crea gli ostacoli 
    
    return ' ';
}

void clearCONSOLE()
{
    #if defined _WIN32
        system("cls");
    #else 
        system("clear");
    #endif
}

void print()
{
    clearCONSOLE();
    std::cout<<"\n\tPunteggio: "<<GRAFICA.punti<<"\n";
    for(int i = 0; i != LENGTH_MATRIX; ++i)
        std::cout<<"-";
    // Valore della matrice dell'int 
    for(int i=0; i != HEIGHT_MATRIX; ++i)
    {
        for (int j=0; j != LENGTH_MATRIX; ++j)
            std::cout<<interprete(i,j); // stampa la grafica 
        std::cout<<"\n";
    }
    for(int i = 0; i != LENGTH_MATRIX; ++i)
        std::cout<<"-";
}

//************** Crea lo script del personaggio *************
/*
 * Il presonaggio verrà posizionato nella seconda colonna.
 * Inizializzato alla 4 riga
 */
 
void inizializza_matrix()
{
    if( GRAFICA.punti != 0 )
        input_WASD();
    else
        GRAFICA.MATRIX[ 4 ][ 3 ] = t_rex;
}

//fix movimento
void input_WASD()
{
    char in;
    GRAFICA.input[0] = GRAFICA.input[1];
    //temp = GRAFICA.input[ 1 ];
    //GRAFICA.input[ 0 ] = temp;
    bool risp=true;
    while (risp) 
    {
        std::cin>>in;
        if(in == 'w' || in == 's')
            if( GRAFICA.input[ 1 ] < HEIGHT_MATRIX && GRAFICA.input[ 1 ] > 0 ) risp = false;
    }

    if( in != 'w' )
    {
        if (GRAFICA.input [1] != HEIGHT_MATRIX - 1)
        ++GRAFICA.input[1];
    }
    else
    {
        if(GRAFICA.input[1] != 1)
        --GRAFICA.input[1];
    }
    GRAFICA.MATRIX[ GRAFICA.input[ 0 ] ][ 3 ] = CLEAR;
    GRAFICA.MATRIX[ GRAFICA.input[ 1 ] ][ 3 ] = t_rex;
}
