#pragma once

class Player {
  	private:
  		float x, y, width, height; // wymiary platformy i pozycja
  		float accelerate, velocity; // przy�pieszenie lewo, grawitacja
  		bool moving; // czy posta� jest w ruchu ( o� x )
  		sf::Texture texture;
  		sf::Sprite sprite;
	public:
	    /* konstruktor */
  		Player()
  		{
  		    this->init(); // inicjalizacja postaci
          	texture.loadFromFile("img/postac.png"); // wczytanie tekstury
            sprite.setTexture(texture);
            sprite.setPosition(sf::Vector2f(this->x, this->y));
        }

        /* destruktor */
  		~Player(){}

        float xPos(){ return this->x; }
        float yPos(){ return this->y; }
        float getWidth(){ return this->width; }
        float getHeight(){ return this->height; }
        float getVelocity() { return this->velocity; }
        bool isMoving() { return this->moving; }

        /* inicjalizacja postaci (nowa gra) */
        void init()
        {
            this->width = 48;
          	this->height = 70;
          	this->velocity = -1.0f;
          	this->accelerate = 5.0f;
          	this->moving = false;
          	this->x = (SCREEN_WIDTH/2)-(this->width/2) * 1.0f;
          	this->y = (SCREEN_HEIGHT)-this->height-(AIR_GAP*2)-(SIZE*2) * 1.0f;
        }

        /* aktualizacja logiki postaci */
  		void update(bool collzion, float pos = 0) // parametry: collizion - czy w�st�puje kolizja z platform�, pos - pozycja platformy (o� y)
  		{
  		    /* je�eli kolizja wyst�puje */
  		    if(collzion)
            {
                sprite.setPosition(this->x, pos - this->height); // ustaw wysoko�� na na pozycj� y platformy
                this->velocity = 0; // posta� nie opada
  		    }
  		    else
            {
                this->velocity += VEL; // zwi�kszamy pr�dko��
                this->y += this->velocity; // uaktualniamy pozycj�
                sprite.setPosition(this->x, this->y); // przesuni�cie sprajtu na ekranie
            }

            /* je�eli wci�ni�to strza�k� w prawo */
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                if(this->x + this->width < SCREEN_WIDTH-OFFSET) // wykrywanie kolizji z praw� �cian�
                {
                    this->x += this->accelerate; // przesuni�cie postaci w prawo
                }
            }
            /* je�eli wci�ni�to strza�k� w prawo */
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                if(this->x > OFFSET) // wykrywanie kolizji z lew� �cian�
                {
                    this->x += this->accelerate * -1.0; // przesuni�cie postaci w lewo
                }
            }
            /* je�eli wci�ni�to strza�k� w g�r� lub spacj� */
            if((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)))
            {
                this->jump(); // wykonanie skoku
            }
        }
        /* rysowanie postaci */
  		void draw(sf::RenderWindow &window)
  		{
            window.draw(sprite);
        }
        /* skok */
  		void jump()
  		{
  		    /* je�eli posta� stoi na platformie */
  		    if(this->velocity == 0)
            {
                velocity = -10.0f; // si�a skoku
                this->y -=5; // przesuni�cie postaci (unikni�cie wykrycia kolizji)
  		    }
        }
};
