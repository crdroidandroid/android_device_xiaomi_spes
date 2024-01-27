/*
 * Copyright (C) 2021 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <libinit_dalvik_heap.h>
#include <libinit_variant.h>

#include "vendor_init.h"

static const variant_info_t spes_info = {
    .hwc_value = "Global",
    .sku_value = "",

    .brand = "Redmi",
    .device = "spes",
    .marketname = "Redmi Note 11",
    .model = "2201117TG",
    .name = "spes_global",
    .build_fingerprint = "Redmi/spes_global/spes:13/TKQ1.221114.001/V14.0.5.0.TGCMIXM:user/release-keys",

    .nfc = false,
};

static const variant_info_t spes_in_info = {
    .hwc_value = "India",
    .sku_value = "k7tin",

    .brand = "Redmi",
    .device = "spes",
    .marketname = "Redmi Note 11",
    .model = "2201117TI",
    .name = "spes_global",
    .build_fingerprint = "Redmi/spes_global/spes:13/TKQ1.221114.001/V14.0.5.0.TGCMIXM:user/release-keys",

    .nfc = false,
};

static const variant_info_t spesn_info = {
    .hwc_value = "",
    .sku_value = "k7tn",

    .brand = "Redmi",
    .device = "spesn",
    .marketname = "Redmi Note 11",
    .model = "2201117TY",
    .name = "spesn_global",
    .build_fingerprint = "Redmi/spesn_global/spesn:13/TKQ1.221114.001/V14.0.5.0.TGCMIXM:user/release-keys",

    .nfc = true,
};

static const std::vector<variant_info_t> variants = {
    spes_info,
    spes_in_info,
    spesn_info,
};

void vendor_load_properties() {
    search_variant(variants);
    set_dalvik_heap();
}
