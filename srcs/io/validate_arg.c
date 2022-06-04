/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:57:11 by takkatao          #+#    #+#             */
/*   Updated: 2022/06/04 15:55:36 by takkatao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"

static char	*get_basename(char *path)
{
	char	*found;

	found = ft_strrchr(path, '/');
	if (found == NULL)
		return (ft_xstrdup(path));
	return (ft_xstrdup(found + 1));
}

static char	*get_extension(char *filename)
{
	char	*found;

	found = ft_strrchr(filename, '.');
	if (found == NULL || found == filename)
		return (ft_xstrdup(""));
	return (ft_xstrdup(found + 1));
}

/*
 * Check program arguments are valid and exit if not valid. A valid rt file is
 * ending with the .rt extension. If a file name is ".rt", it considered as
 * invalid because it is a hidden file and has no extension. "..rt" may be
 * controversial, but I think is a valid file. Don't check whether file existence
 * or permissions here.
 */
void	validate_arg(int argc, char **argv)
{
	char	*filename;
	char	*extension;

	if (argc != 2)
		puterr_exit("argument must be 1");
	filename = get_basename(argv[1]);
	extension = get_extension(filename);
	if (ft_strcmp("rt", extension) != 0)
		puterr_exit("Invalid file extension");
	free(filename);
	free(extension);
}
