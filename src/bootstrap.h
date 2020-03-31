
#ifndef RVM_SRC_BOOTSTRAP_H
#define RVM_SRC_BOOTSTRAP_H

const unsigned char bootstrap[616] =
    {
        0x52, 0x49, 0x54, 0x45, 0x30, 0x30, 0x30, 0x36,
        0xbd, 0xf8, 0x00, 0x00, 0x02, 0x68, 0x4d, 0x41,
        0x54, 0x5a, 0x30, 0x30, 0x30, 0x30, 0x49, 0x52,
        0x45, 0x50, 0x00, 0x00, 0x02, 0x1a, 0x30, 0x30,
        0x30, 0x32, 0x00, 0x00, 0x00, 0x8f, 0x00, 0x01,
        0x00, 0x03, 0x00, 0x02, 0x00, 0x00, 0x00, 0x16,
        0x61, 0x01, 0x56, 0x02, 0x00, 0x5d, 0x01, 0x00,
        0x61, 0x01, 0x56, 0x02, 0x01, 0x5d, 0x01, 0x01,
        0x0e, 0x01, 0x01, 0x37, 0x01, 0x67, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x07,
        0x72, 0x65, 0x71, 0x75, 0x69, 0x72, 0x65, 0x00,
        0x00, 0x10, 0x72, 0x65, 0x71, 0x75, 0x69, 0x72,
        0x65, 0x5f, 0x72, 0x65, 0x6c, 0x61, 0x74, 0x69,
        0x76, 0x65, 0x00, 0x00, 0x00, 0x00, 0xc3, 0x00,
        0x03, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x23, 0x00, 0x00, 0x00, 0x33, 0x04, 0x00, 0x00,
        0x10, 0x03, 0x4f, 0x04, 0x00, 0x1b, 0x05, 0x00,
        0x50, 0x04, 0x4f, 0x05, 0x01, 0x50, 0x04, 0x01,
        0x05, 0x01, 0x50, 0x04, 0x4f, 0x05, 0x00, 0x50,
        0x04, 0x2e, 0x03, 0x01, 0x01, 0x37, 0x03, 0x00,
        0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x01, 0x2f, 0x00, 0x00, 0x00, 0x02, 0x00, 0x08,
        0x53, 0x54, 0x44, 0x5f, 0x50, 0x41, 0x54, 0x48,
        0x00, 0x00, 0x08, 0x72, 0x76, 0x6d, 0x5f, 0x6c,
        0x6f, 0x61, 0x64, 0x00, 0x00, 0x00, 0x03, 0xd5,
        0x00, 0x03, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00,
        0x00, 0xcd, 0x00, 0x00, 0x33, 0x04, 0x00, 0x00,
        0x1b, 0x03, 0x00, 0x01, 0x04, 0x01, 0x2e, 0x03,
        0x01, 0x01, 0x4f, 0x04, 0x00, 0x41, 0x03, 0x23,
        0x03, 0x00, 0x67, 0x1b, 0x03, 0x00, 0x4f, 0x04,
        0x00, 0x01, 0x05, 0x01, 0x50, 0x04, 0x4f, 0x05,
        0x01, 0x50, 0x04, 0x2e, 0x03, 0x02, 0x01, 0x23,
        0x03, 0x00, 0x62, 0x10, 0x03, 0x4f, 0x04, 0x00,
        0x01, 0x05, 0x01, 0x50, 0x04, 0x4f, 0x05, 0x01,
        0x50, 0x04, 0x2e, 0x03, 0x03, 0x01, 0x2e, 0x03,
        0x04, 0x00, 0x23, 0x03, 0x00, 0x5d, 0x10, 0x03,
        0x1b, 0x04, 0x05, 0x4f, 0x05, 0x02, 0x2e, 0x04,
        0x06, 0x01, 0x2e, 0x03, 0x07, 0x01, 0x21, 0x00,
        0x5f, 0x0f, 0x03, 0x21, 0x00, 0x64, 0x0f, 0x03,
        0x21, 0x00, 0xcb, 0x1b, 0x03, 0x00, 0x01, 0x04,
        0x01, 0x2e, 0x03, 0x01, 0x01, 0x4f, 0x04, 0x01,
        0x41, 0x03, 0x23, 0x03, 0x00, 0x84, 0x1b, 0x03,
        0x00, 0x01, 0x04, 0x01, 0x2e, 0x03, 0x02, 0x01,
        0x23, 0x03, 0x00, 0xb1, 0x10, 0x03, 0x01, 0x04,
        0x01, 0x2e, 0x03, 0x03, 0x01, 0x2e, 0x03, 0x04,
        0x00, 0x23, 0x03, 0x00, 0xac, 0x10, 0x03, 0x1b,
        0x04, 0x05, 0x4f, 0x05, 0x02, 0x2e, 0x04, 0x06,
        0x01, 0x2e, 0x03, 0x07, 0x01, 0x21, 0x00, 0xae,
        0x0f, 0x03, 0x21, 0x00, 0xcb, 0x10, 0x03, 0x1b,
        0x04, 0x05, 0x4f, 0x05, 0x03, 0x01, 0x06, 0x01,
        0x50, 0x05, 0x4f, 0x06, 0x04, 0x50, 0x05, 0x2e,
        0x04, 0x06, 0x01, 0x2e, 0x03, 0x07, 0x01, 0x37,
        0x03, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x04, 0x2e, 0x6d, 0x72, 0x62, 0x00,
        0x00, 0x1a, 0x50, 0x72, 0x6f, 0x62, 0x6c, 0x65,
        0x6d, 0x20, 0x69, 0x6e, 0x20, 0x6e, 0x61, 0x74,
        0x69, 0x76, 0x65, 0x20, 0x66, 0x75, 0x6e, 0x63,
        0x74, 0x69, 0x6f, 0x6e, 0x00, 0x00, 0x05, 0x66,
        0x69, 0x6c, 0x65, 0x20, 0x00, 0x00, 0x0e, 0x2e,
        0x6d, 0x72, 0x62, 0x20, 0x6e, 0x6f, 0x74, 0x20,
        0x66, 0x6f, 0x75, 0x6e, 0x64, 0x00, 0x00, 0x00,
        0x08, 0x00, 0x04, 0x46, 0x69, 0x6c, 0x65, 0x00,
        0x00, 0x07, 0x65, 0x78, 0x74, 0x6e, 0x61, 0x6d,
        0x65, 0x00, 0x00, 0x06, 0x65, 0x78, 0x69, 0x73,
        0x74, 0x3f, 0x00, 0x00, 0x08, 0x72, 0x76, 0x6d,
        0x5f, 0x6c, 0x6f, 0x61, 0x64, 0x00, 0x00, 0x01,
        0x21, 0x00, 0x00, 0x0d, 0x53, 0x74, 0x61, 0x6e,
        0x64, 0x61, 0x72, 0x64, 0x45, 0x72, 0x72, 0x6f,
        0x72, 0x00, 0x00, 0x03, 0x6e, 0x65, 0x77, 0x00,
        0x00, 0x05, 0x72, 0x61, 0x69, 0x73, 0x65, 0x00,
        0x4c, 0x56, 0x41, 0x52, 0x00, 0x00, 0x00, 0x30,
        0x00, 0x00, 0x00, 0x03, 0x00, 0x08, 0x6d, 0x6f,
        0x64, 0x5f, 0x6e, 0x61, 0x6d, 0x65, 0x00, 0x01,
        0x26, 0x00, 0x05, 0x66, 0x6e, 0x61, 0x6d, 0x65,
        0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x02,
        0x00, 0x02, 0x00, 0x01, 0x00, 0x01, 0x00, 0x02,
        0x45, 0x4e, 0x44, 0x00, 0x00, 0x00, 0x00, 0x08
    };

#endif //RVM_SRC_BOOTSTRAP_H