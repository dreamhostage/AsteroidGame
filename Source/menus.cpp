#include "Asteroid.h"

Menus::Menus()
{
    musicBuffer.loadFromFile("Sounds/Music.ogg");
    selectBuffer.loadFromFile("Sounds/select.ogg");
    banerTexture.loadFromFile("Images/baner.png");
    banerSettingsTexture.loadFromFile("Images/banerControl.png");
    banerPlayTexture.loadFromFile("Images/banerPlay.png");
    banerAuthorTexture.loadFromFile("Images/banerAuthor.png");
    gameoverTexture.loadFromFile("Images/GameOver.png");
    screenTexture.loadFromFile("Images/screen.png");
    banerTexture1.loadFromFile("Images/baner2.png");
    banerSettingsTexture1.loadFromFile("Images/banerControl2.png");
    banerPlayTexture1.loadFromFile("Images/banerPlay2.png");
    banerAuthorTexture1.loadFromFile("Images/banerAuthor2.png");

    screenSprite.setTexture(screenTexture);
    gameoverSprite.setTexture(gameoverTexture);
    selectSound.setBuffer(selectBuffer);
    banerAuthorSprite.setTexture(banerAuthorTexture);
    banerPlaySprite.setTexture(banerPlayTexture);
    banerSettingsSprite.setTexture(banerSettingsTexture);
    banerSprite.setTexture(banerTexture);
    music.setBuffer(musicBuffer);

    music.setLoop(true);
    music.setVolume(50);

    pause = true;
    selectButton = false;
    tapOnButton = false;
}

void Menus::startMenu()
{
    if (gameStarted)
    {
        banerAuthorSprite.setTexture(banerAuthorTexture1);
        banerPlaySprite.setTexture(banerPlayTexture1);
        banerSettingsSprite.setTexture(banerSettingsTexture1);
        banerSprite.setTexture(banerTexture1);
    }

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

void Menus::reset()
{
    ViewCenter.x = startGOview.getCenter().x;
    ViewCenter.y = startGOview.getCenter().y;
    view = startGOview;
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
    pause = true;
}
