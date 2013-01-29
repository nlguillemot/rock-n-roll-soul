#pragma once

#include <SFML/Graphics.hpp>

namespace heart
{

class Scene
{
public:
    Scene();
    virtual ~Scene(){}

    virtual void handle_event(const sf::Event& e){}

    virtual void init(){}
    virtual void update(float dt){}
    virtual void exit(){}

    virtual void draw(sf::RenderTarget& target){}

    const sf::View& default_view() const;
    void set_default_view(const sf::View& view);

    void set_view(const sf::View& view);
    const sf::View& view() const;
    sf::View& view();

    void switch_to_next_scene(Scene* next);
    Scene* next_scene() const;
private:
    Scene* next_scene_;

    sf::View default_view_;
    sf::View view_;
};

}
