#include "Logging.h"
#include "WS_Lite.h"
#include "internal/Utils.h"

#include <fstream>
#include <random>

namespace SL {
namespace WS_LITE {

    // Based on utf8_check.c by Markus Kuhn, 2005
    // https://www.cl.cam.ac.uk/~mgk25/ucs/utf8_check.c
    // Optimized for predominantly 7-bit content by Alex Hultman, 2016
    bool isValidUtf8(unsigned char *s, size_t length)
    {
        for (unsigned char *e = s + length; s != e;) {
            if (s + 4 <= e && ((*(uint32_t *)s) & 0x80808080) == 0) {
                s += 4;
            }
            else {
                while (!(*s & 0x80)) {
                    if (++s == e) {
                        return true;
                    }
                }

                if ((s[0] & 0x60) == 0x40) {
                    if (s + 1 >= e || (s[1] & 0xc0) != 0x80 || (s[0] & 0xfe) == 0xc0) {
                        return false;
                    }
                    s += 2;
                }
                else if ((s[0] & 0xf0) == 0xe0) {
                    if (s + 2 >= e || (s[1] & 0xc0) != 0x80 || (s[2] & 0xc0) != 0x80 || (s[0] == 0xe0 && (s[1] & 0xe0) == 0x80) ||
                        (s[0] == 0xed && (s[1] & 0xe0) == 0xa0)) {
                        return false;
                    }
                    s += 3;
                }
                else if ((s[0] & 0xf8) == 0xf0) {
                    if (s + 3 >= e || (s[1] & 0xc0) != 0x80 || (s[2] & 0xc0) != 0x80 || (s[3] & 0xc0) != 0x80 ||
                        (s[0] == 0xf0 && (s[1] & 0xf0) == 0x80) || (s[0] == 0xf4 && s[1] > 0x8f) || s[0] > 0xf4) {
                        return false;
                    }
                    s += 4;
                }
                else {
                    return false;
                }
            }
        }
        return true;
    }

    char *ZlibInflate(char *data, size_t &length, size_t maxPayload, std::string &dynamicInflationBuffer, z_stream &inflationStream,
                      char *inflationBuffer)
    {
        dynamicInflationBuffer.clear();

        inflationStream.next_in = (Bytef *)data;
        inflationStream.avail_in = length;

        int err;
        do {
            inflationStream.next_out = (Bytef *)inflationBuffer;
            inflationStream.avail_out = LARGE_BUFFER_SIZE;
            err = ::inflate(&inflationStream, Z_FINISH);
            if (!inflationStream.avail_in) {
                break;
            }

            dynamicInflationBuffer.append(inflationBuffer, LARGE_BUFFER_SIZE - inflationStream.avail_out);
        } while (err == Z_BUF_ERROR && dynamicInflationBuffer.length() <= maxPayload);

        inflateReset(&inflationStream);

        if ((err != Z_BUF_ERROR && err != Z_OK) || dynamicInflationBuffer.length() > maxPayload) {
            length = 0;
            return nullptr;
        }

        if (dynamicInflationBuffer.length()) {
            dynamicInflationBuffer.append(inflationBuffer, LARGE_BUFFER_SIZE - inflationStream.avail_out);

            length = dynamicInflationBuffer.length();
            return (char *)dynamicInflationBuffer.data();
        }

        length = LARGE_BUFFER_SIZE - inflationStream.avail_out;
        return inflationBuffer;
    }

} // namespace WS_LITE
} // namespace SL
