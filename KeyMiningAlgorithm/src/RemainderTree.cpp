//
// Created by 佘崧林 on 2020/1/22.
//

#include "RemainderTree.h"

RemainderTree::RemainderTree(const ProductTree *&relatedProductTree): AbstractTree(*relatedProductTree) {
    mpz_t square, remainder;
    mpz_inits(square, remainder, NULL);
    this->preOrderForEach([&square, &remainder](AbstractTree *root) -> void{
        if (root->getParent() == nullptr) return;
        mpz_pow_ui(square, root->getNodeData().get_mpz_t(), 2u);
        mpz_mod(remainder, root->getParent()->getNodeData().get_mpz_t(), square);
        root->setNodeData(mpz_class(remainder));
    });
    mpz_clears(square, remainder, NULL);
}
