#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int COLUMN = 30;
int ROW = 30;
int cellmap[30][30];
int newmap[30][30];
int indexgen = 0;

void printCellmap(){      //A function that clears the console and then loops through the array and prints it
  system("clear");
  for(int i = 0; i<ROW; i++) {
    for(int j = 0; j<COLUMN; j++) {
        printf("%d ", cellmap[i][j]);
    }
    printf("\n");
  }
  printf("Generation: %d \n", indexgen++);
  sleep(1); //1 second delay
}

void initGlider(int x, int y){
  cellmap[x][y+1] = 1;    //Creates a "glider" in the map
  cellmap[x+2][y] = 1;
  cellmap[x+2][y+1] = 1;
  cellmap[x+2][y+2] = 1;
  cellmap[x+1][y+2] = 1;
}

void initLWSS(int x, int y){    //Creates a Light Weigth Space Ship
  cellmap[x][y+1] = 1;
  cellmap[x][y+2] = 1;
  cellmap[x][y+3] = 1;
  cellmap[x+1][y] = 1;
  cellmap[x+1][y+3] = 1;
  cellmap[x+2][y+3] = 1;
  cellmap[x+3][y+3] = 1;
  cellmap[x+4][y] = 1;
  cellmap[x+4][y+2] = 1;
}

void mapinit(){     //Initialize the gridmap to 0
  for(int i = 0; i<ROW; i++) {
    for(int j = 0; j<COLUMN; j++) {
      cellmap[i][j] = 0;
      newmap[i][j] = 0;
    }
  }
  initGlider(4,3);
  initLWSS(10, 10);
  printCellmap();
}

int nearCells(int row, int col){    //function to check all the neighbouring cells
  int sum = 0;
  if(cellmap[row][col])
    sum--;                           //Starts at -1 instead to negate the sum-incremention at cellmap[0][0] since we know already that it is 1
  for(int i = -1; i <= 1; i++) {         //Checks the closest 8 neighbours if they are 1 or 0
    for(int j = -1; j <= 1; j++) {
      if(cellmap[row+i][col+j]){
        sum++;
      }
    }
  }
  return sum;
}

void copyArray(){               //Sets cellmap to newmap
    for(int i = 0; i<ROW; i++) {
      for(int j = 0; j<COLUMN; j++) {
        cellmap[i][j] = newmap[i][j];
      }
    }
}

int main(void){
  mapinit();
    while(1){   //Loops continously
      for(int i = 0; i<ROW; i++) {
        for(int j = 0; j<COLUMN; j++) {
            int nSum = nearCells(i, j);   //Checks the amount of neighbours
            if(nSum == 3)                 //If the cell has 3 neighbours then it will be alive next generation no matter the current state
              newmap[i][j] = 1;
            else if(nSum == 2 && cellmap[i][j])   //If the cell only has 2 neighbours while currently being alive then it will remain alive
              newmap[i][j] = 1;
            else newmap[i][j] = 0;                //Else the cell will either die or remain dead
        }
      }
      copyArray();
      printCellmap();
    }
}
