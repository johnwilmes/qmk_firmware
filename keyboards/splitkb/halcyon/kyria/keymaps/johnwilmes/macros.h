#pragma once

#define COMBO_ACTION_KEY KC_NO
#define BLANK(...)
#define IDENTITY(...) __VA_ARGS__

#define COMBO_PRECOG(finger1, finger2)\
    COMBO_DEF(PRECOG_##finger1##_##finger2, COMBO_ACTION_KEY, finger1, finger2)
#define PRECOG_HOMO_DEF(finger1, finger2) \
    COMBO_PRECOG(L_##finger1, L_##finger2) \
    COMBO_PRECOG(R_##finger1, R_##finger2)
#define PRECOG_HETERO_DEF(finger1, finger2) \
    COMBO_PRECOG(L_##finger1, R_##finger2) \
    COMBO_PRECOG(R_##finger1, L_##finger2)

#define EACH_PRECOG_DEF()\
    PRECOG_HOMO_DEF(THUMB_H, PINKY_H)\
    PRECOG_HOMO_DEF(THUMB_H, RING_H)\
    PRECOG_HOMO_DEF(THUMB_H, MIDDLE_H)\
    PRECOG_HOMO_DEF(THUMB_H, INDEX_H)\
    PRECOG_HOMO_DEF(THUMB_I1, PINKY_H)\
    PRECOG_HOMO_DEF(THUMB_I1, RING_H)\
    PRECOG_HOMO_DEF(THUMB_I1, MIDDLE_H)\
    PRECOG_HOMO_DEF(THUMB_I1, INDEX_H)\
    PRECOG_HOMO_DEF(THUMB_O1, PINKY_H)\
    PRECOG_HOMO_DEF(THUMB_O1, RING_H)\
    PRECOG_HOMO_DEF(THUMB_O1, MIDDLE_H)\
    PRECOG_HOMO_DEF(THUMB_O1, INDEX_H)\
    PRECOG_HETERO_DEF(THUMB_O1, THUMB_H)\
    PRECOG_HOMO_DEF(THUMB_O1, INDEX_D)

#define EACH_COMBO_DEF()\
    EACH_PRECOG_DEF()\
    COMBO_DEF(TAB, KC_TAB, L_THUMB_H, L_INDEX_D, L_INDEX_OD)\
    COMBO_DEF(ENTER, KC_ENTER, L_THUMB_H, L_INDEX_H, L_INDEX_O)\
    COMBO_DEF(DELETE, KC_DELETE, R_THUMB_H, R_INDEX_D, R_INDEX_OD)\
    COMBO_DEF(ESCAPE, KC_ESCAPE, R_THUMB_H, R_INDEX_H, R_INDEX_O)\
    COMBO_DEF(EEPROM, EEPROM_FLUSH, L_PINKY_OU, L_PINKY_O, L_PINKY_OD, R_PINKY_OU, R_PINKY_O, R_PINKY_OD)

#define MY_LAYOUT(k0G, k0F, k0E, k0D, k0C, k0B, k9C, k9A, k9B, k5B, k5C, k5D, k5E, k5F, k5G, k1G, k1F, k1E, k1D, k1C, k1B, k6B, k6C, k6D, k6E, k6F, k6G, k2G, k2F, k2E, k2D, k2C, k2B, k3D, k2A, k7A, k8D, k7B, k7C, k7D, k7E, k7F, k7G, k3E, k3C, k3B, k3F, k3A, k8A, k8F, k8B, k8C, k8E)\
    LAYOUT_split_3x6_5_hlc(k0G, k0F, k0E, k0D, k0C, k0B, k5B, k5C, k5D, k5E, k5F, k5G, k1G, k1F, k1E, k1D, k1C, k1B, k6B, k6C, k6D, k6E, k6F, k6G, k2G, k2F, k2E, k2D, k2C, k2B, k3D, k2A, k7A, k8D, k7B, k7C, k7D, k7E, k7F, k7G, k3E, k3C, k3B, k3F, k3A, k8A, k8F, k8B, k8C, k8E, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, k9A, k9B, k9C, KC_NO, KC_NO)

#define FOR_EACH_KEY_DEF(_call, ...)\
    _call(\
    KEY_DEF(L_PINKY_OU, 0, 6, __VA_ARGS__),\
    KEY_DEF(L_PINKY_U, 0, 5, __VA_ARGS__),\
    KEY_DEF(L_RING_U, 0, 4, __VA_ARGS__),\
    KEY_DEF(L_MIDDLE_U, 0, 3, __VA_ARGS__),\
    KEY_DEF(L_INDEX_U, 0, 2, __VA_ARGS__),\
    KEY_DEF(L_INDEX_OU, 0, 1, __VA_ARGS__),\
    KEY_DEF(ENC_CCW, 9, 2, __VA_ARGS__),\
    KEY_DEF(ENC_B, 9, 0, __VA_ARGS__),\
    KEY_DEF(ENC_CW, 9, 1, __VA_ARGS__),\
    KEY_DEF(R_INDEX_OU, 5, 1, __VA_ARGS__),\
    KEY_DEF(R_INDEX_U, 5, 2, __VA_ARGS__),\
    KEY_DEF(R_MIDDLE_U, 5, 3, __VA_ARGS__),\
    KEY_DEF(R_RING_U, 5, 4, __VA_ARGS__),\
    KEY_DEF(R_PINKY_U, 5, 5, __VA_ARGS__),\
    KEY_DEF(R_PINKY_OU, 5, 6, __VA_ARGS__),\
    KEY_DEF(L_PINKY_O, 1, 6, __VA_ARGS__),\
    KEY_DEF(L_PINKY_H, 1, 5, __VA_ARGS__),\
    KEY_DEF(L_RING_H, 1, 4, __VA_ARGS__),\
    KEY_DEF(L_MIDDLE_H, 1, 3, __VA_ARGS__),\
    KEY_DEF(L_INDEX_H, 1, 2, __VA_ARGS__),\
    KEY_DEF(L_INDEX_O, 1, 1, __VA_ARGS__),\
    KEY_DEF(R_INDEX_O, 6, 1, __VA_ARGS__),\
    KEY_DEF(R_INDEX_H, 6, 2, __VA_ARGS__),\
    KEY_DEF(R_MIDDLE_H, 6, 3, __VA_ARGS__),\
    KEY_DEF(R_RING_H, 6, 4, __VA_ARGS__),\
    KEY_DEF(R_PINKY_H, 6, 5, __VA_ARGS__),\
    KEY_DEF(R_PINKY_O, 6, 6, __VA_ARGS__),\
    KEY_DEF(L_PINKY_OD, 2, 6, __VA_ARGS__),\
    KEY_DEF(L_PINKY_D, 2, 5, __VA_ARGS__),\
    KEY_DEF(L_RING_D, 2, 4, __VA_ARGS__),\
    KEY_DEF(L_MIDDLE_D, 2, 3, __VA_ARGS__),\
    KEY_DEF(L_INDEX_D, 2, 2, __VA_ARGS__),\
    KEY_DEF(L_INDEX_OD, 2, 1, __VA_ARGS__),\
    KEY_DEF(L_THUMB_U, 3, 3, __VA_ARGS__),\
    KEY_DEF(L_THUMB_OU, 2, 0, __VA_ARGS__),\
    KEY_DEF(R_THUMB_OU, 7, 0, __VA_ARGS__),\
    KEY_DEF(R_THUMB_U, 8, 3, __VA_ARGS__),\
    KEY_DEF(R_INDEX_OD, 7, 1, __VA_ARGS__),\
    KEY_DEF(R_INDEX_D, 7, 2, __VA_ARGS__),\
    KEY_DEF(R_MIDDLE_D, 7, 3, __VA_ARGS__),\
    KEY_DEF(R_RING_D, 7, 4, __VA_ARGS__),\
    KEY_DEF(R_PINKY_D, 7, 5, __VA_ARGS__),\
    KEY_DEF(R_PINKY_OD, 7, 6, __VA_ARGS__),\
    KEY_DEF(L_THUMB_I2, 3, 4, __VA_ARGS__),\
    KEY_DEF(L_THUMB_I1, 3, 2, __VA_ARGS__),\
    KEY_DEF(L_THUMB_H, 3, 1, __VA_ARGS__),\
    KEY_DEF(L_THUMB_O1, 3, 5, __VA_ARGS__),\
    KEY_DEF(L_THUMB_O2, 3, 0, __VA_ARGS__),\
    KEY_DEF(R_THUMB_O2, 8, 0, __VA_ARGS__),\
    KEY_DEF(R_THUMB_O1, 8, 5, __VA_ARGS__),\
    KEY_DEF(R_THUMB_H, 8, 1, __VA_ARGS__),\
    KEY_DEF(R_THUMB_I1, 8, 2, __VA_ARGS__),\
    KEY_DEF(R_THUMB_I2, 8, 4, __VA_ARGS__)\
    )


/* Without halcyon modules
#define FOR_EACH_KEY_DEF(_call, ...)\
    _call(\
    KEY_DEF(L_PINKY_OU, 0, 6, __VA_ARGS__),\
    KEY_DEF(L_PINKY_U, 0, 5, __VA_ARGS__),\
    KEY_DEF(L_RING_U, 0, 4, __VA_ARGS__),\
    KEY_DEF(L_MIDDLE_U, 0, 3, __VA_ARGS__),\
    KEY_DEF(L_INDEX_U, 0, 2, __VA_ARGS__),\
    KEY_DEF(L_INDEX_OU, 0, 1, __VA_ARGS__),\
    KEY_DEF(R_INDEX_OU, 4, 1, __VA_ARGS__),\
    KEY_DEF(R_INDEX_U, 4, 2, __VA_ARGS__),\
    KEY_DEF(R_MIDDLE_U, 4, 3, __VA_ARGS__),\
    KEY_DEF(R_RING_U, 4, 4, __VA_ARGS__),\
    KEY_DEF(R_PINKY_U, 4, 5, __VA_ARGS__),\
    KEY_DEF(R_PINKY_OU, 4, 6, __VA_ARGS__),\
    KEY_DEF(L_PINKY_O, 1, 6, __VA_ARGS__),\
    KEY_DEF(L_PINKY_H, 1, 5, __VA_ARGS__),\
    KEY_DEF(L_RING_H, 1, 4, __VA_ARGS__),\
    KEY_DEF(L_MIDDLE_H, 1, 3, __VA_ARGS__),\
    KEY_DEF(L_INDEX_H, 1, 2, __VA_ARGS__),\
    KEY_DEF(L_INDEX_O, 1, 1, __VA_ARGS__),\
    KEY_DEF(R_INDEX_O, 5, 1, __VA_ARGS__),\
    KEY_DEF(R_INDEX_H, 5, 2, __VA_ARGS__),\
    KEY_DEF(R_MIDDLE_H, 5, 3, __VA_ARGS__),\
    KEY_DEF(R_RING_H, 5, 4, __VA_ARGS__),\
    KEY_DEF(R_PINKY_H, 5, 5, __VA_ARGS__),\
    KEY_DEF(R_PINKY_O, 5, 6, __VA_ARGS__),\
    KEY_DEF(L_PINKY_OD, 2, 6, __VA_ARGS__),\
    KEY_DEF(L_PINKY_D, 2, 5, __VA_ARGS__),\
    KEY_DEF(L_RING_D, 2, 4, __VA_ARGS__),\
    KEY_DEF(L_MIDDLE_D, 2, 3, __VA_ARGS__),\
    KEY_DEF(L_INDEX_D, 2, 2, __VA_ARGS__),\
    KEY_DEF(L_INDEX_OD, 2, 1, __VA_ARGS__),\
    KEY_DEF(L_THUMB_U, 3, 3, __VA_ARGS__),\
    KEY_DEF(L_THUMB_OU, 2, 0, __VA_ARGS__),\
    KEY_DEF(R_THUMB_OU, 6, 0, __VA_ARGS__),\
    KEY_DEF(R_THUMB_U, 7, 3, __VA_ARGS__),\
    KEY_DEF(R_INDEX_OD, 6, 1, __VA_ARGS__),\
    KEY_DEF(R_INDEX_D, 6, 2, __VA_ARGS__),\
    KEY_DEF(R_MIDDLE_D, 6, 3, __VA_ARGS__),\
    KEY_DEF(R_RING_D, 6, 4, __VA_ARGS__),\
    KEY_DEF(R_PINKY_D, 6, 5, __VA_ARGS__),\
    KEY_DEF(R_PINKY_OD, 6, 6, __VA_ARGS__),\
    KEY_DEF(L_THUMB_I2, 3, 4, __VA_ARGS__),\
    KEY_DEF(L_THUMB_I1, 3, 2, __VA_ARGS__),\
    KEY_DEF(L_THUMB_H, 3, 1, __VA_ARGS__),\
    KEY_DEF(L_THUMB_O1, 3, 5, __VA_ARGS__),\
    KEY_DEF(L_THUMB_O2, 3, 0, __VA_ARGS__),\
    KEY_DEF(R_THUMB_O2, 7, 0, __VA_ARGS__),\
    KEY_DEF(R_THUMB_O1, 7, 5, __VA_ARGS__),\
    KEY_DEF(R_THUMB_H, 7, 1, __VA_ARGS__),\
    KEY_DEF(R_THUMB_I1, 7, 2, __VA_ARGS__),\
    KEY_DEF(R_THUMB_I2, 7, 4, __VA_ARGS__)\
    )
*/
