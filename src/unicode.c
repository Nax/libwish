#include <string.h>
#include <wish.h>

size_t wish_utf8_encode(char* dst, wish_unicode cp)
{
    memset(dst, 0, 4);
    if (cp < 0x80)
    {
        dst[0] = (char)(cp);
        return 1;
    }
    else if (cp < 0x800)
    {
        dst[0] = (char)(0xc0 | (cp >> 6));
        dst[1] = (char)(0x80 | (cp & 0x3f));
        return 2;
    }
    else if (cp < 0x10000)
    {
        dst[0] = (char)(0xe0 | (cp >> 12));
        dst[1] = (char)(0x80 | ((cp >> 6) & 0x3f));
        dst[2] = (char)(0x80 | (cp & 0x3f));
        return 3;
    }
    else if (cp < 0x110000)
    {
        dst[0] = (char)(0xf0 | (cp >> 18));
        dst[1] = (char)(0x80 | ((cp >> 12) & 0x3f));
        dst[2] = (char)(0x80 | ((cp >> 6) & 0x3f));
        dst[3] = (char)(0x80 | (cp & 0x3f));
        return 4;
    }
    else
    {
        return 0;
    }
}

size_t wish_utf8_decode(wish_unicode* cp, const char* src)
{
    wish_unicode codepoint;
    size_t size;

    unsigned char leader = (unsigned char)(src[0]);
    
    if (leader < 0x80)
    {
        size = 1;
        codepoint = leader;
    }
    else if (leader < 0xe0)
    {
        size = 2;
        codepoint = ((leader & ~0xc0) << 6);
        codepoint |= (((unsigned char)(src[1])) & ~0x80);
    }
    else if (leader < 0xf0)
    {
        size = 3;
        codepoint = ((leader & ~0xe0) << 12);
        codepoint |= ((((unsigned char)(src[1])) & ~0x80) << 6);
        codepoint |= ((((unsigned char)(src[2])) & ~0x80));
    }
    else
    {
        size = 4;
        codepoint = ((leader & ~0xf0) << 18);
        codepoint |= ((((unsigned char)(src[1])) & ~0x80) << 12);
        codepoint |= ((((unsigned char)(src[2])) & ~0x80) << 6);
        codepoint |= ((((unsigned char)(src[3])) & ~0x80));
    }
    *cp = codepoint;
    return size;
}

size_t wish_utf8_strlen(const char* src)
{
    size_t pos = 0;
    size_t len = 0;
    unsigned char leader;

    for (;;)
    {
        leader = (unsigned char)(src[pos]);
        if (leader == 0)
            break;
        len++;
        if (leader < 0x80)
            pos += 1;
        else if (leader < 0xe0)
            pos += 2;
        else if (leader < 0xf0)
            pos += 3;
        else
            pos += 4;
    }
    return len;
}
