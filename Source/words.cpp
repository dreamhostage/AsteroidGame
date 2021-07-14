#include "Asteroid.h"

words::words()
{
	this->font.loadFromFile("Images/18949.ttf");
	this->phrase.setFont(font);
	this->phrase.setFillColor(Color::White);
	textSize = 60;
	this->phrase.setCharacterSize(textSize);
	startPositionSet = false;
	textActivated = false;
	backDirection = false;
	phraseNumber = 1;
}

void words::draw()
{
	if (!points)
	{
		if (phrase.getString().toAnsiString().compare("Try to survive") && phraseNumber == 1)
		{
			phrase.setString("Try to survive");
			textActivated = true;
		}
	}
	if (points > 100)
	{
		if (phrase.getString().toAnsiString().compare(" Something EVIL \n watching for you") && phraseNumber == 2)
		{
			phrase.setString(" Something EVIL \n watching for you");
			textActivated = true;
		}
	}
	if (points > 300)
	{
		if (phrase.getString().toAnsiString().compare("Something EVIL is coming!") && phraseNumber == 3)
		{
			phrase.setString("Something EVIL is coming!");
			textActivated = true;
		}
	}
	if (points > 600)
	{
		if (phrase.getString().toAnsiString().compare("Something EVIL is here!") && phraseNumber == 4)
		{
			phrase.setString("Something EVIL is here!");
			CSActivated = true;
			textActivated = true;
		}
	}

	if (textActivated)
	{
		if (!startPositionSet)
		{
			destinationPosition.x = ShipSprite.getPosition().x;
			destinationPosition.y = ShipSprite.getPosition().y - 200;
			appearingPosition.x = destinationPosition.x - screenX - phrase.getString().getSize() * textSize;
			appearingPosition.y = destinationPosition.y;
			phrase.setPosition(appearingPosition);
			timer.restart();
			startPositionSet = true;
		}

		if (phrase.getPosition().x < destinationPosition.x - phrase.getString().getSize() * textSize / 4)
		{
			phrase.setPosition(phrase.getPosition().x + 20, phrase.getPosition().y);
		}

		if (timer.getElapsedTime().asSeconds() > 6)
		{
			backDirection = true;
		}

		if (backDirection)
		{

			if (phrase.getPosition().x < mainX)
			{
				phrase.setPosition(phrase.getPosition().x + 20, phrase.getPosition().y);
			}
			else
			{
				startPositionSet = false;
				textActivated = false;
				backDirection = false;
				++phraseNumber;
				timer.restart();
			}
		}

		window->draw(phrase);
	}
}

void words::reset()
{
	startPositionSet = false;
	textActivated = false;
	backDirection = false;
	phraseNumber = 1;
}