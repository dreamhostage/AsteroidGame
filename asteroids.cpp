#pragma once
#include "Asteroid.h"

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
                                                ImprovementsBase::add(
                                                    position, ImprovementsTypes::HPImprovement);
                                            }

                                            if (rnd2 == 1) {
                                                ImprovementsBase::add(
                                                    position,
                                                    ImprovementsTypes::autoAimImprovement);
                                            }
                                            if (rnd2 == 2) {
                                                ImprovementsBase::add(
                                                    position,
                                                    ImprovementsTypes::rocketsImprovement);
                                            }
                                            if (rnd2 == 3) {
                                                ImprovementsBase::add(
                                                    position, ImprovementsTypes::ammoImprovement);
                                            }
                                            if (rnd2 == 4) {
                                                ImprovementsBase::add(
                                                    position, ImprovementsTypes::shieldImprovement);
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
