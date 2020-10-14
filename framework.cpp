#pragma once
#include "Asteroid.h"

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
        ImprovementsBase::draw();
        rockets::draw();
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
