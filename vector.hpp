/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwane <mwane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 13:21:43 by mwane             #+#    #+#             */
/*   Updated: 2022/09/04 23:29:57 by mwane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <memory>
#include <algorithm>
#include <iterator>
#include "iterator.hpp"

namespace ft
{
    template <class T, class Allocator = std::allocator<T> >
    class vector : public ft::iterator< vector<T> >
    {

        public :

            typedef T                           		 		value_type;
            typedef std::size_t                 		 		size_type;
            typedef std::ptrdiff_t              		 		difference_type;
            typedef ft::vector<value_type, Allocator>           Ivector;
            typedef typename Allocator::reference   			reference;
            typedef typename Allocator::const_reference    		const_reference;
            typedef typename Allocator::pointer          		ptr;
            typedef typename Allocator::const_pointer    		const_ptr;
            typedef ft::iterator<value_type>                    iterator;
            typedef ft::iterator<value_type const>              const_iterator;
            typedef ft::reverse_iterator<iterator>              reverse_iterator;
            typedef ft::reverse_iterator<iterator const>        const_reverse_iterator;
            
            vector() : _allocator(Allocator()), _front(nullptr), _back(nullptr), _size(0), _capacity(0), _max_size(0)
            {
                
            };
            explicit vector( const Allocator& alloc ) : _allocator(alloc), _front(nullptr), _back(nullptr), _size(0), _capacity(0), _max_size(0)
            {};
            explicit vector( size_type count, const value_type& value = value_type(), const Allocator& alloc = Allocator())
            : _allocator(alloc), _front(_allocator.allocate(count)), _back(nullptr), _capacity(count), _max_size(count), _size(0)
            {
                _back = _front;
                for(; count > 0; count--)
                {
                    _allocator.construct(_back, value);
                    _back++;
                    _size++;
                }
                _back = nullptr;
                _end = _front + count;
            };
            
            vector(iterator first, iterator last, const Allocator& alloc = Allocator() ) :  _allocator(alloc), _front(nullptr), _back(nullptr)
            {
                int i = 0;
                iterator tmp(first);
                while (tmp != last)
                {
                    i++;
                    tmp++;
                }
                _front = alloc(i);
                _end = _front + i;
                _size = i;
                _back = _front;
                for (; first != last; first++)
                    push_back(*first);
            };
            vector( const ft::vector<value_type, Allocator>& other ) : _allocator(Allocator()), _front(nullptr), _back(nullptr), _size(0)
            {
                _front = alloc(other._size);
                _max_size = other._max_size;
                _capacity = other.capacity();
                _back = _front;
                _end = other._end;
                for(int i = 0; i < other._size; i++, _back++)
                    _allocator.construct(_back, other._front[i]);
                _size = other.size();
            };
            ~vector()
            {
                // _allocator.deallocate(_front, _size);
            };

            
            ft::vector<value_type, Allocator>& operator=( const ft::vector<value_type, Allocator>& other )
            {
                
            };

            void    reserve(size_type new_cap)
            {
                Ivector tmp = (*this);

                if (new_cap < capacity())
                    return ;

                _front = alloc(new_cap);
                copydata(tmp);
                dealloc(tmp);
            }

            void assign( size_type count, const T& value )
            {
                size_type i = 0;
                for (; i < capacity(); i++)
                    _allocator.destroy(_front + i);
                realloc(count);
                i = 0;
                while (count > 0)
                {
                    _allocator.construct(_front + i, value);
                    count--;
                    i++;
                }
            };

            void assign( iterator first, iterator last )
            {
                if (first == begin() || last == end())
                    throw std::out_of_range("same object");
                iterator tmp(first);
                size_t i = 0;
                for (; tmp != last; tmp++)
                    i++;
                realloc(size() + i);
                _max_size = i;
                _size = i;
                _back = _front;
                for (; first != last- 1; first++, _back++)
                    _allocator.construct(_back, *first);
            };

            reference at( size_type pos )
            {
                if (pos >= _size)
                    throw ;
                return (*(_front + pos));
            };
            
            const_reference at( size_type pos ) const
            {
                if (pos >= _size)
                    throw ;
                return (*(_front + pos));
            };

            reference operator[]( size_type pos )
            {
                return (*(_front + pos));
            };
            const_reference operator[]( size_type pos ) const
            {
                return (*(_front + pos));
            };

            reference front() 
            {
                return (*_front);
            };
            
            const_reference front() const
            {
                return (*_front);
            };

            reference back() 
            {
                return (*(_back - 1));
            };
            
            const_reference back() const 
            {
                return (*(_back - 1));
            };

            value_type* data()
            {
                return (_front);
            };
            
            const value_type* data() const
            {
                return (_front);
            };

            iterator begin()
            {
                return (_front);
            };

            iterator end()
            {
                return (_front + _size);
            };

            const_iterator end() const
            {
                return (_front + _size);
            };

            reverse_iterator rbegin()
            {
                return (reverse_iterator(_front + _size));
            };
            const_reverse_iterator rbegin() const
            {
                return (const_reverse_iterator(_front + _size));
            };

            reverse_iterator rend()
            {
                return (reverse_iterator(_front));
            };
            const_reverse_iterator rend() const
            {
                return (const_reverse_iterator(_front));
            };

            bool empty() const
            {
                if (_size == 0)
                    return (true);
                return (false);
            };

            size_type size() const
            {
                return (_size);
            };

            iterator insert( iterator pos, const T& value )
            {
                size_type i = &(*pos) - _front;

                
                std::cout << size() <<" = size\n";
                realloc(size() + 1);
                pos = begin();
                for (size_type y = 0; y < i; y++)
                {
                    pos++;
                }
                move_right(pos, value);
                return pos;

            };
            
            void insert( iterator pos, size_type count, const T& value )
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
            };
            
            template< class InputIt >
            void insert( iterator pos, InputIt first, InputIt last );

            iterator erase( iterator pos )
            {
                move_left(pos);
                return (pos);
            };
            
            iterator erase( iterator first, iterator last )
            {
                for (;first != last; last--)
                    erase(first);
                return (first);
            };

            void push_back( const T& value )
            {
                insert(end(), value);
            };

            void pop_back()
            {
                _end -= 1;
                _allocator.destroy(_end);
                _back--;
                _size--;
            };

            void            dealloc(Ivector obj)
            {
                for (size_type n = 0; n < _size; n++)
                    _allocator.destroy(obj._front + n);
                _allocator.deallocate(obj._front, obj._end - obj._front);
            }

            void            copydata(Ivector obj)
            {
                size_type i = obj._end - obj._front;
                value_type *data = obj._front;

                for (size_type i = 0; i < obj._size; i++)
                    *(_front + i) = *(data + i);
                _size = obj._size;
                _end = _front + i;
                _back = _front + i;
            }

            value_type*     alloc(size_type const count)
            {
                value_type *data = _allocator.allocate(count);

                _capacity = count;
                for (size_type i = 0; i < count; i++)
                {
                    _allocator.construct(data + i, value_type());
                }
                return data;
            }

            void    realloc(size_type const count)
            {
                Ivector tmp = *(this);

                std::cout << count << "\n";
                if (count <= _capacity)
                    return ;
                else if (count <= _capacity * 2 && count < _capacity)
                {
                    _front = alloc(_size * 2);
                }
                else
                {
                    _front = alloc(count);
                }
                _back = _front;
                _end = _front;
                copydata(tmp);
                dealloc(tmp);
            }

            void    move_right(iterator pos, value_type value)
            {
                value_type current;
                value_type next;

                current = value;
                iterator tmp(end());
                std::cout << "pos 1 = "<<*pos << "\n";
                while (pos != tmp)
                {
                    next = *pos;
                    *pos = current;
                    std::cout << "pos 2 = "<<*pos << "\n";
                    current = next;
                    pos++;
                }
                std::cout << "back = " << back() << "\n";
            }
            
            void    move_left(iterator pos)
            {
                value_type current;

                for (iterator it = pos; it != end(); it++)
                {
                    pos++;
                    current = *pos;
                    *it = current;
                }
                _end -= 1;
            }

            void clear()
            {
                while (_size)
                    pop_back();
            };

            size_type size()
            {
                return (_size);
            }
            //not finished
            size_type capacity() const
            {
                return (_capacity);
            };
            void resize( size_type count, T value = T() )
            {
                Ivector tmp(*this);
                if (count > capacity())
                {
                    realloc(count);
                }
                while (count > _size)
                {
                    push_back(value);
                    count--;
                    return ;
                }
                iterator ite = end();
                while (_size >= count)
                {
                    erase(ite);
                    _end--;
                    count++;
                    ite--;
                }
            };
            
            void swap( vector& other )
            {
                ptr tmp;

                tmp = other._front;
                _front = tmp;
                other._front = _front;
            };

            
            
            friend bool operator==( const vector& lhs, const vector& rhs )
            {
                return (lhs.size() == rhs.size());
            };
            
            friend bool operator!=( const vector& lhs, const vector& rhs )
            {
                return !(lhs == rhs);
            };

            
            friend bool operator<( const vector& lhs, const vector& rhs )
            {
                return (lhs.size() < rhs.size());
            };

            
            friend bool operator<=( const vector& lhs, const vector& rhs )
            {
                return (lhs.size() <= rhs.size());
            };
            
            friend bool operator>( const vector& lhs, const vector& rhs )
            {
                return (lhs.size() > rhs.size());
            };

            
            friend bool operator>=( const vector& lhs, const vector& rhs )
            {
                return (lhs.size() >= rhs.size());
            };
        
        private :
            Allocator       _allocator;
            ptr			    _front;
            ptr				_back;
            size_type       _size;
            size_type       _capacity;
            size_type       _max_size;
            ptr             _end;
    };
};


#endif