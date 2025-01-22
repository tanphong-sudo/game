#ifndef ENEMY_H
#define ENEMY_H

#include <raylib.h>

class Enemy {
public:
    Enemy();
    void Init(Vector2 startPosition, Texture2D enemyTexture);
    void Update(Vector2 playerPosition);
    void Render() const;
    void RenderHealthBar() const; 

    void TakeDamage(int amount);
    bool IsAlive() const;       
    Vector2 GetPosition() const;
    void SetHealth(int newHealth);
    void SetDamage(int newDamage);
    int GetDamage() const; 

    bool CanAttack(Vector2 playerPosition);

private:
    Vector2 position;
    float speed;
    int health;
    int damage;
    Texture2D texture;

    float attackCooldown; 
    static constexpr float attackRange = 60.0f;
    static constexpr float attackDelay = 1.5f;  
};


#endif // ENEMY_H
