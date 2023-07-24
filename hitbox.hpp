#ifndef HITBOX_H
#define HITBOX_H

class Hitbox {
    
public:
    // From top-left
    float x, y, w, h;

    // Getters
    float getBottom() { return y+h; }
    float getTop()    { return y;   }
    float getRight()  { return x+w; }
    float getLeft()   { return x;   }

    // Constructor
    Hitbox(float x, float y, float w, float h);

    // Collision
    bool isColliding(Hitbox* b);

    // Updating position
    void updatePos(float x, float y);

    // Debug draw
    void display();

};

#endif