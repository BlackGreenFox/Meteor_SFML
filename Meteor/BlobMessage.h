#pragma once
#include "BaseObject.h"


class BlobMessage : public BaseObject {
private:
	float opacity = 0;
	String text = " ";
	bool liza = false;

	Sprite sprite2;
	Texture texture2;
public:

	BlobMessage(String file, String file2, Vector2f pos, Text& label) : BaseObject(file) {
		getObjectSprite().setOrigin(getObjectBounds().width / 2.0f, getObjectBounds().height / 2.0f);
		getObjectSprite().setPosition(pos);
		getObjectSprite().setScale(0.4, 0.4);


		texture2.loadFromFile(file2);
		sprite2.setTexture(texture2);
		sprite2.setOrigin(sprite2.getLocalBounds().width / 2.0f, sprite2.getLocalBounds().height / 2.0f);
		sprite2.setPosition(getObjectGlobalBounds().left + getObjectGlobalBounds().width / 2.0f,
			getObjectGlobalBounds().top + getObjectGlobalBounds().height / 2.0f - 10);


		label.setFillColor(Color::Black);
		label.setString(text);
		updateLabelPosition(label);
		setOpacity(opacity, label);
	}

	~BlobMessage() {

	}

	void addCharacterToText(char character, Text& label) {
		opacity = 150;
		setOpacity(opacity, label);
		text += character;   
		String formattedText = formatTextForDisplay(text);
		label.setString(formattedText);
		updateLabelPosition(label);
	}

	String formatTextForDisplay(const String& text, unsigned int charactersPerLine = 19, unsigned int charactersMax = 160) {
		String formattedText;
		
		unsigned int counter = 0;
		int counterLength = text.getSize() - charactersMax ;
		for (char character : text) {
			
			if (counterLength <= 0)
			{
				formattedText += character;
				counter++;

				if (counter >= charactersPerLine) {
					formattedText += '\n';
					counter = 0;
				}
			}
			else {
				counterLength--;
			}
		}

		return formattedText;
	}

	void updateLabelPosition(Text& label) {
		label.setOrigin(label.getLocalBounds().width / 2.0f, label.getLocalBounds().height / 2.0f);
		label.setPosition(getObjectGlobalBounds().left + getObjectGlobalBounds().width / 2.0f,
			getObjectGlobalBounds().top + getObjectGlobalBounds().height / 2.0f - 10);
	}

	void update(Text& label) {
		if (opacity > 0) {
			opacity -= 0.1f;
			
			if (opacity < 100)
				setOpacity(opacity, label);

			if(opacity < 40)
				text = " ";


			if (opacity < 10)
				liza = false;
		}
	}

	void setOpacity(float value, Text& label) {
		value = std::min(100.0f, std::max(0.0f, value));
		Uint8 alpha = static_cast<Uint8>((value / 100.0f) * 255);
		Color spriteColor = getObjectSprite().getColor();
		Color textColor = label.getFillColor();
		spriteColor.a = alpha;
		textColor.a = alpha;
		sprite2.setColor(spriteColor);
		getObjectSprite().setColor(spriteColor);
		label.setFillColor(textColor);
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

	void draw(RenderWindow& window) override {
		window.draw(getObjectSprite());
			
		// 
		if (text.find("LIZA") != std::string::npos)
		{
			window.draw(sprite2);
		}
		
	}
};