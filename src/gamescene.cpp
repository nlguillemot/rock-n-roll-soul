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
        Platform* plat = new Platform(it->asset_name);
        plat->snap_to_position(it->position);
        platforms_.push_back(plat);
    }
}

void GameScene::cleanup_world()
{
    for (Platform* p : platforms_)
    {
        delete p;
    }
    platforms_.clear();
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
    for (Platform* p : platforms_)
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

    for (Platform* p : platforms_)
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


    const sf::View& dft_view = default_view();
    sf::View new_view(
            sf::FloatRect(
                0,0,
                dft_view.GetRect().GetWidth(),
                dft_view.GetRect().GetHeight()));

    new_view.SetCenter(player_.position());

    set_view(new_view);
}

void GameScene::draw(sf::RenderTarget& target)
{
    target.Clear(sf::Color::White);

    background_->draw(target);

    for (Platform* p : platforms_)
    {
        p->draw(target);
    }

    player_.draw(target);
}

}
