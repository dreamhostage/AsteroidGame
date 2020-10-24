#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <math.h>
#include <stdio.h>

#include <iostream>
#include <iterator>
#include <list>
#include <queue>
#include <vector>

#define M_PI 3.14159265358979323846

using namespace sf;

enum class ImprovementsTypes {
    HPImprovement,
    ammoImprovement,
    shieldImprovement,
    rocketsImprovement,
    autoAimImprovement
};

class GlobalVariables {
public:
    RenderWindow* window;
    int mainX;
    int mainY;
    int screenX;
    int screenY;
    Vector2f ViewCenter;
    bool fullscreen;
    bool GameOver;
    bool godmode;
    bool gameStarted;
    View view;
    Vector2f globalCenter;
    Vector2u size;
    Vector2f position1;
    Vector2f position2;
    double angle;
    Vector2f temp;

    GlobalVariables();
    void reset();
};

class smoke : public GlobalVariables {

    Texture particleTexture;
    Sprite particleSprite;
    Vector2f position;
    float angle;
    Vector2f np;

public:
    struct particle {

        Sprite sprite;
        int lifetime = 1000;
        int speed = 2;
        Clock time;
        Vector2f position;
        float angle;
        Color color;
        double f;

        particle(Sprite _sprite, float _angle, Vector2f _position);
        void move();
        double rnd(double fMin, double fMax);
    };

    void add(Sprite sprite);
    void draw(RenderWindow& window);
    smoke();

    std::vector<particle> pbase;
};

class ship : public smoke {

    void addBullet(Vector2f& position, int rotation);
    void drawBullets();
    void moveShip();
    void makeShoot();
    void shipPerformance();

public:
    Texture shipTexture;
    Texture bulletTexture;
    Texture shieldResistTexture;
    Texture shipExplTexture;
    Texture cursorTexture;
    Sprite cursorSprite;
    Sprite shipExplSprite;
    Sprite shieldResistSprite;
    Sprite bulletSprite;
    Sprite ShipSprite;
    SoundBuffer ShipImprovementSoundBuffer;
    SoundBuffer shootBuffer;
    SoundBuffer shieldSoundBuffer;
    SoundBuffer explosionSoundBuffer;
    SoundBuffer bulletDamageBuffer;
    SoundBuffer destroyingBuffer;
    SoundBuffer damageBuffer;
    Sound damage;
    Sound destroying;
    Sound ShipImprovementSound;
    Sound bulletDamageSound;
    Sound explosionSound;
    Sound shieldSound;
    Sound shot;
    std::vector<Sprite> bulletsArray;
    Text HPtext;
    Text bulletsSizeText;
    Text pointsText;
    Text shieldText;
    Text finalPointsText;
    Text rang;
    Clock ShootingTime;
    Clock ShootingTimeNoBullets;
    Clock shipExplTime;
    Font font;
    int health;
    int bulletsSize;
    int shieldCount;
    int rocketsCount;
    int laserShootCount;
    int points;
    int shipRotation;
    int finalpoints;
    double shipSpeed;
    double bulletSpeed;
    double angle;
    double distanse;
    int shipExplFrame;
    bool finalexpl;
    bool aimSelected;
    bool freeze;
    bool startposition;
    std::string text;
    Vector2f mousePosition;
    sf::Vector2f vd;
    Vector2i pixelPos;

    ship();
    void draw();
    void reset();
};

class ImprovementsBase : public ship {

    struct Improvements {
        ImprovementsTypes type;
        Sprite ImprovementSprite;
    };
    std::vector<Improvements> ImprovementsArray;
    Texture HPImprTexture;
    Texture ammoImprTexture;
    Texture shieldImprTexture;
    Texture rocketsImprTexture;
    Texture autoAimImprTexture;
    Sprite HPImprSprite;
    Sprite ammoImprSprite;
    Sprite shieldImprSprite;
    Sprite rocketsImprSprite;
    Sprite autoAimImprSprite;

public:
    ImprovementsBase();
    void draw();
    void add(Vector2f& position, ImprovementsTypes type);
    void reset();
};

class asteroids : public ImprovementsBase {

public:
    struct asteroidsArray {
        Sprite sprite;
        bool type;
        int speed;
        double frame = 0;
        bool explosion = false;
        float rotation;
    };

    std::vector<asteroidsArray> ast;
    Texture bigAstTexture;
    Texture smallAstTexture;
    Texture astExplTexture;
    Sprite astExplSprite;
    Vector2u size;
    Clock AsteroidsSpawningTime;
    int astSpawningCount;

    asteroids();
    void draw();
    void reset();

private:
    std::vector<asteroidsArray>::iterator it;
    std::vector<Sprite>::iterator bit;
    bool destroyed;
    double distanseShip;
    Vector2f shipCoordinates;
    Vector2f currentPosition;

    void add(Vector2f position, bool type, int speed, int rotation = 0);
    void physic();
    bool spawningChecking(Vector2f& first);
    void AsteroidSpawning();
    void asteroidExplosion(asteroidsArray& asteroid);
    void shipDistanceMonitoring(asteroidsArray& asteroid);
    void bulletsDistanceMonitoring(asteroidsArray& asteroid);
    void generateImprovement(Vector2f& position);
};

class laser : public asteroids {
public:
    SoundBuffer laserShootBuffer;
    Sound laserShootSound;
    Texture laserTexture;
    Sprite laserSprite;
    Text laserText;
    Font font;
    int autoAimTime;

    laser();
    void draw();
};

class clissans : public laser {
public:
    struct clissanShips {
        Sprite sprite;
        Sprite LifeSprite;
        Vector2f pos;
        Clock shootingTime;
        int health = 100;
        double final = 0;
        bool destroyed = false;
        bool selected = false;
        bool shoot = false;
        unsigned short int ClissanShipBlaming = 0;
    };

    Texture clissanshipTexture;
    Texture clissansbulletTexture;
    Texture frameTexture;
    Texture ClissansLifeTexture;
    Texture ClissanShipExplTexture;
    Sprite ClissanShipExplSprite;
    Sprite ClissansLifeSprite;
    Sprite frameSprite;
    Sprite clissansbulletSprite;
    Sprite clissanShipSprite;
    SoundBuffer clissansshootBuffer;
    SoundBuffer clissansexplosionSoundBuffer;
    SoundBuffer laserinBuffer;
    Sound clissansexplosionSound;
    Sound laserinSound;
    Sound clissansshot;
    Color ClissanShipCustomColor;
    std::vector<Sprite> clissansbulletsArray;
    std::vector<clissanShips> clisansShipsArray;
    bool side;
    int selNumb;
    int selectedCount;
    int clissansSpawningDistance;
    int clisansCount;
    Vector2f bulletPos;
    clissanShips* selectedClissansShip;

    clissans();
    void draw();
    void reset();

protected:
    void clissansSpauning();
    void addBullet(Vector2f& position, int rotation);
    void drawBullets();
    void makeShootIfClose(clissanShips& ClissansShip);
    void ClissanShipExplosion(clissanShips& ClissansShip);
    void sellectClissanShip(clissanShips& ClissansShip);
    void ClissanShipBulletsChecking(clissanShips& ClissansShip);
    void ClissanShipMovingBehavior(clissanShips& ClissansShip);
};

class CosmoStation : public clissans {

public:
    CosmoStation();
    void CSSpawn();
    void draw();
    void reset();
    bool explSound;
    bool CSalive;

    unsigned short int CSblaming;
    bool CSSelected;
    Sprite CosmoStationSprite;
    Sprite CSLifeBarSprite;

    // private:
    Texture CosmoStationTexture;
    Texture LifeBarTexture;
    Texture CSFrameTexture;
    Texture NeonBallTexture;
    Texture NeonBallTaleTexture;
    Texture NBexplTexture;

    Sprite NBexplSprite;
    Sprite NeonBallTaleSprite;
    Sprite NeonBallSprite;
    Sprite CSFrameSprite;

    std::vector<Sprite> CSbulletsArray;
    std::vector<Sprite> NeonBallTale;

    Color CSCustomColor;
    Color NBCustomColor;

    SoundBuffer NBSoundBuffer;
    SoundBuffer NBexplosionBuffer;

    Sound NBSound;
    Sound NBExplosionSound;

    std::vector<Sprite>::iterator bit;
    Clock CSBulletsShootingTime;
    Clock NBexplClock;
    unsigned short int NBblaming;
    unsigned short int freezeTime;
    unsigned short int NBexplAnimframeX;
    unsigned short int NBexplAnimframeY;
    Clock freezeProgress;
    int NeonBallLife;
    bool NeonBallAction;
    bool CSActivated;
    bool NBtaleWait;
    bool NBexplActivate;

    void moving();
    void laserScaning();
    void LifeBar();
    void BulletsChecking();
    void FrameMoving();
    void NeonBallMoving();
    void addBullet(Vector2f& position, int rotation);
    void Attack();
    void NBexplosion();
};

class rockets : public CosmoStation {
public:
    Texture rocketTexture;
    Texture rockExplTexture;
    Sprite rockExplSprite;
    Sprite rocketSprite;
    SoundBuffer rocketBuffer;
    Sound rocketSound;
    Text rocketsText;
    Font font;
    bool rocketExplosion;
    bool rocketInProgress;
    double frame;
    double shortestDistanse;
    int n;

    rockets();
    void draw();

private:
    void drawRocketExplosion();
    void drawRocketsText();
    void launchRocket();
    void AimNearestAsteroid();
    void aimSelectedClissanShip();
    void aimCosmoStation();
};

class Menus : public rockets {

public:
    Menus();
    void startMenu();
    void reset();

    Texture banerTexture;
    Texture banerSettingsTexture;
    Texture banerPlayTexture;
    Texture banerAuthorTexture;
    Texture gameoverTexture;
    Texture screenTexture;
    Sprite screenSprite;
    Sprite gameoverSprite;
    Sprite banerAuthorSprite;
    Sprite banerPlaySprite;
    Sprite banerSettingsSprite;
    Sprite banerSprite;
    SoundBuffer selectBuffer;
    SoundBuffer musicBuffer;
    Sound music;
    Sound selectSound;
    View startGOview;
    bool selectButton;
    bool tapOnButton;
    bool pause;
    Clock PointsSpeedRaising;
};

class framework : public Menus {

    void Gameover();
    void setSettings(
        int inscreenX, int inscreenY, int inmainX, int inMainY, int num_ammo, int num_asteroids);
    void ResetGame();

public:
    ~framework();
    framework(
        unsigned int x = 0,
        unsigned int y = 0,
        unsigned int num_asteroids = 0,
        unsigned int num_ammo = 0,
        unsigned int godmode = 0,
        int mapX = 0,
        int mapY = 0);
    void run();
};
