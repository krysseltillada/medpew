#include "Ship.hpp"

    Ship::Ship () :
        sp_ShipTexture (new sf::Texture ()),
        sp_ShipSprite (new sf::Sprite ()),
        bulletPosition (new std::vector <sf::Vector2f> ()),
        bulletDirection (new std::vector <sf::Vector2f> ()),
        bullets (new std::vector <sf::CircleShape> ()),
        bulletSize (0) {
            sp_ShipSprite->setOrigin (90, 90);
        }

    Ship &Ship::loadShipTexture (const std::string &fileName) {
        if (!sp_ShipTexture->loadFromFile (fileName))
            throw std::runtime_error ("error loading filename: " + fileName);

        sp_ShipSprite->setTexture (*sp_ShipTexture);

        return *this;
    }

    Ship::operator sf::Sprite &  () {
        return *sp_ShipSprite;
    }

    Ship &Ship::Fire () {

        sf::Vector2f bd;
        sf::CircleShape b (2);

        bd.x = std::cos (Angle * 3.14159265359f / 180);
        bd.y = std::sin (Angle * 3.14159265359f / 180);


        b.setFillColor (sf::Color (233,
                                   89,
                                   30));

        b.setPosition (Position.x + 1,
                       Position.y - 2);


        bulletPosition->push_back (b.getPosition ());
        bulletDirection->push_back (bd);
        bullets->push_back (b);

        bulletSize = bullets->size ();


        return *this;
    }

    Ship &Ship::setPosition (const float &sx, const float &sy) {
        Position.x = sx;
        Position.y = sy;

        sp_ShipSprite->setPosition (Position.x, Position.y);

        return *this;
    }

    Ship &Ship::setSize (const float &s) {
        sp_ShipSprite->setScale (s, s);
        return *this;
    }

    Ship &Ship::setAngle (const int &a) {
        Angle = a;
        sp_ShipSprite->setRotation (Angle);

        Direction.x = std::cos (Angle * 3.14159265359f / 180);
        Direction.y = std::sin (Angle * 3.14159265359f / 180);

        return *this;
    }

    Ship &Ship::setBulletPosition (const float &bx, const float &by, const std::size_t &i) {
        bulletPosition->at (i).x = bx;
        bulletPosition->at (i).y = by;

        bullets->at (i).setPosition (bx, by);

        return *this;
    }

    Ship &Ship::removeBullet (const std::size_t &i) {
        bullets->erase (bullets->begin () + i);
        bulletDirection->erase (bulletDirection->begin () + i);
        bulletPosition->erase (bulletPosition->begin () + i);

        bulletSize = bullets->size ();

        return *this;
    }

    const sf::Vector2f &Ship::getPosition () const {
        return Position;
    }

    const sf::Vector2f &Ship::getDirection () const {
        return Direction;
    }

    const int &Ship::getAngle () const {
        return Angle;
    }

    const sf::Vector2f &Ship::getBulletPosition (const std::size_t &i) const {
        return bulletPosition->at (i);
    }

    const sf::Vector2f &Ship::getBulletDirection (const std::size_t &i) const {
        return bulletDirection->at (i);
    }

    const sf::CircleShape &Ship::getBullets (const std::size_t &i) const {
        return bullets->at (i);
    }

    const std::size_t &Ship::getBulletSize () const {
        return bulletSize;
    }

    Ship &Ship::Clear () {

     bulletPosition->clear ();
     bulletDirection->clear ();
     bullets->clear ();

     bulletSize = bullets->size();

     return *this;
    }



