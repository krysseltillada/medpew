#ifndef SHIP_HEADER
#define SHIP_HEADER

#include "RandomGenerator.hpp"

#include <SFML/Graphics.hpp>

#include <iostream>

#include <memory>

#include <vector>

#include <stdexcept>

#include <typeinfo>

class Ship {
public:
    Ship ();

    operator sf::Sprite & ();

    Ship &loadShipTexture (const std::string &);

    Ship &Fire ();

    Ship &setPosition (const float &, const float &);
    Ship &setSize (const float &);

    Ship &setBulletPosition (const float &, const float &, const std::size_t &i);

    Ship &removeBullet (const std::size_t &);

    Ship &setAngle (const int &);

    Ship &Clear ();

    const sf::Vector2f &getPosition () const;
    const sf::Vector2f &getDirection () const;

    const int &getAngle () const;

    const sf::Vector2f &getBulletPosition (const std::size_t &) const;
    const sf::Vector2f &getBulletDirection (const std::size_t &) const;
    const sf::CircleShape &getBullets (const std::size_t &) const;

    const std::size_t &getBulletSize () const;

    float getShipRadius () const {
        return sp_ShipSprite->getGlobalBounds ().width / 2;
    }

    sf::Sprite getShip () {
        return *sp_ShipSprite;
    }

private:

    std::unique_ptr <sf::Texture> sp_ShipTexture;
    std::unique_ptr <sf::Sprite> sp_ShipSprite;

    std::unique_ptr <std::vector <sf::Vector2f> > bulletPosition;
    std::unique_ptr <std::vector <sf::Vector2f> > bulletDirection;

    std::unique_ptr <std::vector <sf::CircleShape> > bullets;

    sf::Vector2f Position;
    sf::Vector2f Direction;

    std::size_t bulletSize;

    int Angle;

    RandomGenerator r;


};


#endif // SHIP_HEADER
