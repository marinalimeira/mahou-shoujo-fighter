#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#define HEIGHT 900
#define WIDTH 600

typedef struct {
  float x;
  float y;
  int heigth;
  int width;

  int maxFrame;
  int curFrame;
  int frameCount;
  int frameDelay;
  int animationColumns;
  int animationDirection;

  ALLEGRO_BITMAP *image;
} Sprite;

  ALLEGRO_DISPLAY *display = NULL;
  ALLEGRO_BITMAP *background = NULL;
  ALLEGRO_EVENT_QUEUE *event_queue = NULL;
  ALLEGRO_BITMAP *image = NULL;
  ALLEGRO_TIMER *timer;


void init();

void main(int argc, int **argv){

  init();
  
  Sprite homura;
  homura.x = 0;
  homura.y = 400;
  homura.maxFrame = 8;
  homura.curFrame = 0;
  homura.heigth = 128;
  homura.width = 108;
  homura.frameCount = 0;
  homura.frameDelay = 5;
  homura.animationColumns = 8;
  homura.image = al_load_bitmap("imgs/sprites/running/homura_running_by_konbe.bmp");
  al_convert_mask_to_alpha(homura.image, al_map_rgb(0, 255, 38));

  while (1) {
    ALLEGRO_EVENT event;
    ALLEGRO_TIMEOUT timeout;
    al_init_timeout(&timeout, 0.01);

    int has_events = al_wait_for_event_until(event_queue, &event, &timeout);

    if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        break;
    }

    if(event.type == ALLEGRO_EVENT_TIMER) {
      if(++homura.frameCount >= homura.frameDelay)
      {
        if(++homura.curFrame >= homura.maxFrame)
        homura.curFrame = 0;
        homura.frameCount = 0;
      }

      homura.x += 2;

      if(homura.x > HEIGHT)
        homura.x = 20;
    }

    al_draw_bitmap_region(homura.image, homura.curFrame * homura.width, 0, homura.width, homura.heigth, homura.x, homura.y, 0);
    al_flip_display();
    al_draw_bitmap(background, 0, 0, 0);
  }

  al_destroy_event_queue(event_queue);
  al_destroy_display(display);
  
}

void init(){
  if (!al_init() ? printf("Failed to initialize Allegro.\n") : 0); 

  if (!al_install_keyboard() ? printf("Failed to install Keyboard.\n") : 0);

  if (!al_init_image_addon() ? printf("Failed to initialize add-on allegro_image.\n") : 0);
  display = al_create_display(HEIGHT, WIDTH);
  if (!display ? printf("Failed to create display.\n") : 0);

  background = al_load_bitmap("imgs/bg.png");
  if (!background ? printf("Fail to load background.\n") : 0);

  event_queue = al_create_event_queue();

  al_draw_bitmap(background, 0, 0, 0);

  timer = al_create_timer(1.0 / 60);
  al_start_timer(timer);

  al_register_event_source(event_queue, al_get_timer_event_source(timer));
  al_register_event_source(event_queue, al_get_keyboard_event_source());
  al_register_event_source(event_queue, al_get_display_event_source(display));
}