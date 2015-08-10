void initializeHomura(Character *homura);
void initializeMami(Character *mami);

void initializeHomura(Character *homura){
  homura->life = 100;
  homura->upKey = ALLEGRO_KEY_W;
  homura->downKey = ALLEGRO_KEY_S;
  homura->leftKey = ALLEGRO_KEY_A;
  homura->rightKey = ALLEGRO_KEY_D;
  homura->attack1Key = ALLEGRO_KEY_Q;
  homura->attack2Key = ALLEGRO_KEY_E;

  homura->x = 100;
  homura->y = 400;
  homura->animationDirection = 0;

  homura->velX = 5;
  homura->velY = 5;
  homura->dirX = 0;
  homura->dirY = 0;

  homura->running.heigth = 128;
  homura->running.width = 108;
  homura->running.maxFrame = 7;
  homura->running.curFrame = 0;
  homura->running.frameCount = 0;
  homura->running.frameDelay = 2;
  homura->running.limited = false;

  homura->running.image = al_load_bitmap("imgs/sprites/running/homura_running_by_konbe.bmp");
  al_convert_mask_to_alpha(homura->running.image, al_map_rgb(0, 255, 38));

  homura->idle.heigth = 128;
  homura->idle.width = 98;
  homura->idle.maxFrame = 8;
  homura->idle.curFrame = 0;
  homura->idle.frameCount = 0;
  homura->idle.frameDelay = 2;
  homura->idle.limited = false;

  homura->idle.image = al_load_bitmap("imgs/sprites/idle/homura_idle_by_konbe.bmp");
  al_convert_mask_to_alpha(homura->idle.image, al_map_rgb(0, 255, 38));

  homura->attack1.heigth = 128;
  homura->attack1.width = 100;
  homura->attack1.maxFrame = 8;
  homura->attack1.curFrame = 0;
  homura->attack1.frameCount = 0;
  homura->attack1.frameDelay = 2;
  homura->attack1.limited = true;

  homura->attack1.image = al_load_bitmap("imgs/sprites/attacking/homura_attack1_by_konbe.bmp");
  al_convert_mask_to_alpha(homura->attack1.image, al_map_rgb(0, 255, 38));

  homura->attack2.heigth = 128;
  homura->attack2.width = 74;
  homura->attack2.maxFrame = 7;
  homura->attack2.curFrame = 0;
  homura->attack2.frameCount = 0;
  homura->attack2.frameDelay = 2;
  homura->attack2.limited = true;

  homura->attack2.image = al_load_bitmap("imgs/sprites/attacking/homura_attack2_by_konbe.bmp");
  al_convert_mask_to_alpha(homura->attack2.image, al_map_rgb(0, 255, 38));

  homura->hurt.heigth = 140;
  homura->hurt.width = 91;
  homura->hurt.maxFrame = 5;
  homura->hurt.curFrame = 0;
  homura->hurt.frameCount = 0;
  homura->hurt.frameDelay = 2;
  homura->hurt.limited = true;

  homura->hurt.image = al_load_bitmap("imgs/sprites/hurt/homura_hurt_by_konbe.bmp");
  al_convert_mask_to_alpha(homura->hurt.image, al_map_rgb(0, 255, 38));

  homura->dying.heigth = 140;
  homura->dying.width = 120;
  homura->dying.maxFrame = 13;
  homura->dying.curFrame = 0;
  homura->dying.frameCount = 0;
  homura->dying.frameDelay = 2;
  homura->dying.limited = true;

  homura->dying.image = al_load_bitmap("imgs/sprites/dying/homura_dying_by_konbe.bmp");
  al_convert_mask_to_alpha(homura->dying.image, al_map_rgb(0, 255, 38));

  homura->bullet.releaseFrame = 3;
  homura->bullet.heigth = 12; 
  homura->bullet.width = 6;
  homura->bullet.fired = false;
  homura->bullet.ready = false;
  homura->bullet.speed = 10;
  homura->bullet.damage = 6;
  homura->bullet.dirX = 1;
  homura->bullet.animationDirection = 0;
  homura->bullet.image = al_load_bitmap("imgs/miscellaneous/homura_bullet.bmp");
  al_convert_mask_to_alpha(homura->bullet.image, al_map_rgb(0, 255, 38));

  homura->current_sprite = homura->idle;
}

void initializeMami(Character *mami){
  mami->life = 100;
  mami->upKey = ALLEGRO_KEY_I;
  mami->downKey = ALLEGRO_KEY_K;
  mami->leftKey = ALLEGRO_KEY_L;
  mami->rightKey = ALLEGRO_KEY_J;
  mami->attack1Key = ALLEGRO_KEY_U;
  mami->attack2Key = ALLEGRO_KEY_O;

  mami->x = 670;
  mami->y = 400;
  mami->animationDirection = 0;

  mami->velX = 5;
  mami->velY = 5;
  mami->dirX = 0;
  mami->dirY = 0;

  mami->running.heigth = 128;
  mami->running.width = 108;
  mami->running.maxFrame = 8;
  mami->running.curFrame = 0;
  mami->running.frameCount = 0;
  mami->running.frameDelay = 2;
  mami->running.limited = false;

  mami->running.image = al_load_bitmap("imgs/sprites/running/mami_running_by_konbe.bmp");
  al_convert_mask_to_alpha(mami->running.image, al_map_rgb(0, 255, 38));

  mami->idle.heigth = 128;
  mami->idle.width = 103;
  mami->idle.maxFrame = 6;
  mami->idle.curFrame = 0;
  mami->idle.frameCount = 0;
  mami->idle.frameDelay = 2;
  mami->idle.limited = false;

  mami->idle.image = al_load_bitmap("imgs/sprites/idle/mami_idle_by_konbe.bmp");
  al_convert_mask_to_alpha(mami->idle.image, al_map_rgb(0, 255, 38));

  mami->attack1.heigth = 150;
  mami->attack1.width = 120;
  mami->attack1.maxFrame = 8;
  mami->attack1.curFrame = 0;
  mami->attack1.frameCount = 0;
  mami->attack1.frameDelay = 2;
  mami->attack1.limited = true;

  mami->attack1.image = al_load_bitmap("imgs/sprites/attacking/mami_attack1_by_konbe.bmp");
  al_convert_mask_to_alpha(mami->attack1.image, al_map_rgb(0, 255, 38));

  mami->attack2.heigth = 140;
  mami->attack2.width = 141;
  mami->attack2.maxFrame = 18;
  mami->attack2.curFrame = 0;
  mami->attack2.frameCount = 0;
  mami->attack2.frameDelay = 2;
  mami->attack2.limited = true;

  mami->attack2.image = al_load_bitmap("imgs/sprites/attacking/mami_attack2_by_konbe.bmp");
  al_convert_mask_to_alpha(mami->attack2.image, al_map_rgb(0, 255, 38));

  mami->hurt.heigth = 140;
  mami->hurt.width = 124;
  mami->hurt.maxFrame = 6;
  mami->hurt.curFrame = 0;
  mami->hurt.frameCount = 0;
  mami->hurt.frameDelay = 2;
  mami->hurt.limited = true;

  mami->hurt.image = al_load_bitmap("imgs/sprites/hurt/mami_hurt_by_konbe.bmp");
  al_convert_mask_to_alpha(mami->hurt.image, al_map_rgb(0, 255, 38));

  mami->dying.heigth = 140;
  mami->dying.width = 134;
  mami->dying.maxFrame = 12;
  mami->dying.curFrame = 0;
  mami->dying.frameCount = 0;
  mami->dying.frameDelay = 2;
  mami->dying.limited = true;

  mami->dying.image = al_load_bitmap("imgs/sprites/dying/mami_dying_by_konbe.bmp");
  al_convert_mask_to_alpha(mami->dying.image, al_map_rgb(0, 255, 38));

  mami->bullet.releaseFrame = 5;
  mami->bullet.heigth = 14; 
  mami->bullet.width = 5;
  mami->bullet.fired = false;
  mami->bullet.ready = false;
  mami->bullet.speed = 10;
  mami->bullet.damage = 6;
  mami->bullet.dirX = -1;
  mami->bullet.animationDirection = 0;
  mami->bullet.image = al_load_bitmap("imgs/miscellaneous/mami_bullet.bmp");
  al_convert_mask_to_alpha(mami->bullet.image, al_map_rgb(0, 255, 51));

  mami->current_sprite = mami->idle;
}
