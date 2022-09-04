/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwane <mwane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 16:14:08 by mwane             #+#    #+#             */
/*   Updated: 2022/09/04 19:12:29 by mwane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <iomanip>
#include "vector.hpp"

void print_vector(int id, const std::vector<int>& container)
{
    std::cout << std::setw(31) << id << ".(st) ";
    for (const int x: container) {
         std::cout << x << ' ';
    }
    std::cout << '\n';
}

void ft_print_vector(int id, ft::vector<int>& container)
{
    std::cout << std::setw(31) << id << ".(ft) ";
    ft::vector<int>::iterator it = container.begin();
    ft::vector<int>::iterator ite = container.end();
    for (; it != ite; it++)
    {
        std::cout << *it << ' ';
    }
    std::cout << '\n';
}

int main()
{
    std::vector<int> l(4, 8);
    std::vector<int> td(10, 4);
    ft::vector<int> dx(10, 4);
    ft::vector<int> x(4, 8);


    std::cout << std::setw(31) <<"std::vector at = " << l.at(1) << std::endl;
    std::cout << std::setw(31) <<"ft::vector at = " << x.at(1) << std::endl;
    ft_print_vector(0, x);
    print_vector(0, l);
    l.assign(10, 10);
    x.assign(10, 10);
    ft_print_vector(1, x);
    print_vector(1, l);
    // std::cout << std::setw(31) <<"std::vector [9] = "<< l[9] <<std::endl;
    // std::cout << std::setw(31) <<"ft::vector [9] = "<< x[9] << std::endl;
    // try{
    //     std::cout << std::setw(31) <<"std::vector [100] = "<< l[100] << std::endl;
    //     std::cout << std::setw(31) <<"ft::vector [100] = "<< x[100] << std::endl;
    // }
    // catch(std::exception &e)
    // {
    //     std::cout << std::setw(31) <<e.what() << std::endl;
    // }
    // std::cout << std::setw(31) <<"std::vector data = "<< l.data() << std::endl;
    // std::cout << std::setw(31) <<"ft::vector data = "<< x.data() << std::endl;
    // std::cout << std::setw(31) <<"std::vector size = "<< l.size() << std::endl;
    // std::cout << std::setw(31) <<"ft::vector size = "<< x.size() << std::endl;
    // std::cout << std::setw(31) <<"std::vector capacity = "<< l.capacity() << std::endl;
    // std::cout << std::setw(31) <<"ft::vector capacity = "<< x.capacity() << std::endl;
    // std::cout << std::setw(31) <<"std::vector size after clear = "<< l.size() << std::endl;
    // std::cout << std::setw(31) <<"ft::vector size after clear = "<< x.size() << std::endl;
    // std::cout << std::setw(31) <<"std::vector [1] = " << l[1] << std::endl;
    // std::cout << std::setw(31) <<"ft::vector [1] = "<< x[1] << std::endl;

    // ft::iterator<int> it = x.begin();
    std::vector<int>::iterator it2 = l.begin() + 5;
    // l.erase(it2, it2 + 2);
    // x.erase(it, it + 2);
    x.erase(x.begin());
    l.erase(l.begin());
    std::cout << std::setw(31) <<"std::vector size = "<< l.capacity() << std::endl;
    std::cout << std::setw(31) <<"ft::vector size = "<< x.size() << std::endl;
    ft_print_vector(2, x);
    print_vector(2, l);
    ft::iterator<int> it = (x.begin() + 5);
    x.erase(x.end() - 1);
    l.erase(l.end() - 1);
    l.insert(it2, 200);
    x.insert(it, 200);
    ft_print_vector(3, x);
    print_vector(3, l);
    l.resize(5);
    x.resize(5);
    ft_print_vector(4, x);
    print_vector(4, l);
    x.push_back(6);
    l.push_back(6);
    ft_print_vector(5, x);
    print_vector(5, l);
    return (0);
}