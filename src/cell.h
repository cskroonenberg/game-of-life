/**
 * @file cell.h
 * @author Caden Kroonenberg (cskroonenberg@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-09-22
 */
#ifndef CELL_H
#define CELL_H

class Cell {
    private:
    bool m_is_alive;
    int m_neighbor_count;
    int m_x_pos;
    int m_y_pos;

    public:
    Cell(bool is_alive, int neighbor_count, int x_pos, int y_pos) {
        m_is_alive = is_alive;
        m_neighbor_count = neighbor_count;
        m_x_pos = x_pos;
        m_y_pos = y_pos;
    }

    /**
     * @brief check surrounding neighbors and update neighbor counts according to cell count
     * 
     * @param cell_state_grid 
     */
    void updateNeighborCount(bool** cell_state_grid) {
        // TODO: Check edge cases
        m_neighbor_count = 0;

        if (cell_state_grid[m_x_pos - 1][m_y_pos + 1]) {    // X _ _
            m_neighbor_count++;                             // _ O _
        }                                                   // _ _ _

        if (cell_state_grid[m_x_pos][m_y_pos + 1]) {        // _ X _
            m_neighbor_count++;                             // _ O _
        }                                                   // _ _ _

        if (cell_state_grid[m_x_pos + 1][m_y_pos + 1]) {    // _ _ X
            m_neighbor_count++;                             // _ O _
        }                                                   // _ _ _

        if (cell_state_grid[m_x_pos + 1][m_y_pos]) {        // _ _ _
            m_neighbor_count++;                             // _ O X
        }                                                   // _ _ _

        if (cell_state_grid[m_x_pos + 1][m_y_pos - 1]) {    // _ _ _
            m_neighbor_count++;                             // _ O _
        }                                                   // _ _ X

        if (cell_state_grid[m_x_pos][m_y_pos - 1]) {        // _ _ _
            m_neighbor_count++;                             // _ O _
        }                                                   // _ X _

        if (cell_state_grid[m_x_pos - 1][m_y_pos - 1]) {    // _ _ _
            m_neighbor_count++;                             // _ O _
        }                                                   // X _ _

        if (cell_state_grid[m_x_pos - 1][m_y_pos]) {        // _ _ _
            m_neighbor_count++;                             // X O _
        }                                                   // _ _ _
    }

    /**
     * @brief check neighbor count, then update state according to the rules of Conway's Game of Life
     * 
     * @pre neighbour count should be updated
     * @return updated cell state
     */
    bool updateState() {
        if(m_neighbor_count == 3) {
            m_is_alive = true;
        } else if (m_neighbor_count == 2 && m_is_alive) {
            m_is_alive = true;
        } else {
            m_is_alive = false;
        }
        return m_is_alive;
    }

    int neighborCount() {
        return m_neighbor_count;
    }

    bool isAlive() {
        return m_is_alive;
    }
};
#endif // CELL_H