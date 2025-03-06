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

                IceObj() {
                        starting = (Vector2){400, 225};
                        position = starting;
                        velocity = (Vector2){0.25, 0.25};
                        accel = (Vector2){-0.02, -0.02};
                }

                IceObj(float x, float y) {
                        starting = (Vector2){x, y};
			position = starting;
			velocity = (Vector2){0.25, 0.25};
			accel = (Vector2){-0.02, -0.02};
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
        if (position.x <= 20) { position.x = 22; velocity.x *= -0.75; }
        if (position.x >= 780) { position.x = 778; velocity.x *= -0.75; }
        if (position.y <= 20) { position.y = 22; velocity.y *= -0.75; }
        if (position.y >= 430) { position.y = 428; velocity.y *= -0.75; }
}

#endif
