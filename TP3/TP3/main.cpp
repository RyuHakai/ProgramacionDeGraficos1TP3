#include <stdio.h>
#include <allegro5/allegro.h>
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

const float FPS = 60;
const int SCREEN_W = 640;
const int SCREEN_H = 480;
const int BOUNCER_SIZE = 32;
const int START_SIZE = 200;
const int BULLET_SIZE = 16;
const int LIFE_SIZE = 64;
const int HALF = 16;
const int HALF_B = 8;
enum MYKEYS {
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_SPACE
};

int main(int argc, char **argv)
{
	ALLEGRO_DISPLAY *display = NULL;
	//ALLEGRO_SAMPLE *sample = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP  *bloque = NULL;
	ALLEGRO_BITMAP  *bloque2 = NULL;
	ALLEGRO_BITMAP  *player = NULL;
	ALLEGRO_BITMAP  *bullet = NULL;
	ALLEGRO_BITMAP  *start = NULL;
	ALLEGRO_BITMAP  *end = NULL;
	ALLEGRO_BITMAP  *life3_cont = NULL;
	ALLEGRO_BITMAP  *life2_cont = NULL;
	ALLEGRO_BITMAP  *life1_cont = NULL;
	float player_x = SCREEN_W *0.5 - BOUNCER_SIZE *0.5;
	float player_y = SCREEN_H *0.5 - BOUNCER_SIZE *0.5;
	float bloque_x = SCREEN_W * 0.25 - BOUNCER_SIZE *0.5;
	float bloque_y = SCREEN_H * 0.25 - BOUNCER_SIZE *0.5;
	float bloque2_x = SCREEN_W * 0.75 - BOUNCER_SIZE *0.5;
	float bloque2_y = SCREEN_H * 0.75 - BOUNCER_SIZE *0.5;
	float start_x = SCREEN_W *0.5 - START_SIZE *0.5;
	float start_y = SCREEN_H *0.5 - START_SIZE *0.5;
	float bullet_x = player_x + HALF_B;
	float bullet_y = player_y + HALF_B;
	float life3_cont_y = 0;
	float life3_cont_x = SCREEN_W - LIFE_SIZE;
	float life2_cont_y = 0;
	float life2_cont_x = SCREEN_W - LIFE_SIZE;
	float life1_cont_y = 0;
	float life1_cont_x = SCREEN_W - LIFE_SIZE;
	bool patrulla_x = true;
	bool patrulla2_x = true;
	bool key[5] = { false, false, false, false, false };
	bool redraw = true;
	bool doexit = false;
	bool player_live = true;
	int vidas = 3;
	int inmunidad = 0;
	bool bullet_live = false;
	int bullet_dir = 1;
	int bullet_dir_Dead = 1;
	bool bloque_live = true;
	bool bloque2_live = true;
	bool start_live = true;
	int start_cont = 0;
	bool end_live = false;
//checkeos-----------------------------------------------------------------------
	if (!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}

	if (!al_install_keyboard()) {
		fprintf(stderr, "failed to initialize the keyboard!\n");
		return -1;
	}

	timer = al_create_timer(1.0 / FPS);
	if (!timer) {
		fprintf(stderr, "failed to create timer!\n");
		return -1;
	}

	display = al_create_display(SCREEN_W, SCREEN_H);
	if (!display) {
		fprintf(stderr, "failed to create display!\n");
		al_destroy_timer(timer);
		return -1;
	}

	if (!al_init_image_addon()) {
		al_show_native_message_box(display, "Error", "Error", "Failed to initialize al_init_image_addon!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return 0;
	}
//audio---------------------------------------------------------------------------
	/*	if (!al_install_audio()) {
	fprintf(stderr, "failed to initialize audio!\n");
	return -1;
	}

	if (!al_init_acodec_addon()) {
	fprintf(stderr, "failed to initialize audio codecs!\n");
	return -1;
	}

	if (!al_reserve_samples(1)) {
	fprintf(stderr, "failed to reserve samples!\n");
	return -1;
	}
	sample = al_load_sample("Fantasy_Game_Background.wav");

	if (!sample) {
	printf("Audio clip sample not loaded!\n");
	return -1;
	}*/

//carga--------------------------------------------------------------------------
	bloque = al_load_bitmap("bloque.jpg");

	if (!bloque) {
		al_show_native_message_box(display, "Error", "Error", "Failed to load image!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(display);
		return 0;
	}
	bloque2 = al_load_bitmap("bloque.jpg");

	if (!bloque2) {
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
	bullet = al_load_bitmap("Bullet.png");

	if (!bullet) {
		al_show_native_message_box(display, "Error", "Error", "Failed to load image!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(display);
		return 0;
	}
	start = al_load_bitmap("Start.png");
	if (!start) {
		al_show_native_message_box(display, "Error", "Error", "Failed to load image!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(display);
		return 0;
	}
	end = al_load_bitmap("GameOver.png");
	if (!end) {
		al_show_native_message_box(display, "Error", "Error", "Failed to load image!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(display);
		return 0;
	}
	life3_cont = al_load_bitmap("Life3.png");

	if (!life3_cont) {
		al_show_native_message_box(display, "Error", "Error", "Failed to load image!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(display);
		return 0;
	}
	life2_cont = al_load_bitmap("Life2.png");

	if (!life2_cont) {
		al_show_native_message_box(display, "Error", "Error", "Failed to load image!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(display);
		return 0;
	}
	life1_cont = al_load_bitmap("Life1.png");

	if (!life1_cont) {
		al_show_native_message_box(display, "Error", "Error", "Failed to load image!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(display);
		return 0;
	}

	al_clear_to_color(al_map_rgb(255, 0, 255));

	al_set_target_bitmap(al_get_backbuffer(display));

	event_queue = al_create_event_queue();
	if (!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_bitmap(player);
		al_destroy_bitmap(bloque);
		al_destroy_bitmap(bloque2);
		al_destroy_bitmap(bullet);
		al_destroy_bitmap(life3_cont);
		al_destroy_bitmap(life2_cont);
		al_destroy_bitmap(life1_cont);
		al_destroy_bitmap(start);
		al_destroy_bitmap(end);
		//al_destroy_sample(sample);
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}

	al_register_event_source(event_queue, al_get_display_event_source(display));

	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_flip_display();

	al_start_timer(timer);

	while (!doexit)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		//al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);
		//al_rest(10.0);

		if (ev.type == ALLEGRO_EVENT_TIMER) {
			if (key[KEY_UP] && player_y >= 4.0) {
				player_y -= 4.0;
				bullet_dir_Dead = 1;
				if (!bullet_live) {
					bullet_y -= 4.0;
				}
			}

			if (key[KEY_DOWN] && player_y <= SCREEN_H - BOUNCER_SIZE - 4.0) {
				player_y += 4.0;
				bullet_dir_Dead = 2;
				if (!bullet_live) {
					bullet_y += 4.0;
				}
			}

			if (key[KEY_LEFT] && player_x >= 4.0) {
				player_x -= 4.0;
				bullet_dir_Dead = 3;
				if (!bullet_live) {
					bullet_x -= 4.0;
				}
			}

			if (key[KEY_RIGHT] && player_x <= SCREEN_W - BOUNCER_SIZE - 4.0) {
				player_x += 4.0;
				bullet_dir_Dead = 4;
				if (!bullet_live) {
					bullet_x += 4.0;
				}
			}
			if (key[KEY_SPACE] && !bullet_live) {
				bullet_live = true;
				bullet_dir = bullet_dir_Dead;
			}
			if (bloque_live) {
				if (patrulla_x) {
					bloque_x += 2;
					if (bloque_x >= 480)
						patrulla_x = false;
				}
				if (!patrulla_x) {
					bloque_x -= 2;
					if (bloque_x <= 160)
						patrulla_x = true;
				}
			}
			if (bloque2_live) {
				if (patrulla2_x) {
					bloque2_x += 2;
					if (bloque2_x >= 480)
						patrulla2_x = false;
				}
				if (!patrulla2_x) {
					bloque2_x -= 2;
					if (bloque2_x <= 160)
						patrulla2_x = true;
				}
			}
			if (bullet_live) {
				switch (bullet_dir) {
				case 1:
					bullet_y -= 4.0;
					break;
				case 2:
					bullet_y += 4.0;
					break;
				case 3:
					bullet_x -= 4.0;
					break;
				case 4:
					bullet_x += 4.0;
					break;
				default:
					break;
				}
			}
			if (inmunidad > 0)
				inmunidad--;
			if (start_cont < 60)
				start_cont++;
			if (start_cont >= 60)
				start_live = false;
			if (bloque_live && player_live) {
				if (player_x + HALF > bloque_x - HALF && player_x - HALF < bloque_x + HALF)
					if (player_y + HALF > bloque_y - HALF && player_y - HALF < bloque_y + HALF)
						if (inmunidad == 0) {
							vidas -= 1;
							inmunidad = 60;
							if (vidas <= 0) {
								end_live = true;
								bloque_live = false;
								bloque2_live = false;
							}
						}
			}
			if (bloque2_live && player_live) {
				if (player_x + HALF > bloque2_x - HALF && player_x - HALF < bloque2_x + HALF)
					if (player_y + HALF > bloque2_y - HALF && player_y - HALF < bloque2_y + HALF)
						if (inmunidad == 0) {
							vidas -= 1;
							inmunidad = 60;
							if (vidas <= 0) {
								end_live = true;
								player_live = false;
								bloque_live = false;
								bloque2_live = false;
							}

						}
			}
			if (bloque_live && bullet_live) {
				if (bullet_x + HALF_B > bloque_x - HALF && bullet_x - HALF_B < bloque_x + HALF)
					if (bullet_y + HALF_B > bloque_y - HALF && bullet_y - HALF_B < bloque_y + HALF) {
						bloque_live = false;
						bullet_live = false;
						bullet_y = player_y + HALF_B;
						bullet_x = player_x + HALF_B;
					}
			}
			if (bloque2_live && bullet_live) {
				if (bullet_x + HALF_B > bloque2_x - HALF && bullet_x - HALF_B < bloque2_x + HALF)
					if (bullet_y + HALF_B > bloque2_y - HALF && bullet_y - HALF_B < bloque2_y + HALF) {
						bloque2_live = false;
						bullet_live = false;
						bullet_y = player_y + HALF_B;
						bullet_x = player_x + HALF_B;
					}
			}
			if (bullet_live) {
				if (bullet_x < 0 || bullet_x > SCREEN_W || bullet_y < 0 || bullet_y > SCREEN_H) {
					bullet_live = false;
					bullet_y = player_y + HALF_B;
					bullet_x = player_x + HALF_B;
				}
			}
			if (!bloque2_live && !bloque_live) {
				end_live = true;
				player_live = false;
			}
			redraw = true;
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				key[KEY_UP] = true;
				break;

			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = true;
				break;

			case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = true;
				break;

			case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = true;
				break;

			case ALLEGRO_KEY_SPACE:
				key[KEY_SPACE] = true;
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				key[KEY_UP] = false;
				break;

			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = false;
				break;

			case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = false;
				break;

			case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = false;
				break;

			case ALLEGRO_KEY_SPACE:
				key[KEY_SPACE] = false;
				break;

			case ALLEGRO_KEY_ESCAPE:
				doexit = true;
				break;
			}
		}

		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;

			al_clear_to_color(al_map_rgb(0, 0, 0));
			if (!start_live || end_live) {
				if (vidas > 0 && player_live)
					al_draw_bitmap(player, player_x, player_y, 0);
				if (bloque_live)
					al_draw_bitmap(bloque, bloque_x, bloque_y, 0);
				if (bloque2_live)
					al_draw_bitmap(bloque, bloque2_x, bloque2_y, 0);
				if (bullet_live)
					al_draw_bitmap(bullet, bullet_x, bullet_y, 0);
				if (vidas == 3 && player_live)
					al_draw_bitmap(life3_cont, life3_cont_x, life3_cont_y, 0);
				if (vidas == 2 && player_live)
					al_draw_bitmap(life2_cont, life2_cont_x, life2_cont_y, 0);
				if (vidas == 1 && player_live)
					al_draw_bitmap(life1_cont, life1_cont_x, life1_cont_y, 0);
			}
			if(start_live)
				al_draw_bitmap(start, start_x, start_y, 0);
			if(end_live)
				al_draw_bitmap(end, start_x, start_y, 0);
		}
			al_flip_display();
	}

	al_destroy_bitmap(player);
	al_destroy_bitmap(bloque);
	al_destroy_bitmap(bloque2);
	al_destroy_bitmap(bullet);
	al_destroy_bitmap(life3_cont);
	al_destroy_bitmap(life2_cont);
	al_destroy_bitmap(life1_cont);
	al_destroy_bitmap(start);
	al_destroy_timer(timer);
	//al_destroy_sample(sample);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

	return 0;
}