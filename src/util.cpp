#include "util.hpp"

namespace heart
{
    FunctionSeqItem::FunctionSeqItem(const std::function<void ()>& f):
    f_(f)
    {
    }
    void FunctionSeqItem::init()
    {
        f_();
        set_complete(true);
    }

    ColorTweenSeqItem::ColorTweenSeqItem(const sf::Color& start, const sf::Color& end, sf::Color& current, sf::Uint32 duration):
    start_(start),
    end_(end),
    current_(current),
    duration_(duration),
    time_accumulator_(0)
    {
    }
    void ColorTweenSeqItem::init()
    {
        current_ = start_;
    }
    void ColorTweenSeqItem::update(sf::Uint32 dt)
    {
        time_accumulator_ += dt;

        if (time_accumulator_ > duration_)
        {
            set_complete(true);
        }
        else
        {
            current_ = color_LERP(start_,end_,static_cast<float>(time_accumulator_)/duration_);
        }
    }
    void ColorTweenSeqItem::exit()
    {
        current_ = end_;
    }

    DrawableColorTweenSeqItem::DrawableColorTweenSeqItem(const sf::Color& start, const sf::Color& end, sf::Uint32 duration, sf::Drawable& tweened):
    tweened_(tweened)
    {
        fade_seq_.append(
            std::make_shared<ColorTweenSeqItem>(start,end,color_,duration));
    }
    void DrawableColorTweenSeqItem::update(sf::Uint32 dt)
    {
        fade_seq_.update(dt);

        tweened_.SetColor(color_);

        if (fade_seq_.empty())
        {
            set_complete(true);
        }
    }

    ScopedSequenceSeqItem::ScopedSequenceSeqItem(const std::function<void ()>& on_start, const std::function<void ()>& on_end):
    on_start_(on_start),
    on_end_(on_end)
    {
    }
    void ScopedSequenceSeqItem::append(const SequencerItem::pointer& item)
    {
        sequencer_.append(item);
    }
    void ScopedSequenceSeqItem::init()
    {
        on_start_();
    }
    void ScopedSequenceSeqItem::update(sf::Uint32 dt)
    {
        if (sequencer_.empty())
        {
            set_complete(true);
        }
        else
        {
            sequencer_.update(dt);
        }
    }
    void ScopedSequenceSeqItem::exit()
    {
        on_end_();
    }

    WaitUntilSeqItem::WaitUntilSeqItem(const std::function<bool ()>& cond):
    cond_(cond)
    {
    }
    void WaitUntilSeqItem::init()
    {
        if (cond_())
        {
            set_complete(true);
        }
    }
    void WaitUntilSeqItem::update(sf::Uint32 dt)
    {
        if (cond_())
        {
            set_complete(true);
        }
    }
}
