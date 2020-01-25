//
// Created by 佘崧林 on 2020/1/24.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE EfficientlyGCDTest
#include <boost/test/included/unit_test.hpp>
#include <gmpxx.h>
#include <vector>

#include "../include/EffientlyGCD.hpp"

std::vector< std::vector<mpz_class> > testCases = {
        {
            mpz_class(3), mpz_class(5), mpz_class(7), mpz_class(11),
            mpz_class(13), mpz_class(17), mpz_class(19),
            mpz_class(14549535),
        },
        {
            mpz_class("da645626c962c7862094ea092da4eb415c5d0862f5af7c9806eb924e06b21f297b5f58ef4ac306a6c85bb050f904d499f01cdf68ba2eb19d4f373e4bbaa375f5", 16),
            mpz_class("e1ce7c3eda491c12182d1b4d7c017b707c6e34db1100466393510dbd0947a44a175437ea9236d2a414dc671419a353e2af60efd6decc703e17891b595bd8b3d1", 16),
            mpz_class("a10b937f317691ea6ad3349abd6db42185db6df7b79dfb90a78f6cc02ed9c55781ab98c93625a29d5b83fc4a8ef2be39e53d41eca910ac00cce047c43d3dfab", 16),
            mpz_class("ee219b8e44af723c666490e469db944535a2866a5c0aaddc6f45123f477007a1f3fc533ec71ed01b0f24b1b4d0f7e4b995ae2ee25d2ab97e6ada1d0436ccb3ed", 16),
            mpz_class("f6d8d9572584763db16a2dc220c4dc2196bd455f93543b1bc98a6c36c2e1bc5a1191bbe8256023c27097855b8458d3a73b9e5363c2df7a56633aa2ba458b0af3", 16),
            mpz_class("c8371fbc63bec5903887d4ff985a95e868d0cde6246efa8b664f6f5b33d4b3404140e295d0edaa3e7e4e4ddf8d8892b4ebe97c41c27d2b04736a6caadff6f25f", 16),
            mpz_class("f962bee0df1664e680ce37138824c45c3b6f7199b3e7209ed669035ae277058bbeecd09b6fa2c1cdc597e0d3d6c5afb7bbafc5a76745cc2e0be1153c61279311", 16),
        }
};

mpz_class generatePrime(size_t nbits) {
    static time_t seed;
    static gmp_randstate_t random_state;
    if (!seed) {
        seed = time(nullptr);
        gmp_randinit_mt(random_state);
        gmp_randseed_ui(random_state, seed);
    }

    mpz_t prime; mpz_init(prime);
    mpz_urandomb(prime, random_state, nbits);
    mpz_nextprime(prime, prime);

    mpz_class result = mpz_class(prime);
    mpz_clear(prime);
    return mpz_class(prime);
}

BOOST_AUTO_TEST_CASE( prime512_7_product_4 ) {
    std::vector<mpz_class> pVector;
    pVector.reserve(7);
    for (int i = 0; i < 7; i++) {
        pVector.emplace_back(generatePrime(512));
    }
    testCases.emplace_back(pVector);

    mpz_t product;
    mpz_init(product);
    for(auto primeVector: testCases) {
        std::list<mpz_class> productList;
        for (int i = 0; i < 4; i++) {
            mpz_mul(product, primeVector[(i * 2) % 7].get_mpz_t(), primeVector[(i * 2 + 1) % 7].get_mpz_t());
            productList.emplace_back(mpz_class(product));
            BOOST_TEST_MESSAGE(
                    mpz_class(product).get_str(16).substr(0, 16) << "... = " <<
                    primeVector[(i * 2) % 7].get_str(16).substr(0, 16) << "... * " <<
                    primeVector[(i * 2 + 1) % 7].get_str(16).substr(0, 16) << "..."
            );
//            BOOST_TEST_MESSAGE(
//                    mpz_class(product).get_str(16) << " = " <<
//                    primeVector[(i * 2) % 7].get_str(16) << " * " <<
//                    primeVector[(i * 2 + 1) % 7].get_str(16)
//            );
        }

        auto gcdList = EffientlyGCD(productList);
        auto p = productList.begin(), g = gcdList.begin();
        BOOST_TEST_MESSAGE("Number -> GCD List: ");
        for (; p != productList.end() && g != gcdList.end(); p++, g++) {
            BOOST_TEST_MESSAGE("\t\t" << p->get_str(16).substr(0, 16) << "... -> " << g->get_str(16).substr(0, 16) << "...");
        }
//    BOOST_REQUIRE_MESSAGE(p != productList.end() || g != gcdList.end(),
//            "GCD list size isn't equal to the number list");
//    BOOST_TEST(true);
    }
    mpz_clear(product);
}
