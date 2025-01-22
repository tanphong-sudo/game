#include "Game.h"
#include <raylib.h>
#include <raymath.h>

Game::Game() : gameState(State::MENU), dungeon(40, 30) {}

Vector2 exitPosition = {700, 500};

void Game::Init() {
    enemyCount = 3;
    currentLevel = 1;
    dungeon.Generate();
    player.Init({400, 300});

    enemyTexture = LoadTexture("assets/sprites/enemy.png");
    SpawnEnemies(enemyCount); 

    playerGold = 0; // Initialize player's gold count
    SpawnGold(10);
}

void Game::NextLevel() {
    currentLevel++;
    enemyCount += 2;

    // Enter the shop 
    inShop = true;
    EnterShop();

    dungeon.Generate();
    player.Init({400, 300});

    SpawnGold(10 + 5 * currentLevel);
    SpawnEnemies(enemyCount);

    // ko spawn ngay tuong
    do {
        exitPosition = {
            static_cast<float>(GetRandomValue(20, 780)),
            static_cast<float>(GetRandomValue(20, 580))
        };
    } while (dungeon.IsWall(exitPosition)); 
}

void Game::EnterShop() {
    int damageUpgradeCost = 20 + (currentLevel * 5); 
    int healthUpgradeCost = 20 + (currentLevel * 5); 

    while (inShop) {
        BeginDrawing();
        ClearBackground(BLACK);

        DrawText("SHOP", 350, 100, 40, YELLOW);
        DrawText(TextFormat("1. Increase Damage (Cost: %d Gold)", damageUpgradeCost), 200, 200, 20, WHITE);
        DrawText(TextFormat("2. Increase Health (Cost: %d Gold)", healthUpgradeCost), 200, 250, 20, WHITE);
        DrawText("Press ENTER to Exit Shop", 200, 300, 20, GRAY);

        DrawText(TextFormat("Gold: %d", playerGold), 10, 10, 20, GOLD);

        EndDrawing();

        if (IsKeyPressed(KEY_ONE) && playerGold >= damageUpgradeCost) {
            playerGold -= damageUpgradeCost;
            player.IncreaseDamage(5);
            damageUpgradeCost += 5;  
        }
        if (IsKeyPressed(KEY_TWO) && playerGold >= healthUpgradeCost) { 
            playerGold -= healthUpgradeCost;
            player.IncreaseHealth(20);
            healthUpgradeCost += 5;  
        }
        if (IsKeyPressed(KEY_ENTER)) { 
            inShop = false;
        }
    }
}

void Game::SpawnGold(int count) {
    for (int i = 0; i < count; i++) {
        Vector2 randomPosition;
        do {
            randomPosition = {
                static_cast<float>(GetRandomValue(20, 780)), 
                static_cast<float>(GetRandomValue(20, 580)) 
            };
        } while (dungeon.IsWall(randomPosition)); 

        goldItems.push_back({randomPosition, false});
    }
}

void Game::SpawnEnemies(int count) {
    for (int i = 0; i < count; i++) {
        Vector2 randomPosition = {
            static_cast<float>(GetRandomValue(50, 750)),
            static_cast<float>(GetRandomValue(50, 550))
        };
        Enemy enemy;
        enemy.Init(randomPosition, enemyTexture);

        int enemyHealth = 50 + (currentLevel * 20); 
        int enemyDamage = 5 + (currentLevel * 2);  

        enemy.SetHealth(enemyHealth);
        enemy.SetDamage(enemyDamage);

        enemies.push_back(enemy);
    }
}

void Game::Update() {
    switch (gameState) {
        case State::MENU:
            UpdateMenu();
            break;
        case State::PLAYING:
            UpdatePlaying();
            break;
        case State::GAME_OVER:
            UpdateGameOver();
            break;
    }
}

void Game::Render() {
    switch (gameState) {
        case State::MENU:
            RenderMenu();
            break;
        case State::PLAYING:
            RenderPlaying();
            break;
        case State::GAME_OVER:
            RenderGameOver();
            break;
    }
}

void Game::UpdateMenu() {
    if (IsKeyPressed(KEY_ENTER)) {
        gameState = State::PLAYING;
    }
}

void Game::RenderMenu() {
    DrawText("DUNGEON OF ETERNITY", 200, 200, 40, RAYWHITE);
    DrawText("Press ENTER to Start", 300, 300, 20, GRAY);
}

void Game::UpdatePlaying() {
    player.Update();

    for (auto& item : goldItems) {
        if (!item.isCollected && Vector2Distance(player.GetPosition(), item.position) < 50.0f) {
            item.isCollected = true;
            playerGold += 20; 
        }
    }

    for (auto& enemy : enemies) {
        if (enemy.IsAlive()) {
            enemy.Update(player.GetPosition());
        }
    }

    for (auto& enemy : enemies) {
        if (enemy.IsAlive() && enemy.CanAttack(player.GetPosition())) {
            player.TakeDamage(enemy.GetDamage()); 
        }
    }

    if (Vector2Distance(player.GetPosition(), exitPosition) < 25.0f) {
        NextLevel();
    }

    if (IsKeyPressed(KEY_SPACE)) {
        for (auto& enemy : enemies) {
            if (enemy.IsAlive() && Vector2Distance(player.GetPosition(), enemy.GetPosition()) < 50.0f) {
                enemy.TakeDamage(player.GetDamage()); 
                break; 
            }
        }
    }
    if (!player.IsAlive()) {
        gameState = State::GAME_OVER;
    }

}


void Game::RenderPlaying() {
    dungeon.Render();
    player.Render();

    for (const auto& enemy : enemies) {
        if (enemy.IsAlive()) {
            enemy.Render();
        }
    }

    for (const auto& item : goldItems) {
        if (!item.isCollected) {
            DrawCircleV(item.position, 10, YELLOW); 
        }
    }

    DrawText(TextFormat("Gold: %d", playerGold), 10, 10, 20, GOLD);
    DrawText(TextFormat("Damage: %d", player.GetDamage()), 10, 40, 20, WHITE);
    DrawText(TextFormat("Health: %d / %d", player.GetHealth(), player.GetMaxHealth()), 10, 70, 20, RED);
    DrawText(TextFormat("Level: %d", currentLevel), 10, 100, 20, WHITE);

    DrawCircleV(exitPosition, 15, GREEN);

}

void Game::UpdateGameOver() {
    if (IsKeyPressed(KEY_R)) {
        gameState = State::MENU;
    }
}

void Game::RenderGameOver() {
    DrawText("GAME OVER", 300, 200, 40, RED);
    DrawText("Press R to Return to Menu", 250, 300, 20, GRAY);
}

