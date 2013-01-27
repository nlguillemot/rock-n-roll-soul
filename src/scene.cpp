#include "scene.hpp"

namespace heart
{

Scene::Scene()
{
    next_scene_ = nullptr;
}

const sf::View& Scene::default_view() const
{
    return default_view_;
}

void Scene::set_default_view(const sf::View& view)
{
    default_view_ = view;
}

void Scene::set_view(const sf::View& view)
{
    view_ = view;
}

const sf::View& Scene::view() const
{
    return view_;
}

sf::View& Scene::view()
{
    return view_;
}

void Scene::switch_to_next_scene(Scene* next)
{
    next_scene_ = next;
}

Scene* Scene::next_scene() const
{
    return next_scene_;
}

}
