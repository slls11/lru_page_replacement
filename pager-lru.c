/*
 * File: pager-lru.c
 * Author: Slav Ivavovich
 * Assignment: PA6
 * 
*/

#include <stdio.h> 
#include <stdlib.h>
#include "simulator.h"

void pageit(Pentry q[MAXPROCESSES]) { 
    /* Static vars */
    static int initialized = 0;
    static size_t tick = 1; // artificial time
    static size_t timestamps[MAXPROCESSES][MAXPROCPAGES];
    /* Local vars */
    int proc, page;
    /* initialize static vars on first run */
    if (!initialized) {
        for (proc=0; proc < MAXPROCESSES; proc++) {
            for (page=0; page < MAXPROCPAGES; page++) {
                timestamps[proc][page] = 0; 
            }
        }
        initialized = 1;
    }
    
    for(proc = 0; proc < MAXPROCESSES; proc++){
        if (q[proc].active == 1){
            //continue;
            page = (q[proc].pc / PAGESIZE);
            if (!(q[proc].pages[page]) && !(pagein(proc, page))){

                    int lru_page; size_t lru_time = 0;
                    for (int page_num = 0; page_num < MAXPROCPAGES; page_num++){ // find lru page
                        if (q[proc].pages[page_num] && (tick - timestamps[proc][page_num]) > lru_time){
                            lru_time = tick - timestamps[proc][page_num]; 
                            lru_page = page_num;
                        }
                    }
                    //printf("pageout:%d,%d\n",proc,lru_page);
                    pageout(proc, lru_page);
            }
            timestamps[proc][page] = tick;
        }
        tick++;
        //printf("TICK: %d\n", tick);
    }
}

