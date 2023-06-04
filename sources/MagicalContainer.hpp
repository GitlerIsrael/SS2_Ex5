#pragma once

#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;
namespace ariel {
    class MagicalContainer {
    private:
        vector<int> elements;
        vector<const int*> prime_elements;

    public:
        MagicalContainer();

        void addElement(const int& element);

        void removeElement(int element);

        int size() const;

        int PrimeSize() const;

        bool check_prime(int n);


        class Iterator{
        protected:
            const MagicalContainer *container;
            size_t currentIndex;

        public:

            Iterator(const MagicalContainer &container);

            Iterator(const Iterator &other);

            ~Iterator();

            //for tidy-
            Iterator(Iterator&& other) = default;

            Iterator& operator=(Iterator&& other) = default;
            //

            Iterator &operator=(const Iterator &other);

            virtual Iterator &operator++();

            int operator*() const;

            bool operator==(const Iterator &other) const;

            bool operator!=(const Iterator &other) const;

            bool operator<(const Iterator &other) const;

            bool operator>(const Iterator &other) const;

            Iterator begin();

            Iterator end();
        };


        class AscendingIterator : public Iterator{
        private:
            const MagicalContainer *container;
            size_t currentIndex;

        public:
            AscendingIterator(const MagicalContainer &container);

            AscendingIterator(const AscendingIterator &other);

//            ~AscendingIterator();

//            //for tidy-
//            AscendingIterator(AscendingIterator&& other) = default;
//
//            AscendingIterator& operator=(AscendingIterator&& other) = default;
//            //
//
//            AscendingIterator &operator=(const AscendingIterator &other);
//
//            AscendingIterator &operator++() override;
//
//            int operator*() const;
//
//            bool operator==(const AscendingIterator &other) const;
//
//            bool operator!=(const AscendingIterator &other) const;
//
//            bool operator<(const AscendingIterator &other) const;
//
//            bool operator>(const AscendingIterator &other) const;
//
//            AscendingIterator begin();
//
//            AscendingIterator end();
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