#include <MedianFilter.h>

std::vector<std::vector<int>> example{
        {1, 1, 1, 1, 1, 1},
        {2, 2, 2, 2, 2, 2},
        {3, 3, 3, 3, 3, 3},
        {4, 4, 4, 4, 4, 4},
        {5, 5, 5, 5, 5, 5},
};
std::vector<std::vector<int>> example2{
        {62,  47,  89, 78,  45,  133, 221, 44, 55,  74},
        {74,  66,  34, 33,  112, 49,  55,  49, 79,  77},
        {63,  83,  87, 130, 228, 59,  62,  78, 161, 202},
        {100, 44,  65, 69,  0,   88,  88,  65, 51,  71},
        {72,  44,  64, 77,  90,  118, 196, 34, 65,  166},
        {83,  67,  59, 121, 216, 76,  58,  41, 46,  40},
        {77,  74,  52, 98,  201, 7,   52,  91, 64,  52},
        {69,  68,  90, 73,  19,  76,  80,  54, 41,  55},
        {71,  77,  62, 67,  50,  77,  80,  66, 65,  66},
        {64,  113, 25, 73,  89,  92,  171, 80, 57,  29},
};


void Print(const std::vector<std::vector<int>> &mat) {
    for (auto &row: mat) {
        std::cout << std::endl;
        for (const int &el: row) {
            std::cout << el << ", ";
        }
    }
    std::cout << std::endl;
}

int main() {
    auto filter = my_cv::MedianFilter();
    Print(example);
//    Print(filter.process(example));
//    Print(filter.process_easy(example, 0));
//    Print(filter.process_easy(example, 1));
//    Print(filter.process_easy(example, 2));
//    Print(filter.process_easy(example2, 0));
//    Print(filter.process_easy(example2, 1));
    Print(filter.process_easy(example2, 2));
//    Print(filter.process_medium(example, 0));
//    Print(filter.process_medium(example, 1));
//    Print(filter.process_medium(example, 2));
//    Print(filter.process_medium(example2, 0));
//    Print(filter.process_medium(example2, 1));
//    Print(filter.process_medium(example2, 2));
//    Print(filter.process_hard(example, 0));
//    Print(filter.process_hard(example, 1));
//    Print(filter.process_hard(example, 2));
//    Print(filter.process_hard(example2, 0));
//    Print(filter.process_hard(example2, 1));
    Print(filter.process_hard(example2, 2));
    return 0;
}
