// تعریف نمودار و سری داده‌ها
lv_obj_t* chart2;
lv_chart_series_t *ser11, *ser22, *ser33;

// تعریف مسیر فایل

int file_count;
int data_count = 0;  // تعداد داده‌های خوانده شده


void event_handler_exit(lv_event_t* e) {
  Serial.println("Exit");
  show_chart = 0;
  tft.fillScreen(TFT_BLACK);
  lv_obj_clean(lv_scr_act());
  create_labels();
  create_battery_shape();  // ایجاد نمایشگر باتری
  create_chart();          // chart
  button_create();
  sd_card();
  timer_();
  create_dropdown();
  lv_example_led_1();
  charj = 75;
}


// تابع خواندن داده‌ها از فایل CSV
void read_data_from_sd() {
  tft.fillScreen(TFT_BLACK);
  lv_obj_clean(lv_scr_act());
  tft.setCursor(10, 10);
  String s1 = "Please wait ...";
  tft.setTextFont(1);
  tft.setTextSize(2);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.println(s1);
  Serial.print("Wait ...");

  String name2_ = "File name:" + FILE_NAME;
  tft.setCursor(10, 50);
  tft.println(name2_);
  //تعداد خط ها
  show_chart = 1;
  file_count = 0;
  File file = SD.open(FILE_NAME.c_str());
  if (file) {
    while (file.available()) {
      String line = file.readStringUntil('\n');
      ++file_count;
    }

    file.close();
  } else {
    Serial.println("Failed to open the file");
  }
  Serial.print("line number:");
  Serial.println(file_count);

  //دکمه خروج
  btn_exit = lv_btn_create(lv_scr_act());
  lv_obj_add_style(btn_exit, &style_label3, 0);
  lv_obj_align(btn_exit, LV_ALIGN_TOP_LEFT, 5, 288);  // موقعیت دکمه پاک کردن
  lv_obj_set_size(btn_exit, 80, 28);
  // Label for the clear button
  label_new = lv_label_create(btn_exit);
  lv_label_set_text(label_new, "Exit");
  lv_obj_center(label_new);
  lv_obj_add_event_cb(btn_exit, event_handler_exit, LV_EVENT_CLICKED, NULL);

  label_name = lv_label_create(lv_scr_act());
  lv_obj_add_style(label_name, &style_sample, 0);
  lv_obj_align(label_name, LV_ALIGN_TOP_LEFT, 100, 300);
  //lv_obj_set_size(label_time, 130, 40);
  String name_ = "File name:" + FILE_NAME;
  lv_label_set_text(label_name, name_.c_str());

  label1 = lv_label_create(lv_scr_act());
  lv_obj_add_style(label1, &style_label2, 0);
  lv_label_set_text(label1, "S1:Red");
  //lv_obj_set_style_text_color(label1, lv_palette_main(LV_PALETTE_RED), 0);
  lv_obj_set_style_text_color(label1, lv_color_hex(0xFF5733), 0);
  lv_obj_align(label1, LV_ALIGN_TOP_LEFT, 255, 300);

  label2 = lv_label_create(lv_scr_act());
  lv_obj_add_style(label2, &style_label2, 0);
  lv_label_set_text(label2, "S2:Green");
  //(label2, lv_palette_main(LV_PALETTE_GREEN), 0);
  lv_obj_set_style_text_color(label2, lv_color_hex(0x33FF57), 0);
  lv_obj_align(label2, LV_ALIGN_TOP_LEFT, 320, 300);

  label3 = lv_label_create(lv_scr_act());
  lv_obj_add_style(label3, &style_label2, 0);
  lv_label_set_text(label3, "S3:Blue");
  //lv_obj_set_style_text_color(label3, lv_palette_main(LV_PALETTE_BLUE), 0);
  lv_obj_set_style_text_color(label3, lv_color_hex(0x3357FF), 0);
  lv_obj_align(label3, LV_ALIGN_TOP_LEFT, 400, 300);

  //نمودار ترسیم
  drawChartWithTemperature();
  Serial.println("wait  for show");
  data_count = 0;
  file = SD.open(FILE_NAME);
  if (file) {
    while (file.available()) {                     /* let the GUI do its work */
      String line = file.readStringUntil('\n');    // خواندن یک خط
      int comma1 = line.indexOf(',');              // پیدا کردن اولین کاما
      int comma2 = line.indexOf(',', comma1 + 1);  // پیدا کردن دومین کاما

      if (comma1 != -1 && comma2 != -1) {
        // جدا کردن زمان و مقادیر دما
        String time_str = line.substring(0, comma1);                                   // زمان
        String temp1_str = line.substring(comma1 + 1, comma2);                         // دمای سنسور 1
        String temp2_str = line.substring(comma2 + 1, line.indexOf(',', comma2 + 1));  // دمای سنسور 2
        String temp3_str = line.substring(line.lastIndexOf(',') + 1);                  // دمای سنسور 3

        if (temp1_str != "" && temp2_str != "" && temp3_str != "" ) {
          // تبدیل رشته به عدد
          temp_sensor1 = temp1_str.toFloat();
          temp_sensor2 = temp2_str.toFloat();
          temp_sensor3 = temp3_str.toFloat();


          data_count++;  // افزایش تعداد داده‌ها
          sensor1 = temp_sensor1;
          sensor2 = temp_sensor2;
          sensor3 = temp_sensor3;
          update_chart2();
        }
      }
    }
    file.close();
  } else {
    Serial.println("Failed to open the file");
  }
  Serial.println(data_count);
  lv_obj_t* slider;
  slider = lv_slider_create(lv_scr_act());
  lv_slider_set_range(slider, LV_IMG_ZOOM_NONE, LV_IMG_ZOOM_NONE * 10);
  lv_obj_add_event_cb(slider, slider_x_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
  lv_obj_set_size(slider, 300, 10);
  lv_obj_align_to(slider, chart2, LV_ALIGN_OUT_BOTTOM_MID, 0, -30);

  slider = lv_slider_create(lv_scr_act());
  lv_slider_set_range(slider, LV_IMG_ZOOM_NONE, LV_IMG_ZOOM_NONE * 10);
  lv_obj_add_event_cb(slider, slider_y_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
  lv_obj_set_size(slider, 10, 200);
  lv_obj_align_to(slider, chart2, LV_ALIGN_OUT_RIGHT_MID, -20, 0);
}

static void slider_x_event_cb(lv_event_t* e) {
  lv_obj_t* obj = lv_event_get_target(e);
  int32_t v = lv_slider_get_value(obj);
  lv_chart_set_zoom_x(chart2, v);
}

static void slider_y_event_cb(lv_event_t* e) {
  lv_obj_t* obj = lv_event_get_target(e);
  int32_t v = lv_slider_get_value(obj);
  lv_chart_set_zoom_y(chart2, v);
}


void update_chart2() {
  float temp1 = sensor1;
  float temp2 = sensor2;
  float temp3 = sensor3;

  Serial.print("s1:");
  Serial.print(temp1);
  Serial.print("/s2:");
  Serial.print(temp2);
  Serial.print("/s3:");
  Serial.println(temp3);

  // تنظیم محدوده محور Y
  float maxTemp = max(max(temp1, temp2), temp3);
  float minTemp = min(min(temp1, temp2), temp3);
  lv_chart_set_range(chart2, LV_CHART_AXIS_PRIMARY_Y, 0, maxTemp + 50);
  // اضافه کردن دماها به نمودار
  lv_chart_set_next_value(chart2, ser11, temp1);
  lv_chart_set_next_value(chart2, ser22, temp2);
  lv_chart_set_next_value(chart2, ser33, temp3);
  // بروزرسانی نمودار
  lv_chart_refresh(chart2);
}


void drawChartWithTemperature() {
  chart2 = lv_chart_create(lv_scr_act());
  lv_obj_set_size(chart2, 460, 285);
  lv_obj_align(chart2, LV_ALIGN_TOP_LEFT, 1, 1);
  lv_chart_set_type(chart2, LV_CHART_TYPE_LINE);

  // تنظیمات ظاهری نمودار
  lv_obj_set_style_border_color(chart2, lv_color_hex(0xFFFFFF), 0);  // حاشیه سفید
  lv_obj_set_style_border_width(chart2, 2, 0);                       // عرض حاشیه
  lv_obj_set_style_pad_all(chart2, 10, 0);                           // فضای داخلی
  lv_chart_set_div_line_count(chart2, 10, 10);                       // خطوط شبکه
  lv_obj_set_style_arc_color(chart2, lv_color_hex(0xAAAAAA), 0);     // رنگ خطوط شبکه
  lv_obj_set_style_bg_color(chart2, lv_color_hex(0x202020), 0);      // پس‌زمینه تیره
  lv_chart_set_range(chart2, LV_CHART_AXIS_PRIMARY_Y, 0, 1200);
  if(file_count>3000)file_count=3000;
  lv_chart_set_point_count(chart2, file_count);  // تعداد نقاط بیشتر در هر سری

  // ایجاد سری برای هر سنسور با رنگ دلخواه هگز
  ser11 = lv_chart_add_series(chart2, lv_color_hex(0xFF5733), LV_CHART_AXIS_PRIMARY_Y);  // رنگ نارنجی
  ser22 = lv_chart_add_series(chart2, lv_color_hex(0x33FF57), LV_CHART_AXIS_PRIMARY_Y);  // رنگ سبز
  ser33 = lv_chart_add_series(chart2, lv_color_hex(0x3357FF), LV_CHART_AXIS_PRIMARY_Y);  // رنگ آبی
}
