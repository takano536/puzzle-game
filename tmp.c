#include <limits.h>  // CHAR_BIT
#include <stdio.h>
#include <string.h>

// 記号定数
#define MSB_CRC8 (0x85)  // x8 + x7 + x2 + x0

// CRC8の計算(生成多項式:0x85,左送り)
static unsigned char GetCRC8(const void *buff, size_t size) {
    const unsigned MSB_CRC8 = 0x85;
    unsigned char *p = (unsigned char *)buff;
    unsigned char crc8;

    for (crc8 = 0x00; size != 0; size--) {
        crc8 ^= *p++;

        for (int i = 0; i < CHAR_BIT; i++) {
            if (crc8 & 0x80) {
                crc8 <<= 1;
                crc8 ^= MSB_CRC8;
            } else {
                crc8 <<= 1;
            }
        }
    }
    return crc8;
}

// メイン関数
int main(void) {
    char buff[1024];
    char *find;

    while (fgets(buff, sizeof(buff), stdin) != NULL) {
        if ((find = strchr(buff, '\n')) != NULL) {
            *find = '\0';
        }
        printf("0x%02X %s\n", GetCRC8(buff, strlen(buff)), buff);
    }
    return 0;
}