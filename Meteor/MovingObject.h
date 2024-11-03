#pragma once
#include "BaseObject.h"

class MovingObject : public BaseObject
{
private:
	float velocity;
public:

	MovingObject(String file, float velocity = 2) : BaseObject(file) {
		this->velocity = velocity;
		getObjectSprite().setOrigin(getObjectBounds().width / 2.0f, getObjectBounds().height / 2.0f);
	}

	~MovingObject() {

	}

	Sprite& getObjectSprite() {
		return const_cast<Sprite&>(getSprite());
	}
	FloatRect& getObjectBounds() {
		return const_cast<FloatRect&>(getBounds());
	}
	FloatRect& getObjectGlobalBounds() {
		return const_cast<FloatRect&>(getWorldBounds());
	}

	void setVelocity(float value) {
		velocity = value;
	}

	float getVelocity() {
		return velocity;
	}

	virtual void move(float& time) {
		getObjectSprite().move(static_cast<float>(velocity * time), static_cast<float>(velocity * time));
	}


};

