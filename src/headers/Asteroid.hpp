#ifndef ASTEROID_HEADER
#define ASTEROID_HEADER

#include "RandomGenerator.hpp"

#include <SFML/Graphics.hpp>

#include <vector>

#include <memory>

#include <iostream>

#include <stdexcept>

class Asteroid {
public:
    Asteroid ();

    Asteroid &pushTextureFile (const std::string &);
    Asteroid &setAsteroidCount (const std::size_t &);
    Asteroid &setAsteroidSize (const float &);
    Asteroid &Rotate (const float &);
    Asteroid &setDeltaTime (const float &);
    Asteroid &create ();
    Asteroid &Explode (const std::size_t &);
    Asteroid &remove (const std::size_t &, const std::string &);
    Asteroid &Clear ();

    float getRadius (const std::size_t &) const;

    Asteroid &Draw (sf::RenderWindow &);

    sf::Sprite &getAsteroid (const std::size_t &);
    sf::Sprite &getMiniAsteroid (const std::size_t &);

    sf::CircleShape &getCollider (const std::size_t &, const std::string &);

    unsigned int getAsteroidCount (const std::string &) const;

private:
    sf::Vector2i SpawnRandom (const int &, const int &,
                              const int &, const int &);

    sf::Texture texture;
    sf::Sprite sprite;

    std::vector <sf::Texture> sp_TexturesAsteroid;

    std::vector <sf::Sprite> Asteroids;
    std::vector <sf::Vector2f> AsteroidsDir;
    std::vector <sf::CircleShape> colliders;

    std::vector <int> randomHitstatus;

    std::vector <sf::Sprite> miniAsteroids;
    std::vector <sf::Vector2f> miniAsteroidsDir;
    std::vector <sf::CircleShape> miniColliders;

    std::vector <float> AsteroidSpeed;
    std::vector <float> miniAsteroidSpeed;

    sf::CircleShape circleCollider;

    RandomGenerator randPositionX;
    RandomGenerator randPositionY;
    RandomGenerator randAngle;
    RandomGenerator randTexture;
    RandomGenerator randSpeed;
    RandomGenerator randCount;
    RandomGenerator randHit;
    RandomGenerator randColor;

    unsigned int AsteroidCount;
    unsigned int MiniAsteroidCount;

    float rotate;
    float asteroidSize;
    float deltaTime;
};





#endif // ASTEROID_HEADER
