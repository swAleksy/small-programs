
package minesweeper;

import java.util.Scanner;
import java.util.Arrays;
import java.util.Random;

public class minesweeper {

    static int getNumber( int a, int b){
        Scanner scanner = new Scanner(System.in);
        int num = 0;  
        try {
            System.out.printf("Enter number in range %d to %d:\t", a, b-1);
            num = scanner.nextInt();
            if (num >= a && num <= b)
            return num;
            else{
                System.out.println("wrong number");   
                return getNumber(a, b);
            }
        } 
        catch (NumberFormatException e) {
            scanner.nextLine(); 
            throw new NumberFormatException("Invalid input. Please enter a valid integer.");
        }
    }

    static int[][] layMines(int rows, int cols, int noOfMines){
        int[][] arr = new int[noOfMines][2];
        Random rand = new Random();
        
        for (int i = 0; i < noOfMines; i++){
            int val1,val2;  
            do {
                val1 = rand.nextInt(rows);
                val2 = rand.nextInt(cols);
            } while (!isUnique(arr, val1, val2));
            arr[i][0] = val1;
            arr[i][1] = val2;
        }
        return arr;
    }

    static boolean isUnique(int[][] unique, int val1, int val2) {
        for (int[] pair : unique) {
            if (pair[0] == val1 && pair[1] == val2) {
                return false;
            }
        }
        return true;
    }

    static int numberOfNeighboringMines(int x, int y, int[][] minesList){
        int count = 0;
        for (int i = -1; i < 2; i++){
            for (int j = -1; j < 2; j++){
                if (i == 0 && j == 0)
                    continue;
                int [] tempArr = {x + i, y + j};
                for(int[] row : minesList)
                    if (Arrays.equals(row, tempArr))
                        count ++;
            }
        }
        return count;
    }

    static String[][] createBoard(int rows, int cols, int[][] minesList){
        String[][] board = new String[rows][cols];
        for (int[] coord : minesList){
            board[coord[0]][coord[1]] = "*";
        }

        for (int i = 0; i < rows; i++){
            for (int j = 0; j < cols; j++){
                if (board[i][j] != "*"){
                    Integer y = numberOfNeighboringMines(i, j, minesList);
                    board[i][j] = y.toString();
                }
            }
        }
        return board;
    }

    static String[][] createMask(int rows, int cols){
        String[][] mask = new String[rows][cols];

        for (int i = 0; i < rows; i++){
            Arrays.fill(mask[i], "-");
        }
        return mask;

    }

    static String[][] revealFields(int x, int y, String[][] board, String[][] mask) {
        if (mask[x][y].equals("-")) { // Check if the field is unrevealed
            if (board[x][y].equals("*"))
                mask[x][y] = "M";
            else
                mask[x][y] = "U";
            
            if (board[x][y].equals("0")) { // If the field is equal to "0"
                for (int i = -1; i < 2; i++) {
                    for (int j = -1; j < 2; j++) {
                        if (i == 0 && j == 0)
                            continue;
                        
                        int newX = x + i;
                        int newY = y + j;
                        
                        if (newX >= 0 && newX < board.length && newY >= 0 && newY < board[0].length) {
                            mask = revealFields(newX, newY, board, mask);
                        }
                    }
                }
            }
        }
        
        return mask;
    }
    
    static void printMap(String[][] board, String[][] mask) {
        for (int i = 0; i < board.length; i++) {
            for (int j = 0; j < board[i].length; j++) {
                if (mask[i][j] == "U" || mask[i][j] == "M")
                    System.out.print(board[i][j] + " ");
                else
                    System.out.print(mask[i][j] + " ");
            }
            System.out.println();
        }
        System.out.println();
    }

    static boolean isGameOn(String[][] mask){
        for (int i = 0; i < mask.length; i++) {
            for (int j = 0; j < mask[i].length; j++) {
                if (mask[i][j].equals("M")){
                    System.out.println("GAME OVER");
                    return false;
                }
                if (mask[i][j].equals("-"))
                    return true;
            }
        }
        System.out.println("YOU WON");
        return false;
    }       

    static void game(int x, int y, int noOfMi){
        int [][] minArr = layMines(x, y, noOfMi);
        String[][] board = createBoard(x, y, minArr);
        String[][] mask = createMask(x, y);
        printMap(board, mask);
        
        while (isGameOn(mask)){
            int coordX = getNumber(0, x);
            int coordY = getNumber(0, y);
            revealFields(coordX, coordY, board, mask);
            printMap(board, mask);
        }
    }
    public static void main(String[] args){
        game(10, 10, 10);
    }   
     
}