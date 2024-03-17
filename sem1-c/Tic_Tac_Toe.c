#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

char map[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};

int check_draw() {
    for(int i = 0; i < 9; i++) {
        if(map[i] == ' ') {
            return 0;
        }
    }
    return 1;
}

void map_print() {
    system("cls");
    printf("   |   |   \n");
    printf(" %c | %c | %c \n", map[0], map[1], map[2]);
    printf("___|___|___\n");
    printf("   |   |   \n");
    printf(" %c | %c | %c \n", map[3], map[4], map[5]);
    printf("___|___|___\n");
    printf("   |   |   \n");
    printf(" %c | %c | %c \n", map[6], map[7], map[8]);
    printf("   |   |   \n\n");
}

int check_if_won(char ch) {
    if(map[0] == ch && map[1] == ch && map[2] == ch) return 1;
    else if(map[3] == ch && map[4] == ch && map[5] == ch) return 1;
    else if(map[6] == ch && map[7] == ch && map[8] == ch) return 1;
    else if(map[0] == ch && map[3] == ch && map[6] == ch) return 1;
    else if(map[1] == ch && map[4] == ch && map[7] == ch) return 1;
    else if(map[2] == ch && map[5] == ch && map[8] == ch) return 1;
    else if(map[0] == ch && map[4] == ch && map[8] == ch) return 1;
    else if(map[2] == ch && map[4] == ch && map[6] == ch) return 1;
    else return 0;
}

void single_mode() {
    while(1) {
        int position;

        while(1) {
            map_print();
            printf("[0][1][2]\n[3][4][5]\n[6][7][8]\nWhere do you want to enter X?\n");
            scanf("%d", &position);
            if(map[position] == 'O') {
                continue;
            }
            map[position] = 'X';
            break;
        }

        if(check_if_won('X') == 1) {
                map_print();
                printf("Congrats, You won!\n");
                break;
            }
        
        if(check_draw() == 1) {
            map_print();
            printf("Draw!\n");
            break;
        }

        while(1) {
            int rand_position = rand() % 9;
            if(map[rand_position] != ' ')
                continue;
            map[rand_position] = 'O';
            break;
        }

        if(check_if_won('O') == 1) {
                map_print();
                printf("You lost!\n");
                break;
            }
        
        if(check_draw() == 1) {
            map_print();
            printf("Draw!\n");
            break;
        }
    }

}

void multi_mode() {
    while(1) {
        int position;
        
        while(1) {
            map_print();
            printf("[0][1][2]\n[3][4][5]\n[6][7][8]\nWhere do you want to enter X?\n");
            scanf("%d", &position);
            if(map[position] == 'O') {
                continue;
            }
            map[position] = 'X';
            break;
        }

        if(check_if_won('X') == 1) {
                map_print();
                printf("Congrats Player 1, You won!\n");
                break;
            }
        
        if(check_draw() == 1) {
            map_print();
            printf("Draw!\n");
            break;
        }

        while(1) {
            map_print();
            printf("[0][1][2]\n[3][4][5]\n[6][7][8]\nWhere do you want to enter O?\n");
            scanf("%d", &position);
            if(map[position] == 'X') {
                continue;
            }
            map[position] = 'O';
            break;
        }
        
        if(check_if_won('O') == 1) {
                map_print();
                printf("Congrats Player 2, You won!\n");
                break;
            }

        if(check_draw() == 1) {
            map_print();
            printf("Draw!\n");
            break;
        }

    }

}

int main() {
    srand(time(NULL));
    char ans_mode;
    printf("Select game mode\nSingleplayer [s]\nMultiplayer [m]\n");
    scanf(" %c", &ans_mode);
    if(ans_mode == 's') {
        single_mode();
    }
    else if(ans_mode == 'm') {
        multi_mode();
    }
    else {
        printf("Wrong input\n");
    }

    getch();
    return 0;
}