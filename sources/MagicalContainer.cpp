//implemented only for compiling now. The implementations are not at o(1) where needed at this level of the excercise.
// At this level need only to compile + tests.

#include "MagicalContainer.hpp"
#include <stdexcept>


using namespace std;

namespace ariel {
    MagicalContainer::MagicalContainer() {}


    void MagicalContainer::addElement(const int& element) {
        auto it = std::find(elements.begin(), elements.end(), element);
        if (it != elements.end()) {
            throw std::runtime_error("Can't add duplicate elements.");
        } else {
            auto it = std::lower_bound(elements.begin(), elements.end(), element);
            elements.insert(it, element);

            if (check_prime(element)) {
                auto it_prime = std::lower_bound(prime_elements.begin(), prime_elements.end(), &element,
                                                 [](const int *a, const int *b) {
                                                     return *a < *b;
                                                 });
                prime_elements.insert(it_prime, &element);
            }
        }
    }

    void MagicalContainer::removeElement(int element) {
        auto it = std::find(elements.begin(), elements.end(), element);
        if (it != elements.end()) {
            elements.erase(it);
        }else{
            throw std::runtime_error("Element not exist");
        }
    }

    int MagicalContainer::size() const {
        return elements.size();
    }

    int MagicalContainer::PrimeSize() const {
        return prime_elements.size();
    }

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

    // Iterator

    MagicalContainer::Iterator::Iterator(const MagicalContainer &container) : container(&container), currentIndex(0) {}

    MagicalContainer::Iterator::Iterator(const Iterator &other) : container(other.container), currentIndex(other.currentIndex) {}

    MagicalContainer::Iterator::~Iterator() {}

    MagicalContainer::Iterator &
    MagicalContainer::Iterator::operator=(const Iterator &other) {
        if(&container != &other.container) {throw std::runtime_error("Not valid operation - different containers.");}
        if (this != &other) {
            container = other.container;
            currentIndex = other.currentIndex;
        }
        return *this;
    }

    MagicalContainer::Iterator &MagicalContainer::Iterator::operator++() {
        if(currentIndex == container->size()) {throw std::runtime_error("Can't increment after end.");}
        ++currentIndex;
        return *this;
    }

    int MagicalContainer::Iterator::operator*() const {
        return container->elements.at(currentIndex);
    }

    bool MagicalContainer::Iterator::operator==(const Iterator &other) const {
        return currentIndex == other.currentIndex;
    }

    bool MagicalContainer::Iterator::operator!=(const Iterator &other) const {
        return !(*this == other);
    }

    bool MagicalContainer::Iterator::operator<(const Iterator &other) const {
        return currentIndex < other.currentIndex;
    }

    bool MagicalContainer::Iterator::operator>(const Iterator &other) const {
        return currentIndex > other.currentIndex;
    }

    MagicalContainer::Iterator MagicalContainer::Iterator::begin() {
        return Iterator(*container);
    }

    MagicalContainer::Iterator MagicalContainer::Iterator::end() {
        Iterator iter(*container);
        iter.currentIndex = container->elements.size();
        return iter;
    }

    // Ascending Iterator

    MagicalContainer::AscendingIterator::AscendingIterator(const MagicalContainer &container) : Iterator(container) {}

    MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator &other) : Iterator(other) {}
//
//    MagicalContainer::AscendingIterator::~AscendingIterator() {}
//
//    MagicalContainer::AscendingIterator &
//    MagicalContainer::AscendingIterator::operator=(const AscendingIterator &other) {
//        if(&container != &other.container) {throw std::runtime_error("Not valid operation - different containers.");}
//        if (this != &other) {
//            container = other.container;
//            currentIndex = other.currentIndex;
//        }
//        return *this;
//    }
//
//    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator++() {
//        if(currentIndex == container->size()) {throw std::runtime_error("Can't increment after end.");}
//        ++currentIndex;
//        return *this;
//    }
//
//    int MagicalContainer::AscendingIterator::operator*() const {
//        return container->elements.at(currentIndex);
//    }
//
//    bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator &other) const {
//        return currentIndex == other.currentIndex;
//    }
//
//    bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator &other) const {
//        return !(*this == other);
//    }
//
//    bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator &other) const {
//        return currentIndex < other.currentIndex;
//    }
//
//    bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator &other) const {
//        return currentIndex > other.currentIndex;
//    }
//
//    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin() {
//        return AscendingIterator(*container);
//    }
//
//    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end() {
//        AscendingIterator iter(*container);
//        iter.currentIndex = container->elements.size();
//        return iter;
//    }

    // SideCross Iterator

    MagicalContainer::SideCrossIterator::SideCrossIterator(const MagicalContainer &container) : container(&container), currentIndex(0) {}

    MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator &other) : container(other.container), currentIndex(other.currentIndex) {}

    MagicalContainer::SideCrossIterator::~SideCrossIterator() {}

    MagicalContainer::SideCrossIterator &
    MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator &other) {
        if(&container != &other.container) {throw std::runtime_error("Not valid operation - different containers.");}
        if (this != &other) {
            container = other.container;
            currentIndex = other.currentIndex;
        }
        return *this;
    }

    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator++() {
        if(currentIndex == container->size()) {throw std::runtime_error("Can't increment after end.");}
        if(currentIndex == container->elements.size() / 2){
            currentIndex = container->elements.size();
        }
        else if (in_first_half_flag) {
            currentIndex = static_cast<size_t>(container->size() - 1) - currentIndex;
            in_first_half_flag = false;
        }
        else if(!in_first_half_flag){
            currentIndex = static_cast<size_t>(container->size()) - currentIndex;
            in_first_half_flag = true;
        }
        return *this;
    }

    int MagicalContainer::SideCrossIterator::operator*() const {
        return container->elements.at(currentIndex);
    }

    bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator &other) const {
        return currentIndex == other.currentIndex;
    }

    bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator &other) const {
        return !(*this == other);
    }

    bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator &other) const {
        return currentIndex < other.currentIndex;
    }

    bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator &other) const {
        return currentIndex > other.currentIndex;
    }

    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin() {
        return SideCrossIterator(*container);
    }

    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end() {
        SideCrossIterator iter(*container);
        iter.currentIndex = container->elements.size();
        return iter;    }

    // Prime Iterator

    MagicalContainer::PrimeIterator::PrimeIterator(const MagicalContainer &container) : container(&container), currentIndex(0) {}

    MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator &other) : container(other.container), currentIndex(other.currentIndex) {}

    MagicalContainer::PrimeIterator::~PrimeIterator() {}

    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator=(const PrimeIterator &other) {
        if(&container != &other.container) {throw std::runtime_error("Not valid operation - different containers.");}
        if (this != &other) {
            container = other.container;
            currentIndex = other.currentIndex;
        }
        return *this;
    }

    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++() {
        if(currentIndex == container->PrimeSize()) {throw std::runtime_error("Can't increment after end.");}
        ++currentIndex;
        return *this;
    }

    int MagicalContainer::PrimeIterator::operator*() const {
        return *container->prime_elements.at(currentIndex);
    }

    bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator &other) const {
        return currentIndex == other.currentIndex;
    }

    bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator &other) const {
        return !(*this == other);
    }

    bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator &other) const {
        return currentIndex < other.currentIndex;
    }

    bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator &other) const {
        return currentIndex > other.currentIndex;
    }

    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin() {
        return PrimeIterator(*container);
    }

    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end() {
        PrimeIterator iter(*container);
        iter.currentIndex = container->prime_elements.size();
        return iter;    }

}