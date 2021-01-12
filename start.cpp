/*
 * 快速排序，递归与非递归
 */


#include <string>
#include <vector>
#include <iostream>
#include <stack>

using namespace std;

// 以尾部为check_val, 从begin 到 end-1进行互换, 最后check_index+1 和 end互换
int singlePartition(vector<int> &vec, int begin, int end) {
    if (begin >= end || end > vec.size()-1) {
        return begin;
    }
    int left = begin, right = end;
    int check_val = vec[end], check_index = begin;
    for (int i = begin; i < end; i++) {
        if (vec[i] < check_val) {
            swap(vec[check_index++], vec[i]);
        }
    }
    swap(vec[check_index], vec[end]);
    return check_index;
}

// 用栈存储每次begin, end
void QuickSortUnRecur(vector<int> &vec) {
    stack<int> index_stack;
    int part_index = singlePartition(vec, 0, vec.size()-1);
    index_stack.push(0);
    index_stack.push(vec.size()-1);
    while(!index_stack.empty()) {
        int end = index_stack.top(); index_stack.pop();
        int begin = index_stack.top(); index_stack.pop();
        if (begin >= end) {
            continue;
        }
        int check_index = singlePartition(vec, begin, end); 
        index_stack.push(begin);
        index_stack.push(check_index-1);
        index_stack.push(check_index+1);
        index_stack.push(end);
    }
}


// 0为check_val, 尾部先动, 参考 0 1 2， 头部先动会失败
void QuickSort(vector<int> &vec, int begin, int end) {
    if (begin >= end || end > vec.size()-1) {
        return;
    }
    int left = begin, right = end;
    int begin_val = vec[begin];
    while (left < right) {
        while (vec[right] >= begin_val && left < right) {
            right--;
        }
        while (vec[left] <= begin_val && left < right) {
            left++;
        }
        if (left < right) {
            swap(vec[left], vec[right]);
        }
    }
    swap(vec[begin], vec[left]);
    QuickSort(vec, begin, left-1);
    QuickSort(vec, right+1, end);
}

template<class T>
void OutputVec(const vector<T> &vec) {
    for (const auto &v : vec) {
        cout << v  << " ";
    }
    cout << endl;
}

int main() {
    vector<int> a = {6, 1, 2, 7, 9, 3, 4, 5, 10, 8};
    vector<int> b = {6, 1, 2, 7, 9, 3, 4, 5, 10, 8};
    vector<int> c = {1, 1};
    vector<int> d = {};

    QuickSort(a, 0, a.size()-1);
    QuickSortUnRecur(b);
    QuickSort(c, 0, c.size()-1);
    QuickSort(d, 0, d.size()-1);

    OutputVec<int>(a);
    OutputVec<int>(b);
    OutputVec<int>(c);
    OutputVec<int>(d);

    return 0;
}
