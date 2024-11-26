String ss;

//***************************لیست فایل ها *************************
char selected_file[64];

// تابع برای بستن لیست
void close_file_list(lv_event_t *e) {
  lv_obj_del_async(list);  // حذف لیست به‌صورت غیرهمزمان
}

void event_handler_open_file(lv_event_t *e) {
  //
  // ایجاد لیست
  list = lv_list_create(lv_scr_act());
  lv_obj_set_size(list, 250, 200);
  lv_obj_center(list);
  // دکمه Close در بالای لیست
  lv_obj_t *close_btn = lv_list_add_btn(list, LV_SYMBOL_CLOSE, "Close");
  lv_obj_add_event_cb(close_btn, close_file_list, LV_EVENT_CLICKED, list);
  // باز کردن SD کارت
  if (!SD.begin()) {
    Serial.println("SD card initialization failed!");
    return;
  }
  File root = SD.open("/");
  if (!root) {
    Serial.println("Failed to open directory!");
    return;
  }

  // افزودن فایل‌ها به لیست
  File file = root.openNextFile();
  while (file) {
    if (!file.isDirectory()) {
      lv_obj_t *btn = lv_list_add_btn(list, LV_SYMBOL_FILE, file.name());
      lv_obj_add_event_cb(
        btn, [](lv_event_t *e) {
          lv_obj_t *btn = lv_event_get_target(e);
          list = lv_obj_get_parent(btn);  // دریافت شیء لیست
          const char *file_name = lv_list_get_btn_text(list, btn);

          // ذخیره نام فایل در متغیر
          strncpy(selected_file, file_name, sizeof(selected_file));
          Serial.printf("Selected file: %s\n", selected_file);

          // بستن لیست
          lv_obj_del_async(list);
          FILE_NAME = selected_file;
          FILE_NAME = "/" + FILE_NAME;
          tft.fillScreen(TFT_BLACK);
          lv_obj_clean(lv_scr_act());
          read_data_from_sd();
        },
        LV_EVENT_CLICKED, NULL);
    }
    file = root.openNextFile();
  }

  root.close();

  //create_main_button();
}
/////////////////////////////////////////////////////////////////////

void show_uart(String text) {
  ss = text;
  // lv_textarea_add_text(terminal, s.c_str());
  // lv_textarea_add_text(terminal, "\n");  // Add new line
}

void event_handler_new(lv_event_t *e) {
  //ساخت فایل اکسل جدید
  terminalText = lv_textarea_get_text(fileNameInput);
  ss = terminalText;
  file_name = "/" + ss + ".csv";

  if (SD.exists(file_name)) {
    Serial.println("File already exists. Overwriting...");
    ss = "The file already exists";
    create_message_box("Warning", ss);
  } else {

    dataFile = SD.open(file_name, FILE_WRITE);
    if (dataFile) {
      dataFile.println("Time(ms),Temp1,Temp2,Temp3");
      dataFile.close();
      ss = file_name + " create";
      create_message_box("New Project", ss);
    } else {
      Serial.println("خطا در ایجاد فایل!");
      ss = "Faild create file!!!";
      create_message_box("Warning", ss);
    }
  }
}



void event_handler_save(lv_event_t *e) {
  ss = "Save";
  // lv_textarea_add_text(terminal, s.c_str());
  // lv_textarea_add_text(terminal, "\n");  // Add new line
}


void event_handler_start(lv_event_t *e) {
  stop_count = 0;
  stop_time = 0;
  stop_count = 0;
  ss = "Program Start";
  //create_message_box("", ss);
  if (start_program == 0) {
    start_program = 1;
    stop_program = 0;
    hu_ = 0;
    sec_ = 0;
    min_ = 0;
  }
}

void event_handler_stop(lv_event_t *e) {
  ss = "Program Stop";
  stop_time = 0;
  stop_count = 1;
  //create_message_box("", ss);
  lv_led_off(led1);
  if (stop_program == 0) {
    stop_program = 1;
    start_program = 0;
  }
}

void button_create() {
  lv_style_init(&style_label3);
  lv_style_set_text_font(&style_label3, &lv_font_unscii_8);  // تنظیم فونت


  // open new file
  ///////////////////////////////////////////////
  btn_open_file = lv_btn_create(lv_scr_act());
  lv_obj_add_style(btn_open_file, &style_label3, 0);
  lv_obj_align(btn_open_file, LV_ALIGN_TOP_LEFT, 260, 5);  // موقعیت دکمه پاک کردن
  lv_obj_set_size(btn_open_file, 100, 35);
  // Label for the clear button
  label_open_file = lv_label_create(btn_open_file);
  lv_label_set_text(label_open_file, "Open Project");
  lv_obj_center(label_open_file);
  lv_obj_add_event_cb(btn_open_file, event_handler_open_file, LV_EVENT_CLICKED, NULL);

  // Create a clear button
  ///////////////////////////////////////////////
  btn_new = lv_btn_create(lv_scr_act());
  lv_obj_add_style(btn_new, &style_label3, 0);
  lv_obj_align(btn_new, LV_ALIGN_TOP_LEFT, 5, 5);  // موقعیت دکمه پاک کردن
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
  originalY = 5;
  lv_obj_set_pos(fileNameInput, originalX, originalY);  // تنظیم موقعیت ورودی نام فایل
  lv_textarea_set_placeholder_text(fileNameInput, "Enter file name");

  // اضافه کردن رویداد کلیک به فیلد ورودی
  lv_obj_add_event_cb(
    fileNameInput, [](lv_event_t *e) {
      // جابه‌جا کردن فیلد ورودی
      lv_obj_set_pos(fileNameInput, originalX + 70, originalY + 140);  // جابه‌جایی به پایین
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
  lv_obj_align(btn_start, LV_ALIGN_TOP_LEFT, 90, 50);
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
  lv_obj_align(btn_stop, LV_ALIGN_TOP_LEFT, 5, 50);
  lv_obj_set_size(btn_stop, 70, 35);
  label_stop = lv_label_create(btn_stop);
  lv_label_set_text(label_stop, "Stop");
  lv_obj_center(label_stop);
  lv_obj_add_event_cb(btn_stop, event_handler_stop, LV_EVENT_CLICKED, NULL);

  //****************terminal_creat******************
  // lv_style_init(&style_label7);
  // //lv_style_set_text_color(&style_label7, lv_color_hex(0xFFFFFF));  // رنگ متن لیبل‌ها (سفید)
  // lv_style_set_text_font(&style_label7, &lv_font_unscii_8);  // تنظیم فونت
  // terminal = lv_textarea_create(lv_scr_act());
  // lv_obj_add_style(terminal, &style_label7, 0);
  // lv_obj_set_size(terminal, 170, 110);                  // سایز ترمینال
  // lv_obj_align(terminal, LV_ALIGN_TOP_LEFT, 280, 200);  // تنظیم موقعیت ترمینال
  // lv_textarea_set_text(terminal, "Log ...\n");          // متن اولیه
}

// تابع handler برای واکنش به تغییر انتخاب
static void dropdown_event_handler(lv_event_t *e) {
  lv_obj_t *ddlist = lv_event_get_target(e);

  // دریافت انتخاب انجام‌شده از Drop-Down
  lv_dropdown_get_selected_str(ddlist, selected_item, sizeof(selected_item));

  // نمایش انتخاب در سریال (برای مثال)
  Serial.print("آیتم انتخاب شده: ");
  Serial.println(selected_item);  // در اینجا از selected_item استفاده می‌شود که نوع آن char[] است
  String ss1 = selected_item;
  if (ss1 == "250ms") sample_time = 1;
  if (ss1 == "500ms") sample_time = 2;
  if (ss1 == "1sec") sample_time = 3;
  if (ss1 == "5sec") sample_time = 4;
  if (ss1 == "10sec") sample_time = 5;
  if (ss1 == "20sec") sample_time = 6;
  if (sample_time == 1) count_ok = 50;
  if (sample_time == 2) count_ok = 100;
  if (sample_time == 3) count_ok = 200;
  if (sample_time == 4) count_ok = 1000;
  if (sample_time == 5) count_ok = 2000;
  if (sample_time == 6) count_ok = 4000;
  Serial.print("sample_time:");
  Serial.println(sample_time);
}

void create_dropdown() {
  lv_obj_t *scr = lv_scr_act();
  lv_obj_t *ddlist = lv_dropdown_create(scr);  // فقط یک آرگومان
  lv_dropdown_set_options(ddlist, "250ms\n500ms\n1sec\n5sec\n10sec\n20sec");
  lv_obj_align(ddlist, LV_ALIGN_TOP_LEFT, 200, 70);  // موقعیت دکمه پاک کردن
  //lv_obj_set_pos(ddlist, LV_ALIGN_TOP_LEFT, 5, 90);  // موقعیت دکمه پاک کردن // x=50, y=50
  lv_obj_set_size(ddlist, 100, 30);  // عرض=200, ارتفاع=50
  lv_obj_add_event_cb(ddlist, dropdown_event_handler, LV_EVENT_VALUE_CHANGED, NULL);


  lv_style_init(&style_sample);
  lv_style_set_text_font(&style_sample, &lv_font_unscii_8);        // تنظیم فونت
  lv_style_set_bg_color(&style_sample, lv_color_hex(0x000000));    // رنگ پس‌زمینه لیبل‌ها (خاکستری تیره)
  lv_style_set_text_color(&style_sample, lv_color_hex(0xFFFFFF));  // رنگ متن لیبل‌ها (سفید)
  label_sample = lv_label_create(lv_scr_act());
  lv_obj_add_style(label_sample, &style_sample, 0);
  lv_obj_align(label_sample, LV_ALIGN_TOP_LEFT, 206, 60);
  //lv_obj_set_size(label_time, 130, 40);
  lv_label_set_text(label_sample, "Sample time");
}