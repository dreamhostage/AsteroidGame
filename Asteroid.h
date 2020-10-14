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

class objects {
public:
    RenderWindow* window;
    Texture screenTexture;
    Texture banerTexture;
    Texture banerSettingsTexture;
    Texture banerPlayTexture;
    Texture banerAuthorTexture;
    Texture gameoverTexture;
    Sprite gameoverSprite;
    Sprite banerAuthorSprite;
    Sprite banerPlaySprite;
    Sprite banerSettingsSprite;
    Sprite banerSprite;
    Sprite screenSprite;
    SoundBuffer destroyingBuffer;
    SoundBuffer damageBuffer;
    SoundBuffer musicBuffer;
    SoundBuffer selectBuffer;
    Sound selectSound;
    Sound music;
    Sound damage;
    Sound destroying;
    Font font;
    int mainX;
    int mainY;
    int screenX;
    int screenY;
    int astSpawningCount;
    Vector2f ViewCenter;
    View view;
    View view2;
    bool fullscreen;
    bool GameOver;
    bool godmode;
    bool gameStarted;
    bool select;
    bool select2;
    uint32_t resettime;
    Vector2f globalCenter;
    Vector2u size;
    Vector2f position1;
    Vector2f position2;
    int clisansCount;
    int clissansSpawningDistance;

    objects();
    void setSettings(
        int inscreenX,
        int inscreenY,
        int inmainX,
        int inMainY,
        int num_ammo,
        int num_asteroids = 0);
    void startMenu();
};

class ship : public objects {
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
    bool finalexpl;
    bool aimSelected;
    bool freeze;
    bool startposition;
    std::string text;
    Vector2f mousePosition;
    sf::Vector2f vd;
    Vector2i pixelPos;

    ship();
    void addBullet(Vector2f& position, int rotation);
    void drawBullets();
    void Gameover();
    void draw();
};

class UPhealthIcon : public ship {
public:
    std::vector<Sprite> HPbase;
    Texture texture;

    UPhealthIcon();
    void draw();
    void add(Vector2f& position);
};

class UPammoIcon : public UPhealthIcon {
public:
    std::vector<Sprite> ammoBase;
    Texture ammoTexture;

    UPammoIcon();
    void draw();
    void add(Vector2f& position);
};

class ShieldIcon : public UPammoIcon {
public:
    std::vector<Sprite> shieldBase;
    Texture shieldIconTexture;

    ShieldIcon();
    void draw();
    void add(Vector2f& position);
};

class RocketIcons : public ShieldIcon {
public:
    std::vector<Sprite> rocketsIconsBase;
    Texture rocketIconTexture;

    RocketIcons();
    void draw();
    void add(Vector2f& position);
};

class autoaimIcon : public RocketIcons {
public:
    std::vector<Sprite> autoaimIconsBase;
    Texture autoaimIconTexture;

    autoaimIcon();
    void draw();
    void add(Vector2f& position);
};

class asteroidsArray {
public:
    Sprite sprite;
    bool type;
    int speed;
    double frame;
    bool explosion;
    float rotation;

    asteroidsArray();
};

class asteroids : public autoaimIcon {
public:
    std::vector<asteroidsArray> ast;
    Texture bigAstTexture;
    Texture smallAstTexture;
    Texture astExplTexture;
    Sprite astExplSprite;
    Vector2u size;
    Clock AsteroidsSpawningTime;

    asteroids();
    void add(Vector2f position, bool type, int speed, int rotation = 0);
    void physic();
    bool spawningChecking(Vector2f& first);
    void AsteroidSpawning();
    void draw();
};

class laser : public asteroids {
public:
    SoundBuffer laserShootBuffer;
    Sound laserShootSound;
    Texture laserTexture;
    Sprite laserSprite;
    Text laserText;
    int autoAimTime;

    laser();
    void draw();
};

class clissanShips {
public:
    Sprite sprite;
    Sprite LifeSprite;
    Vector2f pos;
    int health;
    double final;
    bool destroyed;
    uint32_t time1;
    uint32_t time2;
    bool selected;
    bool shoot;

    clissanShips();
};

class clissans : public laser {
public:
    Texture clissanshipTexture;
    Texture clissansbulletTexture;
    Texture frameTexture;
    Texture ClissansLifeTexture;
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
    std::vector<Sprite> clissansbulletsArray;
    std::vector<clissanShips> clisansShipsArray;
    bool side;
    int selNumb;
    int selectedCount;
    Vector2f bulletPos;
    Vector2f temp;

    clissans();
    void clissansSpauning();
    void addBullet(Vector2f& position, int rotation);
    void drawBullets();
    void makeShoot(int i);
    void draw();
};

class CosmoStation : public clissans {

public:
    CosmoStation();
    void draw();
    void moving();
    void laserScaning();
    void LifeBar();
    void BulletsChecking();
    void FrameMoving();
    void NeonBallMoving();
    void addBullet(Vector2f& position, int rotation);
    void Attack();
    void CSSpawn();
    void NBexplosion();

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
    Sprite CosmoStationSprite;
    Sprite LifeBarSprite;
    std::vector<Sprite> CSbulletsArray;
    std::vector<Sprite> NeonBallTale;
    Color CSCustomColor;
    Color NBCustomColor;
    SoundBuffer NBSoundBuffer;
    Sound NBSound;
    std::vector<Sprite>::iterator bit;
    Clock CSBulletsShootingTime;
    Clock NBexplClock;
    unsigned short int CSblaming;
    unsigned short int NBblaming;
    unsigned short int freezeTime;
    unsigned short int NBexplAnimframeX;
    unsigned short int NBexplAnimframeY;
    std::time_t freezeProgress;
    int NeonBallLife;
    bool alive;
    bool explSound;
    bool CSSelected;
    bool NeonBallAction;
    bool CSActivated;
    bool NBtaleWait;
    bool NBexplActivate;
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
    bool rocketExplosion;
    bool rocketInProgress;
    double frame;
    double shortestDistanse;
    int n;

    rockets();
    void draw();
};

class framework : public rockets {
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
