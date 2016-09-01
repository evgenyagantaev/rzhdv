// D:\Work\Keil\L4_AKP\NUCLEO\Src\ReportDescriptor\DescAKP.hid
// char ReportDescriptor[28] = {
/*----------    in usbd_conf.h      -----------*/
//#define USBD_CUSTOMHID_OUTREPORT_BUF_SIZE    64
/*----------   (defined in Cube MX) -----------*/
//#define USBD_CUSTOM_HID_REPORT_DESC_SIZE     28

//#ifndef __USBD_DescAKP__H__
//#define __USBD_DescAKP__H__
//#ifdef __cplusplus
// extern "C" {
//#endif

//__ALIGN_BEGIN static uint8_t CUSTOM_HID_ReportDesc_FS[USBD_CUSTOM_HID_REPORT_DESC_SIZE] __ALIGN_END =
//{
  /* USER CODE BEGIN 0 */ 
    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
    0x09, 0x00,                    // USAGE (Undefined)
    0xA1, 0x01,                    // COLLECTION (Application)
    0x26, 0xFF, 0x00,              //   LOGICAL_MAXIMUM (255)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x09, 0x00,                    //   USAGE (Undefined)
    0x75, 0x08,                    //   REPORT_SIZE (8)
    0x95, 0x10,                    //   REPORT_COUNT (16)
    0x81, 0x02,                    //   INPUT (Data,Var,Abs)
    0x09, 0x00,                    //   USAGE (Undefined)
    0x75, 0x08,                    //   REPORT_SIZE (8)
    0x95, 0x10,                    //   REPORT_COUNT (16)
    0x91, 0x02,                    //   OUTPUT (Data,Var,Abs)
  /* USER CODE END 0 */ 
//  0xC0    /*     END_COLLECTION	             */
   
//}; 
//#ifdef __cplusplus
//}
//#endif

//#endif //__USBD_DescAKP__H__
