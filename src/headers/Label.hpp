#ifndef LABEL_HEADER
#define LABEL_HEADER

#include <SFML/Graphics.hpp>

#include <string>

class Label {
public:

    Label () = default;

    Label &Draw (sf::RenderWindow &w) {
        w.draw (labelText);
        return *this;
    }

    Label &setLabelFont (const std::string &fileName) {
        if (!labelFont.loadFromFile(fileName))
            throw std::runtime_error ("error loading font file " + fileName);

        labelText.setFont (labelFont);

        return *this;
    }

    Label &setContent (const std::string &lb) {
        content = lb;
        labelText.setString(content);

        return *this;
    }

    Label &setTextColor (const sf::Color &c) {
        labelText.setColor(c);
        return *this;
    }

    Label &setPosition (const sf::Vector2f &pos) {
        labelText.setPosition (pos.x,
                               pos.y);

        return *this;
    }

    Label &setSize (const float &s) {
        labelText.setCharacterSize(s);
        return *this;
    }

private:
    sf::Font labelFont;
    sf::Text labelText;

    std::string content;

};

#endif // LABEL_HEADER
