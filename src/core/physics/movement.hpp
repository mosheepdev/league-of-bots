#ifndef MOVEMENT_HPP
#define MOVEMENT_HPP

#include <queue>
#include <vector>
#include "../logic/elements/elem.hpp"

typedef enum MovePriority {
    right_click = 0, own_ability = 1, enemy_ability = 2
} MovePriority;

typedef struct Move {
    Coord start;
    Coord target;
    std::vector<float> unit_travel;
    int distance;
    int travelled;
    MovePriority priority;

    friend bool operator < (const Move& lhs, const Move& rhs);
    friend bool operator > (const Move& lhs, const Move& rhs);

    struct GreaterComparator {
        bool operator() (const Move* lhs, const Move* rhs);
    };
} Move;

class MovePriorityQueue: public std::priority_queue<Move*, std::vector<Move*>, 
        Move::GreaterComparator> {
    public:
        void removeRightClickMove();
        void replaceRightClickMove(Move* move);
};

Move* constructLinearMove(Coord start, Coord target, MovePriority priority);

Move* constructInstantMove(Coord start, Coord target, MovePriority priority);

class MovementManager {
    public:
        MovementManager(Elem* elem, float velocity);
        bool update(float ms);
        void request(Move* move);
        float getVelocity();
        void setVelocity(float velocity);

    private:
        Elem* m_elem;
        MovePriorityQueue m_moves;
        float m_velocity;
};

#endif
