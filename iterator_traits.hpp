/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwane <mwane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 20:21:34 by mwane             #+#    #+#             */
/*   Updated: 2022/09/03 20:55:56 by mwane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

namespace ft
{
    struct input_iterator_tag { };

    struct output_iterator_tag { };

    struct forward_iterator_tag : public input_iterator_tag { };

    struct bidirectional_iterator_tag : public forward_iterator_tag { };

    struct random_access_iterator_tag : public bidirectional_iterator_tag { };

    struct contiguous_iterator_tag : public random_access_iterator_tag { };




    template< class Iter>
    struct iterator_traits
    {
        typedef typename Iter::difference_type      difference_type;
        typedef typename Iter::value_type           value_type;
        typedef typename Iter::pointer	            pointer;
        typedef typename Iter::reference            reference;
        typedef typename Iter::iterator_category    iterator_category;
    };
    
    template< class T >
    struct iterator_traits<T*>
    {
        typedef typename difference_type      std::ptrdiff_t;
        typedef typename value_type           T;
        typedef typename pointer	          T*;
        typedef typename reference            T&;
        typedef typename iterator_category    random_access_iterator_tag;
    };

    template< class T >
    struct iterator_traits<const T*>
    {
        typedef typename difference_type      std::ptrdiff_t;
        typedef typename value_type           T;
        typedef typename pointer	          T*;
        typedef typename reference            T&;
        typedef typename iterator_category    random_access_iterator_tag;
    };
}