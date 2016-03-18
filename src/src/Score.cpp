#include "Score.hpp"

Score::operator sf::Text &() {
    std::ostringstream toString;

    toString << score;

    scoreText.setString (toString.str ());

    return scoreText;
}

Score &Score::setFont (const std::string &fileName) {
    fontFile = fileName;

    if (!scoreFont.loadFromFile(fontFile))
        throw std::runtime_error ("cannot find file--> " + fontFile);

    scoreText.setFont (scoreFont);
    return *this;
}

Score &Score::setFontSize (const float &s) {
    fontSize = s;
    scoreText.setCharacterSize(fontSize);
    return *this;
}

Score &Score::initialScore (const int &scr) {
    score = scr;
    return *this;
}

Score &Score::setMultiplier (const int &multip) {
    multiplier = multip;
    return *this;
}

Score &Score::setColor (const sf::Color &c) {
    fontColor = c;
    scoreText.setColor(fontColor);
    return *this;
}

Score &Score::increase (const int &s) {
    score += s * multiplier;
    return *this;
}

Score &Score::setPosition (const float &x, const float &y) {
    scoreText.setPosition(x, y);
    return *this;
}

sf::Vector2f Score::getPosition() const {
    return scoreText.getPosition();
}

int Score::getScore () {
    return score;
}

int Score::getMultiplier () {
    return multiplier;
}

Score &Score::Clear() {
    score = 0;
    multiplier = 0;
    return *this;
}


