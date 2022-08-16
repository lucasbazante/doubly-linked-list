#ifndef _LIST_H_
#define _LIST_H_

/*
 * @file list.h
 *
 * @author Fernanda Lustosa
 * @author Lucas Bazante
 *
 * @date Aug 19th, 2021.
 */

#include <iostream>  // cout, endl
using std::cout;
using std::endl;

#include <iterator>  // bidirectional_iterator_tag
#include <cassert>   // assert()
#include <algorithm> // copy
using std::copy;
#include <cstddef>   // std::ptrdiff_t
#include <type_traits>

namespace sc   // linear sequence. Better name: sequence container (same as STL).
{
	/*!
	 * A class representing a biderectional iterator defined over a linked list.
	 *
	 * \note
	 * This iterator only works for traversing elements inside the same list.
	 *
	 * This class is incomplete and it is provided "as is".
	 *
	 * \date May, 2nd 2017.
	 * \author Selan R. dos Santos
	 */

	template < typename T >
	class list
	{
		private:
			//=== the data node.
			struct Node
			{
				T data; // Tipo de informação a ser armazenada no container.
				Node* next;
				Node* prev;

				Node( const T& d = T{}, Node* n = nullptr, Node* p = nullptr )
					: data {d}, next{n}, prev{p}
				{ /* empty */ }
			};


			//=== The iterator classes.
		public:

			class const_iterator : public std::bidirectional_iterator_tag
			{
					//=== Some aliases to help writing a clearer code.
				public:
					using value_type        = T;         //!< The type of the value stored in the list.
					using pointer           = T *;       //!< Pointer to the value.
					using reference         = T &;       //!< reference to the value.
					using const_reference   = const T &; //!< const reference to the value.
					using difference_type   = std::ptrdiff_t;
					using iterator_category = std::bidirectional_iterator_tag;

				private:
					Node* m_ptr;  //!< The raw pointer.

				public:
					/*!
					 * Default constructor.
					 *
					 * @param ptr Pointer to a node.
					 */
					const_iterator( Node* ptr = nullptr ) : m_ptr{ ptr } {}
					
					// Default destructor
					~const_iterator() = default;
					
					// Copy constructor.
					const_iterator( const const_iterator& ) = default;
					
					// Assign operator overload. 
					const_iterator& operator=( const const_iterator& ) = default;
				
					// Dereference operator.
					reference operator*() { return m_ptr->data; }
					
					// Const dereference operator.
					const_reference operator*() const { return m_ptr->data; }
					
					// Increment prefix operator.
					const_iterator operator++() { m_ptr = m_ptr->next; return *this; }
				
					// Increment postfix operator.
					const_iterator operator++( int ) { auto cpy = *this; m_ptr = m_ptr->next; return cpy; } // return the copy and increment by 1
				
					// Decrement prefix operator.
					const_iterator operator--() { m_ptr = m_ptr->prev; return *this; }
					
					// Decrement postfix operator.
					const_iterator operator--( int ) { auto cpy = *this; m_ptr = m_ptr->prev; return cpy; }
					
					// Equality operator.
					bool operator==( const const_iterator& rhs ) const { return m_ptr == rhs.m_ptr; }
					
					// Inequality operator.
					bool operator!=( const const_iterator& rhs ) const { return m_ptr != rhs.m_ptr; }

					// We need friendship so the list<T> class may access the m_ptr field.
					friend class list<T>;

					friend std::ostream& operator<< ( std::ostream& os_, const const_iterator& s_ )
					{
						os_ << "[@" << s_.m_ptr << ", val = " << s_.m_ptr->data << "]";
						return os_;
					}
			};


			class iterator : public std::bidirectional_iterator_tag
			{
					//=== Some aliases to help writing a clearer code.
				public:
					using value_type        = T; //!< The type of the value stored in the list.
					using pointer           = T *; //!< Pointer to the value.
					using reference         = T &; //!< reference to the value.
					using const_reference   = const T &; //!< const reference to the value.
					using difference_type   = std::ptrdiff_t;
					using iterator_category = std::bidirectional_iterator_tag;

				private:
					Node* m_ptr;  //!< The raw pointer.

				public:

					// Default constructor.
					iterator( Node* ptr = nullptr ) : m_ptr{ ptr } { }
					
					// Default destructor.
					~iterator() = default;
					
					// Copy constructor.
					iterator( const iterator& ) = default;
					
					// Assign operator overload.
					iterator& operator=( const iterator& ) = default;
					
					// Dereference operator.
					reference  operator*() { return m_ptr->data; }
					
					// Const dereference operator.
					const_reference  operator*() const { return m_ptr->data; }
					
					// Increment prefix operator. 
					iterator operator++() { m_ptr = m_ptr->next; return *this; }
					
					// Increment postfix operator.
					iterator operator++( int ) { auto cpy = *this; m_ptr = m_ptr->next; return cpy; }
					
					// Decrement prefix operator.
					iterator operator--() { m_ptr = m_ptr->prev; return *this; }
					
					// Decrement postfix operator.
					iterator operator--( int ) { auto cpy = *this; m_ptr = m_ptr->prev; return cpy; }
					
					// Equality operator.
					bool operator==( const iterator& rhs ) const { return m_ptr == rhs.m_ptr; }
					
					// Inequality operator.
					bool operator!=( const iterator& rhs ) const { return m_ptr != rhs.m_ptr; }

					// We need friendship so the list<T> class may access the m_ptr field.
					friend class list<T>;

					friend std::ostream& operator<< ( std::ostream& os_, const iterator& s_ )
					{
						os_ << "[@" << s_.m_ptr << ", val = " << s_.m_ptr->data << "]";
						return os_;
					}
			};


			//=== Private members.
		private:
			size_t m_len;		//!< List length.
			Node* m_head;		//!< Head node.
			Node* m_tail;		//!< Tail node.

		public:
			//=== Public interface

			//=== [I] Special members
			
			// Default constructor.
			list()
				: m_len{ 0 },
				  m_head{ new Node },
			m_tail{ new Node{ T{}, nullptr, m_head } }
			{
				m_head->next = m_tail;
			}

			// List constructor.
			/*!
			 * Constructs the list with count default-inserted instances of T.
			 *
			 * @param count Number of values inside the list.
			 */
			explicit list( size_t count )
				: m_len{ 0 },
				  m_head{ new Node },
			m_tail{ new Node{ T{}, nullptr, m_head } }
			{
				m_head->next = m_tail;

				for ( int idx = 0; idx < count; ++idx )
					push_back( T{} );
			}


			// List constructor.
			/*!
			 * Constructs the list with contents of the range [first, last).
			 *
			 * @tparam InputIt The type of iterator for the range.
			 * @param first Pointer to the first element of the range.
			 * @param last Pointer to the position after the last element of the range.
			 */
			template< typename InputIt >
			list( InputIt first, InputIt last )
				: m_len{ 0 },
				  m_head{ new Node },
			m_tail{ new Node{ T{}, nullptr, m_head } }
			{
				m_head->next = m_tail;

				while ( first != last )
					push_back( *first++ );
			}

			// Copy constructor.
			/*!
			 * Constructs a new list with the content of other.
			 *
			 * @param clone_ List to be copied.
			 */	
			list( const list& clone_ )
				: m_len{ 0 },
				  m_head{ new Node },
			m_tail{ new Node{ T{}, nullptr, m_head } }
			{
				auto first = clone_.cbegin();

				while ( first != clone_.cend() )
				{
					push_back( *first++ );
				}
			}

			// List constructor.
			/*!
			 * Constructs the list with the contents of the initializer list ilist_.
			 *
			 * @param ilist_ Initializer list to be copied.
			 */
			list( std::initializer_list<T> ilist_ )
				: m_len{ 0 },
				  m_head{ new Node },
			m_tail{ new Node{ T{}, nullptr, m_head } }
			{
				m_head->next = m_tail;

				for ( auto i : ilist_ )
					push_back( i );
			}

			// List destructor.
			/*! 
			 * Deallocate the memory used by the list.
			 */
			~list() { clear(); delete m_head; delete m_tail; }
			
			// Copy assignment operator.
			/*!
			 * Replace the contents of the list with a copy of the contents of other.
			 *
			 * @param rhs Const reference to the lis to be copied.
			 */
			list& operator=( const list& rhs )
			{
				clear();

				auto first = rhs.cbegin();

				while ( first != rhs.cend() )
					push_back( *first++ );

				return *this;
			}

			// Assignment operator overload.
			/*!
			 * Replaces the content with those identified by initializer list ilist_.
			 *
			 * @param ilist_ Initializer list with content to be copied.
			 */
			list& operator=( std::initializer_list<T> ilist_ )
			{
				clear();

				for ( auto i : ilist_ )
					push_back( i );

				return *this;
			}

			//=== [II] ITERATORS
			
			// Returns an iterator to the first item in the list.
			iterator begin() { return iterator{ m_head->next }; }
			
			// Returns a constant iterator to the first item in the list.
			const_iterator cbegin() const  { return const_iterator{ m_head->next }; }

			// Returns an iterator to the end mark in the list, i.e. the position just after the last element of the list.
			iterator end() { return iterator{ m_tail }; }

			// Returns a const iterator to the end mark in the list, i.e. the position just after the last element of the list.
			const_iterator cend() const  { return const_iterator{ m_tail }; }

			//=== [III] Capacity/Status
			
			// Returns True if the container contains no elements, and False otherwise.
			bool empty ( void ) const { return !m_len; }

			// Returns the number of elements in the container.
			size_t size( void ) const { return m_len; }

			//=== [IV] Modifiers
			
			// Remove all elements from the container, releasing all associated memory.
			void clear()
			{
				while ( m_tail->prev != m_head )
					pop_back();
			}

			// Returns the object at the beginning of the list.
			T front( void ) { return m_head->next->data; }

			// Returns a const to the object at the beginnig of the list.
			T front( void ) const  { return m_head->next->data; }

			// Returns the object at the end of the list.
			T back( void ) { return m_tail->prev->data; }

			// Returns a const to the object at the end of the list.
			T back( void ) const  { return m_tail->prev->data; }

			// Adds value to the front of the list.
			/*!
			 * Adds the element in position immediately after the main node.
			 *
			 * @param value_ Const reference for the value to be added.
			 */
			void push_front( const T& value_ )
			{
				insert( begin(), value_ );
			}

			// Adds value to the end of the list.
			/*!
			 * Adds the element in position immediately before the tail node.
			 *
			 * @param value_ Const reference for the value to be added.
			 */
			void push_back( const T& value_ )
			{
				insert( end(), value_ );
			}

			// Removes the object at the front of the list.
			void pop_front( )
			{
				if ( empty() )
					return;

				Node* first = m_head->next;

				m_head->next = first->next;
				first->next->prev = m_head;

				--m_len;
				delete first;
			}

			// Removes the object at the end of the list.
			void pop_back( )
			{
				if ( empty() )
					return;

				Node* last = m_tail->prev; // copy to avoid loss

				m_tail->prev = last->prev; // link tail with the last but one
				last->prev->next = m_tail; // link last but one with tail

				--m_len;
				delete last;
			}

			//=== [IV-a] MODIFIERS W/ ITERATORS
			
			// 
			/*!
			 * Replaces the contents of the list with copies of the elements in the range [first; last).
			 *
			 * @tparam InItr Iterator type for the iterator of the range.
			 * @param first Pointer to the first element of the range.
			 * @param last Pointer to the position after the last element of the range.
			 */
			template < class InItr >
			void assign( InItr first_, InItr last_ )
			{
				*this = list( first_, last_ );
			}

			//
			/*!
			 * Replaces the contents of the list with the elements from the initializer list ilist.
			 *
			 * @param ilist_ Initializer list to be assigned on the list.
			 */
			void assign( std::initializer_list<T> ilist_ )
			{
				*this = ilist_;
			}

			/*!
			 * Inserts a new value in the list before the iterator 'it'
			 * and returns an iterator to the new node.
			 *
			 * \param pos_ An iterator to the position before which we want to insert the new data.
			 * \param value_ The value we want to insert in the list.
			 * \return An iterator to the new element in the list.
			 */
			iterator insert( iterator pos_, const T& value_ )
			{
				m_len++;
				Node* nptr = new Node{ value_, pos_.m_ptr, pos_.m_ptr->prev };
				pos_.m_ptr->prev->next = nptr;
				pos_.m_ptr->prev = nptr;

				return iterator{ nptr };
			}

			/*!
             * Inserts elements from the range [first; last) before pos_
			 * and returns an iterator to the last inserted node.
             * 
			 * @tparam InItr Iterator type to the range iterator.
             * @param pos_ An iterator to the position before which we want to insert the new data.
             * @param first Pointer to the first element of the range.
             * @param last Pointer to the position after the last element of the range.
			 * @return An iterator to the last element inserted in the list.
             */
			template < typename InItr >
			iterator insert( iterator pos_, InItr first_, InItr last_ )
			{
				iterator it{};

				while ( first_ != last_ )
					it = insert( pos_, *first_++ );

				return it;
			}

			/*!
             * Inserts elements from the initializer list ilist before pos_
             * and returns an iterator to the last inserted node.
             *
             * \param pos_ An iterator to the position before which we want to insert the new data.
             * \param ilist_ The initializer list wich contents copied.
             * \return An iterator to the last element inserted in the list.
             */
			iterator insert( iterator pos_, std::initializer_list<T> ilist_ )
			{
				iterator it{};

				for ( auto i : ilist_ )
					it = insert( pos_, i );

				return it;
			}

			/*!
			 *  Erases the node pointed by 'it_' and returns an iterator
			 *  to the node just past the deleted node.
			 *
			 *  \param it_ The node we wish to delete.
			 *  \return An iterator to the node following the deleted node.
			 */
			iterator erase( iterator it_ )
			{
				if ( empty() or it_ == end() or it_ == --begin() )
					return end();

				--m_len;

				it_.m_ptr->next->prev = it_.m_ptr->prev;
				it_.m_ptr->prev->next = it_.m_ptr->next;

				auto s = it_.m_ptr->next;
				delete it_.m_ptr;

				return s;
			}

		    /*!
			 * Erases the nodes pointed inside the range and returns an iterator
			 * to the node just past the deleted node.
			 *
			 * @param start Pointer to the first element of the range.
             * @param end Pointer to the position after the last element of the range. 
			 * @return An iterator to the node following the deleted node.
			 */
			iterator erase( iterator start, iterator end )
			{
				if ( not std::distance( start, end ) )
					return end;

				iterator it{};

				while ( start != end )
					it = erase( start++ );

				return it;
			}

			// Returns a const iterator to the value_.
			const_iterator find( const T& value_ ) const
			{
				return std::find( cbegin(), cend(), value_ );
			}

			// Returns an iterator to the value_.
			iterator find( const T& value_ )
			{
				return std::find( begin(), end(), value_ );
			}

			//=== [V] UTILITY METHODS
			// Merges two lists into one.
			/*!
			 * Moves all nodes from other to the list and at the end the other list is empty.
			 *
			 * @param other Reference to list to be merged.
			 */
			void merge( list& other ) 
			{ 
				if ( *this == other or other.size() == 0 )
					return;
				
				Node *h = other.m_head->next;

				while ( h != other.m_tail )
				{
					++m_len;
					--other.m_len;
					
					Node *k = m_head->next;
					Node *next = h->next;
					
					bool end = false;
					while ( k != nullptr )
					{
						if ( k == m_tail or h->data < k->data )
						{
							k->prev->next = h;
							h->prev = k->prev;
							h->next = k;
							k->prev = h;
							break;
						}

						k = k->next;
					}

					h = next;
				}
				

				other.m_head->next = other.m_tail;
				other.m_tail->prev = other.m_head;
			}

			// Transfers all elements from other into *this.
			/*!
			 * Moves all nodes from other to the pos position in the list, other becomes empty at the end.
			 *
			 * @param pos Const iterator to the position after the insertion.
			 * @param other Reference to other list.
			 */
			void splice( const_iterator pos, list& other ) 
			{
				if ( *this == other or other.size() == 0 or pos.m_ptr == m_head )
					return;

				Node *h = other.m_head->next;
				Node *tail = pos.m_ptr;
				while ( h != other.m_tail )
				{
					++m_len;
					--other.m_len;

					tail->prev->next = h;
					h->prev = tail->prev;
					tail->prev = h;

					Node *next = h->next;

					h->next = tail;

					h = next;
				}

				other.m_head->next = other.m_tail;
				other.m_tail->prev = other.m_head;
			}
	
			// Reverses the order of the elements in the container.
			void reverse( void ) 
			{
				auto curr = m_head;
				while ( curr != nullptr )
				{
					std::swap( curr->next, curr->prev );
					curr = curr->prev;
				}
					
				std::swap( m_head, m_tail );
			}

			// Removes all consecutive duplicate elements from the container.
			void unique( void ) 
			{
				if ( empty() or m_len == 1 )
					return;

				auto curr = begin();
				auto next = ++begin();

				while ( next != end() )
				{
					if ( *curr == *next )
						curr = erase( curr );
					else
						++curr;
					++next;
				}
			}

			// Sorts the elements in the container in ascending order, using merge sort implementation, to be stable.
			void sort( void ) 
			{	
				if ( m_len <= 1 ) return;

				// maintain old values
				auto last_{ m_tail->prev };
				auto size_{ m_len };

				auto mid {	m_len / 2 };
				auto it  { std::next( begin(), mid ) };

				// changing logical end of list
				it.m_ptr->prev->next = m_tail;
				m_tail->prev		 = it.m_ptr->prev;
				m_len				 = mid;

				// move to auxiliary list, splitting in halves
				list l_aux_lf{  }; // left range
				list l_aux_rg{  }; // right range

				// first half 
				l_aux_lf.splice( l_aux_lf.cbegin(), *this );

				// changing logical begin of list
				m_head->next   = it.m_ptr;
				it.m_ptr->prev = m_head;

				// changing logical end back to actual end so we can split in secold half
				m_tail->prev = last_;
				m_len        = size_ - mid;

				// second half
				l_aux_rg.splice( l_aux_rg.cbegin(), *this );

				// recursive calls
				l_aux_lf.sort();
				l_aux_rg.sort();

				// merging steps
				l_aux_lf.merge(l_aux_rg);

				// moves sorted values back to original list
				splice(cbegin(), l_aux_lf);
			}
	};

	//=== [VI] OPERATORS

	// Compares two lists.
	/*!
	 * Checks if the contents of lhs and rhs are equal.
	 *
	 * @tparam List type.
	 * @param l1_ Const reference to a list.
	 * @param l2_ Const reference to the other list.
	 *
	 * @return True if they are the same, False if not.
	 */
	template < typename T >
	inline bool operator==( const sc::list<T>& l1_, const sc::list<T>& l2_ )
	{
		if ( l1_.size() != l2_.size() )
			return false;

		auto it1{ l1_.cbegin() }, it2{ l2_.cbegin() };

		while ( it1 != l1_.cend() )
			if ( not ( *it1++ == *it2++ ) )
				return false;

		return true;
	}

	// Compare inequality between two lists.
	/*!
	 * Checks if the contents of lhs and rhs are different.
	 *
	 * @tparam List type.
     * @param l1_ Const reference to a list.
     * @param l2_ Const reference to the other list.
	 *
	 * @return True if they are different, False if they aren't.
	 */
	template < typename T >
	inline bool operator!=( const sc::list<T>& l1_, const sc::list<T>& l2_ )
	{
		if ( l1_.size() != l2_.size() )
			return true;

		auto it1{ l1_.cbegin() }, it2{ l2_.cbegin() };

		while ( it1 != l1_.cend() )
			if ( *it1++ != *it2++ )
				return true;

		return false;
	}
}
#endif
