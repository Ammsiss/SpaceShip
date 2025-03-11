#include <raylib.h>

#include <deque>
#include <string_view>

#include "./cinc/Enemy.h"
#include "./cinc/EntityManager.h"
#include "./cinc/Player.h"
#include "./inc/Constants.h"
#include "./inc/Helper.h"
#include "cinc/Bullet.h"
#include "cinc/Exploder.h"

bool menu()
{
    constexpr int headerFontSize{50};
    constexpr std::string_view header{"Space Game"};
    int headerTextSize{MeasureText(header.data(), headerFontSize)};

    constexpr int optionFontSize{30};
    constexpr std::string_view play{"Play"};
    constexpr std::string_view quit{"Quit"};
    int playTextSize{MeasureText(play.data(), optionFontSize)};
    int quitTextSize{MeasureText(quit.data(), optionFontSize)};

    const char *options[]{play.data(), quit.data()};
    const int optionSize[]{playTextSize, quitTextSize};
    int selection{0};

    bool begin{false};
    bool close{false};
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        DrawText(header.data(), (Constants::windowSize / 2) - (headerTextSize / 2), 50, headerFontSize, RED);

        for (std::size_t i{0}, spacing{100}; i < std::size(options); ++i, spacing += 100)
        {
            if (selection == Helper::toI(i))
                DrawText("X", ((Constants::windowSize / 2) - (optionSize[i] / 2) - 30), Helper::toI(spacing) + 50,
                         optionFontSize, BLUE);

            DrawText(options[i], (Constants::windowSize / 2) - (optionSize[i] / 2), Helper::toI(spacing) + 50,
                     optionFontSize, RED);
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

        constexpr std::string_view header{"LOSER!"};
        const int headerTextSize{MeasureText(header.data(), 50)};

        DrawText(header.data(), (Constants::windowSize / 2) - (headerTextSize / 2), (Constants::windowSize / 2) - 25,
                 50, RED);

        EndDrawing();
    }
}

void printDebug()
{
    int enemyCount{ 0 };
    int meteorCount{ 0 };
    int exploderCount{ 0 };
    int enemyBulletCount{ 0 };

    for (const auto& entity : EntityManager::getEntities())
    { 
        if (dynamic_cast<Enemy*>(entity))
        {
            ++enemyCount;
        }
        else if (dynamic_cast<Exploder*>(entity))
        {
            ++exploderCount;
        }
        else if (dynamic_cast<Bullet*>(entity))
        {
            ++enemyBulletCount;
        }
        else
        {
            ++meteorCount;
        }
    }

    DrawText(TextFormat("Enemies: %d", enemyCount), 10, 10, 15, RED);
    DrawText(TextFormat("E Bullets: %d", enemyBulletCount), 10, 30, 15, RED);
    DrawText(TextFormat("Meteors: %d", meteorCount), 10, 50, 15, RED);
    DrawText(TextFormat("Exploders: %d", exploderCount), 10, 70, 15, RED);
}

int main()
{
    InitWindow(1000, 1000, "Space Game");
    SetTargetFPS(60);

    bool play{menu()};

    int score{ 0 };
    if (play)
    {
        Sprite::loadTextures();
        Player player{Vec{500, 500}, 0, 3, 3, BLUE, true, Sprite::Type::player};

        while (!WindowShouldClose())
        {
            BeginDrawing();
            ClearBackground(BLACK);

            const char* scoreText{ TextFormat("SCORE: %d", score) };
            int length{ MeasureText(scoreText, 30) };
            DrawText(scoreText, (Constants::windowSize / 2) - (length / 2), 10, 30, RED);

            //player.updateEntity();
            //player.updateDirection();
            //player.timeToShoot();

            EntityManager::spawnEnemy();
            EntityManager::spawnMeteor();
            EntityManager::spawnExploder();

            for (auto &entity : EntityManager::getEntities())
            {
                entity->updateEntity();
                //player.checkCollision(*entity);

                Enemy *enemy{dynamic_cast<Enemy*>(entity)};
                if (enemy)
                {
                    enemy->timeToShoot(player.getCenter());
                }

                for (auto &bullet : EntityManager::getPlayerBullets())
                {
                    bullet->checkCollision(*entity);
                }
            }

            for (auto &bullet : EntityManager::getPlayerBullets())
            {
                bullet->updateEntity();
            }

            for (auto &particle : EntityManager::getParticles())
            {
                particle->move();
                particle->render(RED);
                particle->offScreen();
            }


            printDebug();
            DrawText(TextFormat("Particles: %d", EntityManager::getParticles().size()), 10, 90, 15, RED);
            
            EntityManager::cleanEntities(score);
            //EntityManager::cleanPlayerBullets();
            EntityManager::cleanParticles();
            EndDrawing();

            if (player.getDead())
            {
                Sprite::cleanTextures();
                break;
            }
        }
    }

    youLose();

    CloseWindow();
}
