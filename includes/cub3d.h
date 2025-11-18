/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-bail <sle-bail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 17:42:10 by sle-bail          #+#    #+#             */
/*   Updated: 2025/11/18 17:42:13 by sle-bail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../libft/libft.h"

# ifdef __linux__
#  include "../minilibx-linux/mlx.h"
#  include <X11/keysym.h>
# else
#  include "../minilibx_opengl_20191021/mlx.h"
# endif

# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIDTH 1280
# define HEIGHT 720

# define MAX_STACK_SIZE 131072

# define MOVESPEED 0.027
# define ROTATIONSPEED 0.05
# define MOB_SPEED 1.7

# define MOUSE_SPEED 0.005
# define ANGLE_SPEED 0.5

# define TICK_SPEED 0.1
# define TARGET_FPS 60

// Keycodes - macOS only (Linux uses X11 keysyms from keysym.h)
# ifndef __linux__
#  define XK_Escape 53
#  define XK_w 13
#  define XK_s 1
#  define XK_a 0
#  define XK_d 2
#  define XK_space 49
#  define XK_m 46
#  define XK_Left 123
#  define XK_Right 124
# endif

# define GAME_MENU 0
# define GAME_PLAYING 1
# define GAME_WON 2
# define GAME_LOST 3

# define MONSTER_FOV_DEGREES 60.0
# define MONSTER_SIGHT_DISTANCE 15.0
# define MONSTER_MIN_DISTANCE 0.5
# define TELEPORT_MAX_ATTEMPTS 48
# define EVENT_COOLDOWN_MS 10000
# define FLICKER_BLACKOUT_MS 100
# define FLICKER_SHORT_MS 300
# define FLICKER_LONG_MS 900
# define FLICKER_VERYLONG_MS 1600
# define PAUSE_BEFORE_SCREAMER_MS 4000
# define SCREAMER_DURATION_MS 2000

# define KEY_MOUSE_LEFT 1
# define KEY_MOUSE_RIGHT 2

# define GRID_CENTER_OFFSET 0.5
# define CAMERA_PLANE_MAGNITUDE 0.888
# define MOB_ANIMATION_DURATION 0.3
# define MOB_COLLISION_RADIUS 0.20
# define MOB_SPAWN_ATTEMPTS 100
# define FLOAT_EPSILON 1e-9
# define FAR_PLANE_DISTANCE 1e30
# define DOOR_DISTANCE_MIN 0.2

# define MMAP_VIEW_DIST 6
# define MMAP_PIXEL_SIZE 200
# define MMAP_COLOR_WALL 0x6B1B12
# define MMAP_COLOR_FLOOR 0x3D230C
# define MMAP_COLOR_PLAYER 0x6B1B12
# define MMAP_COLOR_SPACE 0x000000
# define MMAP_DEBUG_MSG 0

typedef struct s_direction
{
	double	dirx;
	double	diry;
	double	planex;
	double	yaw;
}			t_direction;

typedef struct s_player
{
	double			dirx;
	double			diry;
	double			planey;
	double			planex;
	double			pos_x;
	double			pos_y;
	double			yaw;
	char			player_dir;
	int				moving_x;
	int				moving_y;
	int				rotate;
	int				capture_mouse;
}					t_player;

typedef struct s_ray
{
	double			dirx;
	double			diry;
	double			camerax;
	double			planex;
	double			planey;
	int				mapx;
	int				mapy;
	double			deltadistx;
	double			deltadisty;
	double			sidedistx;
	double			sidedisty;
	int				stepx;
	int				stepy;
	int				side;
	double			wall_distance;
	double			wall_x;
	int				draw_start;
	int				draw_end;
	int				line_height;
}					t_ray;

typedef struct s_img
{
	void			*data;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_img;

typedef struct s_map
{
	char			*map;
	char			**map_tab;
	char			**infos;
	int				height;
	int				width;
}					t_map;

typedef struct s_rgb
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
}					t_rgb;

typedef struct s_texture
{
	void			*img;
	char			*addr;
	int				line_length;
	int				bits_per_pixel;
	int				endian;
	int				width;
	int				height;
}					t_texture;

typedef struct s_minimap
{
	char			**map;
	t_img			*img;
	int				view_dist;
	int				size;
	int				tile_size;
	int				offset_x;
	int				offset_y;
	double			rotation;
}					t_minimap;

typedef enum e_door_orient
{
	DOOR_X,
	DOOR_Y
}	t_door_orient;

typedef struct s_door
{
	int				i;
	int				j;
	t_door_orient	orient;
	int				is_closed;
}					t_door;

typedef struct s_ray_result
{
	double			t;
	double			u;
	int				hit;
}					t_ray_result;

typedef struct s_ray_calc
{
	double			rx;
	double			ry;
	double			t;
	double			u;
}					t_ray_calc;

typedef struct s_sprite
{
	double			x;
	double			y;
	t_texture		*texture;
}					t_sprite;

typedef struct s_mob
{
	double			x;
	double			y;
	t_texture		*img[2];
	int				frame;
	double			t_anim;
}					t_mob;

typedef struct s_button
{
	int				x;
	int				y;
	int				width;
	int				height;
}					t_button;

typedef struct s_cub
{
	void			*mlx;
	void			*win;
	t_img			img;
	t_map			*map;
	char			*no_texture;
	char			*so_texture;
	char			*ea_texture;
	char			*we_texture;
	t_rgb			*floor_rgb;
	t_rgb			*ceiling_rgb;
	t_player		*player;
	t_ray			*ray;
	int				w_height;
	int				w_width;
	t_texture		*no_texture_img;
	t_texture		*so_texture_img;
	t_texture		*ea_texture_img;
	t_texture		*we_texture_img;
	char			*floor_texture;
	t_texture		*floor_texture_img;
	char			*ceiling_texture;
	t_texture		*ceiling_texture_img;
	double			movespeed;
	double			rotationspeed;
	double			*camera_x_cache;
	t_sprite		*sprite;
	t_texture		*sprite_texture;
	t_texture		*screamer_texture;
	t_mob			*mob;
	double			mob_spawn_x;
	double			mob_spawn_y;
	double			mob_speed;
	t_img			minimap;
	double			*z_buffer;
	int				event_state;
	long			event_next_ms;
	long			blackout_until_ms;
	int				monster_prev_visible;
	long			event_cooldown_until_ms;
	char			**door_state;
	t_texture		*door_texture;
	t_door			*doors;
	int				door_count;
	int				game_state;
	long			game_end_time;
	t_texture		*menu_texture;
	t_button		*start_button;
	t_texture		*win_texture;
	long			win_display_until_ms;
	t_texture		*gameover_texture;
	long			gameover_display_until_ms;
}					t_cub;

void				my_mlx_pixel_put(t_img *data, int x, int y, int color);
bool				is_correct_extension(char *filename, char *ext);
bool				is_line_empty(char *line);
bool				is_valid_identifier(char *line);
bool				is_first_or_last_line_valid(char *line);
bool				pos_nb_checker(char *map, t_cub *data);
int					end_of_spaces_index(char *line);
char				*skip_to_next_line(char *str);
char				**split_on_space_tab(char const *s);
void				ft_free(char **ptr);
bool				check_walls(t_cub *cub, char **map, int i, int j);
bool				map_checker(t_cub *data, char **map);
void				set_player_pos(t_cub *data);
int					raycasting(t_cub *data);
int					data_init(t_cub *data);
void				player_init(t_cub *data);
void				arg_check(t_cub *data, int argc, char **argv);
int					ft_close_window(t_cub *cub);

t_texture			*select_texture(t_cub *data, t_ray *ray);
void				calculate_texture_coordinates(t_ray *ray,
						t_texture *texture, int *tex_x);
int					get_texture_color(t_texture *texture, int tex_x, int tex_y);
void				draw_column(t_cub *data, int x, t_texture *texture,
						int tex_x);
void				cast_single_ray(t_cub *data, int x);
void				render_floor_textured(t_cub *game, int x, int start_y);
void				render_ceiling_textured(t_cub *game, int x, int end_y);

int					optimized_pixel_put(t_img *img, int x, int y, int color);

int					parse_texture_path(t_cub *game, char *id, char **dest,
						char *err);
int					north_texture(t_cub *data);
int					south_texture(t_cub *data);
int					west_texture(t_cub *data);
int					east_texture(t_cub *data);
int					floor_texture(t_cub *data);
int					ceiling_texture(t_cub *data);
t_texture			*load_texture_from_xpm(t_cub *data, const char *path);

void				ceiling_color(t_cub *data);
void				floor_color(t_cub *data);
void				textures_and_colors_init(t_cub *data);

void				initialize_mlx(t_cub *cub);
void				malloc_error(void);
void				window_error(t_cub *cub);
void				image_error(t_cub *cub);
void				initialize_game(t_cub *data);
void				run_game(t_cub *data);
void				precalculate_camera_x(t_cub *data);
void				events_handling(t_cub *cub);
int					key_hook(int keysym, t_cub *cub);
int					key_release_handler(int keysym, t_cub *cub);
void				cub_free(t_cub *data);
void				free_data(t_cub *data);

void				move_player(t_cub *cub);
void				move_in_direction(t_cub *cub, double dx, double dy);
void				rotate_player(t_cub *data);

int					render_frame(t_cub *game);

void				init_sprite(t_cub *data);
void				render_sprite(t_cub *data);
void				init_sprite_params(int *params, int start, int height,
						int left);
void				draw_sprite_loop(t_cub *data, int params[5], double tr_y);
void				draw_sprite_column(t_cub *d, int x, int prm[5], double tr_y);
void				render_doors(t_cub *data);
void				render_one_door(t_cub *g, t_door *door);
void				render_closed_doors(t_cub *g);
t_ray_result		compute_ray_intersection(t_cub *g, t_door *door,
						double camera_x);
int					clamp_texture_x(double u, t_texture *tex);
int					compute_texture_y(t_cub *g, t_texture *tex, int y_pos,
						int line_h);

void				init_mob(t_cub *data);
void				mob_update(t_cub *data, double dt);
void				mob_render(t_cub *data);
int					check_collision(t_cub *data, double len);
void				find_spawn(t_cub *data, double *x, double *y);

void				update_monster_event(t_cub *data);
int					get_event_state(t_cub *data);
int					should_show_blackout(t_cub *data);
long				now_ms(void);

bool				is_position_within_map_bounds(double x, double y, t_map *map);
bool				is_tile_walkable(char tile_char);
bool				can_move_to_coordinates(t_cub *game, double target_x,
						double target_y);
void				attempt_position_update(t_cub *game, double new_x,
						double new_y);
void				apply_movement_vector(t_cub *game, double dx, double dy);

double				compute_rotated_x(double x, double y, double angle);
double				compute_rotated_y(double x, double y, double angle);
void				apply_rotation_to_direction(t_player *plr,
						double rotation_angle);
void				apply_rotation_to_camera_plane(t_player *plr,
						double rotation_angle);
void				execute_rotation(t_cub *game, double angle);


void				free_map_data(t_map *map);
void				free_texture_strings(t_cub *data);
void				free_texture_image(void *mlx, t_texture *texture_img);
void				free_texture_images(t_cub *data);
void				free_mlx_resources(t_cub *data);

int					read_file_infos(t_cub *data, int fd);
int					read_map_content(t_cub *data, int fd);
int					cleanup_remaining_lines(int fd);
void				copy_strings(char *result, char *s1, char const *s2);
char				*ft_strjoin_free(char *s1, char const *s2, int free_s1);

void				raycast_init(int x, t_player *player, t_ray *ray,
						double camera_x);
void				dda_init(t_ray *ray, t_player *player);
void				exec_dda(t_cub *data, t_ray *ray, int hit);
void				line_height(t_ray *ray, t_player *player, t_cub *data);

void				init_texture_pointers(t_cub *data);
void				init_window_dimensions(t_cub *data);
int					init_map_structure(t_cub *data);
int					init_game_objects(t_cub *data);
void				init_mlx_pointers(t_cub *data);

bool				is_first_or_last_line_valid(char *line);
bool				is_player_character(char c);
bool				pos_nb_checker(char *map, t_cub *data);
bool				is_valid_position(int x, int y, char **map, int map_height);
bool				is_empty_space_at(int x, int y, char **map, int map_height);
bool				is_walkable(char c);
void				flood_fill(char **map_copy, int x, int y, int map_height);
char				**copy_map(char **original_map, int map_height);
void				free_map_copy(char **map_copy, int map_height);
bool				check_map_borders_after_flood(char **map_copy,
						int map_height);
bool				flood_fill_test(t_cub *data, char **map);
bool				perform_flood_fill_validation(t_cub *data, char **map);

bool				infos_checker(t_cub *data);

int					data_init(t_cub *data);
void				set_player_direction(t_player *player, t_direction dir);
void				set_player_direction_north(t_player *player);
void				set_player_direction_south(t_player *player);
void				set_player_direction_east(t_player *player);
void				set_player_direction_west(t_player *player);

bool				check_adjacent_horizontal(int x, int y, char **map,
						int map_height);
bool				check_adjacent_vertical(int x, int y, char **map,
						int map_height);
bool				check_diagonal_neighbors(int x, int y, char **map,
						int map_height);
bool				check_walls(t_cub *cub, char **map, int x, int y);
void				set_player_pos(t_cub *data);

bool				is_door_character(char c);
bool				validate_door_placement(t_cub *data, char **map);
int					init_door_state(t_cub *data);
void				free_door_state(char **door_state, int height);
int					door_texture_loader(t_cub *data);
void				toggle_door_state(t_cub *data);
bool				is_door_closed(t_cub *data, int mapx, int mapy);
int					init_doors(t_cub *data);

bool				check_all_doors_open(t_cub *data);
void				trigger_victory(t_cub *data);
void				reset_game(t_cub *data);
void				find_spawn(t_cub *data, double *x, double *y);

int					load_menu_texture(t_cub *data);
int					is_button_clicked(t_button *button, int mouse_x, int mouse_y);
int					load_win_texture(t_cub *data);
int					load_gameover_texture(t_cub *data);

int					read_map_content2(t_cub *data, int fd, char *line,
						size_t *j);
bool				check_duplicate_identifiers(t_cub *data);

void				render_minimap(t_cub *data);
void				render_minimap_image(t_cub *data, t_minimap *minimap);
double				get_minimap_rotation_from_spawn(char dir);
void				init_img(t_cub *data, t_img *img, int width, int height);
void				set_image_pixel(t_img *img, int x, int y, int color);
void				free_tab(void **tab);
void				err_msg(char *detail, char *str, int code);
void				debug_display_minimap(t_minimap *minimap);

#endif
