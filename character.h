typedef struct {
  int heigth;
  int width;

  int maxFrame;
  int curFrame;
  int frameCount;
  int frameDelay;
  bool limited;

  ALLEGRO_BITMAP *image;
} Sprite;

typedef struct {

  int leftKey;
  int rightKey;
  int attack1Key;
  int attack2Key;

  int life;

  float x;
  float y;
  int dirX;
  int dirY;

  float velX;
  float velY;

  int animationDirection;

  Sprite running;
  Sprite idle;
  Sprite attack1;
  Sprite attack2;
  Sprite hurt;

  Sprite current_sprite;
} Character;

typedef struct {
  float x;
  float y;

  int dirX;
  
  float velX;

  ALLEGRO_BITMAP *image;
} Cloud;

typedef struct {
  float x;
  float y;

  int dirX;
  int animationDirection;

  int speed;
  int damage;
  bool fired;

  ALLEGRO_BITMAP *image;
} Bullet;