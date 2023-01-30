//
// Created by Rickard Karlsson on 2021-12-22.
//

#include "Cell.h"

Cell::Cell(int x, int y):mine(false),xCoord(x),yCoord(y), amountOfMinesAdjacent(0)
{
    open = false;
    flagged = false;
}


void Cell::setMine(bool is_a_Mine)
{
    mine = is_a_Mine;
}

bool Cell::isMine() const
{
    return mine;
}

bool Cell::isFlagged() const
{
    return flagged;
}

bool Cell::isOpen() const
{
    return open;
}

void Cell::openCell()
{
    open = true;
}

void Cell::flagCell()
{
    flagged = !(flagged);
}

int Cell::getAmountOfMinesAdjacent() const
{
    return amountOfMinesAdjacent;
}

void Cell::countAdjacentMines(std::vector<std::vector<Cell>>& cellsVector)
{
    //if this is a mine we don't count
    if(!mine){
        for(int y = -1 ; y<=1; y++){ //on the y-axis we want to move 3 steps
            for(int x = -1; x<=1; x++){//on the x-axis we want to move 3 steps aswell except when we reach ourown spot
                if(y == 0 && x == 0){ //
                    continue;
                }
                try
                {
                    if(cellsVector.at(y+yCoord).at(x+xCoord).isMine()){
                        amountOfMinesAdjacent++;
                    }
                }
                catch(const std::out_of_range& e)
                {
                    //throws errors when edges tries to check for cells out of bounds of the vector
                }
            }
        }
    }
}
