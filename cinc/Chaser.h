#include "../cinc/Sprite.h"
#include "../cinc/Entity.h"
#include "../cinc/EntityManager.h"

#include "Aggregates.h"
#include "Constants.h"
#include "Random.h"
#include "Helper.h"
#include "cinc/Player.h"

#include <vector>
#include <cmath>

using namespace std;

struct Node {
    int x, y, g, f;
    Node(int x, int y, int g, int f) : x(x), y(y), g(g), f(f) {}
};

// Min-heap priority queue comparator
struct Compare {
    bool operator()(const Node& a, const Node& b) {
        return a.f > b.f;
    }
};

const int GRID_SIZE = 1000;

inline vector<pair<int, int>> directions = {{0,1}, {1,0}, {0,-1}, {-1,0}}; // Right, Down, Left, Up

inline int heuristic(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

inline pair<int, int> get_next_step(int sx, int sy, int gx, int gy) {
    if (sx == gx && sy == gy) return {sx, sy}; // Already at goal

    pair<int, int> bestMove = {sx, sy}; // Default: Stay in place
    int bestH = heuristic(sx, sy, gx, gy);

    for (auto& d : directions) {
        int nx = sx + d.first, ny = sy + d.second;
        if (nx < 0 || ny < 0 || nx >= GRID_SIZE || ny >= GRID_SIZE) continue; // Stay in bounds

        int newH = heuristic(nx, ny, gx, gy); // Calculate new heuristic
        if (newH < bestH) { // Pick the best move (lower heuristic)
            bestMove = {nx, ny};
            bestH = newH;
        }
    }

    return bestMove; // Return the move that brings it closer
}

class Chaser : public Entity
{
public:
    Chaser(Vec center, float angle, float turnSpeed, float speed, Color color, bool goingRight, Sprite::Type textureType)
    : Entity{center, Vec{Constants::enemySize, Constants::enemySize}, angle, turnSpeed, speed, color, goingRight, textureType}
{
    updateHitBox();
}

    void render() override
    {
        float angle{ Random::getReal((m_angle - 180) - 20, (m_angle - 180) + 20) };
        Vec center{Random::getReal(m_center.x - 15, m_center.x + 15), Random::getReal(m_center.y - 15, m_center.y + 15)};
        EntityManager::spawnParticle(center, angle, true, 2, RED);

        DrawTexture(Sprite::getTexture(m_textureType), Helper::toI(m_tl.x), Helper::toI(m_tl.y), WHITE);
    }
 
    void offScreen() override
    {
        if (m_tl.x > Constants::windowSize)
            m_dead = true;
    }

    void collisionLogic() override
    {
        Helper::spawnParticles(RED, m_center);
        m_dead = true;
        m_killedByPlayer = true;
    }

    void move() override
    {
        pair<int, int> nextHop{ get_next_step(Helper::toI(m_center.x), Helper::toI(m_center.y), Helper::toI(center.x), Helper::toI(center.y)) };

        m_center.x = static_cast<float>(nextHop.first);
        m_center.y = static_cast<float>(nextHop.second);

    updateHitBox();
        updateHitBox();
    }

private:
};


