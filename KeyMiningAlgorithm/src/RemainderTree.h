//
// Created by 佘崧林 on 2020/1/22.
//

#ifndef KEYMININGALGORITHM_REMAINDERTREE_H
#define KEYMININGALGORITHM_REMAINDERTREE_H

#include <gmpxx.h>
#include <functional>

#include "AbstractTree.h"
#include "ProductTree.h"

class RemainderTree : public AbstractTree<mpz_class> {
public:
    explicit RemainderTree(const ProductTree *&relatedProductTree);
};


#endif //KEYMININGALGORITHM_REMAINDERTREE_H
