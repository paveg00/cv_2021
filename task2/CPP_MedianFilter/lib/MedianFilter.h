#include <iostream>
#include <vector>

namespace my_cv {
    class MedianFilter {
    public:
        MedianFilter() = default;
        ~MedianFilter() = default;
        std::vector<std::vector<int>> process_easy(const std::vector<std::vector<int>> &mat, int radius);

        std::vector<std::vector<int>> process(const std::vector<std::vector<int>> &mat);

        std::vector<std::vector<int>> process_medium(const std::vector<std::vector<int>> &mat, int radius);

        std::vector<std::vector<int>> process_hard(const std::vector<std::vector<int>> &mat, int radius);
    };
}