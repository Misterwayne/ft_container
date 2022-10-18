/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwane <mwane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 13:21:43 by mwane             #+#    #+#             */
/*   Updated: 2022/10/15 16:26:46 by mwane            ###   ########.fr       */
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

/*rm -rf containers_test
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
			typedef ft::random_access_iterator<value_type>                 iterator;
			typedef ft::random_access_iterator<const value_type>           const_iterator;
			typedef ft::reverse_iterator<iterator>                         reverse_iterator;
			typedef ft::reverse_iterator<const iterator>                   const_reverse_iterator;


			//Member Functions

			vector() : _allocator(Allocator()), _front(), _back(), _size(0), _capacity(0), _max_size(0){};
			
			explicit vector(const Allocator &alloc) : _allocator(alloc), _front(), _back(), _size(0), _capacity(0), _max_size(0){};
			
			explicit vector(size_type count, const value_type &value = value_type(), const Allocator &alloc = Allocator())
				: _allocator(alloc), _front(_allocator.allocate(count)), _back(), _size(0),  _capacity(count), _max_size(count)
			{
				_back = _front;
				_size = count;
				for (; count > 0; count--)
				{
					_allocator.construct(_back, value);
					_back++;
				}
				_end = _back;
			};

			template < class InputIt>
			explicit vector(InputIt first, InputIt last, const Allocator &alloc = allocator_type()
			, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = NULL)
			: _allocator(alloc), _front(), _back()
			{
				size_type i = 0;
				InputIt tmp(first);
				while (tmp != last)
				{
					i++;
					tmp++;
				}
				_back = _front;
				_front = _allocator.allocate(i);
				for (size_type y = 0; y < i; y--)
					_allocator.construct(_front + y, *first);
				_size = i;
			};


			vector(const Ivector &other) : _allocator(Allocator()), _front(), _back(), _size(other._size), _capacity(other._capacity), _max_size(other._max_size)
			{
				_front = alloc(other._size);
				_back = _front;
				_end = _front + other.size();
				for (size_type i = 0; i < other._size; i++, _back++)
					_allocator.construct(_back, other._front[i]);
				_size = other.size();
			};
			
			~vector()
			{
				clear();
				_allocator.deallocate(_front, _capacity);
			};

			Ivector &operator=(const Ivector &other)
			{
				clear();
				_front = alloc(other._size);
				_max_size = other._max_size;
				_capacity = other.capacity();
				_back = _front;
				_end = _front + other.size();
				for (size_type i = 0; i < other._size; i++, _back++)
					_allocator.construct(_back, other._front[i]);
				_size = other.size();
				return (*this);
			};

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
			};


			allocator_type  get_allocator() const
			{
				return (_allocator);
			}

			//Element access

			reference at(size_type pos)
			{
				if (pos >= _size)
					throw std::out_of_range("out of raneg");
				return (*(_front + pos));
			}

			const_reference at(size_type pos) const
			{
				if (pos >= _size)
					throw std::out_of_range("out of raneg");
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
				return (*(_front + _size));
			}

			const_reference back() const
			{
				return (*(_front + _size));
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
				return (reverse_iterator(end() - 1));
			}

			const_reverse_iterator rbegin() const
			{
				return (const_reverse_iterator(end() - 1));
			}

			reverse_iterator rend()
			{
				return (reverse_iterator(begin() - 1));
			}

			const_reverse_iterator rend() const
			{
				return (const_reverse_iterator(begin() - 1));
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
				return (_capacity);
			}

			void reserve(size_type new_cap)
			{
				if (new_cap < capacity())
					return;

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
				_size = i;
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
				size_type i = &(*pos) - _front;

				realloc(size() + 1);
				pos = begin();
				for (size_type y = 0; y < i; y++)
				{
					pos++;
				}
				move_right(pos, value);
				return pos;
			}

			void insert(iterator pos, size_type count, const T &value)
			{
				size_type i = &(*pos) - _front;

				realloc(size() + count);

				pos = begin();
				for (size_type y = 0; y < i; y++)
					pos++;
				while (count > 0)
				{
					move_right(pos, value);
					count--;
				}
			}

			template <class InputIt>
			void insert(iterator pos, InputIt first, InputIt last
			, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = NULL)
			{
				size_type i = &(*pos) - _front;

				realloc(size() + i);
				pos = begin();
				for (size_type y = 0; y < i; y++)
					pos++;
				for (; first != last; first++)
					move_right(pos, *first);
			}

			iterator erase(iterator pos)
			{
				move_left(pos);
				resize(_size);
				return (pos);
			}

			iterator erase(iterator first, iterator last)
			{
				for (; first != last; first++)
					erase(first);
				return (first);
			}

			void push_back(const T &value)
			{
				resize(_size + 1, value);
			}

			void pop_back()
			{
				resize(_size - 1);
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
				vector tmp;

				tmp._front = other._front;
				tmp._size = other._size;
				tmp._allocator = other._allocator;
				tmp._max_size = other._max_size;
				tmp._capacity = other._capacity;
				tmp._end = other._end;
				this->_front = tmp._front;
				this->_size = tmp._size;
				this->_allocator = tmp._allocator;
				this->_max_size = tmp._max_size;
				this->_capacity = tmp._capacity;
				this->_end = tmp._end;
				other._front = this->_front;
				other._size = this->_size;
				other._allocator = this->_allocator;
				other._max_size = this->_max_size;
				other._capacity = this->_capacity;
				other._end = this->_end;
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
				{
					reserve(_capacity * 2);
				}
				else
				{
					reserve(count);
				}
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


			void move_left(iterator pos)
			{
				value_type current;

				for (iterator it = pos; it != end(); it++)
				{
					pos++;
					current = *pos;
					*it = current;
				}
				_allocator.destroy(_front + _size);
				_size--;
			}


		private:
			Allocator   _allocator;
			pointer     _front;
			pointer     _back;
			size_type   _size;
			size_type   _capacity;
			size_type   _max_size;
			pointer     _end;

			void    check_range(const size_type n)
			{
				if (n >= size())
					throw std::out_of_range("out of range");
			}
	};
	
	template< class T, class Alloc >
	bool operator==(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs)
	{
		return (lhs.size() == rhs.size());
	}


	template< class T, class Alloc >
	bool operator!=(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs)
	{
		return !(lhs == rhs);
	}


	template< class T, class Alloc >
	bool operator<(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs)
	{
		return (lhs.size() < rhs.size());
	}


	template< class T, class Alloc >
	bool operator<=(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs)
	{
		return (lhs.size() <= rhs.size());
	}

	template< class T, class Alloc >
	bool operator>(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs)
	{
		return (lhs.size() > rhs.size());
	}

	template< class T, class Alloc >
	bool operator>=(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs)
	{
		return (lhs.size() >= rhs.size());
	}

	template<class T, class Alloc>
	void swap(ft::vector<T, Alloc>& lhs, ft::vector<T,Alloc>& rhs)
	{
		lhs.swap(rhs);
	}
};


#endif