/*
    Copyright (C) 2018 Martin Sandsmark <martin.sandsmark@kde.org>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once

#include "core/Types.h"

#include "TextButton.h"
#include "UiScreen.h"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <array>
#include <string>


struct TextButton;

namespace sf {
class Event;
}

class HomeScreen : public UiScreen
{
public:
    ~HomeScreen();
    struct Button {
        enum Type {
            Singleplayer = 0,
            Multiplayer = 1,
            Zone = 2,
            Tutorial = 3,
            MapEditor = 4,
            History = 5,
            Options = 6,
            About = 7,
            Banner = 8,
            Exit = 9,
            TypeCount
        };

        ScreenRect rect;


        int frame = 0;

        std::string description;

        sf::Texture texture;
        sf::Texture hoverTexture;
        sf::Texture selectedTexture;

        ScreenPos offset;
        ScreenPos hoverOffset;
        ScreenPos selectedOffset;

        sf::Text text;
        ScreenRect textRect;
    };
    enum GameTypeChoice {
        Campaign,
        StandardGame,
        GameTypeCount
    };

    HomeScreen();

    bool init();

    Button::Type getSelection();
    GameTypeChoice getGameType() const { return (m_gameType == -1) ? GameTypeChoice::StandardGame : GameTypeChoice(m_gameType); }

private:
    void render();
    bool handleMouseEvent(const sf::Event &event);

    std::array<Button, Button::TypeCount> m_buttons;

    ScreenRect m_descriptionRect;
    sf::Text m_description;
    sf::Text m_todoText;
    sf::Text m_versionText;
    std::array<TextButton, GameTypeChoice::GameTypeCount> m_textButtons;

    int m_hoveredButton = -1;
    int m_selectedButton = -1;
    int m_gameType = -1;
};
