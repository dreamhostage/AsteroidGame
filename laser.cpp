#pragma once
#include "Asteroid.h"

laser::laser()
{
    laserShootBuffer.loadFromFile("Sounds/Laser_Shoot.ogg");
    laserTexture.loadFromFile("Images/laser.png");
    laserSprite.setTexture(laserTexture);
    size = laserTexture.getSize();
    laserSprite.setOrigin(size.x / 2, size.y);
    laserShootSound.setBuffer(laserShootBuffer);
    laserText.setFont(font);
    laserText.setCharacterSize(40);
    laserText.setFillColor(Color::Red);
    autoAimTime = 0;
}
void laser::draw()
{
    if (gameStarted) {
        if (laserShootCount) {
            laserText.setPosition(ViewCenter.x - screenX / 2 + 300, ViewCenter.y - screenY / 2);
            text = "LASER: ";
            text += std::to_string(laserShootCount);
            laserText.setString(text);
            window->draw(laserText);

            position1 = ShipSprite.getPosition();
            for (int i = 0; i < ast.size(); ++i) {
                position2 = ast[i].sprite.getPosition();
                distanse = sqrt(
                    (position1.x - position2.x) * (position1.x - position2.x)
                    + (position1.y - position2.y) * (position1.y - position2.y));
                if (distanse < 200) {
                    laserShootSound.play();

                    if (autoAimTime < 4) {
                        laserSprite.setPosition(position1);
                        vd = position1 - position2;
                        laserSprite.setRotation(std::atan2(vd.y, vd.x) * 180.f / M_PI + 270);
                        window->draw(laserSprite);
                        ++autoAimTime;
                    } else {
                        autoAimTime = 0;
                        std::vector<asteroidsArray>::iterator it = ast.begin();
                        ast.erase(it + i);
                        if (!godmode)
                            --laserShootCount;
                        ++points;
                    }
                }
            }
        }
    }
}
