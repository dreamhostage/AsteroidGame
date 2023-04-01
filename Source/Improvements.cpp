#include "Asteroid.h"

ImprovementsBase::ImprovementsBase()
{
    HPImprTexture.loadFromFile("Images/HP.png");
    HPImprSprite.setTexture(HPImprTexture);
    size = HPImprTexture.getSize();
    HPImprSprite.setOrigin(size.x / 2, size.y / 2);

    ammoImprTexture.loadFromFile("Images/ammo.png");
    ammoImprSprite.setTexture(ammoImprTexture);
    size = ammoImprTexture.getSize();
    ammoImprSprite.setOrigin(size.x / 2, size.y / 2);

    shieldImprTexture.loadFromFile("Images/shieldicon.png");
    shieldImprSprite.setTexture(shieldImprTexture);
    size = shieldImprTexture.getSize();
    shieldImprSprite.setOrigin(size.x / 2, size.y / 2);

    rocketsImprTexture.loadFromFile("Images/rockets.png");
    rocketsImprSprite.setTexture(rocketsImprTexture);
    size = rocketsImprTexture.getSize();
    rocketsImprSprite.setOrigin(size.x / 2, size.y / 2);

    autoAimImprTexture.loadFromFile("Images/autoshoot.png");
    autoAimImprSprite.setTexture(autoAimImprTexture);
    size = autoAimImprTexture.getSize();
    autoAimImprSprite.setOrigin(size.x / 2, size.y / 2);
}

void ImprovementsBase::Tick()
{
    for (int i = 0; i < ImprovementsArray.size(); ++i) {
        bool destroyed = false;
        position1 = ShipSprite.getPosition();
        position2 = ImprovementsArray[i].ImprovementSprite.getPosition();
        distanse = sqrt(
            (position1.x - position2.x) * (position1.x - position2.x)
            + (position1.y - position2.y) * (position1.y - position2.y));
        if (!GameOver) {
            if (distanse < 50) {
                ShipImprovementSound.play();

                if (ImprovementsArray[i].type == ImprovementsTypes::ammoImprovement) {
                    bulletsSize += 100;
                } else if (ImprovementsArray[i].type == ImprovementsTypes::HPImprovement) {
                    if (health < 100) {
                        health += 50;
                        LifeBar.setSize(sf::Vector2f(LifeBar.getSize().x + (screenX * 0.5), LifeBar.getSize().y));
                        LifeBar.setOrigin(LifeBar.getSize().x / 2, LifeBar.getSize().y / 2);
                        if (health > 100)
                        {
                            health = 100;
                            ship::LifeBar.setSize(sf::Vector2f(screenX - 50, 10));
                        }
                    }
                } else if (ImprovementsArray[i].type == ImprovementsTypes::shieldImprovement) {
                    shieldCount += 3;
                } else if (ImprovementsArray[i].type == ImprovementsTypes::rocketsImprovement) {
                    rocketsCount += 5;
                } else if (ImprovementsArray[i].type == ImprovementsTypes::autoAimImprovement) {
                    laserShootCount += 5;
                }

                std::vector<Improvements>::iterator it = ImprovementsArray.begin();
                ImprovementsArray.erase(it + i);
                destroyed = true;
            }
        }
        if (!destroyed)
            window->draw(ImprovementsArray[i].ImprovementSprite);
    }
}

void ImprovementsBase::add(Vector2f& position, ImprovementsTypes type)
{
    Improvements temp;

    if (type == ImprovementsTypes::HPImprovement) {
        temp.ImprovementSprite = HPImprSprite;
    } else if (type == ImprovementsTypes::ammoImprovement) {
        temp.ImprovementSprite = ammoImprSprite;
    } else if (type == ImprovementsTypes::shieldImprovement) {
        temp.ImprovementSprite = shieldImprSprite;
    } else if (type == ImprovementsTypes::autoAimImprovement) {
        temp.ImprovementSprite = autoAimImprSprite;
    } else if (type == ImprovementsTypes::rocketsImprovement) {
        temp.ImprovementSprite = rocketsImprSprite;
    }

    temp.ImprovementSprite.setPosition(position);
    temp.type = type;
    ImprovementsArray.push_back(std::move(temp));
}

void ImprovementsBase::reset()
{
    auto iit = ImprovementsArray.begin();
    while (iit != ImprovementsArray.end()) {
        iit = ImprovementsArray.erase(iit);
    }
}
