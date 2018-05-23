#include <stdio.h>
#include <allegro5/allegro.h>
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"

int main(int argc, char **argv) {

	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_BITMAP  *bloque = NULL;
	ALLEGRO_BITMAP  *player = NULL;


	if (!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}

	display = al_create_display(800, 600);
	if (!display) {
		fprintf(stderr, "failed to create display!\n");
		return -1;
	}

	if (!al_init_image_addon()) {
		al_show_native_message_box(display, "Error", "Error", "Failed to initialize al_init_image_addon!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return 0;
	}

	bloque = al_load_bitmap("bloque.jpg");

	if (!bloque) {
		al_show_native_message_box(display, "Error", "Error", "Failed to load image!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(display);
		return 0;
	}

	player = al_load_bitmap("player.jpg");

	if (!player) {
		al_show_native_message_box(display, "Error", "Error", "Failed to load image!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(display);
		return 0;
	}

	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_draw_bitmap(bloque, 700, 60, 0);
	al_draw_bitmap(player, 200, 60, 0);

	al_flip_display();

	al_rest(1);

	al_destroy_display(display);

	al_destroy_bitmap(bloque);
	al_destroy_bitmap(player);

	return 0;
}