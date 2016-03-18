#ifndef GAME_HEADER
#define GAME_HEADER

#include "Ship.hpp"

#include "Collision.hpp"

#include "Asteroid.hpp"

#include "Score.hpp"

#include "Button.hpp"

#include "Label.hpp"

#include <SFML/Graphics.hpp>

#include <string>

#include <memory>

#include <iostream>

#include <stdio.h>

#define DEBUG
#define C

#ifdef DEBUG

template <typename T>
inline void LOG (const T &s) { std::cout << s << std::endl; }

#ifdef C
#define DEBUG_LOG(v) {printf ("%s\n", #v);}
#endif


#endif



namespace Harmonious {
    namespace State {
        enum class GameState {
            GAME_EXIT_SUCCESS,
            GAME_EXIT_FAILED
        };
    }

    namespace Main {

    class Game {
    public:
        Game ();

        void MainMenu ();
        void GameOver ();

        void init  (); /// initializes main_menu objects etc..
        void Start ();  /// initialize game objects, etc..
        void Run ();  /// runs the main game loop
        void Event (); /// gets the user inputs, window events, etc...
        void Update (); /// updates the game
        void Draw (); /// draws the objects into the screen
        void Free ();

    private:
        static State::GameState gameState;

        static std::string windowName;
        static int windowWidth;
        static int windowHeight;

        std::unique_ptr <sf::RenderWindow> sp_GameWindow;
        std::unique_ptr <sf::Event> sp_GameEvent;

        Ship player;
        Asteroid asteroid;
        Score playerScore;

        sf::Vector2f mousePosition;
        sf::Clock gameClock;

        RandomGenerator spawnCount;

        Button button;
        Button button2;
        Button button3;
        Button button4;

        Label label;
        Label label2;

        bool ifFire = false;

        bool ifStart = false;
        bool ifGameStart = false;
        bool ifMainMenu = true;
        bool ifDecrease = false;
        bool ifGameOver = false;
        bool ifReturn = false;


        int colorCount = 0;
        int prevScore = 0;


    };

    }
}




#endif // GAME_HEADER
