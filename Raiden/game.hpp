//
//  game.hpp
//  Raiden
//
//  Created by 王彥普 on 2021/1/8.
//  Copyright © 2021 !!!. All rights reserved.
//

#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <ctime>
#include <cstdlib>
#include<unistd.h>
#include <vector>

#include "config.h"
#include "fighter.hpp"
#include "enemy.hpp"
#include "Firebullet.hpp"
#include "professor.hpp"
using namespace sf;

class Game
{
    friend class FBullet;
    friend class Enemy;
    
private:
    Texture t_vesta;
    Sprite vesta;
    Texture t_victory;
    Sprite victory;
    Texture t_defeated;
    Sprite defeated;
    RenderWindow window;
    
    Fighter* player1 = nullptr;
    Fighter* player2 = nullptr;
    Boss* LCK;
    int playerNum = 1;
    int bulletSpacing = 10;
    int bosebulSpacing = 50;
public:
    Game(); // init
    ~Game();
    void run();
    void reset();
    void deleteBullet(std::vector<FBullet>&, int);
};

