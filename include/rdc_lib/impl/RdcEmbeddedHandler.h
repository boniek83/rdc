/*
Copyright (c) 2020 - present Advanced Micro Devices, Inc. All rights reserved.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
#ifndef INCLUDE_RDC_LIB_IMPL_RDCEMBEDDEDHANDLER_H_
#define INCLUDE_RDC_LIB_IMPL_RDCEMBEDDEDHANDLER_H_

#include <future>  // NOLINT(build/c++11)
#include "rdc_lib/RdcHandler.h"
#include "rdc_lib/RdcGroupSettings.h"
#include "rdc_lib/RdcMetricFetcher.h"
#include "rdc_lib/RdcCacheManager.h"
#include "rdc_lib/RdcMetricsUpdater.h"
#include "rdc_lib/RdcWatchTable.h"
#include "rdc_lib/RdcModuleMgr.h"
#include "rdc_lib/RdcNotification.h"

namespace amd {
namespace rdc {

class RdcEmbeddedHandler: public RdcHandler {
 public:
    // Job API
    rdc_status_t rdc_job_start_stats(rdc_gpu_group_t groupId,
                        const char job_id[64], uint64_t update_freq) override;
    rdc_status_t rdc_job_get_stats(const char jobId[64],
                rdc_job_info_t* p_job_info) override;
    rdc_status_t rdc_job_stop_stats(const char job_id[64]) override;
    rdc_status_t rdc_job_remove(const char job_id[64]) override;
    rdc_status_t rdc_job_remove_all() override;

    // Discovery API
    rdc_status_t rdc_device_get_all(
        uint32_t gpu_index_list[RDC_MAX_NUM_DEVICES], uint32_t* count) override;
    rdc_status_t rdc_device_get_attributes(uint32_t gpu_index,
        rdc_device_attributes_t* p_rdc_attr) override;

    // Group API
    rdc_status_t rdc_group_gpu_create(rdc_group_type_t type,
                const char* group_name,
                rdc_gpu_group_t* p_rdc_group_id) override;
    rdc_status_t rdc_group_gpu_add(rdc_gpu_group_t groupId,
                uint32_t gpu_index) override;
    rdc_status_t rdc_group_field_create(uint32_t num_field_ids,
        rdc_field_t* field_ids, const char* field_group_name,
        rdc_field_grp_t* rdc_field_group_id) override;
    rdc_status_t rdc_group_field_get_info(
        rdc_field_grp_t rdc_field_group_id,
        rdc_field_group_info_t* field_group_info) override;
    rdc_status_t rdc_group_gpu_get_info(rdc_gpu_group_t p_rdc_group_id,
        rdc_group_info_t* p_rdc_group_info) override;
    rdc_status_t rdc_group_get_all_ids(
            rdc_gpu_group_t group_id_list[], uint32_t* count) override;
    rdc_status_t rdc_group_field_get_all_ids(
            rdc_field_grp_t field_group_id_list[], uint32_t* count) override;
    rdc_status_t rdc_group_gpu_destroy(
        rdc_gpu_group_t p_rdc_group_id) override;
    rdc_status_t rdc_group_field_destroy(
        rdc_field_grp_t rdc_field_group_id) override;

    // Field API
    rdc_status_t rdc_field_watch(rdc_gpu_group_t group_id,
        rdc_field_grp_t field_group_id, uint64_t update_freq,
        double max_keep_age, uint32_t max_keep_samples) override;
    rdc_status_t rdc_field_get_latest_value(uint32_t gpu_index,
        rdc_field_t field, rdc_field_value* value) override;
    rdc_status_t rdc_field_get_value_since(uint32_t gpu_index,
        rdc_field_t field, uint64_t since_time_stamp,
        uint64_t *next_since_time_stamp, rdc_field_value* value) override;
    rdc_status_t rdc_field_unwatch(rdc_gpu_group_t group_id,
        rdc_field_grp_t field_group_id) override;
    // Diagnostic API
    rdc_status_t rdc_diagnostic_run(
        rdc_gpu_group_t group_id,
        rdc_diag_level_t level,
        rdc_diag_response_t* response) override;
    rdc_status_t rdc_test_case_run(
        rdc_gpu_group_t group_id,
        rdc_diag_test_cases_t test_case,
        rdc_diag_test_result_t* result) override;

    // Control API
    rdc_status_t rdc_field_update_all(uint32_t wait_for_update) override;

    explicit RdcEmbeddedHandler(rdc_operation_mode_t op_mode);
    ~RdcEmbeddedHandler();

 private:
    rdc_status_t get_gpu_gauges(rdc_gpu_gauges_t* gpu_gauges);
    RdcGroupSettingsPtr group_settings_;
    RdcCacheManagerPtr cache_mgr_;
    RdcMetricFetcherPtr metric_fetcher_;
    RdcModuleMgrPtr rdc_module_mgr_;
    RdcNotificationPtr rdc_notif_;
    RdcWatchTablePtr watch_table_;
    RdcMetricsUpdaterPtr metrics_updater_;
    std::future<void> updater_;
};

}  // namespace rdc
}  // namespace amd

extern "C" {
    amd::rdc::RdcHandler *make_handler(rdc_operation_mode_t op_mode);
}

#endif  // INCLUDE_RDC_LIB_IMPL_RDCEMBEDDEDHANDLER_H_
