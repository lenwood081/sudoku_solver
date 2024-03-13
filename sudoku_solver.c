#include <stdlib.h>
#include <stdio.h>


const int GRID_SIZE  = 9;

//global varible for counting iterations
int counter;

int is_safe(int[9][9], int, int, int);
int solve(int[9][9], int, int);
void print_grid(int[9][9]);


void print_grid(int grid[9][9]) {
    for (int y = 0; y < GRID_SIZE; y++) {
        for (int x = 0; x < GRID_SIZE; x++) {
            printf("%d ", grid[y][x]);
        }
        printf("\n");
    }
    printf("\n");
}

int is_safe(int grid[9][9], int num, int col, int row) {
    //check for same number in row
    for (int x = 0; x < GRID_SIZE; x++) {
        if (grid[row][x]==num) 
            return 0;
    }

    //check for same number in column
    for (int y = 0; y < GRID_SIZE; y++) {
        if (grid[y][col]==num) 
            return 0;
    }

    //check for same number in 3*3 grid
    int grid_x_corner = row - row % 3;
    int grid_y_corner = col - col % 3;
    for (int x = grid_x_corner; x < grid_x_corner+3; x++) {
        for (int y = grid_y_corner; y < grid_y_corner+3; y++) {
            if (grid[x][y] == num) {
                return 0;
            }
        }
    }

    //if safe return true
    return 1;
}

int solve(int grid[9][9], int row, int col) {
    counter++;

    //base case --> end of grid therfore solved
    if (row == GRID_SIZE-1 && col == GRID_SIZE) 
        return 1;


    //move to next row
    if (col == GRID_SIZE) {
        col= 0;
        row++;
    }

    //check if grid already has a value
    if (grid[row][col] > 0) 
        return solve(grid, row, col+1);

    for (int i = 1; i <= GRID_SIZE; i++) {
        if (is_safe(grid, i, col, row)) {
            grid[row][col] = i;
            if (solve(grid, row, col+1)==1) 
                return 1;
            //else try for next number 
        }

        //if value does not work set to zero and reiterate
        grid[row][col] = 0;
    }
    //if cant be solved
    return 0;
}

int main(int argc, char const *argv[])
{
    counter = 0;
    int grid[9][9] = { //the error checker doesnt like grid[GRID_SIZE][GRID_SIZE]
        {3, 0, 6, 5, 0, 8, 4, 0, 0},
        {5, 2, 0, 0, 0, 0, 0, 0, 0},
        {0, 8, 7, 0, 0, 0, 0, 3, 1},
        {0, 0, 3, 0, 1, 0, 0, 8, 0},
        {9, 0, 0, 8, 6, 3, 0, 0, 5},
        {0, 5, 0, 0, 9, 0, 6, 0, 0}, 
        {1, 3, 0, 0, 0, 0, 2, 5, 0},
        {0, 0, 0, 0, 0, 0, 0, 7, 4},
        {0, 0, 5, 2, 0, 6, 3, 0, 0} 
    };

    print_grid(grid);
    if (!solve(grid, 0, 0)) {
        printf("sudoku has no solution\n");
    } else {
        print_grid(grid);
    }
    printf("Number of interations: %d\n", counter);
    return 0;
}

