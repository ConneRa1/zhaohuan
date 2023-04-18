#include "UI.h"
UI::UI() {}
UI::UI(Texture& texture, int width, int height, float x, float y, string name) :Object(texture, width, height, x, y) {
	this->name = name;
}

void UI::update() {
}