/********************************|
| Autor: Krzysztof kszyho8 Czoch |
|          2017.10.27            |
|********************************/

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <fstream>
#include <SFML/Graphics.hpp>

#include "conf.h"
#include "Platform.h"
#include "Player.h"

Player player; // deklaracja postaci
std::vector <Platform> platforms; // deklaracja kontenera z platformami
std::fstream config;  // plik konfiguracyjny do wczytania tekstur platform

sf::Font font;
sf::Text textScore("0", font);

/* inicjalizacja nowej gry */
void init(){
    gameState = 2; // status gry (gra rozpoczêta/trwaj¹ca)

    /* ustawienei punktów */
    score = 0;
    textScore.setString(std::to_string(score));
    textScore.setPosition(sf::Vector2f(20, 40));
    player.init(); // inicjalizacja postaci

    /* inicjalizacja platform */
    platforms[0].init(true);
    for(int i=1; i<platforms.size(); i++)
    {
        platforms[i].init(false, platforms[i-1].yPos());
    }
}

void loadConfig(std::string s)
{
    switch(std::stoi(s))
    {
    case 1:
        schody2 = 0;
        break;
    case 2:
        schody2 = 20;
        break;
    case 3:
        schody2 = 40;
        break;
    default:
        schody2 = 60;
        break;
    }
}

int main()
{
    srand(time(NULL));

    /* wczytanie pliku konfiguracyjnego z wyborem koloru platformy */
    std::string s = "4";
    config.open("config.cfg", std::ios::in);
    if ( !config.is_open() )
    {
        config.close();
        config.open("config.cfg", std::ios::out);
        config<<"4\n/*	liczba otpowiadająca za teksturę platformy\n*	1 - pierwsza tekstura ( brązowa )\n*   	2 - druga tekstua ( fioletowa )\n*	3 - trzecia tekstura (niebieska)\n* 	4 - trzecia tekstura ( pajęczyna )/";
        config.close();
        config.open("config.cfg", std::ios::in);
        std::getline(config, s);
        config.close();
    }
    else
    {
        std::getline(config, s);
        config.close();
    }
    loadConfig(s);

    /* stworzenie okna */
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Super jump");
    window.setFramerateLimit(60); // iloœæ klatek na sekundê

    sf::Texture texture_left, texture_middle, texture_right; // deklaracja tekstur platform

    font.loadFromFile("font/Action_Man.ttf");

    sf::Text text("SCORE:", font);
    text.setCharacterSize(30);
    text.setStyle(sf::Text::Bold);
    text.setColor(sf::Color::White);
    text.setPosition(sf::Vector2f(20,10));

    textScore.setCharacterSize(40);
    textScore.setStyle(sf::Text::Bold);
    textScore.setColor(sf::Color::White);

    /* wczytanie tekstur platformy pocz¹tkowej */
    texture_left.loadFromFile("img/platformy.png", sf::IntRect(0, schody2, SIZE, SIZE));
    texture_middle.loadFromFile("img/platformy.png", sf::IntRect(20, schody2, SIZE, SIZE));
    texture_right.loadFromFile("img/platformy.png", sf::IntRect(40, schody2, SIZE, SIZE));

    /* stworzenie platformy pocz¹tkowej */
    Platform p1(texture_left, texture_middle, texture_right, true);
    platforms.push_back(p1); // dodanie platformy do kontenera

    /*
    for(int i=0; i<5; i++) // nie wczytuje tekstur :(
    {
        Platform *p2 = new Platform(texture_left, texture_middle, texture_right, false, platforms[i].yPos());
        platforms.push_back(*p2);
        delete(p2);
    }
    */

    /*
    * nieeleganckie rozwi¹zanie, powy¿szy zakomentowany kod nie chcia³ wspó³pracowaæ w ¿aden sposób
    */
    Platform p2(texture_left, texture_middle, texture_right, false, platforms[0].yPos());
    platforms.push_back(p2);

    Platform p3(texture_left, texture_middle, texture_right, false, platforms[1].yPos());
    platforms.push_back(p3);

    Platform p4(texture_left, texture_middle, texture_right, false, platforms[2].yPos());
    platforms.push_back(p4);

    Platform p5(texture_left, texture_middle, texture_right, false, platforms[3].yPos());
    platforms.push_back(p5);

    Platform p6(texture_left, texture_middle, texture_right, false, platforms[4].yPos());
    platforms.push_back(p6);

    Platform p7(texture_left, texture_middle, texture_right, false, platforms[5].yPos());
    platforms.push_back(p7);
    /* koniec zgrozy */

    /* inicjalizacja t³a */
    sf::Texture backgroundTexture;
    backgroundTexture.setSmooth(true);
    sf::Sprite backgroundSprite;
    backgroundTexture.loadFromFile("img/tlo.png");
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setPosition(sf::Vector2f(0, 0));

    /* inicjalizacja ciemych cegie³ lewych */
    sf::Texture wallLTexture;
    wallLTexture.setSmooth(true);
    sf::Sprite wallLSprite;
    wallLTexture.loadFromFile("img/wallL.png");
    wallLSprite.setTexture(wallLTexture);
    wallLSprite.setPosition(sf::Vector2f(0, 0));

    /* inicjalizacja ciemych cegie³ prawych */
    sf::Texture wallRTexture;
    wallRTexture.setSmooth(true);
    sf::Sprite wallRSprite;
    wallRTexture.loadFromFile("img/wallR.png");
    wallRSprite.setTexture(wallRTexture);
    wallRSprite.setPosition(sf::Vector2f(SCREEN_WIDTH-OFFSET, 0));

    /* inicjalizacja grafiti */
    sf::Texture graffitiT;
    graffitiT.setSmooth(true);
    sf::Sprite graffitiS;
    graffitiT.loadFromFile("img/grafiti.png");
    graffitiS.setTexture(graffitiT);
    graffitiS.setPosition(sf::Vector2f(400, 200));
    graffitiS.setRotation(30);

    /* inicjalizacja menu */
    sf::Texture menuTexture;
    menuTexture.setSmooth(true);
    sf::Sprite menuSprite;
    menuTexture.loadFromFile("img/menu.png");
    menuSprite.setTexture(menuTexture);
    menuSprite.setPosition(sf::Vector2f(SCREEN_WIDTH/2-(490/2), SCREEN_HEIGHT/2-(292/2)));

    /* inicjalizacja pauzy */
    sf::Texture pauseTexture;
    pauseTexture.setSmooth(true);
    sf::Sprite pauseSprite;
    pauseTexture.loadFromFile("img/pause.png");
    pauseSprite.setTexture(pauseTexture);
    pauseSprite.setPosition(sf::Vector2f(SCREEN_WIDTH/2-(490/2), SCREEN_HEIGHT/2-(292/2)));

    /* inicjalizacja końca gry gry */
    sf::Texture overTexture;
    overTexture.setSmooth(true);
    sf::Sprite overSprite;
    overTexture.loadFromFile("img/over.png");
    overSprite.setTexture(overTexture);
    overSprite.setPosition(sf::Vector2f(SCREEN_WIDTH/2-(490/2), SCREEN_HEIGHT/2-(292/2)));

    /* g³ówna pêtla gry */
    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    switch(gameState)
                    {
                        case 1:
                            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                            {
                                window.close();
                            }
                            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
                            {
                                gameState = 2;
                                init();
                            }
                            break;
                        case 2:
                            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                            {
                                gameState = 3;
                            }
                            break;
                        case 3:
                            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                            {
                                gameState = 1;
                            }
                            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
                            {
                                gameState = 2;
                                init();
                            }
                            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                            {
                                gameState = 2;
                            }
                            break;
                        case 4:
                            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                            {
                                gameState = 1;
                            }
                            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
                            {
                                init();
                            }
                            break;
                    }
                    break;
            }
        }

        /* UPDATE POCZ¥TEK */
        switch(gameState)
        {
            case 1:
                break;
            case 2:
                {
                int col = 0; // licznik kolizji

                /* sprawdzenie kolizji z ka¿d¹ platform¹ */
                for(size_t i=0; i<platforms.size(); i++)
                {
                    if(player.xPos() + player.getWidth() > platforms[i].xPos() && player.xPos() < platforms[i].xPos() + platforms[i].getWidth())
                    {
                        if(player.yPos() + player.getHeight() + player.getVelocity() >= platforms[i].yPos() && player.yPos() + player.getHeight() < platforms[i].yPos()+SIZE)
                        {
                            if(player.getVelocity() >= 0) // sprawdz
                            {
                                player.update(true, platforms[i].yPos());
                                col++;
                                if(score < platforms[i].getPoints())
                                {
                                    score = platforms[i].getPoints();
                                    textScore.setString(std::to_string(score));
                                }
                            }
                        }
                    }
                    platforms[i].update();
                }
                if(col == 0)
                {
                    player.update(false);
                }
                if(player.yPos() < 200)
                {
                    for(int i=0; i<platforms.size(); i++)
                    {
                        platforms[i].down();
                    }
                }
                if(player.yPos() >= SCREEN_HEIGHT)
                {
                    gameState = 4;
                }
                }
                break;
            case 3:
                break;
            case 4:
                break;
        }
        /* UPDATE KOINEC */

        /* DRAW POCZ¥TEK */
        window.clear(sf::Color(255, 255, 255)); // bia³e t³o pod teksturami
        window.draw(backgroundSprite);
        window.draw(wallRSprite);
        window.draw(wallLSprite);
        window.draw(graffitiS);
        switch(gameState)
        {
            case 1:
                window.draw(menuSprite);
                break;
            default:
                for(int i=0; i<platforms.size(); i++) // wyœwietlenie wszystjich platform
                {
                    platforms[i].draw(window);
                }
                player.draw(window);
                if(gameState == 3)
                {
                    window.draw(pauseSprite);
                }
                if(gameState == 4)
                {
                    window.draw(overSprite);
                    textScore.setPosition(sf::Vector2f(500, 231));
                    window.draw(textScore);
                }
                else
                {
                    window.draw(text);
                    window.draw(textScore);
                }
                break;
        }

        window.display();
        /* DRAW KOINEC */
    }

    return 0;
}
