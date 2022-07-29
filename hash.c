/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 12:28:34 by bkandemi          #+#    #+#             */
/*   Updated: 2022/07/29 16:04:24 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

unsigned long hash(const char *s, unsigned long m)
{
	unsigned long	h;
	unsigned const char	*us;
	/* cast s to unsigned const char * */
	/* this ensures that elements of s will be treated as having values >= 0 */
	us = (unsigned const char *) s;
	h = 0;
	while(*us != '\0') {
		h = (h * 256 + *us) % m;
		us++;
	}
	return h;
}
