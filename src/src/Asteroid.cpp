#include "Asteroid.hpp"

Asteroid::Asteroid () :
    sp_TexturesAsteroid (std::vector <sf::Texture> ()),
    randPositionX (100, 800),
    randPositionY (100, 600),
    randAngle (0, 360),
    randSpeed (10.2f, 122.f),
    randCount (2, 5),
    randColor (0, 255)
    {


    }

Asteroid &Asteroid::pushTextureFile (const std::string &fileName) {
    if (!texture.loadFromFile(fileName))
        throw std::runtime_error ("error loading file " + fileName);

    sp_TexturesAsteroid.push_back (texture);

    return *this;
}

Asteroid &Asteroid::setAsteroidCount (const std::size_t &s) {
    AsteroidCount = s;
    MiniAsteroidCount = s / 2;
    return *this;
}

Asteroid &Asteroid::setAsteroidSize (const float &s) {
    asteroidSize = s;
    return *this;
}


Asteroid &Asteroid::Rotate (const float &s) {
    rotate = s;
    return *this;
}

Asteroid &Asteroid::setDeltaTime (const float &dt) {
    deltaTime = dt;
    return *this;
}

float Asteroid::getRadius (const std::size_t &r) const {
    return Asteroids[r].getGlobalBounds ().width / 2;
}

sf::Vector2i Asteroid::SpawnRandom (const int &minX, const int &maxX,
                                    const int &minY, const int &maxY) {


                                        return sf::Vector2i (randPositionX.generate(),
                                                             randPositionY.generate());

                                 }

Asteroid &Asteroid::create () {


    sf::Vector2i explosionPoint (SpawnRandom(0, 800, 0, 600));
    sf::Vector2f explosionDir;


    for (std::size_t asteroidCount = 0; asteroidCount != AsteroidCount; ++asteroidCount) {
        int angle = randAngle.generate();
        int ind = randTexture.generate (0, sp_TexturesAsteroid.size () - 1);

        unsigned r = randColor.generate ();
        unsigned g = randColor.generate ();
        unsigned b = randColor.generate ();

        float speed = randSpeed.generate();

        sprite.setTexture (sp_TexturesAsteroid[ind]);
        sprite.setScale (asteroidSize, asteroidSize);

        sprite.setPosition (explosionPoint.x, explosionPoint.y);

        explosionDir.x = std::cos (angle * 3.14159265359 / 180);
        explosionDir.y = std::sin (angle * 3.14159265359 / 180);

        circleCollider.setFillColor (sf::Color::Transparent);
        circleCollider.setOutlineColor(sf::Color (r, g, b));
        circleCollider.setOutlineThickness(2);
        circleCollider.setRadius(45);
        circleCollider.setOrigin (-7, 9);

        circleCollider.setPosition(explosionPoint.x, explosionPoint.y);

        AsteroidSpeed.push_back (speed);
        colliders.push_back (circleCollider);
        Asteroids.push_back (sprite);
        AsteroidsDir.push_back (explosionDir);

    }

    return *this;
}

Asteroid &Asteroid::Draw (sf::RenderWindow &w) {

    for (std::size_t asteroidCount = 0; asteroidCount != Asteroids.size (); ++asteroidCount) {
        Asteroids[asteroidCount].setPosition (Asteroids[asteroidCount].getPosition ().x + ((AsteroidsDir[asteroidCount].x * deltaTime) * AsteroidSpeed[asteroidCount]),
                                              Asteroids[asteroidCount].getPosition ().y + ((AsteroidsDir[asteroidCount].y * deltaTime) * AsteroidSpeed[asteroidCount]));

        colliders[asteroidCount].setPosition (colliders[asteroidCount].getPosition ().x + ((AsteroidsDir[asteroidCount].x * deltaTime) * AsteroidSpeed[asteroidCount]),
                                              colliders[asteroidCount].getPosition ().y + ((AsteroidsDir[asteroidCount].y * deltaTime) * AsteroidSpeed[asteroidCount]));


        w.draw (Asteroids[asteroidCount]);
        w.draw (colliders[asteroidCount]);
    }

    for (std::size_t mAsteroidCount = 0; mAsteroidCount != miniAsteroids.size (); ++mAsteroidCount) {
        miniAsteroids[mAsteroidCount].setPosition (miniAsteroids[mAsteroidCount].getPosition ().x + ((miniAsteroidsDir[mAsteroidCount].x * deltaTime) * miniAsteroidSpeed[mAsteroidCount]),
                                                   miniAsteroids[mAsteroidCount].getPosition ().y + ((miniAsteroidsDir[mAsteroidCount].y * deltaTime) * miniAsteroidSpeed[mAsteroidCount]));

        miniColliders[mAsteroidCount].setPosition (miniColliders[mAsteroidCount].getPosition ().x + ((miniAsteroidsDir[mAsteroidCount].x * deltaTime) * miniAsteroidSpeed[mAsteroidCount]),
                                                   miniColliders[mAsteroidCount].getPosition ().y + ((miniAsteroidsDir[mAsteroidCount].y * deltaTime) * miniAsteroidSpeed[mAsteroidCount]));


        w.draw (miniAsteroids[mAsteroidCount]);
        w.draw (miniColliders[mAsteroidCount]);
    }

    return *this;
}

sf::Sprite &Asteroid::getAsteroid (const std::size_t &a) {
    return Asteroids[a];
}

sf::Sprite &Asteroid::getMiniAsteroid (const std::size_t &ma) {
    return miniAsteroids[ma];
}

sf::CircleShape &Asteroid::getCollider (const std::size_t &c, const std::string &s) {
    if (s == "asteroid")
      return colliders[c];
    else if (s == "miniasteroid")
      return miniColliders[c];

    throw std::runtime_error ("invalid type");
}

Asteroid &Asteroid::Explode (const std::size_t &i) {
    std::size_t cnt = randCount.generate ();

    for (std::size_t c = 0; c != cnt; ++c) {
        sf::Vector2f d;

        int a = randAngle.generate();
        float s = randSpeed.generate();

        unsigned r = randColor.generate();
        unsigned g = randColor.generate();
        unsigned b = randColor.generate();

        sprite.setPosition(Asteroids[i].getPosition ().x,
                           Asteroids[i].getPosition ().y);

        sprite.setScale (asteroidSize / 2,
                         asteroidSize / 2);

        d.x = std::cos (a * 3.14159265359 / 180);
        d.y = std::sin (a * 3.14159265359 / 180);

        circleCollider.setFillColor (sf::Color::Transparent);
        circleCollider.setOutlineColor(sf::Color (r, g, b));
        circleCollider.setOutlineThickness(2);
        circleCollider.setRadius(45);
        circleCollider.setOrigin (-7, 9);
        circleCollider.setRadius(45 / 2);

        circleCollider.setPosition(Asteroids[i].getPosition ().x - 8,
                                   Asteroids[i].getPosition ().y + 9);

        miniAsteroids.push_back (sprite);
        miniAsteroidsDir.push_back (d);
        miniAsteroidSpeed.push_back (s);
        miniColliders.push_back (circleCollider);


    }

    return *this;
}

Asteroid &Asteroid::remove (const std::size_t &i, const std::string &t) {

    if (t == "asteroid") {
        Asteroids.erase (Asteroids.begin () + i);
        AsteroidsDir.erase (AsteroidsDir.begin () + i);
        AsteroidSpeed.erase (AsteroidSpeed.begin () + i);
        colliders.erase (colliders.begin () + i);
        --AsteroidCount;
    } else if (t == "miniasteroid") {
        miniAsteroids.erase (miniAsteroids.begin () + i);
        miniAsteroidsDir.erase (miniAsteroidsDir.begin () + i);
        miniAsteroidSpeed.erase (miniAsteroidSpeed.begin () + i);
        miniColliders.erase (miniColliders.begin () + i);
        --MiniAsteroidCount;
    }
    else
        throw std::runtime_error ("invalid type");

    return *this;
}

unsigned int Asteroid::getAsteroidCount (const std::string &t) const {
    if (t == "asteroid")
        return Asteroids.size ();
    else if (t == "miniasteroid")
        return miniAsteroids.size ();

    return 0;
}

Asteroid &Asteroid::Clear () {
    sp_TexturesAsteroid.clear ();

    Asteroids.clear ();
    AsteroidsDir.clear ();
    colliders.clear ();

    randomHitstatus.clear ();

    miniAsteroids.clear ();
    miniAsteroidsDir.clear ();
    miniColliders.clear();

    AsteroidSpeed.clear ();
    miniAsteroidSpeed.clear ();

    return *this;

}





