/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwane <mwane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 20:21:34 by mwane             #+#    #+#             */
/*   Updated: 2022/11/06 19:35:41 by mwane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP
#include <iostream>

namespace ft
{

	struct input_iterator_tag { };

	struct output_iterator_tag { };

	struct forward_iterator_tag : public input_iterator_tag { };

	struct bidirectional_iterator_tag : public forward_iterator_tag { };

	struct random_access_iterator_tag : public bidirectional_iterator_tag { };

	struct contiguous_iterator_tag : public random_access_iterator_tag { };


	template <bool is_iterator, typename T>
	struct check_iterator
	{
		typedef T type;
		static const bool value = is_iterator;
	};

	template <typename T>
	struct is_iterator_type : public check_iterator<false, T> {};
	
	template <>
	struct is_iterator_type<ft::bidirectional_iterator_tag> : public check_iterator<true, ft::bidirectional_iterator_tag> {};
	
	template <>
	struct is_iterator_type<ft::contiguous_iterator_tag> : public check_iterator<true, ft::contiguous_iterator_tag> {};
	
	template <>
	struct is_iterator_type<ft::forward_iterator_tag> : public check_iterator<true, ft::forward_iterator_tag> {};
	
	template <>
	struct is_iterator_type<ft::input_iterator_tag> : public check_iterator<true, ft::input_iterator_tag> {};
	
	template <>
	struct is_iterator_type<ft::random_access_iterator_tag> : public check_iterator<true, ft::random_access_iterator_tag> {};
	
	template <>
	struct is_iterator_type<ft::output_iterator_tag> : public check_iterator<true, ft::output_iterator_tag> {};
	

	template <typename T>
	struct is_iterator : is_iterator_type<T>{};



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
		typedef  std::ptrdiff_t                 difference_type;
		typedef  T                              value_type;
		typedef  T*                             pointer;
		typedef  T&                             reference;
		typedef  ft::random_access_iterator_tag iterator_category;
	};

	template< class T >
	class iterator_traits<const T*>
	{
		typedef  std::ptrdiff_t                 difference_type;
		typedef  T                              value_type;
		typedef  T*                             pointer;
		typedef  T&                             reference;
		typedef  ft::random_access_iterator_tag iterator_category;
	};

	template <class Iterator>
	typename ft::iterator_traits<Iterator>::difference_type
	distance (Iterator first, Iterator last)
	{
		typename ft::iterator_traits<Iterator>::difference_type res = 0;
		for(; first != last; first++)
			res++;
		return (res);
	};

	template<class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
	class iterator
	{
		public :
			typedef T           value_type;
			typedef Distance    difference_type;
			typedef Pointer     pointer;
			typedef Reference   reference;
			typedef Category    iterator_category;
	};

	template <class T>
	class bidirectional_iterator : ft::iterator<ft::bidirectional_iterator_tag, T>
	{
		public :
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::value_type        value_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type   difference_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::pointer           pointer;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::reference         reference;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::iterator_category iterator_category;
		
			bidirectional_iterator(pointer min, pointer max)
			{
				_ptr = min;
				first = min;
				last = max;
			}

			virtual  ~bidirectional_iterator()
			{
			};

			bidirectional_iterator		operator++(int)
			{
				bidirectional_iterator tmp = *this;
				++(*this);
				return tmp;
			}

			bidirectional_iterator&		operator++()
			{
				pointer parent;
				
				// std::cout << _ptr->data->first << " : gate 1\n";
				if (_ptr == last)
				{
					_ptr = _ptr->right;
					// std::cout << "lol\n";
					return (*this);
				}
				// std::cout << "gate 2\n";
				parent = _ptr->parent;
				if(_ptr->right->is_leaf())
				{
					if (parent->right == _ptr)
					{
						// std::cout << "gate 3\n";
						while (_ptr->parent->right == _ptr)
							_ptr = _ptr->parent;
					}
					_ptr = _ptr->parent;
					return *this;
				}
				else if (!_ptr->right->is_leaf())
				{
					// std::cout << "gate 4\n";
					_ptr = _ptr->right;
					while (!_ptr->left->is_leaf())
						_ptr = _ptr->left;
					return *this;
				}
				// std::cout << "gate 5\n";
				return *this;
			}

			bidirectional_iterator&		operator--()
			{
				pointer parent;
				
				std::cout << _ptr->data->first << " : gate 1\n";
				if (_ptr == first->parent)
				{
					_ptr = first;
					std::cout << "lol\n";
					return (*this);
				}
				else if (_ptr == last->right)
				{
					// std::cout << "lol\n";
					_ptr = last;
					return (*this);
				}
				// std::cout << "gate 2\n";
				parent = _ptr->parent;
				if(_ptr->left->is_leaf())
				{
					if (parent->left == _ptr)
					{
						// std::cout << "gate 3\n";
						while (_ptr->parent->left == _ptr)
							_ptr = _ptr->parent;
					}
					_ptr = _ptr->parent;
					return *this;
				}
				else if (!_ptr->left->is_leaf())
				{
					// std::cout << "gate 4\n";
					_ptr = _ptr->left;
					while (!_ptr->right->is_leaf())
						_ptr = _ptr->right;
					return *this;
				}
				// std::cout << "gate 5\n";
				return *this;
			}

			bidirectional_iterator		operator--(int)
			{
				bidirectional_iterator tmp = *this;
				--(*this);
				return (tmp);
			}

			typename T::data_type		&operator*() const
			{
				typename T::data_type		*data;

				data = _ptr->data;
				return *(data);
			}
			
			typename T::data_type*		operator->() const
            {
                return &(operator*());
            }

			bool operator==(const bidirectional_iterator & other) const
            {
                return *_ptr == *other._ptr;
            }
            bool operator!=(const bidirectional_iterator & other) const
            {
                return !(_ptr == other._ptr);
            }

			bidirectional_iterator& operator=(const bidirectional_iterator & other)
			{
                if (this == &other)
                    return (*this);
                _ptr  = other._ptr;
                return (*this);
            }

		private :
			pointer _ptr;
			pointer first;
			pointer last;
	};

	template <typename T>
    typename ft::bidirectional_iterator<T>::difference_type
    operator==(const ft::bidirectional_iterator<T> lhs, const ft::bidirectional_iterator<T> rhs)
    {
        return (lhs._ptr == rhs._ptr);
    }

    template <typename T1, typename T2>
    typename ft::bidirectional_iterator<T1>::difference_type
    operator==(const ft::bidirectional_iterator<T1> lhs, const ft::bidirectional_iterator<T2> rhs)
    {
        return (lhs._ptr == rhs._ptr);
    }

    template <typename T>
    typename ft::bidirectional_iterator<T>::difference_type
    operator!=(const ft::bidirectional_iterator<T> lhs, const ft::bidirectional_iterator<T> rhs)
    {
        return (lhs._ptr != rhs._ptr);
    }

    template <typename T1, typename T2>
    typename ft::bidirectional_iterator<T1>::difference_type
    operator!=(const ft::bidirectional_iterator<T1> lhs, const ft::bidirectional_iterator<T2> rhs)
    {
        return (lhs._ptr != rhs._ptr);
    }


    template <typename T>
    typename ft::bidirectional_iterator<T>::difference_type
    operator<(const ft::bidirectional_iterator<T> lhs, const ft::bidirectional_iterator<T> rhs)
    {
        return (lhs._ptr < rhs._ptr);
    }

    template <typename T1, typename T2>
    typename ft::bidirectional_iterator<T1>::difference_type
    operator<(const ft::bidirectional_iterator<T1> lhs, const ft::bidirectional_iterator<T2> rhs)
    {
        return (lhs._ptr < rhs._ptr);
    }

    template <typename T>
    typename ft::bidirectional_iterator<T>::difference_type
    operator>(const ft::bidirectional_iterator<T> lhs, const ft::bidirectional_iterator<T> rhs)
    {
        return (lhs._ptr > rhs._ptr);
    }

    template <typename T1, typename T2>
    typename ft::bidirectional_iterator<T1>::difference_type
    operator>(const ft::bidirectional_iterator<T1> lhs, const ft::bidirectional_iterator<T2> rhs)
    {
        return (lhs._ptr > rhs._ptr);
    }

    template <typename T>
    typename ft::bidirectional_iterator<T>::difference_type
    operator<=(const ft::bidirectional_iterator<T> lhs, const ft::bidirectional_iterator<T> rhs)
    {
        return (lhs._ptr <= rhs._ptr);
    }

    template <typename T1, typename T2>
    typename ft::bidirectional_iterator<T1>::difference_type
    operator<=(const ft::bidirectional_iterator<T1> lhs, const ft::bidirectional_iterator<T2> rhs)
    {
        return (lhs._ptr <= rhs._ptr);
    }

    template <typename T>
    typename ft::bidirectional_iterator<T>::difference_type
    operator>=(const ft::bidirectional_iterator<T> lhs, const ft::bidirectional_iterator<T> rhs)
    {
        return (lhs._ptr >= rhs._ptr);
    }

    template <typename T1, typename T2>
    typename ft::bidirectional_iterator<T1>::difference_type
    operator>=(const ft::bidirectional_iterator<T1> lhs, const ft::bidirectional_iterator<T2> rhs)
    {
        return (lhs._ptr >= rhs._ptr);
    }
};


#endif