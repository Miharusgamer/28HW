#include <iostream>
#include <future>
#include <thread>

void merge(int* arr, int l, int m, int r)
{
    int nl = m - l + 1;
    int nr = r - m;

    // ������� ��������� ��������� �� �������
    int* left = new int[nl];
    int* right = new int[nr];

    // �������� ������ �� ��������� �������
    for (int i = 0; i < nl; i++)
        left[i] = arr[l + i];
    for (int j = 0; j < nr; j++)
        right[j] = arr[m + 1 + j];

    int i = 0, j = 0;
    int k = l;  // ������ ����� �����

    while (i < nl && j < nr) {
        // ���������� ����������� �������� ������� �� ������� ������
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        }
        else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }
    // ���������� ���������� �������� ����� �����
    while (i < nl) {
        arr[k] = left[i];
        i++;
        k++;
    }
    // ���������� ���������� �������� ������ �����
    while (j < nr) {
        arr[k] = right[j];
        j++;
        k++;
    }

    // ����������� ���������� ������
    delete[] left;
    delete[] right;
}

void mergeSort(int* arr, int l, int r)
{
    if (l < r) {
        int m = l + (r - l) / 2;

        if (r - l + 1 <= 10000) {
            // ���� ������ ����� ��� ���������� �� ��������� 10000,
            // ��������� ���������� � ������� ������
            mergeSort(arr, l, m);
            mergeSort(arr, m + 1, r);
        }
        else {
            // �����, ������� ��� ��������� ������ ��� ���������� ����� � ������ �������
            std::future<void> leftFuture = std::async(std::launch::async, mergeSort, arr, l, m);
            std::future<void> rightFuture = std::async(std::launch::async, mergeSort, arr, m + 1, r);

            // ���������� ���������� ����� �������
            leftFuture.get();
            rightFuture.get();
        }

        // ���������� ����������
        merge(arr, l, m, r);
    }
}

int main()
{
    int arr[] = { 42, 17, 9, 83, 56, 25, 74, 61, 37, 89, 22, 45, 12, 68, 31, 77, 52, 19, 93, 64, 28, 87, 39, 71, 58, 14, 96, 63, 34, 81, 67, 23, 78, 51, 18, 92, 65, 29, 86, 38, 72, 59, 15, 95, 62, 33, 80, 66, 24, 79, 53, 20, 91, 46, 30, 85, 73, 60, 16, 94, 32, 82, 57, 84, 55, 21, 90, 47, 13, 76, 50, 88, 41, 27, 69, 98, 75, 11, 70, 48, 10, 97, 54, 49, 40, 26, 43, 99, 36, 44, 35 };
    int arrSize = sizeof(arr) / sizeof(arr[0]);

    // �������� mergeSort � �������������� ���������������
    std::thread t(mergeSort, arr, 0, arrSize - 1);
    t.join();

    // ������� ��������������� ������
    for (int i = 0; i < arrSize; i++)
    std::cout << arr[i] << " ";
    std::cout << std::endl;

    return 0;
}