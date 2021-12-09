#include <algorithm>
#include "MedianFilter.h"

#include "assert.h"

/*
 * Методы класса
 */

enum BorderType {
    BORDER_CONSTANT,
    BORDER_REPLICATE,
    BORDER_REFLECT
};

enum Op {
    ADD,
    SUB
};

struct ExtendedMatrix {
    ExtendedMatrix(const std::vector<std::vector<int>> &_matrix, int R, BorderType border_type);

    int get(int i, int j);

    const std::vector<std::vector<int>> &matrix;
    int n;
    int m;
    int n_r;
    int m_r;
    int R;
    BorderType border_type;
};

ExtendedMatrix::ExtendedMatrix(const std::vector<std::vector<int>> &_matrix, int R, BorderType border_type) : matrix(
        _matrix), R(R), border_type(border_type), n(matrix.size()), m(matrix[0].size()), n_r(n + R), m_r(m + R) {}

int ExtendedMatrix::get(int i, int j) {
    assert(i >= -R && i < n_r && j >= -R && j < m_r);
//        i = std::abs(i);
//        j = std::abs(j);
    if (i < 0 || j < 0 || i >= n || j >= m) {
        switch (border_type) {
            case BORDER_CONSTANT:
                return 0;
            case BORDER_REPLICATE: {
                int i_res = i < 0 ? 0 : (i >= n ? n - 1 : i);
                int j_res = j < 0 ? 0 : (j >= m ? m - 1 : j);
                return matrix[i_res][j_res];
            }
            case BORDER_REFLECT: {
                int i_res = i < 0 ? std::abs(i) : (i >= n ? i - n : i);
                int j_res = j < 0 ? std::abs(j) : (j >= m ? j - m : j);
                return matrix[i_res][j_res];
            }
        }
    }
    return matrix[i][j];
}

struct Histogram {
    Histogram();

    void Add(const Histogram &snd_histogram, Op op);

    void Add(const std::vector<int> &elems, Op op);

    void Add(int elem, Op op);

    int ReleaseLTMDN(int elems);

    int GetMedian(int elems);

    std::vector<int> hist;
    static constexpr int size = 256;
    int ltmdn{0};
    int median{0};
};

Histogram::Histogram() : hist(size, 0) {}

void Histogram::Add(const Histogram &snd_histogram, Op op) {
    for (int i = 0; i < size; ++i) {
        if (op == ADD) {
            hist[i] += snd_histogram.hist[i];
        } else {
            hist[i] -= snd_histogram.hist[i];
        }
    }
}

void Histogram::Add(const std::vector<int> &elems, Op op) {
    for (const auto &elem: elems) {
        if (op == ADD) ++hist[elem]; else --hist[elem];
        if (median > elem) {
            if (op == ADD) ++ltmdn; else --ltmdn;;
        }
    }
}

int Histogram::ReleaseLTMDN(int elems) {
    int median_cnt = elems / 2 + 1;
    while (!(ltmdn < median_cnt && hist[median] + ltmdn >= median_cnt)) {
        if (ltmdn >= median_cnt) {
            --median;
            ltmdn -= hist[median];
        } else {
            ltmdn += hist[median];
            ++median;
        }
    }
    return median;
}

void Histogram::Add(int elem, Op op) {
    if (op == ADD) ++hist[elem]; else --hist[elem];
}

int Histogram::GetMedian(int elems) {
    ltmdn = 0;
    median = 0;
    return ReleaseLTMDN(elems);
}

namespace my_cv {

    std::vector<std::vector<int>> MedianFilter::process(const std::vector<std::vector<int>> &mat) {
        auto res = mat;
        for (auto &row: res) {
            for (int &el: row) {
                ++el;
            }
        }
        return res;
    }


    std::vector<std::vector<int>> MedianFilter::process_easy(const std::vector<std::vector<int>> &mat, int radius) {
        int n = mat.size();
        int m = mat[0].size();
        std::vector<std::vector<int>> res(n, std::vector<int>(m, 0));
        auto extended_matrix = ExtendedMatrix(mat, radius, BORDER_REPLICATE);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                std::vector<int> temp;
                for (int ki = -radius; ki <= radius; ++ki) {
                    for (int kj = -radius; kj <= radius; ++kj) {
                        temp.emplace_back(extended_matrix.get(i + ki, j + kj));
                    }
                }
                auto m = temp.begin() + temp.size() / 2;
                std::nth_element(temp.begin(), m, temp.end());
                res[i][j] = temp[temp.size() / 2];
            }
        }
        return res;
    }

    std::vector<std::vector<int>> MedianFilter::process_medium(const std::vector<std::vector<int>> &mat, int radius) {
        int n = mat.size();
        int m = mat[0].size();
        int D = radius * 2 + 1;
        std::vector<std::vector<int>> res(n, std::vector<int>(m, 0));
        auto extended_matrix = ExtendedMatrix(mat, radius, BORDER_REPLICATE);
        for (int i = 0; i < n; ++i) {
            std::vector<int> temp;
            for (int ki = -radius; ki <= radius; ++ki) {
                for (int kj = -radius; kj <= radius; ++kj) {
                    temp.emplace_back(extended_matrix.get(i + ki, kj));
                }
            }
            Histogram histogram;
            histogram.Add(temp, Op::ADD);
            res[i][0] = histogram.ReleaseLTMDN(D * D);
            for (int j = 1; j < m; ++j) {
                std::vector<int> temp2;
                for (int ki = -radius; ki <= radius; ++ki) {
                    temp2.emplace_back(extended_matrix.get(i + ki, j - radius - 1));
                }
                histogram.Add(temp2, SUB);
                temp2.clear();
                for (int ki = -radius; ki <= radius; ++ki) {
                    temp2.emplace_back(extended_matrix.get(i + ki, j + radius));
                }
                histogram.Add(temp2, ADD);
                res[i][j] = histogram.ReleaseLTMDN(D * D);
            }
        }
        return res;
    }

    std::vector<std::vector<int>> MedianFilter::process_hard(const std::vector<std::vector<int>> &mat, int radius) {
        int n = mat.size();
        int m = mat[0].size();
        int D = radius * 2 + 1;
        std::vector<std::vector<int>> res(n, std::vector<int>(m, 0));
        auto extended_matrix = ExtendedMatrix(mat, radius, BORDER_REPLICATE);
        std::vector<Histogram> hs(m + radius * 2);
        auto get_hs = [&hs, radius, m](int i) -> Histogram & {
            assert(i >= -radius && i < m + radius);
            return hs[i + radius];
        };
        Histogram main_hist;
        // init hs
        for (int j = -radius; j < m + radius; ++j) {
            std::vector<int> temp;
            for (int ki = -radius; ki <= radius; ++ki) {
                temp.emplace_back(extended_matrix.get(ki, j));
            }
            get_hs(j).Add(temp, ADD);
        }
        { // process first row
            for (int j = -radius; j <= radius; ++j) {
                main_hist.Add(get_hs(j), ADD);
            }
            res[0][0] = main_hist.GetMedian(D * D);
            for (int j = 1; j < m; ++j) {
                main_hist.Add(get_hs(j + radius), ADD);
                main_hist.Add(get_hs(j - radius - 1), SUB);
                res[0][j] = main_hist.GetMedian(D * D);
            }
        }
        for (int i = 1; i < n; ++i) {
            main_hist = Histogram();
            // init H for the next row
            for (int j = -radius; j <= radius; ++j) {
                get_hs(j).Add(extended_matrix.get(i - radius - 1, j), SUB);
                get_hs(j).Add(extended_matrix.get(i + radius, j), ADD);
                main_hist.Add(get_hs(j), ADD);
            }
            res[i][0] = main_hist.GetMedian(D * D);

            for (int j = 1; j < m; ++j) {
                get_hs(j + radius).Add(extended_matrix.get(i - radius - 1, j + radius), SUB);
                get_hs(j + radius).Add(extended_matrix.get(i + radius, j + radius), ADD);
                main_hist.Add(get_hs(j + radius), ADD);
                main_hist.Add(get_hs(j - radius - 1), SUB);
                res[i][j] = main_hist.GetMedian(D * D);
            }
        }
        return res;
    }

}