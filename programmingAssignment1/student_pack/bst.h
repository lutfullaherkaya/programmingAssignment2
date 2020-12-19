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
	  void printSideways(Node *kok, std::string str = "") const;	
    void findYardimci(Node *kok, std::list<Node *> &liste, const Key &az, const Key &cok) const;	
    void dugumleriVektoreEkleInorder(Node *kok, std::vector<Node *> &vektor) const;
    Node *&asgariyiBul(Node *&kok) const;

  private:
    void makeEmpty(Node * &);       // utility for destructor
    
    // Define your private utility functions below this line
    void dugumVektorundenCompleteAgacYap(Node *&kok, std::vector<Node *> &vektor);	
    Node *dugumVektorundenCompleteAgacYapYardimci(std::vector<Node *> &vektor, size_t bas, size_t son);	
    void altAgacHeightSubsizeGuncelle(Node *kok);	
    void altAgaciCompleteTreeYap(Node *&subtree);	
    void dugumHeightVeSubsizeGuncelle(Node *&dugum);	
    void insertYardimci(Node *&kok, const Key &key, const Object &data);	
    void removeYardimci(Node *&kok, const Key &key, bool asgariyiSiliyoruz = false);

  private: /* DO NOT CHANGE PROTOTYPES: compiler defaults are blocked */  
    BinarySearchTree(const BinarySearchTree &);
    const BinarySearchTree & operator=(const BinarySearchTree &);

  private:  // static utility functions
    template <typename T> //static utility function
    static const T & max(const T &, const T &);

    // Define more below this line if needed
    static size_t minn(const size_t a, const size_t b);	
    static size_t kokunuKaziIndeksiniDon(size_t dugumSayisi);

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
 	if (!datalist.empty()) {	
    std::vector<Node *> dugumVektoru;	
    typename std::list<std::pair<K, O>>::const_iterator it;	
    for (it = datalist.begin(); it != datalist.end(); ++it) {	
      dugumVektoru.push_back(new Node(it->first, it->second, NULL, NULL));	
    }	
    dugumVektorundenCompleteAgacYap(root, dugumVektoru);	
    numNodes = subsize(root);	
  }
}


// IMPLEMENT
template <typename K, typename O, typename B, typename C>
void
BinarySearchTree<K,O,B,C>::toCompleteBST()
{
  altAgaciCompleteTreeYap(root);
}


// IMPLEMENT
template <typename K, typename O, typename B, typename C>
void
BinarySearchTree<K,O,B,C>::insert(const K & k, const O & x)
{
  insertYardimci(root, k, x);	
  numNodes = subsize(root);
}


// IMPLEMENT
template <typename K, typename O, typename B, typename C>
void
BinarySearchTree<K,O,B,C>::remove(const K & k)
{
  removeYardimci(root, k);	
  numNodes = subsize(root);
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
  findYardimci(root, ranges, lower, upper);	
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

// STUDENT PRIVATE MEMBER FUNCTION IMPLEMENTATIONS	
/* student private utility.*/	
template<typename Key, typename Object, typename BalanceCondition, typename Comparator>	
void BinarySearchTree<Key, Object, BalanceCondition, Comparator>::	
printSideways(Node *kok, std::string str) const {	
  if (kok) {	
    printSideways(kok->right, str + "\t");	
    std::cout << str << kok->data << std::endl;	
    printSideways(kok->left, str + "\t");	
  }	
}	
/* student private utility.*/	
template<typename Key, typename Object, typename BalanceCondition, typename Comparator>	
typename BinarySearchTree<Key, Object, BalanceCondition, Comparator>::	
Node *&BinarySearchTree<Key, Object, BalanceCondition, Comparator>::	
asgariyiBul(Node *&kok) const {	
  if (kok->left) {	
    return asgariyiBul(kok->left);	
  }	
  else {	
    return kok;	
  }	
}	
/* student private utility.*/	
template<typename Key, typename Object, typename BalanceCondition, typename Comparator>	
void BinarySearchTree<Key, Object, BalanceCondition, Comparator>::	
altAgacHeightSubsizeGuncelle(Node *kok) {	
  if (kok) {	
    altAgacHeightSubsizeGuncelle(kok->left);	
    altAgacHeightSubsizeGuncelle(kok->right);	
    dugumHeightVeSubsizeGuncelle(kok);	
  }	
}	
template<typename Key, typename Object, typename BalanceCondition, typename Comparator>	
void BinarySearchTree<Key, Object, BalanceCondition, Comparator>::	
dugumleriVektoreEkleInorder(Node * kok, std::vector<Node*>& vektor) const {	
  if (kok) {	
    dugumleriVektoreEkleInorder(kok->left, vektor);	
    vektor.push_back(kok);	
    dugumleriVektoreEkleInorder(kok->right, vektor);	
  }	
}	
/* student private utility. */	
template<typename Key, typename Object, typename BalanceCondition, typename Comparator>	
void BinarySearchTree<Key, Object, BalanceCondition, Comparator>::	
insertYardimci(Node *&kok, const Key &key, const Object &data) {	
  if (kok) {	
    bool esit = false;	
    if (isLessThan(key, kok->key)) {	
      insertYardimci(kok->left, key, data);	
    }	
    else if (isLessThan(kok->key, key)) {	
      insertYardimci(kok->right, key, data);	
    }	
    else {	
      esit = true;	
      kok->data = data;	
    }	
    if (!esit) {	
      dugumHeightVeSubsizeGuncelle(kok);	
      if (kok->subsize > 1) {	
        if (!isBalanced(kok->height, log2(subsize(kok)))) {	
          altAgaciCompleteTreeYap(kok);	
        }	
      }	
    }	
  }	
  else {	
    kok = new Node(key, data, NULL, NULL);	
  }	
}	
template<typename Key, typename Object, typename BalanceCondition, typename Comparator>	
void BinarySearchTree<Key, Object, BalanceCondition, Comparator>::	
altAgaciCompleteTreeYap(Node *& subtree) {	
  std::vector<Node *> dugumVektoru;	
  dugumleriVektoreEkleInorder(subtree, dugumVektoru);	
  dugumVektorundenCompleteAgacYap(subtree, dugumVektoru);	
}	
/* student private utility. */	
template<typename Key, typename Object, typename BalanceCondition, typename Comparator>	
void BinarySearchTree<Key, Object, BalanceCondition, Comparator>::	
removeYardimci(Node *&kok, const Key &key, bool asgariyiSiliyoruz) {	
  if (kok) {	
    if (isLessThan(key, kok->key)) {	
      removeYardimci(kok->left, key, asgariyiSiliyoruz);	
    }	
    else if (isLessThan(kok->key, key)) {	
      removeYardimci(kok->right, key, asgariyiSiliyoruz);	
    }	
    else {	
      if (kok->left && kok->right) {	
        Node *eskiKok = kok;	
        kok = asgariyiBul(kok->right);	
        removeYardimci(eskiKok->right, kok->key, true);	
        kok->right = eskiKok->right;	
        kok->left = eskiKok->left;	
        delete eskiKok;	
      }	
      else {	
        Node *eskiKok = kok;	
        kok = kok->left ? kok->left : kok->right;	
        if (!asgariyiSiliyoruz) {	
          delete eskiKok;	
        }	
      }	
    }	
  }	
  if (kok) {	
    dugumHeightVeSubsizeGuncelle(kok);	
    if (subsize(kok) > 1) {	
      if (!isBalanced(height(kok), log2(subsize(kok)))) {	
        altAgaciCompleteTreeYap(kok);	
      }	
    }	
  }	
}	
/* student private utility. */	
template<typename Key, typename Object, typename BalanceCondition, typename Comparator>	
void BinarySearchTree<Key, Object, BalanceCondition, Comparator>::	
findYardimci(Node *kok, std::list<Node *> &liste, const Key &az, const Key &cok) const {	
  if (kok) {	
    if (isLessThan(kok->key, az)) { // kok araligin solunda	
      findYardimci(kok->right, liste, az, cok);	
    }	
    else if (isLessThan(cok, kok->key)) { // kok araligin saginda	
      findYardimci(kok->left, liste, az, cok);	
    }	
    else { // kok araligin icinde	
      findYardimci(kok->left, liste, az, cok);	
      liste.push_back(kok);	
      findYardimci(kok->right, liste, az, cok);	
    }	
  }	
}	
/* student private utility. */	
template<typename Key, typename Object, typename BalanceCondition, typename Comparator>	
void BinarySearchTree<Key, Object, BalanceCondition, Comparator>::	
dugumHeightVeSubsizeGuncelle(Node *&dugum) {	
  dugum->height = 1 + max(height(dugum->left), height(dugum->right));	
  dugum->subsize = 1 + subsize(dugum->left) + subsize(dugum->right);	
}	
/* student private static utility. */	
template<typename Key, typename Object, typename BalanceCondition, typename Comparator>	
size_t BinarySearchTree<Key, Object, BalanceCondition, Comparator>::kokunuKaziIndeksiniDon(size_t dugumSayisi) {	
  int levelSayisi = log2(dugumSayisi) + 1;	
  int solAgacDugumSayisi = minn((dugumSayisi - exp2(levelSayisi - 1) + 1), exp2(levelSayisi - 2));	
  return exp2(levelSayisi - 2) + solAgacDugumSayisi - 1;	
}	
template<typename Key, typename Object, typename BalanceCondition, typename Comparator>	
void BinarySearchTree<Key, Object, BalanceCondition, Comparator>::	
dugumVektorundenCompleteAgacYap(Node *&kok, std::vector<Node *> &vektor) {	
  if (!vektor.empty()) {	
    kok = dugumVektorundenCompleteAgacYapYardimci(vektor, 0, vektor.size()-1);	
    altAgacHeightSubsizeGuncelle(kok);	
  }	
  else {	
    kok = NULL;	
  }	
}	
/* student private utility. */	
template<typename Key, typename Object, typename BalanceCondition, typename Comparator>	
typename BinarySearchTree<Key, Object, BalanceCondition, Comparator>::Node *BinarySearchTree<Key, Object, BalanceCondition, Comparator>::	
dugumVektorundenCompleteAgacYapYardimci(std::vector<Node *> &vektor, size_t bas, size_t son) {	
  if (son - bas + 1 <= 0) {	
    return NULL;	
  }	
  else if (son - bas + 1 == 1) {	
    vektor[bas]->left = NULL;	
    vektor[bas]->right = NULL;	
    return vektor[bas];	
  }	
  else {	
    size_t orta = bas + kokunuKaziIndeksiniDon(son - bas + 1);	
    vektor[orta]->left = dugumVektorundenCompleteAgacYapYardimci(vektor, bas, orta - 1);	
    vektor[orta]->right = dugumVektorundenCompleteAgacYapYardimci(vektor, orta + 1, son);	
    return vektor[orta];	
  }	
}	
/* student private static utility. */	
template<typename Key, typename Object, typename BalanceCondition, typename Comparator>	
size_t BinarySearchTree<Key, Object, BalanceCondition, Comparator>::minn(const size_t a, const size_t b) {	
  return a < b ? a : b;	
}