#ifndef MTM4_SET_H
#define MTM4_SET_H

#include "exceptions.h"

namespace mtm{
    
    /**
     * A set
     * @tparam Type The type of an element on the group.
     *      Required to implement:
     *                             - operator ==
     *                             - copy constructor
     */
    template<typename Type>
    class MtmSet{
        /**
         * A node in the set
         */
        class Node{
        public:
            Type element;
            Node* next;

            explicit Node(Type new_element): element(new_element), next(NULL){}
            Node(const Node& node): element(node.element), next(NULL){}
            //const Type *operator->() const{
            //    return &element;
            //}
        };

        Node* head;
    
    public:
        //Forward declaration
        class const_iterator;
        
        /**
         * A iterator for Set
        */
        class iterator{
            Node* node_ptr;
        public:
            /**
             * Empty constructor. Should not be dereferenced.
             * Same as MtmSet::end()
             */
            iterator(): node_ptr(NULL){};
            
            /**
             * Constructor of Set iterator
             * @param node The node the iterator points to
             */
            explicit iterator(Node *node){
                node_ptr = node;
            }
            
            /**
             * Copy constructor
             * @param it The iterator to copy
             */
            iterator(const iterator& it) = default;

            /**
             * Destructor
             */
            ~iterator() = default;

            /**
             * Copy assignment operator.
             * @param rhs The iterator to copy.
             * @return A reference to this iterator.
             */
            iterator& operator=(const iterator& rhs) = default;
            
            /**
             * Dereference operator * .
             * Used like dereference of a pointer with * .
             * @return A reference of the data in the node the iterator
             *  points to.
             * @throws NodeIsEndException if the iterator doesn't point to
             * an element in the set (end())
             */
            const Type& operator*() const{
                if (this->node_ptr == NULL){
                    throw NodeIsEndException();
                }
                return node_ptr->element;
            }
            
            /**
             * Dereference operator -> .
             * Used like dereference of a pointer with -> .
             * @return A pointer to the data in the node the iterator
             *  points to.
             * C++ use the -> operator on the returned pointer,
             * this allows the user to treat the iterator like a pointer.
             * @throws NodeIsEndException if the iterator doesn't point to
             * an element in the set (end())
             */
            const Type *operator->() const{
                if (this->node_ptr == NULL){
                    throw NodeIsEndException();
                }
                return &(node_ptr->element);
            }
            
            /**
             * Prefix increment operator (++i)
             * @return a reference to the iterator;
             * @throws NodeIsEndException if the iterator doesn't point to
             * an element in the set (end())
             */
            iterator& operator++(){
                if (this->node_ptr == NULL){
                    throw NodeIsEndException();
                }
                this->node_ptr = node_ptr->next;
                return *this;
            }
            
            /**
             * Postfix increment operator (i++)
             * @return iterator that points to the same node as this before
             * the increment
             * @throws NodeIsEndException if the iterator doesn't point to
             * an element in the set (end())
             */
            iterator operator++(int){
                if (this->node_ptr == NULL){
                    throw NodeIsEndException();
                }
                iterator tmp(*this);
                ++(*this);
                return tmp;
            }
            
            /**
             * Compare an iterator with const_iterator. (when there is a
             *  regular iterator on the left.
             * @param rhs the right const_iterator.
             * @return true if the two iterators point to the same node
             */
            bool operator==(const const_iterator& rhs) const{
                return (rhs == *this);
            }
            
            /**
             * Compare an iterator with const_iterator. (when there is a
             *  regular iterator on the left.
             * @param rhs the right const_iterator.
             * @return true if the two iterators don't point to the same node
             */
            bool operator!=(const const_iterator& rhs) const{
                return !(*this == rhs);
            }

            friend class const_iterator;
        };
        
        /**
         * A const_iterator for Set
        */
        class const_iterator{
            Node const* node_ptr;
        public:
            /**
             * Empty constructor. Should not be dereferenced.
             * Same as MtmSet::end()
             */
            const_iterator(): node_ptr(NULL){};
            
            /**
             * Constructor of Set const_iterator
             * @param node The node the const_iterator points to
             */
            explicit const_iterator(Node *node){
                node_ptr = node;
            }
            
            /**
             * Copy constructor
             * @param it The const_iterator to copy
             */
            const_iterator(const const_iterator& it) = default;
            
            /**
             * Constructor from iterator (not const_iterator)
             * Allows casting from iterator to const_iterator
             * @param it The iterator to "copy" to a const_iterator
             */
            const_iterator(const iterator& it){
                this->node_ptr = it.node_ptr;
            }

            /**
             * Destructor
             */
            ~const_iterator() = default;

            /**
             * Copy assignment operator.
             * @param rhs The iterator to copy.
             * @return A reference to this const_iterator.
             */
            const_iterator& operator=(const const_iterator& rhs) = default;
            
            /**
             * Dereference operator * .
             * Used like dereference of a pointer with * .
             * @return A reference of the data in the node the const_iterator
             *  points to.
             * @throws NodeIsEndException if the iterator doesn't point to
             * an element in the set (end())
             */
            const Type& operator*() const{
                if (this->node_ptr == NULL){
                    throw NodeIsEndException();
                }
                return node_ptr->element;
            }
            
            /**
             * Dereference operator -> .
             * Used like dereference of a pointer with -> .
             * @return A pointer to the data in the node the const_iterator
             *  points to.
             *  C++ use the -> operator on the returned pointer,
             *  this allows the user to treat the const_iterator like a pointer.
             * @throws NodeIsEndException if the iterator doesn't point to
             * an element in the set (end())
             */
            const Type *operator->() const{
                if (this->node_ptr == NULL){
                    throw NodeIsEndException();
                }
                return &(node_ptr->element);
            }
            
            /**
             * Prefix increment operator (++i)
             * @return a reference to the iterator;
             * @throws NodeIsEndException if the iterator doesn't point to
             * an element in the set (end())
             */
            const_iterator& operator++() {
                if (this->node_ptr == NULL){
                    throw NodeIsEndException();
                }
                node_ptr = node_ptr->next;
                return *this;
            }
            
            /**
             * Postfix increment operator (i++)
             * @return const_iterator that points to the same node as this
             * before the increment
             * @throws NodeIsEndException if the iterator doesn't point to
             * an element in the set (end())
             */
            const_iterator operator++(int){
                if (this->node_ptr == NULL){
                    throw NodeIsEndException();
                }
                const_iterator tmp(*this);
                ++(*this);
                return tmp;
            }
            
            /**
             * Compare two const_iterators.
             * @param rhs the right const_iterator
             * @return true if the two const_iterators point to the same node
             */
            bool operator==(const const_iterator& rhs) const{
                return (this->node_ptr == rhs.node_ptr);
            }
            
            /**
             * Compare two const_iterators.
             * @param rhs the right const_iterator
             * @return true if the two const_iterators don't point to the same
             * node
             */
            bool operator!=(const const_iterator& rhs) const{
                return !(*this == rhs);
            }
        };
        
        /**
         * Empty constructor
         * Creates an empty set
         */
        MtmSet(): head(NULL){};
        
        /**
         * Copy constructor
         * @param set the Set to copy
         */
        MtmSet(const MtmSet& set): head(NULL){
            const_iterator source_it = set.begin();
            while(source_it != set.end()){
                this->insert(*source_it);
                source_it++;
            }
        }
        
        /**
         * Destructor
         * Free all allocated memory in the set.
         */
        ~MtmSet(){
            this->clear();
            this->head = NULL;
        }
        
        /**
         * Insert a new element to the set, doesn't insert if there is already
         *  an equal element in the set.
         * If an element was't inserted, all iterators should stay valid.
         * @param elem The element to insert to the set
         * @return An iterator to the inserted element, or to the equal
         * element if the element wasn't inserted.
         */
        iterator insert(const Type& elem){
            if (head == NULL){
                head = new Node(elem);
                return this->begin();
            }
            if (this->contains(elem)){
                return this->find(elem);
            }
            Node *insert = head;
            while (insert->next != NULL){
                insert = insert->next;
            }
            insert->next = new Node(elem);
            return iterator(insert);
        }
        
        /**
         * Remove an element from the set. If there is no element equal to
         *  elem in the set, does nothing.
         * If an element wasn't removed, all iterators should stay valid.
         * @param elem the element to remove.
         */
        void erase(const Type& elem){
            if (!this->contains(elem)) return;
            if (head->element == elem){
                Node *temp = head->next;
                delete head;
                head = temp;
                return;
            }
            Node *erase = head;
            while (erase->next != NULL){
                if (erase->next->element == elem){
                    Node *temp = erase->next->next;
                    delete erase->next;
                    erase->next = temp;
                }
            }
        }
        
        /**
         * Remove the element the iterator points to from the set.
         * Iterator to another set is undefined.
         * @param it The iterator to the element to the set.
         */
        void erase(const iterator& it){
            erase(*it);
        }
        
        /**
         * Get the amount of elements in the set.
         * @return The amount of elements in the set.
         */
        int size() const{
            int size = 0;
            for(const_iterator i = this->begin(); i != this->end(); i++){
                size++;
            }
            return size;
        }
        
        /**
         * Check if the set is empty.
         * @return true is the set is empty.
         */
        bool empty() const{
            return (head == NULL);
        }
        
        /**
         * Empty the set, free all allocated memory in the set.
         */
        void clear(){
            while(head != NULL){
                this->erase(head->element);
            }
        }
        
        /**
         * Get an iterator to the first element in the set.
         * If set is empty, return the same as end.
         * @return
         */
        iterator begin(){
            iterator beginning(head);
            return beginning;
        }
        
        /**
         * Get a const_iterator to the first element in the set.
         * If set is empty, return the same as end.
         * @return
         */
        const_iterator begin() const{
            const_iterator beginning(head);
            return beginning;
        }
        
        /**
         * Returns an iterator referring to the past-the-end element in the set.
         * The past-the-end element is the theoretical element that would follow
         * the last element in the set. It does not point to any element, and
         * thus should not be dereferenced.
         * @return Iterator to past-the-end element.
         */
        iterator end(){
            iterator i;
            return i;
        }
        
        /**
         * Returns a const_iterator referring to the past-the-end element in
         * the set.
         * The past-the-end element is the theoretical element that would follow
         * the last element in the set. It does not point to any element, and
         * thus should not be dereferenced.
         * @return const_iterator to past-the-end element.
         */
        const_iterator end() const{
            const_iterator i;
            return i;
        }
        
        /**
         * Find an element in the set.
         * @param elem The element to find
         * @return An iterator that points to the elem.
         */
        iterator find(const Type& elem){
            for(iterator i = this->begin(); i != this->end(); i++){
                if (*i == elem) return i;
            }
            return this->end();
        }
        
        /**
         * Find an element in the set.
         * @param elem The element to find
         * @return A const_iterator that points to the elem.
         */
        const_iterator find(const Type& elem) const{
            for(const_iterator i = this->begin(); i != this->end(); i++){
                if (*i == elem) return i;
            }
            return this->end();
        }
        
        /**
         * Check if an element is in the set.
         * @param elem The element to check if it's in the set.
         * @return True if the element is in the set, false otherwise.
         */
        bool contains(const Type& elem) const{
            const_iterator i = find(elem);
            return (i != this->end());
        }
        
        /**
         * Check if this set is a superset of a given set.
         * Superset: A superset of B if B is a subset of A, that mean's that
         *  A contains all the elements in B.
         * @param subset The set to check if it's a subset.
         * @return True if the given set is a subset of this set.
         */
        bool isSuperSetOf(const MtmSet& subset) const{
            const_iterator it = subset.begin();
            while(it != subset.end()){
                if (!this->contains(*it)){
                    return false;
                }
                it++;
            }
            return true;
        }
        
        /**
         * Check if two set are equal, meaning, they contain the same elements.
         * @param rhs The set right of the == operator.
         * @return true if thw two set conatain the same elements, false
         *  otherwise.
         */
        bool operator==(const MtmSet& rhs) const{
            const_iterator left = this->begin();
            const_iterator right = rhs.begin();
            while ((left != this->end()) && (right != rhs.end())){
                if (!(*left == *right)){
                    return false;
                }
                left++;
                right++;
            }
            if (left == right){
                return true;
            } else {
                return false;
            }
        }
        
        /**
         * Check if two set are equal, meaning, they contain the same elements.
         * @param rhs The set right of the != operator.
         * @return false if thw two set conatain the same elements, true
         *  otherwise.
         */
        bool operator!=(const MtmSet& rhs) const{
            return !(*this == rhs);
        }
        
        /**
         * Insert all the elements in the given set to this set (union).
         * @param set The set to insert all the elements from.
         * @return A reference to this set.
         */
        MtmSet& unite(const MtmSet& set){
            const_iterator it = set.begin();
            while(it != set.end()){
                this->insert(*it);
                it++;
            }
            return *this;
        }
        
        /**
         * Returns a new set that is an union of this set, and a given set.
         * @param set The other set (other than this) to be in the union.
         * @return The new set.
         */
        MtmSet unite(const MtmSet& set) const{
            MtmSet new_set;
            new_set.unite(*this);
            new_set.unite(set);
            return new_set;
        }
        
        /**
         * Remove all the elements from this set, that are not in the given set
         * (intersection).
         * @param set The other set in the intersection.
         * @return A reference to this set.
         */
        MtmSet& intersect(const MtmSet& set){
            iterator it = this->begin();
            while(it != this->end()){
                if (!(set.contains(*it))){
                    iterator temp(it);
                    it++;
                    this->erase(temp);
                } else {
                    it++;
                }
            }
            return *this;
        }
        
        /**
         * Returns a new set that is an intersection of this set,
         *  and a given set.
         * @param set The other set (other than this) to be in the intersection.
         * @return The new set.
         */
        MtmSet intersect(const MtmSet& set) const{
            MtmSet new_set;
            new_set.unite(*this);
            new_set.intersect(set);
            return new_set;
        }
        
        /**
         * Remove all the elements in the set, that doesn't meet a given
         *  condition.
         * @tparam func - A function of an object-function that receive 1
         *  argument, of the same type as an element in the set, and returns
         *  a bool.
         * @param condition - function (or object-function) that returns true
         * if the element is meeting the condition and false otherwise.
         * @return A reference to this set.
         */
        template<typename func>
        MtmSet& getSubSet(func condition){
            iterator it = this->begin();
            while (it != this->end()){
                if (!(condition(*it))){
                    iterator temp(it);
                    erase(temp);
                    it++;
                } else {
                    it++;
                }
            }
            return *this;
        }
        
        /**
         * Get a subset of this set, that contains all the elements in the set,
         * that doesn't meet a given condition.
         * @tparam func - A function of an object-function that receive 1
         *  argument, of the same type as an element in the set, and returns
         *  a bool.
         * @param condition - function (or object-function) that returns true
         * if the element is meeting the condition and false otherwise.
         * @return A the new set.
         */
        template<typename func>
        MtmSet getSubSet(func condition) const{
            MtmSet new_set;
            new_set.unite(*this);
            new_set.getSubSet(condition);
            return new_set;
        }
    };
} // namespace mtm

#endif //MTM4_SET_H
