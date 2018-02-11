/*
** EPITECH PROJECT, 2017
** My Hunter
** File description:
** Yup
*/

#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include "../include/my.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	sfVideoMode mode = {800, 600, 32};
	sfRenderWindow *window;
	sfTexture *canard;
	sfTexture *texture;
	sfSprite *sprite;
	sfSprite *sprite_duck;
	sfEvent event;
	sfIntRect rect;
	sfClock *clock = sfClock_create();
	sfTime time;
	sfVector2f position_duck;
	sfVector2i position_mouse;
	float seconds;
	int score = 0;
	int i = 0;
	int rebond = 1;
	float vitesse_duck = 1;
	int fail = 0;

	position_duck.x = 0;
	position_duck.y = 0;
	window = sfRenderWindow_create(mode, "My Hunter", sfResize | sfClose, NULL);
	texture = sfTexture_createFromFile("assets/background.png", NULL);
	canard = sfTexture_createFromFile("assets/spritesheet.png", NULL);
	if (!texture || !canard || !window)
		return (0);
	sprite = sfSprite_create();
	sprite_duck = sfSprite_create();
	rect.top = 0;
	rect.left = 0;
	rect.width = 110;
	rect.height = 110;
	sfSprite_setTexture(sprite, texture, sfTrue);
	sfSprite_setTexture(sprite_duck, canard, sfTrue);
	sfRenderWindow_setFramerateLimit(window, 30);
	while (sfRenderWindow_isOpen(window)) {
		if (position_duck.x == 690) {
			rebond = - 1;
		}
		position_duck.x = position_duck.x + (vitesse_duck * rebond);
		if (position_duck.x == 0) {
			rebond = 1;
		}
		time = sfClock_getElapsedTime(clock);
		seconds = time.microseconds / 1000000.0;
		if (seconds > 0.5) {
			i = i + 1;
			rect.left = rect.left + 110;
			if (i == 3) {
				rect.left = 0;
				i = 0;
			}
			sfSprite_setTextureRect(sprite_duck, rect);
			sfClock_restart(clock);
		}
		while (sfRenderWindow_pollEvent(window, &event)) {
			if (event.type == sfEvtMouseButtonPressed) {
				position_mouse = sfMouse_getPosition(window);
				if (position_mouse.x > position_duck.x && position_mouse.x < position_duck.x + 110 && position_mouse.y > position_duck.y && position_mouse.y < position_duck.y + 110) {
					position_duck.y = rand() % 500;
					position_duck.x = 0;
					rebond = 1;
					score = score + 1;
					if (vitesse_duck < 10) {
						vitesse_duck = vitesse_duck + 1;
					}
					my_printf("score = %d, fail = %d\n", score, fail);
				} else {
					fail = fail + 1;
					my_printf("score = %d, fail = %d\n", score, fail);
				}
			}
			if (event.type == sfEvtClosed || fail >= 3) {
				sfRenderWindow_close(window);
				my_printf("Game Over\n");
			}
		}
		sfSprite_setPosition(sprite_duck, position_duck);
		sfRenderWindow_clear(window, sfBlack);
		sfRenderWindow_drawSprite(window, sprite, NULL);
		sfRenderWindow_drawSprite(window, sprite_duck, NULL);
		sfRenderWindow_display(window);
	}
	sfSprite_destroy(sprite);
	sfRenderWindow_destroy(window);
	return (0);
}