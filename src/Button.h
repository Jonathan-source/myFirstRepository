#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <iostream>
class Button : public sf::Drawable {
            public:
                Button(int actionID = 0);
                virtual ~Button();

                void setText(const std::string& text);
                void setCharacterSize(int size);
               	void setSize(const sf::Vector2f size);
                void setFillColor(const sf::Color& color);
                void setOutlineColor(const sf::Color& color);
                void setOutlineThickness(float thickness);
		void setPosition(const int &x, const int &y);
		void onMouseEntered();
		void onMouseWithdraw();
                void isLeftClicked();

		int getActionID() const;
		void setActionID(int id);
                sf::FloatRect getGlobalBound()const;

		// Inherited via Drawable
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

            private:
                sf::RectangleShape shape;
                sf::Text label;
		sf::Font font;

                sf::Color fillColor;
                sf::Color outlineColor;

		int actionID;
};

#endif

