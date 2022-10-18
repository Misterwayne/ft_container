/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traits.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwane <mwane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 16:19:11 by mwane             #+#    #+#             */
/*   Updated: 2022/10/15 16:37:12 by mwane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRAIT_HPP
#define TRAIT_HPP

namespace ft
{

    template< bool B, class T = void >
    struct enable_if
    {};

    template <typename T>
    struct enable_if<true, T>
    {
        typedef T type;
    };

    template <bool is_integral, typename T>
    struct check_type
    {
        typedef T type;
        static const bool value = is_integral;
    };


    template <typename>
    struct is_integral_type : public check_type<false, bool> {};
    
    template <>
    struct is_integral_type<bool> : public check_type<true, bool> {};
    
    template <>
    struct is_integral_type<char> : public check_type<true, char> {};
    
    template <>
    struct is_integral_type<wchar_t> : public check_type<true, wchar_t> {};
    
    template <>
    struct is_integral_type<signed char> : public check_type<true, signed> {};
    
    template <>
    struct is_integral_type<short int> : public check_type<true, short int> {};
    
    template <>
    struct is_integral_type<int> : public check_type<true, int> {};
    
    template <>
    struct is_integral_type<long int> : public check_type<true, long int> {};
    
    template <>
    struct is_integral_type<long long int> : public check_type<true, long long int> {};
    
    template <>
    struct is_integral_type<unsigned char> : public check_type<true, unsigned char> {};
    
    template <>
    struct is_integral_type<unsigned short int> : public check_type<true, unsigned short int> {};
    
    template <>
    struct is_integral_type<unsigned int> : public check_type<true, unsigned int> {};

    template <>
    struct is_integral_type<unsigned long int> : public check_type<true, unsigned long int> {};
    
    template <>
    struct is_integral_type<unsigned long long int> : public check_type<true, unsigned long long int> {};


    template <typename T>
    struct is_integral : is_integral_type<T>{};
}

#endif