#pragma once
#include <SFML/Graphics.hpp>

namespace heart
{
    class MainApp
    {
    public:
        MainApp(const sf::VideoMode& mode, const std::string& gametitle);
        ~MainApp();
        void exec();
    private:
        void poll_events();
        void handle_event(const sf::Event& e);
        void update(sf::Uint32 dt);
        void draw();

        sf::RenderWindow window_;
        sf::View view_;
    };
} // end namespace heart
