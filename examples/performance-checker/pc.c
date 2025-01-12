#define RGFW_IMPLEMENTATION
#include "RGFW.h"

#define NUMBER_OF_TESTS 1000
#define NUMBER_OF_RUNS 1000

#define MILI 1e+6
#define SEC 1e+9
#define NANO 1
#define TIME_UNIT NANO

RGFWDEF void first_test(RGFW_window* win);
RGFWDEF void second_test(RGFW_window* win);

RGFWDEF void print_timeUnit(void);

#define NO_PRINT_TEST
#define NO_PRINT_AVG

int main(void) {
    RGFW_window* win = RGFW_createWindow("name", RGFW_RECT(500, 500, 500, 500), (u64)RGFW_CENTER);

    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);


    double avgs[NUMBER_OF_TESTS * 2];
    
    u32 index;
    for (index = 0; index < NUMBER_OF_RUNS; index += 2) {
        double timing[NUMBER_OF_TESTS * 2];

        first_test(win);
        
        u32 i;
        for (i = 0; i < NUMBER_OF_TESTS * 2; i += 2) {
            double start = (double)(RGFW_getTimeNS() / TIME_UNIT);
            first_test(win);
            timing[i] = (double)(RGFW_getTimeNS() / TIME_UNIT) - start;
        }

        second_test(win);

        for (i = 1; i < NUMBER_OF_TESTS * 2; i += 2) {
            double start = (double)(RGFW_getTimeNS() / TIME_UNIT);
            second_test(win);
            timing[i] = (double)(RGFW_getTimeNS() / TIME_UNIT) - start;
        }
        
        double test1avg = 0;
        double test2avg = 0; 

        #if !defined(NO_PRINT_AVG) && !defined(NO_PRINT_TEST)
        printf("Results   test1  test2");
        print_timeUnit();
        #endif

        for (i = 0; i < NUMBER_OF_TESTS * 2; i += 2) {
            #ifndef NO_PRINT_TEST
            printf("Test %i : %f      %f", (i / 2), timing[i], timing[i + 1]);
            print_timeUnit();
            #endif

            test1avg += timing[i];
            test2avg += timing[i + 1];
        }
        
        #ifndef NO_PRINT_AVG
        printf("Average: %f      %f", (test1avg / NUMBER_OF_TESTS), (test2avg / NUMBER_OF_TESTS)); 
        print_timeUnit();
        #endif
        
        RGFW_sleep(50000000);

        avgs[index] = (test1avg / NUMBER_OF_TESTS); 
        avgs[index + 1] = (test2avg / NUMBER_OF_TESTS);
    }

    double test1avg = 0;
    double test2avg = 0;

    for (index = 0; index < NUMBER_OF_RUNS * 2; index += 2) {
        test1avg += avgs[index];
        test2avg += avgs[index + 1];
    }

    printf("Avg runs: %f      %f", (test1avg / NUMBER_OF_RUNS), (test2avg / NUMBER_OF_RUNS)); 
    print_timeUnit();
    
    printf("End test\n");
    RGFW_window_close(win);
}

void print_timeUnit(void) {
    if (TIME_UNIT == NANO)
        printf("   nanoseconds :\n");
    else if (TIME_UNIT == MILI)
        printf("    milisecondss :\n");
    else if (TIME_UNIT == SEC)
        printf("   seconds :\n");
}

void first_test(RGFW_window* win) {
    RGFW_window_checkEvent(win);
}

void second_test(RGFW_window* win) {
    RGFW_window_checkEvent(win);
}