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


    // Iterator base class


    MagicalContainer::Iterator::Iterator(const MagicalContainer &container) : container(&container), currentIndex(0) {}

    MagicalContainer::Iterator::Iterator(const Iterator &other) : container(other.container), currentIndex(other.currentIndex) {}

    MagicalContainer::Iterator &
    MagicalContainer::Iterator::operator=(const Iterator &other) {
        if(&container != &other.container) {throw std::runtime_error("Not valid operation - different containers.");}
        if (this != &other) {
            container = other.container;
            currentIndex = other.currentIndex;
        }
        return *this;
    }

    int MagicalContainer::Iterator::operator*() const {
        return container->elements.at(currentIndex);
    }

    bool MagicalContainer::Iterator::operator==(const Iterator &other) const {
        if (typeid(*this) != typeid(other)) { throw std::runtime_error("Can't use == between other types of Iterators");}
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


    // Ascending Iterator

    MagicalContainer::AscendingIterator::AscendingIterator(const MagicalContainer &container) : Iterator((container)) {}

    MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator &other) : Iterator(other) {}


    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator++() {
        if(getCurrentIndex() == getContainer()->size()) {throw std::runtime_error("Can't increment after end.");}
        incrementCurrentIndex();
        return *this;
    }

    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin() {
        return AscendingIterator(*getContainer());
    }

    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end() {
        AscendingIterator iter(*getContainer());
        iter.setCurrentIndex(getContainer()->elements.size());
        return iter;
    }

    // SideCross Iterator

    MagicalContainer::SideCrossIterator::SideCrossIterator(const MagicalContainer &container) : Iterator(container) {}

    MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator &other) : Iterator(other) {}

    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator++() {
        if(getCurrentIndex() == getContainer()->size()) {throw std::runtime_error("Can't increment after end.");}
        if(getCurrentIndex() == getContainer()->elements.size() / 2){
            setCurrentIndex(getContainer()->elements.size());
        }
        else if (in_first_half_flag) {
            setCurrentIndex(static_cast<size_t>(getContainer()->size() - 1) - getCurrentIndex());
            in_first_half_flag = false;
        }
        else if(!in_first_half_flag){
            setCurrentIndex(static_cast<size_t>(getContainer()->size()) - getCurrentIndex());
            in_first_half_flag = true;
        }
        return *this;
    }

    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin() {
        return SideCrossIterator(*getContainer());
    }

    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end() {
        SideCrossIterator iter(*getContainer());
        iter.setCurrentIndex(getContainer()->elements.size());
        return iter;    }

    // Prime Iterator

    MagicalContainer::PrimeIterator::PrimeIterator(const MagicalContainer &container) : Iterator(container) {}

    MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator &other) : Iterator(other) {}

    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++() {
        if(getCurrentIndex() == getContainer()->PrimeSize()) {throw std::runtime_error("Can't increment after end.");}
        incrementCurrentIndex();
        return *this;
    }

    int MagicalContainer::PrimeIterator::operator*() const {
        return *getContainer()->prime_elements.at(getCurrentIndex());
    }

    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin() {
        return PrimeIterator(*getContainer());
    }

    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end() {
        PrimeIterator iter(*getContainer());
        iter.setCurrentIndex(getContainer()->prime_elements.size());
        return iter;    }

}