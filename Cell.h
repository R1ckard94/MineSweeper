//
// Created by Rickard Karlsson on 2021-12-22.
//

#ifndef HELLOSFML_CELL_H
#define HELLOSFML_CELL_H


#include <vector>

class Cell {
    int xCoord;
    //! Coordinate X
    int yCoord;
    //! coordinate Y
    bool mine;
    //! if the cell is a mine this is set to true
    int amountOfMinesAdjacent;
    //! if the cell is not a mine holds the value of neighboring mines that exists in the vector to the cell
    bool flagged;
    //! a bool to determine if the cell is flagged or not
    bool open;
    //! a bool to determine if the cell is open or not

public:
    Cell(int x, int y);
    //! simple CTOR to create Cell class, X and Y are the coordinates according to the vector matrix
    bool isOpen() const;
    //! checks if a cell is open
    void openCell();
    //! opens a cell by setting its bool value to true
    void flagCell();
    //! flags and unflags a cell
    bool isFlagged() const;
    //! checks if a cell is flagged
    void setMine(bool is_a_Mine);
    //! sets a cell to carry a mine
    bool isMine() const;
    //! check if a cell is a mine or not
    void countAdjacentMines(std::vector<std::vector<Cell>>& cellsVector);
    //! Recursive
    int getAmountOfMinesAdjacent() const;
    //! returns the amount of cells around a cell given by the function countAdjacentMines
};


#endif //HELLOSFML_CELL_H
