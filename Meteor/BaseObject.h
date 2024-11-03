#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;


class BaseObject
{
private:
	// Varibles
	String file;
	Image image;
	Texture texture;
	Sprite sprite;
public:
	// Constructor & Destructor
	BaseObject(String file) {
		this->file = file;
		this->image.loadFromFile(this->file);
		this->texture.loadFromImage(this->image);
		this->sprite.setTexture(this->texture);
	}

	~BaseObject() {

	}

	const Sprite& getSprite() const {
		return sprite;
	}
	const FloatRect& getBounds() const {
		return sprite.getLocalBounds();
	}
	const FloatRect& getWorldBounds() const {
		return sprite.getGlobalBounds();
	}

	// Base Logic
	virtual void draw(RenderWindow& window) {
		window.draw(sprite);
	}
};

