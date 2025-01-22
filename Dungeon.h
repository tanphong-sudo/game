#ifndef DUNGEON_H
#define DUNGEON_H

#include <vector>
#include <raylib.h>

class Dungeon {
public:
    Dungeon(int width, int height);
    ~Dungeon();

    void Generate();     
    void Render();       

    bool IsWall(Vector2 position) const; 

private:
    int width, height;     
    std::vector<std::vector<int>> grid; 

    void CreateRoom(int x, int y, int w, int h);
    void CreateCorridor(int x1, int y1, int x2, int y2); 
};

#endif // DUNGEON_H
