/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwane <mwane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 15:33:37 by mwane             #+#    #+#             */
/*   Updated: 2022/09/04 19:05:46 by mwane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "pair.hpp"
#include "iterator.hpp"

template<class Key,
		 class T,
		 class Compare = std::less<Key>,
		 class Allocator = std::allocator<ft::pair<const Key, T> > >
class map
{
	typedef Key                         			key_type;
	typedef T                           			mapped_type;
	typedef std::pair<const Key, T>     			value_type;
	typedef typename std::size_t;					size_type;
	typedef typename std::ptrdiff_t					difference_type;
	typedef typename Compare						key_compare;
	typedef typename Allocator						allocator_type;
	typedef typename value_type&					reference;
	typedef typename value_type const & 			const_reference;
	typedef typename Allocator::pointer 			pointer;
	typedef typename Allocator::const_pointer 		const_pointer;
	typedef typename ft::iterator<T>				iterator;
	typedef typename ft::iterator<T> const			const_iterator;
	typedef typename ft::reverse_iterator<T>		reverse_iterator;
	typedef typename ft::reverse_iterator<T> const	const_reverse_iterator;

	class value_compare : public std::binary_function<value_type, value_type, bool>
	{
		public :
			bool operator()(const value_type& lhs, const value_type& rhs ) const
			{
				return (comp(lhs.first, rhs.second));
			}
		protected :
			Compare comp;
			value_compare(Compare c) : comp(c){};
	};

	public :
		key_compare		comp;
		allocator_type	alloc;

		//Member function
		map()
		{
			
		};

		explicit map( const Compare& comp, const Allocator& alloc = Allocator() ) comp(comp), alloc(alloc)
		{

		};

		template< class InputIt >
		map( InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator() ) comp(comp), alloc(alloc)
		{

		};

		map( const map& other ) comp(other.comp) alloc(other.alloc)
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
			return (alloc);
		};

		//Element access
		mapped_type& at( const Key& key );

		const mapped_type& at( const Key& key ) const;

		mapped_type& operator[](const Key& key)
		{
			
		};

		//Capacity
		bool	empty() const;

		size_type size() const;

		size_type max_size() const;
		
		void clear();

		std::pair<iterator, bool> insert( const value_type& value );

		iterator insert( iterator hint, const value_type& value );

		template< class InputIt >
		void insert( InputIt first, InputIt last );

		void erase( iterator pos );

		void erase( iterator first, iterator last );

		void swap( map& other );

		size_type count( const Key& key ) const;

		const_iterator find( const Key& key ) const;

		std::pair<iterator,iterator> equal_range( const Key& key );

		std::pair<const_iterator,const_iterator> equal_range( const Key& key ) const;

		iterator lower_bound( const Key& key );

		const_iterator lower_bound( const Key& key ) const;

		iterator lower_bound( const Key& key );

		iterator upper_bound( const Key& key );

		const_iterator upper_bound( const Key& key ) const;

		key_compare key_comp() const;

		std::map::value_compare value_comp() const;

		iterator begin();

		const_iterator begin() const;

		iterator end();

		const_iterator end() const;
};