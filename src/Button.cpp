        #include "Button.h"
        
        Button::Button(int actionID)
        {
            this->actionID = 0;
            setFillColor(sf::Color(86,20,19));
            setOutlineThickness(5);
            setOutlineColor(sf::Color(146,20,19));
        }

        Button::~Button()
        {
        }

        void Button::setSize(const sf::Vector2f size)
        {
            this->shape.setSize(size); 	
        }

        void Button::setText(const std::string& text)
        {
            this->label.setString(text);
        }

        void Button::setCharacterSize(int size)
        {
            this->label.setCharacterSize(size);
        }

        void Button::setFillColor(const sf::Color& color)
        {
            this->fillColor = color;
            this->shape.setFillColor(this->fillColor);
        }

        void Button::setOutlineColor(const sf::Color& color)
        {
            this->fillColor = color;
            this->shape.setOutlineColor(this->outlineColor);
        }

        void Button::setPosition(const int &x, const int &y)
        {
            this->shape.setPosition(x, y);
        }

        void Button::setOutlineThickness(float thickness)
        {
            this->shape.setOutlineThickness(thickness);
        }

        sf::FloatRect Button::getGlobalBound()const
        {
            return this->shape.getGlobalBounds();
        }

        int Button::getActionID() const
        {
            return this->actionID;
        }

        void Button::setActionID(int id)
        {
            this->actionID = id;
        }
        
        void Button::onMouseEntered()
        {
                const float light = 1.5;

                this->shape.setOutlineColor(sf::Color(  this->outlineColor.r * light,
                                                        this->outlineColor.g * light, 
                                                        this->outlineColor.b * light));

                this->shape.setFillColor(sf::Color( this->fillColor.r * light,
                                                    this->fillColor.b * light,
                                                    this->fillColor.b * light));
        }

        void Button::Button::onMouseWithdraw()
        {
            setFillColor(sf::Color(86,20,19));
            setOutlineColor(sf::Color(146,20,19));
        }


        void Button::isLeftClicked()
        {   
            std::cout << "Button with action ID: " << this->actionID << " was clicked.\n";      
        }

        void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            target.draw(this->shape);
            target.draw(this->label);
        }
