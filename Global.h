//
// Created by Rickard Karlsson on 2021-12-22.
//

#ifndef HELLOSFML_GLOBAL_H
#define HELLOSFML_GLOBAL_H

#include <string>
//! Global variables
const int DIFFICULTY_EASY = 1;
const int DIFFICULTY_MEDIUM = 2;
const int DIFFICULTY_HARD= 3;
const int ROW_AND_COLUMN_SIZE = 9;
const int ROW_AND_COLUMN_SIZE_2 = 16;
const int ROW_AND_COLUMN_SIZE_3 = 24;
const int MINES = 10;
const int MINES_2 = 40;
const int MINES_3 = 99;
const int CELL_SIZE = 16;

const std::string TITLE = "MineSweeper";
const std::string TITLE_GAME_OVER = "GAME OVER";
const std::string TITLE_GAME_WIN = "GAME WON";

const int SCREEN_SIZE_SMALLER_CELLS = 7;
const int SCREEN_SIZE_BIGGER_CELLS = 5;
const int WINDOW_SIZE_EASY = CELL_SIZE * ROW_AND_COLUMN_SIZE * SCREEN_SIZE_SMALLER_CELLS;
const int WINDOW_SIZE_MEDIUM = CELL_SIZE * ROW_AND_COLUMN_SIZE_2 * SCREEN_SIZE_BIGGER_CELLS;
const int WINDOW_SIZE_HARD = CELL_SIZE * ROW_AND_COLUMN_SIZE_3 * SCREEN_SIZE_BIGGER_CELLS;






#endif //HELLOSFML_GLOBAL_H
