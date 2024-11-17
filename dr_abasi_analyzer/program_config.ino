

void program_config() {
  if (start_program == 1) {
    update_time();

  }
}


void update_time() {

  static uint32_t lastSeconds = 0;
  if (sec_ != lastSeconds) {  // بررسی تغییر مقدار ثانیه‌ها
    time_show = "Time=" + String(hu_) + ":" + String(min_) + ":" + String(sec_);
    lv_label_set_text(label_time, time_show.c_str());
  }
}