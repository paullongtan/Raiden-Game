//
//  professor.cpp
//  
//
//  Created by 王彥普 on 2021/1/10.
//

#include "professor.hpp"

Boss::Boss()
{
    if (!t_plane.loadFromFile("../Resources/images/LCK.png"))
    {
        t_plane.loadFromFile("Raiden/Resources/images/LCK.png");
    }
    
    plane.setTexture(t_plane);
    plane.setScale(0.4, 0.4);
    plane.setPosition(WIDTH / 2, HEIGHT * 1 / 10);
    
    planeHit.setTexture(t_plane);
    planeHit.setScale(0.4, 0.4);
    planeHit.setColor(Color::Red);
}

float Boss::getX() const
{
    return plane.getPosition().x;
}

float Boss::getY() const
{
    return plane.getPosition().y;
}

float Boss::planeWidth() const
{
    return plane.getGlobalBounds().width;
}

float Boss::planeHeight() const
{
    return plane.getGlobalBounds().height;
}

void Boss::setPosition(float x, float y)
{
    plane.setPosition(x, y);
}

void Boss::move(float dt) // Boss的移動型態，有四種
{
    float speed = 700;
    if (moveType == 1)
    {
        plane.move(-speed * dt * 1.2, 0);
        if (getX() <= 0)
        {
            moveType = 2;
            plane.setPosition(0, getY());
        }
    }
    else if (moveType == 2)
    {
        plane.move(speed * dt, speed * dt / 2);
        if (getX() + planeWidth() >= WIDTH)
        {
            moveType = 3;
            plane.setPosition(WIDTH - planeWidth(), getY());
        }
    }
    else if (moveType == 3)
    {
        plane.move(-speed * dt * 1.2, 0);
        if (getX() <= 0)
        {
            moveType = 4;
            plane.setPosition(0, getY());
        }
    }
    else
    {
        plane.move(speed * dt, -speed * dt / 2);
        if (getX() + planeWidth() >= WIDTH)
        {
            moveType = 1;
            plane.setPosition(WIDTH - planeWidth(), getY());
        }
    }
    
}

void Boss::checkCollision(FBullet& bullet)
{
    if (bullet.getTop() <= getY() + planeHeight() && bullet.getBottom() >= getY() && bullet.getLeft() >= getX() && bullet.getRight() <= getX() + planeWidth())
    {
        health -= 50;
        planeHit.setPosition(getX(), getY());
        showHit = 1;
        bullet.outBorder();
    }
    if (health <= 0)
        alive = 0;
}

void Boss::draw(RenderWindow& window)
{
    if (alive == 1)
    {
        if (showHit == 0)
            window.draw(plane);
        else
        {
            window.draw(planeHit);
            showHit = 0;
        }
    }
}

bool Boss::getAlive() const
{
    return alive;
}

int Boss::getHealth() const
{
    return health;
}

void Boss::reset()
{
    plane.setPosition(WIDTH / 2, HEIGHT * 1 / 10);
    health = 15000;
    alive = 1;
    moveType = 1;
}
