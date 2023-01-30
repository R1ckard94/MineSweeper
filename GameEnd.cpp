//
// Created by Rickard Karlsson on 2022-01-04.
//

#include "GameEnd.h"
#include <iostream>

GameEnd::GameEnd(sf::Font& aFont):font(aFont)
{
    gameOverText.setFont(font);
    gameOverText.setString("Game Over");
    gameOverText.setCharacterSize(60);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setOutlineColor(sf::Color::Black);
    gameOverText.setOutlineThickness(2.0);
    gameOverText.setStyle(sf::Text::Style::Bold | sf::Text::Style::Italic);
    gameOverText.setPosition(135.0,0.0);
    timeText.setFont(font);
    timeText.setCharacterSize(26);
    timeText.setFillColor(sf::Color::Black);
    timeText.setPosition(87.5,75.0);
}

void GameEnd::draw(sf::RenderWindow &window)
{
    sf::RectangleShape infoBox(sf::Vector2f(460.0,150.0));
    sf::Text restartText, quitText;

    infoBox.setPosition(80.0,200.0);
    infoBox.setFillColor(sf::Color::Black);

    restartText.setFont(font);
    restartText.setString("Press R to Restart");
    restartText.setCharacterSize(40);
    restartText.setPosition(87.5, 210.0);
    restartText.setFillColor(sf::Color::White);

    quitText.setFont(font);
    quitText.setString("Press Q to Quit");
    quitText.setCharacterSize(40);
    quitText.setPosition(87.5,260.0);
    quitText.setFillColor(sf::Color::White);

    window.draw(gameOverText);
    window.draw(infoBox);
    window.draw(restartText);
    window.draw(quitText);

}

void GameEnd::setText(const std::string title)
{
    gameOverText.setString(title);
}

void GameEnd::setTextColor(const sf::Color color)
{
    gameOverText.setFillColor(color);
}
sf::Text GameEnd::getTimeText() const
{
    return timeText;
}