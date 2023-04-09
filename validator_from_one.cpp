#include <iostream>
#include <thread>
#include <vector>
#include <ctime>

using namespace std;

uint64_t bs = 0;

void check(uint64_t bound, uint64_t submin, uint64_t submax)
{
    for (uint64_t i = submin; i <= submax; i++) {
        uint64_t x = i;

        while (x != 1) {
            if (x < bound) break;
            if (x & 1) x = 3 * x + 1;
            else x >>= 1;
        }
    }
    return;
}

void arange(uint64_t mmin, uint64_t mmax, uint32_t thnum)
{
    uint64_t step, submin, submax, nnum;
    vector<thread> thds;

    nnum = mmax - mmin + 1;
    if (thnum > nnum) thnum = nnum;

    step = nnum / thnum;
    submin = mmin;
    for (uint32_t i = 1; i <= thnum; i++) {
        if (i == thnum) submax = mmax;
        else submax = submin + step - 1;

        thds.push_back(thread(check, mmin, submin, submax));

        submin = submax + 1;
    }

    for (uint32_t i = 0; i < thnum; i++)
        thds[i].join();
}

int main()
{
    uint64_t mmin;
    uint32_t thnum;

    printf("Assume any number less than Min is validated.\n");
    printf("Batch size(around 10,000,000 recommended): "); scanf("%llu", &bs);
    printf("Min: "); scanf("%llu", &mmin);
    printf("Threads: "); scanf("%u", &thnum);
    
    uint64_t left = mmin, right;
    while (true) {
        right = left + bs - 1;
        clock_t start, end;
        start = clock();
        arange(left, right, thnum);
        end = clock();
        printf("%llu to %llu: Pass! %lf sec\n", left, right, double(end-start)/CLOCKS_PER_SEC);

        left = right + 1;
    }

    fflush(stdin);
    getchar();
    return 0;
}