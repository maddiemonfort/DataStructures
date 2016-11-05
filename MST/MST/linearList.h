//
//  linearlist.h
//
//  Created by Madeleine Monfort on 12/1/15.
//  Copyright © 2015 Madeleine Monfort. All rights reserved.
//
#ifndef linearlist_h
#define linearlist_h
#include <iostream>

template<class T>
class linearList 
{
   public:
      //virtual ~linearList() {};
      virtual bool empty() const = 0;
      virtual int size() const = 0;
      virtual T& get(int theIndex) const = 0;
      virtual int indexOf(const T& theElement)const = 0;
      virtual void erase(int theIndex) = 0;
      virtual void insert(int theIndex, const T& theElement) = 0;
      //virtual void output(std::ostream& out) const = 0;
};
#endif /* linearlist_h */