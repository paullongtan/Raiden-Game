//
//  game.cpp
//  Raiden
//
//  Created by 王彥普 on 2021/1/8.
//  Copyright © 2021 !!!. All rights reserved.
//

#include "game.hpp"
using namespace sf;

Game::Game() { ; }

Game::~Game() { ; }

void Game::run()
{

  // 背景照片讀入
    if (!t_vesta.loadFromFile("Raiden/Resources/images/Vesta.jpg"))
    {
        t_vesta.loadFromFile("../Resources/images/Vesta.jpg");
    }
    
    if (!t_victory.loadFromFile("Raiden/Resources/images/victory.jpg"))
    {
        t_victory.loadFromFile("../Resources/images/victory.jpg");
    }
    
    if (!t_defeated.loadFromFile("Raiden/Resources/images/defeated.png"))
    {
        t_defeated.loadFromFile("../Resources/images/defeated.png");
    }
    
    // 音效設定
    SoundBuffer bExplode;
    if (!bExplode.loadFromFile("Raiden/Resources/audio/explode.wav"))
    {
        bExplode.loadFromFile("../Resources/audio/explode.wav");
    }
    Sound explode;
    explode.setVolume(80);
    explode.setBuffer(bExplode);
    bool boom = 0;
    bool boomP2 = 0;
    bool boomBoss = 0;
    
    SoundBuffer bAngry;
    if (!bAngry.loadFromFile("Raiden/Resources/audio/angry.wav"))
    {
        bAngry.loadFromFile("../Resources/audio/angry.wav");
    }
    Sound angry;
    angry.setVolume(80);
    angry.setBuffer(bAngry);
    bool bossAngry = 0;
    
    // 戰機物件建立
    playerNum = 1;
    player1 = new Fighter;
    player2 = new Fighter;
    LCK = new Boss;
    
    RenderWindow window(VideoMode(WIDTH, HEIGHT), "RAIDEN");
    window.setFramerateLimit(120);
    vesta.setTexture(t_vesta);
    vesta.setPosition(0, 0);
    victory.setTexture(t_victory);
    victory.setPosition(0, 0);
    defeated.setTexture(t_defeated);
    defeated.setScale(1.69, 1.69);
    defeated.setPosition(0, 0);

    //window.setKetRepeatEnabled = true;

  
    // 用於展示玩家剩餘血量
    RectangleShape playerHpBar;
    RectangleShape playerHpBarBack;
    playerHpBar.setSize(sf::Vector2f(300.f, 25.f));
    playerHpBar.setFillColor(sf::Color::Blue);
    playerHpBar.setPosition(sf::Vector2f(20.f, 20.f));

    RectangleShape playerHpBar2;
    RectangleShape playerHpBarBack2;
    playerHpBarBack2 = playerHpBar2;
    playerHpBar2.setSize(sf::Vector2f(300.f, 25.f));
    playerHpBar2.setFillColor(sf::Color::Green);
    playerHpBar2.setPosition(sf::Vector2f(580.f, 20.f));
    playerHpBarBack2 = playerHpBar2;
    playerHpBarBack2.setFillColor(sf::Color(25, 25, 25, 200));

    // 開始計時
    Clock clock;
    float timer = 0;
    float speed = 500;
    float lastShoot = 0;
    float lastShoot2 = 0;
    
    // 用於處理新生成敵人及子彈的vector
    std::vector<FBullet> bulletvecLeft;
    std::vector<FBullet> bulletvecRight;
    std::vector<FBullet> bulletvecLeft2;
    std::vector<FBullet> bulletvecRight2;
    std::vector<FBullet> bulletvecLeftLCK;
    std::vector<FBullet> bulletvecRightLCK;
    std::vector<FBullet> bulletvecAngry;
    std::vector<Enemy> dogs;
    std::vector<Enemy> biggerDogs;
    
    // 儲存玩家射擊狀態
    bool isFiring = false;
    bool isFiring2 = false;
    float winTime = 0;
    float loseTime = 0;

    while (window.isOpen())
    {
        // 過去時間累積及時鐘重設
        float dt = clock.restart().asSeconds();
//        std::cout << "W:" << winTime;
//        std::cout << "L:" << loseTime;
//        std::cout << "T:" << timer;
        timer += dt;
        lastShoot += dt;
        lastShoot2 += dt;
        if (LCK->getAlive() == 0)
            winTime += dt;
        if (player1->alive == 0)
        {
            if (playerNum == 2)
            {
                if (player2->alive == 0)
                    loseTime += dt;
            }
            else
                loseTime += dt;
        }

        Event e; // 聆聽事件
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
            {
                window.close();
            }
            if (e.type == Event::KeyPressed && e.key.code == Keyboard::Escape)
            {
                window.close();
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::W)) // Up
        {
            player1->move(0.f, -speed * dt);
            if (player1->getY() <= 0) // 邊界設定
                player1->setPosition(player1->getX(), 0.f);
        }
        
        if (Keyboard::isKeyPressed(Keyboard::S)) // Bottom
        {
            player1->move(0.f, speed * dt);
            if (player1->getY() >= window.getSize().y - player1->planeHeight())
                player1->setPosition(player1->getX(), window.getSize().y - player1->planeHeight());
        }
        
        if (Keyboard::isKeyPressed(Keyboard::A)) // Left
        {
            player1->move(-speed * dt * 1.2, 0.f);
            if (player1->getX() <= 0)
                player1->setPosition(0.f, player1->getY());
        }
        if (Keyboard::isKeyPressed(Keyboard::D)) // Right
        {
            player1->move(speed * dt * 1.2, 0.f);
            if (player1->getX() >= window.getSize().x - player1->planeWidth())
                player1->setPosition(window.getSize().x - player1->planeWidth(),player1->getY());
        }

        if (Keyboard::isKeyPressed(Keyboard::LShift))  // 處於射擊狀態
            isFiring = true;

        // 召喚玩家二
        if (Keyboard::isKeyPressed(Keyboard::Enter))
        {
            playerNum = 2;
            loseTime = 0;
            lastShoot2 = 0;
        }

        // 當有兩位玩家時
        if (playerNum == 2)
        {
            if (Keyboard::isKeyPressed(Keyboard::Up))
            {
                player2->move(0.f, -speed * dt);
                if (player2->getY() <= 0)  // Up
                    player2->setPosition(player2->getX(), 0.f);
            }
            if (Keyboard::isKeyPressed(Keyboard::Down)) // Down
            {
                player2->move(0.f, speed * dt);
                if (player2->getY() >=
                    window.getSize().y - player2->planeHeight())
                    player2->setPosition(player2->getX(), window.getSize().y - player2->planeHeight());
            }
            if (Keyboard::isKeyPressed(Keyboard::Left)) // Left
            {
                player2->move(-speed * dt * 1.2, 0.f);
                if (player2->getX() <= 0)
                    player2->setPosition(0.f, player2->getY());
            }
            if (Keyboard::isKeyPressed(Keyboard::Right)) // Right
            {
                player2->move(speed * dt * 1.2, 0.f);
                if (player2->getX() >= window.getSize().x - player2->planeWidth())
                    player2->setPosition(window.getSize().x - player2->planeWidth(),
                              player2->getY());
            }

            if (Keyboard::isKeyPressed(Keyboard::M)) // 屬於射擊狀態
                isFiring2 = true;
        }

        LCK->move(dt); // boss移動狀態切換
        window.clear();
        window.draw(vesta);
        
        // 飛機繪製
        LCK->draw(window);
        player1->draw(window);
        if (playerNum == 2)
            player2->draw(window);

        /* 固定亂數種子 */
        srand(time(NULL));

        // enemy物件建立
        if (time(NULL) % 2 == 1)
        {
            int pos_x = (rand() + 67) % 500;
            Enemy dog(pos_x, 0, window, 1);
            dogs.push_back(dog);
        }
        if (time(NULL) % 7 == 1)
        {
            int pos_x = (rand() + 91) % 500;
            Enemy biggerDog(pos_x, 0, window, 2);
            biggerDogs.push_back(biggerDog);
        }

        // 當Boss仍存活時持續生成一般敵人
        if (LCK->getAlive() == 1)
        {
            for (int i = 0; i < dogs.size(); i += 120)
            {
                if (dogs[i].life <= 0)
                    continue;
                if (dogs[i].getTop() > 1500)
                {
                    dogs[i].life = 0;
                    dogs[i].setPos(10000, 10000);
                    continue;
                }
                dogs[i].draw(window); // 敵人繪製
                dogs[i].fly(speed * dt * 0.8); // 敵人移動
            }

            for (int i = 0; i < biggerDogs.size(); i += 120)
            {
                if (biggerDogs[i].life <= 0)
                    continue;
                if (biggerDogs[i].getTop() > 1500)
                {
                    biggerDogs[i].life = 0;
                    biggerDogs[i].setPos(10000, 10000);
                    continue;
                }
                biggerDogs[i].draw(window);
                biggerDogs[i].fly(speed * dt * 0.6);
            }
        }

        if (isFiring == true)
        {
            // 生成新的子彈object並設定其位置(玩家一)
            if (lastShoot >= 0.2)
            {
                FBullet newBulletLeft(Vector2f(10, 20));
                FBullet newBulletRight(Vector2f(10, 20));
                newBulletLeft.setPos(Vector2f(player1->getX() + player1->planeWidth() * (3 / 7), player1->getY()));
                newBulletRight.setPos(sf::Vector2f(player1->getX() + player1->planeWidth(), player1->getY()));
                bulletvecLeft.push_back(newBulletLeft);
                bulletvecRight.push_back(newBulletRight);
                lastShoot = 0;
            }
            isFiring = false; // 將射擊狀態改回false
        }

        for (int i = 0; i < bulletvecLeft.size(); i += 1)
        {
            // 確認子彈是否與敵人碰撞
            LCK->checkCollision(bulletvecLeft[i]);
            LCK->checkCollision(bulletvecRight[i]);
            for (int j = 0; j < dogs.size(); j++)
            {
                dogs[j].checkCollision(bulletvecLeft[i]);
                dogs[j].checkCollision(bulletvecRight[i]);
            }
            for (int j = 0; j < biggerDogs.size(); j++)
            {
                biggerDogs[j].checkCollision(bulletvecLeft[i]);
                biggerDogs[j].checkCollision(bulletvecRight[i]);
            }
            // 子彈繪製與移動
            bulletvecLeft[i].draw(window);
            bulletvecLeft[i].fire(speed * dt * 1.2);
            bulletvecRight[i].draw(window);
            bulletvecRight[i].fire(speed * dt * 1.2);
        }
//      deleteBullet(bulletvecLeft, bulletSpacing);
//      deleteBullet(bulletvecRight, bulletSpacing);
      
        // 確認玩家與敵人的碰撞
        for (int i = 0; i < dogs.size(); i++)
        {
            player1->checkCollisionEnemy(dogs[i]);
            player2->checkCollisionEnemy(dogs[i]);
        }
        for (int i = 0; i < biggerDogs.size(); i++)
        {
            player1->checkCollisionEnemy(biggerDogs[i]);
            player2->checkCollisionEnemy(biggerDogs[i]);
        }

        // 玩家二子彈object生成
        if (isFiring2 == true)
        {
            if (lastShoot2 > 0.2)
            {
                Color p2B = Color::Green;
                FBullet newBulletLeft2(Vector2f(10, 20), p2B);
                FBullet newBulletRight2(Vector2f(10, 20), p2B);
                newBulletLeft2.setPos(Vector2f(player2->getX() + player2->planeWidth() * (3 / 7), player2->getY()));
                newBulletRight2.setPos(Vector2f(player2->getX() + player2->planeWidth(), player2->getY()));
                bulletvecLeft2.push_back(newBulletLeft2);
                bulletvecRight2.push_back(newBulletRight2);
                lastShoot2 = 0;
            }
                isFiring2 = false;
        }
        
        // 玩家二子彈繪製與移動
        for (int i = 0; i < bulletvecLeft2.size(); i += 1)
        {
            // 子彈與敵人碰撞的檢測
            for (int j = 0; j < dogs.size(); j++)
            {
                dogs[j].checkCollision(bulletvecLeft2[i]);
                dogs[j].checkCollision(bulletvecRight2[i]);
            }
            for (int j = 0; j < biggerDogs.size(); j++)
            {
                biggerDogs[j].checkCollision(bulletvecLeft2[i]);
                biggerDogs[j].checkCollision(bulletvecRight2[i]);
            }
            LCK->checkCollision(bulletvecLeft2[i]);
            LCK->checkCollision(bulletvecRight2[i]);
            bulletvecLeft2[i].draw(window);
            bulletvecRight2[i].draw(window);
            bulletvecLeft2[i].fire(speed * dt * 1.2);
            bulletvecRight2[i].fire(speed * dt * 1.2);
            
        }
          //deleteBullet(bulletvecLeft2, bulletSpacing);
          //deleteBullet(bulletvecRight2, bulletSpacing);
      
        // LCK Bullet
        Color pR = Color::Red;
        FBullet newBulletLeftLCK(Vector2f(20,50), pR);
        FBullet newBulletRightLCK(Vector2f(20,50), pR);
        newBulletLeftLCK.setPos(Vector2f(LCK->getX() + LCK->planeWidth() * (3/7), LCK->getY()));
        newBulletRightLCK.setPos(Vector2f(LCK->getX() + LCK->planeWidth(), LCK->getY()));
        bulletvecLeftLCK.push_back(newBulletLeftLCK);
        bulletvecRightLCK.push_back(newBulletRightLCK);
      
        // Boss狀態檢測，低於特定血量開啟狂暴模式
        if (LCK->getHealth() < 5000)
        {
            // 進入狂暴模式時播放生氣音效
            if (bossAngry == 0)
            {
                angry.play();
                bossAngry = 1;
            }
            
            // 狂棒模式時多一發快速子彈
            if (LCK->getAlive() == 1)
            {
                FBullet newBulletAngry(sf::Vector2f(50,50), pR);
                newBulletAngry.setPos(sf::Vector2f(LCK->getX() + LCK->planeWidth() * (1/2), LCK->getY()));
                bulletvecAngry.push_back(newBulletLeftLCK);
                for (int i = 0; i < bulletvecAngry.size(); i += bosebulSpacing / 2)
                {
                    player1->checkCollision(bulletvecAngry[i]);
                    if (playerNum == 2)
                    {
                        player2->checkCollision(bulletvecAngry[i]);
                    }
                    bulletvecAngry[i].draw(window);
                    bulletvecAngry[i].fire(-speed * dt * 2);
                }
            }
        }
      
        // Boss子彈的繪製、移動及玩家的碰撞檢測
        if (LCK->getAlive() == 1)
        {
            for (int i = 0; i < bulletvecLeftLCK.size(); i += bosebulSpacing)
            {
                player1->checkCollision(bulletvecLeftLCK[i]);
                player1->checkCollision(bulletvecRightLCK[i]);
                if (playerNum == 2)
                {
                    player2->checkCollision(bulletvecLeftLCK[i]);
                    player2->checkCollision(bulletvecRightLCK[i]);
                }
                bulletvecLeftLCK[i].draw(window);
                bulletvecRightLCK[i].draw(window);
                bulletvecLeftLCK[i].fire(-speed * dt * 1.2);
                bulletvecRightLCK[i].fire(-speed * dt * 1.2);
            }
        }

        // 玩家一血條調整與繪製
        float hpPercent = static_cast<float>(player1->health) / player1->maxHealth;
        playerHpBar.setSize(Vector2f(300.f * hpPercent, playerHpBar.getSize().y));
        window.draw(playerHpBarBack);
        window.draw(playerHpBar);
        
        // 玩家二血條調整與繪製
        if (playerNum == 2)
        {
            float hpPercent2 = static_cast<float>(player2->health) / player2->maxHealth;
            playerHpBar2.setSize(Vector2f(300.f * hpPercent2, playerHpBar2.getSize().y));
            window.draw(playerHpBarBack2);
            window.draw(playerHpBar2);
        }
      
        //
        if (LCK->getAlive() == 0)
        {
            // 打敗Boss時，播放爆炸音效
            if (boomBoss == 0)
            {
                explode.play();
                boomBoss = 1;
            }
            
            // 等待五秒鐘再繪製勝利背景
            if (winTime > 3)
            {
                window.clear();
                window.draw(victory);
            }
        }
    
        // 玩家死亡時，播放音效
        if (player1->alive == 0 && boom == 0)
        {
            boom = 1;
            explode.play();
        }
        
        if (playerNum == 2)
        {
            if (player2->alive == 0 && boomP2 == 0)
            {
                boomP2 = 1;
                explode.play();
            }
        }
    
        // Game Over，條件為場上沒有生存玩家
            // 等待三秒時間，再繪製戰敗背景
        if (loseTime > 3)
        {
            window.clear();
            window.draw(defeated);
        }
        

        window.display();
    }
    // 刪除物件指標指向的物件
    reset();
}

void Game::reset()
{
    delete player1;
    delete player2;
    delete LCK;
}

void Game::deleteBullet(std::vector<FBullet>& bulletVec, int spacing)
{
    int counter = -10 * spacing;
    if (bulletVec.size() % spacing == 1 && bulletVec.size() != 1)
    {

        for ( int i = 0; i < bulletVec.size(); i += spacing)
            {
                //Bullet culling (top of screen)
                if (bulletVec[i].getBottom() < 0 || bulletVec[i].getTop() > HEIGHT )
                    counter = i;
            }
        counter = counter / spacing + 1;
        if (counter > 0)
            bulletVec.erase(bulletVec.begin(), bulletVec.begin() + counter * spacing + 1);
    }
}
