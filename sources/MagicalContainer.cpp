#include "MagicalContainer.hpp"
#include <stdexcept>
#include <iostream>


using namespace std;

namespace ariel {
    // Default constructor.
    MagicalContainer::MagicalContainer() {}

    // Add element to MagicalContainer vector
    void MagicalContainer::addElement(const int& element) {
        auto it = std::find(elements.begin(), elements.end(), element); // Check if element already exist. O(n)
        if (it != elements.end()) {
            throw std::runtime_error("Can't add duplicate elements."); // Throw exception that already exist.
        } else {
            auto it = std::lower_bound(elements.begin(), elements.end(), element); // Check where o push the new element. O(log n)
            elements.insert(it, element);

            //         // Re-create prime and side cross vectors. (did it because elements vector resize its capacity sometimes and realloc new memory for all elements)
            create_pointers_vectors();
        }
    }

    // Remove element from MagicalContainer vector.
    void MagicalContainer::removeElement(int element) {
        auto it = std::find(elements.begin(), elements.end(), element); // Find if element exist. O(n).
        if (it != elements.end()) {
            elements.erase(it);
        }else{
            throw std::runtime_error("Element not exist");
        }

        // Re-create prime and side cross vectors. (did it because elements vector resize its capacity sometimes and realloc new memory for all elements)
        create_pointers_vectors();
    }


    void MagicalContainer::create_pointers_vectors() {
        // Clear prime vector and init it again.
        prime_elements.clear(); // O(n)
        for(int& elem : elements) { // O(n)
            if (check_prime(elem)) {
                prime_elements.push_back(&elem);
            }
        }

        // Clear sideCross vector and init it again.
        sideCross_elements.clear();
        //Manipulate elements vector to create sideCross vector.
        int index = 0;
        bool in_first_half_flag = true;
        while(index != size() / 2) {
            sideCross_elements.push_back(&elements.at(static_cast<size_t>(index)));
            if (in_first_half_flag) {
                index = size() - 1 - index;
            } else {
                index = size() - index;
            }
            in_first_half_flag = !in_first_half_flag;
        }
        sideCross_elements.push_back(&elements.at(static_cast<size_t>(index)));
    }


    // Return container elements vector size.
    int MagicalContainer::size() const {
        return elements.size();
    }

    // Return container prime elements vector size.
    int MagicalContainer::PrimeSize() const {
        return prime_elements.size();
    }

    // Helper function to check if number is a prime.
    bool MagicalContainer::check_prime(int n) {
        if (n < 2) {
            return false;
        }

        int sqrtn = static_cast<int>(std::sqrt(n));
        for (int i = 2; i <= sqrtn; ++i) {
            if (n % i == 0) {
                return false;
            }
        }

        return true;
    }


    // Iterator base class

    // Iterator constructor.
    MagicalContainer::Iterator::Iterator(const MagicalContainer &container) : container(&container), currentIndex(0) {}

    // Copy constructor.
    MagicalContainer::Iterator::Iterator(const Iterator &other) : container(other.container), currentIndex(other.currentIndex) {}

    // assignment operator overloading.
    MagicalContainer::Iterator & MagicalContainer::Iterator::operator=(const Iterator &other) {
        // Check if has the same container. if not, throw exception.
        if(&container != &other.container) {throw std::runtime_error("Not valid operation - different containers.");}
        if (this != &other) { // For preventing a case that we delete this and then try to use it.
            container = other.container;
            currentIndex = other.currentIndex;
        }
        return *this;
    }

    //operator* overloading.
    int MagicalContainer::Iterator::operator*() const {
        return container->elements.at(currentIndex);
    }

    // operator== overloading.
    bool MagicalContainer::Iterator::operator==(const Iterator &other) const {
        // Check if the iterators are from the same type. if not - throw exception.
        if (typeid(*this) != typeid(other)) { throw std::runtime_error("Can't use == between other types of Iterators");}
        return currentIndex == other.currentIndex;
    }

    // operator!= overloading.
    bool MagicalContainer::Iterator::operator!=(const Iterator &other) const {
        return !(*this == other);
    }

    // operator< overloading.
    bool MagicalContainer::Iterator::operator<(const Iterator &other) const {
        return currentIndex < other.currentIndex;
    }

    // operator> overloading.
    bool MagicalContainer::Iterator::operator>(const Iterator &other) const {
        return currentIndex > other.currentIndex;
    }


    // Ascending Iterator

    // AscendingIterator constructor (use base class - Iterator).
    MagicalContainer::AscendingIterator::AscendingIterator(const MagicalContainer &container) : Iterator((container)) {}

    // Copy constructor (use base class - Iterator).
    MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator &other) : Iterator(other) {}

    // Operator++ overriding. (pure virtual in base class).
    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator++() {
        // Check if not arrived to end of container elements vector.
        if(getCurrentIndex() == getContainer()->size()) {throw std::runtime_error("Can't increment after end.");}
        incrementCurrentIndex(); // Increment index by one.
        return *this;
    }

    // Returns begin iterator.
    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin() {
        return AscendingIterator(*getContainer());
    }

    // Returns end iterator.
    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end() {
        AscendingIterator iter(*getContainer());
        iter.setCurrentIndex(getContainer()->elements.size());
        return iter;
    }

    // SideCross Iterator

    // SideCrossIterator constructor (use base class - Iterator).
    MagicalContainer::SideCrossIterator::SideCrossIterator(const MagicalContainer &container) : Iterator(container) {}

    // Copy constructor (use base class - Iterator).
    MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator &other) : Iterator(other) {}

    // operator* overriding.
    int MagicalContainer::SideCrossIterator::operator*() const {
        return *getContainer()->sideCross_elements.at(getCurrentIndex());
    }

    // Operator++ overriding. (pure virtual in base class).
    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator++() {
        // Check if not arrived to end of container elements vector.
        if(getCurrentIndex() == getContainer()->size()) {throw std::runtime_error("Can't increment after end.");}
        incrementCurrentIndex(); // Increment index by one.
        return *this;
    }

    // Returns begin iterator.
    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin() {
        return SideCrossIterator(*getContainer());
    }

    // Returns end iterator.
    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end() {
        SideCrossIterator iter(*getContainer());
        iter.setCurrentIndex(getContainer()->elements.size());
        return iter;    }

    // Prime Iterator

    // PrimeIterator constructor (use base class - Iterator).
    MagicalContainer::PrimeIterator::PrimeIterator(const MagicalContainer &container) : Iterator(container) {}

    // Copy constructor (use base class - Iterator).
    MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator &other) : Iterator(other) {}

    // Operator++ overriding. (pure virtual in base class).
    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++() {
        // Check if not arrived to end of container elements vector.
        if(getCurrentIndex() == getContainer()->PrimeSize()) {throw std::runtime_error("Can't increment after end.");}
        incrementCurrentIndex();
        return *this;
    }

    // operator* overriding.
    int MagicalContainer::PrimeIterator::operator*() const {
        return *getContainer()->prime_elements.at(getCurrentIndex());
    }

    // Returns begin iterator.
    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin() {
        return PrimeIterator(*getContainer());
    }

    // Returns end iterator.
    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end() {
        PrimeIterator iter(*getContainer());
        iter.setCurrentIndex(getContainer()->prime_elements.size());
        return iter;    }

}