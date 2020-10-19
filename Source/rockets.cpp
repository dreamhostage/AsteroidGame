#include "Asteroid.h"

rockets::rockets()
{
    rocketTexture.loadFromFile("Images/Rocket.png");
    rocketBuffer.loadFromFile("Sounds/rocket.ogg");
    rockExplTexture.loadFromFile("Images/asteroidexplosion.png");
    font.loadFromFile("Images/18949.ttf");
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
        drawRocketExplosion();
    }
    if (rocketsCount) {

        drawRocketsText();

        if (!rocketInProgress) {
            if (Mouse::isButtonPressed(Mouse::Right)) {
                launchRocket();
            }
        } else {
            window->draw(rocketSprite);
            if (!aimSelected && !CSSelected) {
                AimNearestAsteroid();
            } else if (aimSelected) {
                aimSelectedClissanShip();
            } else if (CSSelected) {
                aimCosmoStation();
            }
        }
    }
}

void rockets::drawRocketExplosion()
{
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

void rockets::drawRocketsText()
{
    rocketsText.setPosition(ViewCenter.x - screenX / 2 + 300, ViewCenter.y - screenY / 2 + 50);
    text = "ROCKETS: ";
    text += std::to_string(rocketsCount);
    rocketsText.setString(text);
    window->draw(rocketsText);
}

void rockets::launchRocket()
{
    if (!GameOver) {
        rocketSound.play();
        rocketSprite.setPosition(ShipSprite.getPosition());
        rocketInProgress = true;
    }
}

void rockets::AimNearestAsteroid()
{
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
}

void rockets::aimSelectedClissanShip()
{
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
}

void rockets::aimCosmoStation()
{
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
        if (CSLifeBarSprite.getScale().x > 0.005) {
            CSLifeBarSprite.setScale(
                CSLifeBarSprite.getScale().x - 0.025, CSLifeBarSprite.getScale().y);
        } else {
            CSalive = false;
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
