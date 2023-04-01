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

    exitTexture.loadFromFile("Images/exit.png");
    exitSptite.setTexture(exitTexture);

    exitInfoTexture.loadFromFile("Images/exitInfo.png");
    exitInfoSprite.setTexture(exitInfoTexture);

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

    selectButton = false;
    tapOnButton = false;
    resumePlay = false;
}

void Menus::startMenu()
{
    if (gameStarted)
    {
        if (resumePlay)
        {
            banerAuthorSprite.setTexture(banerAuthorTexture1);
            banerPlaySprite.setTexture(banerPlayTexture1);
            banerSettingsSprite.setTexture(banerSettingsTexture1);
            banerSprite.setTexture(banerTexture1);
            resumePlay = false;
        }
    }
    else
    {
        if (!resumePlay)
        {
            banerAuthorSprite.setTexture(banerAuthorTexture);
            banerPlaySprite.setTexture(banerPlayTexture);
            banerSettingsSprite.setTexture(banerSettingsTexture);
            banerSprite.setTexture(banerTexture);
            resumePlay = true;
        }
    }

    if (bIsGamePaused) {
        if (!tapOnButton) {
            if (banerSprite.getPosition().y
                > ViewCenter.y + ((screenX * screenY * 300) / (VideoMode::getDesktopMode().width * VideoMode::getDesktopMode().height))) {
                banerSprite.setPosition(
                    banerSprite.getPosition().x, banerSprite.getPosition().y - 1);
                exitSptite.setPosition(banerSprite.getPosition().x + screenX / 2 - exitTexture.getSize().x / 2, banerSprite.getPosition().y);
                window->draw(banerSprite);
                window->draw(exitSptite);
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
                    window->draw(exitSptite);
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
                    window->draw(exitSptite);
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
                    window->draw(exitSptite);
                    window->draw(banerAuthorSprite);
                } else if (
                    position1.x > exitSptite.getPosition().x + 180
                    && position1.x < exitSptite.getPosition().x + 380
                    && position1.y > exitSptite.getPosition().y + 100
                    && position1.y < exitSptite.getPosition().y + 170) {
                    if (!selectButton) {
                        selectSound.play();
                        selectButton = true;
                    }
                    exitInfoSprite.setPosition(exitSptite.getPosition());
                    window->draw(banerSprite);
                    window->draw(exitInfoSprite);
                    if (Mouse::isButtonPressed(Mouse::Left)) {
                        exitGame = true;
                    }
                }
                else {
                    selectButton = false;
                    window->draw(banerSprite);
                    window->draw(exitSptite);
                }
            }
        } else {
            if (banerSprite.getPosition().y > ViewCenter.y - 750) {
                banerSprite.setPosition(
                    banerSprite.getPosition().x, banerSprite.getPosition().y - 10);
                exitSptite.setPosition(banerSprite.getPosition().x + screenX / 2 - exitTexture.getSize().x / 2, banerSprite.getPosition().y);
                window->draw(banerSprite);
                window->draw(exitSptite);
            } else {
                gameStarted = true;
                bIsGamePaused = false;
            }
        }
    }
}

void Menus::reset()
{
    banerAuthorSprite.setPosition(
        ViewCenter.x, ViewCenter.y + ((screenX * screenY * 300) / (VideoMode::getDesktopMode().width * VideoMode::getDesktopMode().height)));
    banerPlaySprite.setPosition(
        ViewCenter.x, ViewCenter.y + ((screenX * screenY * 300) / (VideoMode::getDesktopMode().width * VideoMode::getDesktopMode().height)));
    banerSettingsSprite.setPosition(
        ViewCenter.x, ViewCenter.y + ((screenX * screenY * 300) / (VideoMode::getDesktopMode().width * VideoMode::getDesktopMode().height)));
    banerSprite.setPosition(
        ViewCenter.x, ViewCenter.y + ((screenX * screenY * 600) / (VideoMode::getDesktopMode().width * VideoMode::getDesktopMode().height)));
    gameoverSprite.setPosition(view.getCenter().x, view.getCenter().y - 700);

    tapOnButton = false;
    bIsGamePaused = true;
}
