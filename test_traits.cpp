/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_traits.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwane <mwane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 15:39:13 by mwane             #+#    #+#             */
/*   Updated: 2022/09/03 20:19:43 by mwane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pair.hpp"
#include <string>
#include <type_traits>
#include "traits.hpp"
#include <iostream> 

template <class T>
typename ft::enable_if<ft::is_integral<T>::value,bool>::type
  is_odd (T i) {return bool(i%2);}


int main()
{
    ft::pair <std::string,int> planet, homeplanet;

    planet = ft::make_pair("Earth",6371);
    homeplanet = ft::make_pair("Mars", 7854);

    std::cout << "Home planet: " << homeplanet.first << '\n';
    std::cout << "Planet size: " << planet.first << '\n';

    homeplanet.swap(planet);

    std::cout << "Home planet: " << homeplanet.first << '\n';
    std::cout << "Planet size: " << planet.first << '\n';

    std::cout << "is odd : " << is_odd(3) << "\n";

    return (0);
}