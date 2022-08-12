#include "../mlx/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include "minhee.h"
//used printf: replace with a custom error writing function

#define X_EVENT_KEY_PRESS	2
#define X_EVENT_EXIT		17

#define	KEY_ESC	53
#define KEY_W	13
#define KEY_A	0
#define	KEY_S	1
#define	KEY_D	2
#define KEY_LEFT	123
#define	KEY_RIGHT	124

int	exit_game(void) // <- need to free all heap memory: pass struct!
{
	printf("bye!\n");
	exit(0);
	return (0);
}

int	key_press(int keycode, t_game *game)
{
	t_keys *keys = game->keys;
	if (keycode == KEY_W)
		game->map->player.pos_y += TYPE_MAN_PLAYER_POS;
	else if (keycode == KEY_S)
		game->map->player.pos_y -= TYPE_MAN_PLAYER_POS;
	else if (keycode == KEY_A)
		game->map->player.pos_x -= TYPE_MAN_PLAYER_POS;
	else if (keycode == KEY_D)
		game->map->player.pos_x += TYPE_MAN_PLAYER_POS;
	else if (keycode == KEY_LEFT)
		game->map->player.vision_theta += TYPE_MAN_PLAYER_ANGLE;
	else if (keycode == KEY_RIGHT)
		game->map->player.vision_theta -= TYPE_MAN_PLAYER_ANGLE;
	else if (keycode == KEY_ESC)
		exit_game();
	printf("x: %f y: %f angle: %f\n", game->map->player.pos_x, game->map->player.pos_y, game->map->player.vision_theta);
	return (0);
}

int	exit_hook(void)
{
	return exit_game();
}

int	init_img(t_game *game)
{
	char	*temp;
	int		img_w;
	int		img_h;

	temp = game->map->n_path;
	game->mlx->n_img = mlx_xpm_file_to_image(game->mlx->mlx, temp, &img_w, &img_h);
	if (temp != NULL)
		free(temp);
	temp = game->map->s_path;
	game->mlx->s_img = mlx_xpm_file_to_image(game->mlx->mlx, temp, &img_w, &img_h);
	if (temp != NULL)
		free(temp);
	temp = game->map->w_path;
	game->mlx->w_img = mlx_xpm_file_to_image(game->mlx->mlx, temp, &img_w, &img_h);
	if (temp != NULL)
		free(temp);
	temp = game->map->e_path;
	game->mlx->e_img = mlx_xpm_file_to_image(game->mlx->mlx, temp, &img_w, &img_h);
	if (temp != NULL)
		free(temp);
	if (game->mlx->n_img && game->mlx->s_img && game->mlx->w_img && game->mlx->e_img)
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_game	game;
	t_keys	keys;

	// parse map & check
	if (argc != 2)
	{
		printf("wrong number of arguments\n");
		return (0);
	}
	game.map = (t_map *)malloc(sizeof(t_map));
	if (game.map == NULL)
		return (1);
	if (parse_map(game.map, argv[1]))
	{
		printf("map error\n");
		free(game.map);
		return (0);
	}
	// creating window
	game.mlx = (t_mlx *)malloc(sizeof(t_mlx));
	if (game.mlx == NULL)
		return (1);
	game.mlx->mlx = mlx_init();
	game.mlx->win = mlx_new_window(game.mlx->mlx, TYPE_HOR_PIX, TYPE_VER_PIX, "cub3d");

	//need to get image void* in game.mlx
	init_img(&game);

	game.keys = (t_keys *)malloc(sizeof(t_keys));
	// need to pass arg(struct pointer) in place of null
	mlx_hook(game.mlx->win, X_EVENT_KEY_PRESS, 0, key_press, &game);
	mlx_hook(game.mlx->win, X_EVENT_EXIT, 0, exit_hook, NULL);
	//mlx_loop_hook(game.mlx->mlx, function goes here, game);
	mlx_loop(game.mlx->mlx);

	return (0);
}
