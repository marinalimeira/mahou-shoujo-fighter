void moveCharacterUp(Character *c);
void moveCharacterDown(Character *c);
void moveCharacterLeft(Character *c);
void moveCharacterRight(Character *c);

void makeHomuraAttack1(Character *c);
void makeMamiAttack1(Character *c);
void makeMamiAttack2(Character *c);
void makeHomuraDefense(Character *c);

void collideBullet(Character *character, Character *enemie);
void drawBullet(Character *c);
void maintenceShield(Character *c);

void animateCharacter(Character *c);
void killCharacter(Character *c);
void stopCharacter(Character *c, int key);

int checkEnd(Character *h, Character *m, int t);

void moveCharacterUp(Character *c){
  c->dirY = -1;
  c->current_sprite = c->running;
}

void moveCharacterDown(Character *c){
  c->dirY = 1;
  c->current_sprite = c->running;
}

void moveCharacterLeft(Character *c){
  c->animationDirection = ALLEGRO_FLIP_HORIZONTAL;
  c->current_sprite = c->running;
}

void moveCharacterRight(Character *c){
  c->animationDirection = 0;
  c->current_sprite = c->running;
}

void makeHomuraAttack1(Character *c){
  if (!c->bullet.fired){
    c->current_sprite = c->attack1;

    if (c->bullet.animationDirection == ALLEGRO_FLIP_HORIZONTAL) {
      c->bullet.animationDirection = 0;
      c->bullet.dirX = 1;
    }
    if (c->animationDirection == 0){
      c->bullet.x = c->x + 80;
    } else {
      c->bullet.x = c->x + 5;
      c->bullet.animationDirection = ALLEGRO_FLIP_HORIZONTAL;
      c->bullet.dirX = -1;
    }
    c->bullet.y = c->y + 47;
    c->bullet.ready = true;
  }
}

void makeMamiAttack1(Character *c){
  if (!c->bullet.fired){
    c->current_sprite = c->attack1;

    if (c->bullet.animationDirection == ALLEGRO_FLIP_HORIZONTAL) {
      c->bullet.animationDirection = 0;
      c->bullet.dirX = -1;
    }
    if (c->animationDirection == 0){
      c->bullet.x = c->x + 5;
    } else {
      c->bullet.x = c->x + 100;
      c->bullet.animationDirection = ALLEGRO_FLIP_HORIZONTAL;
      c->bullet.dirX = 1;
    }
    c->bullet.y = c->y + 60;
    c->bullet.ready = true;
  }
}

void makeMamiAttack2(Character *c){
  if (!c->bullet.fired){
    c->current_sprite = c->attack2;

    if (c->bullet.animationDirection == ALLEGRO_FLIP_HORIZONTAL) {
      c->bullet.animationDirection = 0;
      c->bullet.dirX = -1;
      c->bullet2.animationDirection = 0;
      c->bullet2.dirX = -1;
    }
    if (c->animationDirection == 0){
      c->bullet.x = c->x + 5;
      c->bullet2.x = c->x + 5;
    } else {
      c->bullet.x = c->x + 100;
      c->bullet.animationDirection = ALLEGRO_FLIP_HORIZONTAL;
      c->bullet.dirX = 1;
      c->bullet2.x = c->x + 100;
      c->bullet2.animationDirection = ALLEGRO_FLIP_HORIZONTAL;
      c->bullet2.dirX = 1;
    }
    c->bullet.y = c->y + 65;
    c->bullet2.y = c->y + 65;
    c->bullet.ready = true;
    c->bullet2.ready = true;
  }
}

void makeHomuraDefense(Character *c){
  c->shield.active = true;
  c->shield.active_for = 0;
  c->shield.x = c->x;
  c->shield.y = c->y;
}

void maintenceShield(Character *c){
  c->shield.active_for++;
  if (c->shield.active_time <= c->shield.active_for){
    c->shield.active = false;
    c->shield.active_for = 0;
  }
}

void collideBullet(Character *c, Character *e){
  if (c->bullet.fired) {
    c->bullet.x += c->bullet.speed * c->bullet.dirX;
    // this checks if direction is 1, bullet is in enemy's area, the same if direction is -1 and then checks y
    if (e->has_shield){
      if (e->shield.active){
        if (((((c->bullet.dirX == 1) && (c->bullet.x >= e->x) && (c->x < e->shield.x) &&
              ((c->bullet.x <= e->shield.x + e->shield.width))) || ((c->bullet.dirX == -1)
              && (c->bullet.x <= e->shield.x + e->shield.width) && (c->x > e->shield.x) &&
              (c->bullet.x >= e->shield.x)))) && ((c->bullet.y >= e->shield.y) && (c->bullet.y <= e->shield.heigth + e->shield.y))){
           c->bullet.fired = false;
        }
      }
    }
    if (((((c->bullet.dirX == 1) && (c->bullet.x >= e->x) && (c->x < e->x) &&
              ((c->bullet.x <= e->x + e->current_sprite.width))) || ((c->bullet.dirX == -1)
              && (c->bullet.x <= e->x + e->current_sprite.width) && (c->x > e->x) &&
              (c->bullet.x >= e->x)))) && ((c->bullet.y >= e->y) && (c->bullet.y <= e->current_sprite.heigth + e->y))){
      c->bullet.fired = false;
      e->current_sprite = e->hurt;
      e->dirX = 0;
      e->dirY = 0;
      e->life -= c->bullet.damage;
      if (e->life < 0)
        e->life = 0;
    }
  }
}

void collideBullet2(Character *c, Character *e){
  if (c->bullet2.fired) {
    c->bullet2.x += c->bullet2.speed * c->bullet2.dirX;
    if (e->has_shield){
      if (e->shield.active){
        if (((((c->bullet2.dirX == 1) && (c->bullet2.x >= e->shield.x) && (c->x < e->shield.x) &&
              ((c->bullet2.x <= e->shield.x + e->shield.width))) || ((c->bullet2.dirX == -1)
              && (c->bullet2.x <= e->shield.x + e->shield.width) && (c->x > e->shield.x) &&
              (c->bullet2.x >= e->shield.x)))) && ((c->bullet2.y >= e->shield.y) &&
            (c->bullet2.y <= e->shield.heigth + e->shield.y))){
         c->bullet2.fired = false;
        }
      }
    }
    // this checks if direction is 1, bullet is in enemy's area, the same if direction is -1 and then checks y
    if (((((c->bullet2.dirX == 1) && (c->bullet2.x >= e->x) && (c->x < e->x) &&
              ((c->bullet2.x <= e->x + e->current_sprite.width))) || ((c->bullet2.dirX == -1)
              && (c->bullet2.x <= e->x + e->current_sprite.width) && (c->x > e->x) &&
              (c->bullet2.x >= e->x)))) && ((c->bullet2.y >= e->y) &&
            (c->bullet2.y <= e->current_sprite.heigth + e->y))){
      c->bullet2.fired = false;
      e->current_sprite = e->hurt;
      e->dirX = 0;
      e->dirY = 0;
      e->life -= c->bullet2.damage;
      if (e->life < 0)
        e->life = 0;
    }
  }
}

void killCharacter(Character *c){
  c->live = false;
  c->current_sprite = c->dying;
  c->dirX = 0;
  c->dirY = 0;
}

void animateCharacter(Character *c){
  if(++c->current_sprite.frameCount >= c->current_sprite.frameDelay) {
    if (c->live){
      if(++c->current_sprite.curFrame >= c->current_sprite.maxFrame){
        c->current_sprite.curFrame = 0;
        if (c->current_sprite.limited){
          c->current_sprite = c->idle;
        }
      } else if (c->current_sprite.curFrame <= 0)
        c->current_sprite.curFrame = c->current_sprite.maxFrame - 1;

     c->current_sprite.frameCount = 0;
    } else {
      if (c->current_sprite.curFrame < c->current_sprite.maxFrame - 1){
        c->current_sprite.curFrame++;
      }
    }
  }

  c->x += c->velX * c->dirX;

  if(c->x >= HEIGHT - 128){
    c->x = HEIGHT - 128;
  } else if (c->x <= 0){
    c->x = 0;
  }

  c->y += c->velY * c->dirY;

  if(c->y <= WIDTH - 250){
    c->y = WIDTH - 250;
  } else if (c->y + 130 >= WIDTH){
    c->y = WIDTH - 130;
  }
}

void stopCharacter(Character *c, int key){
  if (((key == c->upKey) || (key == c->downKey) || (key == c->rightKey) ||
    (key == c->leftKey) || (key == c->attack1Key) || (key == c->attack2Key))
    && (!c->current_sprite.limited)){
    c->current_sprite = c->idle;
    c->dirX = 0;
    c->dirY = 0;
  }
}

void drawBullet(Character *c){
  if ((c->bullet.ready) && (c->current_sprite.curFrame == c->bullet.releaseFrame)){
    c->bullet.fired = true;
    c->bullet.ready = false;
  } else if (c->bullet.fired){
    al_draw_bitmap_region(c->bullet.image, 0, 0, c->bullet.heigth, c->bullet.width, c->bullet.x, c->bullet.y, c->bullet.animationDirection);
    if (c->bullet.x >= 900 || c->bullet.x <= -17)
      c->bullet.fired = false;
  }
}

void drawBullet2(Character *c){
  if ((c->bullet2.ready) && (c->current_sprite.curFrame == c->bullet2.releaseFrame)){
    c->bullet2.fired = true;
    c->bullet2.ready = false;
  } else if (c->bullet2.fired){
    al_draw_bitmap_region(c->bullet2.image, 0, 0, c->bullet2.heigth, c->bullet2.width,
        c->bullet2.x, c->bullet2.y, c->bullet2.animationDirection);
    if (c->bullet2.x >= 900 || c->bullet2.x <= -17)
      c->bullet2.fired = false;
  }
}

int checkEnd(Character *h, Character *m, int t){
  int win = 0;

  if (m->life <= 0){
    killCharacter(m);
    win = 1;
  } else if (h->life <= 0){
    killCharacter(h);
    win = 2;
  }

  if (t/20 <= 0){
    if (h->life > m->life){
      killCharacter(m);
      win = 1;
    } else if (h->life == m->life){
      win = 3;
    } else {
      killCharacter(h);
      win = 2;
    }
  }

  return win;
}
