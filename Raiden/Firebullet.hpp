#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/GpuPreference.hpp>
#include <iostream>
#include "config.h"

using namespace sf;

// 子彈
class FBullet
{
private:
    sf::RectangleShape bullet;
    bool outOfBorder = 0;
    
public:
    FBullet(Vector2f size);
    FBullet(Vector2f size, Color bulletColor);

    void setDirection();
    void fire(int speed);
    int getRight();
    int getLeft();
    int getTop();
    int getBottom();
    void draw(RenderWindow &window);
    void setPos(Vector2f newPos);
    void outBorder();
};
