#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#define HEIGHT 900
#define WIDTH 600

void init(){
  if (al_init()){
    printf("Allegro started.\n");
  }

  if (al_install_keyboard()){
    printf("Keyboard installed.\n");
  }
}

int main(int argc, int **argv){
  
  ALLEGRO_DISPLAY *display = NULL;
  ALLEGRO_BITMAP *background = NULL;

  init();

  al_init_image_addon();

  background = al_load_bitmap("imgs/bg.jpg");
  printf("Background loaded.\n");

  display = al_create_display(HEIGHT, WIDTH);
  printf("Display created.\n");

  al_draw_bitmap(background, 0, 0, 0);

  al_flip_display();

  al_rest(10.0);
  al_destroy_display(display);
  
}