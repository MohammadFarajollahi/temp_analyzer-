void create_battery_shape() {
  lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(0x000000), 0);
  // نقاط بدنه باتری
  static lv_point_t battery_points[] = {
    { 55, 10 },
    { 20, 10 },
    { 20, 10 },
     //{ 20, 25 },
    // { 50, 25 },
    { 50, 10 },
    { 55, 10 },
    { 55, 15 },
    { 60, 15 },
    { 60, 20 },
    { 55, 20 },
    { 55, 25 },
    { 20, 25 },

  };

  // ایجاد خطوط بدنه باتری
  lv_obj_t *battery_line = lv_line_create(lv_scr_act());
  lv_line_set_points(battery_line, battery_points, sizeof(battery_points) / sizeof(lv_point_t));
  lv_obj_set_style_line_width(battery_line, 2, 0);
  lv_obj_set_style_line_color(battery_line, lv_color_hex(0xFFFFFF), 0);
  lv_obj_align(battery_line, LV_ALIGN_TOP_LEFT, 410, 5);

  // ایجاد قسمت پر شده برای نمایش شارژ
  battery_fill = lv_obj_create(lv_scr_act());
  lv_obj_set_size(battery_fill, 100, 14);                              // اندازه نوار شارژ کوچکتر
  lv_obj_align(battery_fill, LV_ALIGN_TOP_LEFT, 430, 15);              // محل قرارگیری نوار شارژ
  lv_obj_set_style_bg_color(battery_fill, lv_color_hex(0x00FF00), 0);  // رنگ نوار شارژ سبز اولیه
  lv_obj_set_style_radius(battery_fill, 3, 0);                         // گرد کردن لبه‌ها
  lv_obj_clear_flag(battery_fill, LV_OBJ_FLAG_SCROLLABLE);             // غیرفعال کردن اسکرول

  // تنظیم اندازه اولیه نوار شارژ
  update_battery_level(100);  // مقدار اولیه شارژ (75%)
}

// تابعی برای به‌روزرسانی مقدار شارژ باتری
void update_battery_level(int level) {
  if (level < 0) level = 0;
  if (level > 100) level = 100;

  // تغییر اندازه نوار شارژ بر اساس درصد
  lv_obj_set_width(battery_fill, (level * 35) / 100);  // 40 عرض نوار شارژ

  // تغییر رنگ نوار شارژ
  if (level > 35) {
    lv_obj_set_style_bg_color(battery_fill, lv_color_hex(0x00FF00), 0);  // سبز اگر بالای 20 درصد باشد
  } else {
    lv_obj_set_style_bg_color(battery_fill, lv_color_hex(0xFF0000), 0);  // قرمز اگر زیر 20 درصد باشد
  }
}