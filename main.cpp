#include <raylib.h>

#include <string_view>
#include <deque>
#include <algorithm>

#include "./Player/Player.h"
#include "./Enemy/Enemy.h"
#include "./Entity/Entity.h"

#include "./inc/Constants.h"
#include "./inc/Aggregates.h"
#include "./inc/Random.h"

int toI(float value)
{
    return static_cast<int>(value);
}

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
            if (selection == toI(i))
                DrawText("X", ((Constants::windowSize / 2) - (optionSize[i] / 2) - 30), toI(spacing) + 50, optionFontSize, BLUE);

            DrawText(options[i], (Constants::windowSize / 2) - (optionSize[i] / 2), toI(spacing) + 50, optionFontSize, RED);
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

int main()
{
    InitWindow(1000, 1000, "Space Game");
    SetTargetFPS(60);

    bool play = menu();

    Player player{ Vec{ 500, 500 }, 0, 3.0f, 3 };

    std::deque<Enemy> enemies
    { 
        Enemy{ Vec{ -50, static_cast<float>(Random::getInt(100, 900)) }, -0.5, 0, 4 }
    };

    bool dead{ false };
    double lastTimeEnemy{ GetTime() };
    while (play && !WindowShouldClose()) 
    {
        
        BeginDrawing();
        ClearBackground(BLACK);

        player.updateDirection();
        player.move();
        player.render();

        for (auto& enemy : enemies)
        {
            if (player.checkCollision(enemy.getTl(), enemy.getBr()) || player.offScreen() || player.getDead())
            {
                dead = true;
            }
        }
         
        player.timeToShoot();
        player.shoot();

        for (auto& enemy: enemies)
        {
            player.hitEnemy(enemy);
            enemy.hitPlayer(player);
            enemy.move();
            enemy.render();

            enemy.timeToShoot(player.getCenter());
        }
        enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
            [](const auto& enemy)
            {
                if (enemy.offScreen() || enemy.getDead())
                    return true;
                return false;
            }
        ), enemies.end());
        DrawText(TextFormat("%d", enemies.size()), 20, 50, 20, RED);

        Enemy::shoot();
 
        double currentTime{ GetTime() };
        if (currentTime - lastTimeEnemy >= 1)
        {
            enemies.emplace_back(Vec{ -50, static_cast<float>(Random::getInt(100, 900)) }, (Random::getInt(0, 1)) ? Random::getReal(0.0f, 45.0f) : Random::getReal(315.0f, 360.0f), 0, 4);
            lastTimeEnemy = currentTime;
        }

        EndDrawing();

        if (dead)
            break;
    }

    youLose();

    CloseWindow();
}
