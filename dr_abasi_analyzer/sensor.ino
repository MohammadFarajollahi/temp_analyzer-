int sensor_read_count;
void read_sensor() {
  ++sensor_read_count;
  if (sensor_read_count >= 100) {
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
  }
  //
}