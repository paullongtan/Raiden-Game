//
//  main.h
//  Raiden
//
//  Created by 王彥普 on 2021/1/8.
//  Copyright © 2021 !!!. All rights reserved.
//

#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

#define MAX_NUMBER_OF_ITEMS 3

class Menu
{
private:
    int selectedItemIndex;
    Font font;
    Text menu[MAX_NUMBER_OF_ITEMS];
    Text title;
    Texture bg_texture;

public:
    Menu(float width, float height);
    ~Menu();

    void draw(RenderWindow &window);
    void MoveUp();
    void MoveDown();
    int GetPressedItem() {return selectedItemIndex;};

};
