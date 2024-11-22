
// void remove_spinner(lv_timer_t * timer) {
//     lv_obj_t * spinner = (lv_obj_t *) timer->user_data;
//     lv_obj_del(spinner);
// }

// void create_timed_spinner() {
//     lv_obj_t * spinner = lv_spinner_create(lv_scr_act(), 1000, 60);
//     lv_obj_set_size(spinner, 100, 100);
//     lv_obj_center(spinner);

//     // حذف Spinner بعد از 3 ثانیه
//     lv_timer_create(remove_spinner, 3000, spinner);
// }


// ////////////////
void create_spinner() {
  // ایجاد Spinner
  spinner = lv_spinner_create(lv_scr_act(), 1000, 60);
  lv_obj_set_size(spinner, 100, 100);  // اندازه Spinner
  lv_obj_center(spinner);              // قرار دادن در مرکز صفحه

  // تنظیم رنگ Spinner
  lv_obj_set_style_arc_color(spinner, lv_palette_main(LV_PALETTE_BLUE), LV_PART_INDICATOR);
  lv_obj_set_style_arc_width(spinner, 8, LV_PART_INDICATOR);
}

//////////////////////////////////////////////////2222222222222//////////////////////////////////////
void create_arc_spinner() {
  lv_obj_t* arc = lv_arc_create(lv_scr_act());
  lv_obj_set_size(arc, 100, 100);
  lv_obj_center(arc);
  lv_arc_set_bg_angles(arc, 0, 360);
  lv_arc_set_value(arc, 50);
  lv_obj_set_style_arc_width(arc, 10, LV_PART_INDICATOR);

  lv_anim_t anim;
  lv_anim_init(&anim);
  lv_anim_set_var(&anim, arc);
  lv_anim_set_exec_cb(&anim, (lv_anim_exec_xcb_t)lv_arc_set_end_angle);
  lv_anim_set_time(&anim, 2000);
  lv_anim_set_values(&anim, 0, 360);
  lv_anim_set_repeat_count(&anim, LV_ANIM_REPEAT_INFINITE);
  lv_anim_start(&anim);
}