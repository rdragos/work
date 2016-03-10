from fractions import Fraction as Frac
from copy import copy

def pivot(matrix, line, column):

    store = [ [0 for _ in range(len(matrix[0]))] for _ in range(len(matrix))]
    for l in range(len(matrix)):
        for c in range(len(matrix[0])):
            if l == line and c == column:
                store[l][c] = Frac(1, matrix[l][c])
            elif l == line:
                store[l][c] = matrix[l][c] / matrix[line][column]
            elif c == column:
                store[l][c] = -matrix[l][c] / matrix[line][column]
            else:
                store[l][c] = matrix[l][c] - (matrix[l][column] * matrix[line][c] / matrix[line][column])
    return store

def debug(matrix):

    for line in matrix:
        string = ""
        for el in line:
            reduced_frac = str(el.numerator) + "/" + str(el.denominator)

            if el.numerator == 0:
                reduced_frac = "0"
            elif el.denominator == 1:
                reduced_frac = str(el.numerator)

            string += "& " + reduced_frac + " "
        print(string)


def main():
    a = [[1, 2, 2, 1], \
        [-3, 0, 1, -1], \
        [-2, -1, 0, -1], \
        [-3, -4, -5, 0] \
    ]

    n = 3

    for i in range(len(a)):
        for j in range(len(a[0])):
            a[i][j] = Frac(a[i][j], 1)

    debug(a)
    for it in range(6):
        flag = 0
        for line in range(n):
            if a[line][n] < 0:
                mn = 10000
                sel_column = 0

                for col in range(n):
                    if a[line][col] < 0:
                        if mn > a[line][n] / a[line][col]:
                            mn = a[line][n] / a[line][col]
                            sel_column = col
                a = pivot(a, line, sel_column)
                print('Pivot around ' + str(line + 1) + ' ' + str(sel_column + 1))
                debug(a)
                flag = 1
                break
        if flag == 1:
            continue
        for column in range(n):
            if a[n][column] < 0:
                mn = 10000
                sel_line = 0

                for line in range(n):
                    if a[line][n] == 0:
                        continue
                    if a[line][column] > 0:
                        if mn > a[line][n] / a[line][column]:
                            mn = a[line][n] / a[line][column]
                            sel_line = line

                a = pivot(a, sel_line, column)
                print('Pivot around ' + str(sel_line + 1) + ' ' + str(column + 1))
                debug(a)
                break
    print('yello')
if __name__=="__main__":
    main()
