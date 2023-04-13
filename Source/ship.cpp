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
    ammoTexture.loadFromFile("Images/ammo.png");
    shieldCountTexture.loadFromFile("Images/shield.png");

    shieldCountSprite.setTexture(shieldCountTexture);
    size = shieldCountTexture.getSize();
    shieldCountSprite.setOrigin(size.x / 2, size.y / 2);
    shieldCountSprite.setScale(0.45, 0.45);

    ammoSprite.setTexture(ammoTexture);
    size = ammoTexture.getSize();
    ammoSprite.setOrigin(size.x / 2, size.y / 2);
    ammoSprite.setScale(0.6, 0.6);

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
    foneSprite.setOrigin(size.x / 2, size.y / 2);
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
    bIsPlayerShipInsideTunnel = false;

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

void ship::Tick()
{
    if (gameStarted) {
        if (!GameOver) {
            //---
            b2Vec2 pos = body->GetPosition();
            float angl = body->GetAngle();
            ShipSprite.setPosition(pos.x * SCALE, pos.y * SCALE);

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

            foneSprite.setPosition(ShipSprite.getPosition());
            view = window->getView();
            view.setCenter(ViewCenter);
            window->setView(view);

            position1 = ShipSprite.getPosition();
            b2Vec2 posi;

            if (position1.x < 0) {
                position1.x = mainX;
                //ShipSprite.setPosition(position1);
                posi.x = position1.x / SCALE;
                posi.y = position1.y / SCALE;
                body->SetTransform(posi, body->GetAngle());
            }
            if (position1.y < 0) {
                position1.y = mainY;
                //ShipSprite.setPosition(position1);
                posi.x = position1.x / SCALE;
                posi.y = position1.y / SCALE;
                body->SetTransform(posi, body->GetAngle());
            }
            if (position1.x > mainX) {
                position1.x = 0;
                //ShipSprite.setPosition(position1);
                posi.x = position1.x / SCALE;
                posi.y = position1.y / SCALE;
                body->SetTransform(posi, body->GetAngle());
            }
            if (position1.y > mainY) {
                position1.y = 0;
                //ship::ShipSprite.setPosition(position1);
                posi.x = position1.x / SCALE;
                posi.y = position1.y / SCALE;
                body->SetTransform(posi, body->GetAngle());
            }
            //---

            if (!freeze) {
                if (Keyboard::isKeyPressed(Keyboard::A))
                {
                    ShipSprite.rotate(shipRotation * -1);
                    //body->SetTransform(body->GetPosition(), body->GetAngle() - 0.1f);
                }
                if (Keyboard::isKeyPressed(Keyboard::D))
                {
                    ShipSprite.rotate(shipRotation);
                    //body->SetTransform(body->GetPosition(), body->GetAngle() + 0.1f);
                }
                if (Keyboard::isKeyPressed(Keyboard::W)) 
                {
                    if (!bIsPlayerShipInsideTunnel)
                    {
                        moveShip();
                        smoke::add(ShipSprite);
                    }
                }
            }
            if (!Keyboard::isKeyPressed(Keyboard::F))
                if (Mouse::isButtonPressed(Mouse::Left)) {
                    if (!bIsPlayerShipInsideTunnel)
                    {
                        makeShoot();
                    }
                }
        }

        shipPerformance();

        if (gameStarted) {
            window->draw(ShipSprite);
            window->draw(pointsText);
            if (ship::health)
            {
                window->draw(ammoSprite);
                window->draw(bulletsSizeText);
                window->draw(LifeBar);
            }
            drawBullets();
        }
        tunnelEngine();
    }
}

void ship::moveShip()
{
    /*angle = ShipSprite.getRotation();
    angle -= (angle - 90) * 2;

    ShipSprite.setPosition(
        position1.x + shipSpeed * sin((angle)*M_PI / 180),
        position1.y + shipSpeed * cos((angle)*M_PI / 180));*/

    //---
    body->SetTransform(body->GetPosition(), (ShipSprite.getRotation() - 180) / DEG);
    b2Vec2 force = b2Vec2((cos(body->GetAngle() - 4.7) * 20.0f), (sin(body->GetAngle() - 4.7) * 20.0f));
    b2Vec2 ImpulsePoint = body->GetPosition();
    //body->ApplyLinearImpulse(force, ImpulsePoint, true);
    body->ApplyForce(force, ImpulsePoint, true);
    //---
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
    if (ship::health)
    {
        bulletsSizeText.setPosition(ViewCenter.x - screenX / 2 + 50, ViewCenter.y - ammoTexture.getSize().y / 3);
        pointsText.setPosition(ViewCenter.x, ViewCenter.y - screenY / 2 + 10);
        ammoSprite.setPosition(ViewCenter.x - screenX / 2 + ammoTexture.getSize().x / 2, ViewCenter.y);

        bulletsSizeText.setString(std::to_string(bulletsSize));

        pointsText.setString(std::to_string(points));

        if (health <= 30)
        {
            ship::LifeBar.setFillColor(sf::Color(121, 0, 0, 180));
        }
        else
        {
            ship::LifeBar.setFillColor(sf::Color(0, 121, 0, 180));
        }

        if (shieldCount) {
            shieldText.setString(std::to_string(shieldCount));

            shieldText.setPosition(ViewCenter.x - screenX / 2 + shieldCountTexture.getSize().x / 2, ViewCenter.y - shieldCountTexture.getSize().y + 2);
            shieldCountSprite.setPosition(ViewCenter.x - screenX / 2 + shieldCountTexture.getSize().x / 3 - 5, ViewCenter.y - shieldCountTexture.getSize().y / 2 - 15);

            shieldResistSprite.setPosition(ShipSprite.getPosition());
            window->draw(shieldResistSprite);
            window->draw(shieldText);
            window->draw(shieldCountSprite);
        }

        LifeBar.setPosition(view.getCenter().x, view.getCenter().y - (screenY / 2) + 10);
    }
}

void ship::reset()
{
    // ShipSprite.setPosition(ViewCenter);

    b2Vec2 posit;
    posit.x = ViewCenter.x / SCALE;
    posit.y = ViewCenter.y / SCALE;
    body->SetTransform(posit, (0 - 180) / DEG);
    body->SetLinearVelocity(b2Vec2(0, 0));
    body->SetAngularVelocity(0);

    shipTexture.loadFromFile("Images/ship.png");
    ShipSprite.setTexture(shipTexture);
    ShipSprite.setRotation(0);
    ship::LifeBar.setSize(sf::Vector2f(screenX - 50, 10));
    ship::LifeBar.setOrigin((screenX - 50) / 2, 5);
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

void ship::tunnelEngine()
{
    if (tunnelActivated)
    {
        position1 = ShipSprite.getPosition();
        position2 = portalCircle.getPosition();
        distanse = sqrt(
            (position1.x - position2.x) * (position1.x - position2.x)
            + (position1.y - position2.y) * (position1.y - position2.y));

        if (portalSize > 190)
        {
            if (distanse < 170)
            {
                if (portalSize < screenX + 200)
                {
                    portalSize += 0.7;
                    portalCircle.setRadius(portalSize + 20);
                    portalCircle.setOrigin(portalCircle.getRadius(), portalCircle.getRadius());
                }
                bIsPlayerShipInsideTunnel = true;
                body->SetAwake(false);
            }
        }
    }
}