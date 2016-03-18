#include "Game.hpp"

namespace Harmonious {
    namespace Main {
        std::string Game::windowName = "medpew";

        int Game::windowWidth = 800;
        int Game::windowHeight = 600;

        State::GameState Game::gameState = State::GameState::GAME_EXIT_FAILED;

        Game::Game () :
            sp_GameWindow (new sf::RenderWindow (sf::VideoMode(Game::windowWidth, Game::windowHeight), Game::windowName)),
            sp_GameEvent  (new sf::Event ()),
            spawnCount (5, 10) { }

        void Game::MainMenu () {
            DEBUG_LOG("22");


            button.checkEvent(*sp_GameEvent);
            button2.checkEvent(*sp_GameEvent);

            if (button2.getEvent("exitGame"))
                    gameState = State::GameState::GAME_EXIT_SUCCESS;

            if (button.getEvent("startGame")) {
                    ifMainMenu = false;
                    ifStart = true;
            }

            if (!ifDecrease) {
                ++colorCount;

                if (colorCount >= 255)
                  ifDecrease = true;


            } else if (ifDecrease) {
                if ( !(colorCount > 0) )
                       ifDecrease = false;

                    --colorCount;
                }


            label.setTextColor (sf::Color (colorCount,
                                           colorCount,
                                           colorCount));

            button.Draw(*sp_GameWindow);
            button2.Draw(*sp_GameWindow);
            label.Draw (*sp_GameWindow);

            sp_GameWindow->display ();
            sp_GameWindow->clear ();


        }

        void Game::GameOver () {

            button3.checkEvent (*sp_GameEvent);
            button4.checkEvent (*sp_GameEvent);


            if (button3.getEvent ("restartGame")) {
                 Free ();

                 ifStart = true;
                 ifGameOver = false;
            }


            if (button4.getEvent("exit")) {
                Free ();
                gameState = State::GameState::GAME_EXIT_SUCCESS;
            }


            label2.Draw (*sp_GameWindow);
            button3.Draw (*sp_GameWindow);
            button4.Draw (*sp_GameWindow);

            sp_GameWindow->display ();
            sp_GameWindow->clear ();

        }

        void Game::init () {


            label.setContent ("Medpew");
            label.setLabelFont ("resources/vanadine/VanadineRegular.ttf");
            label.setSize (80);
            label.setTextColor(sf::Color::Green);
            label.setPosition (sf::Vector2f (Game::windowWidth - 530, Game::windowHeight - 500));

            label2.setContent ("Game Over");
            label2.setLabelFont ("resources/vanadine/VanadineRegular.ttf");
            label2.setSize (80);
            label2.setTextColor(sf::Color::White);
            label2.setPosition (sf::Vector2f (Game::windowWidth - 575, Game::windowHeight - 500));


            button.setLabel("Play");
            button.setTextFont("resources/vanadine/VanadineRegular.ttf");
            button.setTextColor(sf::Color::Red);
            button.setEvent("startGame");
            button.setButtonBackground(sf::Color::Transparent);
            button.setButtonSize(sf::Vector2f (120, 50));
            button.setBackgroundHoverColor(sf::Color::Transparent);
            button.setPosition(sf::Vector2f (337, 278));
            button.setLabelSize(50);
            button.setLabelFontStyle("bold");
            button.setTextHoverColor(sf::Color::Yellow);

            button2.setLabel("Exit");
            button2.setTextFont("resources/vanadine/VanadineRegular.ttf");
            button2.setTextColor(sf::Color::Red);
            button2.setEvent("exitGame");
            button2.setButtonBackground(sf::Color::Transparent);
            button2.setButtonSize(sf::Vector2f (120, 50));
            button2.setBackgroundHoverColor(sf::Color::Transparent);
            button2.setPosition(sf::Vector2f (343, 278 + 100));
            button2.setLabelSize(50);
            button2.setLabelFontStyle("bold");
            button2.setTextHoverColor(sf::Color::Yellow);

            button3.setLabel("again");
            button3.setTextFont("resources/vanadine/VanadineRegular.ttf");
            button3.setTextColor(sf::Color::Red);
            button3.setEvent("restartGame");
            button3.setButtonBackground(sf::Color::Transparent);
            button3.setButtonSize(sf::Vector2f (120, 50));
            button3.setBackgroundHoverColor(sf::Color::Transparent);
            button3.setPosition(sf::Vector2f (338, 278));
            button3.setLabelSize(50);
            button3.setLabelFontStyle("bold");
            button3.setTextHoverColor(sf::Color::Yellow);


            button4.setLabel("Exit");
            button4.setTextFont("resources/vanadine/VanadineRegular.ttf");
            button4.setTextColor(sf::Color::Red);
            button4.setEvent("exit");
            button4.setButtonBackground(sf::Color::Transparent);
            button4.setButtonSize(sf::Vector2f (120, 50));
            button4.setBackgroundHoverColor(sf::Color::Transparent);
            button4.setPosition(sf::Vector2f (343, 278 + 100));
            button4.setLabelSize(50);
            button4.setLabelFontStyle("bold");
            button4.setTextHoverColor(sf::Color::Yellow);


            sp_GameWindow->setKeyRepeatEnabled (false);
        }

        void Game::Start () {

            player.loadShipTexture ("resources/ship.png");

            player.setPosition (Game::windowWidth / 2, Game::windowHeight / 2);
            player.setSize (0.25f);

            player.setAngle (0);

            asteroid.pushTextureFile("resources/asteroid1.png");

            asteroid.setAsteroidCount (spawnCount.generate ());
            asteroid.setAsteroidSize (0.30f);
            asteroid.create ();

            if (playerScore.getScore () <= 0) {

            playerScore.setFont ("resources/vanadine/VanadineRegular.ttf");
            playerScore.setMultiplier (20);
            playerScore.initialScore (200);
            playerScore.setFontSize(40);
            playerScore.setColor (sf::Color::Green);
            playerScore.setPosition( (Game::windowWidth / 2) - 50, 0);

            } else {
                playerScore.initialScore (playerScore.getScore ());
                playerScore.setMultiplier (playerScore.getMultiplier () + 20);

            }

        }

        void Game::Run () {
            init ();


            while (sp_GameWindow->isOpen ()) {
                while (sp_GameWindow->pollEvent (*sp_GameEvent))
                        Event ();


                if (ifMainMenu) {
                    MainMenu();
                }

                if (ifGameOver)
                    GameOver();


                if(ifStart) {
                    Start();
                    ifStart = false;
                    ifGameStart = true;
                    ifMainMenu = false;
                }

                if (ifGameStart) {
                    Draw ();
                    Update();
                }






            }

        }

        void Game::Event () {
            if (sp_GameEvent->type == sf::Event::MouseMoved) {
                mousePosition.x = sp_GameEvent->mouseMove.x;
                mousePosition.y = sp_GameEvent->mouseMove.y;
            }

            if (sp_GameEvent->type == sf::Event::KeyPressed) {

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                ifFire = true;

            }


            if (sp_GameEvent->type == sf::Event::Closed)
                gameState = State::GameState::GAME_EXIT_SUCCESS;


            if (gameState == State::GameState::GAME_EXIT_SUCCESS)
                sp_GameWindow->close ();
        }

        void Game::Update () {
            // const float PI = 3.14159265359f;

            const float bulletSpeed = 300.2f;
            const float shipSpeed = 200.0f;

            bool ifHit = false;
            bool ifHit2 = false;

            sf::Time time = gameClock.getElapsedTime ();


            float deltaTime = time.asSeconds();

            gameClock.restart ();

            sf::Vector2f newVec;


            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                player.setAngle (player.getAngle () - 0.90f);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                player.setAngle (player.getAngle () + 1);

            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                player.setPosition (player.getPosition ().x + player.getDirection ().x * deltaTime * shipSpeed,
                                    player.getPosition ().y + player.getDirection ().y * deltaTime * shipSpeed);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                player.setPosition (player.getPosition ().x - player.getDirection ().x * deltaTime * shipSpeed,
                                    player.getPosition ().y - player.getDirection ().y * deltaTime * shipSpeed);
            }

            if (ifFire)  {
                player.Fire ();
                ifFire = false;
            }

            if (player.getAngle () >= 360)
                player.setAngle (1);

            if (player.getAngle () <= 0)
                player.setAngle (360);

            asteroid.setDeltaTime (deltaTime);


            for (std::size_t bulletCount = 0; bulletCount != player.getBulletSize (); ++bulletCount) {


                 player.setBulletPosition (player.getBulletPosition (bulletCount).x + player.getBulletDirection (bulletCount).x * deltaTime * bulletSpeed,
                                           player.getBulletPosition (bulletCount).y + player.getBulletDirection (bulletCount).y * deltaTime * bulletSpeed,
                                                                     bulletCount);

                 if (Collision::WindowCollision(player.getBulletPosition (bulletCount).x,
                                                player.getBulletPosition (bulletCount).y,
                                                0, 0,
                                                Game::windowHeight, Game::windowWidth)) {
                                                    player.removeBullet (bulletCount);
                                                    --bulletCount;
                                                }


            }

             for (std::size_t asteroidCount = 0; asteroidCount != asteroid.getAsteroidCount("asteroid"); ++asteroidCount) {
                    std::string collides = Collision::WindowCircleCollisionS(asteroid.getCollider(asteroidCount, "asteroid").getRadius(),
                                                         asteroid.getCollider(asteroidCount, "asteroid").getPosition().x,
                                                         asteroid.getCollider(asteroidCount, "asteroid").getPosition().y,
                                                         0, 0,
                                                         Game::windowHeight, Game::windowWidth);

                    sf::Vector2f newAsteroidPos = asteroid.getAsteroid(asteroidCount).getPosition();
                    sf::Vector2f newColliderPos = asteroid.getCollider(asteroidCount, "asteroid").getPosition();

                    if (collides == "Left") {
                        newAsteroidPos.x = asteroid.getCollider(asteroidCount, "asteroid").getRadius () + Game::windowWidth;
                        newColliderPos.x = asteroid.getCollider(asteroidCount, "asteroid").getRadius () + Game::windowWidth;
                    }
                    else if (collides == "Right") {
                        newAsteroidPos.x = -asteroid.getCollider(asteroidCount, "asteroid").getRadius ();
                        newColliderPos.x = -asteroid.getCollider(asteroidCount, "asteroid").getRadius ();
                    }
                    else if (collides == "Up") {
                        newAsteroidPos.y = asteroid.getCollider(asteroidCount, "asteroid").getRadius () + Game::windowHeight;
                        newColliderPos.y = asteroid.getCollider(asteroidCount, "asteroid").getRadius () + Game::windowHeight;
                    }
                    else if (collides == "Down") {
                        newAsteroidPos.y = -asteroid.getCollider(asteroidCount, "asteroid").getRadius ();
                        newColliderPos.y = -asteroid.getCollider(asteroidCount, "asteroid").getRadius ();
                    }

                    asteroid.getAsteroid(asteroidCount).setPosition(newAsteroidPos.x, newAsteroidPos.y);
                    asteroid.getCollider(asteroidCount, "asteroid").setPosition(newColliderPos.x, newColliderPos.y);


            }


            for (std::size_t asteroidCount = 0; asteroidCount != asteroid.getAsteroidCount("asteroid"); ++asteroidCount) {
                    sf::FloatRect b1 = asteroid.getCollider(asteroidCount, "asteroid").getGlobalBounds();
                    sf::FloatRect b2 = player.getShip ().getGlobalBounds ();

                    if (b1.intersects(b2)) {
                        ifGameOver = true;
                        ifStart = false;
                        ifGameStart = false;
                        break;
                    }

            }

            for (std::size_t minasteroidCount = 0; minasteroidCount != asteroid.getAsteroidCount("miniasteroid"); ++minasteroidCount) {
                    sf::FloatRect b1 = asteroid.getCollider(minasteroidCount, "miniasteroid").getGlobalBounds();
                    sf::FloatRect b2 = player.getShip ().getGlobalBounds();

                    if (b1.intersects(b2)) {
                        ifGameOver = true;
                        ifStart = false;
                        ifGameStart = false;

                        break;
                    }
            }


            for (std::size_t mAsteroidCount = 0; mAsteroidCount != asteroid.getAsteroidCount("miniasteroid"); ++mAsteroidCount) {
                    std::string collides = Collision::WindowCircleCollisionS(asteroid.getCollider(mAsteroidCount, "miniasteroid").getRadius(),
                                                         asteroid.getCollider(mAsteroidCount, "miniasteroid").getPosition().x,
                                                         asteroid.getCollider(mAsteroidCount, "miniasteroid").getPosition().y,
                                                         0, 0,
                                                         Game::windowHeight, Game::windowWidth);

                    sf::Vector2f newAsteroidPos = asteroid.getMiniAsteroid(mAsteroidCount).getPosition();
                    sf::Vector2f newColliderPos = asteroid.getCollider(mAsteroidCount, "miniasteroid").getPosition();

                    if (collides == "Left") {
                        newAsteroidPos.x = asteroid.getCollider(mAsteroidCount, "miniasteroid").getRadius () + Game::windowWidth;
                        newColliderPos.x = asteroid.getCollider(mAsteroidCount, "miniasteroid").getRadius () + Game::windowWidth;
                    }
                    else if (collides == "Right") {
                        newAsteroidPos.x = -asteroid.getCollider(mAsteroidCount, "miniasteroid").getRadius ();
                        newColliderPos.x = -asteroid.getCollider(mAsteroidCount, "miniasteroid").getRadius ();
                    }
                    else if (collides == "Up") {
                        newAsteroidPos.y = asteroid.getCollider(mAsteroidCount, "miniasteroid").getRadius () + Game::windowHeight;
                        newColliderPos.y = asteroid.getCollider(mAsteroidCount, "miniasteroid").getRadius () + Game::windowHeight;
                    }
                    else if (collides == "Down") {
                        newAsteroidPos.y = -asteroid.getCollider(mAsteroidCount, "miniasteroid").getRadius ();
                        newColliderPos.y = -asteroid.getCollider(mAsteroidCount, "miniasteroid").getRadius ();
                    }

                    asteroid.getMiniAsteroid(mAsteroidCount).setPosition(newAsteroidPos.x, newAsteroidPos.y);
                    asteroid.getCollider(mAsteroidCount, "miniasteroid").setPosition(newColliderPos.x, newColliderPos.y);


            }


            for (std::size_t asteroidCount = 0; asteroidCount != asteroid.getAsteroidCount("asteroid"); ++asteroidCount) {
                    sf::FloatRect c2 = asteroid.getAsteroid(asteroidCount).getGlobalBounds();

                    for (std::size_t bulletCount = 0; bulletCount != player.getBulletSize(); ++bulletCount) {
                        sf::FloatRect c1 = player.getBullets (bulletCount).getGlobalBounds();

                        if (c1.intersects(c2)) {

                                playerScore.increase(200);

                                asteroid.Explode(asteroidCount);
                                asteroid.remove(asteroidCount, "asteroid");
                                --asteroidCount;

                            ifHit = true;

                            player.removeBullet(bulletCount);

                            --bulletCount;

                            break;
                        }
                    }

                    if (ifHit) {
                        ifHit = false;
                        break;
                    }
            }

            for (std::size_t minAsteroid = 0; minAsteroid != asteroid.getAsteroidCount("miniasteroid"); ++minAsteroid) {
                sf::FloatRect c1 = asteroid.getMiniAsteroid(minAsteroid).getGlobalBounds();

                for (std::size_t bulletCount = 0; bulletCount != player.getBulletSize(); ++bulletCount) {
                        sf::FloatRect c2 = player.getBullets(bulletCount).getGlobalBounds();

                        if (c1.intersects(c2)) {
                                playerScore.increase(20);

                                asteroid.remove(minAsteroid, "miniasteroid");
                                player.removeBullet(bulletCount);

                                --minAsteroid;
                                --bulletCount;

                                ifHit2 = true;

                                break;
                        }

                }

                if (ifHit2) {
                    ifHit2 = false;
                    break;
                }
            }


            if (Collision::WindowCircleCollisionB(player.getShipRadius(),
                                                 player.getPosition().x, player.getPosition().y,
                                                 0, 0,
                                                 Game::windowHeight, Game::windowWidth)) {
                                                        ifGameOver = true;
                                                        ifStart = false;
                                                        ifGameStart = false;
                                                 }


            if (asteroid.getAsteroidCount ("asteroid") <= 0 &&
                asteroid.getAsteroidCount ("miniasteroid") <= 0) {
                    ifStart = true;

                }

        }


        void Game::Draw () {

            for (std::size_t bulletCount = 0; bulletCount != player.getBulletSize (); ++bulletCount)
                sp_GameWindow->draw (player.getBullets (bulletCount));


            asteroid.Draw (*sp_GameWindow);


            sp_GameWindow->draw (player);
            sp_GameWindow->draw (playerScore);


            sp_GameWindow->display ();
            sp_GameWindow->clear ();
        }

        void Game::Free () {
            player.Clear ();
            playerScore.Clear ();
            asteroid.Clear ();

        }
    }
}
