#include "Firebullet.hpp"

FBullet::FBullet(Vector2f size)
{
    bullet.setSize(size);
    bullet.setFillColor(Color::Blue);
}

FBullet::FBullet(Vector2f size, Color bulletColor)
{
    bullet.setSize(size);
    bullet.setFillColor(bulletColor);
}

void FBullet::fire(int speed)
{
    if (getBottom() >= 1500 || getTop() <= 0)
        outOfBorder = 1;
    if (outOfBorder == 0)
        bullet.move(0,-speed);
}

int FBullet::getRight()
{
    return bullet.getPosition().x + bullet.getSize().x;
}

int FBullet::getLeft()
{
    return bullet.getPosition().x;
}

int FBullet::getTop()
{
    return bullet.getPosition().y;
}

int FBullet::getBottom()
{
    return bullet.getPosition().y + bullet.getSize().y;
}

void FBullet::draw(RenderWindow &window)
{
    if (outOfBorder == 0)
        window.draw(bullet);
}

void FBullet::setPos(sf::Vector2f newPos)
{
    bullet.setPosition(newPos);
}

void FBullet::outBorder()
{
    outOfBorder = 1;
    setPos(Vector2f(100000,100000));
}





