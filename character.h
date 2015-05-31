typedef struct {
  int heigth;
  int width;

  int maxFrame;
  int curFrame;
  int frameCount;
  int frameDelay;
  int animationColumns;

  ALLEGRO_BITMAP *image;
} Sprite;

typedef struct {
  float x;
  float y;
  int dirX;
  int dirY;

  float velX;
  float velY;

  int animationDirection;

  Sprite running;
  Sprite idle;

  Sprite current_sprite;
} Character;