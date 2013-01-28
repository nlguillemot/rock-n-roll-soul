#pragma once

#include "scene.hpp"
#include <SFML/Audio.hpp>
#include "animation.hpp"

namespace heart
{

class MenuDecoration
{
public:
    MenuDecoration(const std::string& style);
    virtual ~MenuDecoration();

    virtual sf::Vector2f position() const;
    virtual void set_position(const sf::Vector2f& pos);

    virtual sf::FloatRect bounds() const;
    virtual sf::FloatRect transformed_bounds() const;

    virtual void update(sf::Uint32 dt);
    virtual void draw(sf::RenderTarget& target);
protected:
    Animation* anim_;
    AnimData* anim_data_;
};

class MenuButton : public MenuDecoration
{
public:
    MenuButton(const std::string& style);

    void set_action(const std::function<void()>& action);
    const std::function<void()>& action() const;
private:
    std::function<void()> action_;
};

class MenuScene : public Scene
{
public:
    MenuScene(const std::string& menu_name);
    ~MenuScene();

    void handle_event(const sf::Event& e);

    void init();
    void update(sf::Uint32 dt);
    void draw(sf::RenderTarget& target);
    void exit();
private:
    void init_menu();
    void cleanup_menu();

    Animation* background_;
    AnimData* background_data_;

    std::string menu_name_;

    std::vector<MenuButton*> buttons_;
    std::vector<MenuDecoration*> decorations_;

    sf::Music bgm_;
};

}
