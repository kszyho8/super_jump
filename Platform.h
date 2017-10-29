#pragma once
#include <stdlib.h> // potrzebne przy generowaniu liczb losowych

class Platform {
    private:
        int points; // odpowiada za numer platformy
        float x, y, width, height; // wymiary platformy i pozycja
        sf::Texture texture_left, texture_middle, texture_right;
        sf::Sprite sprite_l, sprite_m, sprite_r;
    public:
        /* konstruktor */
        Platform(sf::Texture l, sf::Texture m, sf::Texture r, bool first = false, float wysokosc = 0){ // first - czy pierwsza platforma(szersza), float wysokoœæ poprzedniej platformy

            /* NIE DZIA£A
            this->texture_left.loadFromFile("img/platformy.png", sf::IntRect(0, 20, SIZE, SIZE));
            this->texture_middle.loadFromFile("img/platformy.png", sf::IntRect(20, 20, SIZE, SIZE));
            this->texture_right.loadFromFile("img/platformy.png", sf::IntRect(40, 20, SIZE, SIZE));
            */
            /* przypisanie tekstur */
            this->texture_left = l;
            this->texture_middle = m;
            this->texture_right = r;

            /* przypisanie tekstur do spriteów */
            sprite_l.setTexture(texture_left);

            texture_middle.setRepeated(true);
            sprite_m.setTextureRect(sf::IntRect(0, 0, this->width-(SIZE*2), this->height));
            sprite_m.setTexture(texture_middle);

            sprite_r.setTexture(texture_right);

            this->init(first, wysokosc); // inicjalizacja wartoœci pocz¹tkowych
        }
        /* destruktor */
        ~Platform(){}

        /* inicjalizacja wartoœci pocz¹tkowych */
        void init( bool first = false, float wysokosc = 0) // first - czy pierwsza platforma(szersza), float wysokoœæ poprzedniej platformy
        {
            /* je¿eli platforma pierwsza */
            if(first == true){
                this->x = AIR_GAP + OFFSET * 1.0f; // pozycja x najbli¿ej krawêdzi lewej
                this->y = SCREEN_HEIGHT - (AIR_GAP*2) - SIZE; // wysokoœæ na samym dole
                this->width = SCREEN_WIDTH - (AIR_GAP*2) - (OFFSET*2); //
                total = 0; // numer wszystkich platformy ZMIENNA GLOBALNA
            } else {
                /* ustawienie szerokoœci platformy */
                do {
                    this->width = rand()%((SCREEN_WIDTH-(OFFSET*2))/2);
                } while(this->width < 100); // dopóki platforma nie jest wiêksza ni¿ 100px

                int a = SCREEN_WIDTH-AIR_GAP-this->width-(OFFSET*2); // zmienna odpowiadaj¹ca za maksymaln¹ pozycjê platformy w osi x
                this->x = OFFSET + rand()%a + (float)AIR_GAP; // ustawienie pozycji platformy
                this->y = wysokosc - 100; // ustawienie pozycji y platformy (pozycja poprzedniej - 100px)
                total++; // numer wszystkich platform ZMIENNA GLOBALNA
            }
            this->height = 20; // wysokoœæ platformy
            this->points = total; // numer platformy
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

        /* aktualizacja logiki platformy */
        void update(){
            /* je¿eli platforma znajduje siê poza ekranem (na dole) */
            if(this->y > SCREEN_HEIGHT && this->width < 614)
            {
                /* wczytanie nowej szerokoœci */
                do
                {
                    this->width = rand()%((SCREEN_WIDTH-(OFFSET*2))/2);
                } while(this->width < 100);
                /* generowanie po³o¿enia */
                int a = SCREEN_WIDTH-AIR_GAP-this->width-(OFFSET*2);
                this->x = OFFSET + rand()%a + (float)AIR_GAP;
                this->y -= 600;
                /* barysowanie platformy */
                sprite_l.setPosition(sf::Vector2f(this->x, this->y));
                sprite_m.setTextureRect(sf::IntRect(0, 0, this->width-(SIZE*2), this->height));
                sprite_m.setPosition(sf::Vector2f(this->x+SIZE, this->y));
                sprite_r.setPosition(sf::Vector2f(this->x + this->width - SIZE, this->y));
                total++; // numer wszystkich platform ZMIENNA GLOBALNA
                this->points = total; // numer platformy
            }
        }
        /* rysowanie platformy na ekranie */
        void draw(sf::RenderWindow &window){
            window.draw(sprite_l);
            window.draw(sprite_m);
            window.draw(sprite_r);
        }
        /* opadanie platformy */
        void down()
        {
            this->y += 4.0f;
            sprite_l.setPosition(sf::Vector2f(this->x, this->y));
            sprite_m.setPosition(sf::Vector2f(this->x+SIZE, this->y));
            sprite_r.setPosition(sf::Vector2f(this->x + this->width - SIZE, this->y));
        }
};
