

// تابع کال‌بک برای دکمه "OK"
static void msgbox_event_cb(lv_event_t* e) {
  lv_obj_t* msgbox = lv_event_get_target(e);  // مسیج باکس را بگیر
  lv_obj_del(msgbox);                         // حذف مسیج باکس
}

void create_message_box(String mes1, String mes2) {
  // متن پیام
  static const char* btns[] = { "OK", NULL };

  // ایجاد مسیج باکس
 // lv_obj_t* msgbox = lv_msgbox_create(NULL, mes1.c_str(), mes2.c_str(), btns, true);
 lv_obj_t* msgbox = lv_msgbox_create(NULL, mes1.c_str(), mes2.c_str(), NULL, true);

  // تنظیم اندازه و مکان مسیج باکس
  lv_obj_set_width(msgbox, 200);
  lv_obj_center(msgbox);

  // افزودن کال‌بک برای دکمه‌های مسیج باکس
 // lv_obj_add_event_cb(msgbox, msgbox_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
}