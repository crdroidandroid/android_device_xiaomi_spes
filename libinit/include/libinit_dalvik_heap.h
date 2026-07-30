/*
 * Copyright (C) 2021 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef LIBINIT_DALVIK_HEAP_H
#define LIBINIT_DALVIK_HEAP_H

#include <string>

typedef struct dalvik_heap_info {
    std::string heapstartsize;
    std::string heapgrowthlimit;
    std::string heapsize;
    std::string heapminfree;
    std::string heapmaxfree;
    std::string heaptargetutilization;
    std::string foreground_heap_growth_multiplier;
    std::string enable_time_based_gc_trigger;
    std::string usejit;
    std::string jitmaxsize;
    std::string jitinitialsize;
    std::string jitthreshold;
    std::string parallel_image_loading;
    std::string madvise_vdexfile_size;
    std::string madvise_odexfile_size;
    std::string usap_pool_enabled;
    std::string usap_pool_size_min;
    std::string usap_pool_size_max;
    std::string usap_refill_threshold;
    std::string usap_pool_refill_delay_ms;
    std::string pinner_quota;
} dalvik_heap_info_t;

void set_dalvik_heap(void);

#endif // LIBINIT_DALVIK_HEAP_H
