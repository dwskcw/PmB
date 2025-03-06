#include <utility>

#ifndef PLAYER_H
#define PLAYER_H

class Player {
        public:
                std::pair<double, double> starting;
                std::pair<double, double> position;
                std::pair<double, double> velocity;

                Player(double x, double y) {
                        starting.first = x;
                        starting.second = y;
                        position.first = x;
                        position.second = y;
                        velocity.first = 0;
                        velocity.second = 0;
                }

                void updatePosition();
                void reset() {
                        position = starting;
                        velocity.first = 0;
                        velocity.second = 0;
                }
};      

void Player::updatePosition() {
        position.first += velocity.first;
        position.second += velocity.second;

        // simple bounds checks for four corners
        if (position.first <= 20) { position.first = 21; velocity.first *= -1.75; }
        if (position.first >= 780) { position.first = 779; velocity.first *= -1.75; }
        if (position.second <= 20) { position.second = 21; velocity.second *= -1.75; }
        if (position.second >= 430) { position.second = 429; velocity.second *= -1.75; }
}

#endif
