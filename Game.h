#include "Player.h"
#include "Dungeon.h"
#include "Enemy.h"
#include <vector>

struct Item {
    Vector2 position;
    bool isCollected;
};

class Game {
public:
    Game();
    void Init();
    void Update();
    void Render();

private:
    enum class State { MENU, PLAYING, GAME_OVER };
    State gameState;

    Player player;
    Dungeon dungeon;

    int enemyCount;
    std::vector<Enemy> enemies;
    Texture2D enemyTexture;

    std::vector<Item> goldItems; 
    int playerGold;
    int currentLevel; 
    bool inShop;   
    void EnterShop();

    void NextLevel();

    void SpawnGold(int count);

    void SpawnEnemies(int count);

    void UpdateMenu();
    void RenderMenu();
    void UpdatePlaying();
    void RenderPlaying();
    void UpdateGameOver();
    void RenderGameOver();
};
