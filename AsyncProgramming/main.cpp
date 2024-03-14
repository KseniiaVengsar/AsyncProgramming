#include <iostream>
#include <vector>
#include <future>
#include <algorithm>


int findMin(const std::vector<int>& vec, size_t start, size_t end) {
    int min = vec[start];
    for (size_t i = start + 1; i < end; ++i) {
        if (vec[i] < min) {
            min = vec[i];
        }
    }
    return min;
}


int asyncFindMin(const std::vector<int>& vec, size_t start, size_t end) {
    return findMin(vec, start, end);
}

std::vector<int> selectionSort(const std::vector<int>& vec) {
    std::vector<int> sortedVec = vec;

    for (size_t i = 0; i < sortedVec.size(); ++i) {
        //promise è future 
        std::promise<int> promise;
        std::future<int> future = promise.get_future();

        std::thread([&promise, &sortedVec, i]() {
            int min = asyncFindMin(sortedVec, i, sortedVec.size());
        promise.set_value(min);
            }).detach();

           
            int min = future.get();

           
            std::swap(sortedVec[i], sortedVec[std::find(sortedVec.begin() + i, sortedVec.end(), min) - sortedVec.begin()]);
    }

    return sortedVec;
}

int main() {
    std::vector<int> vec = { 5, 3, 8, 1, 9, 2 };

    std::vector<int> sortedVec = selectionSort(vec);

    for (int num : sortedVec) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}

