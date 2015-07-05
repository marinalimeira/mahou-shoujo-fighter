void moveCharacterUp(Character *c);
void moveCharacterDown(Character *c);
void moveCharacterLeft(Character *c);
void moveCharacterRight(Character *c);
void makeHomuraAttack1(Character *c);
void makeMamiAttack1(Character *c);
void makeAttack2(Character *c);
void collideBullet(Character *character, Character *enemie);
void killCharacter(Character *c);
void animateCharacter(Character *c);
void stopCharacter(Character *c, int key);
void drawBullet(Character *c);

void moveCharacterUp(Character *c){
  (*c).dirY = -1;
  (*c).current_sprite = (*c).running;
}

void moveCharacterDown(Character *c){
  (*c).dirY = 1;
  (*c).current_sprite = (*c).running;
}

void moveCharacterLeft(Character *c){
  (*c).animationDirection = ALLEGRO_FLIP_HORIZONTAL;  
  (*c).current_sprite = (*c).running;
}

void moveCharacterRight(Character *c){
  (*c).animationDirection = 0;
  (*c).current_sprite = (*c).running;
}

void makeHomuraAttack1(Character *c){
  if (!(*c).bullet.fired){
    (*c).current_sprite = (*c).attack1;

    if ((*c).bullet.animationDirection == ALLEGRO_FLIP_HORIZONTAL) {
      (*c).bullet.animationDirection = 0;
      (*c).bullet.dirX = 1;
    }
    if ((*c).animationDirection == 0){
      (*c).bullet.x = (*c).x + 96;
    } else {
      (*c).bullet.x = (*c).x - 13;
      (*c).bullet.animationDirection = ALLEGRO_FLIP_HORIZONTAL; 
      (*c).bullet.dirX = -1;
    }
    (*c).bullet.y = (*c).y + 47;
    (*c).bullet.fired = true;
  }
}

void makeMamiAttack1(Character *c){
  if (!(*c).bullet.fired){
    (*c).current_sprite = (*c).attack1;

    if ((*c).bullet.animationDirection == ALLEGRO_FLIP_HORIZONTAL) {
      (*c).bullet.animationDirection = 0;
      (*c).bullet.dirX = -1;
    }
    if ((*c).animationDirection == 0){
      (*c).bullet.x = (*c).x - 6;
    } else {
      (*c).bullet.x = (*c).x + 27;       
      (*c).bullet.animationDirection = ALLEGRO_FLIP_HORIZONTAL; 
      (*c).bullet.dirX = 1;
    }
    (*c).bullet.y = (*c).y + 55;     
    (*c).bullet.fired = true;
  }
}

void makeAttack2(Character *c){
  (*c).current_sprite = (*c).attack2;
}

void collideBullet(Character *c, Character *e){
  if ((*c).bullet.fired) {
    (*c).bullet.x += (*c).bullet.speed * (*c).bullet.dirX;
    if (((((*c).bullet.x >= (*e).x && (*c).bullet.dirX == 1 && ((*c).x < (*e).x)) || 
        ((*c).bullet.x <= (*e).x + 100 && (*c).bullet.dirX == -1 && ((*c).x > (*e).x)))) &&
        (((*c).bullet.y >= (*e).y) && ((*c).bullet.y <= (*e).current_sprite.width + (*e).y))){
      (*c).bullet.fired = false;
      (*e).current_sprite = (*e).hurt;
      (*e).life -= (*c).bullet.damage;
    }
  }
}

void killCharacter(Character *c){
  (*c).live = false;
  (*c).current_sprite = (*c).dying;
}

void animateCharacter(Character *c){
  if(++(*c).current_sprite.frameCount >= (*c).current_sprite.frameDelay) {
    if(++(*c).current_sprite.curFrame >= (*c).current_sprite.maxFrame){
      (*c).current_sprite.curFrame = 0;
       if ((*c).current_sprite.limited)
        (*c).current_sprite = (*c).idle;
    } else if ((*c).current_sprite.curFrame <= 0)
      (*c).current_sprite.curFrame = (*c).current_sprite.maxFrame - 1;

    (*c).current_sprite.frameCount = 0;
  }

  (*c).x += (*c).velX * (*c).dirX;

  if((*c).x >= HEIGHT - 128){
    (*c).x = HEIGHT - 128;
  }
  else if ((*c).x <= 0){
    (*c).x = 0;
  }

  (*c).y += (*c).velY * (*c).dirY;

  if((*c).y <= WIDTH - 250){
    (*c).y = WIDTH - 250;
  } else if ((*c).y + 130 >= WIDTH){
    (*c).y = WIDTH - 130;
  }
}

void stopCharacter(Character *c, int key){
  if ((key == (*c).upKey) || (key == (*c).downKey) ||
    (key == (*c).rightKey) || (key == (*c).leftKey) ||
    (key == (*c).attack1Key) || (key == (*c).attack2Key)){
    (*c).current_sprite = (*c).idle;
    (*c).dirX = 0;  
    (*c).dirY = 0; 
  }
}

void drawBullet(Character *c){
  if ((*c).bullet.fired){
    al_draw_bitmap_region((*c).bullet.image, 0, 0, (*c).bullet.heigth, (*c).bullet.width, (*c).bullet.x, (*c).bullet.y, (*c).bullet.animationDirection);
    if ((*c).bullet.x >= 900 || (*c).bullet.x <= -17)
      (*c).bullet.fired = false; 
  }
}
