#include <raylib.h>

#include <string_view>
#include <deque>

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

void spawnEnemy(double& lastTime, std::deque<Enemy>& enemies)
{
    double currentTime{ GetTime() };
    if (currentTime - lastTime >= 3)
    {
        enemies.emplace_back(Vec{ -200, Random::getReal(100.0f, 900.0f) }, 0, 0, 4);
        lastTime = currentTime;
    }

}

int main()
{
    InitWindow(1000, 1000, "Space Game");
    SetTargetFPS(60);

    bool play{ menu() };

    if (play)
    {
        Player player{ Vec{ 500, 500 }, 0, 3, 4 };
        std::deque<Enemy> enemies{};

        double lastTime{ GetTime() };
        while (!WindowShouldClose()) 
        {
            BeginDrawing();
            ClearBackground(BLACK); 

            // PLAYER
            Helper::updateEntity(player);
            player.updateDirection();
            player.shoot();

            // ENEMY
            spawnEnemy(lastTime, enemies);
            for (auto& enemy : enemies)
            {
                Helper::updateEntity(enemy);
                enemy.timeToShoot(player.getCenter());
            }
            Enemy::shoot();



            EndDrawing();
        }
    }

    CloseWindow();
}
