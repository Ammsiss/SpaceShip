#include <raylib.h>

#include <string_view>
#include <deque>
#include <algorithm>

#include "./cinc/Player.h"
#include "./cinc/Enemy.h"

#include "./inc/Constants.h"
#include "./inc/Helper.h"
#include "./inc/Random.h"

bool menu()
{
    constexpr int headerFontSize{ 50 };
    constexpr std::string_view header{"Space Game"};
    int headerTextSize{ MeasureText(header.data(), headerFontSize) };

    constexpr int optionFontSize{ 30 };
    constexpr std::string_view play{ "Play" };
    constexpr std::string_view quit{ "Quit" };
    int playTextSize{ MeasureText(play.data(), optionFontSize) };
    int quitTextSize{ MeasureText(quit.data(), optionFontSize) };

    const char* options[]{ play.data(), quit.data() };
    const int optionSize[]{ playTextSize, quitTextSize };
    int selection{ 0 };

    bool begin{ false };
    bool close{ false };
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        DrawText(header.data(), (Constants::windowSize / 2) - (headerTextSize / 2), 50, headerFontSize, RED);


        for (std::size_t i{ 0 }, spacing{ 100 }; i < std::size(options); ++i, spacing += 100)
        {
            if (selection == Helper::toI(i))
                DrawText("X", ((Constants::windowSize / 2) - (optionSize[i] / 2) - 30), Helper::toI(spacing) + 50, optionFontSize, BLUE);

            DrawText(options[i], (Constants::windowSize / 2) - (optionSize[i] / 2), Helper::toI(spacing) + 50, optionFontSize, RED);
        }

        if (IsKeyPressed(KEY_W))
            selection = 0;
        else if (IsKeyPressed(KEY_S))
            selection = 1;

        if (IsKeyPressed(KEY_ENTER) && selection == 0)
            begin = true;
        else if (IsKeyPressed(KEY_ENTER) && selection == 1)
            close = true;


        EndDrawing();

        if (begin)
            return true;
        if (close)
            return false;
    }

    return false;
}

void youLose()
{
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        constexpr std::string_view header{ "LOSER!" };
        const int headerTextSize{ MeasureText(header.data(), 50) };

        DrawText(header.data(), (Constants::windowSize / 2) - (headerTextSize / 2), (Constants::windowSize / 2) - 25, 50, RED);

        EndDrawing();
    }
}

Entity* spawnEnemy()
{
    static double lastTime{ GetTime() };

    double currentTime{ GetTime() };
    if (currentTime - lastTime >= 3)
    {
        lastTime = currentTime;
        return new Enemy{ Vec{ -200, Random::getReal(100.0f, 900.0f) }, 0, 0, 4, RED };
    }

    return nullptr;
}

Entity* spawnMeteor()
{
    static double lastTime{ GetTime() };

    double currentTime{ GetTime() };
    if (currentTime - lastTime >= 5)
    {
        lastTime = currentTime;
        return new Entity{ Vec{ -200, Random::getReal(100.0f, 900.0f) }, Vec{ 20, 20 }, 0, 0, 3, BROWN };
    }

    return nullptr;
}

int main()
{
    InitWindow(1000, 1000, "Space Game");
    SetTargetFPS(60);

    bool play{ menu() };

    if (play)
    {
        Player player{ Vec{ 500, 500 }, 0, 3, 4, BLUE };
        std::deque<Entity*> entities{};

        while (!WindowShouldClose()) 
        {
            BeginDrawing();
            ClearBackground(BLACK); 

            player.updateEntity();
            player.updateDirection();
            player.shoot();

            Entity* enemy_ptr{ spawnEnemy() };
            if (enemy_ptr)
                entities.push_back(enemy_ptr);

            Entity* meteor_ptr{ spawnMeteor() };
            if (meteor_ptr)
                entities.push_back(meteor_ptr);

            for (auto& entity : entities)
            {
                entity->updateEntity();
                player.checkCollision(*entity);
                player.hitEntity(*entity);

                Enemy* enemy { dynamic_cast<Enemy*>(entity) };
                if (enemy)
                {
                    enemy->timeToShoot(player.getCenter());
                    enemy->offScreen();
                }
            }
            Enemy::shoot();
            Enemy::hitPlayer(player);

            entities.erase(std::remove_if(entities.begin(), entities.end(), 
                [](const auto& entity)
                {
                    return entity->getDead();
                }
            ), entities.end());
            Enemy::printBullet();

            EndDrawing();
 
            if (player.getDead())
                break;

        }
    }

    youLose();

    CloseWindow();
}
