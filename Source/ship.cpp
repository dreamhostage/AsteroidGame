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
    destroyingBuffer.loadFromFile("Sounds/destroying.ogg");
    damageBuffer.loadFromFile("Sounds/damage.ogg");
    font.loadFromFile("Images/18949.ttf");

    damage.setBuffer(damageBuffer);
    destroying.setBuffer(destroyingBuffer);
    ShipImprovementSound.setBuffer(ShipImprovementSoundBuffer);
    bulletDamageSound.setBuffer(bulletDamageBuffer);
    cursorSprite.setTexture(cursorTexture);
    shipExplSprite.setTexture(shipExplTexture);
    explosionSound.setBuffer(explosionSoundBuffer);
    shieldSound.setBuffer(shieldSoundBuffer);
    shot.setBuffer(shootBuffer);

    shipExplSprite.setScale(2, 2);
    shipExplSprite.setOrigin(96, 96);

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
    shipExplFrame = 0;

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

    // ShipSmoke.setTexture("Images/particle.png");
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
                    moveShip();
                    smoke::add(ShipSprite);
                }
            }
            if (!Keyboard::isKeyPressed(Keyboard::F))
                if (Mouse::isButtonPressed(Mouse::Left)) {
                    makeShoot();
                }
        }

        shipPerformance();

        if (gameStarted) {
            window->draw(ShipSprite);
            window->draw(HPtext);
            window->draw(bulletsSizeText);
            window->draw(pointsText);
            drawBullets();
        }
    }
}

void ship::moveShip()
{
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

    view = window->getView();
    view.setCenter(ViewCenter);
    window->setView(view);
}

void ship::makeShoot()
{
    if (bulletsSize) {
        if (ShootingTime.getElapsedTime().asMilliseconds() > 120) {
            if (!godmode)
                --bulletsSize;
            shot.play();
            pixelPos = Mouse::getPosition(*window);
            position1 = ShipSprite.getPosition();
            mousePosition = window->mapPixelToCoords(pixelPos);
            vd = mousePosition - position1;
            addBullet(position1, std::atan2(vd.y, vd.x) * 180.f / M_PI + 90);
            ShootingTime.restart();
        }
    } else {
        if (ShootingTimeNoBullets.getElapsedTime().asSeconds() > 1) {
            shot.play();
            pixelPos = Mouse::getPosition(*window);
            position1 = ShipSprite.getPosition();
            mousePosition = window->mapPixelToCoords(pixelPos);
            vd = mousePosition - position1;
            addBullet(position1, std::atan2(vd.y, vd.x) * 180.f / M_PI + 90);
            ShootingTimeNoBullets.restart();
        }
    }
}

void ship::shipPerformance()
{
    HPtext.setPosition(ViewCenter.x - screenX / 2 + 10, ViewCenter.y - screenY / 2);
    bulletsSizeText.setPosition(ViewCenter.x - screenX / 2 + 10, ViewCenter.y - screenY / 2 + 50);
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
        shieldText.setPosition(ViewCenter.x - screenX / 2 + 300, ViewCenter.y - screenY / 2 + 100);
        shieldResistSprite.setPosition(ShipSprite.getPosition());
        window->draw(shieldResistSprite);
        window->draw(shieldText);
    }
}

void ship::reset()
{
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
    shipExplFrame = 0;
    freeze = false;
    startposition = false;
    finalpoints = 0;
    finalexpl = false;
}
