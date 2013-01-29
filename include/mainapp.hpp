#pragma once
#include <SFML/Graphics.hpp>
#include "scene.hpp"

namespace heart
{
    class MainApp
    {
    public:
        MainApp(const sf::VideoMode& mode, const std::string& gametitle, Scene* first_scene);
        ~MainApp();
        void exec();

        void switch_to_scene(Scene* next_scene);
    private:
        void poll_events();
        void handle_event(const sf::Event& e);
        void update(float dt);
        void draw();

        Scene* current_scene_;

        sf::RenderWindow window_;
    };
} // end namespace heart
