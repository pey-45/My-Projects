from operations import *

#sudoku = [[0, 0, 5, 6, 0, 0, 0, 2, 0],
#          [0, 3, 8, 2, 0, 7, 6, 4, 0],
#          [0, 0, 6, 9, 8, 0, 5, 3, 0],
#          [0, 5, 0, 0, 3, 2, 0, 9, 0],
#          [4, 0, 0, 0, 9, 0, 7, 0, 0],
#          [0, 9, 3, 0, 4, 0, 2, 0, 8],
#          [0, 1, 0, 3, 0, 0, 9, 6, 2],
#          [3, 6, 0, 4, 0, 9, 0, 0, 0],
#          [8, 0, 0, 0, 0, 1, 3, 0, 0]]

sudoku = [[0 for j in range(9)] for i in range(9)]

introducirSudoku(sudoku)
imprimirSudoku(sudoku)

while not terminado(sudoku):
    for i in range(9):
     comprobacionFila(sudoku, i)
    for j in range(9):
     comprobacionColumna(sudoku, j)

imprimirSudoku(sudoku)