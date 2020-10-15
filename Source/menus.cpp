#include "Asteroid.h"

Menus::Menus()
{
    pause = true;
}

void Menus::startMenu()
{
    if (pause) {
        if (!tapOnButton) {
            if (banerSprite.getPosition().y
                > ViewCenter.y + ((screenX * screenY * 300) / (1920 * 1080))) {
                banerSprite.setPosition(
                    banerSprite.getPosition().x, banerSprite.getPosition().y - 1);
                window->draw(banerSprite);
            } else {
                position1 = window->mapPixelToCoords(Mouse::getPosition(*window));
                if (position1.x > banerSprite.getPosition().x - 430
                    && position1.x < banerSprite.getPosition().x - 180
                    && position1.y > banerSprite.getPosition().y + 90
                    && position1.y < banerSprite.getPosition().y + 160) {
                    if (!selectButton) {
                        selectSound.play();
                        selectButton = true;
                    }
                    window->draw(banerSettingsSprite);
                } else if (
                    position1.x > banerSprite.getPosition().x - 70
                    && position1.x < banerSprite.getPosition().x + 50
                    && position1.y > banerSprite.getPosition().y + 120
                    && position1.y < banerSprite.getPosition().y + 190) {
                    if (!selectButton) {
                        selectSound.play();
                        selectButton = true;
                    }
                    window->draw(banerPlaySprite);
                    if (Mouse::isButtonPressed(Mouse::Left)) {
                        if (!gameStarted)
                            music.play();
                        tapOnButton = true;
                    }
                } else if (
                    position1.x > banerSprite.getPosition().x + 180
                    && position1.x < banerSprite.getPosition().x + 380
                    && position1.y > banerSprite.getPosition().y + 100
                    && position1.y < banerSprite.getPosition().y + 170) {
                    if (!selectButton) {
                        selectSound.play();
                        selectButton = true;
                    }
                    window->draw(banerAuthorSprite);
                } else {
                    selectButton = false;
                    window->draw(banerSprite);
                }
            }
        } else {
            if (banerSprite.getPosition().y > ViewCenter.y - 750) {
                banerSprite.setPosition(
                    banerSprite.getPosition().x, banerSprite.getPosition().y - 10);
                window->draw(banerSprite);
            } else {
                gameStarted = true;
                pause = false;
            }
        }
    }
}

void Menus::resetGame()
{
    ViewCenter.x = view2.getCenter().x;
    ViewCenter.y = view2.getCenter().y;
    view = view2;
    window->setView(view);
    banerAuthorSprite.setPosition(
        ViewCenter.x, ViewCenter.y + ((screenX * screenY * 300) / (1920 * 1080)));
    banerPlaySprite.setPosition(
        ViewCenter.x, ViewCenter.y + ((screenX * screenY * 300) / (1920 * 1080)));
    banerSettingsSprite.setPosition(
        ViewCenter.x, ViewCenter.y + ((screenX * screenY * 300) / (1920 * 1080)));
    banerSprite.setPosition(
        ViewCenter.x, ViewCenter.y + ((screenX * screenY * 600) / (1920 * 1080)));
    gameoverSprite.setPosition(view.getCenter().x, view.getCenter().y - 700);
    tapOnButton = false;
    ShipSprite.setPosition(ViewCenter);
    shipTexture.loadFromFile("Images/ship.png");
    ShipSprite.setTexture(shipTexture);
    ShipSprite.setRotation(0);
    LifeBarSprite.setScale(1, 1);
    health = 100;
    bulletsSize = 50;
    laserShootCount = 0;
    rocketsCount = 0;
    shieldCount = 1;
    points = 0;
    shipExplFrame = 0;
    freeze = false;
    startposition = false;
    finalpoints = 0;
    finalexpl = false;
    gameStarted = false;
    GameOver = false;
    pause = true;
    NBexplAnimframeX = 0;
    NBexplAnimframeY = 0;
    alive = true;
    explSound = false;
    CSSelected = false;
    NeonBallAction = false;
    CSActivated = true;
    NBtaleWait = false;
    NBexplActivate = false;
    CSSpawn();
}

void Menus::Gameover()
{
    if (GameOver) {
        if (!finalexpl) {
            finalexpl = true;
            explosionSound.play();
        }

        position1 = ShipSprite.getPosition();
        angle = ShipSprite.getRotation() - 0.5;
        shipExplSprite.setPosition(position1);
        shipTexture.loadFromFile("Images/destroyedship.png");
        if (shipExplFrame < 65) {
            shipExplSprite.setScale(2, 2);

            shipExplSprite.setOrigin(96, 96);
            if (shipExplTime.getElapsedTime().asMilliseconds() > 20) {
                shipExplSprite.setTextureRect(IntRect(shipExplFrame * 192, 0, 192, 192));
                shipExplSprite.setPosition(ShipSprite.getPosition());
                ++shipExplFrame;
                shipExplTime.restart();
            }
            window->draw(shipExplSprite);
        }
        ShipSprite.setPosition(position1.x - 1, position1.y - 1);
        ShipSprite.setRotation(angle);

        if (!startposition) {
            startposition = true;
            gameoverSprite.setPosition(view.getCenter().x, view.getCenter().y - screenY / 2);
            finalPointsText.setPosition(view.getCenter().x - 30, view.getCenter().y - 40);
            rang.setPosition(view.getCenter().x - 280, view.getCenter().y + 40);
            PointsSpeedRaising.restart();
            view2 = view;
        }

        if (gameoverSprite.getPosition().y < view.getCenter().y - 100) {
            gameoverSprite.setPosition(
                gameoverSprite.getPosition().x, gameoverSprite.getPosition().y + 5);
        } else {
            if (finalpoints <= points) {
                if (points > 0) {
                    finalpoints++;
                    finalPointsText.setString(std::to_string(finalpoints - 1));
                } else {
                    finalPointsText.setString("0");
                    rang.setString("Your rang: looser of loosers");
                    window->draw(rang);
                }
            } else {
                if (points < 10)
                    rang.setString("Your rang: flying turd");
                else if (points < 50)
                    rang.setString("Your rang: autistic");
                else if (points < 100)
                    rang.setString("Your rang: stupid warrior");
                else if (points < 200)
                    rang.setString("Your rang: low warrior");
                else if (points < 300)
                    rang.setString("Your rang: middle warrior");
                else if (points < 400)
                    rang.setString("Your rang: warrior");
                else if (points < 600)
                    rang.setString("Your rang: pretty warrior");
                else if (points < 800)
                    rang.setString("Your rang: strong warrior");
                else if (points < 1000)
                    rang.setString("Your rang: flying death");
                else
                    rang.setString("Your rang: DOMINATOR");

                window->draw(rang);
            }

            if (PointsSpeedRaising.getElapsedTime().asSeconds() < points / 100 + 5) {
                window->draw(finalPointsText);
            } else {
                position1 = view2.getCenter();

                distanse = sqrt(
                    (position1.x - globalCenter.x) * (position1.x - globalCenter.x)
                    + (position1.y - globalCenter.y) * (position1.y - globalCenter.y));
                if (distanse > 10) {
                    vd = globalCenter - position1;
                    angle = std::atan2(vd.y, vd.x) * 180.f / M_PI + 90;

                    angle -= (angle - 90) * 2;

                    view2.setCenter(
                        position1.x + 20 * sin((angle)*M_PI / 180),
                        position1.y + 20 * cos((angle)*M_PI / 180));

                    window->setView(view2);
                } else {
                    resetGame();
                }
            }
        }

        window->draw(gameoverSprite);
    }
}
