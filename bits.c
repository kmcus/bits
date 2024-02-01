#include <bits.h>
#include <string.h>

#define MAX_BITS 32

#if OS == ZEPHYR
#define mem_alloc k_malloc
#define mem_free k_free
#endif

#ifndef mem_alloc
#error mem_alloc is not defined
#endif

#ifndef mem_free
#error mem_free is not defined, using free
#endif

char *bits_describe(uint32_t value, bits_value_t *bits)
{
    bits_group_t *grp;
    bits_desc_t *bit;

    char *str_ptrs[MAX_BITS];

    size_t i = 0, j, k = 0;
    size_t length = 0;

    while (grp = bits->groups[i++])
    {
        j = 0;
        uint32_t shift_mask = (1 << (grp->lst - grp->fst + 1));
        if (shift_mask > 1)
            shift_mask -= 1;

        uint32_t mask = shift_mask << grp->fst;
        // printk("mask: %u\n", mask);

        while (bit = &grp->bits[j++], bit->desc)
        {
            uint32_t bits = bit->val << grp->fst;
            // printk("value/mask/bits: %u/%u/%u %s\n", value, mask, bits, bit->desc);

            if ((value & mask) == bits)
            {
                str_ptrs[k++] = bit->desc;
                length += strlen(bit->desc) + 1;
                break;
            }
        }
        if (!bit->desc)
        {
            str_ptrs[k++] = "X";
            length += 2;
        }
    }

    char *buf = mem_alloc(length);
    i = 0;
    char *buf_ptr = buf;
    while (i < k)
    {
        size_t len = strlen(str_ptrs[i]);
        strcpy(buf_ptr, str_ptrs[i]);
        buf_ptr += len;
        *(buf_ptr++) = '|';
        i++;
    }
    *(buf_ptr - 1) = 0;

    return buf;
}