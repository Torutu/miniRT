/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_ratio.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 10:47:43 by sataskin          #+#    #+#             */
/*   Updated: 2024/12/10 15:42:44 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* FORMAT 
		 ambient lighting ratio in range [0.0,1.0]: 0.2
*/

int	add_lighting_ratio(char *str, t_arg *new)
{
	if (ft_strlen(str) > 3)
		return (1);
	new->l_rat = ft_atof(str);
	if (new->l_rat > 1.0 || new->l_rat < 0)
		return (1);
	return (0);
}
