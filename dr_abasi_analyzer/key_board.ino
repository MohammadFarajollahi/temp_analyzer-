

// تابع نمایش کیبورد مجازی
void showKeyboard() {
  kb = lv_keyboard_create(lv_scr_act());
  lv_keyboard_set_mode(kb, LV_KEYBOARD_MODE_USER_4);  // حالت کیبورد متنی
  lv_keyboard_set_textarea(kb, fileNameInput);        // اتصال کیبورد به ورودی نام فایل
  lv_obj_set_size(kb, 480, 140);
  lv_obj_align(kb, LV_ALIGN_BOTTOM_MID, 0, 0);  // Align keyboard at the bottom

  // دکمه تأیید
  btn_confirm = lv_btn_create(lv_scr_act());
  lv_obj_set_size(btn_confirm, 90, 30);
  lv_obj_set_pos(btn_confirm, 10, 135);  // تنظیم موقعیت دکمه تأیید

  ///new////

  lv_obj_add_event_cb(
    btn_confirm, [](lv_event_t *e) {
      lv_obj_del(kb);           // حذف کیبورد
      lv_obj_del(btn_confirm);  // حذف دکمه تأیید
      lv_obj_set_pos(fileNameInput, originalX, originalY);
    },
    LV_EVENT_CLICKED, NULL);  // رویداد کلیک
  lv_style_init(&style_label4);
  lv_style_set_text_font(&style_label4, &lv_font_unscii_8);  // تنظیم فونت
  lv_obj_t *label_confirm = lv_label_create(btn_confirm);
   lv_obj_add_style(label_confirm, &style_label4, 0);
  lv_label_set_text(label_confirm, "Confirm");
}
