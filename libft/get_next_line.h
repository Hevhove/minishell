/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvan-hov <hvan-hov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 11:33:27 by hvan-hov          #+#    #+#             */
/*   Updated: 2022/05/16 18:12:40 by hvan-hov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct s_i {
  long long i;
  long long j;
  long long k;
};

char *get_next_line(int fd);
void ft_putchar_fd(char c, int fd);
void ft_putendl_fd(char *s, int fd);
void ft_putstr_fd(char *s, int fd);
char *ft_strnjoin(const char *s1, char *s2, struct s_i i);
char *ft_strchr(const char *s, int c);

#endif
