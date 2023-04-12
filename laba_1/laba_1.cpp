#include <iostream>
#include <random>
#include <time.h>
#include <math.h>
#include <cmath>
#include <chrono>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>

using namespace std;

typedef  chrono::high_resolution_clock Clock;

class Solution {
private:
    size_t M, N;
public:
    long long** matrix;
    //n always bigger than m

    Solution() {
        M = 0;
        N = 0;
        matrix = nullptr;
    }
    ~Solution() {
        for (size_t i = 0; i < M; i++)
        {
            delete[] matrix[i];
        }
        delete[] matrix;
    }

    bool exponential_finder(long long target) {
            //std::cout << "Target: " << target << std::endl;
            long long i = 0;
            long long j = N-1;
            while (i != M && j != -1)
            {
                //std::cout << "exp:  >>{" << matrix[i][j] << "}->";
                if (matrix[i][j] == target)
                    return 1;
                long long border = 1;
                long long low, high;
                while (j-border >= 0 && matrix[i][j-border] > target) {
                    //std::cout << matrix[i][j-border] << "->";
                    border *= 2;
                }

                //low = (border) / 2 + j;
                //high = min(j+border,static_cast<long long>(N-1));
                low = max(j - border, static_cast<long long>(0));
                high = j - border / 2;
                //std::cout << std::endl;
                //std::cout << "interval: [" << matrix[i][low] << ", " << matrix[i][high] << "]\nbinary: ";           
                while (low <= high) {
                    long long mid = (high - low) / 2 + low; 
                    //std::cout << matrix[i][mid] << "->";
                    if (matrix[i][mid] == target)
                        return 1;
                    else if (target < matrix[i][mid])
                        high = mid - 1;
                    else
                        low = mid + 1;
                }       
                if (low >= 0 && high >= 0)
                    j = min(low, high);
                else if (low >= 0)
                    j = low;
                else
                    j = high;
                //std::cout << " {" << matrix[i][j] << "}"<< std::endl;
                i++;
                //std::cout << ">>" << matrix[i][j] << std::endl;
            }
            //std::cout << std::endl;
            return 0;
    }

    bool ladder_finder(long long target) {
        size_t i = 0;
        size_t j = N - 1;
        bool found = 0;
        while (i != M && j != -1)
        {
            //std::cout << matrix[i][j] << "->";
            if (matrix[i][j] == target)
            {
                found = 1;
                break;
            }
            else if (matrix[i][j] > target)
                j--;
            else i++;

        }
        return found;
    }

    bool binary_finder(long long target) {
        bool found = 0;
        if (M > N) {
            for (size_t columns = 0; columns < N && found != 1; ++columns) {  
                long long low = 0;
                long long high = M - 1;
                while (low <= high) {
                   long long mid = (high-low) / 2 + low;
                    //std::cout << matrix[mid][columns];
                    if (matrix[mid][columns] == target)
                    {
                        found = 1;
                        break;
                    }
                    else if (matrix[mid][columns] < target)
                        low = mid + 1;
                    else
                        high = mid - 1;
                }
            }
        }
        else {
            for (size_t rows = 0; rows < M && found != 1; ++rows) {
                long long low = 0;
                long long high = N - 1;
                while (low <= high) {
                    long long mid = (high-low) / 2 + low;
                    if (matrix[rows][mid] == target)
                    {
                        found = 1;
                        break;
                    }
                    else if (matrix[rows][mid] < target)
                        low = mid + 1;
                    else
                        high = mid - 1;
                }
            }
        }
        return found;
    }


    void print() {
        for (size_t i = 0; i < M; i++)
        {
            for (size_t j = 0; j < N; j++)
                cout << setw(3) << matrix[i][j] << " ";
            cout << endl;
        }
    }

    void linear_data_generation(size_t m, size_t n) {
        for (size_t i = 0; i < M; i++)
        {
            delete[] matrix[i];
        }
        delete[] matrix;

        this->M = m;
        this->N = n;
        matrix = new long long* [M];
        for (size_t i = 0; i < M; ++i)
        {
            matrix[i] = new long long[N];
            for (size_t j = 0; j < N; ++j)
            { 
                //std::cout << n / m * i + j << std::endl;
                matrix[i][j] = (N / M * i + j)*2;
            }
        }
        //matrix = arr;
    }
    void exponential_data_generation(size_t m, size_t n) {
        for (size_t i = 0; i < this->M; i++)
        {
            delete[] matrix[i];
        }
        delete[] matrix;
        this->M = m;
        this->N = n;
        matrix = new long long* [M];
        for (size_t i = 0; i < M; ++i)
        {
            matrix[i] = new long long[N];
            for (size_t j = 0; j < N; ++j)
            {
                //std::cout << n / m * i + j << std::endl;
                matrix[i][j] = (N/M * i * j) * 2;
            }
        }
        //matrix = arr;
    }


};

void measuring(size_t iterations)
{
    size_t n = 10;
    size_t m = 10;
    long long target;
    for (size_t i = 0; i < 1; ++i)
    {
        //Solution solution(n, m);





        /*
        target = rand() % solution.matrix[n - 1][m - 1];

        auto start = Clock::now();
        solution.linear_solution(target);
        auto end = Clock::now();
        chrono::duration<float> duration = end - start;
        cout << fixed << duration.count() << endl;

        auto n_start = chrono::high_resolution_clock::now();
        solution.binary_solution(target);

        auto n_end = chrono::high_resolution_clock::now();
        duration = n_end - n_start;
        cout << fixed << duration.count() << endl;*/
    }
}
int main()
{
    srand(time(0));

    Solution solution;

    size_t M = 2;
    size_t N = pow(2, 13);
    long long target_one = 2 * N + 1;
    long long target_two = 16 * N + 1;

    std::stringstream ss;
    ofstream f1("first_graph.txt");
    ofstream f2("second_graph.txt");
    std::cout << "Ladder VS Binary VS Exponential algorithms" << std::endl;
    for (int j = 0; M != pow(2,14); j++)
    {

        std::cout << "Array size: " << M << " x " << N << std::endl;
        solution.linear_data_generation(M, N);
        M *= 2;
        double duration_ladder = 0;
        double duration_binary = 0;
        double duration_exponential = 0;
        for (int i = 0; i < 100; i++)
        {
            auto start_ladder = Clock::now();
            solution.ladder_finder(target_one);
            auto end_ladder = Clock::now();

            auto start_binary = Clock::now();
            solution.binary_finder(target_one);
            auto end_binary = Clock::now();

            auto start_exponential = Clock::now();
            solution.exponential_finder(target_one);
            auto end_exponential = Clock::now();

            duration_ladder += chrono::duration_cast<chrono::microseconds>(end_ladder - start_ladder).count();
            duration_binary += chrono::duration_cast<chrono::microseconds>(end_binary - start_binary).count();
            duration_exponential += chrono::duration_cast<chrono::microseconds>(end_exponential - start_exponential).count();
        }
        duration_ladder /= 100;
        duration_binary /= 100;
        duration_exponential /= 100;
        ss << duration_ladder << " " << duration_binary << " " << duration_exponential << std::endl;
        std::cout << "Speed: " << duration_ladder << "mks " << duration_binary << "mks " << duration_exponential << "mks" << std::endl;
    }
    std::cout << std::endl;
    string temp;
    temp = ss.str();
    std::replace(temp.begin(), temp.end(), '.', ',');
    f1 << temp;
    ss.str("");

    M = 2;
    N = pow(2, 13);
    Solution first_data;
    Solution second_data;
    std::cout << "Linear VS Exponential data generations AND exponential algorihm" << std::endl;
    for (int j = 0; M != pow(2, 14); j++)
    {
        std::cout << "Array size: " << M << " x " << N << std::endl;
        first_data.linear_data_generation(M, N);
        second_data.exponential_data_generation(M, N);
        M *= 2;
        double duration_first_data = 0;
        double duration_second_data = 0;
        for (int i = 0; i < 100; i++)
        {
            auto start_first_data = Clock::now();
            first_data.exponential_finder(target_one);
            auto end_first_data = Clock::now();

            auto start_second_data = Clock::now();
            second_data.exponential_finder(target_two);
            auto end_second_data = Clock::now();

            duration_first_data += chrono::duration_cast<chrono::microseconds>(end_first_data - start_first_data).count();
            duration_second_data += chrono::duration_cast<chrono::microseconds>(end_second_data - start_second_data).count();
        }
        duration_first_data /= 100;
        duration_second_data /= 100;
        ss << duration_first_data << " " << duration_second_data << std::endl;
        std::cout << "Speed: " << duration_first_data << "mks " << duration_second_data << "mks" << std::endl;
    }
    temp;
    temp = ss.str();
    std::replace(temp.begin(), temp.end(), '.', ',');
    f2 << temp;
    ss.clear();

    f1.close();
    f2.close();
}

