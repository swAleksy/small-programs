import random

def get_number(a, b):
    while True:
        try:
            val = int(input(f"podaj liczbe z zakresu {a} - {b}: "))

        except ValueError:
            print("to nie jest liczba ")

        else:
            if val in range(a,b+1):
                return val

def lay_mines(noOfMines, x, y):
    arr = set()
    while len(arr) < noOfMines:
        i = random.randrange(x)
        j = random.randrange(y)
        arr.add((i,j))
    
    return arr

def number_of_neighboring_mines(coord, coordsList):
    noOfMines = 0
    for i in coordsList:
        for a in range(-1,2):
            for b in range(-1,2):
                if (coord[0] - a, coord[1] - b) == i:
                    noOfMines += 1
    
    return noOfMines

# def number_of_neighboring_mines2(coord, minesList):
#     noOfMines = 0
#     j = coord[0]
#     i = coord[1]
#     for x in [(i-1, j-1), (i-1, j), (i-1, j+1),
#                 (i,j-1), (i, j+1),
#                 (i+1, j-1), (i+1, j), (i+1, j-1)]:
#         if x in minesList:
#             noOfMines += 1;
    
#     return noOfMines;

def create_board(x, y, mines, mine="*"):
    borad = []
    mask = []
    for i in range(x):
        row = []
        oRow = []
        for j in range(y):
            oRow.append("_")
            if (i,j) in mines:
                row.append(mine)
            else:
                row.append(number_of_neighboring_mines((i,j), mines))
        borad.append(row)
        mask.append(oRow)

    return (borad, mask)

def reveal_fields(x, y, board, mask, isFirst = True):

    if board[x][y] == "*" and isFirst == True:
        mask[x][y] = "*"
        return board, mask

    if board[x][y] > 0:
        mask[x][y] = "N"
        return board, mask
    
    mask[x][y] = "E"
    for a in range(-1, 2):
        for b in range(-1, 2):
            new_x, new_y = x + a, y + b
            if 0 <= new_x < len(board) and 0 <= new_y < len(board[0]) and mask[new_x][new_y] == "_":
                board, mask = reveal_fields(new_x, new_y, board, mask, isFirst = False)

    return board, mask

def print_board(board, mask):
    
    for row in range(len(board)):
        for el in range(len(board[row])):
            if mask[row][el] == "N":
                print(f"{board[row][el]:^3}", end="")
            elif mask[row][el] == "E":
                print("   ", end="")
            else:
                print(f"{mask[row][el]:^3}", end="")
        print()

def contiueCheck(mask):
    for row in mask:
        if "*" in row:
            print("\ngame over")
            return False
        
    for row in mask:
        if '_' in row:
             return True
    
    print("\nwygranko")
    return False

def sapper():
    x = 10
    y = 10
    noOfMines = 30
    mines = lay_mines(noOfMines, x, y)
    board, mask = create_board(x, y, mines)
    
    print_board(board, mask)

    isGameOn = True
    while isGameOn:
        coordX = get_number(1,x) - 1
        coordY = get_number(1,y) - 1
        board, mask = reveal_fields(coordX, coordY, board, mask)
        print_board(board, mask)
        isGameOn = contiueCheck(mask)

sapper()