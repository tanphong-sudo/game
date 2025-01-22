#include "Player.h"
#include <raylib.h>
#include "Utility.h"

Player::Player()
    : position({0, 0}), speed(290.0f), health(100), damage(20), maxHealth(100), gold(0), experience(0) {}

void Player::Init(Vector2 startPosition) {
    position = startPosition;
    sprite = LoadTexture("assets/sprites/player.png");
    TraceLog(LOG_INFO, "Player initialized at (%.2f, %.2f)", position.x, position.y);
}

void Player::TakeDamage(int amount) {
    health -= amount;
    if (health < 0) health = 0;
}

bool Player::IsAlive() const {
    return health > 0;
}

void Player::Update() {
    if (IsKeyDown(KEY_W)) position.y -= speed * GetFrameTime();
    if (IsKeyDown(KEY_S)) position.y += speed * GetFrameTime();
    if (IsKeyDown(KEY_A)) position.x -= speed * GetFrameTime();
    if (IsKeyDown(KEY_D)) position.x += speed * GetFrameTime();

    position.x = Clamp(position.x, 0.0f, static_cast<float>(GetScreenWidth()));
    position.y = Clamp(position.y, 0.0f, static_cast<float>(GetScreenHeight()));
}


void Player::Render() {
    DrawTextureEx(sprite, position, 0.0f, 0.5f, RAYWHITE);

    DrawRectangle(10, 70, 200, 20, RED); 
    DrawRectangle(10, 70, health / 100.0f * 200, 20, GREEN);
    DrawText("Health", 220, 70, 20, WHITE); 
}


Vector2 Player::GetPosition() const {
    return position;
}

void Player::SetPosition(Vector2 newPosition) {
    position = newPosition;
}


void Player::AddGold(int amount) {
    gold += amount;
}

void Player::GainExperience(int amount) {
    experience += amount;
}

void Player::IncreaseDamage(int amount) {
    damage += amount;
}

void Player::IncreaseHealth(int amount) {
    maxHealth += amount; 
    health = maxHealth; 
}

int Player::GetDamage() const {
    return damage;
}

int Player::GetHealth() const {
    return health; 
}

int Player::GetMaxHealth() const {
    return maxHealth; 
}
