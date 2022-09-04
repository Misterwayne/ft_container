/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwane <mwane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 14:44:25 by mwane             #+#    #+#             */
/*   Updated: 2022/09/04 13:15:12 by mwane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tuple>

namespace ft
{
    template <class T1, class T2>
    struct pair : public std::tuple<T1, T2>
    {
        typedef T1      first_type;
        typedef T2      second_type;
        public :
            pair() : first(first_type()), second(second_type()) {};
            template<class U, class V>
            pair (const ft::pair<U,V>& pr) : first(pr.first), second(pr.second) {};
            pair(const first_type& a, const second_type& b) : first(a), second(b) {};

            pair& operator= (const pair& pr)
            {
                this->first = pr.first;
                this->second = pr.second;
                return (*this);
            };

            void    swap(ft::pair<first_type, second_type>& pr)
            {
                first_type tmp1(pr.first);
                second_type tmp2(pr.second);

                pr.first = this->first;
                pr.second = this->second;
                this->first = tmp1;
                this->second = tmp2;
            }

            first_type first;
            second_type second;
    };

    template<class T1, class T2>
    pair<T1, T2> make_pair(T1 x, T2 y)
    {
        return (pair<T1,T2>(x, y));
    };
    
}
