/*
--------    -------
-------   ## ------
------   ##   -----
------   #    -----
------        -----
-------       -----
---------    ------
--------   --------
-------     -------
-------      ------
-------       -----
------        -----
------        -----
------       ------
------       ------
------        -----
------        -----
-------       -----
-------        ----
------      # #----
-----       # ##---
-----      ## ##---
----       ##  ##--
---        ##  ##--
---        ##  ----
----       ##  ----
------     ###  ---
--------## ###  ---
---------#####-----
--------#######----
--------#######----
------#####-###----
-----####---###----
-----###----###----
----##------##-----
---##-------##-----
-###--------##-----
-###---------##----
#####--------##----
#-##---------##----
---###-------##----
-------------###---
-------------####--
-------------#-####
*/



const unsigned char PROGMEM walk6[] = {
// width, height,
19, 44,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0c,0x06,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xe0,0xf8,0x00,0x38,0xf0,0xc0,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0xe8,0xf8,0xf0,0x7f,0xff,0xfc,0xe0,0x00,0x00,0x00,0x00,
0xc0,0x70,0xf0,0xf8,0x4c,0x07,0x03,0x03,0x01,0x00,0x00,0x00,0x1f,0xff,0xe3,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x01,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0f,0x07,0x0e,0x0c,0x08,0x08
};


const unsigned char PROGMEM walk6_mask[] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x1c,0x3e,0xbf,0xff,0xff,0x7f,0x7e,0x3c,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0xf8,0xff,0xff,0xff,0xff,0xff,0xfe,0x9c,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x80,0xc0,0xf0,0xf9,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0xf0,0xc0,0x00,0x00,
0x00,0x00,0x00,0x01,0x03,0x03,0x87,0x87,0xef,0xff,0xff,0x7f,0xff,0xff,0xef,0x0c,0x00,0x00,0x00,
0xc0,0x70,0xf0,0xf8,0x4c,0x07,0x03,0x03,0x01,0x00,0x00,0x00,0x1f,0xff,0xe3,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x01,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0f,0x07,0x0e,0x0c,0x08,0x08
};



const unsigned char PROGMEM walk6_plus_mask[] = {
// width, height,
19, 44,
0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x1c,0x00, 0x3e,0x00, 0xbf,0x0c, 0xff,0x06, 0xff,0x02, 0x7f,0x00, 0x7e,0x00, 0x3c,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,
0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0xf8,0x00, 0xff,0x00, 0xff,0x00, 0xff,0x00, 0xff,0x00, 0xff,0x00, 0xfe,0x00, 0x9c,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,
0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x80,0x00, 0xc0,0x00, 0xf0,0x00, 0xf9,0x00, 0xff,0x00, 0xff,0x00, 0xff,0x00, 0xff,0xe0, 0xff,0xf8, 0xff,0x00, 0xff,0x38, 0xfc,0xf0, 0xf0,0xc0, 0xc0,0x00, 0x00,0x00, 0x00,
0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x01,0x00, 0x03,0x00, 0x03,0x80, 0x87,0x80, 0x87,0xe8, 0xef,0xf8, 0xff,0xf0, 0xff,0x7f, 0x7f,0xff, 0xff,0xfc, 0xff,0xe0, 0xef,0x00, 0x0c,0x00, 0x00,0x00, 0x00,0x00, 0x00,
0xc0, 0xc0,0x70, 0x70,0xf0, 0xf0,0xf8, 0xf8,0x4c, 0x4c,0x07, 0x07,0x03, 0x03,0x03, 0x03,0x01, 0x01,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x1f, 0x1f,0xff, 0xff,0xe3, 0xe3,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,
0x00, 0x00,0x00, 0x00,0x00, 0x00,0x01, 0x01,0x01, 0x01,0x01, 0x01,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x0f, 0x0f,0x07, 0x07,0x0e, 0x0e,0x0c, 0x0c,0x08, 0x08,0x08, 0x08
};


const uint8_t PROGMEM walk6_comp_w[] = {
0x12,0x2f,0x30,0xb9,0xdc,0x06,0x65,0x2a,0x25,0xa9,0x94,0x75,0x76,0x34,0xa6,0x53,
0xa5,0x94,0x74,0x54,0xf9,0xad,0x54,0x58,0xda,0x29,0xe9,0x94,0xfc,0x4b,0xc9,0xed,
0x36,0x7a,0xa9,0x98,0x94,0xc2,0x5b,0x3a,0x1d,0xfa,0x9c,0x53,0x56,0xd9,0x75,0x3a,
0x07
}; // 49b vs 114b uncompressed
const uint8_t PROGMEM walk6_comp_b[] = {
0x12,0x2f,0x30,0xa6,0x9c,0xdc,0xa6,0x96,0xdb,0xe4,0x56,0x39,0xe4,0x22,0x2b,0xbd,
0x3a,0x34,0x66,0x77,0x72,0x4c,0x29,0x25,0xfd,0xa9,0xf1,0x96,0xde,0x6e,0x95,0x54,
0x52,0x49,0x25,0x1d,0xe7,0xd6,0xd9,0xe1,0x52
}; // 41b vs 114b uncompressed
