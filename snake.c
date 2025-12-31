                                                                 // SNAKE GAME //

#include <conio.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// HEIGHT & WIDTH
#define HEIGHT 20
#define WIDTH 40

int snakeTailX[100], snakeTailY[100]; // COORDINATES OF SNAKE
int snakeTailLen; // LENGTH OF THE SNAKES'S TAIL
int gameover, key, score; // SCORE AND SIGNAL FLAGES
int x, y, fruitx, fruity; // COORDINATES OF SNAKE'S HEAD AND FRUIT 

// FUNC TO GENERATE THE FRUIT WITHIN THE BOUNDARY
void setup() {
    gameover = 0; // SIGNAL FOR GAMEOVER

    x = WIDTH / 2; // INITIAL COORDINATES OF THE SNAKE
    y = HEIGHT / 2;
    
    fruitx = rand() % WIDTH; // INTIAL COORDINATES OF THE FRUIT
    fruity = rand() % HEIGHT;
    while (fruitx == 0)
        fruitx = rand() % WIDTH;

    while (fruity == 0)
        fruity = rand() % HEIGHT;

    score = 0; // SCORE INITIALIZED
}

// FUNC TO DRAW THE GAME FIELD , SNAKE AND FRUIT
void draw() {
    system("cls");
    
    for (int i = 0; i < WIDTH + 2; i++) // TOP WALL
        printf("-");
    printf("\n");
    
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j <= WIDTH; j++) {

            if (j == 0 || j == WIDTH) // CREATING SIDE WALLS WITH '#'
                printf("#");
            
            if (i == y && j == x) // SNAKE'S HEAD WITH 'O'
                printf("O");
            
            else if (i == fruity && j == fruitx) // SNAKE'S FOOD WITH '*'
                printf("*");
            
            else { // SNAKES'S BODY WITH 'O'
                int prTail = 0;
                for (int k = 0; k < snakeTailLen; k++) {
                    if (snakeTailX[k] == j
                        && snakeTailY[k] == i) {
                        printf("o");
                        prTail = 1;
                    }
                }
                if (!prTail)
                    printf(" ");
            }
        }
      printf("\n");
            
    }
    
    // CREATING BOTTOM WALLS WITH '-'
    for (int i = 0; i < WIDTH + 2; i++)
        printf("-");
     printf("\n");

    // PRINTING SCORE AND INTRUCTIONS
    printf("score = %d", score);
    printf("\n");
    printf("Press w, l, r, d for movement.\n");
    printf("Press X to quit the game.");
}

//FUNC TO TAKE THE REAL TIME INPUT 
void input() {
    if (kbhit()) {
        switch (tolower(getch())) {
        case 'l':
            if(key!=2)
            key = 1;
            break;
        case 'r':
            if(key!=1)
            key = 2;
            break;
        case 'w':
            if(key!=4)
            key = 3;
            break;
        case 'd':
            if(key!=3)
            key = 4;
            break;
        case 'x':
            gameover = 1;
            break;
        }
    }
}

void logic() { // FUNC THAT CHECK EAT, MOVE, COLLISIONS 
    
    // UPDATING THE COORDINATES FOR CONTINOUS / MOVEMENT OF SNAKE
    int prevX = snakeTailX[0];
    int prevY = snakeTailY[0];
    int prev2X, prev2Y;
    snakeTailX[0] = x;
    snakeTailY[0] = y;
    for (int i = 1; i < snakeTailLen; i++) {
        prev2X = snakeTailX[i];
        prev2Y = snakeTailY[i];
        snakeTailX[i] = prevX;
        snakeTailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    
    switch (key) { // CHANGING THE DIRECTION OF MOVEMENT OF SNAKE 
    case 1:
        x--;
        break;
    case 2:
        x++;
        break;
    case 3:
        y--;
        break;
    case 4:
        y++;
        break;
    default:
        break;
    }

    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) //  IF THE GAME IS OVER 
        gameover = 1;
        
    for (int i = 0; i < snakeTailLen; i++) {  // CHECKS FOR COLLISION WITH THE TAIL (O)
        if (snakeTailX[i] == x && snakeTailY[i] == y)
            gameover = 1;
    }

    // IF SNAKE REACHES THE FRUIT , SCORE WILL BE UPDATED
    if (x == fruitx && y == fruity) { 
        fruitx = rand() % WIDTH;
        fruity = rand() % HEIGHT;
        while (fruitx == 0)
            fruitx = rand() % WIDTH;

        while (fruity == 0) // GENERATION OF NEW FRUIT 
            fruity = rand() % HEIGHT;
        score += 10;
         snakeTailLen++;
    }
}

void main() {
    setup();  // INTIAL SET UP THAT INITIALIZE THE REQUIRED VARIABLES

    while (!gameover) { // GAME LOOP STARTS HERE 

        // FUNC THAT WILL BE CALLED REPEATEDLY AFTER THE GIVEN INTERVAL
        draw();
        input();
        logic();
        Sleep(33);
    }
}
