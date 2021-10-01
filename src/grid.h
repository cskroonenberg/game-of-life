/**
 * @file grid.h
 * @author Caden Kroonenberg (cskroonenberg@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-09-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef GRID_H
#define GRID_H

#include <iostream>
#include <fstream>
#include <string>

class Grid {
    private:
    int M_ROWS;     // # of rows in grid
    int M_COLS;     // # of cols in grid
    int** m_cell_neighbors;     // 2D arr of the count of (living) neighbors for each cell
    bool** m_cell_state;        // 2D arr tracking if a cell is alive or not

    public:
    Grid(std::string file_name) {

        std::ifstream init_stream(file_name);
        init_stream >> M_ROWS;
        init_stream >> M_COLS;
        
        m_cell_neighbors = new int*[M_ROWS];
        m_cell_state = new bool*[M_COLS];

        for(int i = 0; i < M_ROWS; i++) {
            m_cell_neighbors[i] = new int[M_COLS];
            m_cell_state[i] = new bool[M_COLS];
            for(int j = 0; j < M_COLS; j++) {
                init_stream >> m_cell_state[i][j]; // assign inital value
                std::cout << m_cell_state[i][j] << "\n";
            }
        }
        updateAllNeighbors();
    }

    ~Grid() {
        for(int i = 0; i < M_ROWS; i++) {
            delete[] m_cell_neighbors[i]; // free each sub-array
            delete[] m_cell_state[i];
        }
        delete[] m_cell_neighbors;  // free array
        delete[] m_cell_state;
    }

    void print() {
        for(int i = 0; i < M_ROWS; i++) {
            for(int j = 0; j < M_COLS; j++) {
                if(m_cell_state[i][j]) {
                    std::cout << "*" << " ";
                } else {
                    std::cout << "_" << " ";
                }
            }
            std::cout << "\n";
        }
    }

    /**
     * @brief check surrounding neighbors and update neighbor counts according to cell count
     * 
     * @param x_pos x coordinate of cell
     * @param y_pos y coordinate of cell 
     */
    int updatedNeighbors(const int x_pos, const int y_pos) const {
        int neighbor_count = 0;

        if(x_pos != 0 && y_pos != M_COLS - 1) {
            if (m_cell_state[x_pos - 1][y_pos + 1]) {   // X _ _
                neighbor_count++;                       // _ O _
            }                                           // _ _ _
        }

        if (y_pos != M_COLS - 1) {
            if (m_cell_state[x_pos][y_pos + 1]) {        // _ X _
                neighbor_count++;                        // _ O _
            }                                            // _ _ _
        }

        if (x_pos != M_ROWS - 1 && y_pos != M_COLS - 1) {
            if (m_cell_state[x_pos + 1][y_pos + 1]) {    // _ _ X
                neighbor_count++;                        // _ O _
            }                                            // _ _ _
        }

        if (x_pos != M_ROWS -1) {
            if (m_cell_state[x_pos + 1][y_pos]) {        // _ _ _
                neighbor_count++;                        // _ O X
            }                                            // _ _ _
        }

        if (x_pos != M_ROWS - 1 && y_pos != 0) {
            if (m_cell_state[x_pos + 1][y_pos - 1]) {    // _ _ _
                neighbor_count++;                        // _ O _
            }                                            // _ _ X
        }

        if (y_pos != 0) {
            if (m_cell_state[x_pos][y_pos - 1]) {        // _ _ _
                neighbor_count++;                        // _ O _
            }                                            // _ X _
        }

        if (x_pos != 0 && y_pos != 0) {
            if (m_cell_state[x_pos - 1][y_pos - 1]) {    // _ _ _
                neighbor_count++;                        // _ O _
            }                                            // X _ _
        }

        if (x_pos != 0) {
            if (m_cell_state[x_pos - 1][y_pos]) {        // _ _ _
                neighbor_count++;                        // X O _
            }                                            // _ _ _
        }
        return neighbor_count;
    }

    bool updatedState(const int x_pos, const int y_pos) const {
        if(m_cell_neighbors[x_pos][y_pos] == 3) {
            return true;
        } else if (m_cell_neighbors[x_pos][y_pos] == 2 && m_cell_state[x_pos][y_pos]) {
            return true;
        } else {
            return false;
        }
    }

    void updateAllNeighbors() {
        for(int i = 0; i < M_ROWS; i++) {
            for(int j = 0; j < M_COLS; j++) {
                m_cell_neighbors[i][j] = updatedNeighbors(i, j);
            }
        }
    }

    void updateAllStates() {
        for(int i = 0; i < M_ROWS; i++) {
            for(int j = 0; j < M_COLS; j++) {
                m_cell_state[i][j] = updatedState(i, j);
            }
        }
    }

    void updateGrid() {
        updateAllNeighbors();
        updateAllStates();
    }

    /* each tick:
    1) iterate through each cell and update # of neighbours
    2) iterate through each cell and update cell state
    */

};
#endif // GRID_H