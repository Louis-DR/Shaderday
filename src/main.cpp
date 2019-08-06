#include <iostream>
#include <cmath>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

float sigmoid(float x) {
    return 1 / (1 + std::exp(-x));
}

void updateShift(sf::Image* shiftarr_red, sf::Image* shiftarr_blue, float t) {
    for (auto x=0 ; x<256 ; x++) {
        sf::Uint8 hue, sat, lum;
        hue = 0 *255/360;
        if (x<140) hue = 0.05*x;
        else hue = 360-0.05*(360-x);
        sat = 0.8*x;
        lum = 0.7*x;
        shiftarr_red->setPixel(x,0, sf::Color{hue,sat,lum, 255});
    }
    for (auto x=0 ; x<256 ; x++) {
        sf::Uint8 hue, sat, lum;
        // hue = 120 *360/255;
        if (x<140) hue = 230-0.3*(230-x);
        else hue = 230-0.3*(230-x);
        sat = 0.7*x;
        lum = 0.5*x;
        shiftarr_blue->setPixel(x,0, sf::Color{hue,sat,lum, 255});
    }
}

int  main() {
    sf::RenderWindow  window(sf::VideoMode(1000, 1000), "My window");
    sf::Clock clock;

    sf::Texture texture;

    sf::Sprite sprite_nofilter;
    sf::Shader shader_nofilter;
    sf::Image shiftarr_nofilter;
    sf::Texture shift_nofilter;

    sf::Sprite sprite_red;
    sf::Shader shader_red;
    sf::Image shiftarr_red;
    sf::Texture shift_red;

    sf::Sprite sprite_blue;
    sf::Shader shader_blue;
    sf::Image shiftarr_blue;
    sf::Texture shift_blue;
    
    texture.loadFromFile("res/pic.png");

    sprite_nofilter.setTexture(texture);
    shiftarr_nofilter.create(256,1);
    for (auto x=0 ; x<256 ; x++) shiftarr_nofilter.setPixel(x,0, sf::Color{x,x,x,255});
    shift_nofilter.loadFromImage(shiftarr_nofilter);
    shader_nofilter.loadFromFile("res/shader.frag", sf::Shader::Fragment);
    shader_nofilter.setUniform("texture", sf::Shader::CurrentTexture);
    shader_nofilter.setUniform("shift", shift_nofilter);
    shader_nofilter.setUniform("opacity", 1.0f);

    sprite_red.setTexture(texture);
    shiftarr_red.create(256,1);
    for (auto x=0 ; x<256 ; x++) {
        sf::Uint8 hue, sat, lum;
        hue = 0 *360/255;
        sat = 0.8*x;
        lum = 0.8*x;
        shiftarr_red.setPixel(x,0, sf::Color{hue,sat,lum, 255});
    }
    shift_red.loadFromImage(shiftarr_red);
    shader_red.loadFromFile("res/shader.frag", sf::Shader::Fragment);
    shader_red.setUniform("texture", sf::Shader::CurrentTexture);
    shader_red.setUniform("shift", shift_red);
    shader_red.setUniform("opacity", 1.0f);

    sprite_blue.setTexture(texture);
    shiftarr_blue.create(256,1);
    for (auto x=0 ; x<256 ; x++) {
        sf::Uint8 hue, sat, lum;
        hue = 115 *360/255;
        sat = 0.7*x;
        lum = 0.5*x;
        shiftarr_blue.setPixel(x,0, sf::Color{hue,sat,lum, 255});
    }
    shift_blue.loadFromImage(shiftarr_blue);
    shader_blue.loadFromFile("res/shader.frag", sf::Shader::Fragment);
    shader_blue.setUniform("texture", sf::Shader::CurrentTexture);
    shader_blue.setUniform("shift", shift_blue);
    shader_blue.setUniform("opacity", 1.0f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                default:
                    break;
            }
        }
        window.clear(sf::Color::Black);

        float t = (clock.getElapsedTime().asMilliseconds()%10000) /1000.0f;
        std::cout << t << std::endl;
        float goldhour = sigmoid((t-2)*8) - sigmoid((t-8)*8);
        float bluehour = sigmoid((t-3)*8) - sigmoid((t-7)*8);

        updateShift(&shiftarr_red, &shiftarr_blue, t);
        shift_red.update(shiftarr_red);
        shift_blue.update(shiftarr_blue);
        shader_red.setUniform("shift", shift_red);
        shader_blue.setUniform("shift", shift_blue);

        shader_red.setUniform("opacity", goldhour);
        shader_blue.setUniform("opacity", bluehour);

        window.draw(sprite_nofilter, &shader_nofilter);
        window.draw(sprite_red, &shader_red);
        window.draw(sprite_blue, &shader_blue);
        window.display();
    }

    system("pause");
    return 0;
}