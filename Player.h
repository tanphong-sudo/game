#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>

class Player {
public:
    Player();
    void Init(Vector2 startPosition);
    void Update();
    void Render();

    Vector2 GetPosition() const;
    void SetPosition(Vector2 newPosition);

    void AddGold(int amount);
    void GainExperience(int amount);
    void TakeDamage(int amount); 
    bool IsAlive() const;     
    void IncreaseDamage(int amount);
    void IncreaseHealth(int amount);

    int GetDamage() const;        
    int GetHealth() const;          
    int GetMaxHealth() const;        

private:
    Vector2 position;
    float speed;
    int health;
    int damage;
    int maxHealth;
    int gold;
    int experience;
    Texture2D sprite;
};

#endif // PLAYER_H
