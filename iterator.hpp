/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwane <mwane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 19:32:06 by mwane             #+#    #+#             */
/*   Updated: 2022/09/04 21:55:56 by mwane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <iterator>

namespace ft
{
    template<class T>
    class iterator
    {
        public :
            typedef T                            value_type;
            typedef value_type*                  ptr;
            typedef value_type const *           const_ptr;
            typedef value_type&                  reference;
            typedef value_type const &           const_reference;
            typedef std::ptrdiff_t               diff;
            iterator() : _ptr(nullptr){};
            iterator(ptr ptr) : _ptr(ptr){};
            ~iterator(){};
            iterator<T>& operator++()
            { 
                ++_ptr;
                return *this;
            };
            iterator<T> operator++(int)
            {
                iterator retval = *this;
                ++(*this);
                return retval;
            };
            iterator<T> operator--(int)
            {
                iterator<T> retval = *this;
                --(*this);
                return retval;
            }
            iterator<T>& operator--()
            {
                --_ptr;
                return (*this);
            }
            reference operator[](int index)
            {
                return (_ptr + index);
            }
            
            const_reference operator[](int index) const
            {
                return (_ptr + index);
            }

            bool operator==(const iterator & other) const
            {
                return *_ptr == *other._ptr;
            }
            bool operator!=(const iterator & other) const
            {
                return !(*this == other);
            }

            iterator& operator=(iterator<T> const & 
            other)
            {
                _ptr = other._ptr;
                return (*this);
            }

            iterator<T> operator+(diff val)
            {
                return (_ptr + val);
            }

            iterator<T> operator-(diff val)
            {
                return (_ptr - val);
            }
            
            reference operator*()
            {
                return *(_ptr);
            }

            const_reference operator*() const
            {
                return (*_ptr);
            }
        private :
            ptr _ptr;
    };

    template<class T>
    class reverse_iterator
    {
        public :
            typedef T                            value_type;
            typedef value_type*                  ptr;
            typedef value_type const *           const_ptr;
            typedef value_type&                  reference;
            typedef value_type const &           const_reference;
            typedef std::ptrdiff_t               diff;
            reverse_iterator() : _ptr(nullptr){};
            reverse_iterator(ptr ptr) : _ptr(ptr){};
            ~reverse_iterator(){};
            reverse_iterator& operator++()
            { 
                --_ptr;
                return *this;
            };
            reverse_iterator operator++(int)
            {
                reverse_iterator retval = *this;
                --(*this);
                return retval;
            };
            reverse_iterator operator--(int)
            {
                reverse_iterator retval = *this;
                ++(*this);
                return retval;
            }
            reverse_iterator& operator--()
            {
                ++_ptr;
                return (*this);
            }
            reference operator[](int index)
            {
                return (_ptr + index);
            }
            
            const_reference operator[](int index) const
            {
                return (_ptr + index);
            }

            bool operator==(const reverse_iterator & other) const
            {
                return *_ptr == *other._ptr;
            }
            bool operator!=(const reverse_iterator & other) const
            {
                return !(*this == other);
            }
            reverse_iterator& operator=(reverse_iterator &other)
            {
                *(this) = other;
                return (*this);
            }

            reverse_iterator operator=(reverse_iterator other)
            {
                _ptr = other._ptr;
                return (*this);
            }

            reverse_iterator& operator+(int val)
            {
                _ptr -= val;
                return (*this);
            }

            reverse_iterator& operator-(int val)
            {
                _ptr += val;
                return (*this);
            }
            
            reference operator*()
            {
                return *_ptr;
            }

            const_reference operator*() const
            {
                return *_ptr;
            }
        private :
            ptr _ptr;
    };
}
