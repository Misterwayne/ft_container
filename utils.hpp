/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwane <mwane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 13:14:42 by mwane             #+#    #+#             */
/*   Updated: 2022/10/15 16:31:41 by mwane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef UTILS_HPP
#define UTILS_HPP

namespace ft {

    template <class T1, class T2, class R>
    struct binary_function
    {
        typedef T1  first_type;

        typedef T2  second_type;

        typedef R   result;
    };


    template <class T>
    struct less : public ft::binary_function<T, T, bool>
    {
        bool operator()(const T &lhs, const T &rhs) const 
        {
            return lhs < rhs; 
        }
    };
}

#endif