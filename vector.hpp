/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwane <mwane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 13:21:43 by mwane             #+#    #+#             */
/*   Updated: 2022/11/12 19:26:10 by mwane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <memory>
#include <algorithm>
#include "iterator.hpp"
#include "traits.hpp"
#include "pair.hpp"
#include "utils.hpp"
#include "iterator_traits.hpp"

/*
rm -rf containers_test
rm -rf 42TESTERS-CONTAINERS
git clone git@github.com:mli42/containers_test.git
git clone git@github.com:Mazoise/42TESTERS-CONTAINERS.git
.vscode
containers_test
ft_containers_monkey_tester
42TESTERS-CONTAINERS
containers_test
ft_containers_monkey_tester
42TESTERS-CONTAINERS

*/

namespace ft
{
	template <class T, class Allocator = std::allocator<T> >
	class vector
	{

		public:
			typedef T                                                      value_type;
			typedef Allocator                                              allocator_type;
			typedef std::size_t                                            size_type;
			typedef std::ptrdiff_t                                         difference_type;
			typedef ft::vector<value_type, Allocator>                      Ivector;
			typedef typename Allocator::reference                          reference;
			typedef typename Allocator::const_reference                    const_reference;
			typedef typename Allocator::pointer                            pointer;
			typedef typename Allocator::const_pointer                      const_pointer;
			typedef ft::random_access_iterator<T>                 		   iterator;
			typedef ft::random_access_iterator<const T>          		   const_iterator;
			typedef ft::reverse_iterator<iterator>                         reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>                   const_reverse_iterator;


			//Member Functions

			vector() : _allocator(Allocator()), _front(), _back(), _size(0), _capacity(0){}
			
			explicit vector(const Allocator &alloc) : _allocator(alloc), _front(), _back(), _size(0), _capacity(0){}
			
			explicit vector(size_type count, const value_type &value = value_type(), const Allocator &alloc = Allocator())
				: _allocator(alloc), _front(_allocator.allocate(count)), _back(), _size(count),  _capacity(count)
			{
				_back = _front;
				_size = count;
				for (; count > 0; count--)
				{
					_allocator.construct(_back, value);
					_back++;
				}
				_end = _back;
			}

			template < class InputIt>
			explicit vector(InputIt first, InputIt last, const Allocator &alloc = allocator_type()
			, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = NULL)
			: _allocator(alloc), _front(), _back(), _size(0), _capacity(0)
			{
				assign(first, last);
			}


			vector(const Ivector &other) : _allocator(Allocator()), _front(), _back(), _size(other._size), _capacity(other._capacity)
			{
				_front = alloc(other._size);
				_back = _front;
				_end = _front + other.size();
				for (size_type i = 0; i < other._size; i++, _back++)
					_allocator.construct(_back, other._front[i]);
				_size = other.size();
			}
			
			~vector()
			{
				clear();
				_allocator.deallocate(_front, _capacity);
			}

			Ivector &operator=(const Ivector &other)
			{
				clear();
				assign(other.begin(), other.end()); 
				return (*this);
			}

			void assign(size_type count, const T &value)
			{
				clear();
				resize(count, value);
			}

			template <class InputIt>
			void assign(InputIt first, InputIt last
			, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = NULL)
			{
				InputIt tmp(first);
				clear();
				size_t i = 0;
				for (; tmp != last; tmp++)
					i++;
				realloc(size() + i);
				_back = _front;
				for (; first != last; first++, _back++)
					_allocator.construct(_back, *first);
				_size = i;
			}

			allocator_type  get_allocator() const
			{
				return (_allocator);
			}

			//Element access

			reference at(size_type pos)
			{
				if (pos >= _size)
					throw std::out_of_range("out of range");
				return (*(_front + pos));
			}

			const_reference at(size_type pos) const
			{
				if (pos >= _size)
					throw std::out_of_range("out of range");
				return (*(_front + pos));
			}

			reference operator[](size_type pos)
			{
				return (*(_front + pos));
			}

			const_reference operator[](size_type pos) const
			{
				return (*(_front + pos));
			}

			reference front()
			{
				return (*_front);
			}

			const_reference front() const
			{
				return (*_front);
			}

			reference back()
			{
				return (*(_front + (_size - 1)));
			}

			const_reference back() const
			{
				return (*(_front + (_size - 1)));
			}

			value_type *data()
			{
				return (_front);
			}

			const value_type *data() const
			{
				return (_front);
			}
			
			//Iterator

			iterator begin()
			{
				return (iterator(_front));
			}

			const_iterator begin() const
			{
				return (const_iterator(_front));
			}

			iterator end()
			{
				return (iterator(_front + _size));
			}

			const_iterator end() const
			{
				return (const_iterator(_front + _size));
			}

			reverse_iterator rbegin()
			{
				return (reverse_iterator(end()));
			}

			const_reverse_iterator rbegin() const
			{
				return (const_reverse_iterator(end()));
			}

			reverse_iterator rend()
			{
				return (reverse_iterator(begin()));
			}

			const_reverse_iterator rend() const
			{
				return (const_reverse_iterator(begin()));
			}

			//Capacity

			bool empty() const
			{
				if (_size == 0)
					return (true);
				return (false);
			}

			size_type size() const
			{
				return (_size);
			}
			
			size_type   max_size() const
			{
				return (_allocator.max_size());
			}

			void reserve(size_type new_cap)
			{
				if (new_cap < capacity())
					return;
				if (new_cap > max_size())
					throw std::length_error("vector::reserve");

				pointer tmp = _allocator.allocate(new_cap);
				size_type i = 0;
				for (; i < _size; i++)
				{
					_allocator.construct(tmp + i, *(_front + i));
					_allocator.destroy(_front + i);
				}
				_allocator.deallocate(_front, _capacity);
				_capacity = new_cap;
				_front = tmp;
			}
			
			size_type capacity() const
			{
				return (_capacity);
			}

			//Modifiers
			
			void clear()
			{
				for (size_type n = 0; n < _size; n++)
				{
					_allocator.destroy(_front + n);
				}
				_size = 0;
			}
			
			iterator insert(iterator pos, const T &value)
			{
				difference_type posx = pos.base() - _front;
				insert(pos, 1, value);
				return iterator(begin() + posx);
			}

			void insert(iterator pos, size_type count, const T &value)
			{
				size_type i = pos - begin();
				size_type y = end() - pos;
				size_type x = 0;

				if (count == 0)
					return ;
				if (_size + count > _capacity)
				{
					if (_size + count <= _capacity * 2)
					{
						if (_capacity > 400)
							x = 400;
						else 
							x = _capacity;
						reserve(_capacity + x);
					}
					else
						reserve(_size + count);
				}
				_size += count;
				for(x = 0; x < y; x++)
				{
					_allocator.construct(&_front[_size - x - 1], _front[_size - count - x -1]);
					_allocator.destroy(&_front[_size - count - x - 1]);
				}
				for(x = 0; x < count; x++)
				{
					_allocator.construct(&_front[i + x], value);
				}
			}

			template <class InputIt>
			void insert(iterator pos, InputIt first, InputIt last
			, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = NULL)
			{
				size_type i = 0;

				for (InputIt tmp(first); tmp != last; tmp++)
					i++;

				while (i)
				{
					pos = insert(pos, *first);
					i--;
					pos++;
					first++;
				}
			}

			iterator erase(iterator pos)
			{
				return (erase(pos, pos + 1));
			}

			iterator erase(iterator first, iterator last)
			{
				size_type start, finish, diff;
				
				if (first == end() || first == last)
					return first;
				start = first - begin();
				finish = end() - last;
				diff = 0;
				iterator tmp(first);
            	for(; tmp != last; tmp++)
					diff++;
				size_type i = 0;
				for (; i < finish;i++)
				{
					_allocator.destroy(&_front[start + i]);
					_allocator.construct(&_front[start + i], _front[start + i + diff]);
				}
				size_type k = diff;
				for (; diff > 0; diff--, finish++)
					_allocator.destroy(&_front[start + finish]);
				_size -= k;
				return (first);
			}

			void push_back(const T &value)
			{
				resize(_size + 1, value);
			}

			void pop_back()
			{
				_allocator.destroy(_front + (--_size));
			}

			void resize(size_type count, value_type value = value_type())
			{
				if (count > capacity())
					realloc(count);
				size_type i = _size;
				while (i < count)
				{
					_allocator.construct(_front + i, value);
					i++;
					_size++;
				}
				for (size_type j = count; j < _size; j++)
					_allocator.destroy(_front + j);
				_size = count;
			}

			void swap(vector &other)
			{
				ft::swap(_front, other._front);
				ft::swap(_size, other._size);
				ft::swap(_allocator, other._allocator);
				ft::swap(_capacity, other._capacity);
				ft::swap(_end, other._end);
			}

		protected :

			pointer alloc(size_type const count)
			{
				pointer data = _allocator.allocate(count);
				_capacity = count;
				return data;
			}

			void realloc(size_type const count)
			{
				if (count <= _capacity)
					return;
				else if (count < _capacity * 2)
					reserve(_capacity * 2);
				else
					reserve(count);
			}

			void move_right(iterator pos, value_type value)
			{
				value_type current;
				value_type next;

				current = value;
				iterator tmp(end() + 1);
				while (pos != tmp)
				{
					next = *pos;
					*pos = current;
					current = next;
					pos++;
				}
				_size++;
			}

		private:
			allocator_type  _allocator;
			pointer     	_front;
			pointer     	_back;
			size_type   	_size;
			size_type   	_capacity;
			pointer     	_end;

			void    check_range(const size_type n)
			{
				if (n >= size())
					throw std::out_of_range("out of range");
			}
	};
	
	template< class T, class Alloc >
	bool operator==(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		for (size_t i = 0; i < lhs.size(); i++)
		{
			if (lhs[i] != rhs[i])
				return (false); 
		}	
		return (true);
	}


	template< class T, class Alloc >
	bool operator!=(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs)
	{
		return !(lhs == rhs);
	}


	template< class T, class Alloc >
	bool operator<(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}


	template< class T, class Alloc >
	bool operator<=(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs)
	{
		return !(rhs < lhs);
	}

	template< class T, class Alloc >
	bool operator>(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs)
	{
		return (rhs < lhs);
	}

	template< class T, class Alloc >
	bool operator>=(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs)
	{
		return !(lhs < rhs);
	}

	template<class T, class Alloc>
	void swap(ft::vector<T, Alloc>& lhs, ft::vector<T,Alloc>& rhs)
	{
		lhs.swap(rhs);
	}
};


#endif