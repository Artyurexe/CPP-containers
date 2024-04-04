// #ifndef S21_TREE_H
// #define S21_TREE_H

// #include <utility>
// #include <limits>
// #include <iostream>

// using std::pair;
// using std::cout;

// template <typename Key> class rbtree {
//     friend class iterator;
// public:
//     using value_type = Key;
//     using reference = value_type &;
//     using const_reference = const value_type &;
//     using size_type = size_t;

// private:
//     template <typename Type> class node {

//     public:
//         value_type data;
//         node* left_child;
//         node* right_child;
//         node* parent;
//         bool is_red;
//         node(): left_child(nullptr), right_child(nullptr), parent(nullptr),
//         data(value_type()), is_red(true) {}; node(value_type data):
//         data(data), left_child(nullptr), right_child(nullptr),
//         parent(nullptr), is_red(true) {}; ~node() {};
//     };

//     size_type tree_size;
//     node<Key>* root;
//     node<Key>* new_node;
//     node<Key>* current_node;
//     node<Key>* highest_node;
//     node<Key>* end_node;

// public:
//     class const_iterator {};

//     // iterator finished but I'm not 100% sure if it works
//     template <typename Node> class s21_iterator {
//         rbtree& parent;
//     public:
//         using iterator_category = std::bidirectional_iterator_tag;
//         using difference_type = std::ptrdiff_t;
//         using pointer = node<Key>*;

//         s21_iterator(rbtree& pr): parent(pr), m_ptr(nullptr) {}
//         s21_iterator(pointer ptr, rbtree& pr): parent(pr), m_ptr(ptr) {}

//         reference operator*() const { return m_ptr->data; }
//         s21_iterator& operator++() {
//             if (m_ptr == parent.highest_node) m_ptr = parent.end_node;
//             else m_ptr = parent.find_successor(m_ptr);
//             return *this;
//         }  // ++it
//         s21_iterator operator++(value_type) { iterator tmp = *this;
//         ++(*this); return tmp; } // it++ s21_iterator& operator--() { m_ptr =
//         parent.find_predeccessor(m_ptr); return *this; }  // --it
//         s21_iterator operator--(value_type) { iterator tmp = *this;
//         --(*this); return tmp; } // it-- friend bool operator==(const
//         s21_iterator& a, const s21_iterator& b) { return a.m_ptr->data ==
//         b.m_ptr->data; };
//         // I wonder if a.m_ptr->data - b.m_ptr->data == EPS would be better
//         friend bool operator!=(const s21_iterator& a, const s21_iterator& b)
//         { return a.m_ptr->data != b.m_ptr->data; };
//     private:
//         pointer m_ptr;
//     };

//     using iterator = s21_iterator<node<Key>>;
//     iterator iter;

//     void printtree() {
//         for (auto it = this->begin(); it != this->end(); it++) {
//             cout << *it;
//         }
//     };

//     rbtree(): tree_size(0), root(nullptr), new_node(nullptr),
//     current_node(nullptr), highest_node(nullptr), iter(*this) { end_node =
//     new node<Key>(0); }; rbtree(std::initializer_list<value_type> const
//     &items) {
//         end_node = new node<Key>(0);
//         for (const auto& item : items)
//             insert(item);
//     };
//     rbtree(const rbtree &&s): root(s.root), new_node(nullptr),
//     current_node(nullptr), tree_size(s.tree_size),
//     highest_node(s.highest_node), end_node(s.end_node), iter(*this) {
//         s.root = nullptr;
//         s.tree_size = 0;
//         s.new_node = nullptr;
//         s.current_node = nullptr;
//         s.highest_node = nullptr;
//         s.end_node = nullptr;
//     };
//     ~rbtree() {
//         while (root) delete_node(root->data);
//         delete end_node;
//     };

//     iterator begin() { return iterator(smallest_child(root), *this); }
//     iterator end() { return iterator(end_node, *this); }

//     bool empty() { return !tree_size; };
//     size_type size() { return tree_size; };
//     size_type max_size() { return std::numeric_limits<size_t>::max() /
//     sizeof(node<Key>); };

//     void unique_insert(value_type data) {
//         new_node = new rbtree::node<Key>(data);
//         if ((highest_node && new_node->data > highest_node->data) ||
//         !highest_node)
//             highest_node = new_node;
//         tree_size++;
//         create_root_if_needed();
//         current_node = root;
//         while (new_node) {
//             if (!current_node->is_red && current_node->left_child &&
//             current_node->right_child && current_node->left_child->is_red &&
//             current_node->right_child->is_red) {
//                 if (current_node != root) current_node->is_red = true;
//                 current_node->left_child->is_red = false;
//                 current_node->right_child->is_red = false;
//                 fix_double_red();
//             }
//             unique_BST_traverse();
//         };
//         fix_double_red();
//         current_node = nullptr;
//     };
//     void insert(value_type data) {
//         new_node = new rbtree::node<Key>(data);
//         if ((highest_node && new_node->data > highest_node->data) ||
//         !highest_node)
//             highest_node = new_node;
//         tree_size++;
//         create_root_if_needed();
//         current_node = root;
//         while (new_node) {
//             if (!current_node->is_red && current_node->left_child &&
//             current_node->right_child && current_node->left_child->is_red &&
//             current_node->right_child->is_red) {
//                 if (current_node != root) current_node->is_red = true;
//                 current_node->left_child->is_red = false;
//                 current_node->right_child->is_red = false;
//                 fix_double_red();
//             }
//             BST_traverse();
//         };
//         fix_double_red();
//         current_node = nullptr;
//     };

//     // I'm not sure, but deletion will work for unique tree too
//     void delete_node(value_type data) {
//         current_node = root;
//         find(data);
//         if (current_node) {
//             tree_size--;
//             if (current_node->left_child && current_node->right_child) {
//                 node<Key>* successor = find_predeccessor(current_node);
//                 current_node->data = successor->data;
//                 current_node = successor;
//             }
//             successor_replacement();
//             if (current_node->is_red || (current_node->left_child &&
//             current_node->left_child->is_red)) {
//                 grandchild_adoption(current_node->left_child);
//             } else if (current_node->is_red || (current_node->right_child &&
//             current_node->right_child->is_red)) {
//                 grandchild_adoption(current_node->right_child);
//             } else {
//                 if (current_node->left_child)
//                     grandchild_adoption(current_node->left_child);
//                 else if (current_node->right_child)
//                     grandchild_adoption(current_node->right_child);
//                 else grandchild_adoption(nullptr);
//             }
//             if ((current_node->left_child &&
//             !current_node->left_child->is_red) || (current_node->right_child
//             && !current_node->right_child->is_red) ||
//             (!current_node->right_child && !current_node->left_child)) {
//                 double_black_removal(current_node);
//             }
//             if (current_node->left_child)
//                 current_node->left_child->is_red = false;
//             else if (current_node->right_child)
//                 current_node->right_child->is_red = false;
//             delete current_node;
//             current_node = nullptr;
//             highest_node = biggest_child(root);
//         }
//     };

// private:
//     void double_black_removal(node<Key>* double_black) {
//         if (root != double_black && !current_node->is_red) {
//             node<Key>* grandparent = double_black->parent;
//             if (grandparent->left_child == nullptr) {
//                 fix_double_black(true, grandparent);
//             } else if (grandparent->right_child == nullptr) {
//                 fix_double_black(false, grandparent);
//             }
//         }
//     };

//     void fix_double_black(bool is_right, node<Key>* grandparent) {
//         node<Key>* uncle = is_right ? grandparent->right_child :
//         grandparent->left_child; switch (sibling_check(uncle)) {
//             case 1:
//                 AVL_rotation(uncle);
//                 grandparent->parent->is_red = false;
//                 if (uncle)
//                     uncle->is_red = true;
//                 break;
//             case 2:
//                 uncle->is_red = true;
//                 double_black_removal(grandparent);
//                 break;
//             case 3:
//                 if (is_right) {
//                     if (uncle->left_child && uncle->left_child->is_red &&
//                     !(uncle->right_child)) {
//                         uncle->left_child->is_red = false;
//                         AVL_rotation(uncle->left_child);
//                         AVL_rotation(uncle);
//                     } else {
//                         uncle->right_child->is_red = false;
//                         //AVL_rotation(uncle); not sure if this should be
//                         commented
//                     }
//                 } else if (uncle->right_child &&uncle->right_child->is_red &&
//                 !(uncle->left_child)) {
//                     uncle->right_child->is_red = false;
//                     AVL_rotation(uncle->right_child);
//                     AVL_rotation(uncle);
//                 } else {
//                     if (uncle->left_child)
//                         uncle->left_child->is_red = false;
//                     //AVL_rotation(uncle); not sure if this should be
//                     commented
//                 }
//                 break;
//             default:
//                 break;
//         }
//     }

//     int sibling_check(node<Key>* sibling) {
//         if (sibling->is_red) {
//             return 1;
//         } else if (sibling->left_child && !sibling->left_child->is_red &&
//         sibling->right_child && !sibling->right_child->is_red) {
//             return 2;
//         } else return 3;
//     };

//     void create_root_if_needed() {
//         if (root == nullptr) {
//             new_node->is_red = false;
//             root = new_node;
//             new_node = nullptr;
//         }
//     };

//     void unique_BST_traverse() {
//         if (new_node->data < current_node->data) {
//             if (!(current_node->left_child)) {
//                 current_node->left_child = new_node;
//                 new_node->parent = current_node;
//                 current_node = new_node;
//                 new_node = nullptr;
//             } else current_node = current_node->left_child;
//         } else if (new_node->data > current_node->data) {
//             if (!(current_node->right_child)) {
//                 current_node->right_child = new_node;
//                 new_node->parent = current_node;
//                 current_node = new_node;
//                 new_node = nullptr;
//             } else current_node = current_node->right_child;
//         } else {
//             delete new_node ;
//             new_node = nullptr;
//         }
//     };
//     void BST_traverse() {
//         if (new_node->data < current_node->data) {
//             if (!(current_node->left_child)) {
//                 current_node->left_child = new_node;
//                 new_node->parent = current_node;
//                 current_node = new_node;
//                 new_node = nullptr;
//             } else current_node = current_node->left_child;
//         } else if (new_node->data >= current_node->data) {
//             if (!(current_node->right_child)) {
//                 current_node->right_child = new_node;
//                 new_node->parent = current_node;
//                 current_node = new_node;
//                 new_node = nullptr;
//             } else current_node = current_node->right_child;
//         } else {
//             delete new_node;
//             new_node = nullptr;
//         }
//     };

//     void find(value_type data) {
//         while (current_node && current_node->data != data) {
//             if (data < current_node->data)
//                 current_node = current_node->left_child;
//             else current_node = current_node->right_child;
//         }
//     };

//     void successor_replacement() {
//         if (current_node->left_child && current_node->right_child) {
//             node<Key>* successor = smallest_child(current_node->right_child);
//             current_node->data = successor->data;
//             current_node = successor;
//         }
//     };

//     void grandchild_adoption(node<Key>* grandchild) {
//         if (grandchild) {
//             grandchild->parent = current_node->parent;
//             //grandchild->is_red = false;
//         }
//         if (current_node == root) root = grandchild;
//         else if (current_node->parent->right_child == current_node)
//             current_node->parent->right_child = grandchild;
//         else current_node->parent->left_child = grandchild;
//     };

//     void fix_double_red() {
//         if (current_node != root && current_node->is_red &&
//         current_node->parent->is_red) {
//             node<Key>* parent = current_node->parent;
//             node<Key>* grandparent = parent->parent;
//             grandparent->is_red = true; //probably need to remove this
//             if ((parent->left_child == current_node &&
//             grandparent->left_child == parent) || (parent->right_child ==
//             current_node && grandparent->right_child == parent)) {
//                 parent->is_red = false;
//                 AVL_rotation(parent);
//             } else {
//                 current_node->is_red = false;
//                 AVL_rotation(current_node);
//                 AVL_rotation(current_node);
//             }
//         }
//     };

//     void AVL_rotation(node<Key>* ascending_node) {
//         if (ascending_node->parent == root) root = ascending_node;
//         if (ascending_node->parent->right_child == ascending_node) {
//             ascending_node->parent->right_child = ascending_node->left_child;
//             ascending_node->left_child = ascending_node->parent;
//             ascending_node->parent = ascending_node->left_child->parent;
//             if (ascending_node->left_child->parent->left_child ==
//             ascending_node->left_child)
//                 ascending_node->left_child->parent->left_child =
//                 ascending_node;
//             else ascending_node->left_child->parent->right_child =
//             ascending_node; ascending_node->left_child->parent =
//             ascending_node;
//         } else {
//             ascending_node->parent->left_child = ascending_node->right_child;
//             ascending_node->right_child = ascending_node->parent;
//             ascending_node->parent = ascending_node->right_child->parent;
//             if (ascending_node->right_child->parent->right_child ==
//             ascending_node->right_child)
//                 ascending_node->right_child->parent->right_child =
//                 ascending_node;
//             else ascending_node->right_child->parent->left_child =
//             ascending_node; ascending_node->right_child->parent =
//             ascending_node;
//         }
//     };

//     node<Key>* find_successor(node<Key>* current) {
//         if (iterator(current, *this) == this->end()) return current;
//         node<Key>* successor = current;
//         if (current->right_child != NULL) {
//             successor = smallest_child(successor->right_child);
//         } else {
//             while (successor->parent && successor->parent->right_child ==
//             successor)
//                 successor = successor->parent;
//             successor = successor->parent;
//         }
//         return successor;
//     };

//     node<Key>* find_predeccessor(node<Key>* current) {
//         if (iterator(current, *this) == this->begin()) return current;
//         node<Key>* predeccessor = current;
//         if (current->left_child != NULL) {
//             predeccessor = biggest_child(predeccessor->left_child);
//         } else {
//             while (predeccessor->parent && predeccessor->parent->left_child
//             == predeccessor)
//                 predeccessor = predeccessor->parent;
//             predeccessor = predeccessor->parent;
//         }
//         return predeccessor;
//     };

//     node<Key>* smallest_child(node<Key>* current) {
//         while (current->left_child)
//             current = current->left_child;
//         return current;
//     }

//     node<Key>* biggest_child(node<Key>* current) {
//         while (current->right_child)
//             current = current->right_child;
//         return current;
//     }
// };

// #endif