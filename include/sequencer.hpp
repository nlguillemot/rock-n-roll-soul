#pragma once
#ifndef POULP_SEQUENCER_H
#define POULP_SEQUENCER_H

#include <queue>
#include <memory>
#include <SFML/Config.hpp>

namespace heart
{
// ----------------
// SEQUENCER ITEM
// ----------------
    class SequencerItem
    {
    public:
        SequencerItem();
        virtual ~SequencerItem(){}

        virtual void init(){}
        virtual void update(sf::Uint32 dt){}
        virtual void exit(){}
    
        bool complete() const;
    protected:
        void set_complete(bool state);
    private:
        bool complete_;
    };
// ----------------
// SEQUENCER
// ----------------
    class Sequencer
    {
    public:
        Sequencer();
        void append(const std::shared_ptr<SequencerItem>& item);
        void append(const std::vector<std::shared_ptr<SequencerItem>>& items);
        void update(sf::Uint32 dt);
        bool empty() const;
    private:
        void update_front(sf::Uint32 dt);
        std::queue<std::shared_ptr<SequencerItem>> item_queue_;
        bool active_;
    };
}

#endif
