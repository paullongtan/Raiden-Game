
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "config.h"
#include "game.hpp"
#include "info.hpp"
#include "menu.hpp"
//#include "game.hpp"
//#include "info.hpp"
#include <ctime>
using namespace sf;

int main()
{
    Image image;
    // setting
    srand(time(0));
    RenderWindow window(VideoMode(WIDTH, HEIGHT), "IMRaiden");

    Menu menu(window.getSize().x, window.getSize().y);
    Info info(window.getSize().x, window.getSize().y);
    Game game;

    Music music;
    if (!music.openFromFile("Raiden/Resources/audio/raiden.wav"))
    {
        music.openFromFile("../Resources/audio/raiden.wav");
    }
    music.setVolume(20);
    music.setLoop(true);
    music.play();
      
    SoundBuffer buffer;
    if (!buffer.loadFromFile("Raiden/Resources/audio/pop.wav"))
    {
        buffer.loadFromFile("../Resources/audio/pop.wav");
    }
    Sound pop;
    pop.setVolume(50);
    pop.setBuffer(buffer);
    SoundBuffer bLeave;
    if (!bLeave.loadFromFile("Raiden/Resources/audio/leave.wav"))
    {
        bLeave.loadFromFile("../Resources/audio/leave.wav");
    }
    Sound leave;
    leave.setVolume(50);
    leave.setBuffer(bLeave);
    SoundBuffer bEnter;
    //if (!bEnter.loadFromFile("../Resources/audio/enter.wav"))
    if (!bEnter.loadFromFile("Raiden/Resources/audio/enter.wav"))
    {
        bEnter.loadFromFile("../Resources/audio/enter.wav");
    }
    Sound enter;
    enter.setVolume(50);
    enter.setBuffer(bEnter);
    SoundBuffer bOption;
    //if (!bOption.loadFromFile("../Resources/audio/option.wav"))
    if (!bOption.loadFromFile("Raiden/Resources/audio/option.wav"))
    {
        bOption.loadFromFile("../Resources/audio/option.wav");
    }
    Sound option;
    option.setVolume(50);
    option.setBuffer(bOption);
    
    while(window.isOpen())
    {
        Event event;
        Clock clock;
        float timer = 0, limit = 0.3;

        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case Event::KeyReleased:
                    switch (event.key.code)
                    {
                        case Keyboard::Up:
                        case Keyboard::Left:
                            menu.MoveUp();
                            pop.play();
                            break;
                        case Keyboard::Down:
                        case Keyboard::Right:
                            menu.MoveDown();
                            pop.play();
                            break;
                        case Keyboard::Return:
                        case Keyboard::Space:
                            switch (menu.GetPressedItem())
                            {
                                case 0:
                                    std::cout << "Play button has been pressed" << std::endl;
                                    music.setVolume(30);
                                    window.setVisible(false);
                                    enter.play();
                                    while (timer < limit + 0.1)
                                    {
                                        float time = clock.getElapsedTime().asSeconds();
                                        clock.restart();
                                        timer += time;
                                    }
                                    game.run();
                                    music.setVolume(40);
                                    window.setVisible(true);
                                    break;
                                case 1:
                                    std::cout << "Instruction button has been pressed"
                                    << std::endl;
                                    window.setVisible(false);
                                    option.play();
                                    while (timer < limit)
                                    {
                                        float time = clock.getElapsedTime().asSeconds();
                                        clock.restart();
                                        timer += time;
                                    }
                                    info.info_state();
                                    window.setVisible(true);
                                    break;
                                case 2:
                                    leave.play();
                                    while (timer < limit)
                                    {
                                        float time = clock.getElapsedTime().asSeconds();
                                        clock.restart();
                                        timer += time;
                                    }
                                    window.close();
                                    break;
                            }
                            break;
                    }
            break;
                case Event::Closed:
                    window.close();
                    break;
            }
        }
        window.clear();
        menu.draw(window);
        window.display();
          
        }
        return 0;
}
