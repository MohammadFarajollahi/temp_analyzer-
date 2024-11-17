
void event_handler_sd(lv_event_t *e) {
  String s = "sd card information";
  lv_textarea_add_text(terminal, s.c_str());
  lv_textarea_add_text(terminal, "\n");  // Add new line
}

void event_handler_usb(lv_event_t *e) {
  String s = "USB information";
  lv_textarea_add_text(terminal, s.c_str());
  lv_textarea_add_text(terminal, "\n");  // Add new line
}

void sd_card() {
  lv_style_init(&style_label_sd);
  lv_style_set_text_font(&style_label_sd, &lv_font_unscii_8);        // تنظیم فونت
  lv_style_set_bg_color(&style_label_sd, lv_color_hex(0xFFFFFF));    // رنگ پس‌زمینه لیبل‌ها (خاکستری تیره)
  lv_style_set_text_color(&style_label_sd, lv_color_hex(0x000000));  // رنگ متن لیبل‌ها (سفید)

  button_sd = lv_btn_create(lv_scr_act());
  lv_obj_add_style(button_sd, &style_label_sd, 0);
  lv_obj_align(button_sd, LV_ALIGN_TOP_LEFT, 347, 50);  // موقعیت دکمه پاک کردن
  lv_obj_set_size(button_sd, 128, 28);
  // Label for the clear button
  label_sd = lv_label_create(button_sd);
  if (sd_ok == 1) lv_label_set_text(label_sd, "SD Card ready");
  if (sd_ok == 0) lv_label_set_text(label_sd, "SD Card Error");
  lv_obj_center(label_sd);
  lv_obj_add_event_cb(button_sd, event_handler_sd, LV_EVENT_CLICKED, NULL);

  button_usb = lv_btn_create(lv_scr_act());
  lv_obj_add_style(button_usb, &style_label_sd, 0);
  lv_obj_align(button_usb, LV_ALIGN_TOP_LEFT, 347, 85);  // موقعیت دکمه پاک کردن
  lv_obj_set_size(button_usb, 128, 28);
  // Label for the clear button
  label_usb = lv_label_create(button_usb);
  if (usb_ok == 1) lv_label_set_text(label_usb, "USB Connect");
  if (usb_ok == 0) lv_label_set_text(label_usb, "USB disconnect");
  lv_obj_center(label_usb);
  lv_obj_add_event_cb(button_usb, event_handler_usb, LV_EVENT_CLICKED, NULL);
}

void usb_check() {
  // if (Serial) {
  //   if (!usbConnected) {
  //     Serial.println("USB متصل شد.");
  //     usbConnected = true;
  //     usb_ok = 1;
  //     lv_label_set_text(label_usb, "USB Connect");
  //   }
  // } else {
  //   if (usbConnected) {
  //     Serial.println("USB قطع شد!");
  //     usbConnected = false;
  //     usb_ok = 0;
  //     lv_label_set_text(label_usb, "USB disconnect");
  //   }
  // }



  // بررسی پاسخ
   if (digitalRead(USB_DETECT_PIN) == HIGH) {
    if (!usbConnected) {
      Serial.println("USB متصل شد.");
      usbConnected = true;
      lv_label_set_text(label_usb, "USB Connect");
    }
  } else {
    if (usbConnected) {
      Serial.println("USB قطع شد!");
      usbConnected = false;
      lv_label_set_text(label_usb, "USB disconnect");
    }
  }
}
