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
    setSettings(x, y, mapX, mapY, num_ammo, num_asteroids);
}
void framework::setSettings(
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

    size = banerTexture.getSize();
    banerSprite.setOrigin(size.x / 2, size.y / 2);
    banerSprite.setPosition(
        ViewCenter.x, ViewCenter.y + ((screenX * screenY * 600) / (1920 * 1080)));

    banerSettingsTexture.getSize();
    banerSettingsSprite.setOrigin(size.x / 2, size.y / 2);
    banerSettingsSprite.setPosition(
        ViewCenter.x, ViewCenter.y + ((screenX * screenY * 300) / (1920 * 1080)));

    banerPlayTexture.getSize();
    banerPlaySprite.setOrigin(size.x / 2, size.y / 2);
    banerPlaySprite.setPosition(
        ViewCenter.x, ViewCenter.y + ((screenX * screenY * 300) / (1920 * 1080)));

    banerAuthorTexture.getSize();
    banerAuthorSprite.setOrigin(size.x / 2, size.y / 2);
    banerAuthorSprite.setPosition(
        ViewCenter.x, ViewCenter.y + ((screenX * screenY * 300) / (1920 * 1080)));

    size = gameoverTexture.getSize();
    gameoverSprite.setOrigin(size.x / 2, size.y / 2);
    gameoverSprite.setPosition(view.getCenter().x, view.getCenter().y - 700);

    ship::LifeBar.setSize(sf::Vector2f(screenX - 50, 10));
    ship::LifeBar.setOrigin((screenX - 50) / 2, 5);
    ship::LifeBar.setFillColor(sf::Color(0, 121, 0, 180));

    globalCenter.x = mainX / 2;
    globalCenter.y = mainY / 2;

    this->godmode = godmode;
    // this->godmode = true;
    ship::ShipSprite.setPosition(mainX / 2, mainY / 2);

    CSSpawn();
}

void framework::ResetGame()
{
    Menus::reset();
    CosmoStation::reset();
    ImprovementsBase::reset();
    ship::reset();
    GlobalVariables::reset();
    clissans::reset();
    asteroids::reset();
    tunnel::reset();

    music.stop();
}

void framework::Gameover()
{
    if (GameOver) {
        if (!finalexpl) {
            finalexpl = true;
            explosionSound.play();
        }

        position1 = ShipSprite.getPosition();
        angle = ShipSprite.getRotation() - 0.5;
        shipExplSprite.setPosition(position1);
        shipTexture.loadFromFile("Images/destroyedship.png");
        if (shipExplFrame < 65) {
            shipExplSprite.setScale(2, 2);

            shipExplSprite.setOrigin(96, 96);
            if (shipExplTime.getElapsedTime().asMilliseconds() > 20) {
                shipExplSprite.setTextureRect(IntRect(shipExplFrame * 192, 0, 192, 192));
                shipExplSprite.setPosition(ShipSprite.getPosition());
                ++shipExplFrame;
                shipExplTime.restart();
            }
            window->draw(shipExplSprite);
        }
        ShipSprite.setPosition(position1.x - 1, position1.y - 1);
        ShipSprite.setRotation(angle);

        if (!startposition) {
            startposition = true;
            gameoverSprite.setPosition(view.getCenter().x, view.getCenter().y - screenY / 2);
            finalPointsText.setPosition(view.getCenter().x - 30, view.getCenter().y - 40);
            rang.setPosition(view.getCenter().x - 280, view.getCenter().y + 40);
            PointsSpeedRaising.restart();
            startGOview = view;
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

            if (PointsSpeedRaising.getElapsedTime().asSeconds() < points / 100 + 5) {
                window->draw(finalPointsText);
            } else {
                position1 = startGOview.getCenter();

                distanse = sqrt(
                    (position1.x - globalCenter.x) * (position1.x - globalCenter.x)
                    + (position1.y - globalCenter.y) * (position1.y - globalCenter.y));
                if (distanse > 10) {
                    vd = globalCenter - position1;
                    angle = std::atan2(vd.y, vd.x) * 180.f / M_PI + 90;

                    angle -= (angle - 90) * 2;

                    startGOview.setCenter(
                        position1.x + 20 * sin((angle)*M_PI / 180),
                        position1.y + 20 * cos((angle)*M_PI / 180));

                    window->setView(startGOview);
                } else {
                    ResetGame();
                }
            }
        }

        window->draw(gameoverSprite);
    }
}

void framework::run()
{
    while (window->isOpen()) {
        Event event;
        while (window->pollEvent(event)) {
            if (event.type == Event::Closed)
                window->close();
        }

        if (Keyboard::isKeyPressed(Keyboard::F2)) {
            if (fullscreen) {
                window->create(VideoMode(screenX, screenY), "Asteroids");
                fullscreen = false;
                window->setFramerateLimit(120);
                window->setView(view);
                window->setMouseCursorVisible(false);
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            if (!pause) {
                pause = true;
                banerAuthorSprite.setPosition(
                    ViewCenter.x, ViewCenter.y + ((screenX * screenY * 300) / (1920 * 1080)));
                banerPlaySprite.setPosition(
                    ViewCenter.x, ViewCenter.y + ((screenX * screenY * 300) / (1920 * 1080)));
                banerSettingsSprite.setPosition(
                    ViewCenter.x, ViewCenter.y + ((screenX * screenY * 300) / (1920 * 1080)));
                banerSprite.setPosition(
                    ViewCenter.x, ViewCenter.y + ((screenX * screenY * 600) / (1920 * 1080)));
                tapOnButton = false;
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
        if (!pause) {
            ImprovementsBase::draw();
            if (!isInsideTunnel)
            {
                rockets::draw();
                laser::draw();
            }
            asteroids::draw();
            ship::draw();
            clissans::draw();
            CosmoStation::draw();
            smoke::draw(*window);
            words::draw();
            Gameover();
        }
        if (tunnelActivated)
        {
            tunnel::draw();
        }
        Menus::startMenu();
        if (!isInsideTunnel)
        {
            window->draw(cursorSprite);
        }
        else
        {
            if (portalSize > screenX / 2)
            {
                spawningPosition = window->mapPixelToCoords(Mouse::getPosition(*window));
                pixelCount = 7000;
                pixelspeed = 17;
                centerSize = 150;

                while (pixels.size() < pixelCount)
                {
                    arbiteAngle = rand() % 360;
                    newPixelPos.x = spawningPosition.x + (portalSize * 2) * cos((arbiteAngle)*M_PI / 180);
                    newPixelPos.y = spawningPosition.y + (portalSize * 2) * sin((arbiteAngle)*M_PI / 180);
                    pixelSprite.setPosition(newPixelPos);
                    pixels.push_back(pixelSprite);
                }
            }
        }

        window->display();
        window->clear();
    }
}
