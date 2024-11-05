

// تابع تغییر وضعیت چک باکس
void checkbox_event_cb(lv_event_t *e) {
  checkbox = lv_event_get_target(e);
  lv_chart_series_t *ser = (lv_chart_series_t *)lv_obj_get_user_data(checkbox);
  int index = (checkbox == cb1) ? 0 : (checkbox == cb2) ? 1
                                                        : 2;           // تشخیص چک باکس
  sensorActive[index] = lv_obj_has_state(checkbox, LV_STATE_CHECKED);  // تغییر وضعیت متغیر

  // if (sensorActive[0] == true) {

  // }

    // if (sensorActive[index]) {
    //   lv_chart_add_series(chart, ser->color, LV_CHART_AXIS_PRIMARY_Y);  // اضافه کردن سری به نمودار
    // } else {
    //   lv_chart_remove_series(chart, ser);  // حذف سری از نمودار
    // }
  }

  void creat_check_box() {

    // چک باکس‌ها برای سنسورها
    cb1 = lv_checkbox_create(lv_scr_act());
    lv_checkbox_set_text(cb1, "");
     lv_obj_set_style_text_color(cb1, lv_color_hex(0xFFFFFF), 0);
    lv_obj_align(cb1, LV_ALIGN_TOP_LEFT, 5, 5); // x_pos275 
    lv_obj_set_user_data(cb1, ser1);  // ذخیره سری سنسور

    cb2 = lv_checkbox_create(lv_scr_act());
    lv_checkbox_set_text(cb2, "");
     lv_obj_set_style_text_color(cb2, lv_color_hex(0xFFFFFF), 0);
    lv_obj_align(cb2, LV_ALIGN_TOP_LEFT, 5, 44);
    lv_obj_set_user_data(cb2, ser2);

    cb3 = lv_checkbox_create(lv_scr_act());
    lv_checkbox_set_text(cb3, "");
     lv_obj_set_style_text_color(cb3, lv_color_hex(0xFFFFFF), 0);
    lv_obj_align(cb3, LV_ALIGN_TOP_LEFT, 5, 84);
    lv_obj_set_user_data(cb3, ser3);

    lv_obj_add_event_cb(cb1, checkbox_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_event_cb(cb2, checkbox_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_event_cb(cb3, checkbox_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
  }