#pragma once

#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;
namespace ariel {
    class MagicalContainer {
    private:
        vector<int> elements;

    public:
        MagicalContainer();

        void addElement(int element);

        void removeElement(int element);

        int size() const;

        class AscendingIterator {
        private:
            const MagicalContainer *container;
            size_t currentIndex;

        public:
            AscendingIterator(const MagicalContainer &container);

            AscendingIterator(const AscendingIterator &other);

            ~AscendingIterator();

            AscendingIterator &operator=(const AscendingIterator &other);

            AscendingIterator &operator++();

            int operator*() const;

            bool operator==(const AscendingIterator &other) const;

            bool operator!=(const AscendingIterator &other) const;

            bool operator<(const AscendingIterator &other) const;

            bool operator>(const AscendingIterator &other) const;

            AscendingIterator begin();

            AscendingIterator end();
        };

        class SideCrossIterator {
        private:
            const MagicalContainer *container;
            size_t currentIndex;
            bool in_first_half_flag = true;

        public:
            SideCrossIterator(const MagicalContainer &container);

            SideCrossIterator(const SideCrossIterator &other);

            ~SideCrossIterator();

            SideCrossIterator &operator=(const SideCrossIterator &other);

            SideCrossIterator &operator++();

            int operator*() const;

            bool operator==(const SideCrossIterator &other) const;

            bool operator!=(const SideCrossIterator &other) const;

            bool operator<(const SideCrossIterator &other) const;

            bool operator>(const SideCrossIterator &other) const;

            SideCrossIterator begin();

            SideCrossIterator end();
        };

        class PrimeIterator {
        private:
            const MagicalContainer *container;
            size_t currentIndex;
        public:
            PrimeIterator(const MagicalContainer &container);

            PrimeIterator(const PrimeIterator &other);

            ~PrimeIterator();

            bool check_prime(int n);

            PrimeIterator &operator=(const PrimeIterator &other);

            PrimeIterator &operator++();

            int operator*() const;

            bool operator==(const PrimeIterator &other) const;

            bool operator!=(const PrimeIterator &other) const;

            bool operator<(const PrimeIterator &other) const;

            bool operator>(const PrimeIterator &other) const;

            PrimeIterator begin();

            PrimeIterator end();
        };


    };

}