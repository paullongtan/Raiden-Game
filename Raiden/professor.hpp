//
//  professor.hpp
//  
//
//  Created by 王彥普 on 2021/1/10.
//

#pragma once
#include <SFML/Graphics.hpp>
#include "config.h"
#include "Firebullet.hpp"
using namespace sf;

// Boss
class Boss
{
private:
    int health = 15000;
    Texture t_plane;
    Sprite plane;
    Sprite planeHit;
    bool alive = 1;
    int moveType = 1;
    bool showHit = 0;
    
public:
    Boss();
    void reset();
    float getX() const;
    float getY() const;
    void setPosition(float x, float y);
    void move(float dt);
    float planeWidth() const;
    float planeHeight() const;
    int getPlayerNum() const;
    void checkCollision(FBullet& bullet);
    void draw(RenderWindow& window);
    bool getAlive() const;
    int getHealth() const;
    
};
