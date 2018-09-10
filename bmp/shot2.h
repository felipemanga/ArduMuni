/*
--    --
-      -
        
        
        
        
-      -
--    --
*/



const unsigned char PROGMEM shot2[] = {
// width, height,
8, 8,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};


const unsigned char PROGMEM shot2_mask[] = {
0x3c,0x7e,0xff,0xff,0xff,0xff,0x7e,0x3c
};



const unsigned char PROGMEM shot2_plus_mask[] = {
// width, height,
8, 8,
0x00, 0x3c,0x00, 0x7e,0x00, 0xff,0x00, 0xff,0x00, 0xff,0x00, 0xff,0x00, 0x7e,0x00, 0x3c
};


const uint8_t PROGMEM shot2_comp_w[] = {
0x07,0x07,0xf0,0x07
}; // 4b vs 8b uncompressed
const uint8_t PROGMEM shot2_comp_b[] = {
0x07,0x07,0x76,0xca,0xc6,0x9f,0x55,0x6e
}; // 8b vs 8b uncompressed
const uint8_t PROGMEM shot2_comp_a[] = {
0x07,0x07,0x76,0xca,0xc6,0x9f,0x55,0x6e
}; // 8b vs 8b uncompressed