#pragma once
#include "MovingObject.h"

class Meteor : public MovingObject
{
	float opacity = 100;
	float flytime = 0;
	float size;
	int currentFrame = 0;
	std::vector<int> frames = {0, 672, 1344};
public:
	Meteor(String file, float velocity = 0.5f) : MovingObject(file, velocity) {
		respawn();
	}

	void setOpacity(float value) {

		value = std::min(100.0f, std::max(0.0f, value));
		Uint8 alpha = static_cast<Uint8>((value / 100.0f) * 255);
		Color spriteColor = getObjectSprite().getColor();
		spriteColor.a = alpha;

		getObjectSprite().setColor(spriteColor);
	}

	void setFlytime(float value) {
		flytime += value;
	}

	void animation() { 
		if (!(currentFrame + 1 >= frames.size())) {
			currentFrame++;
			getObjectSprite().setTextureRect(IntRect(frames[currentFrame], 0, 672, 528));
		}	
	}


	void move(float& time) override{
		getObjectSprite().move(static_cast<float>(getVelocity() * time * -1), static_cast<float>(getVelocity() * time));

		opacity -= 0.1f;
		if (size > 0)
			size -= 0.00005f;
			

		setOpacity(opacity);
		getObjectSprite().setScale(size, size);

		if (flytime > 5000) {
			animation();
			flytime = rand() % 4000;
		}

		if (getObjectSprite().getPosition().x < -280 || getObjectSprite().getPosition().y > 880)
			respawn();
	}

	void respawn() {
		currentFrame = 0;
		getObjectSprite().setTextureRect(IntRect(frames[currentFrame], 0, 672, 528));
		size = static_cast<float>(((rand() % 10) + 5)* 0.01);
		float x = static_cast<float>(rand() % 1700);

		flytime = rand() % 1500;
		opacity = 100;

		getObjectSprite().setPosition(Vector2f(x, -100));
		
		getObjectSprite().setScale(size, size);
		setVelocity(0.1 + static_cast<float>(std::rand()) / RAND_MAX * 0.9);
	}
};

