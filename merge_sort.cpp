/*
 * 归并，递归与非递归
 * 递归， divide and conquer, 分散至长度为1的数组，递归两两合并
 * 非递归，step从1开始2倍递增，左右数组融合，融合后数组与原数组交换
 */


#include <string>
#include <vector>
#include <iostream>

#include "util.h"

using namespace std;

void Merge(vector<int> &vec, int begin, int slice, int end) {
    vector<int> left_vec(vec.begin() + begin, vec.begin() + slice + 1);
    vector<int> right_vec(vec.begin() + slice + 1, vec.begin() + end + 1);
    int left_index = 0, right_index = 0;
    for (int index = begin; index <= end; index++) {
        if (left_index < left_vec.size() && right_index < right_vec.size()) {
            if (left_vec[left_index] < right_vec[right_index]) {
                vec[index] = left_vec[left_index++];
            } else {
                vec[index] = right_vec[right_index++];
            }
        }
        else {
            if (left_index == left_vec.size()) {
                vec[index] = right_vec[right_index++];
            } else {
                vec[index] = left_vec[left_index++];
            }
        }
    }
}


void MergeSort(vector<int> &vec, int begin, int end) {
    if (begin >= end || end >= vec.size())  {
        return;
    }
    int slice = (begin+end) / 2;
    MergeSort(vec, begin, slice);
    MergeSort(vec, slice+1, end);
    Merge(vec, begin, slice, end);
}

void MergeSortUnRecur(vector<int> &vec, int begin, int end) {
    vector<int> sorted_vec(end - begin + 1, 0);
    for (int step = 1; step < end+1; step *= 2) {
        for (int index = 0; index <= end; index += 2*step) {
            int left = index, mid = min(index+step, end+1), right = min(index + 2*step, end+1);
            // 左包含右不包含
            int start1 = left, end1 = mid;
            int start2 = mid, end2 = right;
            int sorted_index = left;
            while (start1 < end1 && start2 < end2)
                sorted_vec[sorted_index++] = vec[start1] < vec[start2] ? vec[start1++] : vec[start2++];
            while (start1 < end1)
                sorted_vec[sorted_index++] = vec[start1++];
            while(start2 < end2)
                sorted_vec[sorted_index++] = vec[start2++];
        }
        OutputVec<int>(sorted_vec);
        vec.swap(sorted_vec);
    }

}

int main() {
    vector<int> a = {6, 1, 2, 7, 9, 3, 4, 5, 10, 8};
    vector<int> b = {6, 1, 2, 7, 9, 3, 4, 5, 10, 8};
    vector<int> c = {1, 1};
    vector<int> d = {};

    MergeSort(a, 0, a.size()-1);
    MergeSortUnRecur(b, 0, b.size()-1);
    //OutputVec<int>(a);
    //OutputVec<int>(b);

    return 0;

}
