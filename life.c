#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#define MAX_ROW 40
#define MAX_COL 40

int cycle(int a, int b, int c, int d, int e, int f, int g, int h, int oldstate)
{
    int neighbors, newstate;

    neighbors = a + b + c + d + e + f + g + h;

    switch (neighbors)
        {
            case 0: case 1: case 4: case 5: case 6: case 7: case 8:
                newstate = 0;
                break;
            case 2:
                newstate = oldstate;
                break;
            case 3:
                newstate = 1;
                break;
            default:
                break;
        }
    return newstate;
}

int main(void)
{
    int r, c, time, t, neighbors, step = 0, grid[MAX_ROW][MAX_COL] = {0}, newgrid[MAX_ROW][MAX_COL] = {0};

    printf("Enter the number of cycles to compute: "); //how long we're running the game
    scanf("%d", &time);

    grid[1][2] = 1; grid [2][3] = 1; grid[3][1] = 1; grid[3][2] = 1; grid[3][3] = 1; //initial conditions
    grid[25][25] = 1; grid[25][24] = 1; grid[25][26] = 1; grid[24][25] = 1; grid[26][25] = 1;
    grid[22][22] = 1; grid[23][23] = 1; grid[24][21] = 1; grid[24][22] = 1; grid[24][23] = 1;
    grid[31][2] = 1; grid [32][3] = 1; grid[33][1] = 1; grid[33][2] = 1; grid[33][3] = 1;
    grid[26][34] = 1; grid[27][33] = 1; grid[28][33] = 1; grid[28][34] = 1; grid[28][35] = 1;
    
    for (r = 0; r < MAX_ROW; r++) {
        for (c = 0; c < MAX_COL; c++) {
            if (grid[r][c] == 0) printf("#"); else printf(" ");} 
            printf("\n");
    } printf("\n"); //display initial conditions
    usleep(100000);
    system("clear");

    for (t = 0; t < time; t++) { //run for time cycles

        for (r = 0; r < MAX_ROW; r++) { //store new conditions in a temporary grid
            for (c = 0; c < MAX_COL; c++)
                newgrid[r][c] = cycle(grid[(r-1+MAX_ROW)%MAX_ROW][(c-1+MAX_COL)%MAX_COL], grid[(r-1+MAX_ROW)%MAX_ROW][c], grid[(r-1+MAX_ROW)%MAX_ROW][(c+1)%MAX_COL], grid[r][(c-1+MAX_COL)%MAX_COL], grid[r][(c+1)%MAX_COL], grid[(r+1)%MAX_ROW][(c-1+MAX_COL)%MAX_COL], grid[(r+1)%MAX_ROW][c], grid[(r+1)%MAX_ROW][(c+1)%MAX_COL], grid[r][c]);
        }
        for (r = 0; r < MAX_ROW; r++) { //move temp grid to grid and print
            for (c = 0; c < MAX_COL; c++) {
                grid[r][c] = newgrid[r][c];
                if (grid[r][c] == 0) printf("#"); else printf(" ");
            } printf("\n");
        } printf("\n");
        usleep(100000);
        system("clear");

        for (r = 0; r < MAX_ROW; r++) { //display final grid
            for (c = 0; c < MAX_COL; c++) {
                if (grid[r][c] == 0) printf("#"); else printf(" ");
            } printf("\n");
        } printf("Generation %d\n", step++);
    }

    return 0;
}
