//lv_font_unscii_8
//lv_font_unscii_16
//lv_font_montserrat_18
//lv_font_montserrat_14
void create_labels() {
  // تنظیم رنگ پس‌زمینه صفحه اصلی به مشکی
  lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(0x000000), 0);

  // تعریف استایل برای لیبل‌ها
  lv_style_init(&style_label);
  lv_style_set_border_color(&style_label, lv_color_hex(0x4D55F5));  // رنگ کادر (آبی)
  lv_style_set_border_width(&style_label, 2);                       // ضخامت کادر
  lv_style_set_radius(&style_label, 8);                             // شعاع گوشه‌ها
  lv_style_set_bg_color(&style_label, lv_color_hex(0x000000));      // رنگ پس‌زمینه لیبل‌ها (خاکستری تیره)
  lv_style_set_text_color(&style_label, lv_color_hex(0xFFFFFF));    // رنگ متن لیبل‌ها (سفید)
  lv_style_set_pad_all(&style_label, 5);                            // فاصله داخلی (پدینگ)
  lv_style_set_text_font(&style_label, &lv_font_unscii_16);         // تنظیم فونت
                                                                    //
  // ایجاد و اعمال استایل به لیبل سنسور 1
  label1 = lv_label_create(lv_scr_act());
  lv_obj_add_style(label1, &style_label, 0);
  lv_label_set_text(label1, "Sensor1:  -- C");
  lv_obj_align(label1, LV_ALIGN_TOP_LEFT, 39, 0);

  // ایجاد و اعمال استایل به لیبل سنسور 2
  label2 = lv_label_create(lv_scr_act());
  lv_obj_add_style(label2, &style_label, 0);
  lv_label_set_text(label2, "Sensor2:   -- C");
  lv_obj_align(label2, LV_ALIGN_TOP_LEFT, 39, 40);

  // ایجاد و اعمال استایل به لیبل سنسور 3
  label3 = lv_label_create(lv_scr_act());
  lv_obj_add_style(label3, &style_label, 0);
  lv_label_set_text(label3, "Sensor3:   -- C");
  lv_obj_align(label3, LV_ALIGN_TOP_LEFT, 39, 80);

  // ایجاد خط در صفحه فعال
  lv_obj_t *line = lv_line_create(lv_scr_act());
  static lv_point_t line_points[2];                              // نقاط خط
  line_points[0].x = 480;                                         // مختصات شروع
  line_points[0].y = 0;                                        // مختصات شروع
  line_points[1].x = 480;                                        // مختصات پایان
  line_points[1].y = 318;                                        // مختصات پایان
  lv_line_set_points(line, line_points, 2);                      // تنظیم نقاط خط
  lv_obj_set_style_line_color(line, lv_color_hex(0xFFFFFFFF), 0);  // رنگ خط
  lv_obj_set_style_line_width(line, 2, 0);                       // ضخامت خط
}

void update_sensor_labels(lv_obj_t *label1, lv_obj_t *label2, lv_obj_t *label3) {
  float temp1 = sensor1;
  float temp2 = sensor2;
  float temp3 = sensor3;

  char temp_str1[10];
  char temp_str2[10];
  char temp_str3[10];

  // تبدیل دما به رشته با dtostrf
  dtostrf(temp1, 4, 2, temp_str1);
  dtostrf(temp2, 4, 2, temp_str2);
  dtostrf(temp3, 4, 2, temp_str3);

  // به‌روزرسانی متن لیبل‌ها با رشته‌های دما
  lv_label_set_text_fmt(label1, "Sensor1: %sC", temp_str1);
  lv_label_set_text_fmt(label2, "Sensor2: %sC", temp_str2);
  lv_label_set_text_fmt(label3, "Sensor3: %sC", temp_str3);
}