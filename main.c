#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#define HEIGHT 900
#define WIDTH 600

  ALLEGRO_DISPLAY *display = NULL;
  ALLEGRO_BITMAP *background = NULL;
  ALLEGRO_EVENT_QUEUE *event_queue = NULL;
  ALLEGRO_BITMAP *image = NULL;
  ALLEGRO_TIMER *timer;

void init(){
  if (!al_init() ? printf("Failed to initialize Allegro.\n") : 0); 

  if (!al_install_keyboard() ? printf("Failed to install Keyboard.\n") : 0);

  if (!al_init_image_addon() ? printf("Failed to initialize add-on allegro_image.\n") : 0);
}

void main(int argc, int **argv){

  int x = 0;
  int y = 400;
  int curFrame = 0;
  int frameCount = 0;
  int frameDelay = 5;
  int frameWidthHomura = 108;
  int frameHeightHomura = 128;
  const int maxFrame = 7;

  init();

  display = al_create_display(HEIGHT, WIDTH);
  if (!display ? printf("Failed to create display.\n") : 0);

  background = al_load_bitmap("imgs/bg.png");
  if (!background ? printf("Fail to load background.\n") : 0);

  event_queue = al_create_event_queue();

  al_register_event_source(event_queue, al_get_display_event_source(display));

  al_draw_bitmap(background, 0, 0, 0);

  image = al_load_bitmap("imgs/sprites/running/homura_running_by_konbe-transparent.bmp");
  al_convert_mask_to_alpha(image, al_map_rgb(0, 255, 38));
  
  timer = al_create_timer(1.0 / 60);
  al_register_event_source(event_queue, al_get_timer_event_source(timer));
  al_start_timer(timer);
  

  while (1) {
      ALLEGRO_EVENT event;
      ALLEGRO_TIMEOUT timeout;
      al_init_timeout(&timeout, 0.05);

      int has_events = al_wait_for_event_until(event_queue, &event, &timeout);

      if (has_events && event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
          break;
      }

      if(event.type == ALLEGRO_EVENT_TIMER) {
        if(++frameCount >= frameDelay)
        {
          if(++curFrame >= maxFrame)
            curFrame = 0;

          frameCount = 0;
        }

        x += 2;

        if(x > HEIGHT)
          x = 0;
      }

      al_draw_bitmap_region(image, curFrame * frameWidthHomura, 0, frameWidthHomura, frameHeightHomura, x, y, 0);
      al_flip_display();
      al_draw_bitmap(background, 0, 0, 0);
  }

  al_destroy_event_queue(event_queue);
  al_destroy_display(display);
  
}