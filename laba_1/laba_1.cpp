#include <iostream>
#include <random>
#include <time.h>
#include <math.h>
#include <cmath>
#include <chrono>

using namespace std;

class Solution {
private:
    size_t n, m;
    bool binary_search(size_t columns, long long target)
    {
        int low = 0;
        int high = n - 1;
        while (low <= high)
        {
            int mid = low + (high - low) / 2;
            // << matrix[mid][columns];
            if (matrix[mid][columns] > target)
                high = mid - 1;
            else if (matrix[mid][columns] < target)
                low = mid + 1;
            else
            {
                //cout << endl;
                return 1;
            }

            //cout << "->";
        }
        //cout << endl;
        return 0;
    }
public:
    long long** matrix;
    //n always bigger than m

    Solution(size_t n_, size_t m_) {
        n = n_;
        m = m_;
        if (n_ < m_)
        {
            m = n_;
            n = m_;
        }
        matrix = generateMatrix(n, m);
    }
    ~Solution() {
        for (size_t i = 0; i < n; i++)
        {
            delete[] matrix[i];
        }

        delete[] matrix;
    }

    bool linear_solution(long long target)
    {
        cout << "Linear solution:" << endl;
        int i = 0;
        int j = m - 1;
        bool found = 0;
        while (i != n && j != -1)
        {
            //cout << matrix[i][j];
            if (matrix[i][j] == target)
            {
                //cout << endl << target << " exists" << endl;
                //return 1;
                found = 1;
                break;
            }
            else if (matrix[i][j] > target)
                j--;
            else i++;
            //cout << "->";
        }
        if (i == n || j == -1)
            //cout << target << " does not exists" << endl;
        if (!found)
            return 0;
        else
            return 1;
    }

    bool binary_solution(long long target)
    {
        bool found = 0;
        cout << "Binary solution:" << endl;
        for (size_t columns = 0; columns < m; ++columns)
        {
            if (binary_search(columns, target) == 1)
            {
                //cout << target << " exists" << endl;
                found++;
                //return 1;
                //break;
            }

        }
        if (!found)
        {
            //cout << target << " does not exists" << endl;
        }
        else
            return 1;

        return 0;
    }


    void print()
    {
        for (size_t i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
                cout << matrix[i][j] << " ";
            cout << endl;
        }
    }
    long long** generateMatrix(size_t rows, size_t columns) {
        long long** arr = new long long* [rows];
        for (size_t i = 0; i < rows; ++i)
        {
            arr[i] = new long long[columns];
            for (size_t j = 0; j < columns; ++j)
            {
                long long resultValue = 0;
                // !i
                if (i && j) resultValue = max(arr[i - 1][j], arr[i][j - 1]);
                else if (i) resultValue = arr[i - 1][j];
                else if (j) resultValue = arr[i][j - 1];
                arr[i][j] = resultValue + rand() % 2 + 1;

            }
        }
        return arr;
    }



};

void measuring(size_t iterations)
{
    size_t n = 10000;
    size_t m = 10;
    long long target;
    for (size_t i = 0; i < 1; ++i)
    {
        Solution solution(n, m);

        target = rand() % solution.matrix[n - 1][m - 1];

        auto start = chrono::high_resolution_clock::now();
        solution.linear_solution(target);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<float> duration = end - start;
        cout << fixed << duration.count() << endl;

        auto n_start = chrono::high_resolution_clock::now();
        solution.binary_solution(target);

        auto n_end = chrono::high_resolution_clock::now();
        duration = n_end - n_start;
        cout << fixed << duration.count() << endl;
    }
}
int main()
{
    srand(time(0));
    measuring(100);

    //написать 2 решения
    //O(nlong(m)) (через бинарный поиск)
    //O(n+m) (с левого верхнего угла >tagret вниз если < target влево)
    //замерить время через chrono, во время замера отмерить время до нахождения target и время полного прохода алгоса по матрице

}

