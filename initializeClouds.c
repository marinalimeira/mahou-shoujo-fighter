void initializeCloud1(Cloud *cloud);
void initializeCloud2(Cloud *cloud);
void initializeCloud3(Cloud *cloud);

void initializeCloud1(Cloud *cloud){
  (*cloud).x = 400;
  (*cloud).y = 110;

  (*cloud).dirX = -1;
  
  (*cloud).velX = 1;

  (*cloud).image = al_load_bitmap("imgs/miscellaneous/cloud1.bmp");
  al_convert_mask_to_alpha((*cloud).image, al_map_rgb(0, 255, 38));
}

void initializeCloud2(Cloud *cloud){
  (*cloud).x = 50;
  (*cloud).y = 120;

  (*cloud).dirX = -1;
  
  (*cloud).velX = 1;

  (*cloud).image = al_load_bitmap("imgs/miscellaneous/cloud2.bmp");
  al_convert_mask_to_alpha((*cloud).image, al_map_rgb(0, 255, 38));
}

void initializeCloud3(Cloud *cloud){
  (*cloud).x = 800;
  (*cloud).y = 80;

  (*cloud).dirX = -1;
  
  (*cloud).velX = 1;

  (*cloud).image = al_load_bitmap("imgs/miscellaneous/cloud3.bmp");
  al_convert_mask_to_alpha((*cloud).image, al_map_rgb(0, 255, 38));
}
