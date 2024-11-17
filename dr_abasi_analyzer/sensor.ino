int sensor_read_count;
void read_sensor() {
  ++sensor_read_count;
  if (sensor_read_count >= 15) {
    sensor_read_count = 0;
    if (sensorActive[0] == true) {
      sensor1 = thermocouple1.readCelsius();
    } else {
      sensor1 = 0;
    }

    if (sensorActive[1] == true) {
       sensor2 = thermocouple2.readCelsius();
    } else {
      sensor2 = 0;
    }

    if (sensorActive[2] == true) {
      sensor3 = thermocouple3.readCelsius();
    } else {
      sensor3 = 0;
    }
    update_chart();
  }
  //Serial.println(String(sensor1));
  update_sensor_labels(label1, label2, label3);
}