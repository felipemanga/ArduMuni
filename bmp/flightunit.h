/*
---------------  ---------------
---------------  ---------------
----------- -- ## -- -----------
----------  -- ## --  ----------
----------  - #### -  ----------
-- ---- --- -  ##  - --- ---- --
--  --   --  # ## #  --   --  --
-- # - ## -  # ## #  - ## - # --
-- ##   ## ####  #### ##   ## --
-- #####  ############  ##### --
-- #  ###### #    # ######  # --
---  #  ####  ####  ####  #  ---
----- ##  ## # ## # ##  ## -----
------  ## # # ## # # ##  ------
------ #  -  # ## #  -  # ------
-----  ## -- #    # -- ##  -----
---- # ## -  #    #  - ## # ----
--- ## ## -          - ## ## ---
-- ## -  - # --  -- # -  - ## --
- ## - # - # -- #-- # - # - ## -
- # ---  -  ---# ---  -  --- # -
-- ------------ #------------ --
---------------# ---------------
--------------- #---------------
---------------# ---------------
--------------- #---------------
---------------# ---------------
--------------- #---------------
---------------  ---------------
---------------  ---------------
---------------  ---------------
---------------  ---------------
*/



const unsigned char PROGMEM flightunit[] = {
// width, height,
32, 32,
0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x80,0x80,0x00,0x00,0x00,0x00,0xc0,0x10,0xfc,0xfc,0x10,0xc0,0x00,0x00,0x00,0x00,0x80,0x80,0x00,0x00,0x00,0x80,0x00,0x00,0x00,
0x00,0x00,0x00,0x07,0x03,0x0a,0x16,0xd6,0xad,0x2d,0x1e,0x3f,0x03,0xf7,0x0b,0x7a,0x7a,0x0b,0xf7,0x03,0x3f,0x1e,0x2d,0xad,0xd6,0x16,0x0a,0x03,0x07,0x00,0x00,0x00,
0x00,0x00,0x18,0x0c,0x06,0x03,0x00,0x0b,0x03,0x00,0x00,0x0c,0x00,0x01,0x00,0x50,0xa8,0x00,0x01,0x00,0x0c,0x00,0x00,0x03,0x0b,0x00,0x03,0x06,0x0c,0x18,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x05,0x0a,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};


const unsigned char PROGMEM flightunit_mask[] = {
0x00,0x00,0xe0,0xc0,0x80,0x00,0xc0,0xe0,0xc0,0x80,0x18,0xfc,0xc0,0xf0,0xfc,0xff,0xff,0xfc,0xf0,0xc0,0xfc,0x18,0x80,0xc0,0xe0,0xc0,0x00,0x80,0xc0,0xe0,0x00,0x00,
0x00,0x00,0x07,0x0f,0x0f,0x9f,0xff,0xff,0xff,0xff,0x3f,0x7f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x7f,0x3f,0xff,0xff,0xff,0xff,0x9f,0x0f,0x0f,0x07,0x00,0x00,
0x00,0x18,0x3c,0x1e,0x0f,0x07,0x0b,0x1f,0x1f,0x03,0x1c,0x1f,0x0f,0x03,0x03,0xff,0xff,0x03,0x03,0x0f,0x1f,0x1c,0x03,0x1f,0x1f,0x0b,0x07,0x0f,0x1e,0x3c,0x18,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};



const unsigned char PROGMEM flightunit_plus_mask[] = {
// width, height,
32, 32,
0x00, 0x00,0x00, 0x00,0x00, 0xe0,0x80, 0xc0,0x00, 0x80,0x00, 0x00,0x00, 0xc0,0x80, 0xe0,0x80, 0xc0,0x00, 0x80,0x00, 0x18,0x00, 0xfc,0x00, 0xc0,0xc0, 0xf0,0x10, 0xfc,0xfc, 0xff,0xfc, 0xff,0x10, 0xfc,0xc0, 0xf0,0x00, 0xc0,0x00, 0xfc,0x00, 0x18,0x00, 0x80,0x80, 0xc0,0x80, 0xe0,0x00, 0xc0,0x00, 0x00,0x00, 0x80,0x80, 0xc0,0x00, 0xe0,0x00, 0x00,0x00, 0x00,
0x00, 0x00,0x00, 0x00,0x00, 0x07,0x07, 0x0f,0x03, 0x0f,0x0a, 0x9f,0x16, 0xff,0xd6, 0xff,0xad, 0xff,0x2d, 0xff,0x1e, 0x3f,0x3f, 0x7f,0x03, 0xff,0xf7, 0xff,0x0b, 0xff,0x7a, 0xff,0x7a, 0xff,0x0b, 0xff,0xf7, 0xff,0x03, 0xff,0x3f, 0x7f,0x1e, 0x3f,0x2d, 0xff,0xad, 0xff,0xd6, 0xff,0x16, 0xff,0x0a, 0x9f,0x03, 0x0f,0x07, 0x0f,0x00, 0x07,0x00, 0x00,0x00, 0x00,
0x00, 0x00,0x00, 0x18,0x18, 0x3c,0x0c, 0x1e,0x06, 0x0f,0x03, 0x07,0x00, 0x0b,0x0b, 0x1f,0x03, 0x1f,0x00, 0x03,0x00, 0x1c,0x0c, 0x1f,0x00, 0x0f,0x01, 0x03,0x00, 0x03,0x50, 0xff,0xa8, 0xff,0x00, 0x03,0x01, 0x03,0x00, 0x0f,0x0c, 0x1f,0x00, 0x1c,0x00, 0x03,0x03, 0x1f,0x0b, 0x1f,0x00, 0x0b,0x03, 0x07,0x06, 0x0f,0x0c, 0x1e,0x18, 0x3c,0x00, 0x18,0x00, 0x00,
0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x05, 0xff,0x0a, 0xff,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00
};


const uint8_t PROGMEM flightunit_comp_w[] = {
0x1f,0x1f,0xe8,0xa3,0x4f,0x87,0xa5,0x5d,0xd2,0x6e,0x5d,0x44,0xa3,0x29,0x1d,0x7d,
0xf8,0x52,0x72,0x5d,0xc9,0xcb,0x5d,0xa9,0xae,0xee,0x52,0x4e,0xd9,0xb7,0x2a,0x5b,
0xb2,0xdc,0xe5,0xba,0x9c,0xca,0x5a,0xab,0x9c,0xaa,0xeb,0xba,0xaa,0xab,0xbb,0x5c,
0xe5,0xb6,0x0a,0x5f,0xcb,0xe5,0x72,0xb6,0xcb,0xcd,0x3b,0x57,0x94,0x95,0xab,0xca,
0x47,0x38,0xe7,0xf6,0xe2,0x5a,0xaf,0xd7,0x43,0x45,0x95,0xad,0x70,0x0f
}; // 78b vs 128b uncompressed
const uint8_t PROGMEM flightunit_comp_b[] = {
0x1f,0x1f,0x48,0x95,0xcd,0xc7,0xb6,0x5c,0xe7,0x53,0x4b,0x6b,0x77,0xbb,0x93,0x76,
0x7f,0xca,0xed,0xdf,0xaa,0x99,0xb2,0xd9,0xf5,0x74,0xd9,0xac,0xe2,0x57,0x3e,0xbb,
0xab,0xea,0x2f,0x77,0xa5,0xba,0xba,0x4b,0xb9,0x7c,0xca,0xaa,0x6c,0xc9,0x72,0x97,
0xeb,0x72,0x2a,0x6b,0x6d,0xe5,0x52,0x5d,0xd7,0x55,0x5d,0xdd,0xe5,0xaa,0xee,0x75,
0x4e,0xf1,0x2f,0x3b,0xd5,0xa9,0xce,0x26,0x2f,0x5b,0x49,0xa5,0xf6,0x4a,0x7d,0xca,
0xc9,0xec,0xd6,0x55,0xae,0xaa,0x75,0xd6,0xb9,0x4f,0x2a,0xb5,0x57,0xb2,0x52,0x97,
0x4d,0x76,0xb2,0x93,0x9d,0x1c,0x0e,0x2a,0x5b,0x39,0xbc,0x03
}; // 108b vs 128b uncompressed
const uint8_t PROGMEM flightunit_comp_a[] = {
0x1f,0x1f,0x48,0x95,0x5d,0xc7,0xb6,0x54,0x76,0x9d,0x5a,0x5a,0xbb,0x73,0xb3,0x6e,
0x9d,0xb3,0x6f,0xd5,0x4c,0xd9,0xa5,0xb2,0xd3,0x65,0x97,0x8a,0x5f,0x49,0xe7,0x9c,
0x93,0xa3,0x69,0x1d,0x1a,0xb3,0x23,0x69,0xe9,0x9c,0x53,0xfc,0x4b,0xa7,0x9c,0x72,
0x4e,0xc9,0xcb,0x49,0x25,0xd5,0x5e,0x29,0xa9,0x9c,0xdb,0x6e,0x19,0xed,0xd6,0x39,
0x29,0x95,0xda,0x4a,0x25,0xd5,0xe5,0x94,0x74,0xd2,0x49,0x27,0x87,0x82,0xf8,0xf0,
0x0e
}; // 81b vs 128b uncompressed