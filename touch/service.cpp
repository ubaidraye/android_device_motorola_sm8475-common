/*
 * SPDX-FileCopyrightText: The LineageOS Project
 * SPDX-License-Identifier: Apache-2.0
 */

#define LOG_TAG "lineage.touch-service.moto_sm8475"

#include "TouchscreenGesture.h"

#include <android-base/logging.h>
#include <android/binder_manager.h>
#include <android/binder_process.h>

using aidl::vendor::lineage::touch::TouchscreenGesture;

int main() {
    binder_status_t status = STATUS_OK;

    ABinderProcess_setThreadPoolMaxThreadCount(0);
    std::shared_ptr<TouchscreenGesture> tg = ndk::SharedRefBase::make<TouchscreenGesture>();

    const std::string instanceTg = std::string(TouchscreenGesture::descriptor) + "/default";
    status = AServiceManager_addService(tg->asBinder().get(), instanceTg.c_str());
    CHECK_EQ(status, STATUS_OK) << "Failed to add service " << instanceTg << " " << status;

    ABinderProcess_joinThreadPool();
    return EXIT_FAILURE;  // should not reach
}
