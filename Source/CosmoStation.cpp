#include "Asteroid.h"

CosmoStation::CosmoStation()
{
    CosmoStationTexture.loadFromFile("Images/CosmoStation.png");
    CosmoStationSprite.setTexture(CosmoStationTexture);
    CSFrameTexture.loadFromFile("Images/CSFrame.png");
    CSFrameSprite.setTexture(CSFrameTexture);
    NeonBallTexture.loadFromFile("Images/NeonBall.png");
    NeonBallSprite.setTexture(NeonBallTexture);
    NeonBallTaleTexture.loadFromFile("Images/NeonBallTale.png");
    NeonBallTaleSprite.setTexture(NeonBallTaleTexture);
    NBexplTexture.loadFromFile("Images/NBexpl.png");
    NBexplSprite.setTexture(NBexplTexture);

    NBexplSprite.setOrigin(256, 256);

    NBSoundBuffer.loadFromFile("Sounds/NBSound.ogg");
    NBSound.setBuffer(NBSoundBuffer);

    NBexplosionBuffer.loadFromFile("Sounds/NBexplosion.ogg");
    NBExplosionSound.setBuffer(NBexplosionBuffer);

    NeonBallTaleSprite.setScale(0.2, 0.2);
    size = NeonBallTaleTexture.getSize();
    NeonBallTaleSprite.setOrigin(size.x / 2, size.y / 2);

    NeonBallSprite.setScale(0.2, 0.2);
    size = NeonBallTexture.getSize();
    NeonBallSprite.setOrigin(size.x / 2, size.y / 2);

    CosmoStationSprite.setScale(0.6, 0.6);
    LifeBarTexture.loadFromFile("Images/CosmoStationLife.png");
    CSLifeBarSprite.setTexture(LifeBarTexture);

    size = CosmoStationTexture.getSize();
    CosmoStationSprite.setOrigin(size.x / 2, size.y / 2);
    size = LifeBarTexture.getSize();
    CSLifeBarSprite.setOrigin(size.x / 2, size.y / 2);

    size = CSFrameTexture.getSize();
    CSFrameSprite.setOrigin(size.x / 2, size.y / 2);

    CSCustomColor = CosmoStationSprite.getColor();
    NBCustomColor = NeonBallSprite.getColor();
    NBblaming = 5;
    CSblaming = 5;
    NeonBallLife = 5;
    freezeTime = 5;
    NBexplAnimframeX = 0;
    NBexplAnimframeY = 0;
    CSalive = true;
    explSound = false;
    CSSelected = false;
    NeonBallAction = false;
    CSActivated = true;
    NBtaleWait = false;
    NBexplActivate = false;
}

void CosmoStation::Tick()
{
    if (CSalive) {
        moving();
        LifeBar();
        BulletsChecking();
        laserScaning();
        FrameMoving();
        Attack();
        NeonBallMoving();
        window->draw(CosmoStationSprite);
        window->draw(CSLifeBarSprite);
        if (CSSelected)
            window->draw(CSFrameSprite);
    } else {
        if (explSound) {
            explosionSound.play();
            explSound = false;
            freeze = false;
        }
        static double k = 0;
        position1 = CosmoStationSprite.getPosition();
        shipExplSprite.setPosition(position1);
        if (k < 65) {
            shipExplSprite.setScale(2, 2);

            shipExplSprite.setOrigin(96, 96);
            shipExplSprite.setTextureRect(IntRect(int(k) * 192, 0, 192, 192));
            window->draw(shipExplSprite);
            k += 0.3;
        }
    }
}

void CosmoStation::NeonBallMoving()
{
    if (CSActivated) {
        if (!NBtaleWait) {
            if (NeonBallAction) {
                if (NeonBallLife) {

                    NeonBallTaleSprite.setPosition(NeonBallSprite.getPosition());
                    NeonBallTale.insert(NeonBallTale.begin(), NeonBallTaleSprite);

                    if (NeonBallTale.size() > 1) {
                        for (int i = 0; i < NeonBallTale.size() - 1; ++i) {
                            NeonBallTale[i + 1].setScale(
                                NeonBallTale[i].getScale().x - 0.001,
                                NeonBallTale[i].getScale().y - 0.001);
                        }
                    }

                    position1 = NeonBallSprite.getPosition();
                    position2 = ShipSprite.getPosition();
                    distanse = sqrt(
                        (position1.x - position2.x) * (position1.x - position2.x)
                        + (position1.y - position2.y) * (position1.y - position2.y));
                    if (distanse < 50) {
                        NeonBallAction = false;
                        NBtaleWait = true;
                        NeonBallLife = 5;
                        freeze = true;
                        NBexplActivate = true;
                        freezeProgress.restart();
                    } else {
                        position2 = ShipSprite.getPosition();
                        vd = position2 - position1;
                        angle = std::atan2(vd.y, vd.x) * 180.f / M_PI + 90;
                        NeonBallSprite.setRotation(angle);
                        angle -= (angle - 90) * 2;
                        NeonBallSprite.setPosition(
                            position1.x + 2.8 * sin((angle)*M_PI / 180),
                            position1.y + 2.8 * cos((angle)*M_PI / 180));
                    }

                    for (int i = 0; i < bulletsArray.size(); ++i) {
                        position2 = bulletsArray[i].getPosition();
                        distanse = sqrt(
                            (position1.x - position2.x) * (position1.x - position2.x)
                            + (position1.y - position2.y) * (position1.y - position2.y));
                        if (distanse < 50) {
                            laserinSound.play();
                            NBblaming = 7;
                            NeonBallSprite.setColor(Color::Red);
                            --NeonBallLife;
                            bit = bulletsArray.begin();
                            bulletsArray.erase(bit + i);
                        }
                    }
                }
                if (NBblaming) {
                    --NBblaming;
                } else {
                    NeonBallSprite.setColor(NBCustomColor);
                }
                if (!NeonBallLife) {
                    NeonBallAction = false;
                    NBexplActivate = true;
                    NBtaleWait = true;
                    NeonBallLife = 5;
                    NBExplosionSound.play();
                }

                if (NeonBallTale.size() > 140)
                    NeonBallTale.pop_back();

                for (auto it : NeonBallTale) {
                    window->draw(it);
                }

                window->draw(NeonBallSprite);
            }
        } else {
            if (NeonBallTale.size()) {
                NeonBallTale.pop_back();
                for (auto it : NeonBallTale) {
                    window->draw(it);
                }
            } else {
                NBtaleWait = false;
            }
        }
    }
    NBexplosion();
}

void CosmoStation::FrameMoving()
{
    if (Keyboard::isKeyPressed(Keyboard::F))
        if (Mouse::isButtonPressed(Mouse::Left)) {
            position1 = CosmoStationSprite.getPosition();
            pixelPos = Mouse::getPosition(*window);
            position2 = window->mapPixelToCoords(pixelPos);
            distanse = sqrt(
                (position1.x - position2.x) * (position1.x - position2.x)
                + (position1.y - position2.y) * (position1.y - position2.y));

            if (rocketsCount) {
                if (distanse < 120) {
                    CSSelected = true;
                    aimSelected = false;
                    for (int i = 0; i < clisansShipsArray.size(); ++i) {
                        if (clisansShipsArray[i].selected)
                            clisansShipsArray[i].selected = false;
                    }
                } else {
                    CSSelected = false;
                }
            }
        }
    if (CSSelected) {
        CSFrameSprite.setPosition(CosmoStationSprite.getPosition());
    }
}

void CosmoStation::LifeBar()
{
    CSLifeBarSprite.setPosition(
        CosmoStationSprite.getPosition().x, CosmoStationSprite.getPosition().y - 130);
}

void CosmoStation::BulletsChecking()
{
    position1 = CosmoStationSprite.getPosition();
    for (int i = 0; i < bulletsArray.size(); ++i) {
        position2 = bulletsArray[i].getPosition();
        distanse = sqrt(
            (position1.x - position2.x) * (position1.x - position2.x)
            + (position1.y - position2.y) * (position1.y - position2.y));

        if (distanse < 100) {
            laserinSound.play();
            bit = bulletsArray.begin();
            bulletsArray.erase(bit + i);
            CSblaming = 7;
            CosmoStationSprite.setColor(Color::Red);
            if (CSLifeBarSprite.getScale().x > 0.005) {
                CSLifeBarSprite.setScale(
                    CSLifeBarSprite.getScale().x - 0.005, CSLifeBarSprite.getScale().y);
            } else {
                if (CSalive)
                {
                    CSalive = false;
                    tunnel::setPosition(CosmoStationSprite.getPosition());
                    tunnelActivated = true;
                    explSound = true;
                    points += 400;
                }
            }
        }
    }
    if (CSblaming) {
        --CSblaming;
    } else {
        CosmoStationSprite.setColor(CSCustomColor);
    }
}

void CosmoStation::moving()
{
    if (CSActivated) {
        position1 = CosmoStationSprite.getPosition();
        position2 = ShipSprite.getPosition();
        distanse = sqrt(
            (position1.x - position2.x) * (position1.x - position2.x)
            + (position1.y - position2.y) * (position1.y - position2.y));

        if (distanse > 400) {
            vd = position2 - position1;
            angle = std::atan2(vd.y, vd.x) * 180.f / M_PI + 90;
            angle -= (angle - 90) * 2;
            CosmoStationSprite.setPosition(
                position1.x + 1 * sin((angle)*M_PI / 180),
                position1.y + 1 * cos((angle)*M_PI / 180));
        }
    }
    if (!gameStarted) {
        CSActivated = true;
        CSSpawn();
    }
}

void CosmoStation::laserScaning()
{
    if (CSActivated)
    {
        position1 = CosmoStationSprite.getPosition();
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
                }
                else {
                    autoAimTime = 0;
                    std::vector<asteroidsArray>::iterator it = ast.begin();
                    ast.erase(it + i);
                }
            }
        }
    }
}

void CosmoStation::addBullet(Vector2f& position, int rotation)
{
    clissansbulletSprite.setPosition(position);
    clissansbulletSprite.setRotation(rotation);
    clissansbulletsArray.push_back(clissansbulletSprite);
}

void CosmoStation::Attack()
{
    if (!GameOver) {
        if (CSActivated) {
            position1 = CosmoStationSprite.getPosition();
            position2 = ShipSprite.getPosition();
            distanse = sqrt(
                (position1.x - position2.x) * (position1.x - position2.x)
                + (position1.y - position2.y) * (position1.y - position2.y));
            if (distanse < 800) {
                if (!NeonBallAction) {
                    if (!NBtaleWait) {
                        if (!freeze) {
                            if (!NBexplActivate) {
                                NBSound.play();
                                NeonBallAction = true;
                                NeonBallSprite.setPosition(CosmoStationSprite.getPosition());
                                NeonBallSprite.setRotation(rand() & 360);
                            }
                        }
                    }
                }

                if (CSBulletsShootingTime.getElapsedTime().asMilliseconds() > 90) {
                    position1 = ShipSprite.getPosition();
                    position2 = CosmoStationSprite.getPosition();
                    clissansshot.play();
                    vd = position1 - position2;
                    addBullet(position2, std::atan2(vd.y, vd.x) * 180.f / M_PI + 90);
                    CSBulletsShootingTime.restart();
                }
            }
            if (freeze) {
                if (freezeProgress.getElapsedTime().asSeconds() > freezeTime) {
                    freeze = false;
                }
            }
        }
    } else {
        NeonBallAction = false;
        CSActivated = false;
    }
}

void CosmoStation::CSSpawn()
{
    int rnd = rand() % 4;

    if (rnd == 0) {
        CosmoStationSprite.setPosition(mainX + 200, rand() % mainY);
    }
    if (rnd == 1) {
        CosmoStationSprite.setPosition(rand() % mainX, mainY + 200);
    }
    if (rnd == 2) {
        CosmoStationSprite.setPosition(-200, rand() % mainY);
    }
    if (rnd == 3) {
        CosmoStationSprite.setPosition(rand() % mainX, -200);
    }
}

void CosmoStation::NBexplosion()
{
    if (NBexplActivate) {
        NBexplSprite.setPosition(NeonBallSprite.getPosition());
        if (NBexplClock.getElapsedTime().asMilliseconds() > 10) {
            if (NBexplAnimframeX < 8) {
                NBexplSprite.setTextureRect(
                    IntRect(NBexplAnimframeX * 512, NBexplAnimframeY * 512, 512, 512));
                ++NBexplAnimframeX;
            } else {
                NBexplAnimframeX = 0;
                ++NBexplAnimframeY;
                if (NBexplAnimframeY > 8) {
                    NBexplAnimframeY = 0;
                    NBexplAnimframeX = 0;
                    NBexplActivate = false;
                }
            }
            NBexplClock.restart();
        }

        window->draw(NBexplSprite);
    }
}

void CosmoStation::reset()
{
    CSLifeBarSprite.setScale(1, 1);
    NBexplAnimframeX = 0;
    NBexplAnimframeY = 0;
    CSalive = true;
    explSound = false;
    CSSelected = false;
    NeonBallAction = false;
    CSActivated = false;
    NBtaleWait = false;
    NBexplActivate = false;
    CSSpawn();

    auto nbtit = NeonBallTale.begin();
    while (nbtit != NeonBallTale.end()) {
        nbtit = NeonBallTale.erase(nbtit);
    }
}
