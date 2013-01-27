#include "animdata.hpp"
#include <fstream>
#include <sstream>
#include <cassert>
#include <algorithm>
#include <iostream>

namespace heart
{

AnimData::AnimData(const std::string& file_name)
    : fps_(1),
    total_frames_(1)
{
    load_texture(file_name);
    load_properties(file_name);
}

void AnimData::load_texture(const std::string& file_name)
{
    bool found = texture_.LoadFromFile(file_name + ".png");
    if (!found)
    {
        std::cout << "Failed to load " << file_name << ".png" << std::endl;
        return;
    }

    texture_.SetSmooth(false);
}

void AnimData::load_properties(const std::string& file_name)
{
    std::ifstream file(file_name + ".anim");
    
    if (!file)
    {
        return;
    }

    for (;;)
    {
        std::string current_line;
        std::getline(file,current_line);

        int hashtagpos = current_line.find('#');
        if (hashtagpos != std::string::npos)
        {
            current_line = current_line.substr(hashtagpos+1);
        }

        if (!current_line.empty())
        {
            std::istringstream line_stream(current_line);
            std::string property_name;

            line_stream >> property_name;
            handle_property(property_name,line_stream);
        }

        if (file.eof())
        {
            break;
        }
        else if (file.bad())
        {
            assert(false);
            break;
        }
    }
}

void AnimData::handle_property(std::string prop, std::istream& property_stream)
{
    if (prop == "frames")
    {
        property_stream >> total_frames_;
    }
    else if (prop == "fps")
    {
        property_stream >> fps_;
    }
    else if (prop == "sequence")
    {
        std::string sequence_name;
        int start_index = 0, duration = 0;
        property_stream >> sequence_name;
        assert(!sequence_name.empty());
        property_stream >> start_index;
        property_stream >> duration;
        sequences_.push_back(AnimSequence(sequence_name,start_index,duration));
    }
    else if (prop == "point")
    {
        std::string point_name;
        float point_x = 0, point_y = 0;
        property_stream >> point_name;
        assert(!point_name.empty());
        property_stream >> point_x;
        property_stream >> point_y;
        points_[point_name] = sf::Vector2f(point_x,point_y);
    }
    else if (prop == "rect")
    {
        std::string rect_name;
        sf::FloatRect rect;
        property_stream >> rect_name;
        assert(!rect_name.empty());
        property_stream >> rect.Left;
        property_stream >> rect.Top;
        float myWidth, myHeight;
        property_stream >> myWidth;
        property_stream >> myHeight;
        rect.Right = rect.Left + myWidth;
        rect.Bottom = rect.Top + myHeight;
        rects_[rect_name] = rect;
    }
    else if (prop == "constant")
    {
        std::string constant_name;
        float value(0.0f);
        property_stream >> constant_name;
        property_stream >> value;
        constants_[constant_name] = value;
    }
    else if (prop == "string")
    {
        std::string string_name;
        std::string string_value;
        property_stream >> string_name;
        property_stream >> string_value;
        strings_[string_name] = string_value;
    }
}

sf::Image& AnimData::texture()
{
    return texture_;
}

int AnimData::fps() const
{
    return fps_;
}

int AnimData::total_frames() const
{
    return total_frames_;
}

const AnimSequence& AnimData::sequence(const std::string& name) const
{
    return *maybe_sequence(name);
}

const AnimSequence* AnimData::maybe_sequence(const std::string& name) const
{
    std::vector<AnimSequence>::const_iterator it = 
        std::find_if(sequences_.begin(),sequences_.end(),
        [name](const AnimSequence& curr){ return curr.name() == name; }
    );
    
    if (it == sequences_.end())
    {
        return nullptr;
    }
    else
    {
        return &(*it);
    }
}

const sf::Vector2f& AnimData::point(const std::string& name) const
{
    const sf::Vector2f* pt = maybe_point(name);
    assert(pt != nullptr);
    return *pt;
}

const sf::Vector2f* AnimData::maybe_point(const std::string& name) const
{
    std::map<std::string,sf::Vector2f>::const_iterator it =
        points_.find(name);
    if (it == points_.end())
    {
        return nullptr;
    }
    else
    {
        return &it->second;
    }
}

const sf::FloatRect& AnimData::rect(const std::string& name) const
{
    const sf::FloatRect* r = maybe_rect(name);
    assert(r);
    return *r;
}

const sf::FloatRect* AnimData::maybe_rect(const std::string& name) const
{
    std::map<std::string,sf::FloatRect>::const_iterator it =
        rects_.find(name);
    if (it != rects_.end())
    {
        return &it->second;
    }
    else
    {
        return 0;
    }
}

const float& AnimData::constant(const std::string& name) const
{
    const float* c = maybe_constant(name);
    assert(c);
    return *c;
}

const float* AnimData::maybe_constant(const std::string& name) const
{
    std::map<std::string,float>::const_iterator it = constants_.find(name);
    if (it == constants_.end())
    {
        return 0;
    }
    else
    {
        return &it->second;
    }
}

const std::string& AnimData::string(const std::string& name) const
{
    const std::string* s = maybe_string(name);
    assert(s);
    return *s;
}

const std::string* AnimData::maybe_string(const std::string& name) const
{
    std::map<std::string,std::string>::const_iterator it =
        strings_.find(name);
    if (it == strings_.end())
    {
        return 0;
    }
    else
    {
        return &it->second;
    }
}

}
