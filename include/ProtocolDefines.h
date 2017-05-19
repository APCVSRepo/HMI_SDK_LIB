#ifndef __PROTOCOL_DEFINES_H__
#define __PROTOCOL_DEFINES_H__

#define ALERT_TIMEOUT                   0
#define ALERT_CLICK_SOFTBUTTON          1
#define ALERT_ABORTED                   2

#define SCROLLMESSAGE_TIMEOUT           0
#define SCROLLMESSAGE_CLICK_SOFTBUTTON  1
#define SCROLLMESSAGE_REJECTED          2

#define BUTTON_SHORT                    0
#define BUTTON_LONG                     1

#define PERFORMINTERACTION_TIMEOUT      10
#define PERFORMINTERACTION_CHOICE       0

#define SLIDER_OK                       0
#define SLIDER_TIMEOUT                  10
#define SLIDER_ABORTED                  5

#define PERFORMAUDIOPASSTHRU_TIMEOUT    0
#define PERFORMAUDIOPASSTHRU_RETYP      7
#define PERFORMAUDIOPASSTHRU_DONE       0
#define PERFORMAUDIOPASSTHRU_CANCEL     5

#define SPEEK_OK                        0
#define SPEEK_INTERRUPTED               5

typedef enum
{
    TOUCH_START,
    TOUCH_MOVE,
    TOUCH_END
}TOUCH_TYPE;

#endif
