#ifndef PC_MONITOR_PAGE_H
#define PC_MONITOR_PAGE_H

#include <lvgl.h>
#include <memory>
#include <functional>

class PcMonitorPage {
public:
    PcMonitorPage();
    ~PcMonitorPage();

    // Create the monitor page UI
    void Create(lv_obj_t* parent, int width, int height);

    // Update with new PC stats (cJSON format from MQTT)
    void UpdateStats(const cJSON* root);

    // Show/hide the page
    void Show();
    void Hide();
    bool IsVisible() const { return visible_; }

    // Set callback when user wants to switch back to chat
    using SwitchCallback = std::function<void()>;
    void OnSwitchToChat(SwitchCallback cb) { on_switch_ = std::move(cb); }

private:
    bool visible_ = false;
    lv_obj_t* page_ = nullptr;
    lv_obj_t* parent_ = nullptr;

    // UI elements
    lv_obj_t* cpu_bar_ = nullptr;
    lv_obj_t* mem_bar_ = nullptr;
    lv_obj_t* gpu_bar_ = nullptr;
    lv_obj_t* disk_bar_ = nullptr;
    lv_obj_t* cpu_temp_label_ = nullptr;
    lv_obj_t* gpu_temp_label_ = nullptr;
    lv_obj_t* mem_label_ = nullptr;
    lv_obj_t* net_label_ = nullptr;
    lv_obj_t* fan_label_ = nullptr;
    lv_obj_t* battery_label_ = nullptr;
    lv_obj_t* time_label_ = nullptr;
    lv_obj_t* title_label_ = nullptr;

    SwitchCallback on_switch_;

    // Helper to create a progress bar with label
    lv_obj_t* CreateProgressRow(lv_obj_t* parent, const char* icon, const char* label_text,
                                lv_obj_t** out_bar, lv_obj_t** out_value_label);

    // Format helpers
    static const char* FormatBytes(int64_t bytes, char* buf, size_t bufsize);
    static const char* FormatSpeed(int kbps, char* buf, size_t bufsize);
    static const char* FormatPercent(float pct, char* buf, size_t bufsize);
};
#endif  // PC_MONITOR_PAGE_H