#include <raylib.h>

#include <deque>
#include <string_view>
#include <string>

#include "./cinc/Enemy.h"
#include "./cinc/EntityManager.h"
#include "./cinc/Player.h"
#include "./inc/Constants.h"
#include "./inc/Helper.h"
#include "cinc/Bullet.h"
#include "cinc/Exploder.h"
#include "cinc/Chaser.h"

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

void youLose(int score)
{
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        constexpr std::string_view header{"LOSER!"};
        const int headerTextSize{MeasureText(header.data(), 50)};
        std::string scoreText{ "SCORE: " + std::to_string(score) };
        const int scoreTextSize{ MeasureText(scoreText.data(), 50) };

        DrawText(TextFormat("SCORE: %d", score), (Constants::windowSize / 2) - (scoreTextSize / 2), 220, 50, RED);
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
    int chaserCount{ 0 };

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
        else if (dynamic_cast<Chaser*>(entity))
        {
            ++chaserCount;
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
    DrawText(TextFormat("Chasers: %d", chaserCount), 10, 110, 15, RED);
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

        InitAudioDevice();
        Sound shoot{ LoadSound("/Users/ammsiss/Projects/SpaceShip/sounds/shoot.wav") };
        Sound explosion{ LoadSound( "/Users/ammsiss/Projects/SpaceShip/sounds/explosion.wav") };
        SetSoundVolume(shoot, 0.50f);
        SetSoundVolume(explosion, 0.50f);

        while (!WindowShouldClose())
        {
            BeginDrawing();
            ClearBackground(BLACK);

            const char* scoreText{ TextFormat("SCORE: %d", score) };
            int length{ MeasureText(scoreText, 30) };
            DrawText(scoreText, (Constants::windowSize / 2) - (length / 2), 10, 30, RED);

            for (auto &particle : EntityManager::getParticles())
            {
                particle->move();
                particle->renderParticle();
                particle->offScreen();
            }

            for (auto &bullet : EntityManager::getPlayerBullets())
            {
                bullet->updateEntity();
            }

            player.updateEntity();
            player.updateDirection();
            player.timeToShoot(shoot);
            player.updateLocation();

            EntityManager::spawnEnemy();
            EntityManager::spawnMeteor();
            EntityManager::spawnExploder();
            EntityManager::spawnChaser();

            for (auto &entity : EntityManager::getEntities())
            {
                entity->updateEntity();
                player.checkCollision(*entity, explosion);
                Enemy *enemy{dynamic_cast<Enemy*>(entity)};
                if (enemy)
                {
                    enemy->timeToShoot(player.getCenter());
                }

                for (auto &bullet : EntityManager::getPlayerBullets())
                {
                    bullet->checkCollision(*entity, explosion);
                }
            }

            printDebug();
            DrawText(TextFormat("Particles: %d", EntityManager::getParticles().size()), 10, 90, 15, RED);

            EntityManager::cleanEntities(score);
            EntityManager::cleanPlayerBullets();
            EntityManager::cleanParticles();
            EndDrawing();

            if (player.getDead())
            {
                static int countDown{ 60 };

                --countDown; 
                if (countDown <= 0)
                {
                    Sprite::cleanTextures();
                    break;
                }
            }
        }
    }

    youLose(score);

    CloseWindow();
}
