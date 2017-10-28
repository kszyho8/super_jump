#pragma once

class Player {
  	private:
  		float x, y, width, height;
  		float g, accelerate, velocity;
  		bool moveing, direction;
  		sf::Texture texture;
  		sf::Sprite sprite;
	public:
  		Player()
  		{
  		    this->init();

          	texture.loadFromFile("img/postac.png");
            sprite.setTexture(texture);
            sprite.setPosition(sf::Vector2f(this->x, this->y));

        }
  		~Player(){}
        float xPos(){ return this->x; }
        float yPos(){ return this->y; }
        float getWidth(){ return this->width; }
        float getHeight(){ return this->height; }
        float getVelocity() { return this->velocity; }
        bool isMoveing() { return (this->moveing == true)? true : false; }

        void init()
        {
            this->width = 48;
          	this->height = 70;
          	this->velocity = -1.0f;
          	this->accelerate = 5.0f;
          	this->moveing = false;
          	this->x = (SCREEN_WIDTH/2)-(this->width/2) * 1.0f;
          	this->y = (SCREEN_HEIGHT)-this->height-(AIR_GAP*2)-(SIZE*2) * 1.0f;
        }

  		void update(bool collzion, float pos = 0)
  		{
  		    if(collzion)
            {
                sprite.setPosition(this->x, pos - this->height);
                this->velocity = 0;
  		    }
  		    else
            {
                this->velocity += VEL;
                this->y += this->velocity;
                sprite.setPosition(this->x, this->y);
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                if(this->x + this->width < SCREEN_WIDTH-OFFSET)
                {
                    this->x += this->accelerate;
                }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                if(this->x > OFFSET)
                {
                    this->x += this->accelerate * -1.0;
                }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->velocity == 0)
            {
                this->jump();
            }
            //std::cout<<this->velocity<<std::endl;
        }
  		void draw(sf::RenderWindow &window)
  		{
            window.draw(sprite);
        }
  		void jump()
  		{
  		    if(this->velocity == 0)
            {
                velocity = -10.0f;
                this->y -=5;
  		    }
        }
};
