//COMPILAR: gcc c.c -o c -Wall -lncurses
//VERSIONBETA7.5
//ESSE PROGRAMA NÃO USA VARIÁVEIS GLOBAIS AFIM DE GARANTIR PORTABILIDADE
#define _POSIX_C_SOURCE 200809L//define o CLOCK_MONOLITIC
#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#define qinimigos 50
#define distanciainimigos 2

#include "time_elapsed.h"//declare this before anything else
#include "player.h"
#include "enemy.h"
#include "main.h"

int main() {
     
    WINDOW *w;
    char list[6][100] = { "SELECIONE USANDO AS TECLAS W-S", "Jogar", "Score", "Créditos", "Sair"};
    char item[7];
    int ch, i = 0;

    initscr(); // initialize Ncurses
    w = newwin( 10, 150, 1, 1 ); // create a new window
    box( w, 0, 0 ); // sets default borders for the window
     
// now print all the menu items and highlight the first one
    for( i=0; i<5; i++ ) {
        if( i == 1 ) 
            wattron( w, A_STANDOUT ); // highlights the first item.
        else
            wattroff( w, A_STANDOUT );
        sprintf(item, "%-7s",  list[i]);
        //mvwprintw(w, 2,2,"%s",list);
        mvwprintw( w, i+1, 2, "%s", item );
    }
 
    wrefresh( w ); // update the terminal screen
 
    i = 1;
    noecho(); // disable echoing of characters on the screen
    keypad( w, TRUE ); // enable keyboard input for the window.
    curs_set( 0 ); // hide the default screen cursor.
     
       // get the input
   
    while(( ch = wgetch(w)) != 27){ 
         
                // right pad with spaces to make the items appear with even width.
            sprintf(item, "%-7s",  list[i]); 
            mvwprintw( w, i+1, 2, "%s", item ); 
              // use a variable to increment or decrement the value based on the input.
            switch( ch ) {
                case 'w':
                    i--;
                    i = ( i<1 ) ? 4 : i;
                    break;
                case 'W':
                    i--;
                    i = ( i<1 ) ? 4 : i;
                    break;
                case 's':
                    i++;
                    i = ( i>4 ) ? 1 : i;
                    break;
                case 'S':
                    i++;
                    i = ( i>4 ) ? 1 : i;
                    break;
                case '\n':
                    if(i==1){
                        wclear(w);
                        jogo();
                    }
                    if(i==2){
                        wprintw(w,"Andre eh acefalo");
                    }
                    if(i==3){
                        wclear(w);
                        
	                    wrefresh(w);
	                    nodelay(w, TRUE);
	                    //puts("-CRÉDITOS-\n");
	                    break;
                        }
                    if(i==4){
                        delwin(w);
                        endwin();
                        break;
                    }
                    break;
            }
            // now highlight the next item in the list.
            wattron( w, A_STANDOUT );
             
            sprintf(item, "%-7s",  list[i]);
            mvwprintw( w, i+1, 2, "%s", item);
            wattroff( w, A_STANDOUT );
    }
 
    delwin( w );
    endwin();
    return 0;
}