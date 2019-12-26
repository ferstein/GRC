#ifndef VISCA_DEFINITIONS_H
#define VISCA_DEFINITIONS_H

//++++++++++++++++++++++VISCA DECLARATIONS FOR FCB_ER8300++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/**********************/
/* Message formatting */
/**********************/
#define VISCA_DEFAULT_CAM_NR     0x01
#define VISCA_COMMAND            0x01
#define VISCA_CATEGORY_INTERFACE 0x00
#define VISCA_CATEGORY_CAM1      0x04
#define VISCA_CATEGORY_CAM2      0x07
#define VISCA_CATEGORY_PT        0x06
#define VISCA_CATEGORY_ADVANCED  0x05
#define VISCA_CATEGORY_EXTENDED  0x7E
#define VISCA_INQUIRY            0x09
#define VISCA_TERMINATOR         0xFF
#define VISCA_BROADCAST          0x88
#define VISCA_HEADER             0x80


/* Known Vendor IDs */
#define VISCA_VENDOR_SONY      0x0020
#define VISCA_MODEL_FCB_ER8300 0x0700
#define VISCA_MODEL_FCB_CR8300 0x0701

//____________ ERROR CODES ______________________

/* these two are defined by me, not by the specs. */
#define VISCA_SUCCESS                    0x00
#define VISCA_FAILURE                    (-1)

/* specs errors: */
#define VISCA_ERROR_MESSAGE_LENGTH       0x01
#define VISCA_ERROR_SYNTAX               0x02
#define VISCA_ERROR_CMD_BUFFER_FULL      0x03
#define VISCA_ERROR_CMD_CANCELLED        0x04
#define VISCA_ERROR_NO_SOCKET            0x05
#define VISCA_ERROR_CMD_NOT_EXECUTABLE   0x41

/* Generic definitions */
#define VISCA_ON                         0x02
#define VISCA_OFF                        0x03
#define VISCA_RESET                      0x00
#define VISCA_UP                         0x02
#define VISCA_DOWN                       0x03

/* response types */
#define VISCA_RESPONSE_CLEAR             0x40
#define VISCA_RESPONSE_ADDRESS           0x30
#define VISCA_RESPONSE_ACK               0x40
#define VISCA_RESPONSE_COMPLETED         0x50
#define VISCA_RESPONSE_INQIRY            0x50
#define VISCA_RESPONSE_ERROR             0x60
#define VISCA_RESPONSE_INTERFACE_BROADCAST   0x01

#endif // VISCA_DEFINITIONS_H
