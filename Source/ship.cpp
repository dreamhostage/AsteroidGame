#include "Asteroid.h"

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
