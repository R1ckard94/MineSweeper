//
// Created by Rickard Karlsson on 2022-01-04.
//

#ifndef MINESWEEPER_GAMEEND_H
#define MINESWEEPER_GAMEEND_H



#include <SFML/Graphics.hpp>

class GameEnd{
    sf::Font font;
    //! the set font for the texts
    sf::Text gameOverText;
    //! game over or game won text depending on the outcome
    sf::Text timeText;
    //! game time text is always set regarding to how long it took for the user to win
public:
    explicit GameEnd(sf::Font& font);
    //! CTOR needs to get a font value from main in order to display it
    void draw(sf::RenderWindow& window);
    //! draw-function, takes in a RenderWindow object and displays the texts
    void setText(std::string title);
    //! set the title if the game is "won" or "over"
    void setTextColor(sf::Color color);
    //! sets the color of gameOvertext, Green if the game was won and Red if the game is over
    sf::Text getTimeText() const;
    //! returns the timetext object
    template<typename B>
    void setTimeText(long double time, B func){
        int timeMinutes = 0;
        while(func(time)){
            timeMinutes++;
            time = time-60.0;
        }
        if(timeMinutes > 0){
            timeText.setString("Time to Win:\n" + std::to_string(timeMinutes) + (timeMinutes > 1? " Minutes": " Minute")+ " and\n" + std::to_string(time) + " Seconds");
        }else{
            timeText.setString("Time to Win:\n" + std::to_string(time) + " Seconds");
        }
    }
    //! template function that takes in a time and a bool-function that determines how the time will be printed for the win, in minutes and seconds or just seconds
};


#endif //MINESWEEPER_GAMEEND_H
