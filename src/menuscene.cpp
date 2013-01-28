#include "menuscene.hpp"
#include "gamescene.hpp"
#include "util.hpp"

namespace heart
{

MenuButton::MenuButton(const std::string& style)
{
    anim_data_ = new AnimData("assets/" + style);
    anim_ = new Animation(*anim_data_);

    const sf::Vector2f* orig = anim_->maybe_point("origin");
    if (orig)
    {
        anim_->set_origin(*orig);
    }

    const sf::Vector2f* scale = anim_->maybe_point("scale");
    if (scale)
    {
        anim_->set_scale(*scale);
    }
}

MenuButton::~MenuButton()
{
    delete anim_;
    delete anim_data_;
}

sf::Vector2f MenuButton::position() const
{
    return anim_->position();
}

void MenuButton::set_position(const sf::Vector2f& pos)
{
    anim_->set_position(pos);
}

sf::FloatRect MenuButton::bounds() const
{
    return anim_->anim_rect();
}

sf::FloatRect MenuButton::transformed_bounds() const
{
    return anim_->anim_rect_relative();
}

void MenuButton::update(sf::Uint32 dt)
{
    anim_->update(dt);
}

void MenuButton::draw(sf::RenderTarget& target)
{
    anim_->draw(target);
}

void MenuButton::set_action(const std::function<void()>& action)
{
    action_ = action;
}

const std::function<void()>& MenuButton::action() const
{
    return action_;
}

MenuScene::MenuScene(const std::string& menu_name)
{
    background_data_ = new AnimData("assets/" + menu_name);
    background_ = new Animation(*background_data_);
}

MenuScene::~MenuScene()
{
    delete background_;
    delete background_data_;
}

void MenuScene::handle_event(const sf::Event& e)
{
    if (e.Type == sf::Event::MouseButtonPressed)
    {
        for (MenuButton* b : buttons_)
        {
            sf::FloatRect bds = b->transformed_bounds();
            if (bds.Contains((float)e.MouseButton.X,(float)e.MouseButton.Y))
            {
                b->action()();
                break;
            }
        }
    }
}

void MenuScene::cleanup_buttons()
{
    for (MenuButton * b : buttons_)
    {
        delete b;
    }
    buttons_.clear();
}

void MenuScene::init()
{
    cleanup_buttons();

    sf::Vector2f border(30.0f,30.0f);

    sf::Vector2f b_pos = border;
    float furthest_down = 0;

    const std::string* levelname;
    for (size_t i = 0; ; i++)
    {
        std::string lev = "level" + std::to_string(i);
        if (levelname = background_->maybe_string(lev))
        {
            MenuButton* lev_btn = new MenuButton(*levelname + "icon");
            lev_btn->set_action(
                [this,levelname]()
                {
                    switch_to_next_scene(new GameScene(*levelname));
                });

            sf::FloatRect bds = lev_btn->transformed_bounds();
            if (b_pos.x + bds.GetWidth() > view().GetRect().GetWidth() - border.x)
            {
                b_pos.x = border.x;
                b_pos.y = furthest_down + border.y;
            }

            lev_btn->set_position(b_pos);
            b_pos.x += border.x + bds.GetWidth();

            furthest_down = b_pos.y + bds.GetHeight();
            buttons_.push_back(lev_btn);
        }
        else
        {
            break;
        }
    }
}

void MenuScene::update(sf::Uint32 dt)
{
    background_->update(dt);

    for (MenuButton* b : buttons_)
    {
        b->update(dt);
    }

    set_view(default_view());
}

void MenuScene::draw(sf::RenderTarget& target)
{
    target.Clear(sf::Color::Black);

    sf::Vector2f cam_topleft = view().GetCenter() - view().GetHalfSize();
    sf::Vector2f cam_bounds = view().GetHalfSize() * 2.0f;
    sf::Vector2f bgtile(
            background_->transformed_width(),
            background_->transformed_height());

    for (int j = -1; j <= cam_bounds.y/bgtile.y + 1; j++)
    {
        for (int i = -1; i <= cam_bounds.x/bgtile.x + 1; i++)
        {
            sf::Vector2f tilepos(cam_topleft);
            tilepos.x /= bgtile.x;
            tilepos.y /= bgtile.y;
            tilepos.x = std::floor(tilepos.x) * bgtile.x;
            tilepos.y = std::floor(tilepos.y) * bgtile.y;
            tilepos.x += i * bgtile.x;
            tilepos.y += j * bgtile.y;

            background_->set_position(tilepos);
            background_->draw(target);
        }
    }

    for (MenuButton* b : buttons_)
    {
        b->draw(target);
    }
}

}
