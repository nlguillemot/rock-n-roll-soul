#pragma once
#include <SFML/Graphics.hpp>
#include "animdata.hpp"

namespace heart
{
    class Animation
    {
    public:
        Animation(AnimData& anim_data);
        
        bool playing() const;

        void play(const std::string& sequence_name);
        void play(int frame);

        void hold(const std::string& sequence_name);
        void hold(int frame);

        sf::Vector2f point_relative(const std::string& point_name) const;
        sf::Vector2f point(const std::string& point_name) const;
        
        sf::FloatRect rect_relative(const std::string& rect_name) const;
        sf::FloatRect rect(const std::string& rect_name) const;

        sf::FloatRect anim_rect_relative() const;
        sf::FloatRect anim_rect() const;

        sf::Vector2f center_relative() const;
        sf::Vector2f center() const;

        float constant(const std::string& constant_name) const;

        const std::string& string(const std::string& name) const;
        
        float width() const;
        float height() const;

        sf::Uint32 fps() const;
        void set_fps(sf::Uint32 fps);

        void set_position(const sf::Vector2f& p);
        sf::Vector2f position() const;
        
        void set_alpha(sf::Uint8 a);
        sf::Uint8 alpha() const;

        void set_tint(const sf::Color& color);
        const sf::Color& tint() const;

        // relative to original graphic
        const sf::Vector2f& scale() const;
        // w and h must be positive
        void set_scale(const sf::Vector2f& scale);
        void set_scale(float w, float h);

        void fliph(bool flipped);
        void flipv(bool flipped);

        void update(sf::Uint32 dt);
        void draw(sf::RenderTarget& target);
    private:
        sf::Uint32 frame_to_time(int frame) const;
        void update_sprite_to_frame();
        AnimData& anim_data_;
        sf::Sprite sprite_;
        sf::Uint32 timeline_;
        sf::Uint32 fps_;
        int total_frames_;
        
        // These are used to loop a certain sequence in the animation
        int current_frame_;
        int loop_start_;
        int loop_end_;

        bool playing_;
    };
}
