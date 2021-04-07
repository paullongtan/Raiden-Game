//
//  menu.cpp
//  Raiden
//
//  Created by 王彥普 on 2021/1/8.
//  Copyright © 2021 !!!. All rights reserved.
//

#include "menu.hpp"


Menu::Menu(float width, float height)
{
    if (!font.loadFromFile("Raiden/Resources/fonts/prstartk.ttf"))
    {
        font.loadFromFile("../Resources/fonts/prstartk.ttf");
        // handle error
    }
    
    if (!bg_texture.loadFromFile("Raiden/Resources/images/menu.jpg"))
    {
        bg_texture.loadFromFile("../Resources/images/menu.jpg");
        // handle error
    }
    
    title.setFont(font);
    title.setColor(Color(255, 211, 92, 250));
    title.setString("IM-Raiden");
    title.setCharacterSize(60);
    // title.setScale(Vector2f(2, 2));
    title.setPosition(Vector2f(width / 2 - 200, height / (MAX_NUMBER_OF_ITEMS + 2) * 1));

    menu[0].setFont(font);
    menu[0].setColor(Color(254, 255, 212, 255));
    menu[0].setString("Play");
    menu[0].setPosition(Vector2f(width / 2 - 80, height / (MAX_NUMBER_OF_ITEMS + 2) * 2));

    menu[1].setFont(font);
    menu[1].setColor(Color(255, 255, 255, 180));
    menu[1].setString("Instructions");
    menu[1].setPosition(Vector2f(width / 2 - 80, height / (MAX_NUMBER_OF_ITEMS + 2) * 3 - 50));
    menu[2].setFont(font);
    menu[2].setColor(Color(255, 255, 255, 180));
    menu[2].setString("Quit");
    menu[2].setPosition(Vector2f(width / 2 - 80, height / (MAX_NUMBER_OF_ITEMS + 2) * 4 - 100));

    selectedItemIndex = 0;
}

Menu::~Menu()
{
    ;
}

void Menu::draw(RenderWindow &window)
{
    window.clear();
    Sprite bg;
    bg.setTexture(bg_texture);
    // bg_texture.update(window);
    // bg.setTexture(bg_texture);
    window.draw(bg);
    // window.draw(title);
    for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
    {
        window.draw(menu[i]);
    }
}

void Menu::MoveUp()
{
    if (selectedItemIndex - 1 >= 0)
    {
        menu[selectedItemIndex].setColor(Color(255, 255, 255, 180));
        selectedItemIndex--;
        menu[selectedItemIndex].setColor(Color(254, 255, 212, 255));
    }
}

void Menu::MoveDown()
{
    if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
    {
        menu[selectedItemIndex].setColor(Color(255, 255, 255, 180));
        selectedItemIndex++;
        menu[selectedItemIndex].setColor(Color(254, 255, 212, 255));
    }
}
