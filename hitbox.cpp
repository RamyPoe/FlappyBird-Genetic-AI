#include "hitbox.hpp"


// Constructor
Hitbox::Hitbox(float _x, float _y, float _w, float _h) {
    x = _x;
    y = _y;
    w = _w;
    h = _h;
}

// Collision
bool Hitbox::isColliding(Hitbox* b) {
    
    // Collision check
    if (
        x < b->x + b->w &&
        x + w > b->x    &&
        y + h > b->y    &&
        y < b->y + b->h
    ) {
        
        return true;
    }
    return false;

}


// Updating
void Hitbox::updatePos(float _x, float _y) {
    x = _x;
    y = _y;
}

// Debug 
void Hitbox::display() {
    // TODO: add debug hitbox draw
}