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


        class Iterator {
        private:
            const MagicalContainer *container;
            size_t currentIndex;

        public:
            Iterator(const MagicalContainer &container);

            Iterator(const Iterator &other);

            virtual ~Iterator() = default;

            //for tidy-
            Iterator(Iterator&& other) = default;

            Iterator& operator=(Iterator&& other) = default;
            //

            const MagicalContainer* getContainer() const {
                return container;
            }

            size_t getCurrentIndex() const {
                return currentIndex;
            }

            void incrementCurrentIndex() {
                ++currentIndex;
            }

            void setCurrentIndex(size_t size) {
                currentIndex = size;
            }

            Iterator &operator=(const Iterator &other);

            virtual Iterator &operator++() = 0;

            virtual int operator*() const;

            bool operator==(const Iterator &other) const;

            bool operator!=(const Iterator &other) const;

            bool operator<(const Iterator &other) const;

            bool operator>(const Iterator &other) const;
        };


        class AscendingIterator : public Iterator{

        public:
            AscendingIterator(const MagicalContainer &container);

            AscendingIterator(const AscendingIterator &other);

            //for tidy
            ~AscendingIterator() override = default;
            AscendingIterator& operator=(const AscendingIterator& other) {
                Iterator::operator=(other);
                return *this;
            }
            AscendingIterator(AscendingIterator&& other) = default;
            AscendingIterator& operator=(AscendingIterator&& other) = default;
            //

            AscendingIterator &operator++() override;

            AscendingIterator begin();

            AscendingIterator end();
        };

        class SideCrossIterator : public Iterator {
        private:
            bool in_first_half_flag = true;

        public:
            SideCrossIterator(const MagicalContainer &container);

            SideCrossIterator(const SideCrossIterator &other);

            //for tidy
            ~SideCrossIterator() override = default;
            SideCrossIterator& operator=(const SideCrossIterator& other) {
                Iterator::operator=(other);
                return *this;
            }
            SideCrossIterator(SideCrossIterator&& other) = default;
            SideCrossIterator& operator=(SideCrossIterator&& other) = default;
            //

            SideCrossIterator &operator++() override;

            SideCrossIterator begin();

            SideCrossIterator end();
        };

        class PrimeIterator : public Iterator{
        public:
            PrimeIterator(const MagicalContainer &container);

            PrimeIterator(const PrimeIterator &other);

            //for tidy
            ~PrimeIterator() override = default;
            PrimeIterator& operator=(const PrimeIterator& other) {
                Iterator::operator=(other);
                return *this;
            }
            PrimeIterator(PrimeIterator&& other) = default;
            PrimeIterator& operator=(PrimeIterator&& other) = default;
            //

            PrimeIterator &operator++() override;

            int operator*() const override;

            PrimeIterator begin();

            PrimeIterator end();
        };
    };

}