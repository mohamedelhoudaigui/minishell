/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamkadm <mlamkadm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 02:57:13 by mel-houd          #+#    #+#             */
/*   Updated: 2024/02/09 23:29:17 by mlamkadm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

# define TRUE 1
# define FALSE 0
# define QUOTE_CHAR 39
# define DQUOTE_CHAR 34
# define PIPE_CHAR '|'
# define REDIR_OUT_CHAR '>'
# define REDIR_IN_CHAR '<'
# define NEW_LINE_CHAR "`newline'"

# define QUOTE 0
# define DQUOTE 1
# define NO_QUOTE -1

# define REDIR_IN 1
# define REDIR_OUT 2
# define HEREDOC 3
# define APPEND 4
# define PIPE 5
# define WORD 6

#endif
