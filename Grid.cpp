//
// Created by Rickard Karlsson on 2021-12-22.
//

#include "Grid.h"
#include "Global.h"



Grid::Grid():rowAndColumnSize(ROW_AND_COLUMN_SIZE), amountOfMines(MINES), difficulty(DIFFICULTY_EASY)
{
    fillVector();
}

Grid::Grid(int difficulty):difficulty(difficulty)
{
    if(difficulty == DIFFICULTY_MEDIUM){
        rowAndColumnSize = ROW_AND_COLUMN_SIZE_2;
        amountOfMines = MINES_2;
        fillVector();
    }
    else if(difficulty == DIFFICULTY_HARD){
        rowAndColumnSize = ROW_AND_COLUMN_SIZE_3;
        amountOfMines = MINES_3;
        fillVector();
    }
    else{
        Grid tmp;
        *this = tmp;
    }

}

Grid::Grid(const Grid& rhs)://Copy CTOR
board(rhs.board),
gameOver(rhs.gameOver),
gameWon(rhs.gameWon),
rowAndColumnSize(rhs.rowAndColumnSize),
amountOfMines(rhs.amountOfMines),
difficulty(rhs.difficulty)
{}

Grid& Grid::operator=(const Grid& rhs)//Copy assign
{
    Grid tmp(rhs);
    swap(tmp);
    return *this;
}

Grid::~Grid() = default;

void Grid::fillVector()
{
    std::vector<Cell> tmp;
    for (int y = 0; y < rowAndColumnSize; y++)
    {
        tmp.clear();
        for(int x = 0; x < rowAndColumnSize; x++)
        {
            tmp.push_back(Cell(x, y));
        }
        board.push_back(tmp);
    }
    //sets random cells to mines
    generateMines();
    countAdjacentMines();
}

void Grid::swap(Grid rhs)
{
    std::swap(rhs.board,this->board);
    std::swap(rhs.gameOver, this->gameOver);
    std::swap(rhs.gameWon, this->gameWon);
    std::swap(rhs.rowAndColumnSize, this->rowAndColumnSize);
    std::swap(rhs.amountOfMines, this->amountOfMines);
    std::swap(rhs.difficulty,this->difficulty);
}

Grid& Grid::restart()
{
    Grid tmp(difficulty);
    *this = tmp;
    return *this;
}


bool Grid::isGameOver() const
{
    return gameOver;
}


bool Grid::isGameWon() const
{
    return gameWon;
}

int Grid::size() const
{
    return rowAndColumnSize;
}

void Grid::drawBoard(sf::RenderWindow& window)
{
    sf::RectangleShape cell(sf::Vector2f(CELL_SIZE - 1 , CELL_SIZE - 1));
    sf::Sprite iconSprite;
    sf::Texture iconTexture;
    sf::Sprite iconSprite2;
    sf::Texture iconTexture2;
    unopenedCellsLeft = (rowAndColumnSize*rowAndColumnSize)-amountOfMines;

    iconTexture.loadFromFile("Resources/Images/Icons16.png");
    iconSprite.setTexture(iconTexture);


    for(int y = 0; y<rowAndColumnSize; y++){
        for(int x = 0; x<rowAndColumnSize; x++){
            if(!board[y][x].isOpen()){  //if the cell is closed
                    cell.setFillColor(sf::Color::White);
                    cell.setPosition(static_cast<float>(CELL_SIZE * x), static_cast<float>(CELL_SIZE * y));
                    window.draw(cell);
                if(board[y][x].isFlagged()) {
                    iconSprite.setPosition(static_cast<float>(CELL_SIZE * x), static_cast<float>(CELL_SIZE * y));
                    iconSprite.setTextureRect(sf::IntRect(0, 0, CELL_SIZE+2, CELL_SIZE+2));
                    window.draw(iconSprite);
                }
                else if(isGameOver() && board[y][x].isMine()){
                    cell.setFillColor(sf::Color::Red);
                    window.draw(cell);
                }
            }else{  //if the cell is open
                if(!board[y][x].isMine()){
                    cell.setFillColor(sf::Color(150,150,150));
                    unopenedCellsLeft--;
                    if(unopenedCellsLeft == 0){
                        gameWon = true;
                    }
                }else{
                    cell.setFillColor(sf::Color::Red);
                }
                int minesAround = board[y][x].getAmountOfMinesAdjacent();
                cell.setPosition(static_cast<float>(CELL_SIZE * x), static_cast<float>(CELL_SIZE * y));

                window.draw(cell);
                if(0 < minesAround){
                    iconSprite.setPosition(static_cast<float>(CELL_SIZE * x), static_cast<float>(CELL_SIZE * y));
                    iconSprite.setTextureRect(sf::IntRect(CELL_SIZE * minesAround, 0, CELL_SIZE+1, CELL_SIZE));

                    window.draw(iconSprite);
                }
            }


        }
    }

}

void Grid::countAdjacentMines()
{
    for(int i = 0; i<rowAndColumnSize; i++){
        for(int j = 0; j<rowAndColumnSize; j++){
            board[i][j].countAdjacentMines(board);
        }
    }

}

void Grid::generateMines()
{
    srand(time(NULL));

    unsigned int mineX;
    unsigned int mineY;
    for(int i = 0; i<amountOfMines; i++){

        mineX = rand() % rowAndColumnSize;
        mineY = rand() % rowAndColumnSize;

        if(board[mineY][mineX].isMine()){
            i--;
        }else{
            board[mineY][mineX].setMine(true);
        }
    }
}

void Grid::flagCell(int coordX, int coordY)
{
    if(!board[coordY][coordX].isOpen()){
        board[coordY][coordX].flagCell();
    }
}

void Grid::openCell(int coordX, int coordY)
{
    if(!board[coordY][coordX].isFlagged()){
        Cell& currCell = board[coordY][coordX];
        currCell.openCell();
        if(currCell.isMine()){
            gameOver = true;
            return;
        }
        if(currCell.getAmountOfMinesAdjacent() == 0){
            for(int y = -1 ; y<=1; y++){ //on the y-axis we want to move 3 steps
                for(int x = -1; x<=1; x++){//on the x-axis we want to move 3 steps aswell except when we reach ourown spot
                    if(y == 0 && x == 0){ //
                        continue;
                    }
                    try
                    {

                        Cell& tmp = board.at(y+coordY).at(x+coordX);   //in order to trigger the out of bounds check we make this reference
                        if(!tmp.isOpen()){
                            openCell(x+coordX,y+coordY);      //if the cell alrdy is open we dont open it again
                        }
                    }
                    catch(const std::out_of_range & e)
                    {
                        //catches errors when edges tries to check for cells out of bounds of the vector, and program keeps running
                    }
                }
            }
        }
    }
}



