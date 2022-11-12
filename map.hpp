/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwane <mwane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 15:33:37 by mwane             #+#    #+#             */
/*   Updated: 2022/11/08 20:56:05 by mwane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "pair.hpp"
#include "utils.hpp"
#include "iterator.hpp"
#include "iterator_traits.hpp"
#include "binary_search_three.hpp"

namespace ft
{

	template<class Key,
			class T,
			class Compare = ft::less<Key>,
			class Allocator = std::allocator<ft::pair<const Key, T> > >
	class map
	{
		public :
			typedef Key                         							key_type;
			typedef T                           							mapped_type;
			typedef ft::pair<Key, T>     									value_type;
			typedef RBSTnode<key_type, mapped_type>							Node;
			typedef typename std::size_t									size_type;
			typedef typename std::ptrdiff_t									difference_type;
			typedef Compare													key_compare;
			typedef Allocator												allocator_type;
			typedef ft::bidirectional_iterator<Node>						iterator;
			typedef iterator const											const_iterator;
			typedef typename ft::reverse_iterator<iterator>					reverse_iterator;
			typedef typename ft::reverse_iterator<iterator> const			const_reverse_iterator;
			typedef typename allocator_type::template rebind<Node>::other	node_allocator;
			typedef typename allocator_type::reference						reference;
			typedef typename allocator_type::const_reference				const_reference;
			typedef typename allocator_type::pointer 						pointer;
			typedef typename allocator_type::const_pointer 					const_pointer;
			typedef RBST<key_type, mapped_type>								Tree;
		
			class value_compare : public ft::binary_function<value_type, value_type, bool>
			{
				friend class map<key_type, mapped_type, key_compare, allocator_type>;
				
				public :
					bool operator()(const value_type& lhs, const value_type& rhs ) const
					{
						return (comp(lhs.first, rhs.first));
					}
				protected :
					Compare comp;
					value_compare(Compare c) : comp(c){};
			};

			key_compare				_comp;
			allocator_type			_alloc;
			size_type 				_size;
			size_type 				_max_size;
			Tree					_rbt;

			map() : _rbt(Tree()), _alloc(Allocator()), _comp(Compare())
			{
				_size = 0;
			}

			explicit map( const Compare& comp, const Allocator& alloc = Allocator() ) : _comp(comp), _alloc(alloc), _rbt(Tree())
			{
				_size = 0;
			}

			template< class InputIt >
			map( InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator() ) : _comp(comp), _alloc(alloc), _rbt(Tree())
			{
				_size = 0;
				insert<InputIt>(first, last);
			}

			map( const map& other ) : _comp(other.comp), _alloc(other.alloc), _rbt(other._rbt)
			{
				_size = other._size;
				_max_size = other._max_size;
				insert(other.begin(), other.end());
			}

			~map()
			{
				clear();
				erase(begin());
			}

			map& operator=( const map& other )
			{
				_rbt = other._rbt;
				_alloc = other._alloc;
				_size = other._size;
				_max_size = other._max_size;
			}

			allocator_type get_allocator() const
			{
				return (_alloc);
			}

			//Element access
			
			mapped_type at( const Key& key )
			{
				mapped_type tmp = _rbt.getValue(key);
				return (tmp);
			}

			const mapped_type at( const Key& key ) const
			{
				mapped_type tmp = _rbt.getValue(key);
				return (tmp);
			}

			mapped_type operator[](const Key& key)
			{
				return (_rbt.getValue(key));
			}

			void	print()
			{
				_rbt.inorder(_rbt.root);
			}

			//Iterator

			iterator begin()
			{
				return (iterator(_rbt.FindMin(), _rbt.FindMax()));
			}

			const_iterator begin() const
			{
				return (const_iterator(_rbt.FindMin(), _rbt.FindMax()));
			}

			iterator end()
			{
				return (iterator(_rbt.FindMax()->right, nullptr));
			}

			const_iterator end() const
			{
				return (const_iterator(_rbt.FindMax()->right, nullptr));
			}

			reverse_iterator rbegin()
			{
				return reverse_iterator(iterator(_rbt.FindMax(), _rbt.FindMin()));
			}

			const_reverse_iterator rbegin() const
			{
				return const_reverse_iterator(iterator(_rbt.FindMax(), _rbt.FindMin()));
			}

			reverse_iterator rend()
			{
				return reverse_iterator(iterator(_rbt.FindMin()->left, nullptr));
			}

			const_reverse_iterator rend() const;
			
			//Capacity
			
			bool	empty() const
			{
				if (_size == 0)
					return (true);
				return (false);
			}

			size_type size() const
			{
				return (_size);
			}

			size_type max_size() const
			{
				return (_max_size);
			}
			
			//Modifier
			
			void clear()
			{
				while (_size != 2)
					erase(begin());
			}

			ft::pair<iterator, bool> insert( const value_type& value )
			{
				_rbt.Insert(value.first, value.second);
				_size++;
				return (ft::pair<iterator, bool>(begin(), true));
			}

			iterator insert( iterator hint, const value_type& value )
			{
				insert(value);
				return (hint);
			}

			template< class InputIt = ft::bidirectional_iterator<Node> >
			void insert( InputIt first, InputIt last )
			{
				for(; first != last; first++)
					insert(first, value_type(first->first, first->second));
			}

			size_type erase( const Key& key )
			{
				return(_rbt.Remove(key));
			}

			void erase( iterator pos )
			{
				erase(pos->first);
				_size--;
			}

			void erase( iterator first, iterator last )
			{
				for(;first != last; first++)
					erase(first->first);
			}

			void swap( map& other )
			{
				key_compare				tmp_comp = other._comp;
				allocator_type			tmp_alloc = other._alloc;
				size_type 				tmp_size = other._size;;
				size_type 				tmp_max_size = other._max_size;
				Tree					tmp_rbt = other._rbt;

				other._comp = value_compare();
				other._alloc = _alloc;
				other._size = _size;
				other._max_size = _max_size;
				other._rbt = _rbt;

				_rbt = tmp_rbt;
				_comp = tmp_comp;
				_size = tmp_size;
				_max_size = tmp_max_size;
				_alloc = tmp_alloc;

			}

			//Lookup

			size_type count( const Key& key )
			{
				if (_rbt.Search(key))
					return (1);
				return (0);
			}

			const_iterator find( const Key& key ) const
			{
				Node *tmp2 = _rbt.root;
				return (const_iterator(_rbt.Search(tmp2, key), _rbt.FindMax()->right));
			}

			std::pair<iterator,iterator> equal_range( const Key& key )
			{
				return ft::make_pair(lower_bound(key), upper_bound(key));
			}

			std::pair<const_iterator,const_iterator> equal_range( const Key& key ) const
			{
				return ft::make_pair(lower_bound(key), upper_bound(key));
			}

			iterator lower_bound( const Key& key )
			{
				iterator it = begin();

				for(;it != end();it++)
				{
					if (_comp(it->first, key) == false)
						break;
				}
				return (it);
			}

			const_iterator lower_bound( const Key& key ) const
			{
				return (const_iterator(lower_bound(key)));
			}

			iterator upper_bound( const Key& key )
			{
				iterator it = begin();

				for(;it != end();it++)
				{
					if (_comp(key, it->first))
						break;
				}
				return (it);
			}

			const_iterator upper_bound( const Key& key ) const
			{
				return (const_iterator(upper_bound(key)));
			}

			key_compare key_comp() const
			{
				return key_compare();
			}

			value_compare value_comp() const
			{
				return value_compare(key_compare());
			}
	};

	template< class Key, class T, class Compare, class Alloc >
	bool operator==( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return (lhs._rbt == rhs._rbt);
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator!=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return (!lhs._rbt == rhs._rbt);
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator<( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return (lhs.size() < rhs.size());
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator<=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return (lhs.size() <= rhs.size());
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator>( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return (lhs.size() > rhs.size());
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator>=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return (lhs.size() >= rhs.size());
	}
}