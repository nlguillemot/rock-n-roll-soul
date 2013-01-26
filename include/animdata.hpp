#pragma once
#include <string>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>

namespace heart
{
    class AnimSequence
    {
    public:
        AnimSequence(const std::string& sequence_name, int start_frame, int duration)
            : name_(sequence_name), start_(start_frame), duration_(duration) { }
        std::string name() const { return name_; }
        int start() const { return start_; }
        int duration() const { return duration_; }
    private:
        std::string name_;
        int start_;
        int duration_;
    };

    class AnimData
    {
    public:
        AnimData(const std::string& file_name);
        sf::Image& texture();
        int fps() const;
        int total_frames() const;

        const AnimSequence& sequence(const std::string& name) const;
        const AnimSequence* maybe_sequence(const std::string& name) const;

        const sf::Vector2f& point(const std::string& name) const;
        const sf::Vector2f* maybe_point(const std::string& name) const;

        const sf::FloatRect& rect(const std::string& name) const;
        const sf::FloatRect* maybe_rect(const std::string& name) const;

        const float& constant(const std::string& name) const;
        const float* maybe_constant(const std::string& name) const;

        const std::string& string(const std::string& name) const;
        const std::string* maybe_string(const std::string& name) const;

    private:
        void load_texture(const std::string& file_name);
        void load_properties(const std::string& file_name);
        void handle_property(std::string prop, std::istream& property_stream);
        sf::Image texture_;
        int fps_;
        int total_frames_;
        std::vector<AnimSequence> sequences_;
        std::map<std::string,sf::Vector2f> points_;
        std::map<std::string,sf::FloatRect> rects_;
        std::map<std::string,float> constants_;
        std::map<std::string,std::string> strings_;
    };
}
