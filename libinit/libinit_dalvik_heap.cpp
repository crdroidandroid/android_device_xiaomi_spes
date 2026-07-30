/*
 * Copyright (C) 2021 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <sys/sysinfo.h>
#include <libinit_utils.h>

#include <libinit_dalvik_heap.h>

#define HEAPSTARTSIZE_PROP "dalvik.vm.heapstartsize"
#define HEAPGROWTHLIMIT_PROP "dalvik.vm.heapgrowthlimit"
#define HEAPSIZE_PROP "dalvik.vm.heapsize"
#define HEAPMINFREE_PROP "dalvik.vm.heapminfree"
#define HEAPMAXFREE_PROP "dalvik.vm.heapmaxfree"
#define HEAPTARGETUTILIZATION_PROP "dalvik.vm.heaptargetutilization"
#define FOREGROUND_HEAP_GROWTH_MULTIPLIER_PROP "dalvik.vm.foreground-heap-growth-multiplier"
#define ENABLE_TIME_BASED_GC_TRIGGER_PROP "dalvik.vm.enable_time_based_gc_trigger"
#define USEJIT_PROP "dalvik.vm.usejit"
#define JITMAXSIZE_PROP "dalvik.vm.jitmaxsize"
#define JITINITIALSIZE_PROP "dalvik.vm.jitinitialsize"
#define JITTHRESHOLD_PROP "dalvik.vm.jitthreshold"
#define PARALLEL_IMAGE_LOADING_PROP "dalvik.vm.parallel-image-loading"
#define MADVISE_VDEXFILE_SIZE_PROP "dalvik.vm.madvise.vdexfile.size"
#define MADVISE_ODEXFILE_SIZE_PROP "dalvik.vm.madvise.odexfile.size"
#define USAP_POOL_ENABLED_PROP "dalvik.vm.usap_pool_enabled"
#define USAP_POOL_SIZE_MIN_PROP "dalvik.vm.usap_pool_size_min"
#define USAP_POOL_SIZE_MAX_PROP "dalvik.vm.usap_pool_size_max"
#define USAP_REFILL_THRESHOLD_PROP "dalvik.vm.usap_refill_threshold"
#define USAP_REFILL_DELAY_MS_PROP "dalvik.vm.usap_pool_refill_delay_ms"
#define PINNER_QUOTA "persist.sys.pinner.quota_pct"

#define GB(b) (b * 1024ull * 1024 * 1024)

static const dalvik_heap_info_t dalvik_heap_info_8192 = {
    .heapstartsize = "16m",
    .heapgrowthlimit = "384m",
    .heapsize = "512m",
    .heapminfree = "4m",
    .heapmaxfree = "64m",
    .heaptargetutilization = "0.75",
    .foreground_heap_growth_multiplier = "1.0",
    .enable_time_based_gc_trigger = "true",
    .usejit = "true",
    .jitmaxsize = "256m",
    .jitinitialsize = "32m",
    .jitthreshold = "10000",
    .parallel_image_loading = "true",
    .madvise_vdexfile_size = "157286400",
    .madvise_odexfile_size = "157286400",
    .usap_pool_enabled =  "true",
    .usap_pool_size_min = "1",
    .usap_pool_size_max = " 3",
    .usap_refill_threshold = "1",
    .usap_pool_refill_delay_ms = "3000",
};

static const dalvik_heap_info_t dalvik_heap_info_6144 = {
    .heapstartsize = "16m",
    .heapgrowthlimit = "256m",
    .heapsize = "512m",
        .heapminfree = "4m",
    .heapmaxfree = "48m",
    .heaptargetutilization = "0.75",
    .foreground_heap_growth_multiplier = "1.0",
    .enable_time_based_gc_trigger = "true",
    .usejit = "true",
    .jitmaxsize = "256m",
    .jitinitialsize = "32m",
    .jitthreshold = "10000",
    .parallel_image_loading = "true",
    .madvise_vdexfile_size = "104857600",
    .madvise_odexfile_size = "104857600",
    .usap_pool_enabled =  "true",
    .usap_pool_size_min = "1",
    .usap_pool_size_max = " 2",
    .usap_refill_threshold = "1",
    .usap_pool_refill_delay_ms = "3000",
};

static const dalvik_heap_info_t dalvik_heap_info_4096 = {
    .heapstartsize = "12m",
    .heapgrowthlimit = "256m",
    .heapsize = "512m",
    .heapminfree = "4m",
    .heapmaxfree = "32m",
    .heaptargetutilization = "0.75",
    .foreground_heap_growth_multiplier = "0.5",
    .usejit = "true",
    .jitmaxsize = "128m",
    .jitinitialsize = "16m",
    .jitthreshold = "15000",
    .madvise_vdexfile_size = "104857600",
    .madvise_odexfile_size = "104857600",
    .usap_pool_enabled =  "true",
    .usap_pool_size_min = "1",
    .usap_pool_size_max = " 2",
    .usap_refill_threshold = "1",
    .usap_pool_refill_delay_ms = "3000",
    .pinner_quota = "8",
};

void set_dalvik_heap() {
    struct sysinfo sys;
    const dalvik_heap_info_t *dhi;

    sysinfo(&sys);

    if (sys.totalram > GB(7))
        dhi = &dalvik_heap_info_8192;
    else if (sys.totalram > GB(5))
        dhi = &dalvik_heap_info_6144;
    else
        dhi = &dalvik_heap_info_4096;

    property_override(HEAPSTARTSIZE_PROP, dhi->heapstartsize);
    property_override(HEAPGROWTHLIMIT_PROP, dhi->heapgrowthlimit);
    property_override(HEAPSIZE_PROP, dhi->heapsize);
    property_override(HEAPTARGETUTILIZATION_PROP, dhi->heaptargetutilization);
    property_override(HEAPMINFREE_PROP, dhi->heapminfree);
    property_override(HEAPMAXFREE_PROP, dhi->heapmaxfree);
    property_override(FOREGROUND_HEAP_GROWTH_MULTIPLIER_PROP, dhi->foreground_heap_growth_multiplier);
    property_override(USEJIT_PROP, dhi->usejit);
    property_override(JITMAXSIZE_PROP, dhi->jitmaxsize);
    property_override(JITINITIALSIZE_PROP, dhi->jitinitialsize);
    property_override(JITTHRESHOLD_PROP, dhi->jitthreshold);
    property_override(MADVISE_VDEXFILE_SIZE_PROP, dhi->madvise_vdexfile_size);
    property_override(MADVISE_ODEXFILE_SIZE_PROP, dhi->madvise_odexfile_size);
    property_override(USAP_POOL_ENABLED_PROP, dhi->usap_pool_enabled);
    property_override(USAP_POOL_SIZE_MIN_PROP, dhi->usap_pool_size_min);
    property_override(USAP_POOL_SIZE_MAX_PROP, dhi->usap_pool_size_max);
    property_override(USAP_REFILL_THRESHOLD_PROP, dhi->usap_refill_threshold);
    property_override(USAP_REFILL_DELAY_MS_PROP, dhi->usap_pool_refill_delay_ms);
  if (sys.totalram > GB(5)) {
    property_override(ENABLE_TIME_BASED_GC_TRIGGER_PROP, dhi->enable_time_based_gc_trigger);
    property_override(PARALLEL_IMAGE_LOADING_PROP, dhi->parallel_image_loading);
    }
  else if (sys.totalram < GB(5)) {
    property_override(PINNER_QUOTA, dhi->pinner_quota);
    }
}
