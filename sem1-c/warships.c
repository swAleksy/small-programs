#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#define hor 0
#define ver 1


struct Coord{
	int xC,yC,isHit;
	char shipTypeLetter;
};

typedef struct Coord Coord;

void clrscr()
{
    system("@cls||clear");
}

void draw(char boardArr[][10]){
	printf("\n");
	printf("   0 1 2 3 4 5 6 7 8 9");
    printf("\n\n");
        
	for (int i = 0; i < 10; i++){
		printf("%d  ",i);
		for (int j = 0; j < 10; j++){
			printf("%c ",boardArr[j][i]);
		}
		printf("\n");
	}
}

void drawIdx(int lockIdx[][10]){
	printf("\n   (zablokowane pozycje > 0 )\n");
	printf("   0 1 2 3 4 5 6 7 8 9");
    printf("\n\n");
	for (int i = 0; i < 10; i++){
		printf("%d  ",i);
		for (int j = 0; j < 10; j++){
			printf("%d ",lockIdx[j][i]);
		}
	printf("\n");
	}
}

void manualShipsDeployment(char boardArr[][10]){
	printf("\n");
	//int shipsSize[] = {5,4,4,3,3,2,2};
	int shipsSize[] = {5,4};
	int lockIdx[10][10] = {{0}};
	for (int n = 0; n < sizeof(shipsSize)/sizeof(shipsSize[0]); n++){
		int x, y, verOrHor;
		int idxRange = 10 - shipsSize[n];
		int isDeployright = 0;
		printf(" Deploy ship no.%d (size %d) \n", n + 1, shipsSize[n]);	
		drawIdx(lockIdx);
		draw(boardArr);
		do{
			printf(" Select deployment type horizontal (0) or vertical (1): ");
			scanf("%d", &verOrHor);
		} while(verOrHor != hor && verOrHor != ver);
		
////////coord input and check
		while (isDeployright != 1){
			isDeployright = 1;
			if (verOrHor == hor){
				do{
					printf("x: ");
					scanf("%d", &x);
					//x -= 1;
				} while(x < 0 || x > idxRange);
				
				do{
					printf("y: ");
					scanf("%d", &y);
				} while(y < 0 || y > 9);
			}
			
			if (verOrHor == ver){
				do{
					printf("x: ");
					scanf("%d", &x);
					//x -= 1;
				} while(x < 0 || x > 9);
				
				do{
					printf("y: ");
					scanf("%d", &y);
				} while(y < 0 || y > idxRange);
			}
//////////// hor deployment in 3rd quarter error (only for ship size4 and less ??)
			if (verOrHor == hor){
				//printf("test 0\n");
				for (int i = 0; i < shipsSize[n]; i++){
					if (lockIdx[x + i][y] != 0){
						printf("lock 0\n");
						isDeployright = 0;
						printf("wrong deployment \n");
					}
				}
			}

			else if (verOrHor == ver){
				//printf("test 1\n");
				for (int i = 0; i < shipsSize[n]; i++){
					if (lockIdx[x][y + i] != 0){
						printf("lock 1\n");
						isDeployright = 0;
						printf("wrong deployment \n");
					}
				}
			}
		}
////////// tile lock
		if (verOrHor == ver) {
			if(y > 0 && y < 10 - shipsSize[n]){

				lockIdx[x][y - 1] = 3;
				lockIdx[x][y + shipsSize[n]] = 2;
			}
			if (y == 0) lockIdx[x][y + 10 - shipsSize[n]] = 3;
			else if (y == 10 - shipsSize[n]) lockIdx[x][y - 1] = 2;
		} 
		
		else if (verOrHor == hor) {
			if(x > 0 && x < 10 - shipsSize[n]){
				lockIdx[x - 1][y] = 4;
				lockIdx[x + shipsSize[n]] [y] = 5;	
			}
			if (x == 0) lockIdx[x + shipsSize[n]][y] = 4;
			else if (x == 10 - shipsSize[n]) lockIdx[x - 1][y] = 5;
		} 		
//////////////////////

		for (int h = 0; h < 10 - idxRange; h++){
			if(verOrHor == ver) {
				if (x == 0){
					for (int j = 0; j < 2; j++){
						boardArr[x][y + h] = shipsSize[n] + 48 ;
						lockIdx[x + j][y + h] = 1;			
					}					
				}
				else if (x == 9){
					for (int j = -1; j < 1; j++){
						boardArr[x][y + h] = shipsSize[n] + 48 ;
						lockIdx[x + j][y + h] = 1;
					}
				}
				else {
					for (int j = -1; j < 2; j++){
						boardArr[x][y + h] = shipsSize[n] + 48 ;
						lockIdx[x + j][y + h] = 1;		
					}
				}
			}
			if(verOrHor == hor) {
				if (y == 0){
					for (int j = 0; j < 2; j++){
						boardArr[x + h][y] = shipsSize[n] + 48;
						lockIdx[x + h][y + j] = 1;				
					}					
				}
				else if (y == 9){
					for (int j = -1; j < 1; j++){
						boardArr[x + h][y] = shipsSize[n] + 48;
						lockIdx[x + h][y + j] = 1;			
					}					
				}
				else {
					for (int j = -1; j < 2; j++){
						boardArr[x + h][y] = shipsSize[n] + 48;
						lockIdx[x + h][y + j] = 1;				
					}
					
				}
			}
		}		
		
		//printf("test idxlock \n");
		clrscr();
	}
	
	printf("\n All ships deployed!\n");
}

void randomShipsDeployment(char boardArr[][10]){
 
	int shipsSize[] = {5,4,4,3,3,2,2};
	//int shipsSize[] = {5,4};
	int lockIdx[10][10] = {{0}};
	for (int n = 0; n < sizeof(shipsSize)/sizeof(shipsSize[0]); n++){	
		int x = 0, y = 0, size = 11 - shipsSize[n], isPosGood = 0;
		int verOrHor = rand() % 2;
		// hor = 0 ver = 1 
		//printf("=== ver/hor === %d\n",verOrHor);
		while(isPosGood != 1){
		    x = rand()%size;
			y = rand()%size;
			isPosGood = 1;
			if (verOrHor == hor){
				for (int i = 0; i < shipsSize[n]; i++){
					if (lockIdx[x][y + i] == 1){
						isPosGood = 0;
					}
				}
			}

			else if (verOrHor == ver){
				for (int i = 0; i < shipsSize[n]; i++){
					if (lockIdx[x + i][y] == 1){
						isPosGood = 0;
					}
				}
			}
		}
		// mozliwy error przy losowaniu ¡¡¡
		if (verOrHor == hor) {
			if(y > 0 && y < 10 - shipsSize[n]){

				lockIdx[x][y - 1] = 1;
				lockIdx[x][y + 11 - size] = 1;
			}
			if (y == 0) lockIdx[x][y + 11 - size] = 1;
			else if (y == 10 - shipsSize[n]) lockIdx[x][y - 1] = 1;

		} 
		else if (verOrHor == ver) {
			if(x > 0 && x < 10 - shipsSize[n]){
				lockIdx[x - 1][y] = 1;
				lockIdx[x + 11 - size][y] = 1;	
			}
			if (x == 0) lockIdx[x + 11 - size][y] = 1;
			else if (x == 10 - shipsSize[n]) lockIdx[x - 1][y] = 1;
		} 
///// A - 5; B - 4.1; C - 4.2; D- 3.1; E- 3.2; F- 2.1; G-2.2
		for (int h = 0; h < 11 - size; h++){
			for (int j = -1; j < 2; j++){
				if (verOrHor == hor) {
					boardArr[x][y + h] = 65 + n;
					lockIdx[x + j][y + h] = 1;
					
				}

				else if (verOrHor == ver) {
					boardArr[x + h][y] = 65 + n;
					lockIdx[x + h][y + j] = 1;	
				}
			}		
		}
	}
	//drawIdx(lockIdx);
	//draw(boardArr);
}

Coord shot(char board[][10],char maskBoard[][10]){	
	int x, y;
	Coord shot;	
	
	printf("\nenter coordinates: \n");
	do{
		printf("x: ");
		scanf("%d",&x);
	}while(x < 0 || x > 9);
	
	do{
		printf("y: ");
		scanf("%d",&y);
	}while(y < 0 || y > 9);
	//////////////////////////////////////////////////////// ERR 
	if (board[x][y] == 111){
		shot.xC = 69;
		shot.yC = 69;
		return shot;
	}
	
	shot.xC = x;
	shot.yC = y;
	if (board[x][y] != 126){
		shot.shipTypeLetter = board[x][y];
		board[x][y] = 42;
		maskBoard[x][y] = 42;
		shot.isHit = 1;
		return shot;
	}
	else if (board[x][y] == 126){
		shot.isHit = 0;
		board[x][y] = 111;
		maskBoard[x][y] = 111;
		return shot;
	}
	return shot;
}

Coord botShot(char board[][10]){
	int x, y;
	do{
		x = rand() % 10;
		y = rand() % 10;
	}while(board[x][y] == 42 || board[x][y] == 111);
	
	Coord botShot;
	botShot.xC = x;
	botShot.yC = y;
	
	if (board[x][y] == 126){
		board[x][y] = 111;
		botShot.isHit = 0;
		return botShot;
	}
	else {
		board[x][y] = 42;
		botShot.isHit = 1;
		return botShot;
	}
}

void drawMatch(char myBoard[][10], char enemyBoard[][10]){
	draw(enemyBoard);
	printf("<=======================>");
	draw(myBoard);
}

int isShipsLeft(char board[][10]){
	for (int i = 0; i < 10; i++){
		for (int j = 0; j < 10; j++){
			if (board[i][j] != 126){
				if(board[i][j] != 111 || board[i][j] != 42) return 1;
			}
		}
    }		
    return 0;
}

void game(){
	
	char myBoard[10][10], enemyBoard[10][10], enemyMaskBoard[10][10];
	for (int i = 0; i < 10; i++){
		for (int j = 0; j < 10; j++){
			myBoard[i][j] = 126;
			enemyBoard[i][j] = 126;
			enemyMaskBoard[i][j] = 126;
		}
    }
	randomShipsDeployment(enemyBoard);
	printf(" Start deploying your ships ships {5 - battleship (type A), 4x2 - cruisers (type B and C),\n 3x2 - destroyers (type D and E), 2x2(type F and G) - submarines}\n");
	manualShipsDeployment(myBoard);
	int isGameOn = 1, turn = 1;
	
	while(isGameOn){
		Coord myShot, enemyShot;
		int hitScored = 1;
		printf("\n Player turn ===== %d =====",turn);
				
		while(hitScored){
			clrscr();
			
			if (turn != 1){	
				if (enemyShot.isHit == 0){
					printf(" Enemy miss at x:%d y:%d\n",enemyShot.xC, enemyShot.yC);
				}
				else{
					printf(" Enemy hit at x:%d y:%d!\n",enemyShot.xC, enemyShot.yC);			
				}
								
				if (myShot.isHit == 0){
				printf(" Miss at x:%d y:%d\n",myShot.xC, myShot.yC);
				}
				else{
					printf(" Hit at x:%d y:%d!\n",myShot.xC, myShot.yC);
					char hitedType = myShot.shipTypeLetter;
					int count = 0;
					for (int i = 0; i < 10; i++){
						for (int j = 0; j < 10; j++){
							if(enemyBoard[i][j] == hitedType) ++count;
						}
					}
					if (count == 0) printf(" ship type %c destroyed\n",hitedType);							
				}

			}
			
			drawMatch(myBoard,enemyMaskBoard);
			myShot = shot(enemyBoard, enemyMaskBoard);
			while(myShot.xC == 69){
				printf("ERR");
				myShot = shot(enemyBoard, enemyMaskBoard);
			}	
			hitScored = myShot.isHit;
			turn ++;
		}	
		
		if ( isShipsLeft(enemyBoard) == 0 ) break;
			
		printf("\n Bot turn ===== %d =====",turn);
		hitScored = 1;
		
		while(hitScored){
			enemyShot = botShot(myBoard);
			hitScored = enemyShot.isHit;
		}
		
		//drawMatch(myBoard,enemyMaskBoard);
		isGameOn = isShipsLeft(myBoard);
		
		turn ++;
		if ( isShipsLeft(myBoard) == 0 ) break;	
	}
}

int main(){
	srand(time(NULL));
	game();
	return 0;
}
