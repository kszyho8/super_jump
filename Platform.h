#pragma once
#include <stdlib.h>

class Platform {
    private:
        int points;
        float x, y, width, height;
        int text;
        sf::Texture texture_left, texture_middle, texture_right;
        sf::Sprite sprite_l, sprite_m, sprite_r;
    public:
        Platform(sf::Texture l, sf::Texture m, sf::Texture r, bool first = false, float wysokosc = 0){

            this->texture_left = l;
            this->texture_middle = m;
            this->texture_right = r;

            sprite_l.setTexture(texture_left);
            //sprite_l.setPosition(sf::Vector2f(this->x, this->y));

            texture_middle.setRepeated(true);
            sprite_m.setTextureRect(sf::IntRect(0, 0, this->width-(SIZE*2), this->height));
            sprite_m.setTexture(texture_middle);
            //sprite_m.setPosition(sf::Vector2f(this->x+SIZE, this->y));

            sprite_r.setTexture(texture_right);
            //sprite_r.setPosition(sf::Vector2f(this->x + this->width - SIZE, this->y));

            this->init(first, wysokosc);
        }
  	~Platform(){
    }

    void init( bool first = false, float wysokosc = 0)
    {
        if(first == true){
            this->x = AIR_GAP + OFFSET * 1.0f;
            this->y = SCREEN_HEIGHT - (AIR_GAP*2) - SIZE;
            this->width = SCREEN_WIDTH - (AIR_GAP*2) - (OFFSET*2);
            total = 0;
            /*
            this->texture_left.loadFromFile("img/platformy.png", sf::IntRect(0, 20, SIZE, SIZE));
            this->texture_middle.loadFromFile("img/platformy.png", sf::IntRect(20, 20, SIZE, SIZE));
            this->texture_right.loadFromFile("img/platformy.png", sf::IntRect(40, 20, SIZE, SIZE));
            */
        } else {
            do {
                this->width = rand()%((SCREEN_WIDTH-(OFFSET*2))/2);
            } while(this->width < 100);
            int a = SCREEN_WIDTH-AIR_GAP-this->width-(OFFSET*2);
            this->x = OFFSET + rand()%a + (float)AIR_GAP;
            this->y = wysokosc - 100;
            total++;
            /*
            this->texture_left.loadFromFile("img/platformy.png", sf::IntRect(0, 40, SIZE, SIZE));
            this->texture_middle.loadFromFile("img/platformy.png", sf::IntRect(20, 40, SIZE, SIZE));
            this->texture_right.loadFromFile("img/platformy.png", sf::IntRect(40, 40, SIZE, SIZE));
            */
        }
        this->height = 20;
        this->points = total;
        sprite_l.setPosition(sf::Vector2f(this->x, this->y));
        sprite_m.setTextureRect(sf::IntRect(0, 0, this->width-(SIZE*2), this->height));
        sprite_m.setPosition(sf::Vector2f(this->x+SIZE, this->y));
        sprite_r.setPosition(sf::Vector2f(this->x + this->width - SIZE, this->y));
    }

    float xPos(){ return this->x; }
    float yPos(){ return this->y; }
    float getWidth(){ return this->width; }
    float getHeight(){ return this->height; }
    int getPoints() { return this->points; }

  	void update(){
        if(this->y > SCREEN_HEIGHT && this->width < 614)
        {
            do
            {
                this->width = rand()%((SCREEN_WIDTH-(OFFSET*2))/2);
            } while(this->width < 100);
            int a = SCREEN_WIDTH-AIR_GAP-this->width-(OFFSET*2);
            this->x = OFFSET + rand()%a + (float)AIR_GAP;
            this->y -= 600;
            sprite_l.setPosition(sf::Vector2f(this->x, this->y));
            sprite_m.setTextureRect(sf::IntRect(0, 0, this->width-(SIZE*2), this->height));
            sprite_m.setPosition(sf::Vector2f(this->x+SIZE, this->y));
            sprite_r.setPosition(sf::Vector2f(this->x + this->width - SIZE, this->y));
            total++;
            this->points = total;
        }
    }
  	void draw(sf::RenderWindow &window){
        window.draw(sprite_l);
        window.draw(sprite_m);
        window.draw(sprite_r);
    }
    void down()
    {
        this->y += 4.0f;
        sprite_l.setPosition(sf::Vector2f(this->x, this->y));
        sprite_m.setPosition(sf::Vector2f(this->x+SIZE, this->y));
        sprite_r.setPosition(sf::Vector2f(this->x + this->width - SIZE, this->y));
    }
};
