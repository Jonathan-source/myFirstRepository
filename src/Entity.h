#ifndef ENTITY_H
#define ENTITY_H
#include <SFML/Graphics.hpp>
class Entity : public sf::Drawable
 {
     private:
    //VAR
        float speed;
        int health;
        int attackDmg;
    //SPRITE
     protected:
     sf::Sprite sprite;

     public:

        //CONSTRUCT
        Entity();
        Entity(sf::Texture &_texture);
        Entity(float _speed, int health, int attackDmg, sf::Texture& _texture);
        ~Entity();
        //GET FUNC
        float getSpeed() const;
        int getHealth() const;
        int getAttackDmg() const;
        sf::Vector2f getPosition() const;
        sf::FloatRect getGlobalBounds() const;
        //SET FUNC
        void setSpeed(float _speed);
        void setHealth(int _health);
        void setAttackDmg(int _attackDmg);

        //MOVE
        virtual void move() = 0;

        //DRAW
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

 };


#endif
