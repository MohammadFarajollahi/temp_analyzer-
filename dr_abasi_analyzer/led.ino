

void lv_example_led_1(void)
{
    /*Create a LED and switch it OFF*/
    led1  = lv_led_create(lv_scr_act());
    lv_obj_align(led1, LV_ALIGN_TOP_LEFT, 165, 50);
    lv_led_off(led1);
}