#ifndef _title_h__
#define _title_h__

#include "movie.h"
#include <cstring>


class TitleComparator
{
  public:
    // IMPLEMENT BELOW (inline)
    bool operator( ) (const Movie::SecondaryKey & key1, 
                      const Movie::SecondaryKey & key2) const
    { 
        /* i changed it to dynamic array after noticing compile time arrays are not permitted.
           also i could not think of a better way of comparing strings case-independently.
           i know those deletes look quite ugly, i am sorry about that but those deletes
           are as stupid as using dynamic arrays as static arrays. 
        */
        std::string *titles = new std::string[2];
        std::string *directors = new std::string[2];

        titles[0] = std::string(key1.getTitle());
        titles[1] = std::string(key2.getTitle());
        directors[0] = std::string(key1.getDirector());
        directors[1] = std::string(key2.getDirector());
        for (int i = 0; i < 2; ++i) {
            size_t titleLength = titles[i].size();
            size_t directorLength = directors[i].size();
            for (size_t j = 0; j < titleLength; ++j) {
                titles[i][j] = tolower(titles[i][j]);
            }
            for (size_t j = 0; j < directorLength; ++j) {
                directors[i][j] = tolower(directors[i][j]);
            }
        }
        

        if (titles[0] < titles[1]) {
            delete[] titles;
            delete[] directors;
            return true;
        } else if (titles[0] == titles[1]) {
            if (directors[0] < directors[1]) {
                delete[] titles;
                delete[] directors;
                return true;
            } else {
                delete[] titles;
                delete[] directors;
                return false;
            }
        } else {
            delete[] titles;
            delete[] directors;
            return false;
        }
    }

};

#endif
