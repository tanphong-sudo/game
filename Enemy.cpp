#include "Enemy.h"
#include <raymath.h>

Enemy::Enemy() : position({0, 0}), speed(20.0f), health(50), damage(10), attackCooldown(0.0f) {}

void Enemy::Init(Vector2 startPosition, Texture2D enemyTexture) {
    position = startPosition;
    texture = enemyTexture;
}

void Enemy::Update(Vector2 playerPosition) {
    if (attackCooldown > 0.0f) {
        attackCooldown -= GetFrameTime(); 
    }

    // Move toward the player
    Vector2 direction = Vector2Subtract(playerPosition, position);
    if (Vector2Length(direction) > 0) {
        direction = Vector2Normalize(direction);
        position = Vector2Add(position, Vector2Scale(direction, speed * GetFrameTime()));
    }
}

bool Enemy::CanAttack(Vector2 playerPosition) {
    if (attackCooldown <= 0.0f && Vector2Distance(position, playerPosition) <= attackRange) {
        attackCooldown = attackDelay; 
        return true; 
    }
    return false;
}


void Enemy::Render() const {
    DrawTextureEx(texture, position, 0.0f, 0.5f, RAYWHITE);
    RenderHealthBar();
}


void Enemy::TakeDamage(int amount) {
    health -= amount;
    if (health < 0) health = 0;
}

bool Enemy::IsAlive() const {
    return health > 0;
}

Vector2 Enemy::GetPosition() const {
    return position;
}

void Enemy::RenderHealthBar() const {
    // Position the health bar slightly above the enemy
    Vector2 barPosition = { position.x, position.y - 10 };
    float barWidth = 50.0f;
    float healthPercentage = static_cast<float>(health) / 50.0f; // Assume max health is 50

    // Draw the background of the health bar
    DrawRectangle(barPosition.x, barPosition.y, barWidth, 5, RED);

    // Draw the current health portion
    DrawRectangle(barPosition.x, barPosition.y, barWidth * healthPercentage, 5, GREEN);
}

void Enemy::SetHealth(int newHealth) {
    health = newHealth;
}

void Enemy::SetDamage(int newDamage) {
    damage = newDamage;
}

int Enemy::GetDamage() const {
    return damage;
}

