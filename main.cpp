/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwane <mwane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 16:14:08 by mwane             #+#    #+#             */
/*   Updated: 2022/09/11 17:17:20 by mwane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <iomanip>
#include <iterator>
#include "vector.hpp"

int print_count = 0;

void print_vector(std::vector<int>& container)
{
    std::cout << std::setw(31) << print_count << ".(st) ";
    std::vector<int>::reverse_iterator it = container.rbegin();
    std::vector<int>::reverse_iterator ite = container.rend();
    for (; it != ite; it++) {
         std::cout << *it << ' ';
    }
    std::cout << '\n';
    print_count++;
}

void ft_print_vector(ft::vector<int>& container)
{
    std::cout << "\n" <<std::setw(31) << print_count << ".(ft) ";
    ft::vector<int>::reverse_iterator it = container.rbegin();
    ft::vector<int>::reverse_iterator ite = container.rend();
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
    std::vector<int> dx(10, 2);
    ft::vector<int> x(4, 8);


    std::cout << std::setw(31) <<"std::vector at = " << l.at(1) << std::endl;
    std::cout << std::setw(31) <<"ft::vector at = " << x.at(1) << std::endl;
    ft_print_vector(x);
    print_vector(l);
    l.resize(10, 10);
    x.resize(10, 10);
    ft_print_vector(x);
    print_vector(l);
    std::cout << std::setw(31) <<"std::vector [9] = "<< l[9] <<std::endl;
    std::cout << std::setw(31) <<"ft::vector [9] = "<< x[9] << std::endl;
    try{
        std::cout << std::setw(31) <<"std::vector [100] = "<< l[100] << std::endl;
        std::cout << std::setw(31) <<"ft::vector [100] = "<< x[100] << std::endl;
    }
    catch(std::exception &e)
    {
        std::cout << std::setw(31) <<e.what() << std::endl;
    }
    std::cout << std::setw(31) <<"std::vector data = "<< l.data() << std::endl;
    std::cout << std::setw(31) <<"ft::vector data = "<< x.data() << std::endl;
    std::cout << std::setw(31) <<"std::vector size = "<< l.size() << std::endl;
    std::cout << std::setw(31) <<"ft::vector size = "<< x.size() << std::endl;
    x.push_back(6);
    l.push_back(6);
    ft_print_vector(x);
    print_vector(l);
    x.assign(td.begin(), td.end());
    l.assign(td.begin(), td.end());
    std::cout << std::setw(31) <<"std::vector capacity = "<< l.capacity() << std::endl;
    std::cout << std::setw(31) <<"ft::vector capacity = "<< x.capacity() << std::endl;
    ft_print_vector(x);
    print_vector(l);
    l.clear();
    x.clear();
    std::cout << std::setw(31) <<"std::vector size after clear = "<< l.size() << " capacity = " << l.capacity() <<std::endl;
    std::cout << std::setw(31) <<"ft::vector size after clear = "<< x.size() << " capacity = " << x.capacity() <<std::endl;
    std::cout << std::setw(31) <<"std::vector [1] = " << l[1] << std::endl;
    std::cout << std::setw(31) <<"ft::vector [1] = "<< x[1] << std::endl;
    l.resize(10, 10);
    x.resize(10, 10);
    ft_print_vector(x);
    print_vector(l);
    x.erase(x.begin(), x.begin() + 2);
    l.erase(l.begin(), l.begin() + 2);
    ft_print_vector(x);
    print_vector(l);
    std::cout << std::setw(31) <<"std::vector size = "<< l.size() << std::endl;
    std::cout << std::setw(31) <<"ft::vector size = "<< x.size() << std::endl;
    ft_print_vector(x);
    print_vector(l);
    ft::vector<int>::iterator it = (x.begin() + 5);
    std::vector<int>::iterator it2 = l.begin() + 5;
    
    x.erase(x.end() - 1);
    l.erase(l.end() - 1);
    ft_print_vector(x);
    print_vector(l);
    
    l.insert(it2, 200);
    x.insert(it, 200);
    ft_print_vector(x);
    print_vector(l);

    l.insert(it2, dx.begin(), dx.begin() + 3);
    x.insert(it, dx.begin(), dx.begin() + 3);
    ft_print_vector(x);
    print_vector(l);

    l.resize(5);
    x.resize(5);
    ft_print_vector(x);
    print_vector(l);
    x.push_back(6);
    l.push_back(6);
    ft_print_vector(x);
    print_vector(l);

    ft::vector<int> alice(2, 3);
    ft::vector<int> bob(7, 8);
    ft::vector<int> eve(2, 3);
 
    std::cout << std::boolalpha;
 
    // Compare non equal containers
    std::cout << "alice == bob returns " << (alice == bob) << '\n';
    std::cout << "alice != bob returns " << (alice != bob) << '\n';
    std::cout << "alice <  bob returns " << (alice < bob) << '\n';
    std::cout << "alice <= bob returns " << (alice <= bob) << '\n';
    std::cout << "alice >  bob returns " << (alice > bob) << '\n';
    std::cout << "alice >= bob returns " << (alice >= bob) << '\n';
 
    std::cout << '\n';
 
    // Compare equal containers
    std::cout << "alice == eve returns " << (alice == eve) << '\n';
    std::cout << "alice != eve returns " << (alice != eve) << '\n';
    std::cout << "alice <  eve returns " << (alice < eve) << '\n';
    std::cout << "alice <= eve returns " << (alice <= eve) << '\n';
    std::cout << "alice >  eve returns " << (alice > eve) << '\n';
    std::cout << "alice >= eve returns " << (alice >= eve) << '\n';
    return (0);
}