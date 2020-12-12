#include "moviestore.h"


MovieStore::MovieStore( ) //implemented, do not change
{
}


// IMPLEMENT
void
MovieStore::insert(const Movie & movie)
{
    primaryIndex.insert(movie.getID(), movie);
    Movie * moviePtr = &(primaryIndex.find(movie.getID())->data);
    SKey skey(movie);
    secondaryIndex.insert(skey, moviePtr);
    ternaryIndex.insert(skey, moviePtr);
}


// IMPLEMENT
void
MovieStore::remove(const std::string & id)
{
    MovieStore::MSTP::Node * movieNode =  primaryIndex.find(id);
    if (movieNode) {
        SKey skey(movieNode->data);
        ternaryIndex.remove(skey);
        secondaryIndex.remove(skey);
        primaryIndex.remove(id);
    }


}


// IMPLEMENT
void
MovieStore::remove(const std::string & title,
                  const std::string & director)
{
    SKey skey(title, director);
    MovieStore::MSTS::Node *movieNode = secondaryIndex.find(skey);
    if (movieNode) {
        std::string id = movieNode->data->getID();
        ternaryIndex.remove(skey);
        secondaryIndex.remove(skey);
        primaryIndex.remove(id);
    }

}


// IMPLEMENT
void
MovieStore::removeAllMoviesWithTitle(const std::string & title)
{
    SKey skeyBas(title, "a"), skeySon(title, "{");

    // niye ternary kullaninca calisti hic anlamadim asdfadsffd secondary kullanmak gerekir diye dusunuyordum
    std::list<MovieStore::MSTT::Node *> movieler = ternaryIndex.find(skeyBas, skeySon);
    std::list<MovieStore::MSTT::Node *>::const_iterator it = movieler.begin();

    while (it != movieler.end()) {
        remove((*it++)->data->getID()); 
    }
}

// IMPLEMENT
void
MovieStore::makeAvailable(const std::string & id)
{
    MovieStore::MSTP::Node * movieNode =  primaryIndex.find(id);
    if (movieNode) {
        movieNode->data.setAvailable();
    }
}


// IMPLEMENT
void
MovieStore::makeUnavailable(const std::string & title,
                           const std::string & director)
{
    SKey skey(title, director);
    MovieStore::MSTT::Node *movieNode = ternaryIndex.find(skey);
    if (movieNode) {
        movieNode->data->setUnavailable();
    }
}


// IMPLEMENT
void
MovieStore::updateCompany(const std::string & director, 
                           const std::string & Company)
{
    SKey skeyBas("a", director), skeySon("z", director);

    std::list<MovieStore::MSTS::Node *> movieler = secondaryIndex.find(skeyBas, skeySon);
    std::list<MovieStore::MSTS::Node *>::const_iterator it = movieler.begin();

    while (it != movieler.end()) {
        primaryIndex.find((*it++)->data->getID())->data.setCompany(Company);
    }
}


// IMPLEMENT
void
MovieStore::printMoviesWithID(const std::string & id1,
                              const std::string & id2,
                              unsigned short since) const
{
    std::list<MovieStore::MSTP::Node *> movieler = primaryIndex.find(id1, id2);
    std::list<MovieStore::MSTP::Node *>::const_iterator it = movieler.begin();
    while (it != movieler.end()) {
        if ((*it)->data.getYear() >= since) {
            std::cout << (*it)->data << std::endl;
        }
        it++;
    }
}


// IMPLEMENT
void
MovieStore::printMoviesOfDirector(const std::string & director,
                                  const std::string & first,
                                  const std::string & last) const
{
    SKey skeyBas(first, director), skeySon(last, director);

    std::list<MovieStore::MSTS::Node *> movieler = secondaryIndex.find(skeyBas, skeySon);
    std::list<MovieStore::MSTS::Node *>::const_iterator it = movieler.begin();

    while (it != movieler.end()) {
        std::cout << *((*it++)->data) << std::endl;
    }
}



void  // implemented, do not change
MovieStore::printPrimarySorted( ) const
{
  printPrimarySorted(primaryIndex.getRoot());
}


void  // implemented, do not change
MovieStore::printPrimarySorted(MSTP::Node * t) const
{
  if (t == NULL)
  {
    return;
  }

  printPrimarySorted(t->left);
  std::cout << t->data << std::endl;
  printPrimarySorted(t->right);
}


void  // implemented, do not change
MovieStore::printSecondarySorted( ) const
{
  printSecondarySorted(secondaryIndex.getRoot());
}


void  // implemented, do not change
MovieStore::printSecondarySorted(MSTS::Node * t) const
{
  if (t == NULL)
  {
    return;
  }

  printSecondarySorted(t->left);
  std::cout << *(t->data) << std::endl;
  printSecondarySorted(t->right);
}


void  // implemented, do not change
MovieStore::printTernarySorted( ) const
{
  printTernarySorted(ternaryIndex.getRoot());
}


void  // implemented, do not change
MovieStore::printTernarySorted(MSTT::Node * t) const
{
  if (t == NULL)
  {
    return;
  }

  printTernarySorted(t->left);
  std::cout << *(t->data) << std::endl;
  printTernarySorted(t->right);
}

