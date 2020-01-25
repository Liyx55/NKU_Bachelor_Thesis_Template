//
// Created by 佘崧林 on 2020/1/22.
//
#ifndef KEYMININGALGORITHM_EFFIENTLYGCD_HPP
#define KEYMININGALGORITHM_EFFIENTLYGCD_HPP

#include <gmpxx.h>
#include <list>
#if BOOST_TEST_MODULE == EfficientlyGCDTest
#include <boost/test/included/unit_test.hpp>
#endif

#include "../src/ProductTree.h"
#include "../src/RemainderTree.h"


std::list<mpz_class> EffientlyGCD(const std::list<mpz_class>& bigNumbers) {
    std::list<mpz_class> gcdList;
    // TODO: STEP1 - build product tree from RSA moduli
    auto *productTree = new ProductTree(bigNumbers);
#if BOOST_TEST_MODULE == EfficientlyGCDTest
    auto root = productTree->getNodeData();
    BOOST_TEST_MESSAGE("\nProduct tree has been built success. Product tree's root bits length: " << root.get_str(2).size());
#endif
    // TODO: STEP2 - compute remainder tree with `P mod N^2`
    auto *remainderTree = new RemainderTree((const ProductTree *&)productTree);
    std::list<mpz_class> remainderLeaf = remainderTree->preOrderGetLeafList();
    std::list<mpz_class> productLeaf = productTree->preOrderGetLeafList();
#if BOOST_TEST_MODULE == EfficientlyGCDTest
    BOOST_TEST_MESSAGE("Remainder tree has built success. Remainder tree's leaf list:");
    for (const auto& remainder: remainderLeaf) {
        BOOST_TEST_MESSAGE("\t\t" << remainder.get_str(16).substr(0, 16) << "...");
    }
    BOOST_REQUIRE_MESSAGE(productLeaf.size() == bigNumbers.size(), "Product tree leaf number");
    BOOST_REQUIRE_MESSAGE(productLeaf == bigNumbers, "Product tree leaf order");
#endif
    // TODO: STEP3 - compute `gcd(N, z/N)`
    mpz_t quotientNumber, gcdNumber;
    mpz_inits(quotientNumber, gcdNumber, NULL);
    for (auto N = productLeaf.begin(), z = remainderLeaf.begin(); N != productLeaf.end() && z != remainderLeaf.end(); N++, z++) {
        mpz_div(quotientNumber, z->get_mpz_t(), N->get_mpz_t());
        mpz_gcd(gcdNumber, quotientNumber, N->get_mpz_t());
        gcdList.emplace_back(gcdNumber);
    }
    mpz_clears(quotientNumber, gcdNumber, NULL);
    return gcdList;
}

#endif