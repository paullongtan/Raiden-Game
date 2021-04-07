//
//  fighter.hpp
//  Raiden
//
//  Created by 王彥普 on 2021/1/9.
//  Copyright © 2021 !!!. All rights reserved.
//

#pragma once
#include "config.h"
#include <SFML/Graphics.hpp>
#include "Firebullet.hpp"
#include "enemy.hpp"

using namespace sf;

class Fighter
{
    friend class Game;
public:
    
    Fighter();
    ~Fighter();
    float getX() const;
    float getY() const;
    void setPosition(float x, float y);
    void move(float x, float y);
    float planeWidth() const;
    float planeHeight() const;
    int getPlayerNum() const;
    void checkCollision(FBullet& bullet);
    void checkCollisionEnemy(Enemy& enemy);
    void draw(RenderWindow& window);
    void reset();

    
private:
    Texture t_plane;
    Sprite plane;
    
    int health = 10000;
    const int maxHealth = 10000;
    int life = 3;
    int points = 0;
    int bulletType = 1;
    bool alive = 1;
    static int playerNum;
    
    
};
