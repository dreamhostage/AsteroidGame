#include "Asteroid.h"

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
    selectButton = false;

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
