#include <iostream>
#include <SFML/Graphics.hpp>
#include "Global.h"
#include "Grid.h"
#include "GameEnd.h"


template<typename T, typename G>
void setView(T& win, G& grid)
{
    win.setView(sf::View(sf::FloatRect(0, 0, CELL_SIZE * grid.size(), CELL_SIZE * grid.size())));
}

int main()
{
    bool firstCell = false;
    sf::Vector2i CurrentMousePosition;
    std::chrono::time_point<std::chrono::steady_clock> timeStart;
    std::chrono::time_point<std::chrono::steady_clock> timeStop;
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE_EASY, WINDOW_SIZE_EASY), TITLE, sf::Style::Close);

    sf::Font font;
    if(!font.loadFromFile("Resources/Fonts/SourceCode.ttf")){
        std::cout<<"failed to load font from file\n";
        system("pause");
    }
    GameEnd gameEnd(font);

    Grid grid;
    setView(window, grid);

    while (window.isOpen())
    {
        sf::Event event{};

        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed){
                window.close();
            }
            if(event.type == sf::Event::MouseButtonReleased){
                CurrentMousePosition = sf::Mouse::getPosition(window);
                int mouseCoordX = (CurrentMousePosition.x / CELL_SIZE / (grid.size() == ROW_AND_COLUMN_SIZE? SCREEN_SIZE_SMALLER_CELLS:SCREEN_SIZE_BIGGER_CELLS));
                int mouseCoordY = (CurrentMousePosition.y / CELL_SIZE / (grid.size() == ROW_AND_COLUMN_SIZE? SCREEN_SIZE_SMALLER_CELLS:SCREEN_SIZE_BIGGER_CELLS));
                if(event.mouseButton.button == sf::Mouse::Left){
                    if(!firstCell){
                        timeStart = std::chrono::high_resolution_clock::now();
                        firstCell = true;
                    }
                    grid.openCell(mouseCoordX, mouseCoordY);

                }
                if(event.mouseButton.button == sf::Mouse::Right){
                    grid.flagCell(mouseCoordX, mouseCoordY);
                }
            }
            if(event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::Num1){
                    if(grid.size() != ROW_AND_COLUMN_SIZE){
                        window.close();
                        window.create(sf::VideoMode(WINDOW_SIZE_EASY,WINDOW_SIZE_EASY),TITLE, sf::Style::Close);
                        Grid tmp(DIFFICULTY_EASY);
                        grid = tmp;
                        setView(window, grid);
                    }
                    grid.restart();
                    firstCell = false;
                }
                if(event.key.code == sf::Keyboard::Num2){
                    if(grid.size() != ROW_AND_COLUMN_SIZE_2) {
                        window.close();
                        window.create(sf::VideoMode(WINDOW_SIZE_MEDIUM, WINDOW_SIZE_MEDIUM), TITLE, sf::Style::Close);
                        Grid tmp(DIFFICULTY_MEDIUM);
                        grid = tmp;
                        setView(window, grid);
                    }
                    grid.restart();
                    firstCell = false;
                }
                if(event.key.code == sf::Keyboard::Num3){
                    if(grid.size() != ROW_AND_COLUMN_SIZE_3) {
                        window.close();
                        window.create(sf::VideoMode(WINDOW_SIZE_HARD, WINDOW_SIZE_HARD), TITLE, sf::Style::Close);
                        Grid tmp(DIFFICULTY_HARD);
                        grid = tmp;
                        setView(window, grid);
                    }
                    grid.restart();
                    firstCell = false;
                }
                if(event.key.code == sf::Keyboard::R){
                    grid.restart();
                    firstCell = false;
                }
                if(event.key.code == sf::Keyboard::Q){
                    window.close();
                }
            }

        }

        window.clear();
        grid.drawBoard(window);
        window.display();
        if(grid.isGameOver() || grid.isGameWon()){
            timeStop = std::chrono::high_resolution_clock::now();
            std::chrono::duration<long double> timeTook = std::chrono::duration<double>(timeStop - timeStart);

            sf::RenderWindow gameOverWindow(sf::VideoMode(600, 400), TITLE_GAME_OVER, sf::Style::Close);
            gameEnd.setTimeText(timeTook.count(), [](long double time)->bool{ // lambda to check how the time should be printed
                if(time>59){ //since this is in seconds 
                    return true;
                }
                return false;
            });

            if(grid.isGameWon()){
                gameEnd.setText(TITLE_GAME_WIN);
                gameEnd.setTextColor(sf::Color::Green);
                gameOverWindow.setTitle(TITLE_GAME_WIN);

            }else{
                gameEnd.setText(TITLE_GAME_OVER);
                gameEnd.setTextColor(sf::Color::Red);
            }
            while(gameOverWindow.isOpen()){

                while (gameOverWindow.pollEvent(event)) {
                    if (event.type == sf::Event::Closed){
                        gameOverWindow.close();
                        window.close();
                    }
                    if(event.type == sf::Event::KeyPressed){
                        if(event.key.code == sf::Keyboard::R){
                            firstCell = false;
                            grid.restart();
                            gameOverWindow.close();
                        }
                        if(event.key.code == sf::Keyboard::Q){
                            gameOverWindow.close();
                            window.close();
                        }

                    }

                }
                gameOverWindow.clear(sf::Color(200,200,200,0));
                gameEnd.draw(gameOverWindow);
                if(grid.isGameWon()){
                    gameOverWindow.draw(gameEnd.getTimeText());
                }
                gameOverWindow.display();
            }

        }

    }
}