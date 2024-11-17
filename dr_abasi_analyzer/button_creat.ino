
void show_uart(String text) {
  String s = text;
  lv_textarea_add_text(terminal, s.c_str());
  lv_textarea_add_text(terminal, "\n");  // Add new line
}

void event_handler_new(lv_event_t *e) {
  String s = "create new file";
  lv_textarea_add_text(terminal, s.c_str());
  lv_textarea_add_text(terminal, "\n");  // Add new line
}



void event_handler_save(lv_event_t *e) {
  String s = "Save";
  lv_textarea_add_text(terminal, s.c_str());
  lv_textarea_add_text(terminal, "\n");  // Add new line
}


void event_handler_start(lv_event_t *e) {
  String s = "Start";
  lv_textarea_add_text(terminal, s.c_str());
  lv_textarea_add_text(terminal, "\n");  // Add new line
}

void event_handler_stop(lv_event_t *e) {
  String s = "Stop";
  lv_textarea_add_text(terminal, s.c_str());
  lv_textarea_add_text(terminal, "\n");  // Add new line
}

void button_create() {
  lv_style_init(&style_label3);
  lv_style_set_text_font(&style_label3, &lv_font_unscii_8);  // تنظیم فونت

  // Create a clear button
  ///////////////////////////////////////////////
  btn_new = lv_btn_create(lv_scr_act());
  lv_obj_add_style(btn_new, &style_label3, 0);
  lv_obj_align(btn_new, LV_ALIGN_TOP_LEFT, 5, 270);  // موقعیت دکمه پاک کردن
  lv_obj_set_size(btn_new, 100, 35);
  // Label for the clear button
  label_new = lv_label_create(btn_new);
  lv_label_set_text(label_new, "New project");
  lv_obj_center(label_new);
  lv_obj_add_event_cb(btn_new, event_handler_new, LV_EVENT_CLICKED, NULL);

  ////////////////////////////////////////////////////
  // ورودی نام فایل
  fileNameInput = lv_textarea_create(lv_scr_act());
  lv_obj_set_size(fileNameInput, 135, 35);
  originalX = 115;  // ذخیره موقعیت اصلی
  originalY = 271;
  lv_obj_set_pos(fileNameInput, originalX, originalY);  // تنظیم موقعیت ورودی نام فایل
  lv_textarea_set_placeholder_text(fileNameInput, "Enter file name");

  // اضافه کردن رویداد کلیک به فیلد ورودی
  lv_obj_add_event_cb(
    fileNameInput, [](lv_event_t *e) {
      // جابه‌جا کردن فیلد ورودی
      lv_obj_set_pos(fileNameInput, originalX + 70, originalY - 140);  // جابه‌جایی به پایین
      showKeyboard();                                                  // نمایش کیبورد با کلیک بر روی فیلد ورودی
    },
    LV_EVENT_CLICKED, NULL);  // رویداد کلیک

  ///////////////////////////////////////////////
  // تعریف استایل برای لیبل‌ها
  lv_style_init(&style_label5);
  lv_style_set_bg_color(&style_label5, lv_color_hex(0x00FF00));    // رنگ پس‌زمینه لیبل‌ها (خاکستری تیره)
  lv_style_set_text_color(&style_label5, lv_color_hex(0x000000));  // رنگ متن لیبل‌ها (سفید)
  lv_style_set_text_font(&style_label5, &lv_font_unscii_8);        // تنظیم فونت

  btn_start = lv_btn_create(lv_scr_act());
  lv_obj_add_style(btn_start, &style_label5, 0);
  lv_obj_align(btn_start, LV_ALIGN_TOP_LEFT, 90, 215);
  lv_obj_set_size(btn_start, 70, 35);
  label_start = lv_label_create(btn_start);
  lv_label_set_text(label_start, "Start");
  lv_obj_center(label_start);
  lv_obj_add_event_cb(btn_start, event_handler_start, LV_EVENT_CLICKED, NULL);

  // تعریف استایل برای لیبل‌ها
  lv_style_init(&style_label6);
  lv_style_set_bg_color(&style_label6, lv_color_hex(0xFF0000));    // رنگ پس‌زمینه لیبل‌ها (خاکستری تیره)
  lv_style_set_text_color(&style_label6, lv_color_hex(0xFFFFFF));  // رنگ متن لیبل‌ها (سفید)
  lv_style_set_text_font(&style_label6, &lv_font_unscii_8);        // تنظیم فونت
  btn_stop = lv_btn_create(lv_scr_act());
  lv_obj_add_style(btn_stop, &style_label6, 0);
  lv_obj_align(btn_stop, LV_ALIGN_TOP_LEFT, 5, 215);
  lv_obj_set_size(btn_stop, 70, 35);
  label_stop = lv_label_create(btn_stop);
  lv_label_set_text(label_stop, "Stop");
  lv_obj_center(label_stop);
  lv_obj_add_event_cb(btn_stop, event_handler_stop, LV_EVENT_CLICKED, NULL);

  //****************terminal_creat******************
  lv_style_init(&style_label7);
  //lv_style_set_text_color(&style_label7, lv_color_hex(0xFFFFFF));  // رنگ متن لیبل‌ها (سفید)
  lv_style_set_text_font(&style_label7, &lv_font_unscii_8);        // تنظیم فونت
  terminal = lv_textarea_create(lv_scr_act());
  lv_obj_add_style(terminal, &style_label7, 0);
  lv_obj_set_size(terminal, 170, 110);                  // سایز ترمینال
  lv_obj_align(terminal, LV_ALIGN_TOP_LEFT, 280, 200);  // تنظیم موقعیت ترمینال
  lv_textarea_set_text(terminal, "Log ...\n");          // متن اولیه
}