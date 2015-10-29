initializeStart(MenuItem *start){
  start->selected = al_load_bitmap("imgs/menu-itens/start_selected.bmp");
  al_convert_mask_to_alpha(start->selected, al_map_rgb(0, 255, 38));
  start->not_selected = al_load_bitmap("imgs/menu-itens/start.bmp");
  al_convert_mask_to_alpha(start->not_selected, al_map_rgb(0, 255, 38));
  start->current = start->not_selected;
}

initializeScores(MenuItem *scores){
  scores->selected = al_load_bitmap("imgs/menu-itens/scores_selected.bmp");
  al_convert_mask_to_alpha(scores->selected, al_map_rgb(0, 255, 38));
  scores->not_selected = al_load_bitmap("imgs/menu-itens/scores.bmp");
  al_convert_mask_to_alpha(scores->not_selected, al_map_rgb(0, 255, 38));
  scores->current = scores->not_selected;
}

initializeSettings(MenuItem *settings){
  settings->selected = al_load_bitmap("imgs/menu-itens/settings_selected.bmp");
  al_convert_mask_to_alpha(settings->selected, al_map_rgb(0, 255, 38));
  settings->not_selected = al_load_bitmap("imgs/menu-itens/settings.bmp");
  al_convert_mask_to_alpha(settings->not_selected, al_map_rgb(0, 255, 38));
  settings->current = settings->not_selected;
}

initializeExit(MenuItem *ex1t){
  ex1t->selected = al_load_bitmap("imgs/menu-itens/exit_selected.bmp");
  al_convert_mask_to_alpha(ex1t->selected, al_map_rgb(0, 255, 38));
  ex1t->not_selected = al_load_bitmap("imgs/menu-itens/exit.bmp");
  al_convert_mask_to_alpha(ex1t->not_selected, al_map_rgb(0, 255, 38));
  ex1t->current = ex1t->not_selected;
}
