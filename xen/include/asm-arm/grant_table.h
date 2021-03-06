#ifndef __ASM_GRANT_TABLE_H__
#define __ASM_GRANT_TABLE_H__

#include <xen/grant_table.h>

#define INVALID_GFN (-1UL)
#define INITIAL_NR_GRANT_FRAMES 1
#define GNTTAB_MAX_VERSION 1

void gnttab_clear_flag(unsigned long nr, uint16_t *addr);
int create_grant_host_mapping(unsigned long gpaddr,
        unsigned long mfn, unsigned int flags, unsigned int
        cache_flags);
#define gnttab_host_mapping_get_page_type(ro, ld, rd) (0)
int replace_grant_host_mapping(unsigned long gpaddr, unsigned long mfn,
        unsigned long new_gpaddr, unsigned int flags);
void gnttab_mark_dirty(struct domain *d, unsigned long l);
#define gnttab_create_status_page(d, t, i) do {} while (0)
#define gnttab_release_host_mappings(domain) 1
static inline int replace_grant_supported(void)
{
    return 1;
}

#define gnttab_set_frame_gfn(d, st, idx, gfn)                            \
    do {                                                                 \
        ((st) ? (d)->arch.grant_status_gfn                               \
              : (d)->arch.grant_shared_gfn)[idx] = (gfn);                \
    } while ( 0 )

#define gnttab_get_frame_gfn(d, st, idx) ({                              \
   _gfn((st) ? gnttab_status_gmfn(d, (d)->grant_table, idx)              \
             : gnttab_shared_gmfn(d, (d)->grant_table, idx));            \
})

#define gnttab_create_shared_page(d, t, i)                              \
    do {                                                                 \
        share_xen_page_with_guest(                                       \
            virt_to_page((char *)(t)->shared_raw[i]),                    \
            (d), XENSHARE_writable);                                     \
    } while ( 0 )

#define gnttab_shared_gmfn(d, t, i)                                      \
    gfn_x(((i) >= nr_grant_frames(t)) ? _gfn(INVALID_GFN)                \
                                      : (d)->arch.grant_shared_gfn[i])

#define gnttab_status_gmfn(d, t, i)                                      \
    gfn_x(((i) >= nr_status_frames(t)) ? _gfn(INVALID_GFN)               \
                                       : (d)->arch.grant_status_gfn[i])

#endif /* __ASM_GRANT_TABLE_H__ */
/*
 * Local variables:
 * mode: C
 * c-file-style: "BSD"
 * c-basic-offset: 4
 * indent-tabs-mode: nil
 * End:
 */
