#pragma once

#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;
namespace ariel {
    class MagicalContainer {
    private:
        vector<int> elements;
        vector<int*> prime_elements;

    public:
        MagicalContainer();

        ~MagicalContainer();

        // for tidy-
        MagicalContainer(const MagicalContainer&) = default;
        MagicalContainer& operator=(const MagicalContainer&) = default;
        MagicalContainer(MagicalContainer&&) = default;
        MagicalContainer& operator=(MagicalContainer&&)  = default;
        //

        void addElement(int element);

        void removeElement(int element);

        int size() const;

        int PrimeSize() const;

        bool check_prime(int n);


        class AscendingIterator {
        private:
            const MagicalContainer *container;
            size_t currentIndex;

        public:
            AscendingIterator(const MagicalContainer &container);

            AscendingIterator(const AscendingIterator &other);

            ~AscendingIterator();

            //for tidy-
            AscendingIterator(AscendingIterator&& other) = default;

            AscendingIterator& operator=(AscendingIterator&& other) = default;
            //

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

            //for tidy-
            SideCrossIterator(SideCrossIterator&& other) = default;

            SideCrossIterator& operator=(SideCrossIterator&& other) = default;
            //

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

            //for tidy-
            PrimeIterator(PrimeIterator&& other) = default;

            PrimeIterator& operator=(PrimeIterator&& other) = default;
            //

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