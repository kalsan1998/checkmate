#include "player.h"
using namespace std;

Player::Player(Colour colour): colour{colour}{}
Colour Player::getColour() const { return colour; }
