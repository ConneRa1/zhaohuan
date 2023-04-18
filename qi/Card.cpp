#include "Card.h"
Card::~Card()
{
}
Card::Card(Texture& texture, int width, int height, int x, int y) : Object(texture, width, height, x, y) {}
