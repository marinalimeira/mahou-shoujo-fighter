#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "character.h"

#define HEIGHT 900
#define WIDTH 600
#define FPS 20

ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_BITMAP *background = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *timer = NULL;
ALLEGRO_SAMPLE *main_song = NULL;

void init();
void moveCharacterLeft(Character *c);
void moveCharacterRight(Character *c);
void makeAttack1(Character *c);
void makeAttack2(Character *c);

void main(int argc, int **argv){

  init();

  Character homura;

  homura.leftKey = ALLEGRO_KEY_LEFT;
  homura.rightKey = ALLEGRO_KEY_RIGHT;
  homura.attack1Key = ALLEGRO_KEY_UP;
  homura.attack2Key = ALLEGRO_KEY_DOWN;

  homura.x = 100;
  homura.y = 400;
  homura.animationDirection = 0;

  homura.velX = 5;
  homura.dirX = 0;
  homura.dirY = 0;

  homura.running.heigth = 128;
  homura.running.width = 108;
  homura.running.maxFrame = 7;
  homura.running.curFrame = 0;
  homura.running.frameCount = 0;
  homura.running.frameDelay = 2;

  homura.running.image = al_load_bitmap("imgs/sprites/running/homura_running_by_konbe.bmp");
  al_convert_mask_to_alpha(homura.running.image, al_map_rgb(0, 255, 38));

  homura.idle.heigth = 128;
  homura.idle.width = 98;
  homura.idle.maxFrame = 8;
  homura.idle.curFrame = 0;
  homura.idle.frameCount = 0;
  homura.idle.frameDelay = 2;

  homura.idle.image = al_load_bitmap("imgs/sprites/idle/homura_idle_by_konbe.bmp");
  al_convert_mask_to_alpha(homura.idle.image, al_map_rgb(0, 255, 38));

  homura.attack1.heigth = 128;
  homura.attack1.width = 100;
  homura.attack1.maxFrame = 8;
  homura.attack1.curFrame = 0;
  homura.attack1.frameCount = 0;
  homura.attack1.frameDelay = 2;

  homura.attack1.image = al_load_bitmap("imgs/sprites/attacking/homura_attack1_by_konbe.bmp");
  al_convert_mask_to_alpha(homura.attack1.image, al_map_rgb(0, 255, 38));

  homura.attack2.heigth = 128;
  homura.attack2.width = 74;
  homura.attack2.maxFrame = 7;
  homura.attack2.curFrame = 0;
  homura.attack2.frameCount = 0;
  homura.attack2.frameDelay = 2;

  homura.attack2.image = al_load_bitmap("imgs/sprites/attacking/homura_attack2_by_konbe.bmp");
  al_convert_mask_to_alpha(homura.attack2.image, al_map_rgb(0, 255, 38));

  homura.current_sprite = homura.idle;

  Character mami;

  mami.leftKey = ALLEGRO_KEY_D;
  mami.rightKey = ALLEGRO_KEY_A;
  mami.attack1Key = ALLEGRO_KEY_W;
  mami.attack2Key = ALLEGRO_KEY_S;

  mami.x = 670;
  mami.y = 400;
  mami.animationDirection = 0;

  mami.velX = 5;
  mami.dirX = 0;
  mami.dirY = -1;

  mami.running.heigth = 128;
  mami.running.width = 108;
  mami.running.maxFrame = 8;
  mami.running.curFrame = 0;
  mami.running.frameCount = 0;
  mami.running.frameDelay = 2;

  mami.running.image = al_load_bitmap("imgs/sprites/running/mami_running_by_konbe.bmp");
  al_convert_mask_to_alpha(mami.running.image, al_map_rgb(0, 255, 38));

  mami.idle.heigth = 128;
  mami.idle.width = 103;
  mami.idle.maxFrame = 6;
  mami.idle.curFrame = 0;
  mami.idle.frameCount = 0;
  mami.idle.frameDelay = 2;

  mami.idle.image = al_load_bitmap("imgs/sprites/idle/mami_idle_by_konbe.bmp");
  al_convert_mask_to_alpha(mami.idle.image, al_map_rgb(0, 255, 38));

  mami.attack1.heigth = 150;
  mami.attack1.width = 120;
  mami.attack1.maxFrame = 8;
  mami.attack1.curFrame = 0;
  mami.attack1.frameCount = 0;
  mami.attack1.frameDelay = 2;

  mami.attack1.image = al_load_bitmap("imgs/sprites/attacking/mami_attack1_by_konbe.bmp");
  al_convert_mask_to_alpha(mami.attack1.image, al_map_rgb(0, 255, 38));

  mami.attack2.heigth = 140;
  mami.attack2.width = 141;
  mami.attack2.maxFrame = 18;
  mami.attack2.curFrame = 0;
  mami.attack2.frameCount = 0;
  mami.attack2.frameDelay = 2;

  mami.attack2.image = al_load_bitmap("imgs/sprites/attacking/mami_attack2_by_konbe.bmp");
  al_convert_mask_to_alpha(mami.attack2.image, al_map_rgb(0, 255, 38));

  mami.current_sprite = mami.idle;

  Cloud cloud1;
  cloud1.x = 400;
  cloud1.y = 110;

  cloud1.dirX = -1;
  
  cloud1.velX = 1;

  cloud1.image = al_load_bitmap("imgs/miscellaneous/cloud1.bmp");
  al_convert_mask_to_alpha(cloud1.image, al_map_rgb(0, 255, 38));

  Cloud cloud2;
  cloud2.x = 50;
  cloud2.y = 120;

  cloud2.dirX = -1;
  
  cloud2.velX = 1;

  cloud2.image = al_load_bitmap("imgs/miscellaneous/cloud2.bmp");
  al_convert_mask_to_alpha(cloud2.image, al_map_rgb(0, 255, 38));

  Cloud cloud3;
  cloud3.x = 800;
  cloud3.y = 80;

  cloud3.dirX = -1;
  
  cloud3.velX = 1;

  cloud3.image = al_load_bitmap("imgs/miscellaneous/cloud3.bmp");
  al_convert_mask_to_alpha(cloud3.image, al_map_rgb(0, 255, 38));

  Bullet bullet;

  bullet.speed = 10;
  bullet.damage = 5;

  bool done = false;

  while (!done) {
    ALLEGRO_EVENT event;
    
    al_wait_for_event(event_queue, &event);

    if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
      done = true;
    }

    if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
      if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
        done = true;
      } else if (event.keyboard.keycode == homura.leftKey) {
        homura.dirX = -1;
        moveCharacterLeft(&homura);
      } else if (event.keyboard.keycode == homura.rightKey) {
        homura.dirX = 1;
        moveCharacterRight(&homura);
      } else if (event.keyboard.keycode == homura.attack1Key) {
        makeAttack1(&homura);
      } else if (event.keyboard.keycode == homura.attack2Key) {
        makeAttack2(&homura);
      } else if (event.keyboard.keycode == mami.leftKey) {
        mami.dirX = 1;
        moveCharacterLeft(&mami);
      } else if (event.keyboard.keycode == mami.rightKey) {
        mami.dirX = -1;
        moveCharacterRight(&mami);
      } else if (event.keyboard.keycode == mami.attack1Key) {
        makeAttack1(&mami);
      } else if (event.keyboard.keycode == mami.attack2Key) {
        makeAttack2(&mami);
      }

    } else if(event.type == ALLEGRO_EVENT_KEY_UP){

      if ((event.keyboard.keycode == homura.rightKey) || (event.keyboard.keycode == homura.leftKey) ||
        (event.keyboard.keycode == homura.attack1Key) || (event.keyboard.keycode == homura.attack2Key)){
        homura.current_sprite = homura.idle;
        homura.dirX = 0;        
      } if ((event.keyboard.keycode == mami.rightKey) || (event.keyboard.keycode == mami.leftKey) ||
        (event.keyboard.keycode == mami.attack1Key) || (event.keyboard.keycode == mami.attack2Key)){
        mami.current_sprite = mami.idle;
        mami.dirX = 0;
      }       
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
      
      if(++mami.current_sprite.frameCount >= mami.current_sprite.frameDelay) {
        if(++mami.current_sprite.curFrame >= mami.current_sprite.maxFrame)
          mami.current_sprite.curFrame = 0;
        else if (mami.current_sprite.curFrame <= 0)
          mami.current_sprite.curFrame = mami.current_sprite.maxFrame - 1; 

        mami.current_sprite.frameCount = 0;
      }

      mami.x += mami.velX * mami.dirX;

      if(mami.x >= HEIGHT - 128){
        mami.x = HEIGHT - 128;
      }
      else if (mami.x <= 0){
        mami.x = 0;
      }

      cloud1.x += cloud1.velX * cloud1.dirX;

      if (cloud1.x <= -297){
        cloud1.x = 900;
      }

      cloud2.x += cloud2.velX * cloud2.dirX;

      if (cloud2.x <= -300){
        cloud2.x = 900;
      }

      cloud3.x += cloud3.velX * cloud3.dirX;

      if (cloud3.x <= -297){
        cloud3.x = 900;
      }
    }

    al_draw_bitmap_region(homura.current_sprite.image, homura.current_sprite.curFrame * homura.current_sprite.width, 0, homura.current_sprite.width, homura.current_sprite.heigth, homura.x, homura.y, homura.animationDirection);
    al_draw_bitmap_region(mami.current_sprite.image, mami.current_sprite.curFrame * mami.current_sprite.width, 0, mami.current_sprite.width, mami.current_sprite.heigth, mami.x, mami.y, mami.animationDirection);
    al_draw_bitmap_region(cloud1.image, 0, 0, 290, 160, cloud1.x, cloud1.y, 0);
    al_draw_bitmap_region(cloud2.image, 0, 0, 238, 140, cloud2.x, cloud2.y, 0);
    al_draw_bitmap_region(cloud3.image, 0, 0, 569, 247, cloud3.x, cloud3.y, 0);
    al_flip_display();
    al_draw_bitmap(background, 0, 0, 0);
  }

  al_destroy_sample(main_song);
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

  if(!al_install_audio() ? printf("Failed to initialize audio!\n") : 0);

  if(!al_init_acodec_addon() ? printf("Failed to initialize audio codecs!\n") : 0);

  // change this if increase the number of audio file
  if (!al_reserve_samples(1) ? printf("Failed to reserve samples!\n") : 0);

  main_song = al_load_sample( "audio/that_persons_name_is_by_Jacobus21.ogg" );
  if (!main_song ? printf("Background music not loaded!\n") : 0);

  al_play_sample(main_song, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);

  event_queue = al_create_event_queue();

  timer = al_create_timer(1.0 / FPS);
  al_start_timer(timer);

  al_set_window_title(display, "｡＾･ｪ･＾｡");

  al_register_event_source(event_queue, al_get_timer_event_source(timer));
  al_register_event_source(event_queue, al_get_keyboard_event_source());
  al_register_event_source(event_queue, al_get_display_event_source(display));
}

void moveCharacterLeft(Character *c){
  (*c).animationDirection = ALLEGRO_FLIP_HORIZONTAL;  
  (*c).current_sprite = (*c).running;
}

void moveCharacterRight(Character *c){
  (*c).animationDirection = 0;
  (*c).current_sprite = (*c).running;
}

void makeAttack1(Character *c){
  (*c).current_sprite = (*c).attack1;
}

void makeAttack2(Character *c){
  (*c).current_sprite = (*c).attack2;
}
