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
ALLEGRO_FONT *lifeFont = NULL;
ALLEGRO_FONT *overFont = NULL;
ALLEGRO_MOUSE_STATE *state = NULL;
ALLEGRO_BITMAP *cursor = NULL;

#include "menuOptions.h"
#include "character.h"
#include "initializeCharacters.c"
#include "characterFunctions.c"
#include "initializeClouds.c"
#include "cloudFunctions.c"
#include "gameMain.c"

void init();

void main() {
  init();

  Character kyubey;

  initializeKyubey(&kyubey);
  
  int current = 1;
 
  MenuItem start;
  start.selected = al_load_bitmap("imgs/menu-itens/start_selected.bmp");
  al_convert_mask_to_alpha(start.selected, al_map_rgb(0, 255, 38));
  start.not_selected = al_load_bitmap("imgs/menu-itens/start.bmp");
  al_convert_mask_to_alpha(start.not_selected, al_map_rgb(0, 255, 38));
  start.current = start.not_selected;

  MenuItem scores;
  scores.selected = al_load_bitmap("imgs/menu-itens/scores_selected.bmp");
  al_convert_mask_to_alpha(scores.selected, al_map_rgb(0, 255, 38));
  scores.not_selected = al_load_bitmap("imgs/menu-itens/scores.bmp");
  al_convert_mask_to_alpha(scores.not_selected, al_map_rgb(0, 255, 38));
  scores.current = scores.not_selected;
  
  MenuItem settings;
  settings.selected = al_load_bitmap("imgs/menu-itens/settings_selected.bmp");
  al_convert_mask_to_alpha(settings.selected, al_map_rgb(0, 255, 38));
  settings.not_selected = al_load_bitmap("imgs/menu-itens/settings.bmp");
  al_convert_mask_to_alpha(settings.not_selected, al_map_rgb(0, 255, 38));
  settings.current = settings.not_selected;

  MenuItem ex1t;
  ex1t.selected = al_load_bitmap("imgs/menu-itens/exit_selected.bmp");
  al_convert_mask_to_alpha(ex1t.selected, al_map_rgb(0, 255, 38));
  ex1t.not_selected = al_load_bitmap("imgs/menu-itens/exit.bmp");
  al_convert_mask_to_alpha(ex1t.not_selected, al_map_rgb(0, 255, 38));
  ex1t.current = ex1t.not_selected;

  while (true) {
    ALLEGRO_EVENT event;    
    al_wait_for_event(event_queue, &event);

    if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
      break;
    }

    if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
      if (event.keyboard.keycode == ALLEGRO_KEY_DOWN){
        if (current >= 4){
          current = 1;
        } else {
          current++;
        }
      } else if (event.keyboard.keycode == ALLEGRO_KEY_UP){
        if (current == 1){
          current = 4;
        } else {
          current--;
        }
      } else if (event.keyboard.keycode == ALLEGRO_KEY_ENTER){
        if (current == 1){
          gameMain();
        } else if (current == 4){
          break;
        }
      }
    }

    if (current == 1){
      start.current = start.selected;
    } else {
      start.current = start.not_selected;
    }
    if (current == 2){
      scores.current = scores.selected;
    } else {
      scores.current = scores.not_selected;
    }
    if (current == 3){
      settings.current = settings.selected;
    } else {
      settings.current = settings.not_selected;
    }
    if (current == 4){
      ex1t.current = ex1t.selected;
    } else {
      ex1t.current = ex1t.not_selected;
    }

    if(event.type == ALLEGRO_EVENT_TIMER) {
      animateCharacter(&kyubey);
    }
    
    al_draw_bitmap_region(kyubey.current_sprite.image, kyubey.current_sprite.curFrame * kyubey.current_sprite.width, 0, kyubey.current_sprite.width, kyubey.current_sprite.heigth, kyubey.x, kyubey.y, kyubey.animationDirection);
    al_draw_bitmap_region(start.current, 0, 0, 228, 50, 336, 220, 0);
    al_draw_bitmap_region(scores.current, 0, 0, 258, 50, 321, 300, 0);
    al_draw_bitmap_region(settings.current, 0, 0, 355, 50, 282, 380, 0);    
    al_draw_bitmap_region(ex1t.current, 0, 0, 172, 50, 364, 460, 0);
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

  background = al_load_bitmap("imgs/bg-menu.bmp");
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

  lifeFont = al_load_ttf_font("fonts/pixelpoiiz.ttf", 43, 0);
  overFont = al_load_ttf_font("fonts/ice_pixel-7.ttf", 100, 0);

  event_queue = al_create_event_queue();

  timer = al_create_timer(1.0 / FPS);
  al_start_timer(timer);

  al_set_window_title(display, "Mahou Shoujo Fighter");
  
  al_register_event_source(event_queue, al_get_timer_event_source(timer));
  al_register_event_source(event_queue, al_get_keyboard_event_source());
  al_register_event_source(event_queue, al_get_display_event_source(display));
}
