#include "Dungeon.h"
#include <cstdlib>
#include <ctime>   

Dungeon::Dungeon(int width, int height)
    : width(width), height(height) {
    grid = std::vector<std::vector<int>>(height, std::vector<int>(width, 1));
}

Dungeon::~Dungeon() {}

void Dungeon::Generate() {
    grid = std::vector<std::vector<int>>(height, std::vector<int>(width, 0));
}


void Dungeon::Render() {
    ClearBackground(BLACK); 
}


void Dungeon::CreateRoom(int x, int y, int w, int h) {
    for (int i = y; i < y + h && i < height; i++) {
        for (int j = x; j < x + w && j < width; j++) {
            grid[i][j] = 0; // Floor
        }
    }
}

void Dungeon::CreateCorridor(int x1, int y1, int x2, int y2) {
    for (int x = std::min(x1, x2); x <= std::max(x1, x2); x++) {
        if (x < width && y1 < height) {
            grid[y1][x] = 0; // Floor
        }
    }
    // Create a vertical corridor
    for (int y = std::min(y1, y2); y <= std::max(y1, y2); y++) {
        if (x2 < width && y < height) {
            grid[y][x2] = 0; // Floor
        }
    }
}

bool Dungeon::IsWall(Vector2 position) const {
    int gridX = static_cast<int>(position.x / 20); 
    int gridY = static_cast<int>(position.y / 20);

    if (gridX >= 0 && gridX < width && gridY >= 0 && gridY < height) {
        return grid[gridY][gridX] == 1; // 1 is wall
    }
    return true; 
}
