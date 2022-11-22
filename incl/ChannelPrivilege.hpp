/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelPrivilege.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 09:39:35 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/21 09:53:01 by bbrassar         ###   ########.fr       */
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

#endif // CHANNELPRIVILEGE_HPP
