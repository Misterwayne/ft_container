/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwane <mwane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 13:14:42 by mwane             #+#    #+#             */
/*   Updated: 2022/11/11 16:41:11 by mwane            ###   ########.fr       */
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

    template <class T>
    void    swap(T &lhs, T &rhs)
    {
        T tmp = lhs;

        lhs = rhs;
        rhs = tmp;
    }

    template<class InputIt1, class InputIt2>
    bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
    {
        for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2)
        {
            if (*first1 < *first2)
                return true;
            if (*first2 < *first1)
                return false;
        }
    
        return (first1 == last1) && (first2 != last2);
    }
}

#endif