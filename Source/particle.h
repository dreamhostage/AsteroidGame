#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <math.h>

using namespace sf;

struct part {
    Sprite sprite;
    int lifetime = 3000;
    int speed = 2;
    Clock time;
    Vector2f position;
    float angle;
    double rnd(double fMin, double fMax)
    {
        double f = (double)rand() / RAND_MAX;
        return fMin + f * (fMax - fMin);
    }
    part(Sprite _sprite, float _angle, Vector2f _position)
    {
        _angle -= 90;
        sprite = _sprite;
        angle = rnd(_angle - 10, _angle + 10);
        position = _position;

        sprite.setRotation(angle);
        sprite.setPosition(position);
    }
    void move()
    {
        angle = sprite.getRotation();
        angle -= (angle - 90) * 2;
        position = sprite.getPosition();

        sprite.setPosition(
            position.x + speed * sin((angle)*M_PI / 180),
            position.y + speed * cos((angle)*M_PI / 180));
        auto c = sprite.getColor();

        if (c.a > 109)
            c.a -= 1;

        if (c.b > 109)
            c.b -= 1;

        if (c.g > 109)
            c.g -= 1;

        if (c.r > 109)
            c.r -= 1;

        sprite.setColor(c);
    }
};

class particle {
    Texture particleTexture;
    Sprite particleSprite;
    std::vector<part> pbase;
    Vector2f position;
    float angle;

public:
    particle()
    {
        particleTexture.loadFromFile("Images/particle.png");
        particleSprite.setTexture(particleTexture);
        particleSprite.setOrigin(particleTexture.getSize().x / 2, particleTexture.getSize().y / 2);
    }

    void add(Sprite sprite)
    {
        angle = sprite.getRotation() - 90;
        float tmpangle = sprite.getRotation();
        tmpangle -= (tmpangle - 90) * 2;
        position = sprite.getPosition();
        Vector2f np(
            position.x - 40 * sin((tmpangle)*M_PI / 180),
            position.y - 40 * cos((tmpangle)*M_PI / 180));

        for (int i = 0; i < 10; ++i) {
            part temp(particleSprite, angle, np);
            pbase.push_back(temp);
        }
    }

    void draw(RenderWindow& window)
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
};
