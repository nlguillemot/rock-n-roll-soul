#pragma once

#include "scene.hpp"
#include "animation.hpp"

namespace heart
{

class MenuButton
{
public:
    MenuButton(const std::string& style);
    ~MenuButton();

    sf::Vector2f position() const;
    void set_position(const sf::Vector2f& pos);

    sf::FloatRect bounds() const;
    sf::FloatRect transformed_bounds() const;

    void update(sf::Uint32 dt);
    void draw(sf::RenderTarget& target);

    void set_action(const std::function<void()>& action);
    const std::function<void()>& action() const;
private:
    Animation* anim_;
    AnimData* anim_data_;

    std::function<void()> action_;
};

class MenuScene : public Scene
{
public:
    MenuScene();
    ~MenuScene();
    void handle_event(const sf::Event& e);

    void init();
    void update(sf::Uint32 dt);
    void draw(sf::RenderTarget& target);
private:
    void cleanup_buttons();

    Animation* background_;
    AnimData* background_data_;

    std::vector<MenuButton*> buttons_;
};

}
