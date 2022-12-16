/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelPrivilege.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 09:39:35 by bbrassar          #+#    #+#             */
/*   Updated: 2022/12/16 00:46:28 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNELPRIVILEGE_HPP
# define CHANNELPRIVILEGE_HPP

enum ChannelPrivilege
{
	PRIV_NONE = 0,
	PRIV_VOICE = 1,
	PRIV_CHANOP = 2,
	PRIV_UNIQOP = 3,
	PRIV_DISABLED = 4,
};

#endif
