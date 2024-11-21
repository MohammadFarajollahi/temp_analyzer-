#include "FS.h"
#include "SD.h"
#include "SPI.h"
#define CS_PIN 32  // پایه CS برای ESP32-S3 (می‌تواند بسته به سیم‌کشی تغییر کند)

//*****sensor****
//#include "pic_show.h"
#include <max6675.h>

// تعریف پین‌های ارتباطی برای هر سنسور
int thermoDO1 = 25, thermoCS1 = 26, thermoCLK1 = 33;
int thermoDO2 = 25, thermoCS2 = 27, thermoCLK2 = 33;
int thermoDO3 = 25, thermoCS3 = 14, thermoCLK3 = 33;

// ایجاد اشیاء برای هر سنسور
MAX6675 thermocouple1(thermoCLK1, thermoCS1, thermoDO1);
MAX6675 thermocouple2(thermoCLK2, thermoCS2, thermoDO2);
MAX6675 thermocouple3(thermoCLK3, thermoCS3, thermoDO3);

#include <Arduino.h>
#include <lvgl.h>
#define LGFX_USE_V1
#include <LovyanGFX.hpp>
//#include "my_font.h"
class LGFX : public lgfx::LGFX_Device {
  lgfx::Panel_ILI9488 _panel_instance;
  //lgfx::Panel_ILI9486 _panel_instance;
  lgfx::Light_PWM _light_instance;
  lgfx::Bus_SPI _bus_instance;
  lgfx::Touch_XPT2046 _touch_instance;
public:

  LGFX(void) {
    {
      auto cfg = _bus_instance.config();  // バス設定用の構造体を取得します。

      // SPIバスの設定
      cfg.spi_host = VSPI_HOST;  // 使用するSPIを選択  ESP32-S2,C3 : SPI2_HOST or SPI3_HOST / ESP32 : VSPI_HOST or HSPI_HOST
      // ※ ESP-IDFバージョンアップに伴い、VSPI_HOST , HSPI_HOSTの記述は非推奨になるため、エラーが出る場合は代わりにSPI2_HOST , SPI3_HOSTを使用してください。
      cfg.spi_mode = 0;                   // SPI通信モードを設定 (0 ~ 3)
      cfg.freq_write = 40000000;          // 送信時のSPIクロック (最大80MHz, 80MHzを整数で割った値に丸められます)
      cfg.freq_read = 16000000;           // 受信時のSPIクロック
      cfg.spi_3wire = true;               // 受信をMOSIピンで行う場合はtrueを設定
      cfg.use_lock = true;                // トランザクションロックを使用する場合はtrueを設定
      cfg.dma_channel = SPI_DMA_CH_AUTO;  // 使用するDMAチャンネルを設定 (0=DMA不使用 / 1=1ch / 2=ch / SPI_DMA_CH_AUTO=自動設定)
      // ※ ESP-IDFバージョンアップに伴い、DMAチャンネルはSPI_DMA_CH_AUTO(自動設定)が推奨になりました。1ch,2chの指定は非推奨になります。
      cfg.pin_sclk = 18;                       // SPIのSCLKピン番号を設定
      cfg.pin_mosi = 23;                       // SPIのMOSIピン番号を設定
      cfg.pin_miso = 19;                       // SPIのMISOピン番号を設定 (-1 = disable)
      cfg.pin_dc = 2;                          // SPIのD/Cピン番号を設定  (-1 = disable)
      _bus_instance.config(cfg);               // 設定値をバスに反映します。
      _panel_instance.setBus(&_bus_instance);  // バスをパネルにセットします。
    }

    {  // 表示パネル制御の設定を行います。
      auto cfg = _panel_instance.config();
      cfg.pin_cs = 4;    // CS
      cfg.pin_rst = -1;   // RST
      cfg.pin_busy = -1;  // BUSY
      cfg.panel_width = 320;
      cfg.panel_height = 480;
      cfg.offset_x = 0;
      cfg.offset_y = 0;
      cfg.offset_rotation = 0;
      cfg.dummy_read_pixel = 8;
      cfg.dummy_read_bits = 1;
      cfg.readable = true;
      cfg.invert = false;
      cfg.rgb_order = false;
      cfg.dlen_16bit = false;  // 16bit
      cfg.bus_shared = true;   // SDカードとバスを共有している場合 trueに設定(drawJpgFile等でバス制御を行います)
      cfg.memory_width = 320;
      cfg.memory_height = 480;
      _panel_instance.config(cfg);
    }

    {
      auto cfg = _touch_instance.config();
      cfg.x_min = 0;
      cfg.x_max = 319;
      cfg.y_min = 0;
      cfg.y_max = 479;
      cfg.pin_int = -1;
      cfg.bus_shared = true;
      cfg.offset_rotation = 0;
      cfg.spi_host = VSPI_HOST;
      cfg.freq = 1000000;
      cfg.pin_sclk = 18;  // SCLK
      cfg.pin_mosi = 23;  // MOSI
      cfg.pin_miso = 19;  // MISO
      cfg.pin_cs = 16;     //   CS
      _touch_instance.config(cfg);
      _panel_instance.setTouch(&_touch_instance);
    }
    setPanel(&_panel_instance);
  }
};
LGFX tft;
/*Change to your screen resolution*/
static const uint16_t screenWidth = 480;
static const uint16_t screenHeight = 320;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[screenWidth * screenHeight / 10];



/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p) {
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);

  tft.startWrite();
  tft.setAddrWindow(area->x1, area->y1, w, h);
  //tft.pushColors((uint16_t *)&color_p->full, w * h, true);
  tft.writePixels((lgfx::rgb565_t *)&color_p->full, w * h);
  tft.endWrite();

  lv_disp_flush_ready(disp_drv);
}

/*Read the touchpad*/
void my_touchpad_read(lv_indev_drv_t *indev_drv, lv_indev_data_t *data) {
  uint16_t touchX, touchY;
  bool touched = tft.getTouch(&touchX, &touchY);
  if (!touched) {
    data->state = LV_INDEV_STATE_REL;
  } else {
    data->state = LV_INDEV_STATE_PR;
    /*Set the coordinates*/
    data->point.x = touchX;
    data->point.y = touchY;
  }
}


float sensor1;
float sensor2;
float sensor3;
lv_obj_t *label1;
lv_obj_t *label2;
lv_obj_t *label3;
lv_style_t style_label;
lv_style_t style_label2;
lv_style_t style_label3;
lv_style_t style_label4;
lv_style_t style_label5;
lv_style_t style_label6;
lv_style_t style_label7;
lv_style_t style_label_sd;
lv_style_t style_clock;
lv_style_t style_label_usb;
lv_obj_t *battery_bg;    // برای بدنه باتری
lv_obj_t *battery_fill;  // برای نمایش مقدار شارژ
lv_obj_t *chart;
lv_chart_series_t *ser1, *ser2, *ser3;
lv_obj_t *cb1, *cb2, *cb3;
lv_obj_t *checkbox;
lv_obj_t *label_new;
lv_obj_t *btn_new;
lv_obj_t *label_start;
lv_obj_t *btn_start;
lv_obj_t *label_stop;
lv_obj_t *btn_stop;
lv_obj_t *label_save;
lv_obj_t *btn_save;
lv_obj_t *fileNameInput;  // ورودی نام فایل
lv_obj_t *btn_keyboard;   // دکمه کیبورد
lv_obj_t *kb;
lv_obj_t *button_sd;
lv_obj_t *label_sd;
lv_obj_t *button_usb;
lv_obj_t *label_usb;  // کیبورد مجازی
lv_obj_t *label_time;
String fileName;                  // متغیر ذخیره نام فایل
lv_obj_t *btn_confirm;            // دکمه تأیید
lv_coord_t originalX, originalY;  // ذخیره موقعیت اصلی فیلد ورودی
lv_obj_t *terminal;
bool sensorActive[3] = { false, false, false };  // فرض کنید که سه سنسور داریم
int charj;

const int image_width = 16;
const int image_height = 16;

int sd_ok = 0;
int usb_ok = 0;
int usb_chek_count;
int usb_timer;
bool usbConnected = false;
String time_show;
int min_;
int sec_;
int hu_;
int start_program;
int stop_program;
#define USB_DETECT_PIN 39  // پین متصل به VBUS
File dataFile;
const char *terminalText;
String file_name;
//TIMER
// #include "driver/timer.h"  // برای کار با تایمرهای سخت‌افزاری

// // تابع وقفه تایمر
// void IRAM_ATTR onTimer(void *param) {
//   if (start_program == 1) {
//     ++sec_;
//     if (sec_ > 59) {
//       sec_ = 0;
//       ++min_;
//       if (min_ > 59) {
//         min_ = 0;
//         ++hu_;
//       }
//     }
//   }
// }


////////////////////////////////////////////////////////////
void setup() {
  Serial.begin(115200); /* prepare for possible serial debug */
  Serial.println("start...");
                        //TIMER
  // timer_config_t config = {
  //   .alarm_en = TIMER_ALARM_EN,
  //   .counter_en = TIMER_PAUSE,
  //   .intr_type = TIMER_INTR_LEVEL,
  //   .counter_dir = TIMER_COUNT_UP,
  //   .auto_reload = TIMER_AUTORELOAD_EN, // مقدار صحیح
  //   .divider = 8000 // تقسیم‌کننده فرکانس
  // };

  // timer_init(TIMER_GROUP_0, TIMER_0, &config);
  // timer_set_counter_value(TIMER_GROUP_0, TIMER_0, 0); // مقدار اولیه تایمر
  // timer_set_alarm_value(TIMER_GROUP_0, TIMER_0, 1000); // 1 ثانیه
  // timer_enable_intr(TIMER_GROUP_0, TIMER_0); // فعال‌سازی وقفه
  // timer_isr_register(TIMER_GROUP_0, TIMER_0, onTimer, NULL, ESP_INTR_FLAG_IRAM, NULL); // ثبت وقفه
  // timer_start(TIMER_GROUP_0, TIMER_0); // شروع تایمر

  pinMode(USB_DETECT_PIN, INPUT);
  if (!SD.begin(CS_PIN)) {
    Serial.println("Failed to initialize SD card.");
    //return;
  }
  String LVGL_Arduino = "Hello Arduino! ";
  LVGL_Arduino += String('V') + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();

  Serial.println(LVGL_Arduino);
  Serial.println("I am LVGL_Arduino");


  tft.begin();        /* TFT init */
  tft.setRotation(3); /* Landscape orientation, flipped */
  uint16_t calData[] = { 3779, 3907, 3839, 304, 318, 3879, 329, 283 };
  tft.setTouchCalibrate(calData);
  lv_init();
  lv_disp_draw_buf_init(&draw_buf, buf, NULL, screenWidth * screenHeight / 10);

  /*Initialize the display*/
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  /*Change the following line to your display resolution*/
  disp_drv.hor_res = screenWidth;
  disp_drv.ver_res = screenHeight;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&disp_drv);

  /*Initialize the (dummy) input device driver*/
  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_touchpad_read;
  lv_indev_drv_register(&indev_drv);
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////

  tft.fillScreen(TFT_BLACK);
  tft.setCursor(10, 10);
  String s1 = "Start ...";
  tft.setTextFont(1);
  tft.setTextSize(2);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.println(s1);
  Serial.print("Wait ...");
  delay(300);
  if (!SD.begin(CS_PIN)) {
    Serial.println("Failed to initialize SD card.");
    tft.setCursor(10, 30);
    s1 = "Failed to initialize SD card.";
    tft.println(s1);
    sd_ok = 0;
  } else {
    tft.setCursor(10, 30);
    s1 = "SD card ok";
    tft.println(s1);
    sd_ok = 1;
  }
  usb_ok = 0;
  delay(500);
  // tft.fillScreen(TFT_BLACK);
  // // tft.drawJpgFile(SD, "/logo.jpg", 0, 0);
  // tft.pushImage(0, 0, 480, 320, my_image);
  // delay(1000);

  create_labels();
  create_battery_shape();  // ایجاد نمایشگر باتری
  create_battery_chart();  // chart
  button_create();
  sd_card();
  timer_();
  charj = 75;
  //show_uart("start");
}

void loop() {
  lv_timer_handler(); /* let the GUI do its work */
  lv_show();
  usb_check();
  program_config();
  delay(5);

  // if (Serial.available() > 0) {
  //   String input = Serial.readStringUntil('\n');  // Read input until newline

  //   // Update the terminal with the new text
  //   lv_textarea_add_text(terminal, input.c_str());
  //   lv_textarea_add_text(terminal, "\n");  // Add new line
  // }
}
