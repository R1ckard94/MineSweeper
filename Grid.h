//
// Created by Rickard Karlsson on 2021-12-22.
//

#ifndef HELLOSFML_GRID_H
#define HELLOSFML_GRID_H
#include "Cell.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>

class Grid {
    std::vector<std::vector<Cell>> board;
    //! the 2D vector in which the cells are placed
    bool gameOver = false;
    //! a bool to determine if the game is lost/over
    bool gameWon = false;
    //! a bool to determine if the game is won
    int rowAndColumnSize;
    //! a size indicator of the row/column size for the vector, this value is the same as board.size()
    int amountOfMines;
    //! the grid will hold a certain amount of mines depending on the difficulty
    int difficulty;
    //! value of the grids difficulty
    int unopenedCellsLeft;
    //! amount of unopened cells, counts down in the draw function to check when all the cells that doesnt contain a mine are open in order to let the program know that the user has won
    void swap(Grid rhs);
    //! private swap function
    void fillVector();
    //! private fill function that fills the vector with Cells and assigns coordinates to each
public:
    Grid();
    //! default CTOR
    Grid(int difficulty);
    //! CTOR with assignable difficulty
    Grid(const Grid& rhs);
    //! Copy-CTOR
    ~Grid();
    //! DTOR
    Grid& restart();
    //! Restart function to make a new grid and rerun the program
    Grid& operator=(const Grid& rhs);
    //! copy-assign
    void drawBoard(sf::RenderWindow& window);
    //! drawboard function, takes in a RenderWindow object and draws the 2D vector of the game
    void generateMines();
    //! generate mines inside the 2D vector randomly
    void countAdjacentMines();
    //! each cell checks its neighbors and count how many have mines
    void flagCell(int coordX, int coordY);
    //! flags and unflags a cell. A cell that is open can not be flagged
    void openCell(int coordX, int coordY);
    //! opens a cell. A cell that is flagged can not be opened unless it is unflagged.
    //! If a cell doesnt have any mines around it the cell opens recursively opens its neighbours checking if they also have zero mines around
    bool isGameOver() const;
    //! Returns bool if the game is lost
    bool isGameWon() const;
    //! Returns bool if the game is won
    int size() const;
    //! Returns the size of a row/column
};


#endif //HELLOSFML_GRID_H
