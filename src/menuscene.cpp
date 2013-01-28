#include "menuscene.hpp"
#include "gamescene.hpp"
#include "menulayout.hpp"
#include "util.hpp"

namespace heart
{

MenuDecoration::MenuDecoration(const std::string& style)
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

MenuDecoration::~MenuDecoration()
{
    delete anim_;
    delete anim_data_;
}

sf::Vector2f MenuDecoration::position() const
{
    return anim_->position();
}

void MenuDecoration::set_position(const sf::Vector2f& pos)
{
    anim_->set_position(pos);
}

sf::FloatRect MenuDecoration::bounds() const
{
    return anim_->anim_rect();
}

sf::FloatRect MenuDecoration::transformed_bounds() const
{
    return anim_->anim_rect_relative();
}

void MenuDecoration::update(sf::Uint32 dt)
{
    anim_->update(dt);
}

void MenuDecoration::draw(sf::RenderTarget& target)
{
    anim_->draw(target);
}

MenuButton::MenuButton(const std::string& style):
MenuDecoration(style)
{
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

    menu_name_ = menu_name;
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

void MenuScene::init_menu()
{
    cleanup_menu();

    MenuLayout layout;
    if (!layout.load_from_file("menu/" + menu_name_))
    {
        std::cout << "Failed to load menu: " << menu_name_ << std::endl;
        return;
    }

    for (std::vector<MenuLayout::LevelButton>::const_iterator it = layout.levelbuttons().cbegin(); it != layout.levelbuttons().cend(); ++it)
    {
        MenuButton* b = new MenuButton(it->level_icon);
        std::string levelname = it->level_name;
        b->set_action(
            [this,levelname]()
            {
                switch_to_next_scene(new GameScene(levelname));
            });
        b->set_position(it->position);
        buttons_.push_back(b);
    }

    for (std::vector<MenuLayout::Decoration>::const_iterator it = layout.decorations().cbegin(); it != layout.decorations().cend(); ++it)
    {
        MenuDecoration* d = new MenuDecoration(it->asset_name);
        d->set_position(it->position);
        decorations_.push_back(d);
    }
}

void MenuScene::cleanup_menu()
{
    for (MenuButton * b : buttons_)
    {
        delete b;
    }
    for (MenuDecoration * d : decorations_)
    {
        delete d;
    }
    decorations_.clear();
}

void MenuScene::init()
{
    init_menu();

    bgm_.OpenFromFile("sound/gamebgm.wav");
    bgm_.Play();
}

void MenuScene::update(sf::Uint32 dt)
{
    background_->update(dt);

    for (MenuDecoration* d : decorations_)
    {
        d->update(dt);
    }

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

    for (MenuDecoration* d : decorations_)
    {
        d->draw(target);
    }

    for (MenuButton* b : buttons_)
    {
        b->draw(target);
    }
}

void MenuScene::exit()
{
    bgm_.Stop();
}

}
