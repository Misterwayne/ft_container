/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwane <mwane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 19:32:06 by mwane             #+#    #+#             */
/*   Updated: 2022/09/11 19:52:21 by mwane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "iterator_traits.hpp"

namespace ft
{
    template<class T>
    class random_access_iterator : public iterator<ft::random_access_iterator_tag, T>
    {
        public :
            typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type            value_type;
            typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type       difference_type;
            typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category     iterator_category;
            typedef T*                                                                              pointer;
            typedef T&                                                                              reference;
            
            random_access_iterator() : _ptr(){};
            
            random_access_iterator(pointer ptr) : _ptr(ptr){};
            
            virtual ~random_access_iterator(){};

            random_access_iterator& operator=(const random_access_iterator& other)
            {
                if (this == &other)
                    return (*this);
                _ptr  = other._ptr;
                return (*this);
            }

            pointer     base() const
            {
                return (_ptr);
            }
            
            random_access_iterator& operator++()
            { 
                ++_ptr;
                return *this;
            }

            random_access_iterator operator++(int)
            {
                random_access_iterator retval = *this;
                ++(*this);
                return retval;
            }

            random_access_iterator operator--(int)
            {
                random_access_iterator retval = *this;
                --(*this);
                return retval;
            }
            random_access_iterator& operator--()
            {
                --_ptr;
                return (*this);
            }
            
            reference operator[](difference_type index)
            {
                return (*operator+(index));
            }

            bool operator==(const random_access_iterator & other) const
            {
                return *_ptr == *other._ptr;
            }
            bool operator!=(const random_access_iterator & other) const
            {
                return !(_ptr == other._ptr);
            }

            random_access_iterator operator+(difference_type val)
            {
                return (_ptr + val);
            }

            random_access_iterator operator-(difference_type val)
            {
                return (_ptr - val);
            }
            
            pointer     operator->() const
            {
                return &(operator*());
            }

            reference operator*()
            {
                return *(_ptr);
            }

        private :
            pointer _ptr;
    };

    template <typename T>
    typename ft::random_access_iterator<T>::difference_type
    operator==(const ft::random_access_iterator<T> lhs, const ft::random_access_iterator<T> rhs)
    {
        return (lhs.base() == rhs.base());
    }

    template <typename T1, typename T2>
    typename ft::random_access_iterator<T1>::difference_type
    operator==(const ft::random_access_iterator<T1> lhs, const ft::random_access_iterator<T2> rhs)
    {
        return (lhs.base() == rhs.base());
    }

    template <typename T>
    typename ft::random_access_iterator<T>::difference_type
    operator!=(const ft::random_access_iterator<T> lhs, const ft::random_access_iterator<T> rhs)
    {
        return (lhs.base() != rhs.base());
    }

    template <typename T1, typename T2>
    typename ft::random_access_iterator<T1>::difference_type
    operator!=(const ft::random_access_iterator<T1> lhs, const ft::random_access_iterator<T2> rhs)
    {
        return (lhs.base() != rhs.base());
    }


    template <typename T>
    typename ft::random_access_iterator<T>::difference_type
    operator<(const ft::random_access_iterator<T> lhs, const ft::random_access_iterator<T> rhs)
    {
        return (lhs.base() < rhs.base());
    }

    template <typename T1, typename T2>
    typename ft::random_access_iterator<T1>::difference_type
    operator<(const ft::random_access_iterator<T1> lhs, const ft::random_access_iterator<T2> rhs)
    {
        return (lhs.base() < rhs.base());
    }

    template <typename T>
    typename ft::random_access_iterator<T>::difference_type
    operator>(const ft::random_access_iterator<T> lhs, const ft::random_access_iterator<T> rhs)
    {
        return (lhs.base() > rhs.base());
    }

    template <typename T1, typename T2>
    typename ft::random_access_iterator<T1>::difference_type
    operator>(const ft::random_access_iterator<T1> lhs, const ft::random_access_iterator<T2> rhs)
    {
        return (lhs.base() > rhs.base());
    }

    template <typename T>
    typename ft::random_access_iterator<T>::difference_type
    operator<=(const ft::random_access_iterator<T> lhs, const ft::random_access_iterator<T> rhs)
    {
        return (lhs.base() <= rhs.base());
    }

    template <typename T1, typename T2>
    typename ft::random_access_iterator<T1>::difference_type
    operator<=(const ft::random_access_iterator<T1> lhs, const ft::random_access_iterator<T2> rhs)
    {
        return (lhs.base() <= rhs.base());
    }

    template <typename T>
    typename ft::random_access_iterator<T>::difference_type
    operator>=(const ft::random_access_iterator<T> lhs, const ft::random_access_iterator<T> rhs)
    {
        return (lhs.base() >= rhs.base());
    }

    template <typename T1, typename T2>
    typename ft::random_access_iterator<T1>::difference_type
    operator>=(const ft::random_access_iterator<T1> lhs, const ft::random_access_iterator<T2> rhs)
    {
        return (lhs.base() >= rhs.base());
    }

    template <typename T>
    typename ft::random_access_iterator<T>
    operator+(const typename ft::random_access_iterator<T>::difference_type n, ft::random_access_iterator<T>& rhs)
    {
        return (&(*rhs) + n);
    }

    template <typename T>
    typename ft::random_access_iterator<T>::difference_type
    operator-(const ft::random_access_iterator<T> lhs, const ft::random_access_iterator<T> rhs)
    {
        return (lhs.base() - rhs.base());
    }

    template <typename T1, typename T2>
    typename ft::random_access_iterator<T1>::difference_type
    operator-(const ft::random_access_iterator<T1> lhs, const ft::random_access_iterator<T2> rhs)
    {
        return (lhs.base() - rhs.base());
    }

    template<class T>
    class reverse_iterator
    {
        public :
            typedef T                                                     iterator_type;
            typedef typename ft::iterator_traits<T>::iterator_category    iterator_category;
            typedef typename ft::iterator_traits<T>::pointer              pointer;
            typedef typename ft::iterator_traits<T>::value_type           value_type;
            typedef typename ft::iterator_traits<T>::reference            reference;
            typedef typename ft::iterator_traits<T>::difference_type      difference_type;
            
            reverse_iterator() : _ptr(){};
            
            reverse_iterator(iterator_type ptr) : _ptr(ptr){};

            template<class iterator>
            reverse_iterator(const reverse_iterator<iterator>& other) :_ptr(other.base())
            {};
            
            virtual  ~reverse_iterator(){};

            iterator_type base() const
            {
                return (_ptr);
            }
            
            reverse_iterator& operator++()
            { 
                --_ptr;
                return *this;
            }

            reverse_iterator operator++(int)
            {
                reverse_iterator retval = *this;
                ++(*this);
                return retval;
            }

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
            
            reference operator[](int n) const
            {
                return (this->base()[-n - 1]);
            }
            
            reverse_iterator& operator-=(difference_type val) const
            {
                _ptr += val;
                return (*this);
            }

            reverse_iterator& operator+=(difference_type val) const
            {
                _ptr -= val;
                return (*this);
            }

            pointer     operator->() const
            {
                return &(operator*());
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

            reverse_iterator& operator+(difference_type val)
            {
                return (reverse_iterator(_ptr - val));
            }

            reverse_iterator& operator-(int val)
            {
                return (reverse_iterator(_ptr + val));
            }
            
            reference operator*()
            {
                return *_ptr;
            }

        private :
            iterator_type _ptr;
    };

    template <typename T>
    typename ft::reverse_iterator<T>::difference_type
    operator==(const ft::reverse_iterator<T> lhs, const ft::reverse_iterator<T> rhs)
    {
        return (lhs.base() == rhs.base());
    }

    template <typename T1, typename T2>
    typename ft::reverse_iterator<T1>::difference_type
    operator==(const ft::reverse_iterator<T1> lhs, const ft::reverse_iterator<T2> rhs)
    {
        return (lhs.base() == rhs.base());
    }

    template <typename T>
    typename ft::reverse_iterator<T>::difference_type
    operator!=(const ft::reverse_iterator<T> lhs, const ft::reverse_iterator<T> rhs)
    {
        return (lhs.base() != rhs.base());
    }

    template <typename T1, typename T2>
    typename ft::reverse_iterator<T1>::difference_type
    operator!=(const ft::reverse_iterator<T1> lhs, const ft::reverse_iterator<T2> rhs)
    {
        return (lhs.base() != rhs.base());
    }


    template <typename T>
    typename ft::reverse_iterator<T>::difference_type
    operator<(const ft::reverse_iterator<T> lhs, const ft::reverse_iterator<T> rhs)
    {
        return (lhs.base() < rhs.base());
    }

    template <typename T1, typename T2>
    typename ft::reverse_iterator<T1>::difference_type
    operator<(const ft::reverse_iterator<T1> lhs, const ft::reverse_iterator<T2> rhs)
    {
        return (lhs.base() < rhs.base());
    }

    template <typename T>
    typename ft::reverse_iterator<T>::difference_type
    operator>(const ft::reverse_iterator<T> lhs, const ft::reverse_iterator<T> rhs)
    {
        return (lhs.base() > rhs.base());
    }

    template <typename T1, typename T2>
    typename ft::reverse_iterator<T1>::difference_type
    operator>(const ft::reverse_iterator<T1> lhs, const ft::reverse_iterator<T2> rhs)
    {
        return (lhs.base() > rhs.base());
    }

    template <typename T>
    typename ft::reverse_iterator<T>::difference_type
    operator<=(const ft::reverse_iterator<T> lhs, const ft::reverse_iterator<T> rhs)
    {
        return (lhs.base() <= rhs.base());
    }

    template <typename T1, typename T2>
    typename ft::reverse_iterator<T1>::difference_type
    operator<=(const ft::reverse_iterator<T1> lhs, const ft::reverse_iterator<T2> rhs)
    {
        return (lhs.base() <= rhs.base());
    }

    template <typename T>
    typename ft::reverse_iterator<T>::difference_type
    operator>=(const ft::reverse_iterator<T> lhs, const ft::reverse_iterator<T> rhs)
    {
        return (lhs.base() >= rhs.base());
    }

    template <typename T1, typename T2>
    typename ft::reverse_iterator<T1>::difference_type
    operator>=(const ft::reverse_iterator<T1> lhs, const ft::reverse_iterator<T2> rhs)
    {
        return (lhs.base() >= rhs.base());
    }

    template <typename T>
    typename ft::reverse_iterator<T>
    operator+(const typename ft::reverse_iterator<T>::difference_type n, ft::reverse_iterator<T>& rhs)
    {
        return (&(*rhs.base()) + n);
    }

    template <typename T>
    typename ft::reverse_iterator<T>::difference_type
    operator-(const ft::reverse_iterator<T> lhs, const ft::reverse_iterator<T> rhs)
    {
        return (lhs.base() - rhs.base());
    }

    template <typename T1, typename T2>
    typename ft::reverse_iterator<T1>::difference_type
    operator-(const ft::reverse_iterator<T1> lhs, const ft::reverse_iterator<T2> rhs)
    {
        return (lhs.base() - rhs.base());
    }
}
