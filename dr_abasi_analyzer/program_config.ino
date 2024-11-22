char formattedTime[9];
unsigned long startTime;
int fileIndex = 1;  // شروع شماره فایل


void writeBufferToFile() {
  File dataFile = SD.open(file_name, FILE_APPEND);  // باز کردن فایل در حالت نوشتن
  if (dataFile) {
    dataFile.write((uint8_t*)buffer, bufferIndex);  // نوشتن داده‌های بافر
    dataFile.close();                               // بستن فایل
    bufferIndex = 0;                                // ریست کردن بافر
  } else {
    Serial.println("خطا در ذخیره داده‌ها!");
    ss = "Saving Error";
     lv_led_off(led1);
    create_message_box("Warning", ss);
    if (stop_program == 0) {
      stop_program = 1;
      start_program = 0;
    }
  }
}

void program_config() {

  //update_time();
  snprintf(formattedTime, 9, "%02lu:%02lu:%02lu", hu_, min_, sec_);
  bufferIndex += snprintf(buffer + bufferIndex, BUFFER_SIZE - bufferIndex,
                          "%s,%.2f,%.2f,%.2f\n", formattedTime, sensor1, sensor2, sensor3);

  if (bufferIndex >= BUFFER_SIZE - 50) {  // اگر بافر پر شد، داده‌ها ذخیره شوند
    writeBufferToFile();
  }
}


void update_time() {

  static uint32_t lastSeconds = 0;
  if (sec_ != lastSeconds) {  // بررسی تغییر مقدار ثانیه‌ها
    time_show = "Time=" + String(hu_) + ":" + String(min_) + ":" + String(sec_);
    lv_label_set_text(label_time, time_show.c_str());
  }
}