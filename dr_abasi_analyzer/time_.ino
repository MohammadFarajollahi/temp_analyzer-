
void timer_() {

  lv_style_init(&style_clock);
  lv_style_set_text_font(&style_clock, &lv_font_unscii_16);        // تنظیم فونت
  lv_style_set_bg_color(&style_clock, lv_color_hex(0xFFFFFF));    // رنگ پس‌زمینه لیبل‌ها (خاکستری تیره)
  lv_style_set_text_color(&style_clock, lv_color_hex(0xFFFFFF));  // رنگ متن لیبل‌ها (سفید)


  label_time = lv_label_create(lv_scr_act());
  lv_obj_add_style(label_time, &style_clock, 0);
  lv_obj_align(label_time, LV_ALIGN_TOP_LEFT, 5, 90);  // موقعیت دکمه پاک کردن
  //lv_obj_set_size(label_time, 130, 40);
  time_show = "Time=" + String(hu_) + ":" + String(min_) + ":" + String(sec_);
  lv_label_set_text(label_time, time_show.c_str());
}

