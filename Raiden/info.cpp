//
//  info.cpp
//  Raiden
//
//  Created by 王彥普 on 2021/1/8.
//  Copyright © 2021 !!!. All rights reserved.
//

#include "info.hpp"
#include <iostream>
#include "config.h"


Info::Info(float width, float height)
{
    if (!pages_texture[0].loadFromFile("Raiden/Resources/images/instruction1.jpg"))
    {
        pages_texture[0].loadFromFile("../Resources/images/instruction1.jpg");
        // handle error
    }

    pages[0].setTexture(pages_texture[0]);
    selectedPageIndex = 0;
}

Info::~Info()
{
    ;
}

void Info::info_state() // 音效設定
{
    SoundBuffer buffer;
    if (!buffer.loadFromFile("Raiden/Resources/audio/pop.wav"))
    {
        buffer.loadFromFile("../Resources/audio/pop.wav");
    }
    Sound pop;
    pop.setVolume(50);
    pop.setBuffer(buffer);
    
    SoundBuffer bLeave;
    if (!bLeave.loadFromFile("Raiden/Resources/audio/option.wav"))
    {
        bLeave.loadFromFile("../Resources/audio/option.wav");
    }
    Sound leave;
    leave.setVolume(50);
    leave.setBuffer(bLeave);
    
    RenderWindow window(VideoMode(WIDTH, HEIGHT), "RAIDEN");
    while(window.isOpen())
    {
        Event event;
        Clock clock;
        float timer = 0, limit = 0.3;
        

        while(window.pollEvent(event))
        {
            switch (event.type)
            {
            case Event::KeyReleased:
                switch (event.key.code)
                {
                case Keyboard::Space:
                case Keyboard::Return:
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
            case Event::Closed:
                window.close();
                break;
            }
        }
        
        window.clear();
        draw(window, pages[selectedPageIndex]);
        window.display();
    
    }
}

void Info::draw(RenderWindow &window, Sprite &page)
{
    window.clear();
    window.draw(page);
}

void Info::prevPage()
{
    if (selectedPageIndex - 1 >= 0)
    {
        selectedPageIndex--;
        std::cout << selectedPageIndex << std::endl;
        // return selectedPageIndex;
    }
    // else return selectedPageIndex;
}

void Info::nextPage()
{
    if (selectedPageIndex + 1 < MAX_NUM_OF_PAGES)
    {
        // pages[selectedItemIndex].setColor(Color(255, 255, 255, 180));
        // selectedItemIndex++;
        // pages[selectedItemIndex].setColor(Color(254, 255, 212, 255));
        selectedPageIndex++;
        std::cout << selectedPageIndex << std::endl;
        return;
        // return selectedPageIndex;
    }
    // else return selectedPageIndex;
}

