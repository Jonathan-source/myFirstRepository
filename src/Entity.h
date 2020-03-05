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
        sf::Texture texture;
        sf::Texture texture2;
     protected:
     sf::Sprite sprite;

     public:

        //CONSTRUCT
        Entity();
        Entity(float _speed, int health, int attackDmg);
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

        void setSelectTexture();
        void setNormalTexture();
        //MOVE
        virtual void move() = 0;

        //DRAW
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const = 0;

 };


#endif