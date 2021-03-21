#include <SFML/Graphics.hpp>
#include <string.h>
#include "arena.h"
#include <string.h>

inline void shader_on_tex(sf::Shader* shader_,sf::RenderTexture* renderTex_)
{
    sf::Sprite tempS;
    sf::RenderTexture tempT;
    tempT.create(SCREEN_W, SCREEN_H);
    tempS.setTexture(tempT.getTexture());
    tempT.clear();
    sf::Sprite renderSprt;
    renderSprt.setTexture(renderTex_->getTexture());

    tempT.draw(renderSprt, shader_);
    renderTex_->draw(tempS);
}

void centerText(sf::Text* t_)
{
    sf::FloatRect textRect = t_->getLocalBounds();
    t_->setOrigin(textRect.left + textRect.width/2.0f,textRect.top  + textRect.height/2.0f);
}

void topLeftText(sf::Text* t_)
{
    sf::FloatRect textRect = t_->getLocalBounds();
    t_->setOrigin(textRect.left,textRect.top);
}

Vector world_to_screen_pos(Vector w)
{
    w.y = -w.y;
    return w + vec_v((float)SCREEN_W/2.f, (float)SCREEN_H/2.f);
}

Vector screen_to_world_pos(Vector w)
{
    Vector final = w  - vec_v((float)SCREEN_W/2.f, (float)SCREEN_H/2.f);
    final.y = -final.y;
    return final;
}

int main()
{
    std::srand(static_cast<unsigned int>(std::time(NULL)));

    sf::RenderWindow window(sf::VideoMode(SCREEN_W, SCREEN_H, 32), "ML Fihgt", sf::Style::Titlebar);
    window.setVerticalSyncEnabled(true);

    sf::Sprite renderSprt;
    sf::RenderTexture renderTex;
    renderTex.create(SCREEN_H, SCREEN_H);
    renderSprt.setTexture(renderTex.getTexture());
    renderTex.clear();

    sf::Font font;
    font.loadFromFile("res/GoogleSans-Bold.ttf");

    sf::Text text;
    text.setFont(font);
    sf::Vector2f screenSize((float)SCREEN_W, (float)SCREEN_H);

    bool needToDraw = true;

    int tick = 0;

    sf::Shader* updateShader = new sf::Shader;
    updateShader->loadFromFile("res/update.frag", sf::Shader::Fragment);


    Population pop(AGENTS_NB, "Agent");
    Arena arena(pop);
    bool showRays = true;

    renderTex.clear();

    while (window.isOpen())
    {
        sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));
        sf::Event event;
        while (window.pollEvent(event))
        {
            if ((event.type == sf::Event::Closed) || ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
            {
                window.close();
                break;
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code ==  sf::Keyboard::Space)
                {
                    needToDraw = !needToDraw;
                    text.setString("Evolution is happening...");
                    text.setFillColor(sf::Color::White);
                    // text.setScale(sf::Vector2f(2.f, 2.f));
                    centerText(&text);
                    text.setPosition(vec_to_sfvec2_v(world_to_screen_pos(vec_v(0.f,0.f))));
                    window.draw(text);
                    window.display();
                }
                if (event.key.code ==  sf::Keyboard::S)
                {
                    showRays = !showRays;
                }
            }
        }

        tick++;
        if (!arena.do_tournament())
        {
            arena.update_pop();
            arena.restart();
        }

        if (!needToDraw)
        {
            continue;
        }
        window.clear();

        Agent* a = arena.fighterA;
        Agent* b = arena.fighterB;
        // a->print();
        // b->print();

        sf::CircleShape circle(ARENA_RADIUS);
        circle.setFillColor(sf::Color(10, 20, 30));
        circle.setOrigin(circle.getRadius(), circle.getRadius());
        circle.setPosition(vec_to_sfvec2_v(world_to_screen_pos(vec_v(0.f,0.f))));
        window.draw(circle);
        circle.setFillColor(sf::Color(100, 200, 55));
        circle.setRadius((BULLET_RADIUS/3.f)*2.f);
        circle.setOrigin(circle.getRadius(), circle.getRadius());
        circle.setPosition(vec_to_sfvec2_v(world_to_screen_pos(a->pos)));
        window.draw(circle);
        circle.setFillColor(sf::Color(155, 55, 200));
        circle.setPosition(vec_to_sfvec2_v(world_to_screen_pos(b->pos)));
        window.draw(circle);
        circle.setRadius(BULLET_RADIUS/4.f);
        circle.setOrigin(circle.getRadius(), circle.getRadius());
        circle.setFillColor(sf::Color(255, 255, 255));
        circle.setPosition(vec_to_sfvec2_v(world_to_screen_pos(a->pos + invert_v(vec_from_angle_v(a->angle)*BULLET_RADIUS)/2.f)));
        window.draw(circle);
        circle.setPosition(vec_to_sfvec2_v(world_to_screen_pos(b->pos + invert_v(vec_from_angle_v(b->angle)*BULLET_RADIUS/2.f))));
        window.draw(circle);
        if (showRays)
        {
            sf::VertexArray line(sf::Lines, 2);
            line[0].position = vec_to_sfvec2_v(world_to_screen_pos(a->pos));
            line[1].position = vec_to_sfvec2_v(world_to_screen_pos(  a->pos + vec_from_angle_v(a->angle - a->viewWide) * (-10000.f)  ));
            line[0].color = (a->i_agentInAngle) ? sf::Color::Green : sf::Color::Red;
            line[1].color = line[0].color;
            if (a->isAlive)
            {
                window.draw(line);
            }
            line[0].position = vec_to_sfvec2_v(world_to_screen_pos(a->pos));
            line[1].position = vec_to_sfvec2_v(world_to_screen_pos(  a->pos + vec_from_angle_v(a->angle + a->viewWide) * (-10000.f)  ));
            if (a->isAlive)
            {
                window.draw(line);
            }
            line[0].position = vec_to_sfvec2_v(world_to_screen_pos(b->pos));
            line[1].position = vec_to_sfvec2_v(world_to_screen_pos(  b->pos + vec_from_angle_v(b->angle - b->viewWide) * (-10000.f)  ));
            line[0].color = (b->i_agentInAngle) ? sf::Color::Green : sf::Color::Red;
            line[1].color = line[0].color;
            if (b->isAlive)
            {
                window.draw(line);
            }
            line[0].position = vec_to_sfvec2_v(world_to_screen_pos(b->pos));
            line[1].position = vec_to_sfvec2_v(world_to_screen_pos(  b->pos + vec_from_angle_v(b->angle + b->viewWide) * (-10000.f)  ));
            if (b->isAlive)
            {
                window.draw(line);
            }
        }
        circle.setFillColor(sf::Color(255, 155, 55));
        circle.setRadius(BULLET_RADIUS/3.f);
        circle.setOrigin(circle.getRadius(), circle.getRadius());
        for (int i = 0; i < a->bulletNB; ++i)
        {
            circle.setPosition(vec_to_sfvec2_v(world_to_screen_pos(a->bullets[i].pos)));
            window.draw(circle);
        }
        for (int i = 0; i < b->bulletNB; ++i)
        {
            circle.setPosition(vec_to_sfvec2_v(world_to_screen_pos(b->bullets[i].pos)));
            window.draw(circle);
        }

        if (dist_v(screen_to_world_pos(sfvec2_to_vec_v(mousePos)), a->pos) < SCREEN_H/10.f)
        {
            topLeftText(&text);
            text.setFillColor(sf::Color(100, 200, 55));
            text.setPosition(sf::Vector2f(10, 10));
            text.setString("Green");
            window.draw(text);
            text.setPosition(sf::Vector2f(10, 50));
            text.setString("Id : " + std::to_string(a->brain->id));
            window.draw(text);
            text.setPosition(sf::Vector2f(10, 90));
            text.setString("Fitness : " + std::to_string(a->brain->fitness));
            window.draw(text);
            text.setPosition(sf::Vector2f(10, 130));
            text.setString("Age : " + std::to_string(a->brain->generationAge));
            window.draw(text);
            text.setPosition(sf::Vector2f(10, 170));
            text.setString("Max fitness : " + std::to_string(a->brain->maxFitness));
            window.draw(text);
            text.setPosition(sf::Vector2f(10, 210));
            text.setString("Lives : " + std::to_string(a->lives));
            window.draw(text);
        }
        else
        {
            if (dist_v(screen_to_world_pos(sfvec2_to_vec_v(mousePos)), b->pos) < SCREEN_H/10.f)
            {
                topLeftText(&text);
                text.setFillColor(sf::Color(155, 55, 200));
                text.setPosition(sf::Vector2f(10, 10));
                text.setString("Purple");
                window.draw(text);
                text.setPosition(sf::Vector2f(10, 50));
                text.setString("Id : " + std::to_string(b->brain->id));
                window.draw(text);
                text.setPosition(sf::Vector2f(10, 90));
                text.setString("Fitness : " + std::to_string(b->brain->fitness));
                window.draw(text);
                text.setPosition(sf::Vector2f(10, 130));
                text.setString("Age : " + std::to_string(b->brain->generationAge));
                window.draw(text);
                text.setPosition(sf::Vector2f(10, 170));
                text.setString("Max fitness : " + std::to_string(b->brain->maxFitness));
                window.draw(text);
                text.setPosition(sf::Vector2f(10, 210));
                text.setString("Lives : " + std::to_string(b->lives));
                window.draw(text);
            }
        }

        window.display();
    }
    return EXIT_SUCCESS;
}
