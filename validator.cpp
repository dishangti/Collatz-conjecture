#include <iostream>
#include <thread>
#include <vector>
#include <ctime>
#include <mutex>

using namespace std;

mutex mtx;

void check(uint64_t submin, uint64_t submax)
{
    clock_t start, end;
    start = clock();
    for (uint64_t i = submin; i <= submax; i++) {
        uint64_t x = i;

        while (x != 1) {
            if (x & 1) x = 3 * x + 1;
            else x >>= 1;
        }
    }

    end = clock();
    mtx.lock();
    printf("%llu to %llu: Pass! %lf sec\n", submin, submax, double(end-start)/CLOCKS_PER_SEC);
    mtx.unlock();
    return;
}

int main()
{
    uint64_t mmin, mmax, step, submin, submax, nnum;
    uint32_t thnum;
    vector<thread> thds;
    
    printf("Min: "); scanf("%llu", &mmin);
    printf("Max: "); scanf("%llu", &mmax);
    printf("Threads: "); scanf("%u", &thnum);
    nnum = mmax - mmin + 1;
    if (thnum > nnum) thnum = nnum;

    step = nnum / thnum;
    submin = mmin;
    for (uint32_t i = 1; i <= thnum; i++) {
        if (i == thnum) submax = mmax;
        else submax = submin + step - 1;

        thds.push_back(thread(check, submin, submax));

        submin = submax + 1;
    }

    for (uint32_t i = 0; i < thnum; i++)
        thds[i].join();
    return 0;
}