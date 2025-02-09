#ifndef JOGO_HEADER
#define JOGO_HEADER

void jogo(){   
    //start input c
    int c=0;
    //ask number of players [1/2]
    int cont,cont2,score=0;
    //int qplayers;
    //printf("Insira a qnt de jogadores: ");
    //scanf("%d",&qplayers);

    //INITIATE time counting
    clock_gettime(CLOCK_MONOTONIC,&spec); //isso define a função agora
    float enemy_instant, controle_instant,tiros_velocidade,controle_tiro;
    //spec.tv_sec = tempo em segundos, spec.tv_nsec = tempo em nanoseg
    enemy_instant = spec.tv_sec + ((float)spec.tv_nsec/1.0e9);
    controle_instant = enemy_instant;
    tiros_velocidade = enemy_instant;
    controle_tiro = enemy_instant;

    //INITIATE ncurses
    initscr();//initiate main window
    cbreak();
    noecho();

    //INITIATE new windows in function of standart window
    //function newwin(height, width, start_y,stat_x)
    int maxY, maxX;
    getmaxyx(stdscr,maxY,maxX);
    WINDOW *playerWin = newwin(maxY*4/6,maxX*4/6,maxY*1/6,maxX*1/6);
    WINDOW *borderPlayerWin = newwin(maxY*4/6+2,maxX*4/6+2,maxY*1/6-1,maxX*1/6-1);
    wborder(borderPlayerWin,'#','#','#','#','#','#','#','#');
    //atualiza as janelas
    wrefresh(borderPlayerWin);
    //novo jogador player1
    jogador *player1 = inicializajogador(playerWin,2,2);

    keypad(stdscr,TRUE);//allow keyboard arrows
	curs_set(FALSE);//torna o cursor invisível
    //nodelay(playerWin,TRUE);//permite getch() ser pulado caso n exista input
    
    //cores do jogo, em pares
    //init_pair(index, foreground, background);
    start_color();
    init_pair(1,COLOR_GREEN,COLOR_BLACK);
    init_pair(2,COLOR_BLUE,COLOR_BLACK);
    init_pair(3,COLOR_WHITE,COLOR_BLACK);
    init_pair(4,COLOR_RED,COLOR_BLACK);
    attron(A_BOLD);
    inimigo *i[qinimigos];
    for(cont=0;cont<qinimigos;cont++){
        i[cont]=inicializainimigo(cont,maxY*3/5,maxX*3/5);
    }
    desenhaplayer(player1,1);
    wtimeout(playerWin,1);
    do{//loop de tempo, conforme o comando passa, o jogo resume.
        c = controle(player1,&controle_tiro,&controle_instant);
        
        desenhaplayer(player1,1);
        if(time_elapsed(&tiros_velocidade,0.05)){
            desenhatiro(player1);//desenha os tiros
        }
        
        
        
        //wrefresh(playerWin);
        //if(qplayers==2)
        //    controle(player2);
        if(c=='r')
            for(cont=0;cont<qinimigos;cont++)
                i[cont]=inicializainimigo(cont,maxY,maxX);
        
        //if(p[0].vivo==0)mvprintw(0,0,"vose morreu :(");
        //if(p[1].vivo==0&&qplayers==2)mvprintw(0,largura-15,"vose morreu :(");
        //mvprintw(0,largura-10,"pontos: %d",score);

        
        //attron(COLOR_PAIR(2));
        //if(qplayers==2)
        //    desenhaplayer(player2,2);
        //Attron(COLOR_PAIR(4));
        if(time_elapsed(&enemy_instant,0.5)){
            for(cont=0;cont<qinimigos;cont++){//controle de inimigos
                controleinimigo(i[cont],player1);
                desenhainimigo(i[cont],player1);
            }
        }
        //attron(COLOR_PAIR(3));
        
        //if(qplayers==2)
        //    desenhatiro(player2);
        //for(cont2=0;cont2<qplayers;cont2++) //roda o(s) doi(s) jogadores pela função de colisão 
            for(cont=0;cont<qinimigos;cont++)
                colisaotiro(player1,i[cont],&score);
        //for(cont2=0;cont2<qplayers;cont2++) //roda o(s) doi(s) jogadores pela função de morte 
        //    for(cont=0;cont<qinimigos;cont++)
        //        morte(player1,i[cont]);
        //        morte(player2,i[cont]);
        
    }while(c!='p');
}

#endif

/*//===========================================================================//
coisas que nota-se que tem q fazer ainda:
1.Definir o sistema de ondas. Toda vez que os inimigos morrem surge outra onda
cada onda terá os inimigos em posições e tempos definidos.
2.Fazer função que faz surgir os inimigos de forma controlada(espaço/tempo). Eu penso
em usar argumentos variaveis.
3.Fazer jogador menos bugado.
4.uma opção interessante seria printar espaços em branco para cada movimento ao 
invés de fazer clean em toda tela e reescrever tudo
5.precisamos resetar os tiros quando eles somem
*///===========================================================================//
