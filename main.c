#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "character.h"

#define HEIGHT 900
#define WIDTH 600

ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_BITMAP *background = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *timer = NULL;

void init();
void moveCharacterLeft(Character *c);
void moveCharacterRight(Character *c);

void main(int argc, int **argv){

  init();

  Character homura;
  homura.x = 100;
  homura.y = 400;
  homura.animationDirection = 0;

  homura.velX = 2;
  homura.dirX = 0;
  homura.dirY = 0;

  homura.running.heigth = 128;
  homura.running.width = 108;
  homura.running.maxFrame = 7;
  homura.running.curFrame = 0;
  homura.running.frameCount = 0;
  homura.running.frameDelay = 5;
  homura.running.animationColumns = 8;

  homura.running.image = al_load_bitmap("imgs/sprites/running/homura_running_by_konbe.bmp");
  al_convert_mask_to_alpha(homura.running.image, al_map_rgb(0, 255, 38));

  homura.idle.heigth = 128;
  homura.idle.width = 98;
  homura.idle.maxFrame = 8;
  homura.idle.curFrame = 0;
  homura.idle.frameCount = 0;
  homura.idle.frameDelay = 6;
  homura.idle.animationColumns = 8;

  homura.idle.image = al_load_bitmap("imgs/sprites/idle/homura_idle_by_konbe.bmp");
  al_convert_mask_to_alpha(homura.idle.image, al_map_rgb(0, 255, 38));

  homura.current_sprite = homura.idle;

  bool done = false;

  while (!done) {
    ALLEGRO_EVENT event;
    
    al_wait_for_event(event_queue, &event);

    if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
      done = true;
    }

    if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
      switch (event.keyboard.keycode){
        case ALLEGRO_KEY_ESCAPE:
          done = true;
        break;
        case ALLEGRO_KEY_LEFT:
          moveCharacterLeft(&homura);
        break;
        case ALLEGRO_KEY_RIGHT:
          moveCharacterRight(&homura);
          
        break;
      }
    } else if(event.type == ALLEGRO_EVENT_KEY_UP){
      homura.current_sprite = homura.idle;
      homura.dirX = 0;
    } else if(event.type == ALLEGRO_EVENT_TIMER) {

      if(++homura.current_sprite.frameCount >= homura.current_sprite.frameDelay) {
        if(++homura.current_sprite.curFrame >= homura.current_sprite.maxFrame)
          homura.current_sprite.curFrame = 0;
        else if (homura.current_sprite.curFrame <= 0)
          homura.current_sprite.curFrame = homura.current_sprite.maxFrame - 1; 

        homura.current_sprite.frameCount = 0;
      }

      homura.x += homura.velX * homura.dirX;

      if(homura.x >= HEIGHT - 128){
        homura.x = HEIGHT - 128;
      }
      else if (homura.x <= 0){
        homura.x = 0;
      }
    }

    al_draw_bitmap_region(homura.current_sprite.image, homura.current_sprite.curFrame * homura.current_sprite.width, 0, homura.current_sprite.width, homura.current_sprite.heigth, homura.x, homura.y, homura.animationDirection);
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
  al_draw_bitmap(background, 0, 0, 0);

  if (!background ? printf("Fail to load background.\n") : 0);

  event_queue = al_create_event_queue();

  timer = al_create_timer(1.0 / 60);
  al_start_timer(timer);

  al_set_window_title(display, "｡＾･ｪ･＾｡");

  al_register_event_source(event_queue, al_get_timer_event_source(timer));
  al_register_event_source(event_queue, al_get_keyboard_event_source());
  al_register_event_source(event_queue, al_get_display_event_source(display));
}

void moveCharacterLeft(Character *c){
  (*c).animationDirection = ALLEGRO_FLIP_HORIZONTAL;
  (*c).dirX = -1;
  (*c).current_sprite = (*c).running;
}

void moveCharacterRight(Character *c){
  (*c).animationDirection = 0;
  (*c).dirX = 1;
  (*c).current_sprite = (*c).running;
}