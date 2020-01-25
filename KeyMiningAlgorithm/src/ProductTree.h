//
// Created by 佘崧林 on 2020/1/22.
//

#ifndef KEYMININGALGORITHM_PRODUCTTREE_H
#define KEYMININGALGORITHM_PRODUCTTREE_H

#include <gmpxx.h>
#include <list>

#include "AbstractTree.h"

class ProductTree : public AbstractTree<mpz_class>{
public:
    explicit ProductTree(const std::list<mpz_class>& leafList);

    ProductTree &operator=(const AbstractTree<mpz_class> &copy);
};


#endif //KEYMININGALGORITHM_PRODUCTTREE_H
