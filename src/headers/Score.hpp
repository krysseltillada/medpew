#ifndef SCORE_HEADER
#define SCORE_HEADER

#include <SFML/Graphics.hpp>

#include <string>

#include <stdexcept>

#include <sstream>

class Score {
public:
    Score () = default;

    operator sf::Text & ();

    Score &setFont (const std::string &);
    Score &setFontSize (const float &);
    Score &initialScore (const int &);
    Score &setMultiplier (const int &);
    Score &setColor (const sf::Color &);
    Score &increase (const int &);
    Score &setPosition (const float &, const float &);
    Score &Clear ();

    int getScore ();
    int getMultiplier ();

    sf::Vector2f getPosition () const;

private:
    unsigned score = 0;

    int fontSize;
    sf::Color fontColor;
    int multiplier;


    std::string fontFile;

    sf::Font scoreFont;
    sf::Text scoreText;


};


#endif
