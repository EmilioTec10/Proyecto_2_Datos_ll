#include <bits/stdc++.h>
#include "AStar.h"

using namespace std;


/**
 * @brief AStar::isValid Valida si el numero de columna y fila esta dentro del rango de la matriz
 * @param row numero de la fila
 * @param col numero de la columna
 * @return retorna un boleano que dice si esta en rango o no esta
 */
bool AStar::isValid(int row, int col)
{
    // Returns true if row number and column number
    // is in range
    return (row >= 0) && (row < ROW) && (col >= 0)
           && (col < COL);
}

/**
 * @brief AStar::isUnBlocked Valida si la celda dada esta bloqueada
 * @param grid matriz a revisar
 * @param row numero de fila
 * @param col numero de columna
 * @return retorna verdadero si la celda no esta bloquedada y en caso contrario retorna falso
 */
bool AStar::isUnBlocked(char grid[][COL], int row, int col)
{
    // Returns true if the cell is not blocked else false
    if (grid[row][col] == ' ')
        return (true);
    else
        return (false);
}

/**
 * @brief AStar::isDestination Valida si la celda destino a sido alcanzada
 * @param row numero de fila
 * @param col numero de columna
 * @param dest celda destino
 * @return retorna verdadero si la celda destino a sido alcanzada en caso contrario retorna falso
 */
bool AStar::isDestination(int row, int col, Pair dest)
{
    if (row == dest.first && col == dest.second)
        return (true);
    else
        return (false);
}

/**
 * @brief AStar::calculateHValue Funcion que calcula el valor heuristico
 * @param row numero de fila
 * @param col numero de columna
 * @param dest celda destino
 * @return retorna el valor heuristico de la fila y la columna ingresada
 */
double AStar::calculateHValue(int row, int col, Pair dest)
{
    // Return using the distance formula
    return ((double)sqrt(
        (row - dest.first) * (row - dest.first)
        + (col - dest.second) * (col - dest.second)));
}

/**
 * @brief AStar::tracePath Funcion que almacena el camino completo en una lista
 * @param cellDetails celdas
 * @param dest celda destino
 */
void AStar::tracePath(cell cellDetails[][COL], Pair dest)
{
    //printf("\nThe Path is ");
    int row = dest.first;
    int col = dest.second;
    int i = 0;

    stack<Pair> Path;

    while (!(cellDetails[row][col].parent_i == row
             && cellDetails[row][col].parent_j == col)) {
        Path.push(make_pair(row, col));
        int temp_row = cellDetails[row][col].parent_i;
        int temp_col = cellDetails[row][col].parent_j;
        row = temp_row;
        col = temp_col;
    }

    Path.push(make_pair(row, col));
    while (!Path.empty()) {
        pair<int, int> p = Path.top();
        Path.pop();
        //printf("-> (%d,%d) ", p.first, p.second);
        list[i] = p;
        i++;
    }

    return;
}

/**
 * @brief AStar::aStarSearch funcion que calcula el camino mas corto a una matriz de caracteres entre dos puntos por medio del algoritmo a*
 * @param grid Matriz de caracteres
 * @param src par inicial
 * @param dest par destino
 */
void AStar::aStarSearch(char grid[][COL], Pair src, Pair dest)
{
    if (isValid(src.first, src.second) == false) {
        printf("Source is invalid\n");
        return;
    }

    if (isValid(dest.first, dest.second) == false) {
        printf("Destination is invalid\n");
        return;
    }

    if (isUnBlocked(grid, src.first, src.second) == false
        || isUnBlocked(grid, dest.first, dest.second)
               == false) {
        printf("Source or the destination is blocked\n");
        return;
    }

    if (isDestination(src.first, src.second, dest)
        == true) {
        printf("We are already at the destination\n");
        return;
    }

    bool closedList[ROW][COL];
    memset(closedList, false, sizeof(closedList));

    cell cellDetails[ROW][COL];

    int i, j;

    for (i = 0; i < ROW; i++) {
        for (j = 0; j < COL; j++) {
            cellDetails[i][j].f = FLT_MAX;
            cellDetails[i][j].g = FLT_MAX;
            cellDetails[i][j].h = FLT_MAX;
            cellDetails[i][j].parent_i = -1;
            cellDetails[i][j].parent_j = -1;
        }
    }

    // Initialising the parameters of the starting node
    i = src.first, j = src.second;
    cellDetails[i][j].f = 0.0;
    cellDetails[i][j].g = 0.0;
    cellDetails[i][j].h = 0.0;
    cellDetails[i][j].parent_i = i;
    cellDetails[i][j].parent_j = j;


    set<pPair> openList;


    openList.insert(make_pair(0.0, make_pair(i, j)));

    bool foundDest = false;

    while (!openList.empty()) {
        pPair p = *openList.begin();


        openList.erase(openList.begin());


        i = p.second.first;
        j = p.second.second;
        closedList[i][j] = true;


        double gNew, hNew, fNew;

        if (isValid(i - 1, j) == true) {

            if (isDestination(i - 1, j, dest) == true) {

                cellDetails[i - 1][j].parent_i = i;
                cellDetails[i - 1][j].parent_j = j;

                tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }

            else if (closedList[i - 1][j] == false
                     && isUnBlocked(grid, i - 1, j)
                            == true) {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i - 1, j, dest);
                fNew = gNew + hNew;


                if (cellDetails[i - 1][j].f == FLT_MAX
                    || cellDetails[i - 1][j].f > fNew) {
                    openList.insert(make_pair(
                        fNew, make_pair(i - 1, j)));


                    cellDetails[i - 1][j].f = fNew;
                    cellDetails[i - 1][j].g = gNew;
                    cellDetails[i - 1][j].h = hNew;
                    cellDetails[i - 1][j].parent_i = i;
                    cellDetails[i - 1][j].parent_j = j;
                }
            }
        }


        if (isValid(i + 1, j) == true) {

            if (isDestination(i + 1, j, dest) == true) {
                cellDetails[i + 1][j].parent_i = i;
                cellDetails[i + 1][j].parent_j = j;
                tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }

            else if (closedList[i + 1][j] == false
                     && isUnBlocked(grid, i + 1, j)
                            == true) {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i + 1, j, dest);
                fNew = gNew + hNew;


                if (cellDetails[i + 1][j].f == FLT_MAX
                    || cellDetails[i + 1][j].f > fNew) {
                    openList.insert(make_pair(
                        fNew, make_pair(i + 1, j)));
                    // Update the details of this cell
                    cellDetails[i + 1][j].f = fNew;
                    cellDetails[i + 1][j].g = gNew;

                    cellDetails[i + 1][j].h = hNew;
                    cellDetails[i + 1][j].parent_i = i;
                    cellDetails[i + 1][j].parent_j = j;
                }
            }
        }


        if (isValid(i, j + 1) == true) {

            if (isDestination(i, j + 1, dest) == true) {

                cellDetails[i][j + 1].parent_i = i;
                cellDetails[i][j + 1].parent_j = j;

                tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }


            else if (closedList[i][j + 1] == false
                     && isUnBlocked(grid, i, j + 1)
                            == true) {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i, j + 1, dest);
                fNew = gNew + hNew;


                if (cellDetails[i][j + 1].f == FLT_MAX
                    || cellDetails[i][j + 1].f > fNew) {
                    openList.insert(make_pair(
                        fNew, make_pair(i, j + 1)));
                    cellDetails[i][j + 1].f = fNew;
                    cellDetails[i][j + 1].g = gNew;
                    cellDetails[i][j + 1].h = hNew;
                    cellDetails[i][j + 1].parent_i = i;
                    cellDetails[i][j + 1].parent_j = j;
                }
            }
        }
        if (isValid(i, j - 1) == true) {
            if (isDestination(i, j - 1, dest) == true) {
                cellDetails[i][j - 1].parent_i = i;
                cellDetails[i][j - 1].parent_j = j;
                tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }

            else if (closedList[i][j - 1] == false
                     && isUnBlocked(grid, i, j - 1)
                            == true) {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i, j - 1, dest);
                fNew = gNew + hNew;


                if (cellDetails[i][j - 1].f == FLT_MAX
                    || cellDetails[i][j - 1].f > fNew) {
                    openList.insert(make_pair(
                        fNew, make_pair(i, j - 1)));

                    // Update the details of this cell
                    cellDetails[i][j - 1].f = fNew;
                    cellDetails[i][j - 1].g = gNew;
                    cellDetails[i][j - 1].h = hNew;
                    cellDetails[i][j - 1].parent_i = i;
                    cellDetails[i][j - 1].parent_j = j;
                }
            }
        }

    }
    if (foundDest == false)
        printf("Failed to find the Destination Cell\n");

    return;
}
