#include <pebble.h>

Window *my_window;
TextLayer *text_layer;
TextLayer *text_layer2;
static BitmapLayer *s_background_layer;
static GBitmap *s_background_bitmap;

void handle_second_tick(struct tm *tick_time, TimeUnits units_changed) {
  static char buf[40];
  text_layer_set_text(text_layer,"OYATSU TIME");
//  snprintf(buf,40,"%02d:%02d:%02d" , tick_time->tm_hour , tick_time->tm_min ,  tick_time->tm_sec);
  snprintf(buf,40,"%02d:%02d" , tick_time->tm_hour , tick_time->tm_min );
  text_layer_set_text(text_layer2,buf);
}

void handle_init(void) {
  my_window = window_create();

s_background_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_PATSUUSA2);
s_background_layer = bitmap_layer_create(GRect(0, 168-82, 144, 82));
bitmap_layer_set_bitmap(s_background_layer, s_background_bitmap);
layer_add_child(window_get_root_layer(my_window), bitmap_layer_get_layer(s_background_layer));
   
  
  text_layer = text_layer_create(GRect(20, 10, 144, 20));
  layer_add_child( window_get_root_layer(my_window), text_layer_get_layer(text_layer));
  text_layer2 = text_layer_create(GRect(20, 25, 144, 44));
//  text_layer_set_font(text_layer2, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
  text_layer_set_font(text_layer2, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
  layer_add_child( window_get_root_layer(my_window), text_layer_get_layer(text_layer2));
  
  window_stack_push(my_window, true);
  tick_timer_service_subscribe(SECOND_UNIT, handle_second_tick);
}

void handle_deinit(void) {
  text_layer_destroy(text_layer);
  window_destroy(my_window);
  
  gbitmap_destroy(s_background_bitmap);
  bitmap_layer_destroy(s_background_layer);
}

int main(void) {
  handle_init();
  app_event_loop();
  handle_deinit();
}
