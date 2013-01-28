#include "gamescene.hpp"
#include "util.hpp"
#include "menuscene.hpp"

#include <iostream>

namespace heart
{

GameScene::GameScene(const std::string& level)
{
    background_data_ = new AnimData("assets/background");
    background_ = new Animation(*background_data_);

    player_keys_.left = KeyState(sf::Key::Left);
    player_keys_.right = KeyState(sf::Key::Right);
    player_keys_.up = KeyState(sf::Key::Up);
    player_keys_.down = KeyState(sf::Key::Down);
    player_keys_.action = KeyState(sf::Key::Space);

    level_name_ = level;
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
    update_camera();

    bgm_.OpenFromFile("sound/gamebgm.wav");
    collectsndbuf_.LoadFromFile("sound/collect.wav");
    collectsnd_.SetBuffer(collectsndbuf_);

    bgm_.Play();
}

void GameScene::update_explosions(sf::Uint32 dt)
{
    for (std::list<Explosion>::iterator it = explosions_.begin();
        it != explosions_.end(); )

    {
        if (it->done())
        {
            auto next = it;
            ++next;
            explosions_.erase(it);
            it = next;
        }
        else
        {
            it->update(dt);
            ++it;
        }
    }
}

void GameScene::explode(Entity* e)
{
    explosions_.push_back(Explosion(e->animation(), e->position(), 100.0f, 200.0f));
    e->animation()->set_hidden(true);
    collectsnd_.Play();
}

void GameScene::init_world()
{
    cleanup_world();
    player_.reset_state();

    if (!map_.load_from_file("level/" + level_name_))
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

    for (std::vector<GameMap::Collectible>::const_iterator it = map_.collectibles().cbegin(); it != map_.collectibles().cend(); ++it)
    {
        Entity* coll = new Entity(it->asset_name);
        coll->snap_to_position(it->position);
        collectibles_.push_back(coll);
    }

    for (std::vector<GameMap::Decoration>::const_iterator it = map_.decorations().cbegin(); it != map_.decorations().cend(); ++it)
    {
        Entity* dec = new Entity(it->asset_name);
        dec->snap_to_position(it->position);
        decorations_.push_back(dec);
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

    for (Entity* c : collectibles_)
    {
        delete c;
    }
    collectibles_.clear();

    for (Entity* d : decorations_)
    {
        delete d;
    }
    decorations_.clear();

    explosions_.clear();
}

void GameScene::handle_event(const sf::Event& e)
{
    if (e.Type == sf::Event::KeyPressed)
    {
        if (e.Key.Code == sf::Key::M || e.Key.Code == sf::Key::Escape)
        {
            switch_to_next_scene(new MenuScene("mainmenu"));
        }
        else
        {
            player_handle_keydown(e.Key.Code);
        }
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

    if (element_of(player_.state(), states_allowing_aiming))
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
    }
    if (element_of(player_.state(), states_allowing_launching))
    {
        if (code == player_keys_.action.key)
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

    if (element_of(player_.state(), states_allowing_aiming))
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
    else
    {
        player_.stop_aim_movement();
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
    for (Entity* d : decorations_)
    {
        d->update(dt);
    }

    for (Entity* p : platforms_)
    {
        p->update(dt);
    }

    for (Entity* g : goalflags_)
    {
        g->update(dt);
    }

    update_explosions(dt);

    for (Entity* c : collectibles_)
    {
        c->update(dt);

        sf::FloatRect bbox(c->collision_area());
        if (!c->animation()->hidden() &&
            bbox.Intersects(player_.collision_area()))
        {
            explode(c);
        }
    }

    update_player(dt);

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

    update_camera();
}

void GameScene::update_camera()
{
    const sf::View& dft_view = default_view();
    float viewwidth = dft_view.GetRect().GetWidth()*2;
    float viewheight = dft_view.GetRect().GetHeight()*2;

    if (player_.state() == PlayerState::Winning)
    {
        viewwidth = player_.bounding_box().GetWidth()*2;
        viewheight = player_.bounding_box().GetHeight()*2;
    }

    sf::View new_view(
            sf::FloatRect(
                0,0,
                viewwidth,
                viewheight));

    sf::FloatRect player_bbox = player_.bounding_box();
    sf::Vector2f pbbox_c = rect_center(player_bbox);
    new_view.SetCenter(pbbox_c);

    set_view(new_view);
}

void GameScene::update_player(sf::Uint32 dt)
{
    sf::Vector2f oldfeet(player_.feet_relative());

    PlayerState prev_state = player_.state();

    player_.update(dt);

    PlayerState curr_state = player_.state();

    if (curr_state == PlayerState::Winning)
    {
        return;
    }

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

    for (Entity* g : goalflags_)
    {
        sf::FloatRect goalcoll = g->collision_area();
        if (segment_intersects_rectangle(goalcoll,
            oldfeet, newfeet))
        {
            player_.switch_to_state(PlayerState::Winning);
            return;
        }
    }

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
}

void GameScene::draw(sf::RenderTarget& target)
{
    target.Clear(sf::Color::White);

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

    for (Entity* d : decorations_)
    {
        d->draw(target);
    }

    for (Explosion& e : explosions_)
    {
        e.draw(target);
    }

    for (Entity* p : platforms_)
    {
        p->draw(target);
    }

    for (Entity* g : goalflags_)
    {
        g->draw(target);
    }

    for (Entity* c : collectibles_)
    {
        c->draw(target);
    }

    player_.draw(target);
}

void GameScene::exit()
{
    bgm_.Stop();
}

}
