def imprimirSudoku (sudoku): 
    print("-------------------------------")
    for i in range(9):
        print("| ", end = "")
        for j in range(9):
            print(sudoku[i][j], end = "")
            if j%3==2:
                print(" | ", end = "")
            else:
                print("  ", end = "")
        print("", end = "\n")
        if i%3==2:
            print("-------------------------------")


def introducirSudoku (sudoku):
    print("Introduce las coordenadas que deseas [1-9][1-9], 0 en cualquiera de ellas para terminar")
    x = -1
    y = -1
    while x!=0 and y!=0:
        x = int(input("Coordenada x:"))
        y = int(input("Coordenada y:"))
        if x!=0 and y!=0:
            sudoku[x-1][y-1] = int(input("Valor:"))


def terminado (sudoku):
    for i in range(9):
        if 0 in sudoku[i]:
            return False
    return True


def numeroEnFila (sudoku, i, n):
    if n in sudoku[i]:
        return True


def numeroEnColumna (sudoku, j, n):
    for i in range(9):
        if n==sudoku[i][j]:
            return True


def numeroEnCaja (sudoku, i, j, n):
    caja_i=i//3
    caja_j=j//3
    for i in range(3*caja_i, 3*caja_i+3):
        for j in range(3*caja_j, 3*caja_j+3):
            if n==sudoku[i][j]:
                return True


def esValido (sudoku, i, j, n):
    if not numeroEnFila(sudoku, i, n) and not numeroEnColumna(sudoku, j, n) and not numeroEnCaja(sudoku, i, j, n) and sudoku[i][j]==0:
        return True


def comprobacionFila (sudoku, i):
    for n in range(1,10):
        count=0
        for j in range(9): 
            if esValido(sudoku, i, j, n):
                count+=1
                y=j
        if count==1:
            sudoku[i][y]=n


def comprobacionColumna (sudoku, j):
    for n in range(1,10):
        count=0
        for i in range(9): 
            if esValido(sudoku, i, j, n):
                count+=1
                x=i
        if count==1:
            sudoku[x][j]=n