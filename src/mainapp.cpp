#include "mainapp.hpp"
#include <SFML/Window/Event.hpp>
#include "util.hpp"
#include <cassert>
#include <iostream>

namespace heart
{
    MainApp::MainApp(const sf::VideoMode& mode, const std::string& gametitle):
    window_(mode,gametitle)
    {
        view_ = window_.GetDefaultView();
    }
    MainApp::~MainApp()
    {
    }
    void MainApp::exec()
    {
        window_.SetFramerateLimit(60);
        while(window_.IsOpened())
        {
            poll_events();
            update(1000 * window_.GetFrameTime());
            draw();
        }
    }
    void MainApp::poll_events()
    {
        sf::Event e;
        while(window_.GetEvent(e))
        {
            handle_event(e);
        }   
    }
    void MainApp::handle_event(const sf::Event& e)
    {
        switch(e.Type)
        {
        case sf::Event::Closed:
            window_.Close();
            break;
        default:
            break;
        }
    }
    void MainApp::update(sf::Uint32 dt)
    {
    }
    void MainApp::draw()
    {
        window_.Clear(sf::Color::Black);

        window_.Display();
    }
}
