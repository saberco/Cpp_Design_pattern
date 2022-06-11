//实例为选择不同的排序算法
#include <vector>
#include <algorithm>
#include <random>
#include <iostream>

using namespace std;

//抽象的算法类
class Sort{
public:
    virtual void sortVector(vector<int> &arr) = 0;
};
//全局函数，打印vector
void printVector(vector<int> arr){
    for(auto i:arr){
        cout<<" "<<i;
    }
    cout<<endl;
}

//两种排序策略，冒泡和快排
class BubbleSort : public Sort{
public:
    void sortVector(vector<int> &arr) override{
        cout<<"冒泡排序前：";
        printVector(arr);
        int n = arr.size();
        for(int i =0;i<n;++i){
            for(int j = 0;j<n-i-1;++j){
                if(arr[j] > arr[j+1]){
                    swap(arr[j], arr[j+1]);
                }
            }
        }
        cout<<"冒泡排序后：";
        printVector(arr);
    }
};

//插入排序，每次把数插入到合适的位置，一开始把第一个数作为已排序序列
class InserSort : public Sort{
public:
    void sortVector(vector<int> &arr) override{
        cout<<"插入排序前：";
        printVector(arr);
        int n = arr.size();
        for(int i = 1;i<n;++i){
            int key = arr[i];
            int j = i-1;
            while(j>=0 && (key < arr[j])){
                arr[j+1] = arr[j];
                j--;
            }
            arr[j+1] = key;
        }
        cout<<"插入排序后：";
        printVector(arr);
    }
};


//选择排序，每次选择最小的插入到排序序列的开头
class SelectSort : public Sort{
public:
    void sortVector(vector<int> &arr) override{
        cout<<"选择排序前：";
        printVector(arr);
        int n = arr.size();
        for(int i = 0;i<n;++i){
            int minnidx = i;
            for(int j = i+1;j<n;++j){
                if(arr[j] < arr[minnidx]){
                    minnidx = j;
                }
            }
            swap(arr[i], arr[minnidx]);
        }
        cout<<"选择排序后：";
        printVector(arr);
    }
};

class QuicSort : public Sort{
public:
    void sortVector(vector<int> &arr) override{
        cout<<"快速排序前：";
        printVector(arr);
        int n = arr.size();
        helper(arr, 0, n-1);
        cout<<"快速排序后：";
        printVector(arr);
    }

    void helper(vector<int> &arr, int left, int right){
        if(left>=right)return;
        //哨兵
        int key = arr[left];
        int i = left, j = right;
        while(i<j){
            //从右往左找到第一个比基小的数
            while(i<j && key <= arr[j])--j;
            if(i<j){
                arr[i++] = arr[j];
            }
            //从左往右找到第一个比基大的数
            while(i<j && key >= arr[i])++i;
            if(i<j){
                arr[j--] = arr[i];
            }
        }
        //把基归位
        arr[i] = key;
        helper(arr, left, i-1);
        helper(arr, i+1, right);
    }
};


//上下文
class ArrayHandler{
public:
    void sortVector(vector<int> &arr){
        return m_sort->sortVector(arr);
    }

    void setSortStrategy(Sort* sort){
        m_sort = sort;
    }
private:
    Sort* m_sort;
};

//客户端

vector<int> test_array = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25};

int main(){
    ArrayHandler handler;

    //冒泡
    Sort* pSort = new BubbleSort();
    auto rng = default_random_engine{};
    shuffle(begin(test_array), end(test_array), rng);
    handler.setSortStrategy(pSort);
    handler.sortVector(test_array);
    delete pSort;
    //选择
    pSort = new SelectSort();
    rng = default_random_engine{};
    shuffle(begin(test_array), end(test_array), rng);
    handler.setSortStrategy(pSort);
    handler.sortVector(test_array);
    delete pSort;
    //插入
    pSort = new InserSort();
    rng = default_random_engine{};
    shuffle(begin(test_array), end(test_array), rng);
    handler.setSortStrategy(pSort);
    handler.sortVector(test_array);
    delete pSort;
    //快排
    pSort = new QuicSort();
    rng = default_random_engine{};
    shuffle(begin(test_array), end(test_array), rng);
    handler.setSortStrategy(pSort);
    handler.sortVector(test_array);
    delete pSort;

    return 0;
}