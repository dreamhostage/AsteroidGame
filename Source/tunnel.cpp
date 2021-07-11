#include "Asteroid.h"

tunnel::tunnel()
{
    portalSize = 0;
    pixelTexture.loadFromFile("Images/pixel.png");
    pixelSprite.setTexture(pixelTexture);
    size = pixelTexture.getSize();
    pixelSprite.setOrigin(size.x / 2, size.y / 2);
    pixelspeed = 4;
    portalCircle.setRadius(portalSize + 20);
    portalCircle.setFillColor(sf::Color::Black);
    portalCircle.setOrigin(portalCircle.getRadius(), portalCircle.getRadius());
    centerSize = 1;
    pixelCount = 200;
    tunnelActivated = false;
}

void tunnel::draw()
{
    window->draw(portalCircle);
    if (pixels.size() < pixelCount)
    {
        if (appearingTime.getElapsedTime().asMilliseconds() > 1) 
        {
            arbiteAngle = rand() % 360;
            newPixelPos.x = spawningPosition.x + portalSize * cos((arbiteAngle)*M_PI / 180);
            newPixelPos.y = spawningPosition.y + portalSize * sin((arbiteAngle)*M_PI / 180);
            pixelSprite.setPosition(newPixelPos);
            pixels.push_back(pixelSprite);
            appearingTime.restart();
        }
    }

    for (int i = 0; i < pixels.size(); ++i)
    {
        window->draw(pixels[i]);
        position1 = pixels[i].getPosition();
        position2 = spawningPosition;

        distanse = sqrt(
            (position1.x - position2.x) * (position1.x - position2.x)
            + (position1.y - position2.y) * (position1.y - position2.y));

        if (distanse > centerSize)
        {
            vd = position2 - position1;
            angle = std::atan2(vd.y, vd.x) * 180.f / M_PI + 90;
            pixels[i].setRotation(angle);
            angle -= (angle - 90) * 2;
            pixels[i].setPosition(
                position1.x + pixelspeed * sin((angle)*M_PI / 180),
                position1.y + pixelspeed * cos((angle)*M_PI / 180));
        }
        else
        {
            bit = pixels.begin();
            pixels.erase(bit + i);
        }
    }

    if (portalSize < 200)
    {
        portalSize += 0.1;
        portalCircle.setRadius(portalSize + 20);
        portalCircle.setOrigin(portalCircle.getRadius(), portalCircle.getRadius());
    }

    if (centerSize < 50)
    {
        centerSize += 0.02;
    }
}

void tunnel::setPosition(sf::Vector2f position)
{
    spawningPosition = position;
    portalCircle.setPosition(position);
}

void tunnel::reset()
{
    portalSize = 0;
    portalCircle.setRadius(portalSize + 20);
    centerSize = 1;
    tunnelActivated = false;
    for (int i = 0; i < pixels.size(); ++i)
    {
        bit = pixels.begin();
        pixels.erase(bit + i);
    }
}