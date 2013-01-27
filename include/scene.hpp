#pragma once
#include <SFML/Graphics.hpp>

namespace heart
{

class MainApp;

class Scene
{
public:
    virtual ~Scene(){}

    virtual void handle_event(const sf::Event& e){}

    virtual void init(){}
    virtual void update(sf::Uint32 dt){}
    virtual void exit(){}

    virtual void draw(sf::RenderTarget& target){}

    const sf::View& default_view() const;
    void set_default_view(const sf::View& view);

    void set_view(const sf::View& view);
    const sf::View& view() const;
    sf::View& view();
private:
    sf::View default_view_;
    sf::View view_;
};

}
