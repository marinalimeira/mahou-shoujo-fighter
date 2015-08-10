void moveCloud(Cloud *c);

void moveCloud(Cloud *c){
  c->x += c->velX * c->dirX;
  if (c->x <= -300){
    c->x = 900;
  }
}
