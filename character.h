typedef struct {
  int heigth;
  int width;

  int maxFrame;
  int curFrame;
  int frameCount;
  int frameDelay;

  ALLEGRO_BITMAP *image;
} Sprite;

typedef struct {

  int leftKey;
  int rightKey;
  int attack1Key;
  int attack2Key;

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

  Sprite current_sprite;
} Character;

typedef struct {
  float x;
  float y;

  int dirX;
  
  float velX;

  ALLEGRO_BITMAP *image;

} Cloud;