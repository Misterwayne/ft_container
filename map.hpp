/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwane <mwane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 15:33:37 by mwane             #+#    #+#             */
/*   Updated: 2022/10/18 17:05:59 by mwane            ###   ########.fr       */
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
		typedef Key                         					key_type;
		typedef T                           					mapped_type;
		typedef RBST<key_type, mapped_type>						Tree;
		typedef std::pair<const Key, T>     					value_type;
		typedef typename std::size_t							size_type;
		typedef typename std::ptrdiff_t							difference_type;
		typedef Compare											key_compare;
		typedef Allocator										allocator_type;
		typedef typename Allocator::reference					reference;
		typedef typename Allocator::const_reference				const_reference;
		typedef typename Allocator::pointer 					pointer;
		typedef typename Allocator::const_pointer 				const_pointer;
		typedef ft::iterator<ft::random_access_iterator_tag, T>	iterator;
		typedef iterator const									const_iterator;
		typedef typename ft::reverse_iterator<iterator>			reverse_iterator;
		typedef typename ft::reverse_iterator<iterator> const	const_reverse_iterator;

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

		public :
			key_compare				_comp;
			allocator_type			_alloc;
			size_type 				_size;
			size_type 				_max_size;
			Tree					*_rbt;

			//Member function
			map() : _rbt(new Tree)
			{
				
			};

			explicit map( const Compare& comp, const Allocator& alloc = Allocator() ) : _comp(comp), _alloc(alloc), _rbt(new Tree)
			{

			};

			template< class InputIt >
			map( InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator() ) : _comp(comp), _alloc(alloc), _rbt(new Tree)
			{

			};

			map( const map& other ) : _comp(other.comp), _alloc(other.alloc), _rbt(other._rbt)
			{
				
			};

			~map()
			{

			};

			map& operator=( const map& other )
			{
				
			};

			allocator_type get_allocator() const
			{
				return (_alloc);
			};

			//Element access
			
			mapped_type at( const Key& key )
			{
				mapped_type tmp = _rbt->getValue(key);
				return (tmp);
			};

			const mapped_type at( const Key& key ) const
			{
				mapped_type tmp = _rbt->getValue(key);
				return (tmp);
			};

			mapped_type operator[](const Key& key)
			{
				return (_rbt->getValue(key));
			};

			//Iterator

			iterator begin();

			const_iterator begin() const;

			iterator end();

			const_iterator end() const;

			reverse_iterator rbegin();

			const_reverse_iterator rbegin() const;

			reverse_iterator rend();

			const_reverse_iterator rend() const;
			
			//Capacity
			
			bool	empty() const
			{
				if (_size == 0)
					return (true);
				return (false);
			};

			size_type size() const
			{
				return (_size);
			};

			size_type max_size() const
			{
				return (_max_size);
			};
			
			//Modifier
			
			void clear();

			ft::pair<iterator, bool> insert( const value_type& value )
			{

			};

			iterator insert( iterator hint, const value_type& value );

			template< class InputIt >
			void insert( InputIt first, InputIt last );

			void erase( iterator pos );

			void erase( iterator first, iterator last );

			void swap( map& other );

			//Lookup

			size_type count( const Key& key ) const
			{
				if (_rbt->Search(key))
					return (1);
				return (0);
			};

			const_iterator find( const Key& key ) const;

			std::pair<iterator,iterator> equal_range( const Key& key );

			std::pair<const_iterator,const_iterator> equal_range( const Key& key ) const;

			iterator lower_bound( const Key& key );

			const_iterator lower_bound( const Key& key ) const;

			iterator upper_bound( const Key& key );

			const_iterator upper_bound( const Key& key ) const;

			key_compare key_comp() const;

			value_compare value_comp() const;
	};

	template< class Key, class T, class Compare, class Alloc >
	bool operator==( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return (lhs);
	};

	template< class Key, class T, class Compare, class Alloc >
	bool operator!=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{

	};

	template< class Key, class T, class Compare, class Alloc >
	bool operator<( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{

	};

	template< class Key, class T, class Compare, class Alloc >
	bool operator<=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{

	};

	template< class Key, class T, class Compare, class Alloc >
	bool operator>( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{

	};

	template< class Key, class T, class Compare, class Alloc >
	bool operator>=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{

	};

}