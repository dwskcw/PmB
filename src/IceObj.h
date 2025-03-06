#include <utility>

#include "raylib.h"

#ifndef PLAYER_H
#define PLAYER_H

class IceObj {
        public:
                Vector2 starting;
                Vector2 position;
                Vector2 velocity;
		Vector2 accel;

                IceObj(double x, double y) {
                        starting = (Vector2){x, y};
			position = starting;
			velocity = (Vector2){0, 0};
			accel = (Vector2){0.98, 0.98};
                }

                void updatePosition();
                void reset() {
                        position = starting;
                        velocity = (Vector2){0, 0};
                }
};      

void IceObj::updatePosition() {
        position.x += velocity.x;
        position.y += velocity.y;
	velocity.x *= accel.x;
	velocity.y *= accel.y;

        // simple bounds checks for four corners
        if (position.x <= 20) { position.x = 21; velocity.x *= -1.75; }
        if (position.x >= 780) { position.x = 779; velocity.x *= -1.75; }
        if (position.y <= 20) { position.y = 21; velocity.y *= -1.75; }
        if (position.y >= 430) { position.y = 429; velocity.y *= -1.75; }
}

#endif
