#include "gamescene.hpp"
#include "util.hpp"

#include <iostream>

namespace heart
{

GameScene::GameScene()
{
    background_data_ = new AnimData("assets/background");
    background_ = new Animation(*background_data_);

    player_keys_.left = KeyState(sf::Key::Left);
    player_keys_.right = KeyState(sf::Key::Right);
    player_keys_.up = KeyState(sf::Key::Up);
    player_keys_.down = KeyState(sf::Key::Down);
    player_keys_.action = KeyState(sf::Key::Space);
}

GameScene::~GameScene()
{
    cleanup_world();

    delete background_;
    delete background_data_;
}

void GameScene::init()
{
    init_world();
}

void GameScene::init_world()
{
    cleanup_world();
    player_.reset_state();

    if (!map_.load_from_file("assets/level1.map"))
    {
        std::cout << "Failed to load map." << std::endl;
    }

    const GameMap::SpawnPoint* start_spawn = map_.spawnpoint("start");

    if (start_spawn)
    {
        player_.snap_to_position(start_spawn->position);
    }

    for (std::vector<GameMap::Platform>::const_iterator it = map_.platforms().cbegin(); it != map_.platforms().cend(); ++it)
    {
        Entity* plat = new Entity(it->asset_name);
        plat->snap_to_position(it->position);
        platforms_.push_back(plat);
    }

    for (std::vector<GameMap::GoalFlag>::const_iterator it = map_.goalflags().cbegin(); it != map_.goalflags().cend(); ++it)
    {
        Entity* goal = new Entity(it->asset_name);
        goal->snap_to_position(it->position);
        goalflags_.push_back(goal);
    }

    const GameMap::PhysicsConfiguration& physconf(map_.physics());
    player_.set_gravity_effect(physconf.gravity);
}

void GameScene::cleanup_world()
{
    for (Entity* p : platforms_)
    {
        delete p;
    }
    platforms_.clear();

    for (Entity* g : goalflags_)
    {
        delete g;
    }
    goalflags_.clear();
}

void GameScene::handle_event(const sf::Event& e)
{
    if (e.Type == sf::Event::KeyPressed)
    {
        player_handle_keydown(e.Key.Code);
    }
    else if (e.Type == sf::Event::KeyReleased)
    {
        player_handle_keyup(e.Key.Code);
    }
}

void GameScene::player_handle_keydown(sf::Key::Code code)
{
    if (code == sf::Key::R)
    {
        init_world();
        return;
    }

    if (element_of(player_.state(), states_with_direction_switching))
    {
        if (code == player_keys_.left.key)
        {
            player_.switch_direction(Player::Left);
        }
        else if (code == player_keys_.right.key)
        {
            player_.switch_direction(Player::Right);
        }
    }

    if (player_.state() == PlayerState::Idle)
    {
        if (code == player_keys_.left.key ||
            code == player_keys_.right.key)
        {
            player_.switch_to_state(PlayerState::Moving);
        }
    }

    if (element_of(player_.state(), states_allowing_launching))
    {
        if (code == player_keys_.up.key)
        {
            player_.set_aim_movement(Player::Up);
            player_.begin_aim_movement();
        }
        else if (code == player_keys_.down.key)
        {
            player_.set_aim_movement(Player::Down);
            player_.begin_aim_movement();
        }
        else if (code == player_keys_.action.key)
        {
            player_.switch_to_state(PlayerState::Launching);
        }
    }

    if (code == player_keys_.left.key)
    {
        player_keys_.left.held = true;
    }
    else if (code == player_keys_.right.key)
    {
        player_keys_.right.held = true;
    }
    else if (code == player_keys_.up.key)
    {
        player_keys_.up.held = true;
    }
    else if (code == player_keys_.down.key)
    {
        player_keys_.down.held = true;
    }
    else if (code == player_keys_.action.key)
    {
        player_keys_.action.held = true;
    }
}

void GameScene::player_handle_keyup(sf::Key::Code code)
{
    if (element_of(player_.state(), states_with_direction_switching))
    {
        if (code == player_keys_.left.key &&
            player_.direction() == Player::Left)
        {
            if (player_keys_.right.held)
            {
                player_.switch_direction(Player::Right);
            }
            else if (player_.state() == PlayerState::Moving)
            {
                player_.switch_to_state(PlayerState::Idle);
            }
        }
        else if (code == player_keys_.right.key &&
                player_.direction() == Player::Right)
        {
            if (player_keys_.left.held)
            {
                player_.switch_direction(Player::Left);
            }
            else if (player_.state() == PlayerState::Moving)
            {
                player_.switch_to_state(PlayerState::Idle);
            }
        }
    }

    if (element_of(player_.state(), states_allowing_launching))
    {
        if (code == player_keys_.up.key)
        {
            player_.stop_aim_movement();
        }
        else if (code == player_keys_.down.key)
        {
            player_.stop_aim_movement();
        }
    }

    if (player_.state() == PlayerState::Launching)
    {
        if (code == player_keys_.action.key)
        {
            player_.launch();
        }
    }

    if (code == player_keys_.left.key)
    {
        player_keys_.left.held = false;
    }
    else if (code == player_keys_.right.key)
    {
        player_keys_.right.held = false;
    }
    else if (code == player_keys_.up.key)
    {
        player_keys_.up.held = false;
    }
    else if (code == player_keys_.down.key)
    {
        player_keys_.down.held = false;
    }
    else if (code == player_keys_.action.key)
    {
        player_keys_.action.held = false;
    }
}

void GameScene::update(sf::Uint32 dt)
{
    for (Entity* p : platforms_)
    {
        p->update(dt);
    }

    sf::Vector2f oldfeet(player_.feet_relative());

    PlayerState prev_state = player_.state();

    player_.update(dt);

    PlayerState curr_state = player_.state();

    if (prev_state == PlayerState::Landing &&
        curr_state != prev_state)
    {
        if (player_keys_.left.held || player_keys_.right.held)
        {
            player_.switch_to_state(PlayerState::Moving);
        }
    }

    sf::Vector2f newfeet(player_.feet_relative());

    sf::FloatRect playerbounds(player_.feet_rect());

    sf::Vector2f feetdelta = newfeet - oldfeet;

    bool standing_on_platform = false;

    for (Entity* p : platforms_)
    {
        sf::FloatRect platcoll = p->collision_area();
        sf::Vector2f plattopleft(platcoll.Left,platcoll.Top);
        sf::Vector2f plattopright(platcoll.Right,platcoll.Top);

        float dist = plattopleft.y - newfeet.y;

        float height_ratio;
        if (std::fabs(feetdelta.y) < 0.001f)
        {
            height_ratio = 0;
        }
        else
        {
            height_ratio = (plattopleft.y - oldfeet.y) / feetdelta.y;
        }

        float interpolated_feet = oldfeet.x + feetdelta.x * height_ratio;

        float feetmin = interpolated_feet - playerbounds.GetWidth()/2.0f;
        float feetmax = interpolated_feet + playerbounds.GetWidth()/2.0f;

        float platmin = plattopleft.x;
        float platmax = plattopright.x;

        if ((player_.falling() && newfeet.y >= plattopleft.y &&
            oldfeet.y <= plattopleft.y)) 
        {
            if (intersecting_range(feetmin,feetmax,platmin,platmax))
            {
                player_.land_at_y(plattopleft.y);
                standing_on_platform = true;
                break;
            }
        }
        else if (!standing_on_platform && !player_.in_air())
        {
            if (std::fabs(dist) < 0.01f)
            {

                if (intersecting_range(feetmin,feetmax,platmin,platmax))
                {
                    standing_on_platform = true;
                    break;
                }
            }
        }
    }

    if (!standing_on_platform && !player_.in_air())
    {
        player_.switch_to_state(PlayerState::Falling);
    }

    bool out_of_bounds = true;
    for (Entity* p : platforms_)
    {
        if (vector_magnitude(
            p->position() - player_.position())
            < 1000)
        {
            out_of_bounds = false;
        }
    }

    if (out_of_bounds)
    {
        init_world();
    }

    const sf::View& dft_view = default_view();
    sf::View new_view(
            sf::FloatRect(
                0,0,
                dft_view.GetRect().GetWidth()*2,
                dft_view.GetRect().GetHeight()*2));

    new_view.SetCenter(player_.position());

    set_view(new_view);
}

void GameScene::draw(sf::RenderTarget& target)
{
    target.Clear(sf::Color::White);

    sf::Vector2f cam_topleft = view().GetCenter() - view().GetHalfSize();
    sf::Vector2f cam_bounds = view().GetHalfSize() * 2.0f;

    sf::Vector2f bgtile(
            background_->transformed_width(),
            background_->transformed_height());
    for (int j = -1; j <= cam_bounds.y/bgtile.y; j++)
    {
        for (int i = -1; i <= cam_bounds.x/bgtile.x; i++)
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

    for (Entity* p : platforms_)
    {
        p->draw(target);
    }

    player_.draw(target);
}

}
