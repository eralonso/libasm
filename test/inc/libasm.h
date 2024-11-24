#ifndef LIBASM_H
# define LIBASM_H

// MANDATORY

size_t	ft_strlen(const char *str);
char	*ft_strcpy(char *dst, const char *src);
int		ft_strcmp(const char *s1, const char *s2);
ssize_t	ft_write(int fd, const void *buf, size_t count);
ssize_t	ft_read(int fd, void *buf, size_t count);
char	*ft_strdup(const char *s);

//

// BONUS

typedef struct s_list t_list;

struct s_list
{
	void	*data;
	t_list	*next;
};

typedef int (*t_list_data_cmp)(const char *, const char *);


/// MANDATORY

int		ft_atoi_base(const char *str, const char *base);
void	ft_list_push_front(t_list **begin_list, void *data);
int		ft_list_size(t_list *begin_list);
void	ft_list_sort(t_list **begin_list, t_list_data_cmp cmp);
void	ft_list_remove_if(t_list **begin_list, void *data_ref, t_list_data_cmp cmp, void (*free_fct)(void *));

///


/// EXTRA
char	convert_sign_to_number(const char c);
ssize_t	ft_strnchri(const char *s, int c, size_t n);
ssize_t	ft_strchri(const char *s, int c);
int		is_sign_symbol(int c);
char	convert_sign_str_n_to_number(const char *str, const size_t n);
int		ft_isspace(int c);
ssize_t	str_n_find_first_not_of(const char *str, int (*cmp_function)(int), size_t n);
ssize_t	str_find_first_not_of(const char *str, int (*cmp_function)(int));
int		has_char_duplicated(const char *str);
int		str_has_min_size(const char *str, const size_t min_size);
int		is_valid_base(const char *str);

t_list	*ft_create_elem(void *data);
void	ft_list_swap_data(t_list *node1, t_list *node2);
void	ft_list_swap(t_list **begin_list, t_list *node1, t_list *node2);
t_list	*ft_list_at(t_list *begin_list, unsigned int nbr);
t_list	*ft_list_prev(t_list *begin_list, t_list *node);
int		ft_list_index(t_list *begin_list, t_list *node);

///

//

#endif
