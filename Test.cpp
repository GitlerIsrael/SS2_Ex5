//
// Created by israel on 5/29/23.
//
#include <stdexcept>
#include <iostream>
#include "doctest.h"
#include "sources/MagicalContainer.hpp"

using namespace ariel;

TEST_CASE("MagicalContainer - Basic Functionality") {
    MagicalContainer container;

    CHECK_EQ(container.size(), 0);

    SUBCASE("Adding and Removing Elements") {
        container.addElement(5);
        container.addElement(2);
        container.addElement(8);

        CHECK_EQ(container.size(), 3);

        container.removeElement(2);

        CHECK_THROWS_AS(container.removeElement(2), std::runtime_error); // Element already removed from container.
        CHECK_EQ(container.size(), 2);

        container.addElement(3);
        container.addElement(7);

        CHECK_EQ(container.size(), 4);

        CHECK_THROWS_AS(container.removeElement(9), std::runtime_error); // Element not in the container

        CHECK_EQ(container.size(), 4);
    }

    SUBCASE("AscendingIterator") {
        container.addElement(5);
        container.addElement(2);
        container.addElement(8);
        container.addElement(3);

        MagicalContainer::AscendingIterator it = MagicalContainer::AscendingIterator(container).begin();

        CHECK_EQ(*it, 2);
        ++it;
        CHECK_EQ(*it, 3);
        ++it;
        CHECK_EQ(*it, 5);
        ++it;
        CHECK_EQ(*it, 8);
        ++it;
        CHECK_EQ(it, MagicalContainer::AscendingIterator(container).end());
    }

    SUBCASE("SideCrossIterator") {
        container.addElement(5);
        container.addElement(2);
        container.addElement(8);
        container.addElement(3);

        MagicalContainer::SideCrossIterator it = MagicalContainer::SideCrossIterator(container).begin();

        CHECK_EQ(*it, 2);
        ++it;
        CHECK_EQ(*it, 8);
        ++it;
        CHECK_EQ(*it, 3);
        ++it;
        CHECK_EQ(*it, 5);
        ++it;
        CHECK_EQ(it, MagicalContainer::SideCrossIterator(container).end());
    }

    SUBCASE("PrimeIterator") {
        container.addElement(5);
        container.addElement(2);
        container.addElement(8);
        container.addElement(3);

        MagicalContainer::PrimeIterator it = MagicalContainer::PrimeIterator(container).begin();

        CHECK_EQ(*it, 2);
        ++it;
        CHECK_EQ(*it, 3);
        ++it;
        CHECK_EQ(*it, 5);
        ++it;
        CHECK_EQ(it, MagicalContainer::PrimeIterator(container).end());
    }
}

TEST_CASE("MagicalContainer - Edge Cases") {
    MagicalContainer container;

    SUBCASE("Empty Container") {
        MagicalContainer::AscendingIterator it1 = MagicalContainer::AscendingIterator(container).begin();
        MagicalContainer::SideCrossIterator it2 = MagicalContainer::SideCrossIterator(container).begin();
        MagicalContainer::PrimeIterator it3 = MagicalContainer::PrimeIterator(container).begin();

        CHECK_EQ(it1, MagicalContainer::AscendingIterator(container).end());
        CHECK_EQ(it2, MagicalContainer::SideCrossIterator(container).end());
        CHECK_EQ(it3, MagicalContainer::PrimeIterator(container).end());
    }

    SUBCASE("Single Element") {
        container.addElement(5);

        MagicalContainer::AscendingIterator it1 = MagicalContainer::AscendingIterator(container).begin();
        MagicalContainer::SideCrossIterator it2 = MagicalContainer::SideCrossIterator(container).begin();
        MagicalContainer::PrimeIterator it3 = MagicalContainer::PrimeIterator(container).begin();

        CHECK_EQ(*it1, 5);
        CHECK_EQ(*it2, 5);
        CHECK_EQ(*it3, 5);

        ++it1;
        ++it2;
        ++it3;

        CHECK_EQ(it1, MagicalContainer::AscendingIterator(container).end());
        CHECK_EQ(it2, MagicalContainer::SideCrossIterator(container).end());
        CHECK_EQ(it3, MagicalContainer::PrimeIterator(container).end());
    }
}

TEST_CASE("MagicalContainer - Large Container") {
    MagicalContainer container;

    // Add 1000 elements to the container
    for (int i = 1; i <= 1000; ++i) {
        container.addElement(i);
    }

    CHECK_EQ(container.size(), 1000);

    SUBCASE("AscendingIterator") {
        MagicalContainer::AscendingIterator it = MagicalContainer::AscendingIterator(container).begin();

        CHECK_EQ(*it, 1);

        for (int i = 1; i <= 1000; ++i) {
            CHECK_EQ(*it, i);
            ++it;
        }

        CHECK_EQ(it, MagicalContainer::AscendingIterator(container).end());
    }

    SUBCASE("PrimeIterator") {
        MagicalContainer::PrimeIterator it = MagicalContainer::PrimeIterator(container).begin();

        int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47,
                        53, 59, 61, 67, 71, 73, 79, 83, 89, 97};

        int index = 0;
        while (it != MagicalContainer::PrimeIterator(container).end() && index < 25) {
            CHECK_EQ(*it, primes[index]);
            ++it;
            ++index;
        }
    }
}