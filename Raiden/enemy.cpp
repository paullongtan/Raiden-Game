#include "enemy.hpp"
using namespace std;
using namespace sf;

void Enemy::draw(RenderWindow& window)
{
    pdogs.setTexture(graphic);
    window.draw(pdogs);
}

Enemy::Enemy(float x_, float y_, RenderWindow& window, int size)
{
    //cout << "Enemy" << endl;
    if (!graphic.loadFromFile("Raiden/Resources/images/pdogs.png"))
    {
        graphic.loadFromFile("../Resources/images/pdogs.png");
    }
    
    pdogs.setTexture(graphic);
    pdogs.setPosition(Vector2f(x_, y_));
    if (size == 1)
    {
        pdogs.setScale(0.5, 0.5);
        life = 1;
    }
    else if (size == 2)
    {
        pdogs.setScale(0.75, 0.75);
        life = 3;
    }
    
}

void Enemy::setPos(float x, float y)
{
    pdogs.setPosition(x, y);
}

float Enemy::getTop() const
{
    return pdogs.getPosition().y;
}

float Enemy::getBottom() const
{
    return pdogs.getPosition().y + pdogs.getGlobalBounds().height;
}
float Enemy::getLeft() const
{
    return pdogs.getPosition().x;
}

float Enemy::getRight() const
{
    return pdogs.getPosition().x + pdogs.getGlobalBounds().width;
}

void Enemy::fly(int speed)
{
    pdogs.move(0, speed);
    if (pdogs.getPosition().y >= 1500)
    {
        pdogs.setPosition(100000, 100000);
        life = 0;
    }
}

void Enemy::checkCollision(FBullet& bullet)
{
    if (bullet.getTop() <= pdogs.getPosition().y + pdogs.getGlobalBounds().height &&
        bullet.getBottom() >= pdogs.getPosition().y &&
        bullet.getLeft() >= pdogs.getPosition().x &&
        bullet.getRight() <= pdogs.getPosition().x + pdogs.getGlobalBounds().width )
    {
        life -= 1;
        bullet.setPos(Vector2f(104800, 104800));
        bullet.outBorder();
        if (life <= 0)
        {
            pdogs.setPosition(Vector2f(104800, 104800));
        }
        //cout << "life " << life << endl;
    }
}
