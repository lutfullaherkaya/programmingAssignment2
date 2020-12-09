#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE

#include <functional>
#include <cstddef>
#include <ostream>
#include <list>
#include <vector>
#include <stack>
#include <queue>
#include <cmath>
#include <utility>

#include <iostream>   // you may use it for debugging your code


class DefaultBalanceCondition    // default BST, do not change
{
  public:
    bool operator() (int current_height, int ideal_height) const
    {
      return true;
    }
};


template <typename Key, typename Object,
          typename BalanceCondition=DefaultBalanceCondition,
	  typename Comparator=std::less<Key> >
class BinarySearchTree
{
  public:  /* DO NOT CHANGE */
    struct Node   // core structure of BinarySearchTree
    {
       Key key;         // unique key
       Object data;     // data to be stored, characterized by key
       Node * left;     // pointer to left subtree
       Node * right;    // pointer to right subtree
       size_t height;   // height of the node
       size_t subsize;  // size of the subtree node roots including itself

       Node(const Key &, const Object &, 
            Node *, Node *, size_t =0, size_t =1);   // Node constructor
    };

  public:  /* DO NOT CHANGE PROTOTYPES */
    BinarySearchTree();  // zero-parameter constructor
    BinarySearchTree(const std::list<std::pair<Key, Object> > &); // list is always sorted!
    ~BinarySearchTree();  // destructor

  public:  /* DO NOT CHANGE PROTOTYPES */
    void insert(const Key &, const Object &);  // insert new Key-Object
    void remove(const Key &);  // remove Node characterized by Key
    void toCompleteBST();  // convert into a complete BST

  public:  /* DO NOT CHANGE PROTOTYPES */
    Node * find(const Key &) const; // single item
    std::list<Node *> find(const Key &, const Key &) const; // range queries
    int height() const;  // return the height of the tree
    size_t size() const; // return the number of items in the tree
    bool empty() const;  //return whether the tree is empty or not
    Node * getRoot() const; // return a pointer to the root of the tree
    void print(std::ostream &) const;  // print tree structure into an output stream

  private:  /* DO NOT CHANGE DATA TYPES AND IDENTIFIERS */
    Node * root;                     // designated root
    size_t numNodes;                 // size
    Comparator isLessThan;           // operator upon which BST nodes are arranged
    BalanceCondition isBalanced;     // signals whether the signal is balanced
  
  private:  /* DO NOT CHANGE PROTOTYPES */
    Node * find(const Key &, Node *) const;
    int height(Node *) const;
    int subsize(Node *) const;
    void print(Node *, std::ostream &) const;

    // Define your const private utility functions below this line

  private:
    void makeEmpty(Node * &);       // utility for destructor
    
    // Define your private utility functions below this line
    void printSideways(Node * kok, std::string str = "");
    void completeTreeYap(Node *& kok, int i, const int & dugumSayisi, const Key & varsayilanKey, const Object & varsayilanData);
    void completeTreeDegerYaz(Node *kok, typename std::list<std::pair<Key,Object>>::const_iterator & listeIt);
    void completeTreeHeightSubsizeYaz(Node *kok);

    void dugumleriDiziyeEkleInorder(Node * kok, Node **& diziPtr);
    void agacDugumleriniDiziDugumleriyleDegistir(Node *&kok, Node **& diziPtr);


    //silinecek
    Node* BSTConstructorUtility(int n, typename std::list<std::pair<Key,Object>>::const_iterator & listeIt);

  private: /* DO NOT CHANGE PROTOTYPES: compiler defaults are blocked */  
    BinarySearchTree(const BinarySearchTree &);
    const BinarySearchTree & operator=(const BinarySearchTree &);

  private:  // static utility functions
    template <typename T> //static utility function
    static const T & max(const T &, const T &);

    // Define more below this line if needed

};

#endif


// DO NOT CHANGE
template <typename K, typename O, typename B, typename C>
BinarySearchTree<K,O,B,C>::Node::
Node(const K & _k, const O & _d, Node * _l, Node * _r, size_t _h, size_t _s)
  : key(_k), data(_d), left(_l), right(_r), height(_h), subsize(_s)
{
}


// DO NOT CHANGE
template <typename K, typename O, typename B, typename C>
BinarySearchTree<K,O,B,C>::BinarySearchTree()
  : root(NULL), numNodes(0)  //comparator(C() ??)
{
}


// IMPLEMENT
template <typename K, typename O, typename B, typename C>
BinarySearchTree<K,O,B,C>::BinarySearchTree(const std::list<std::pair<K,O> > & datalist)
   : root(NULL), numNodes(0)  // change it as you'd like
{
    int dugumSayisi = datalist.size();
    typename std::list<std::pair<K,O>>::const_iterator it = datalist.begin();

    completeTreeYap(root, 0, dugumSayisi, (*it).first, (*it).second);
    completeTreeDegerYaz(root, it);
    completeTreeHeightSubsizeYaz(root);
}


// IMPLEMENT
template <typename K, typename O, typename B, typename C>
void
BinarySearchTree<K,O,B,C>::toCompleteBST()
{
    int dugumSayisi = root->subsize;
    Node **dugumDizisi = new Node*[dugumSayisi];
    Node **dugumDizisiPtr = dugumDizisi; 
    dugumleriDiziyeEkleInorder(root, dugumDizisiPtr); // degisecek ptr

    completeTreeYap(root, 0, dugumSayisi, dugumDizisi[0]->key, dugumDizisi[0]->data);

    dugumDizisiPtr = dugumDizisi;
    agacDugumleriniDiziDugumleriyleDegistir(root, dugumDizisiPtr);
    completeTreeHeightSubsizeYaz(root);

    delete[] dugumDizisi;
}


// IMPLEMENT
template <typename K, typename O, typename B, typename C>
void
BinarySearchTree<K,O,B,C>::insert(const K & k, const O & x)
{

}


// IMPLEMENT
template <typename K, typename O, typename B, typename C>
void
BinarySearchTree<K,O,B,C>::remove(const K & k)
{

}



// DO NOT CHANGE
template <typename K, typename O, typename B, typename C>
typename BinarySearchTree<K,O,B,C>::Node *
BinarySearchTree<K,O,B,C>::find(const K & key) const
{
  return find(key, root);
}


// DO NOT CHANGE
template <typename K, typename O, typename B, typename C>
typename BinarySearchTree<K,O,B,C>::Node *
BinarySearchTree<K,O,B,C>::find(const K & key, Node * t) const
{
  if (t == NULL)
  {
    return NULL;
  }
  else if (isLessThan(key, t->key))
  {
    return find(key, t->left);
  }
  else if (isLessThan(t->key, key))
  {
    return find(key, t->right);
  }
  else //found
  {
    return t;
  }
}


// IMPLEMENT
template <typename K, typename O, typename B, typename C>
std::list<typename BinarySearchTree<K,O,B,C>::Node *>
BinarySearchTree<K,O,B,C>::find(const K & lower, const K & upper) const
{
  std::list<Node *> ranges;

  // implement

  return ranges;
}


// DO NOT CHANGE
template <typename K, typename O, typename B, typename C>
typename BinarySearchTree<K,O,B,C>::Node *
BinarySearchTree<K,O,B,C>::getRoot() const
{
  return root;
}


// DO NOT CHANGE
template <typename K, typename O, typename B, typename C>
int
BinarySearchTree<K,O,B,C>::height() const
{
  return height(root);
}


// DO NOT CHANGE
template <typename K, typename O, typename B, typename C>
int
BinarySearchTree<K,O,B,C>::height(Node * t) const
{
  return (t == NULL) ? -1 : t->height;
}


// private utility
template <typename K, typename O, typename B, typename C>
int
BinarySearchTree<K,O,B,C>::subsize(Node * t) const
{
  return (t == NULL) ? 0 : t->subsize;
}


// DO NOT CHANGE
template <typename K, typename O, typename B, typename C>
size_t
BinarySearchTree<K,O,B,C>::size() const
{
  return numNodes;
}


// DO NOT CHANGE
template <typename K, typename O, typename B, typename C>
bool
BinarySearchTree<K,O,B,C>::empty() const
{
  return numNodes == 0;
}


// DO NOT CHANGE
template <typename K, typename O, typename B, typename C>
void
BinarySearchTree<K,O,B,C>::makeEmpty(Node * & t)
{
  if (t != NULL)
  {
    makeEmpty(t->left);
    makeEmpty(t->right);
    delete t;

    --numNodes;
  }
  
  t = NULL;
}




// DO NOT CHANGE
template <typename K, typename O, typename B, typename C>
BinarySearchTree<K,O,B,C>::~BinarySearchTree()
{
  makeEmpty(root);
}


// DO NOT CHANGE
template <typename K, typename O, typename B, typename C>
void
BinarySearchTree<K,O,B,C>::print(std::ostream & out) const
{
  print(root, out);
  out << '\n';
}


// DO NOT CHANGE
template <typename K, typename O, typename B, typename C>
void
BinarySearchTree<K,O,B,C>::print(Node * t, std::ostream & out) const
{
  if (t != NULL && t->left != NULL) 
  {
    out << '[';
    print( t->left, out );
  }
  else if (t != NULL && t->left == NULL && t->right != NULL)
  {
    out << "[";
  }

  if (t != NULL)
  {
    if (t->left == NULL && t->right == NULL)
    {
      out << '(' << (t->key) << ')';
    }
    else if (t->left != NULL || t->right != NULL)
    {
      out << '{' << (t->key) << ",H" << t->height << ",S" << t->subsize << '}';
    }
  }
  
  if (t != NULL && t->right != NULL)
  {
    print( t->right, out );
    out << ']';
  }
  else if (t != NULL && t->left != NULL && t->right == NULL)
  {
    out << "]";
  }
}


// do not change
template <typename K, typename O, typename B, typename C>
template <typename T>
const T &
BinarySearchTree<K,O,B,C>::max(const T & el1, const T & el2)
{
  return el1 > el2 ? el1 : el2;
}

// TALEBENIN EKLEDIGI UYE FONKSIYONLARI

/* student private utility.*/
template<typename Key, typename Object, typename BalanceCondition, typename Comparator>
void BinarySearchTree<Key, Object, BalanceCondition, Comparator>::
printSideways(Node * kok, std::string str) {
    if (kok) {
        printSideways(kok->right, str + "\t");
        std::cout << str << kok->data << std::endl;
        printSideways(kok->left, str + "\t");
    }
}

/* student private utility.*/
template<typename Key, typename Object, typename BalanceCondition, typename Comparator>
void BinarySearchTree<Key, Object, BalanceCondition, Comparator>::
completeTreeYap(Node *& kok, int i, const int & dugumSayisi, const Key & varsayilanKey, const Object & varsayilanData) {
    if (i < dugumSayisi) {
        kok = new Node(varsayilanKey, varsayilanData, NULL, NULL);
        completeTreeYap(kok->left,  2*i+1, dugumSayisi, varsayilanKey, varsayilanData);
        completeTreeYap(kok->right, 2*i+2, dugumSayisi, varsayilanKey, varsayilanData);
    }
}

/* student private utility.*/
template<typename Key, typename Object, typename BalanceCondition, typename Comparator>
void BinarySearchTree<Key, Object, BalanceCondition, Comparator>::
completeTreeDegerYaz(Node * kok, typename std::list<std::pair<Key,Object>>::const_iterator & listeIt) {
    if (kok) {
        completeTreeDegerYaz(kok->left, listeIt);
        kok->key = (*listeIt).first;
        kok->data = (*listeIt).second;
        ++listeIt;
        completeTreeDegerYaz(kok->right, listeIt);
    }
}

template<typename Key, typename Object, typename BalanceCondition, typename Comparator>
void BinarySearchTree<Key, Object, BalanceCondition, Comparator>::
completeTreeHeightSubsizeYaz(Node * kok) {
    if (kok) {
        completeTreeHeightSubsizeYaz(kok->left);
        completeTreeHeightSubsizeYaz(kok->right);
        kok->height = 1 + max(height(kok->right), height(kok->left));
        kok->subsize = 1 + subsize(kok->right) + subsize(kok->left);
    }
}

/* silinecek student private utility.*/
template<typename Key, typename Object, typename BalanceCondition, typename Comparator>
typename BinarySearchTree<Key, Object, BalanceCondition, Comparator>::Node* BinarySearchTree<Key, Object, BalanceCondition, Comparator>::
BSTConstructorUtility(int n, typename std::list<std::pair<Key,Object>>::const_iterator & listeIt) {
    if (n <= 0) {
        return NULL;
    } else {
        Node* sol = BSTConstructorUtility(n/2, listeIt);

        Node* root = new Node((*listeIt).first, (*listeIt).second, sol, NULL);
        ++listeIt;

        root->right = BSTConstructorUtility(n - n/2 - 1, listeIt);

        return root;
    }
}

/* student private utility.*/
template<typename Key, typename Object, typename BalanceCondition, typename Comparator>
void BinarySearchTree<Key, Object, BalanceCondition, Comparator>::
dugumleriDiziyeEkleInorder(Node * kok, Node **& diziPtr) {
    if (kok) {
        dugumleriDiziyeEkleInorder(kok->left, diziPtr);
        *diziPtr++ = kok;
        dugumleriDiziyeEkleInorder(kok->right, diziPtr);
    }
}

/* student private utility.*/
template<typename Key, typename Object, typename BalanceCondition, typename Comparator>
void BinarySearchTree<Key, Object, BalanceCondition, Comparator>::
agacDugumleriniDiziDugumleriyleDegistir(Node *& kok, Node **& diziPtr) {
    if (kok) {
        agacDugumleriniDiziDugumleriyleDegistir(kok->left, diziPtr);

        Node *eskiDugum = kok;
        kok = *diziPtr++;
        kok->left = eskiDugum->left;
        kok->right = eskiDugum->right;
        kok->height = 0;
        kok->subsize = 1;
        delete eskiDugum;

        agacDugumleriniDiziDugumleriyleDegistir(kok->right, diziPtr);
    }
}