#include "mainapp.hpp"
#include <SFML/Window/Event.hpp>
#include <cassert>
#include <iostream>

namespace heart
{
    MainApp::MainApp(const sf::VideoMode& mode, const std::string& gametitle, Scene* firstscene):
    window_(mode,gametitle),
    current_scene_(firstscene)
    {
        view_ = window_.GetDefaultView();
    }
    MainApp::~MainApp()
    {
        delete current_scene_;
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
    void MainApp::switch_to_scene(Scene* next_scene)
    {
        delete current_scene_;
        current_scene_ = next_scene;
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
        current_scene_->handle_event(e);

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
        current_scene_->update(dt);
    }
    void MainApp::draw()
    {
        current_scene_->draw(window_);

        window_.Display();
    }
}
