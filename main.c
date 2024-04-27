//
//  conway_gol.c
//  ansictut
//
//  Created by Jan Lubinski on 04/12/2023.
//Conways game of life
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define WIDTH 80
#define HEIGHT 60

void printGrid(void);
void initializeGrid(void);
void simulateNew(void);
void copyNew(void);
int countNeighb(int, int);


int grid[HEIGHT][WIDTH];
int newGrid[HEIGHT][WIDTH];


int main(void)
{
    initializeGrid();
    printGrid();

    while(1)
    {
        simulateNew();
        copyNew();
        system("clear");
        printGrid();
        usleep(500000);

    }
    
};

int countNeighb (int x, int y)
{
    int count=0;
    
    for(int i = -1; i<=1; i++)
    {
        for(int j= -1; j<=1; j++)
        {
            if (!(i == 0 && j == 0) && x + i >= 0 && x + i < HEIGHT && y + j >= 0 && y + j < WIDTH)
                count = count + grid[x+i][y+j];
        };
    };
    return count;
};

void copyNew(void)
{
    for (int i=0; i< HEIGHT; i++) {
        for (int j=0; j < WIDTH; j++)
            grid[i][j] = newGrid[i][j];
    }

};

void simulateNew(void)
{
    for(int i=0; i<HEIGHT;i++)
    {
        for(int j=0;j<WIDTH;j++)
        {
                if ((countNeighb(i, j) >1) && (countNeighb(i, j) <=3) && (grid[i][j]==1))
                    newGrid[i][j]=1;
                else if  ((countNeighb(i, j) ==3) && (grid[i][j]==0))
                    newGrid[i][j]=1;
                else newGrid[i][j]=0;
                
        
        }
    }
}

void printGrid(void) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            //logical_test ? iftrue : iffalse
            printf("%c ", grid[i][j] ? '+' : ' ');
        }
        printf("\n");
    }
};
void initializeGrid(void) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            grid[i][j] = rand() % 2; // Randomly set cells as alive or dead
        }
    }
};



/*
 Any live cell with fewer than two live neighbours dies, as if by underpopulation.
 Any live cell with two or three live neighbours lives on to the next generation.
 Any live cell with more than three live neighbours dies, as if by overpopulation.
 Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

These rules, which compare the behaviour of the automaton to real life, can be condensed into the following:

 Any live cell with two or three live neighbours survives.
 Any dead cell with three live neighbours becomes a live cell.
 All other live cells die in the next generation. Similarly, all other dead cells stay dead.
 */

