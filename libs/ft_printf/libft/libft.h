/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybouras <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 16:27:37 by aybouras          #+#    #+#             */
/*   Updated: 2019/12/15 21:51:07 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIBFT_H
# define FT_LIBFT_H

# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include "get_next_line.h"

typedef unsigned long long	t_ull;

/*
**	Conversions
*/

long long int		ft_atoll(const char *str);
char				*ft_ltoa(long long n);
char				*ft_utoa(unsigned long long n);
int					ft_atoi(const char *s);

/*
**	Memory
*/

void				*ft_memset(void *b, int c, size_t len);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);

/*
**	Strings
*/

int					ft_isdigit(int c);
size_t				ft_strlen(const char *s);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strdup(const char *s1);
int					ft_isspace(int c);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
int					ft_putchar(char c);
int					ft_putstr(char const *s);
int					ft_islower(int c);
int					ft_isupper(int c);
int					ft_tolower(int c);
int					ft_toupper(int c);
void				ft_putnchar(char c, long n);
int					ft_contains(const char *set, char c);
char				*ft_strndup(const char *s, size_t times);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(const char *s1, const char *s2);
int					ft_indexof(char *s, char c);
char				*ft_strjoin_free(char *s1, char *s2);
void				ft_strupper(char *str);
void				ft_strclr(char *s);
char				*ft_strchr(const char *s, int c);
char				*ft_strstr(const char *h, const char *n);
char				*ft_strrchr(const char *s, int c);
int					ft_putchar_fd(int fd, int c);
int					ft_putnchar_fd(int fd, int c, int n);
int					ft_putstr_fd(int fd, const char *s);

/*
**	Get_Next_Line Library
*/

int					get_next_line(int fd, char **line);

/*
**	Math functions
*/

long				ft_abs(long nb);
double				ft_sqrt(int n);
int					ft_pow(int x, unsigned int y);
int					ft_round(double n);

#endif
