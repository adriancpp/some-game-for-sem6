//
//  gem.hpp
//  SDLBruh
//
//  Created by Adrian Witkowski on 01/06/2023.
//

#ifndef gem_hpp
#define gem_hpp

#include <stdio.h>
#include "entity.hpp"

class Gem
    : public Entity
{
public:
    int x;
   
    Gem()
    { }
   
    void initialize()
    {
        std::cout << "P: " << x << std::endl;
    }
};

#endif /* gem_hpp */
