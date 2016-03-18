#ifndef BUTTON_HEADER
#define BUTTON_HEADER

#include <SFML/Graphics.hpp>

#include <iostream>


class Button {
public:

    Button () = default;

    Button &Draw (sf::RenderWindow &w) {
        w.draw (buttonBox);
        w.draw (buttonText);

        return *this;
    }

    Button &setLabelFontStyle (const std::string &t) {
        if (t == "italic")
            buttonText.setStyle(sf::Text::Italic);
        else if (t == "bold")
            buttonText.setStyle(sf::Text::Bold);
        else
            buttonText.setStyle(sf::Text::Regular);

        return *this;
    }

    Button &setButtonBackground (const sf::Color &c) {
        bgdColor = c;
        buttonBox.setFillColor (c);
        return *this;
    }

    Button &setButtonSize (const sf::Vector2f &sz) {
        buttonBox.setSize(sz);
        return *this;
    }

    Button &setBackgroundHoverColor (const sf::Color &c) {
        bghColor = c;
        return *this;
    }

    Button &setTextHoverColor (const sf::Color &c) {
        thColor = c;
        return *this;
    }

    Button &setLabelSize (const float &sz) {
        buttonText.setCharacterSize(sz);
        return *this;
    }

    Button &setPosition (const sf::Vector2f &v) {
        buttonBox.setPosition(v);
        buttonText.setPosition (v.x + 5, v.y - 5);
        return *this;
    }

    Button &setEvent (const std::string &s) {
        Event = s;
        return *this;
    }

    Button &setLabel (const std::string &s) {
        buttonText.setString (s);

        return *this;
    }

    Button &setTextFont (const std::string &s) {
        if (!buttonTextFont.loadFromFile(s))
            throw std::runtime_error ("error loading file " + s);

        buttonText.setFont (buttonTextFont);

        return *this;
    }


    Button &setTextColor (const sf::Color &c) {
        buttonText.setColor(c);
        tdColor = c;

        return *this;
    }

    Button &checkEvent (sf::Event &event) {
        if (event.type == sf::Event::MouseMoved) {
            pointPosition.x = event.mouseMove.x;
            pointPosition.y = event.mouseMove.y;

        }

        boxBounds = buttonBox.getGlobalBounds();

        if (boxBounds.contains(pointPosition.x, pointPosition.y)) {
            buttonBox.setFillColor(bghColor);
            buttonText.setColor (thColor);



        if (!isPressed) {

            if (event.type == sf::Event::MouseButtonPressed) {


                eventStatus = Event;
                isPressed = true;


            }
        }

        } else {
            buttonBox.setFillColor(bgdColor);
            buttonText.setColor (tdColor);
        }

        return *this;
    }

    bool getEvent (const std::string &s) {
        if (isPressed) {
            if (s == eventStatus) {
            isPressed = false;
            eventStatus = " ";
            return true;
            }

            return false;
        }

        return false;

    }




private:
    sf::Vector2f pointPosition;

    sf::Font buttonTextFont;
    sf::Text buttonText;
    sf::RectangleShape buttonBox;

    sf::Color bghColor;
    sf::Color bgdColor;

    sf::Color thColor;
    sf::Color tdColor;

    sf::FloatRect boxBounds;

    std::string Event;
    std::string eventStatus;

    bool isPressed = false;

};

#endif // BUTTON_HEADER
