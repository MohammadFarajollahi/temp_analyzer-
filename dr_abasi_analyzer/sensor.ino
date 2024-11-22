
void read_sensor() {

  ++sensor_read_count;
  if (sensor_read_count >= count_ok) {
    sensor_read_count = 0;
    // خواندن و نمایش دمای سنسور 1
    if (isnan(thermocouple1.readCelsius())) {
      sensor1 = 0;
    } else {
      sensor1 = thermocouple1.readCelsius();
    }

    // خواندن و نمایش دمای سنسور 2
    if (isnan(thermocouple2.readCelsius())) {
      sensor2 = 0;
    } else {
      sensor2 = thermocouple2.readCelsius();
    }

    // خواندن و نمایش دمای سنسور 3
    if (isnan(thermocouple3.readCelsius())) {
      sensor3 = 0;
    } else {
      sensor3 = thermocouple3.readCelsius();
    }
    update_chart();
    update_sensor_labels(label1, label2, label3);
    if (start_program == 1) {
      program_config();
      update_time();
      String send_ = "T=" + String(hu_) + ":" + String(min_) + ":" + String(sec_) + "/" + "s1:" + String(sensor1) + "/" + "s2:" + String(sensor2) + "/" + "s3:" + String(sensor3);
      Serial.println(send_);
      if(led_count == 0){
        lv_led_off(led1);
        led_count = 1;
      }else{
        lv_led_on(led1);
        led_count = 0;
      }
    }
    if (start_program == 1) {
      update_time();
    }
  }
  //
}