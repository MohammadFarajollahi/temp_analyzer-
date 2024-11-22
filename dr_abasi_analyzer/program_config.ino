char formattedTime[9];
unsigned long startTime;
int fileIndex = 1;  // شروع شماره فایل


void writeBufferToFile() {
  File dataFile = SD.open(file_name, FILE_APPEND);  // باز کردن فایل در حالت نوشتن
  if (dataFile) {
    dataFile.write((uint8_t*)buffer, bufferIndex); // نوشتن داده‌های بافر
    dataFile.close();  // بستن فایل
    bufferIndex = 0;   // ریست کردن بافر
  } else {
    Serial.println("خطا در ذخیره داده‌ها!");
  }
}

void program_config() {
  if (start_program == 1) {
    update_time();
    // time_show = String(hu_) + ":" + String(min_) + ":" + String(sec_);
    snprintf(formattedTime, 9, "%02lu:%02lu:%02lu", hu_, min_, sec_);
    bufferIndex += snprintf(buffer + bufferIndex, BUFFER_SIZE - bufferIndex,
                            "%s,%.2f,%.2f,%.2f\n", formattedTime, sensor1, sensor2, sensor3);

    if (bufferIndex >= BUFFER_SIZE - 50) {  // اگر بافر پر شد، داده‌ها ذخیره شوند
      writeBufferToFile();
    }

    // dataFile = SD.open(file_name, FILE_WRITE);
    // if (dataFile) {
    //   time_show = String(hu_) + ":" + String(min_) + ":" + String(sec_);
    //   dataFile.print(time_show);
    //   dataFile.print(",");
    //   dataFile.print(sensor1);
    //   dataFile.print(",");
    //   dataFile.print(sensor2);
    //   dataFile.print(",");
    //   dataFile.println(sensor3);
    //   dataFile.close();
    // } else {
    //   Serial.println("خطا در ذخیره داده‌ها!");
    // }
  }

}


void update_time() {

  static uint32_t lastSeconds = 0;
  if (sec_ != lastSeconds) {  // بررسی تغییر مقدار ثانیه‌ها
    time_show = "Time=" + String(hu_) + ":" + String(min_) + ":" + String(sec_);
    lv_label_set_text(label_time, time_show.c_str());
  }
}