# ROM source patches

color="\033[0;32m"
end="\033[0m"

echo -e "${color}Applying patches safely...${end}"
sleep 1

echo -e "${color}cloning audio HAL ${end}"
rm -rf hardware/qcom-caf/sm8250/audio
git clone https://github.com/LineageOS/android_hardware_qcom_audio.git -b lineage-23.2-caf-sm8250 hardware/qcom-caf/sm8250/audio

echo -e "${color}cloning display HAL ${end}"
rm -rf hardware/qcom-caf/sm8250/display
git clone https://github.com/LineageOS/android_hardware_qcom_display.git -b lineage-23.2-caf-sm8250 hardware/qcom-caf/sm8250/display

if [ -f hardware/google/pixel/kernel_headers/Android.bp ]; then
    rm -rf hardware/google/pixel/kernel_headers/Android.bp
fi
if [ -f hardware/lineage/interfaces/health/aidl/default/Android.bp ]; then
    rm -fr hardware/lineage/interfaces/health/aidl/default/Android.bp
fi
if [ -f device/qcom/sepolicy_vndr/legacy-um/qva/vendor/bengal/legacy-ims/hal_rcsservice.te ]; then
    if ! cmp -s device/qcom/sepolicy_vndr/legacy-um/qva/vendor/bengal/legacy-ims/hal_rcsservice.te device/qcom/sepolicy_vndr/legacy-um/qva/vendor/bengal/ims/hal_rcsservice.te; then
        echo -e "${color}Switching back to legacy imsrcsd sepolicy...${end}"
        rm -rf device/qcom/sepolicy_vndr/legacy-um/qva/vendor/bengal/ims/imsservice.te
        cp device/qcom/sepolicy_vndr/legacy-um/qva/vendor/bengal/legacy-ims/hal_rcsservice.te device/qcom/sepolicy_vndr/legacy-um/qva/vendor/bengal/ims/hal_rcsservice.te
    fi
fi
if grep -q '"qti_kernel_headers"' vendor/lineage/build/soong/Android.bp 2>/dev/null; then
    echo -e "${color}Patching vendor/lineage qti_kernel_headers...${end}"
    sed -i 's/"qti_kernel_headers"/"qti_kernel_headers_old"/g' vendor/lineage/build/soong/Android.bp
fi
if [ -f kernel/xiaomi/spes/Android.bp ]; then
    if grep -q 'name: "qti_kernel_headers"' kernel/xiaomi/spes/Android.bp; then
        echo -e "${color}Fixing duplicate qti_kernel_headers in kernel source...${end}"
        sed -i 's/name: "qti_kernel_headers"/name: "qti_kernel_headers_device"/g' kernel/xiaomi/spes/Android.bp
    fi
fi
if [ ! -d hardware/qcom-caf/sm8250/media ]; then
    echo -e "${color}cloning media HAL...${end}"
    git clone https://github.com/LineageOS/android_hardware_qcom_media.git -b lineage-23.2-caf-sm8250 hardware/qcom-caf/sm8250/media
fi
if [ -f vendor/xiaomi/spes/Android.bp ]; then
    if grep -q '"hardware/qcom-caf/sm8250/media"' vendor/xiaomi/spes/Android.bp || grep -q '"hardware/qcom/sm7250/display"' vendor/xiaomi/spes/Android.bp; then
        echo -e "${color}Purging conflicting hardware namespaces from auto-generated vendor blueprint...${end}"
        sed -i '/"hardware\/qcom-caf\/sm8250\/media"/d' vendor/xiaomi/spes/Android.bp
        sed -i '/"hardware\/qcom\/sm7250\/display"/d' vendor/xiaomi/spes/Android.bp
    fi
fi
if [ -f vendor/xiaomi/spes/Android.bp ]; then
    if ! grep -q '"hardware/qcom-caf/sm8250"' vendor/xiaomi/spes/Android.bp; then
        echo -e "${color}Adding sm8250 display namespace to vendor imports...${end}"
        sed -i '/"device\/xiaomi\/spes",/a \        "hardware/qcom-caf/sm8250",' vendor/xiaomi/spes/Android.bp
    fi
fi
SPEC_MK=$(find device/xiaomi/spes/ -name "*.mk" | grep -E "lineage_spes.mk|spes.mk" | head -n 1)
if [ -f "$SPEC_MK" ]; then
    if ! grep -q "prebuilts/misc/protobuf_vendorcompat" "$SPEC_MK"; then
        echo -e "${color}Adding protobuf_vendorcompat to PRODUCT_SOURCE_ROOT_DIRS...${end}"
        echo -e "\nPRODUCT_SOURCE_ROOT_DIRS += prebuilts/misc/protobuf_vendorcompat" >> "$SPEC_MK"
    fi
fi
AUDIO_BP="hardware/interfaces/audio/common/all-versions/default/Android.bp"
if [ -f "$AUDIO_BP" ]; then
    if grep -q 'true: \["-include' "$AUDIO_BP"; then
        echo -e "${color}Patching select block Boolean-to-String typo in audio blueprint...${end}"
        sed -i 's/true: \["-include/\"true\": \["-include/g' "$AUDIO_BP"
    fi
fi
if [ -f "$AUDIO_BP" ]; then
    if grep -q 'cflags: select(soong_config_variable("android_hardware_audio", "skip_speaker_layout_channel_mask_field")' "$AUDIO_BP"; then
        echo -e "${color}Scrubbing invalid cflags select block in hardware/interfaces audio blueprint...${end}"
        sed -i '/cflags: select(soong_config_variable("android_hardware_audio", "skip_speaker_layout_channel_mask_field")/,/})/d' "$AUDIO_BP"
    fi
fi
echo -e "${color}All patches verified/applied cleanly!${end}"
