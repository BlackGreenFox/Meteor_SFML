#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <windows.h>

// Files
#include "BlobMessage.h"
#include "Meteor.h"

using namespace sf;

enum State {
    Start,
    Play,
    Finish
};

Color interpolateColor(const Color& color1, const Color& color2, float t) {
    Color result;
    result.r = static_cast<Uint8>(color1.r + (color2.r - color1.r) * t);
    result.g = static_cast<Uint8>(color1.g + (color2.g - color1.g) * t);
    result.b = static_cast<Uint8>(color1.b + (color2.b - color1.b) * t);
    return result;
}

int main()
{
    srand(time(NULL));

    Font font;
    Clock timer, timerAnim, timerInfinit, timerSound;
    State gameState;
    Image icon;
    Music music;
    SoundBuffer bufferSound;
    Sound sound;

    if (!font.loadFromFile("Font/Daydream.TTF")) {
        return -1;
    }

    if (!icon.loadFromFile("Images/icon.png")) {
        return 1;
    }
  
    if (!music.openFromFile("Sound/music.mp3")) {
        return -1;
    }

    if (!bufferSound.loadFromFile("Sound/dialog_sound.mp3")) {
        return -1;
    }

    sound.setBuffer(bufferSound);
    music.setLoop(true);
    music.setVolume(50);

    RenderWindow window(VideoMode(1280, 720), "Meteor | Endless Night ");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // Components
    RectangleShape backgroundF(Vector2f(1280, 720));
    RectangleShape backgroundB1(Vector2f(1280, 720));
    RectangleShape backgroundB2(Vector2f(1280, 720));

    Text messageText("Message", font, 14);
    Text startText("What a beautiful night*", font, 48);

    FloatRect textRect = startText.getLocalBounds();
    startText.setOrigin(textRect.left + textRect.width / 2.0f,
        textRect.top + textRect.height / 2.0f);
    startText.setPosition(Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f));
    Text autorText("Create by Anton Kostiuchenko", font, 18);
    autorText.setPosition(640, 400);
    autorText.setFillColor(Color(255,255,255,85));

    BlobMessage message("Images/message.png", "Images/liza.png",Vector2f(690, 300), messageText);

    Meteor meteors[25] = {
    Meteor("Images/meteor.png"),
    Meteor("Images/meteor.png"),
    Meteor("Images/meteor.png"),
    Meteor("Images/meteor.png"),
    Meteor("Images/meteor.png"),
    Meteor("Images/meteor.png"),
    Meteor("Images/meteor.png"),
    Meteor("Images/meteor.png"),
    Meteor("Images/meteor.png"),
    Meteor("Images/meteor.png"),
    Meteor("Images/meteor.png"),
    Meteor("Images/meteor.png"),
    Meteor("Images/meteor.png"),
    Meteor("Images/meteor.png"),
    Meteor("Images/meteor.png"),
    Meteor("Images/meteor.png"),
    Meteor("Images/meteor.png"),
    Meteor("Images/meteor.png"),
    Meteor("Images/meteor.png"),
    Meteor("Images/meteor.png"),
    Meteor("Images/meteor.png"),
    Meteor("Images/meteor.png"),
    Meteor("Images/meteor.png"),
    Meteor("Images/meteor.png"),
    Meteor("Images/meteor.png")
    };


    // Textures
    Texture background_nightsky;
    Texture background_nightsky2;
    Texture background_front;

    background_nightsky.loadFromFile("Images/background.png");
    background_nightsky2.loadFromFile("Images/background2.png");
    background_front.loadFromFile("Images/frontbackground.png");

    backgroundF.setTexture(&background_front);
    backgroundB1.setTexture(&background_nightsky);
    backgroundB2.setTexture(&background_nightsky2);

    backgroundB2.setPosition(Vector2f(1280, 0));

    // Varibles
    Vector2f bg_pos;
    float ftime, ftimeSmooth, fAnimtime, fcolor;
    float backgroundY = 0.0f;
    bool isPlaying = false;
    Color greenColor(58, 205, 163); 
    Color purpleColor(174, 1, 112);  
    gameState = Start;

    timerAnim.restart();
    music.play();

    while (window.isOpen()) {
        Event event;

        // Ticks
        fcolor = std::abs(std::sin(timerInfinit.getElapsedTime().asSeconds() * 0.2));
        fAnimtime = timer.getElapsedTime().asMicroseconds();
        ftime = timer.getElapsedTime().asMicroseconds();
        ftimeSmooth = ftime / 3000;

        timer.restart();
        timerAnim.restart();

       
        Color currentColor = interpolateColor(greenColor, purpleColor, fcolor);
   
        startText.setFillColor(currentColor);


        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && gameState == Start) {
                gameState = Play;
            }
            else if (event.type == sf::Event::KeyPressed && gameState == Play) {
                if (event.key.code == sf::Keyboard::Escape) gameState = Finish;              
                  
                if (event.key.code >= sf::Keyboard::A && event.key.code <= sf::Keyboard::Z) {
                    char charToAdd = static_cast<char>(event.key.code - sf::Keyboard::A + 'A');
                    message.addCharacterToText(charToAdd, messageText);
                    sound.play();
                    timerSound.restart();
                    isPlaying = true;
                }
                else if (event.key.code == sf::Keyboard::Space) {
                    message.addCharacterToText(' ', messageText);
                    sound.play();
                    timerSound.restart();
                    isPlaying = true;
                }
                 
            }
        }

        window.clear();


        backgroundB1.move(-0.005f * ftimeSmooth, 0);
        bg_pos = backgroundB1.getPosition();
        backgroundB1.setPosition(bg_pos.x, 0);
        if (bg_pos.x < -1280)
            backgroundB1.setPosition(1280, 0);



        backgroundB2.move(-0.005f * ftimeSmooth, 0);
        bg_pos = backgroundB2.getPosition();
        backgroundB2.setPosition(bg_pos.x, 0);
        if (bg_pos.x < -1280)
            backgroundB2.setPosition(1280, 0);

        window.draw(backgroundB1);
        window.draw(backgroundB2);

        switch (gameState)
        {
        case Start:
            window.draw(startText);
            window.draw(autorText);
            break;
        case Play:
            for (auto& meteor : meteors) {
                meteor.move(ftimeSmooth);

                meteor.setFlytime(fAnimtime / 500);

                meteor.draw(window);
            }

            if (isPlaying && timerSound.getElapsedTime().asSeconds() >= 0.8f) {  
                sound.stop();
                isPlaying = false;
            }

            message.update(messageText);

            message.draw(window);
            window.draw(messageText);

            window.draw(backgroundF);
            break;
        case Finish:
            sound.stop();
            startText.setString("Endless night, never end");
            window.draw(startText);
            break;
        }



        window.display();
    }

    return 0;
}
 