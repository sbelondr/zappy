/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 19:44:10 by jayache           #+#    #+#             */
/*   Updated: 2021/03/09 09:52:08 by selver           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef LIBFT_H
#	define LIBFT_H

#	include <string.h>
#	include <stdlib.h>
#	include <stdint.h>
#	include <unistd.h>
#	include <math.h>
#	include <errno.h>
#	include <sys/stat.h>
#	include <dirent.h>
#	include <pwd.h>
#	include <fcntl.h>

#	define ERROR_MALLOC "Malloc returned 0\n"

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_hashtable
{
	void			*def;
	size_t			size;
	t_list			**content;
}					t_hashtable;

typedef struct		s_hashnode
{
	char			*key;
	void			*content;
}					t_hashnode;

typedef struct		s_btree
{
	void			*item;
	struct s_btree	*right;
	struct s_btree	*left;
	struct s_btree	*parent;
}					t_btree;

typedef struct		s_vector2
{
	long			x;
	long			y;
}					t_vector2;

typedef struct		s_vector3
{
	float			x;
	float			y;
	float			z;
}					t_vector3;

typedef struct		s_vector4
{
	float			x;
	float			y;
	float			z;
	float			w;
}					t_vector4;

typedef struct		s_matrix
{
	float			**matrix;
	int				width;
	int				height;
}					t_matrix;

typedef struct		s_algo_input
{
	void			(*free)(void *data, size_t size);
	char			*(*serialize)(void *data);
	size_t			(*heuristic)(void *data);
	int				(*cmp)();
	void			**(*neighbors)(void *data);
	int				(*goal_f)(void *data);
	void			*goal_p;
}					t_algo_input;

typedef struct		s_algo_data
{
	t_hashtable		*gscore;
	t_hashtable		*fscore;
	t_hashtable		*camefrom;
	t_list			*openset;
}					t_algo_data;

typedef struct		s_algo_output
{
	size_t			otime;
	size_t			osize;
	void			**path;
}					t_algo_output;

int					ft_toupper(int c);
int					ft_tolower(int c);

void				*ft_memset(void *b, int c, size_t len);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_memalloc(size_t size);
void				ft_memdel(void	**ap);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				ft_bzero(void *s, size_t n);
void				ft_free_2d(void *array, int size);
int					ft_len_2d(char **array);
void				ft_error(const char *const str);

int					ft_atoi(const char *str);
size_t				ft_strlen(const char *s);
size_t				ft_strnlen(const char *s, size_t maxlen);
char				*ft_strdup(const char *s1);
char				*ft_strndup(const char *s1, int n);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strncat(char *s1, const char *s2, size_t len);
char				*ft_strcat(char *s1, const char *s2);
size_t				ft_strlcat(char *s1, const char *s2, size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char*));
char				*ft_strmap(const char *s, char (*f)(char));
char				*ft_strmapi(const char *s, char(*f)(unsigned int, char));
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strnstr(const char *haystack, const char *needle,
		size_t len);
char				*ft_strcut(char *cut, int begin, int end);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strins(char const *s, char const *ins, int pos);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_str3join(char const *a, char const *b, char const *c);
char				*ft_strfjoin(char *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				*ft_itoa(int nb);
void				ft_stradd(char **str, char c);
int					ft_min(int a, int b);
intmax_t			ft_pow(int n, int p);
char				*ft_itoa_base(long long nb, int base);
char				**ft_strsplit(char const *s, char c);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_strequ(const char *s1, const char *s2);
int					ft_strnequ(const char *s1, const char *s2, size_t n);
int					ft_strpbrk(const char *s, const char *charset);
int					ft_striswhitespace(const char *s);
int					ft_strisnumeric(const char *s);

size_t				ft_cntspback(char const *s, char const c);
size_t				ft_cntspfront(char const *s, char const c);
int					ft_sign(double n);
long				ft_max(long a, long b);
unsigned long		ft_abs(int nb);
int					ft_nblen(int nb);

int					ft_islower(int c);
int					ft_isupper(int c);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isprint(int c);
int					ft_isascii(int c);
int					ft_iswhitespace(int c);

int					ft_putchar(unsigned int c);
int					ft_putstr(const char *s);
int					ft_putendl(const char *s);
int					ft_putchar_fd(char c, int fd);
void				ft_putnbr_fd(int nb, int fd);
int					ft_putstr_fd(char const *s, int fd);
void				ft_putnbr(int nb);
int					ft_putendl_fd(const char *s, int fd);

int					get_next_line(int fd, char **line);
int					ft_printf(const char *str, ...);

/*
** LIST FUNCTION
*/

void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lst_append(t_list **root, t_list *append);
void				ft_lstdelbyval(t_list **root, void *val, int (*cmp)(),
		void (*del)());
void				ft_lst_sorted_insert(t_list **root, t_list *add,
		int (*cmp)());
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstnew(void const *content, size_t content_size);
t_list				*ft_lstnew_no_copy(void *content, size_t content_size);
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list				*ft_lstgetbypos(t_list *lst, int pos);
int					ft_lst_exist(t_list *root, void *data, int (cmp()));
size_t				ft_lst_size(t_list	*root);

/*
** MATRIX FUNCTION
*/

t_matrix			ft_matrix(int width, int height);
t_matrix			ft_matrix_identity(void);
t_matrix			ft_matrix_translation(t_vector3 translation);
t_matrix			ft_matrix_ry(float angle);
t_matrix			ft_matrix_projection(float ratio, int near, int far,
		int fov);
t_matrix			ft_matrix_product(t_matrix a, t_matrix b);
t_matrix			ft_vector4_to_matrix(t_vector4 vec);
t_matrix			ft_vector3_to_matrix(t_vector3 vec);
t_matrix			ft_matrix_diag_symetrie(t_matrix matrix);
void				ft_print_matrix(t_matrix matrix);
void				ft_matrix_free(t_matrix m);

/*
** VECTOR FUNCTION
*/

t_vector2			ft_vector2(float x, float y);
t_vector2			ft_vector2_normalize(t_vector2 vec);
t_vector2			ft_vector2_multiply(t_vector2 vec, float scalar);
t_vector2			ft_vector2_add(t_vector2 vec, t_vector2 vec2);
float				ft_vector2_magnitude(t_vector2 vec);
float				ft_vector2_angle(t_vector2 vec1, t_vector2 vec2);
float				ft_vector2_rangle(t_vector2 vec1, t_vector2 vec2);
float				ft_vector2_dot(t_vector2 vec1, t_vector2 vec2);

t_vector3			ft_vector3(float x, float y, float z);
t_vector3			ft_vector3_normalize(t_vector3 vec);
float				ft_vector3_magnitude(t_vector3 vec);
float				ft_vector3_dot(t_vector3 vec1, t_vector3 vec2);
t_vector3			ft_vector3_multiply(t_vector3 vec1, float scalar);
t_vector3			ft_vector3_cross(t_vector3 vec1, t_vector3 vec2);
float				ft_vector3_angle(t_vector3 vec1, t_vector3 vec2);
t_vector3			ft_vector3_axis(t_vector3 vec1, t_vector3 vec2);
t_vector3			ft_vector3_add(t_vector3 vec1, t_vector3 vec2);
t_vector3			ft_vector3_sub(t_vector3 vec1, t_vector3 vec2);
t_vector3			ft_vector3_opposite(t_vector3 vtc);

t_vector4			ft_vector4(float x, float y, float z, float w);
t_vector4			ft_vector4_from_3(t_vector3 vtc);
t_vector4			ft_vector4_p_matrix(t_vector4 vec, t_matrix m);
t_vector4			ft_matrix_to_vector4(t_matrix m);

/*
** DIRECTORY FUNCTION
*/

int					ft_is_dot(char *name);
int					ft_is_dir(char *name);
int					ft_exists(char *name);
int					ft_is_hidden(char *name);
int					ft_cnt_type(char **files, int size, int type);

/*
** BTREE FUNCTIONS
*/

void				ft_btree_apply_prefix(t_btree *root, void(*applyf)(void *));
void				ft_btree_apply_infix(t_btree *root, void(*applyf)(void *));
void				ft_btree_apply_defix(t_btree *root, void(*applyf)(void *));
void				ft_btree_apply_suffix(t_btree *root, void(*applyf)(void *));
void				ft_btree_free(t_btree *root);
t_btree				*ft_btree_create_node(void *item);
void				ft_btree_insert_data(t_btree **root, void *item,
		int (*cmpf)(void *, void *));

/*
** HASHTABLE
*/

t_hashtable			*ft_hashtable_new(size_t size, void *def);
size_t				ft_hashtable_hash(const char *key);
void				ft_hashtable_add(t_hashtable *table, const char *index,
		void *value);
void				ft_hashtable_sub(t_hashtable *table, const char *index);
t_hashnode			*ft_hashnode_new(char *index, void *value);
void				*ft_hashtable_search(t_hashtable *table, const char *index);
void				ft_hashtable_clean(t_hashtable *table);
void				ft_hashtable_free(t_hashtable *table);
size_t				ft_hashtable_size(t_hashtable *table);

/*
** ALGOS
*/

t_algo_output		ft_astar(void *start, t_algo_input *algo);
#	endif
