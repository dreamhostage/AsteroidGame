#include "Asteroid.h"

#include <iostream>

using namespace sf;

objects::objects()
{
    font.loadFromFile("Images/18949.ttf");
    destroyingBuffer.loadFromFile("Sounds/destroying.ogg");
    damageBuffer.loadFromFile("Sounds/damage.ogg");
    screenTexture.loadFromFile("Images/screen.png");
    musicBuffer.loadFromFile("Sounds/Music.ogg");
    selectBuffer.loadFromFile("Sounds/select.ogg");
    banerTexture.loadFromFile("Images/baner.png");
    banerSettingsTexture.loadFromFile("Images/banerControl.png");
    banerPlayTexture.loadFromFile("Images/banerPlay.png");
    banerAuthorTexture.loadFromFile("Images/banerAuthor.png");
    gameoverTexture.loadFromFile("Images/GameOver.png");

    gameoverSprite.setTexture(gameoverTexture);
    selectSound.setBuffer(selectBuffer);
    banerAuthorSprite.setTexture(banerAuthorTexture);
    banerPlaySprite.setTexture(banerPlayTexture);
    banerSettingsSprite.setTexture(banerSettingsTexture);
    banerSprite.setTexture(banerTexture);
    damage.setBuffer(damageBuffer);
    destroying.setBuffer(destroyingBuffer);

    screenSprite.setTexture(screenTexture);

    music.setBuffer(musicBuffer);
    astSpawningCount = 1;
    GameOver = false;
    godmode = false;
    gameStarted = false;
    select = false;
    resettime = 0;

    music.setLoop(true);
    music.setVolume(50);

    srand(time(0));
}
void objects::setSettings(
    int inscreenX, int inscreenY, int inmainX, int inMainY, int num_ammo, int num_asteroids)
{
    ContextSettings settings;
    settings.antialiasingLevel = 8;

    if (!inscreenX || !inscreenY) {
        screenX = VideoMode::getDesktopMode().width;
        screenY = VideoMode::getDesktopMode().height;
        window = new RenderWindow(
            VideoMode(screenX, screenY), "Asteroids", Style::Fullscreen, settings);
        fullscreen = true;

        if (!inmainX || !inMainY) {
            mainX += screenX + 700;
            mainY += screenY + 700;
        } else {
            mainX = screenX + inmainX;
            mainY = screenY + inMainY;
        }
    } else {
        screenX = inscreenX;
        screenY = inscreenY;

        if (!inmainX || !inMainY) {
            mainX = screenX + 700;
            mainY = screenY + 700;
        } else {
            mainX = screenX + inmainX;
            mainY = screenY + inMainY;
        }

        window = new RenderWindow(
            VideoMode(screenX, screenY), "Asteroids", Style::Fullscreen, settings);
        fullscreen = false;
    }

    if (!num_asteroids) {
        astSpawningCount = (screenX * screenY * 20) / (1920 * 1080);
    } else
        astSpawningCount = num_asteroids;

    clisansCount = (screenX * screenY * 10) / (1920 * 1080);
    clissansSpawningDistance = (screenX * screenY * 600) / (1920 * 1080);

    ViewCenter.x = mainX / 2;
    ViewCenter.y = mainY / 2;
    view = window->getView();
    view.setCenter(ViewCenter);

    window->setFramerateLimit(120);
    window->setView(view);
    window->setMouseCursorVisible(false);

    screenSprite.setScale(
        mainX / screenSprite.getLocalBounds().width, mainY / screenSprite.getLocalBounds().height);

    // banerSprite.setScale((double)(screenX / 1920), (double)(screenY / 1080));
    size = banerTexture.getSize();
    banerSprite.setOrigin(size.x / 2, size.y / 2);
    banerSprite.setPosition(
        ViewCenter.x, ViewCenter.y + ((screenX * screenY * 600) / (1920 * 1080)));

    // banerSettingsSprite.setScale((double)(screenX / 1920), (double)(screenY / 1080));
    banerSettingsTexture.getSize();
    banerSettingsSprite.setOrigin(size.x / 2, size.y / 2);
    banerSettingsSprite.setPosition(
        ViewCenter.x, ViewCenter.y + ((screenX * screenY * 300) / (1920 * 1080)));

    // banerPlaySprite.setScale((double)(screenX / 1920), (double)(screenY / 1080));
    banerPlayTexture.getSize();
    banerPlaySprite.setOrigin(size.x / 2, size.y / 2);
    banerPlaySprite.setPosition(
        ViewCenter.x, ViewCenter.y + ((screenX * screenY * 300) / (1920 * 1080)));

    // banerAuthorSprite.setScale((double)(screenX / 1920), (double)(screenY / 1080));
    banerAuthorTexture.getSize();
    banerAuthorSprite.setOrigin(size.x / 2, size.y / 2);
    banerAuthorSprite.setPosition(
        ViewCenter.x, ViewCenter.y + ((screenX * screenY * 300) / (1920 * 1080)));

    size = gameoverTexture.getSize();
    gameoverSprite.setOrigin(size.x / 2, size.y / 2);
    gameoverSprite.setPosition(view.getCenter().x, view.getCenter().y - 700);

    globalCenter.x = mainX / 2;
    globalCenter.y = mainY / 2;
}
void objects::startMenu()
{
    if (!gameStarted) {
        if (!select2) {
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
                    if (!select) {
                        selectSound.play();
                        select = true;
                    }
                    window->draw(banerSettingsSprite);
                } else if (
                    position1.x > banerSprite.getPosition().x - 70
                    && position1.x < banerSprite.getPosition().x + 50
                    && position1.y > banerSprite.getPosition().y + 120
                    && position1.y < banerSprite.getPosition().y + 190) {
                    if (!select) {
                        selectSound.play();
                        select = true;
                    }
                    window->draw(banerPlaySprite);
                    if (Mouse::isButtonPressed(Mouse::Left)) {
                        music.play();
                        select2 = true;
                    }
                } else if (
                    position1.x > banerSprite.getPosition().x + 180
                    && position1.x < banerSprite.getPosition().x + 380
                    && position1.y > banerSprite.getPosition().y + 100
                    && position1.y < banerSprite.getPosition().y + 170) {
                    if (!select) {
                        selectSound.play();
                        select = true;
                    }
                    window->draw(banerAuthorSprite);
                } else {
                    select = false;
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
            }
        }
    }
}

ship::ship()
{
    shipTexture.loadFromFile("Images/ship.png");
    bulletTexture.loadFromFile("Images/bullet.png");
    shipExplTexture.loadFromFile("Images/shipexpl.png");
    shootBuffer.loadFromFile("Sounds/shoot.ogg");
    shieldResistTexture.loadFromFile("Images/shield.png");
    shieldSoundBuffer.loadFromFile("Sounds/shieldsound.ogg");
    explosionSoundBuffer.loadFromFile("Sounds/explosion.ogg");
    cursorTexture.loadFromFile("Images/aim.png");
    bulletDamageBuffer.loadFromFile("Sounds/bulletdamage.ogg");
    ShipImprovementSoundBuffer.loadFromFile("Sounds/improvement.ogg");

    ShipImprovementSound.setBuffer(ShipImprovementSoundBuffer);
    bulletDamageSound.setBuffer(bulletDamageBuffer);
    cursorSprite.setTexture(cursorTexture);
    shipExplSprite.setTexture(shipExplTexture);
    explosionSound.setBuffer(explosionSoundBuffer);
    shieldSound.setBuffer(shieldSoundBuffer);
    shot.setBuffer(shootBuffer);

    bulletSprite.setTexture(bulletTexture);
    ShipSprite.setTexture(shipTexture);
    size = shipTexture.getSize();
    ShipSprite.setOrigin(size.x / 2, size.y / 2);
    size = bulletTexture.getSize();
    bulletSprite.setOrigin(size.x / 2, size.y);

    shieldResistSprite.setTexture(shieldResistTexture);
    size = shieldResistTexture.getSize();
    shieldResistSprite.setOrigin(size.x / 2, size.y / 2);
    size = cursorTexture.getSize();
    cursorSprite.setOrigin(size.x / 2, size.y / 2);

    health = 100;
    bulletsSize = 50;
    shieldCount = 1;
    rocketsCount = 0;
    laserShootCount = 0;
    finalpoints = 0;
    points = 0;

    bulletsSizeText.setFont(font);
    finalPointsText.setFont(font);
    bulletsSizeText.setCharacterSize(40);
    bulletsSizeText.setFillColor(sf::Color::White);
    bulletsSizeText.setPosition(10, 50);

    HPtext.setFont(font);
    HPtext.setCharacterSize(40);
    HPtext.setFillColor(sf::Color::White);
    HPtext.setString("HP: 100");
    HPtext.setPosition(10, 0);

    pointsText.setFont(font);
    pointsText.setCharacterSize(40);
    pointsText.setFillColor(sf::Color::White);
    pointsText.setPosition(10, 100);
    pointsText.setString("SCORE: 0");

    shieldText.setFont(font);
    shieldText.setCharacterSize(40);
    shieldText.setFillColor(sf::Color::Green);

    finalPointsText.setFillColor(sf::Color::White);
    finalPointsText.setCharacterSize(50);

    rang.setFont(font);
    rang.setCharacterSize(50);
    rang.setFillColor(sf::Color::White);

    finalexpl = false;
    aimSelected = false;
    startposition = false;
    freeze = false;

    shipRotation = 3;
    shipSpeed = 3;
    bulletSpeed = 10;
}
void ship::addBullet(Vector2f& position, int rotation)
{
    bulletSprite.setPosition(position);
    bulletSprite.setRotation(rotation);
    bulletsArray.push_back(bulletSprite);
}
void ship::drawBullets()
{
    for (int i = 0; i < bulletsArray.size(); ++i) {
        window->draw(bulletsArray[i]);
        position1 = bulletsArray[i].getPosition();
        double angle = bulletsArray[i].getRotation();
        angle -= (angle - 90) * 2;
        bulletsArray[i].setPosition(
            position1.x + bulletSpeed * sin((angle)*M_PI / 180),
            position1.y + bulletSpeed * cos((angle)*M_PI / 180));
    }
}
void ship::Gameover()
{
    if (!finalexpl) {
        finalexpl = true;
        explosionSound.play();
    }
    static double k = 0;
    ++k;
    position1 = ShipSprite.getPosition();
    angle = ShipSprite.getRotation() - 0.5;
    shipExplSprite.setPosition(position1);
    shipTexture.loadFromFile("Images/destroyedship.png");
    if (k < 65) {
        shipExplSprite.setScale(2, 2);

        shipExplSprite.setOrigin(96, 96);
        shipExplSprite.setTextureRect(IntRect(int(k) * 192, 0, 192, 192));
        shipExplSprite.setPosition(ShipSprite.getPosition());
        window->draw(shipExplSprite);
        k += 0.2;
    }
    ShipSprite.setPosition(position1.x - 1, position1.y - 1);
    ShipSprite.setRotation(angle);

    if (!startposition) {
        startposition = true;
        gameoverSprite.setPosition(view.getCenter().x, view.getCenter().y - screenY / 2);
        finalPointsText.setPosition(view.getCenter().x - 30, view.getCenter().y - 40);
        rang.setPosition(view.getCenter().x - 280, view.getCenter().y + 40);
        resettime = time(NULL);
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

        if (time(NULL) - resettime < points / 100 + 7) {
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
                select2 = false;
                ShipSprite.setPosition(ViewCenter);
                shipTexture.loadFromFile("Images/ship.png");
                ShipSprite.setTexture(shipTexture);
                ShipSprite.setRotation(0);
                health = 100;
                bulletsSize = 50;
                laserShootCount = 0;
                rocketsCount = 0;
                shieldCount = 1;
                points = 0;
                freeze = false;

                startposition = false;
                k = 0;
                finalpoints = 0;
                finalexpl = false;
                gameStarted = false;
                GameOver = false;
            }
        }
    }

    window->draw(gameoverSprite);
}
void ship::draw()
{
    if (gameStarted) {
        if (!GameOver) {
            if (!freeze) {
                if (Keyboard::isKeyPressed(Keyboard::A))
                    ShipSprite.rotate(shipRotation * -1);
                if (Keyboard::isKeyPressed(Keyboard::D))
                    ShipSprite.rotate(shipRotation);
                if (Keyboard::isKeyPressed(Keyboard::W)) {
                    position1 = ShipSprite.getPosition();

                    if (position1.x < 0) {
                        position1.x = mainX;
                        ShipSprite.setPosition(position1);
                    }
                    if (position1.y < 0) {
                        position1.y = mainY;
                        ShipSprite.setPosition(position1);
                    }
                    if (position1.x > mainX) {
                        position1.x = 0;
                        ShipSprite.setPosition(position1);
                    }
                    if (position1.y > mainY) {
                        position1.y = 0;
                        ship::ShipSprite.setPosition(position1);
                    }

                    angle = ShipSprite.getRotation();
                    angle -= (angle - 90) * 2;

                    ShipSprite.setPosition(
                        position1.x + shipSpeed * sin((angle)*M_PI / 180),
                        position1.y + shipSpeed * cos((angle)*M_PI / 180));

                    view = window->getView();
                    position1 = ShipSprite.getPosition();
                    ViewCenter = ShipSprite.getPosition();

                    if (ViewCenter.x < screenX / 2)
                        ViewCenter.x = screenX / 2;
                    if (ViewCenter.y < screenY / 2)
                        ViewCenter.y = screenY / 2;

                    if (ViewCenter.x > mainX - screenX / 2)
                        ViewCenter.x = mainX - screenX / 2;

                    if (ViewCenter.y > mainY - screenY / 2)
                        ViewCenter.y = mainY - screenY / 2;

                    view.setCenter(ViewCenter);
                    window->setView(view);
                }
            }
            if (!Keyboard::isKeyPressed(Keyboard::F))
                if (Mouse::isButtonPressed(Mouse::Left)) {
                    struct timeval ts;
                    if (ShootingTime.getElapsedTime().asMilliseconds() > 120) {
                        if (bulletsSize) {
                            if (!godmode)
                                --bulletsSize;
                            shot.play();
                            pixelPos = Mouse::getPosition(*window);
                            position1 = ShipSprite.getPosition();
                            mousePosition = window->mapPixelToCoords(pixelPos);
                            vd = mousePosition - position1;
                            addBullet(position1, std::atan2(vd.y, vd.x) * 180.f / M_PI + 90);
                            ShootingTime.restart();
                        } else {
                            if (!bulletsArray.size()) {
                                shot.play();
                                pixelPos = Mouse::getPosition(*window);
                                position1 = ShipSprite.getPosition();
                                mousePosition = window->mapPixelToCoords(pixelPos);
                                vd = mousePosition - position1;
                                addBullet(position1, std::atan2(vd.y, vd.x) * 180.f / M_PI + 90);
                            }
                        }
                    }
                }
        } else {
            music.stop();
            Gameover();
        }

        HPtext.setPosition(ViewCenter.x - screenX / 2 + 10, ViewCenter.y - screenY / 2);
        bulletsSizeText.setPosition(
            ViewCenter.x - screenX / 2 + 10, ViewCenter.y - screenY / 2 + 50);
        pointsText.setPosition(ViewCenter.x - screenX / 2 + 10, ViewCenter.y - screenY / 2 + 100);

        text = "BULLETS: ";
        text += std::to_string(bulletsSize);
        bulletsSizeText.setString(text);

        text = "POINTS: ";
        text += std::to_string(points);
        pointsText.setString(text);

        text = "HP: ";
        text += std::to_string(health);
        HPtext.setString(text);
        if (health <= 30)
            HPtext.setFillColor(Color::Red);
        else
            HPtext.setFillColor(Color::White);

        if (shieldCount) {
            text = "SHIELD: ";
            text += std::to_string(shieldCount);
            shieldText.setString(text);
            shieldText.setPosition(
                ViewCenter.x - screenX / 2 + 300, ViewCenter.y - screenY / 2 + 100);
            shieldResistSprite.setPosition(ShipSprite.getPosition());
            window->draw(shieldResistSprite);
            window->draw(shieldText);
        }

        if (gameStarted) {
            window->draw(ShipSprite);
            window->draw(HPtext);
            window->draw(bulletsSizeText);
            window->draw(pointsText);
            drawBullets();
        }
    }
}

UPhealthIcon::UPhealthIcon()
{
    texture.loadFromFile("Images/HP.png");
}
void UPhealthIcon::draw()
{
    for (int i = 0; i < HPbase.size(); ++i) {
        bool destroyed = false;
        position1 = ShipSprite.getPosition();
        position2 = HPbase[i].getPosition();
        double distanse = sqrt(
            (position1.x - position2.x) * (position1.x - position2.x)
            + (position1.y - position2.y) * (position1.y - position2.y));
        if (!GameOver) {
            if (distanse < 50) {
                ShipImprovementSound.play();
                if (health < 100) {
                    health += 50;
                    if (health > 100)
                        health = 100;
                }
                std::vector<Sprite>::iterator it = HPbase.begin();
                HPbase.erase(it + i);
                destroyed = true;
            }
        }

        if (!destroyed)
            window->draw(HPbase[i]);
    }
}
void UPhealthIcon::add(Vector2f& position)
{
    Sprite newImpr;
    newImpr.setTexture(texture);
    newImpr.setPosition(position);
    size = texture.getSize();
    newImpr.setOrigin(size.x / 2, size.y / 2);
    HPbase.push_back(newImpr);
}

UPammoIcon::UPammoIcon()
{
    ammoTexture.loadFromFile("Images/ammo.png");
}
void UPammoIcon::draw()
{
    for (int i = 0; i < ammoBase.size(); ++i) {
        bool destroyed = false;
        position1 = ShipSprite.getPosition();
        position2 = ammoBase[i].getPosition();
        distanse = sqrt(
            (position1.x - position2.x) * (position1.x - position2.x)
            + (position1.y - position2.y) * (position1.y - position2.y));
        if (!GameOver) {
            if (distanse < 50) {
                ShipImprovementSound.play();
                bulletsSize += 50;
                std::vector<Sprite>::iterator it = ammoBase.begin();
                ammoBase.erase(it + i);
                destroyed = true;
            }
        }
        if (!destroyed)
            window->draw(ammoBase[i]);
    }
}
void UPammoIcon::add(Vector2f& position)
{
    Sprite newImpr;
    newImpr.setTexture(ammoTexture);
    newImpr.setPosition(position);
    size = texture.getSize();
    newImpr.setOrigin(size.x / 2, size.y / 2);
    ammoBase.push_back(newImpr);
}

ShieldIcon::ShieldIcon()
{
    shieldIconTexture.loadFromFile("Images/shieldicon.png");
}
void ShieldIcon::draw()
{
    for (int i = 0; i < shieldBase.size(); ++i) {
        bool destroyed = false;
        position1 = ShipSprite.getPosition();
        position2 = shieldBase[i].getPosition();
        distanse = sqrt(
            (position1.x - position2.x) * (position1.x - position2.x)
            + (position1.y - position2.y) * (position1.y - position2.y));
        if (!GameOver) {
            if (distanse < 50) {
                ShipImprovementSound.play();
                shieldCount += 3;
                std::vector<Sprite>::iterator it = shieldBase.begin();
                shieldBase.erase(it + i);
                destroyed = true;
            }
        }
        if (!destroyed)
            window->draw(shieldBase[i]);
    }
}
void ShieldIcon::add(Vector2f& position)
{
    Sprite newImpr;
    newImpr.setTexture(shieldIconTexture);
    newImpr.setPosition(position);
    size = texture.getSize();
    newImpr.setOrigin(size.x / 2, size.y / 2);
    shieldBase.push_back(newImpr);
}

RocketIcons::RocketIcons()
{
    rocketIconTexture.loadFromFile("Images/rockets.png");
}
void RocketIcons::draw()
{
    for (int i = 0; i < rocketsIconsBase.size(); ++i) {
        bool destroyed = false;
        position1 = ShipSprite.getPosition();
        position2 = rocketsIconsBase[i].getPosition();
        distanse = sqrt(
            (position1.x - position2.x) * (position1.x - position2.x)
            + (position1.y - position2.y) * (position1.y - position2.y));
        if (!GameOver) {
            if (distanse < 50) {
                ShipImprovementSound.play();
                rocketsCount += 5;
                std::vector<Sprite>::iterator it = rocketsIconsBase.begin();
                rocketsIconsBase.erase(it + i);
                destroyed = true;
            }
        }
        if (!destroyed)
            window->draw(rocketsIconsBase[i]);
    }
}
void RocketIcons::add(Vector2f& position)
{
    Sprite newImpr;
    newImpr.setTexture(rocketIconTexture);
    newImpr.setPosition(position);
    size = texture.getSize();
    newImpr.setOrigin(size.x / 2, size.y / 2);
    rocketsIconsBase.push_back(newImpr);
}

autoaimIcon::autoaimIcon()
{
    autoaimIconTexture.loadFromFile("Images/autoshoot.png");
}
void autoaimIcon::draw()
{
    for (int i = 0; i < autoaimIconsBase.size(); ++i) {
        bool destroyed = false;
        position1 = ShipSprite.getPosition();
        position2 = autoaimIconsBase[i].getPosition();
        distanse = sqrt(
            (position1.x - position2.x) * (position1.x - position2.x)
            + (position1.y - position2.y) * (position1.y - position2.y));
        if (!GameOver) {
            if (distanse < 50) {
                ShipImprovementSound.play();
                laserShootCount += 5;
                std::vector<Sprite>::iterator it = autoaimIconsBase.begin();
                autoaimIconsBase.erase(it + i);
                destroyed = true;
            }
        }
        if (!destroyed)
            window->draw(autoaimIconsBase[i]);
    }
}
void autoaimIcon::add(Vector2f& position)
{
    Sprite newImpr;
    newImpr.setTexture(autoaimIconTexture);
    newImpr.setPosition(position);
    size = texture.getSize();
    newImpr.setOrigin(size.x / 2, size.y / 2);
    autoaimIconsBase.push_back(newImpr);
}

asteroidsArray::asteroidsArray()
{
    frame = 0;
    explosion = false;
}

asteroids::asteroids()
{
    bigAstTexture.loadFromFile("Images/bigasteroid.png");
    smallAstTexture.loadFromFile("Images/smallasteroid.png");
    astExplTexture.loadFromFile("Images/asteroidexplosion.png");
    size = astExplTexture.getSize();
    astExplSprite.setTexture(astExplTexture);
}
void asteroids::add(Vector2f position, bool type, int speed, int rotation)
{
    asteroidsArray new_ast;
    new_ast.sprite.setPosition(position);
    new_ast.speed = speed;
    new_ast.type = type;
    new_ast.rotation = rotation;

    if (!type) {
        new_ast.sprite.setTexture(bigAstTexture);
        size = bigAstTexture.getSize();
        new_ast.sprite.setOrigin(size.x / 2, size.y / 2);
    } else {
        new_ast.sprite.setTexture(smallAstTexture);
        size = smallAstTexture.getSize();
        new_ast.sprite.setOrigin(size.x / 2, size.y / 2);
    }

    ast.push_back(new_ast);
}
void asteroids::physic()
{
    if (ast.size() > 1) {
        for (int i = 0; i < asteroids::ast.size() - 1; ++i) {
            Vector2f first = asteroids::ast[i].sprite.getPosition();
            for (int k = i + 1; k < asteroids::ast.size(); ++k) {
                Vector2f second = asteroids::ast[k].sprite.getPosition();
                double distanse = sqrt(
                    (first.x - second.x) * (first.x - second.x)
                    + (first.y - second.y) * (first.y - second.y));
                if (distanse < 50) {
                    Vector2f pos2 = asteroids::ast[k].sprite.getPosition();
                    sf::Vector2f v(first.x, first.y);
                    sf::Vector2f vd = v - pos2;
                    int rot = std::atan2(vd.y, vd.x) * 180 / M_PI + 90;
                    asteroids::ast[i].rotation = rot;
                    asteroids::ast[k].rotation = rot + 180;
                    std::swap(ast[i].speed, ast[k].speed);
                }
            }
            asteroids::ast[i].sprite.rotate(asteroids::ast[i].speed);
        }
    }
}
bool asteroids::spawningChecking(Vector2f& first)
{
    for (int i = 0; i < asteroids::ast.size(); ++i) {
        Vector2f second = asteroids::ast[i].sprite.getPosition();
        double distanse = sqrt(
            (first.x - second.x) * (first.x - second.x)
            + (first.y - second.y) * (first.y - second.y));
        if (distanse < 60) {
            return false;
        }
    }
    return true;
}
void asteroids::AsteroidSpawning()
{
    if (AsteroidsSpawningTime.getElapsedTime().asSeconds() > 4) {
        AsteroidsSpawningTime.restart();

        for (int i = 0; i < astSpawningCount; ++i) {
            Vector2f position;
            static int side = 0;
            ++side;
            if (side > 4)
                side = 0;

            if (!side) {
                int temp = mainX / 60;
                position.x = (rand() % temp) * 60;
                position.y = mainY + 100;
                if (spawningChecking(position)) {
                    add(position, 0, (rand() % 4) + 1, 270 + rand() % 180);
                }
            } else if (side == 1) {
                int temp = mainY / 60;
                position.x = -100;
                position.y = (rand() % temp) * 60;
                if (spawningChecking(position)) {
                    add(position, 0, (rand() % 4) + 1, rand() % 180);
                }
            } else if (side == 2) {
                int temp = mainX / 60;
                position.x = (rand() % temp) * 60;
                position.y = -100;
                if (spawningChecking(position)) {
                    add(position, 0, (rand() % 4) + 1, 90 + rand() % 180);
                }
            } else if (side == 3) {
                int temp = mainY / 60;
                position.x = mainX + 100;
                position.y = (rand() % temp) * 60;
                if (spawningChecking(position)) {
                    add(position, 0, (rand() % 4) + 1, 180 + rand() % 180);
                }
            } else if (side == 4) {
                static int k = 0;
                ++k;
                if (k > 3)
                    k = 0;

                if (!k)
                    position = {-100, -100};
                else if (k == 1) {
                    position.x = -100;
                    position.y = mainY - 1;
                } else if (k == 2) {
                    position.x = mainX - 1;
                    position.y = -100;
                } else if (k == 3) {
                    position.x = mainX + 100;
                    position.y = mainY - 1;
                }

                if (spawningChecking(position)) {
                    Vector2f pos = ship::ShipSprite.getPosition();
                    sf::Vector2f v(pos.x, pos.y);
                    sf::Vector2f vd = v - position;
                    add(position, 0, (rand() % 4) + 1, std::atan2(vd.y, vd.x) * 180.f / M_PI + 90);
                }
            }
        }
    }
}
void asteroids::draw()
{
    if (gameStarted) {
        AsteroidSpawning();
        physic();
        Vector2f ship = ship::ShipSprite.getPosition();
        std::vector<asteroidsArray>::iterator it;
        std::vector<Sprite>::iterator bit;

        for (int i = 0; i < asteroids::ast.size(); ++i) {
            if (ast[i].explosion) {
                if (ast[i].frame < 20) {
                    if (!ast[i].type) {
                        astExplSprite.setScale(2, 2);
                    } else {
                        astExplSprite.setScale(1, 1);
                    }

                    astExplSprite.setOrigin(25, 25);
                    astExplSprite.setTextureRect(IntRect(int(ast[i].frame) * 50, 0, 50, 50));
                    astExplSprite.setPosition(ast[i].sprite.getPosition());
                    window->draw(astExplSprite);
                    ast[i].frame += 0.2;
                } else {
                    it = ast.begin();
                    ast.erase(it + i);
                }
            } else {
                bool destroyed = false;
                Vector2f temp = asteroids::ast[i].sprite.getPosition();

                double distanseShip = sqrt(
                    (ship.x - temp.x) * (ship.x - temp.x) + (ship.y - temp.y) * (ship.y - temp.y));

                if (temp.x < (mainX + 110) && temp.y < (mainY + 110) && temp.x > -110
                    && temp.y > -110) {
                    double angle = asteroids::ast[i].rotation;
                    angle -= (angle - 90) * 2;
                    asteroids::ast[i].sprite.setPosition(
                        temp.x + asteroids::ast[i].speed * sin((angle)*M_PI / 180),
                        temp.y + asteroids::ast[i].speed * cos((angle)*M_PI / 180));
                } else {
                    it = ast.begin();
                    ast.erase(it + i);
                    destroyed = true;
                }

                if (gameStarted) {
                    if (!destroyed) {
                        if (distanseShip < 50) {
                            if (!asteroids::ast[i].type) {
                                destroyed = true;
                                ast[i].explosion = true;

                                damage.play();

                                if (!shieldCount) {
                                    if (!godmode)
                                        health -= 20;
                                    if (health <= 0) {
                                        health = 0;
                                        GameOver = true;
                                    }
                                } else {
                                    --shieldCount;
                                    shieldSound.play();
                                }
                            } else if (distanseShip < 30) {
                                destroyed = true;
                                ast[i].explosion = true;

                                damage.play();

                                if (!shieldCount) {
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
                        }

                        ///////////////////////////////////////////////////////////////////////////////////////

                        for (int k = 0; k < bulletsArray.size(); ++k) {
                            Vector2f bulletPosition = bulletsArray[k].getPosition();

                            if (bulletPosition.x < mainX && bulletPosition.y < mainY
                                && bulletPosition.x > 0 && bulletPosition.y > 0) {
                                double distanseBullet = sqrt(
                                    (bulletPosition.x - temp.x) * (bulletPosition.x - temp.x)
                                    + (bulletPosition.y - temp.y) * (bulletPosition.y - temp.y));

                                if (!asteroids::ast[i].type) {
                                    if (distanseBullet < 50) {
                                        destroyed = true;
                                        ast[i].explosion = true;
                                        destroying.play();

                                        bit = bulletsArray.begin();
                                        bulletsArray.erase(bit + k);

                                        ++points;

                                        temp.x -= 30;
                                        int rotation = rand() % 360;

                                        add(temp, 1, 2, rotation);

                                        temp.x += 60;
                                        add(temp, 1, 2, rotation + 100);

                                        ///////////////////////////////////////////
                                        int rnd = rand() % 3;

                                        if (rnd == 1) {
                                            Vector2f position = temp;

                                            if ((mainX - position.x) < 50)
                                                position.x -= 80;

                                            if ((mainY - position.y) < 50)
                                                position.y -= 80;

                                            if (position.x < 50)
                                                position.x = 80;

                                            if (position.y < 50)
                                                position.y = 80;

                                            int rnd2 = rand() % 5;

                                            if (bulletsSize < 2)
                                                rnd2 = 3;

                                            if (rnd2 == 0) {
                                                UPhealthIcon::add(position);
                                            }

                                            if (rnd2 == 1) {
                                                autoaimIcon::add(position);
                                            }
                                            if (rnd2 == 2) {
                                                RocketIcons::add(position);
                                            }
                                            if (rnd2 == 3) {
                                                UPammoIcon::add(position);
                                            }
                                            if (rnd2 == 4) {
                                                ShieldIcon::add(position);
                                            }
                                        }
                                        ///////////////////////////////////////////
                                    }
                                } else {
                                    if (distanseBullet < 22) {
                                        destroying.play();
                                        bit = bulletsArray.begin();
                                        bulletsArray.erase(bit + k);
                                        ++points;
                                        destroyed = true;
                                        ast[i].explosion = true;
                                    }
                                }
                            } else {
                                std::vector<Sprite>::iterator bit = bulletsArray.begin();
                                bulletsArray.erase(bit + k);
                            }
                        }

                        ///////////////////////////////////////////////////////////////////////////////////////
                    }
                }

                if (!destroyed)
                    window->draw(ast[i].sprite);
            }
        }
    } else {
        for (int i = 0; i < ast.size(); ++i) {
            std::vector<asteroidsArray>::iterator it = ast.begin();
            ast.erase(it);
        }
    }
}

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

clissanShips::clissanShips()
{
    health = 100;
    final = 0;
    destroyed = false;
    time1 = time(NULL);
    time2 = 0;
    selected = false;
    shoot = false;
}

clissans::clissans()
{
    clissanshipTexture.loadFromFile("Images/clissanship.png");
    clissansbulletTexture.loadFromFile("Images/clisanbullet.png");
    ClissansLifeTexture.loadFromFile("Images/ClissansLife.png");
    clissansshootBuffer.loadFromFile("Sounds/clisanshoot.ogg");
    laserinBuffer.loadFromFile("Sounds/laserin.ogg");
    clissansexplosionSoundBuffer.loadFromFile("Sounds/explosion.ogg");
    frameTexture.loadFromFile("Images/frame.png");

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

    size = clissanshipTexture.getSize();
    clissanShipSprite.setOrigin(size.x / 2, size.y / 2);
    size = clissansbulletTexture.getSize();
    clissansbulletSprite.setOrigin(size.x / 2, size.y);
    size = frameTexture.getSize();
    frameSprite.setOrigin(size.x / 2, size.y / 2);

    side = true;
    selNumb = -1;
    selectedCount = 0;

    mainX = VideoMode::getDesktopMode().width + 700;
    mainY = VideoMode::getDesktopMode().height + 700;
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
            clisansShipsArray.push_back(new_cship);
        }

        if (rnd == 1) {
            clissanShipSprite.setPosition(0, rand() % mainY);
            new_cship.sprite = clissanShipSprite;
            new_cship.LifeSprite = ClissansLifeSprite;
            new_cship.pos.x = rand() % mainX;
            new_cship.pos.y = rand() % mainY;
            clisansShipsArray.push_back(new_cship);
        }

        if (rnd == 2) {
            clissanShipSprite.setPosition(rand() % mainX, mainY);
            new_cship.sprite = clissanShipSprite;
            new_cship.LifeSprite = ClissansLifeSprite;
            new_cship.pos.x = rand() % mainX;
            new_cship.pos.y = rand() % mainY;
            clisansShipsArray.push_back(new_cship);
        }

        if (rnd == 3) {
            clissanShipSprite.setPosition(mainX, rand() % mainY);
            new_cship.sprite = clissanShipSprite;
            new_cship.LifeSprite = ClissansLifeSprite;
            new_cship.pos.x = rand() % mainX;
            new_cship.pos.y = rand() % mainY;
            clisansShipsArray.push_back(new_cship);
        }
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
void clissans::makeShoot(int i)
{
    if (!GameOver) {
        if (!clisansShipsArray[i].shoot) {
            position1 = ShipSprite.getPosition();
            position2 = clisansShipsArray[i].sprite.getPosition();
            distanse = sqrt(
                (position2.x - position1.x) * (position2.x - position1.x)
                + (position2.y - position1.y) * (position2.y - position1.y));
            if (distanse < 550) {
                clissansshot.play();
                vd = position1 - position2;
                addBullet(position2, std::atan2(vd.y, vd.x) * 180.f / M_PI + 90);
                clisansShipsArray[i].shoot = true;
            }
        }
        clisansShipsArray[i].time2 = time(NULL);
        if (clisansShipsArray[i].time2 - clisansShipsArray[i].time1 > 1) {
            clisansShipsArray[i].time1 = time(NULL);
            clisansShipsArray[i].shoot = false;
        }
    }
}
void clissans::draw()
{
    if (gameStarted) {
        for (int i = 0; i < clisansShipsArray.size(); ++i) {
            if (clisansShipsArray[i].destroyed) {
                if (clisansShipsArray[i].final < 65) {
                    shipExplSprite.setScale(1, 1);

                    shipExplSprite.setOrigin(96, 96);
                    shipExplSprite.setTextureRect(
                        IntRect(int(clisansShipsArray[i].final) * 192, 0, 192, 192));
                    shipExplSprite.setPosition(clisansShipsArray[i].sprite.getPosition());
                    window->draw(shipExplSprite);
                    clisansShipsArray[i].final += 0.4;
                } else {
                    std::vector<clissanShips>::iterator csit = clisansShipsArray.begin();
                    clisansShipsArray.erase(csit + i);
                }
            } else {
                if (Keyboard::isKeyPressed(Keyboard::F))
                    if (Mouse::isButtonPressed(Mouse::Left)) {
                        position1 = clisansShipsArray[i].sprite.getPosition();
                        pixelPos = Mouse::getPosition(*window);
                        position2 = window->mapPixelToCoords(pixelPos);
                        distanse = sqrt(
                            (position1.x - position2.x) * (position1.x - position2.x)
                            + (position1.y - position2.y) * (position1.y - position2.y));

                        if (distanse < 70) {
                            for (int k = 0; k < clisansShipsArray.size(); ++k)
                                if (clisansShipsArray[k].selected)
                                    clisansShipsArray[k].selected = false;
                            clisansShipsArray[i].selected = true;
                            aimSelected = true;
                        }
                    }

                if (clisansShipsArray[i].selected) {
                    frameSprite.setPosition(clisansShipsArray[i].sprite.getPosition());
                    window->draw(frameSprite);
                }

                temp = clisansShipsArray[i].sprite.getPosition();
                position2 = ShipSprite.getPosition();

                for (int k = 0; k < bulletsArray.size(); ++k) {
                    bulletPos = bulletsArray[k].getPosition();
                    double bulletDist = sqrt(
                        (bulletPos.x - temp.x) * (bulletPos.x - temp.x)
                        + (bulletPos.y - temp.y) * (bulletPos.y - temp.y));
                    if (bulletDist < 50) {
                        clisansShipsArray[i].health -= 10;
                        clisansShipsArray[i].LifeSprite.setScale(
                            clisansShipsArray[i].LifeSprite.getScale().x - 0.1,
                            clisansShipsArray[i].LifeSprite.getScale().y);
                        std::vector<Sprite>::iterator bit = bulletsArray.begin();
                        bulletsArray.erase(bit + k);
                        laserinSound.play();
                    }
                }

                if (clisansShipsArray[i].health <= 0) {
                    explosionSound.play();
                    clisansShipsArray[i].destroyed = true;
                    if (clisansShipsArray[i].selected) {
                        clisansShipsArray[i].selected = false;
                        aimSelected = false;
                    }
                    selNumb = -1;
                    points += 10;
                }

                if (temp.x < 0) {
                    temp.x = mainX;
                    clisansShipsArray[i].sprite.setPosition(temp);
                }
                if (temp.y < 0) {
                    temp.y = mainY;
                    clisansShipsArray[i].sprite.setPosition(temp);
                }
                if (temp.x > mainX) {
                    temp.x = 0;
                    clisansShipsArray[i].sprite.setPosition(temp);
                }
                if (temp.y > mainY) {
                    temp.y = 0;
                    clisansShipsArray[i].sprite.setPosition(temp);
                }

                double distanse = sqrt(
                    (clisansShipsArray[i].pos.x - temp.x) * (clisansShipsArray[i].pos.x - temp.x)
                    + (clisansShipsArray[i].pos.y - temp.y)
                        * (clisansShipsArray[i].pos.y - temp.y));
                double shipDistanse = sqrt(
                    (position2.x - temp.x) * (position2.x - temp.x)
                    + (position2.y - temp.y) * (position2.y - temp.y));
                int angle = 0;
                float current = 0;

                makeShoot(i);

                if (distanse > 200) {
                    if (shipDistanse < clissansSpawningDistance) {
                        vd = position2 - temp;
                        angle = std::atan2(vd.y, vd.x) * 180 / M_PI + 170;

                        current = clisansShipsArray[i].sprite.getRotation();
                        if (current < angle)
                            ++current;
                        else if (current > angle)
                            --current;
                        else
                            current = angle;
                    } else {
                        vd = clisansShipsArray[i].pos - temp;
                        angle = std::atan2(vd.y, vd.x) * 180 / M_PI + 90;

                        if (angle > 360)
                            angle = 360 - angle;
                        else if (angle < 0)
                            angle = 360 + angle;

                        current = clisansShipsArray[i].sprite.getRotation();
                        if (current < angle)
                            ++current;
                        else if (current > angle)
                            --current;
                        else
                            current = angle;
                    }
                } else {
                    clisansShipsArray[i].pos.x = rand() % mainX;
                    clisansShipsArray[i].pos.y = rand() % mainY;
                    if (clisansShipsArray[i].pos.x < 200)
                        clisansShipsArray[i].pos.x = 200;
                    if (clisansShipsArray[i].pos.x > mainX - 200)
                        clisansShipsArray[i].pos.x = mainX - 200;

                    if (clisansShipsArray[i].pos.y < 200)
                        clisansShipsArray[i].pos.y = 200;
                    if (clisansShipsArray[i].pos.y > mainX - 200)
                        clisansShipsArray[i].pos.y = mainX - 200;
                }

                clisansShipsArray[i].sprite.setRotation(current);
                current -= (current - 90) * 2;
                clisansShipsArray[i].sprite.setPosition(
                    temp.x + 2 * sin((current)*M_PI / 180), temp.y + 2 * cos((current)*M_PI / 180));

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

    NeonBallTaleSprite.setScale(0.2, 0.2);
    size = NeonBallTaleTexture.getSize();
    NeonBallTaleSprite.setOrigin(size.x / 2, size.y / 2);

    NeonBallSprite.setScale(0.2, 0.2);
    size = NeonBallTexture.getSize();
    NeonBallSprite.setOrigin(size.x / 2, size.y / 2);

    CosmoStationSprite.setScale(0.5, 0.5);
    LifeBarTexture.loadFromFile("Images/CosmoStationLife.png");
    LifeBarSprite.setTexture(LifeBarTexture);

    size = CosmoStationTexture.getSize();
    CosmoStationSprite.setOrigin(size.x / 2, size.y / 2);
    size = LifeBarTexture.getSize();
    LifeBarSprite.setOrigin(size.x / 2, size.y / 2);

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
    alive = true;
    explSound = false;
    CSSelected = false;
    NeonBallAction = false;
    CSActivated = true;
    NBtaleWait = false;
    NBexplActivate = false;
}
void CosmoStation::draw()
{
    if (alive) {
        moving();
        LifeBar();
        BulletsChecking();
        laserScaning();
        FrameMoving();
        Attack();
        NeonBallMoving();
        window->draw(CosmoStationSprite);
        window->draw(LifeBarSprite);
        if (CSSelected)
            window->draw(CSFrameSprite);
    } else {
        if (explSound) {
            explosionSound.play();
            explSound = false;
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
                        freezeProgress = std::time(0);
                        NBexplActivate = true;
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
    LifeBarSprite.setPosition(
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
            if (LifeBarSprite.getScale().x > 0.005) {
                LifeBarSprite.setScale(
                    LifeBarSprite.getScale().x - 0.005, LifeBarSprite.getScale().y);
            } else {
                alive = false;
                explSound = true;
                points += 400;
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
            } else {
                autoAimTime = 0;
                std::vector<asteroidsArray>::iterator it = ast.begin();
                ast.erase(it + i);
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
                        } else {
                            std::time_t temp = std::time(0);
                            if (temp - freezeProgress > freezeTime) {
                                freeze = false;
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

rockets::rockets()
{
    rocketTexture.loadFromFile("Images/Rocket.png");
    rocketBuffer.loadFromFile("Sounds/rocket.ogg");
    rockExplTexture.loadFromFile("Images/asteroidexplosion.png");
    rockExplSprite.setTexture(astExplTexture);
    rocketSound.setBuffer(rocketBuffer);
    rocketsText.setFont(font);
    rocketsText.setCharacterSize(40);
    rocketsText.setFillColor(sf::Color::Yellow);
    rocketSprite.setTexture(rocketTexture);
    size = rocketTexture.getSize();
    rocketSprite.setOrigin(size.x / 2, size.y / 2);
    rocketExplosion = false;
    rocketInProgress = false;
    frame = 0;
    shortestDistanse = 0;
    n = 0;
}
void rockets::draw()
{
    if (rocketExplosion) {
        if (frame < 20) {
            rockExplSprite.setScale(2, 2);
            rockExplSprite.setOrigin(25, 25);
            rockExplSprite.setTextureRect(IntRect(int(frame) * 50, 0, 50, 50));
            window->draw(rockExplSprite);
            frame += 0.2;
        } else {
            frame = 0;
            rocketExplosion = false;
        }
    }
    if (rocketsCount) {
        rocketsText.setPosition(ViewCenter.x - screenX / 2 + 300, ViewCenter.y - screenY / 2 + 50);
        text = "ROCKETS: ";
        text += std::to_string(rocketsCount);
        rocketsText.setString(text);
        window->draw(rocketsText);

        if (!rocketInProgress) {
            if (Mouse::isButtonPressed(Mouse::Right)) {
                if (!GameOver) {
                    rocketSound.play();
                    rocketSprite.setPosition(ShipSprite.getPosition());
                    rocketInProgress = true;
                }
            }
        }
        if (rocketInProgress) {
            window->draw(rocketSprite);
            if (!aimSelected && !CSSelected) {
                if (ast.size()) {
                    position1 = ShipSprite.getPosition();
                    shortestDistanse = 100000;
                    n = 0;

                    for (int i = 0; i < ast.size(); ++i) {
                        position2 = ast[i].sprite.getPosition();
                        distanse = sqrt(
                            (position1.x - position2.x) * (position1.x - position2.x)
                            + (position1.y - position2.y) * (position1.y - position2.y));
                        if (shortestDistanse > distanse) {
                            shortestDistanse = distanse;
                            n = i;
                        }
                    }

                    position1 = rocketSprite.getPosition();
                    position2 = ast[n].sprite.getPosition();
                    distanse = sqrt(
                        (position1.x - position2.x) * (position1.x - position2.x)
                        + (position1.y - position2.y) * (position1.y - position2.y));

                    if (distanse > 50) {
                        position2 = ast[n].sprite.getPosition();
                        vd = position2 - position1;
                        angle = std::atan2(vd.y, vd.x) * 180.f / M_PI + 90;
                        rocketSprite.setRotation(angle);
                        angle -= (angle - 90) * 2;
                        rocketSprite.setPosition(
                            position1.x + bulletSpeed * sin((angle)*M_PI / 180),
                            position1.y + bulletSpeed * cos((angle)*M_PI / 180));
                    } else {
                        rockExplSprite.setPosition(asteroids::ast[n].sprite.getPosition());
                        std::vector<asteroidsArray>::iterator it = ast.begin();
                        asteroids::ast.erase(it + n);
                        if (!godmode)
                            --rocketsCount;
                        rocketInProgress = false;
                        destroying.play();
                        rocketExplosion = true;
                        ++points;
                    }
                } else {
                    position1 = rocketSprite.getPosition();
                    angle = rocketSprite.getRotation() + 1;
                    rocketSprite.setRotation(angle);
                    angle -= (angle - 90) * 2;
                    rocketSprite.setPosition(
                        position1.x + bulletSpeed * sin((angle)*M_PI / 180),
                        position1.y + bulletSpeed * cos((angle)*M_PI / 180));
                }
            } else if (aimSelected) {
                position1 = rocketSprite.getPosition();

                for (int i = 0; i < clisansShipsArray.size(); ++i) {
                    if (clisansShipsArray[i].selected) {
                        position1 = rocketSprite.getPosition();
                        position2 = clisansShipsArray[i].sprite.getPosition();
                        distanse = sqrt(
                            (position1.x - position2.x) * (position1.x - position2.x)
                            + (position1.y - position2.y) * (position1.y - position2.y));
                        if (distanse < 50) {
                            rockExplSprite.setPosition(position2);
                            if (!godmode)
                                --rocketsCount;
                            rocketInProgress = false;
                            destroying.play();
                            rocketExplosion = true;
                            clisansShipsArray[i].health -= 50;
                            clisansShipsArray[i].LifeSprite.setScale(
                                clisansShipsArray[i].LifeSprite.getScale().x - 0.5,
                                clisansShipsArray[i].LifeSprite.getScale().y);

                        } else {
                            position2 = clisansShipsArray[i].sprite.getPosition();
                            vd = position2 - position1;
                            angle = std::atan2(vd.y, vd.x) * 180.f / M_PI + 90;
                            rocketSprite.setRotation(angle);
                            angle -= (angle - 90) * 2;
                            rocketSprite.setPosition(
                                position1.x + bulletSpeed * sin((angle)*M_PI / 180),
                                position1.y + bulletSpeed * cos((angle)*M_PI / 180));
                        }
                    }
                }
            } else if (CSSelected) {
                position1 = rocketSprite.getPosition();
                position2 = CosmoStationSprite.getPosition();
                distanse = sqrt(
                    (position1.x - position2.x) * (position1.x - position2.x)
                    + (position1.y - position2.y) * (position1.y - position2.y));
                if (distanse < 100) {
                    rockExplSprite.setPosition(position2);
                    if (!godmode)
                        --rocketsCount;
                    rocketInProgress = false;
                    destroying.play();
                    rocketExplosion = true;
                    CSblaming = 7;
                    CosmoStationSprite.setColor(Color::Red);
                    if (LifeBarSprite.getScale().x > 0.005) {
                        LifeBarSprite.setScale(
                            LifeBarSprite.getScale().x - 0.025, LifeBarSprite.getScale().y);
                    } else {
                        alive = false;
                        explSound = true;
                        CSSelected = false;
                        points += 400;
                    }
                } else {
                    position2 = CosmoStationSprite.getPosition();
                    vd = position2 - position1;
                    angle = std::atan2(vd.y, vd.x) * 180.f / M_PI + 90;
                    rocketSprite.setRotation(angle);
                    angle -= (angle - 90) * 2;
                    rocketSprite.setPosition(
                        position1.x + bulletSpeed * sin((angle)*M_PI / 180),
                        position1.y + bulletSpeed * cos((angle)*M_PI / 180));
                }
            }
        }
    }
}

framework::~framework()
{
    delete window;
}
framework::framework(
    unsigned int x,
    unsigned int y,
    unsigned int num_asteroids,
    unsigned int num_ammo,
    unsigned int godmode,
    int mapX,
    int mapY)
{
    this->godmode = godmode;
    this->godmode = true;
    objects::setSettings(x, y, mapX, mapY, num_ammo, num_asteroids);
    ship::ShipSprite.setPosition(mainX / 2, mainY / 2);
    CSSpawn();
}
void framework::run()
{
    while (window->isOpen()) {
        Event event;
        while (window->pollEvent(event)) {
            if (event.type == Event::Closed)
                window->close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            if (fullscreen) {
                window->create(VideoMode(screenX, screenY), "Asteroids");
                fullscreen = false;
                window->setFramerateLimit(120);
                window->setView(view);
                window->setMouseCursorVisible(false);
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::F1)) {
            if (!fullscreen) {
                window->create(VideoMode(screenX, screenY), "Asteroids", Style::Fullscreen);
                fullscreen = true;
                window->setFramerateLimit(120);
                window->setView(view);
                window->setMouseCursorVisible(false);
            }
        }

        cursorSprite.setPosition(window->mapPixelToCoords(Mouse::getPosition(*window)));
        mousePosition = window->mapPixelToCoords(Mouse::getPosition(*window));

        window->draw(screenSprite);
        UPhealthIcon::draw();
        UPammoIcon::draw();
        ShieldIcon::draw();
        RocketIcons::draw();
        rockets::draw();
        autoaimIcon::draw();
        laser::draw();
        asteroids::draw();
        ship::draw();
        clissans::draw();
        CosmoStation::draw();
        startMenu();
        window->draw(cursorSprite);

        window->display();
        window->clear();
    }
}
