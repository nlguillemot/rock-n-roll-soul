#pragma once

#include <SFML/Graphics.hpp>
#include "animdata.hpp"

namespace heart
{

class Animation
{
public:
    Animation(const AnimData& anim_data);
    
    bool playing() const;

    void play(const std::string& sequence_name, bool looping=true);
    void play(int frame, bool looping);

    void hold(const std::string& sequence_name);
    void hold(int frame);

    // returns -1 if not found
    int sequence_frame(const std::string& sequence_name) const;
    
    // returns -1 if not found
    int sequence_duration(const std::string& sequence_name) const;

    bool has_sequence(const std::string& sequence_name) const;

    sf::Vector2f point_relative(const std::string& point_name) const;
    sf::Vector2f* maybe_point_relative(sf::Vector2f& dst, const std::string& point_name) const;
    sf::Vector2f point(const std::string& point_name) const;
    const sf::Vector2f* maybe_point(const std::string& point_name) const;
    
    sf::FloatRect rect_relative(const std::string& rect_name) const;
    sf::FloatRect rect(const std::string& rect_name) const;
    const sf::FloatRect* maybe_rect(const std::string& rect_name) const;

    sf::FloatRect anim_rect_relative() const;
    sf::FloatRect anim_rect() const;

    sf::Vector2f center_relative() const;
    sf::Vector2f center() const;

    float constant(const std::string& constant_name) const;
    const float* maybe_constant(const std::string& constant_name) const;

    const std::string& string(const std::string& name) const;
    const std::string* maybe_string(const std::string& name) const;
    
    float original_width() const;
    float original_height() const;
    sf::Vector2f original_size() const;

    float transformed_width() const;
    float transformed_height() const;
    sf::Vector2f transformed_size() const;

    sf::Uint32 fps() const;
    void set_fps(sf::Uint32 fps);

    void set_position(const sf::Vector2f& p);
    void move(const sf::Vector2f& v);
    sf::Vector2f position() const;
    
    void set_rotation(float degrees);
    void rotate(float degrees);
    float rotation() const;

    void set_alpha(sf::Uint8 a);
    sf::Uint8 alpha() const;

    void set_tint(const sf::Color& color);
    const sf::Color& tint() const;

    // relative to original graphic
    const sf::Vector2f& scale() const;
    // w and h must be positive
    void set_scale(const sf::Vector2f& scale);
    void set_scale(float w, float h);

    // vector from (0,0) to (1,1)
    // where (0,0) is top left, (1,1) is bottom right
    void set_origin(const sf::Vector2f& origin);
    const sf::Vector2f& origin() const;
    sf::Vector2f original_pixel_origin() const;
    sf::Vector2f transformed_pixel_origin() const;

    void fliph(bool flipped);
    void flipv(bool flipped);

    void set_hidden(bool hidden);
    bool hidden() const;

    void set_looping(bool looping);
    bool looping() const;

    void update(float dt);
    void draw(sf::RenderTarget& target);

    const AnimData& animdata() const;
private:
    float frame_to_time(int frame) const;
    void update_sprite_to_frame();
    const AnimData& anim_data_;
    sf::Sprite sprite_;
    float timeline_;
    sf::Uint32 fps_;
    int total_frames_;
    
    // These are used to loop a certain sequence in the animation
    int current_frame_;
    int loop_start_;
    int loop_duration_;

    bool playing_;

    void update_origin();
    sf::Vector2f origin_;

    bool hidden_;
    
    bool looping_;
};

}
