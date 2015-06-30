#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#define HEIGHT 900
#define WIDTH 600
#define FPS 20

ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_BITMAP *background = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *timer = NULL;
ALLEGRO_SAMPLE *main_song = NULL;
ALLEGRO_FONT *font = NULL;

#include "character.h"
#include "initializeCharacters.c"
#include "characterFunctions.c"
#include "initializeClouds.c"
#include "cloudFunctions.c"

void init();

void main(int argc, int **argv){
  init();

  Character homura;
  Character mami;

  initializeHomura(&homura);
  initializeMami(&mami);

  Cloud cloud1;
  Cloud cloud2;
  Cloud cloud3;

  initializeCloud1(&cloud1);
  initializeCloud2(&cloud2);
  initializeCloud3(&cloud3);

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
        makeHomuraAttack1(&homura);
      } else if (event.keyboard.keycode == homura.attack2Key) {
        makeAttack2(&homura);
      } else if (event.keyboard.keycode == mami.leftKey) {
        mami.dirX = 1;
        moveCharacterLeft(&mami);
      } else if (event.keyboard.keycode == mami.rightKey) {
        mami.dirX = -1;
        moveCharacterRight(&mami);
      } else if (event.keyboard.keycode == mami.attack1Key) {
        makeMamiAttack1(&mami);
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
      animateCharacter(&homura);
      animateCharacter(&mami);
      
      moveCloud(&cloud1);
      moveCloud(&cloud2);
      moveCloud(&cloud3);
      
      collideBullet(&homura, &mami);
      collideBullet(&mami, &homura);
    }

    if (homura.bullet.fired){
      al_draw_bitmap_region(homura.bullet.image, 0, 0, 12, 6, homura.bullet.x, homura.bullet.y, homura.bullet.animationDirection);
      if (homura.bullet.x >= 900 || homura.bullet.x <= -17)
        homura.bullet.fired = false; 
    }

    if (mami.bullet.fired){
      al_draw_bitmap_region(mami.bullet.image, 0, 0, 14, 5, mami.bullet.x, mami.bullet.y, mami.bullet.animationDirection);
      if (mami.bullet.x >= 900 || mami.bullet.x <= -17)
        mami.bullet.fired = false; 
    }

    if (mami.life <= 0)
      die(&mami);
    if (homura.life <= 0)
      die(&homura);
    
    al_draw_bitmap_region(homura.current_sprite.image, homura.current_sprite.curFrame * homura.current_sprite.width, 0, homura.current_sprite.width, homura.current_sprite.heigth, homura.x, homura.y, homura.animationDirection);
    al_draw_bitmap_region(mami.current_sprite.image, mami.current_sprite.curFrame * mami.current_sprite.width, 0, mami.current_sprite.width, mami.current_sprite.heigth, mami.x, mami.y, mami.animationDirection);
    al_draw_bitmap_region(cloud1.image, 0, 0, 290, 160, cloud1.x, cloud1.y, 0);
    al_draw_bitmap_region(cloud2.image, 0, 0, 238, 140, cloud2.x, cloud2.y, 0);
    al_draw_bitmap_region(cloud3.image, 0, 0, 569, 247, cloud3.x, cloud3.y, 0);
    char homu_life[5]  = "";
    sprintf(homu_life, "%d", homura.life);
    al_draw_text(font, al_map_rgb(74, 20, 140), 120, 10, ALLEGRO_ALIGN_RIGHT, homu_life);
    char mami_life[5]  = "";
    sprintf(mami_life, "%d", mami.life);
    al_draw_text(font, al_map_rgb(249, 168, 37), 800, 10, ALLEGRO_ALIGN_LEFT, mami_life);
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

  al_init_font_addon();
  if (!al_init_ttf_addon() ? printf("Failed to initialize ttf!\n") : 0);

  font = al_load_ttf_font("fonts/pixelpoiiz.ttf", 43, 0);

  event_queue = al_create_event_queue();

  timer = al_create_timer(1.0 / FPS);
  al_start_timer(timer);

  al_set_window_title(display, "｡＾･ｪ･＾｡");

  al_register_event_source(event_queue, al_get_timer_event_source(timer));
  al_register_event_source(event_queue, al_get_keyboard_event_source());
  al_register_event_source(event_queue, al_get_display_event_source(display));
}
