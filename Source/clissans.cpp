#include "Asteroid.h"

clissans::clissans()
{
    clissanshipTexture.loadFromFile("Images/clissanship.png");
    clissansbulletTexture.loadFromFile("Images/clisanbullet.png");
    ClissansLifeTexture.loadFromFile("Images/ClissansLife.png");
    clissansshootBuffer.loadFromFile("Sounds/clisanshoot.ogg");
    laserinBuffer.loadFromFile("Sounds/laserin.ogg");
    clissansexplosionSoundBuffer.loadFromFile("Sounds/explosion.ogg");
    frameTexture.loadFromFile("Images/frame.png");
    ClissanShipExplTexture.loadFromFile("Images/ClissanShipExpl.png");

    ClissanShipExplSprite.setTexture(ClissanShipExplTexture);
    laserinSound.setBuffer(laserinBuffer);
    frameSprite.setTexture(frameTexture);
    ClissansLifeSprite.setTexture(ClissansLifeTexture);
    clissansexplosionSound.setBuffer(clissansexplosionSoundBuffer);
    clissansshot.setBuffer(clissansshootBuffer);
    clissansbulletSprite.setTexture(clissansbulletTexture);
    clissanShipSprite.setTexture(clissanshipTexture);
    clissanShipSprite.setRotation(90);
    size = ClissansLifeTexture.getSize();
    ClissansLifeSprite.setOrigin(size.x / 2, size.y / 2);
    ClissanShipExplSprite.setOrigin(96, 96);

    size = clissanshipTexture.getSize();
    clissanShipSprite.setOrigin(size.x / 2, size.y / 2);
    size = clissansbulletTexture.getSize();
    clissansbulletSprite.setOrigin(size.x / 2, size.y);
    size = frameTexture.getSize();
    frameSprite.setOrigin(size.x / 2, size.y / 2);

    ClissanShipCustomColor = clissanShipSprite.getColor();

    side = true;
    selNumb = -1;
    selectedCount = 0;

    mainX = VideoMode::getDesktopMode().width + 700;
    mainY = VideoMode::getDesktopMode().height + 700;

    selectedClissansShip = NULL;
}

void clissans::clissansSpauning()
{
    if (clisansShipsArray.size() < clisansCount) {
        clissanShips new_cship;

        int rnd = rand() % 4;

        if (rnd == 0) {
            clissanShipSprite.setPosition(rand() % mainX, 0);
            new_cship.sprite = clissanShipSprite;
            new_cship.LifeSprite = ClissansLifeSprite;
            new_cship.pos.x = rand() % mainX;
            new_cship.pos.y = rand() % mainY;
        }

        if (rnd == 1) {
            clissanShipSprite.setPosition(0, rand() % mainY);
            new_cship.sprite = clissanShipSprite;
            new_cship.LifeSprite = ClissansLifeSprite;
            new_cship.pos.x = rand() % mainX;
            new_cship.pos.y = rand() % mainY;
        }

        if (rnd == 2) {
            clissanShipSprite.setPosition(rand() % mainX, mainY);
            new_cship.sprite = clissanShipSprite;
            new_cship.LifeSprite = ClissansLifeSprite;
            new_cship.pos.x = rand() % mainX;
            new_cship.pos.y = rand() % mainY;
        }

        if (rnd == 3) {
            clissanShipSprite.setPosition(mainX, rand() % mainY);
            new_cship.sprite = clissanShipSprite;
            new_cship.LifeSprite = ClissansLifeSprite;
            new_cship.pos.x = rand() % mainX;
            new_cship.pos.y = rand() % mainY;
        }

        clisansShipsArray.push_back(std::move(new_cship));
    }
}

void clissans::addBullet(Vector2f& position, int rotation)
{
    clissansbulletSprite.setPosition(position);
    clissansbulletSprite.setRotation(rotation);
    clissansbulletsArray.push_back(clissansbulletSprite);
}

void clissans::drawBullets()
{
    position1 = ShipSprite.getPosition();
    for (int i = 0; i < clissansbulletsArray.size(); ++i) {
        position2 = clissansbulletsArray[i].getPosition();

        if (position2.x < mainX && position2.y < mainY && position2.x > 0 && position2.y > 0) {
            window->draw(clissansbulletsArray[i]);
            angle = clissansbulletsArray[i].getRotation();
            angle -= (angle - 90) * 2;
            clissansbulletsArray[i].setPosition(
                position2.x + 8 * sin((angle)*M_PI / 180),
                position2.y + 8 * cos((angle)*M_PI / 180));

            distanse = sqrt(
                (position1.x - position2.x) * (position1.x - position2.x)
                + (position1.y - position2.y) * (position1.y - position2.y));
            if (distanse < 46) {
                std::vector<Sprite>::iterator it = clissansbulletsArray.begin();
                clissansbulletsArray.erase(it + i);
                if (!shieldCount) {
                    bulletDamageSound.play();
                    if (!godmode)
                        health -= 10;
                    if (health <= 0) {
                        health = 0;
                        GameOver = true;
                    }
                } else {
                    --shieldCount;
                    shieldSound.play();
                }
            }
        } else {
            std::vector<Sprite>::iterator bit = clissansbulletsArray.begin();
            clissansbulletsArray.erase(bit + i);
        }
    }
}

void clissans::makeShootIfClose(clissanShips& ClissansShip)
{
    if (!GameOver) {
        if (!ClissansShip.shoot) {
            position1 = ShipSprite.getPosition();
            position2 = ClissansShip.sprite.getPosition();
            distanse = sqrt(
                (position2.x - position1.x) * (position2.x - position1.x)
                + (position2.y - position1.y) * (position2.y - position1.y));
            if (distanse < 550) {
                clissansshot.play();
                vd = position1 - position2;
                addBullet(position2, std::atan2(vd.y, vd.x) * 180.f / M_PI + 90);
                ClissansShip.shoot = true;
            }
        }

        if (ClissansShip.shootingTime.getElapsedTime().asSeconds() > 2) {
            ClissansShip.shootingTime.restart();
            ClissansShip.shoot = false;
        }
    }
}

void clissans::draw()
{
    if (gameStarted) {
        for (int i = 0; i < clisansShipsArray.size(); ++i) {
            if (clisansShipsArray[i].destroyed) {
                if (clisansShipsArray[i].final < 65) {
                    ClissanShipExplosion(clisansShipsArray[i]);
                } else {
                    std::vector<clissanShips>::iterator csit = clisansShipsArray.begin();
                    clisansShipsArray.erase(csit + i);
                }
            } else {
                if (Keyboard::isKeyPressed(Keyboard::F))
                    if (Mouse::isButtonPressed(Mouse::Left)) {
                        sellectClissanShip(clisansShipsArray[i]);
                    }

                if (clisansShipsArray[i].selected) {
                    frameSprite.setPosition(clisansShipsArray[i].sprite.getPosition());
                    window->draw(frameSprite);
                }

                smoke::add(clisansShipsArray[i].sprite);

                ClissanShipBulletsChecking(clisansShipsArray[i]);

                ClissanShipMovingBehavior(clisansShipsArray[i]);

                window->draw(clisansShipsArray[i].sprite);
                clisansShipsArray[i].LifeSprite.setPosition(
                    clisansShipsArray[i].sprite.getPosition().x,
                    clisansShipsArray[i].sprite.getPosition().y - 40);
                window->draw(clisansShipsArray[i].LifeSprite);
            }
        }
        drawBullets();
        clissansSpauning();
    } else {
        for (int i = 0; i < clisansShipsArray.size(); ++i) {
            std::vector<clissanShips>::iterator it = clisansShipsArray.begin();
            clisansShipsArray.erase(it);
        }
    }
}

void clissans::ClissanShipExplosion(clissanShips& ClissansShip)
{
    ClissanShipExplSprite.setTextureRect(IntRect(int(ClissansShip.final) * 192, 0, 192, 192));
    ClissanShipExplSprite.setPosition(ClissansShip.sprite.getPosition());
    window->draw(ClissanShipExplSprite);
    ClissansShip.final += 0.4;
}

void clissans::sellectClissanShip(clissanShips& ClissansShip)
{
    position1 = ClissansShip.sprite.getPosition();
    pixelPos = Mouse::getPosition(*window);
    position2 = window->mapPixelToCoords(pixelPos);
    distanse = sqrt(
        (position1.x - position2.x) * (position1.x - position2.x)
        + (position1.y - position2.y) * (position1.y - position2.y));

    if (!aimSelected) {
        if (distanse < 70) {
            if (selectedClissansShip)
                selectedClissansShip->selected = false;
            selectedClissansShip = &ClissansShip;
            ClissansShip.selected = true;
            aimSelected = true;
        } else {
            if (selectedClissansShip)
                selectedClissansShip->selected = false;
        }
    } else {
        if (distanse > 70) {
            if (ClissansShip.selected) {
                ClissansShip.selected = false;
                aimSelected = false;
            }
        }
    }
}

void clissans::ClissanShipBulletsChecking(clissanShips& ClissansShip)
{
    temp = ClissansShip.sprite.getPosition();
    position2 = ShipSprite.getPosition();

    for (int k = 0; k < bulletsArray.size(); ++k) {
        bulletPos = bulletsArray[k].getPosition();
        double bulletDist = sqrt(
            (bulletPos.x - temp.x) * (bulletPos.x - temp.x)
            + (bulletPos.y - temp.y) * (bulletPos.y - temp.y));
        if (bulletDist < 50) {
            ClissansShip.health -= 10;
            ClissansShip.LifeSprite.setScale(
                ClissansShip.LifeSprite.getScale().x - 0.1, ClissansShip.LifeSprite.getScale().y);
            std::vector<Sprite>::iterator bit = bulletsArray.begin();
            bulletsArray.erase(bit + k);
            laserinSound.play();
            ClissansShip.ClissanShipBlaming = 7;
            ClissansShip.sprite.setColor(Color::Red);
        }
    }

    if (ClissansShip.ClissanShipBlaming) {
        --ClissansShip.ClissanShipBlaming;
    } else {
        ClissansShip.sprite.setColor(ClissanShipCustomColor);
    }

    if (ClissansShip.health <= 0) {
        explosionSound.play();
        ClissansShip.destroyed = true;
        if (ClissansShip.selected) {
            ClissansShip.selected = false;
            aimSelected = false;
        }
        points += 10;
    }
}

void clissans::ClissanShipMovingBehavior(clissanShips& ClissansShip)
{
    if (temp.x < 0) {
        temp.x = mainX;
        ClissansShip.sprite.setPosition(temp);
    }
    if (temp.y < 0) {
        temp.y = mainY;
        ClissansShip.sprite.setPosition(temp);
    }
    if (temp.x > mainX) {
        temp.x = 0;
        ClissansShip.sprite.setPosition(temp);
    }
    if (temp.y > mainY) {
        temp.y = 0;
        ClissansShip.sprite.setPosition(temp);
    }

    double distanse = sqrt(
        (ClissansShip.pos.x - temp.x) * (ClissansShip.pos.x - temp.x)
        + (ClissansShip.pos.y - temp.y) * (ClissansShip.pos.y - temp.y));
    double shipDistanse = sqrt(
        (position2.x - temp.x) * (position2.x - temp.x)
        + (position2.y - temp.y) * (position2.y - temp.y));
    int angle = 0;
    float current = 0;

    makeShootIfClose(ClissansShip);

    if (distanse > 200) {
        if (shipDistanse < clissansSpawningDistance) {
            vd = position2 - temp;
            angle = std::atan2(vd.y, vd.x) * 180 / M_PI + 170;

            current = ClissansShip.sprite.getRotation();
            if (current < angle)
                ++current;
            else if (current > angle)
                --current;
            else
                current = angle;
        } else {
            vd = ClissansShip.pos - temp;
            angle = std::atan2(vd.y, vd.x) * 180 / M_PI + 90;

            if (angle > 360)
                angle = 360 - angle;
            else if (angle < 0)
                angle = 360 + angle;

            current = ClissansShip.sprite.getRotation();
            if (current < angle)
                ++current;
            else if (current > angle)
                --current;
            else
                current = angle;
        }
    } else {
        ClissansShip.pos.x = rand() % mainX;
        ClissansShip.pos.y = rand() % mainY;
        if (ClissansShip.pos.x < 200)
            ClissansShip.pos.x = 200;
        if (ClissansShip.pos.x > mainX - 200)
            ClissansShip.pos.x = mainX - 200;

        if (ClissansShip.pos.y < 200)
            ClissansShip.pos.y = 200;
        if (ClissansShip.pos.y > mainX - 200)
            ClissansShip.pos.y = mainX - 200;
    }

    ClissansShip.sprite.setRotation(current);
    current -= (current - 90) * 2;
    ClissansShip.sprite.setPosition(
        temp.x + 2 * sin((current)*M_PI / 180), temp.y + 2 * cos((current)*M_PI / 180));
}

void clissans::reset()
{
    auto cit = clisansShipsArray.begin();
    while (cit != clisansShipsArray.end()) {
        cit = clisansShipsArray.erase(cit);
    }
}
