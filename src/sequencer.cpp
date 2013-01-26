#include "sequencer.hpp"

namespace heart
{
    SequencerItem::SequencerItem():
    complete_(false)
    {
    }
    bool SequencerItem::complete() const
    {
        return complete_;
    }
    void SequencerItem::set_complete(bool state)
    {
        complete_ = state;
    }
    Sequencer::Sequencer()
        : active_(false)
    {
    }
    void Sequencer::append(const SequencerItem::pointer& item)
    {
        item_queue_.push(item);
    }
    void Sequencer::append(const std::vector<SequencerItem::pointer>& items)
    {
        for(unsigned i = 0; i < items.size(); ++i)
        {
            item_queue_.push(items[i]);
        }
    }
    void Sequencer::update(sf::Uint32 dt)
    {
        // only update if not empty
        if(!item_queue_.empty())
        {
            // if it's not active, it might need to be activated.
            if(active_)
            {
                update_front(dt);
            }
            else
            {
                active_ = true;
                item_queue_.front()->init();
                update_front(dt);
            }
        }
    }
    bool Sequencer::empty() const
    {
        return item_queue_.empty();
    }
    void Sequencer::update_front(sf::Uint32 dt)
    {
        item_queue_.front()->update(dt);
        // if item is complete, exit it and process the next one
        if(item_queue_.front()->complete())
        {
            item_queue_.front()->exit();
            item_queue_.pop();
            if(item_queue_.empty())
            {
                active_ = false;
            }
            else
            {
                item_queue_.front()->init();
            }
        }
    }
}
