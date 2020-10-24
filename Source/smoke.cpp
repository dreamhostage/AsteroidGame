#include "Asteroid.h"

smoke::particle::particle(Sprite _sprite, float _angle, Vector2f _position)
{
    _angle -= 90;
    sprite = _sprite;
    angle = rnd(_angle - 10, _angle + 10);
    position = _position;

    sprite.setRotation(angle);
    sprite.setPosition(position);
}
void smoke::particle::move()
{
    angle = sprite.getRotation();
    angle -= (angle - 90) * 2;
    position = sprite.getPosition();

    sprite.setPosition(
        position.x + speed * sin((angle)*M_PI / 180), position.y + speed * cos((angle)*M_PI / 180));
    color = sprite.getColor();

    if (color.a > 20)
        color.a -= 3;

    if (color.b > 20)
        color.b -= 3;

    if (color.g > 20)
        color.g -= 3;

    if (color.r > 20)
        color.r -= 3;

    sprite.setColor(color);
}

double smoke::particle::rnd(double fMin, double fMax)
{
    f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

void smoke::add(Sprite sprite)
{
    angle = sprite.getRotation() - 90;
    float tmpangle = sprite.getRotation();
    tmpangle -= (tmpangle - 90) * 2;
    position = sprite.getPosition();
    np
        = {(float)(position.x - sprite.getTexture()->getSize().y / 2 * sin((tmpangle)*M_PI / 180)),
           (float)(position.y - sprite.getTexture()->getSize().y / 2 * cos((tmpangle)*M_PI / 180))};

    particle temp(particleSprite, angle, np);
    pbase.push_back(std::move(temp));
}

void smoke::draw(RenderWindow& window)
{
    for (int i = 0; i < pbase.size(); ++i) {
        if (pbase[i].time.getElapsedTime().asMilliseconds() < pbase[i].lifetime) {
            window.draw(pbase[i].sprite);
            pbase[i].move();
        } else {
            pbase.erase(pbase.begin() + i);
            --i;
        }
    }
}

smoke::smoke()
{
    particleTexture.loadFromFile("Images/particle.png");
    particleSprite.setTexture(particleTexture);
    particleSprite.setOrigin(particleTexture.getSize().x / 2, particleTexture.getSize().y / 2);
}
