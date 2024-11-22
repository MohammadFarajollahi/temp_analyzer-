

void create_chart() {
  // ایجاد نمودار
  chart = lv_chart_create(lv_scr_act());
  lv_obj_set_size(chart, 473, 190);
  lv_obj_align(chart, LV_ALIGN_TOP_LEFT, 1, 110);
  lv_chart_set_type(chart, LV_CHART_TYPE_LINE);

  // تنظیمات ظاهری نمودار
  lv_obj_set_style_border_color(chart, lv_color_hex(0xFFFFFF), 0);  // حاشیه سفید
  lv_obj_set_style_border_width(chart, 2, 0);                       // عرض حاشیه
  lv_obj_set_style_pad_all(chart, 10, 0);                           // فضای داخلی
  lv_chart_set_div_line_count(chart, 10, 10);                       // خطوط شبکه
  lv_obj_set_style_arc_color(chart, lv_color_hex(0xAAAAAA), 0);     // رنگ خطوط شبکه
  lv_obj_set_style_bg_color(chart, lv_color_hex(0x202020), 0);      // پس‌زمینه تیره

  lv_chart_set_range(chart, LV_CHART_AXIS_PRIMARY_Y, 0, 100);
  lv_chart_set_point_count(chart, 50);  // تعداد نقاط بیشتر در هر سری

  // ایجاد سری برای هر سنسور با رنگ دلخواه هگز
  ser1 = lv_chart_add_series(chart, lv_color_hex(0xFF5733), LV_CHART_AXIS_PRIMARY_Y);  // رنگ نارنجی
  ser2 = lv_chart_add_series(chart, lv_color_hex(0x33FF57), LV_CHART_AXIS_PRIMARY_Y);  // رنگ سبز
  ser3 = lv_chart_add_series(chart, lv_color_hex(0x3357FF), LV_CHART_AXIS_PRIMARY_Y);  // رنگ آبی
}


void update_chart() {
  float temp1 = sensor1;
  float temp2 = sensor2;
  float temp3 = sensor3;

  // Serial.print("s1:");
  // Serial.print(temp1);
  // Serial.print("/s2:");
  // Serial.print(temp2);
  // Serial.print("/s3:");
  // Serial.println(temp3);


  // float temp1 = sensorActive[0] ? sensor1 : 0;
  // float temp2 = sensorActive[1] ? sensor2 : 0;
  // float temp3 = sensorActive[2] ? sensor3 : 0;

  // if (temp1 >= 100 || temp2 >= 100 || temp3 >= 100) lv_chart_set_range(chart, LV_CHART_AXIS_PRIMARY_Y, 0, 200);
  // if (temp1 >= 200 || temp2 >= 200 || temp3 >= 200) lv_chart_set_range(chart, LV_CHART_AXIS_PRIMARY_Y, 0, 300);
  // if (temp1 >= 300 || temp2 >= 300 || temp3 >= 300) lv_chart_set_range(chart, LV_CHART_AXIS_PRIMARY_Y, 0, 400);
  // if (temp1 >= 400 || temp2 >= 400 || temp3 >= 400) lv_chart_set_range(chart, LV_CHART_AXIS_PRIMARY_Y, 0, 500);
  // if (temp1 >= 500 || temp2 >= 500 || temp3 >= 500) lv_chart_set_range(chart, LV_CHART_AXIS_PRIMARY_Y, 0, 600);
  // if (temp1 >= 600 || temp2 >= 600 || temp3 >= 600) lv_chart_set_range(chart, LV_CHART_AXIS_PRIMARY_Y, 0, 700);
  // if (temp1 >= 700 || temp2 >= 700 || temp3 >= 700) lv_chart_set_range(chart, LV_CHART_AXIS_PRIMARY_Y, 0, 800);
  // if (temp1 >= 800 || temp2 >= 800 || temp3 >= 800) lv_chart_set_range(chart, LV_CHART_AXIS_PRIMARY_Y, 0, 900);
  // if (temp1 >= 900 || temp2 >= 900 || temp3 >= 900) lv_chart_set_range(chart, LV_CHART_AXIS_PRIMARY_Y, 0, 1000);
  // if (temp1 >= 1000 || temp2 >= 1000 || temp3 >= 1000) lv_chart_set_range(chart, LV_CHART_AXIS_PRIMARY_Y, 0, 1500);

  // تنظیم محدوده محور Y
  float maxTemp = max(max(temp1, temp2), temp3);
  float minTemp = min(min(temp1, temp2), temp3);
  lv_chart_set_range(chart, LV_CHART_AXIS_PRIMARY_Y, 0, maxTemp + 50);


  // اضافه کردن دماها به نمودار
  lv_chart_set_next_value(chart, ser1, temp1);
  lv_chart_set_next_value(chart, ser2, temp2);
  lv_chart_set_next_value(chart, ser3, temp3);

  // بروزرسانی نمودار
  lv_chart_refresh(chart);
}