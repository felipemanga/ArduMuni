/*
  #  #  
   # #  
### ## #
  ### # 
 # ###  
# ## ###
  # #   
  #  #  
*/



const unsigned char PROGMEM shot1[] = {
// width, height,
8, 8,
0x24,0x14,0xed,0x3a,0x5c,0xb7,0x28,0x24
};


const unsigned char PROGMEM shot1_mask[] = {
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff
};



const unsigned char PROGMEM shot1_plus_mask[] = {
// width, height,
8, 8,
0x24, 0xff,0x14, 0xff,0xed, 0xff,0x3a, 0xff,0x5c, 0xff,0xb7, 0xff,0x28, 0xff,0x24, 0xff
};


const uint8_t PROGMEM shot1_comp_w[] = {
0x07,0x07,0xee,0x5c,0xa5,0xea,0x54,0xa5,0x9c,0xaa,0x54,0x97,0xaa,0x5c,0x37
}; // 15b vs 8b uncompressed
const uint8_t PROGMEM shot1_comp_b[] = {
0x07,0x07,0xef,0x5c,0xa5,0xea,0x54,0xa5,0x9c,0xaa,0x54,0x97,0xaa,0x5c,0x37
}; // 15b vs 8b uncompressed
const uint8_t PROGMEM shot1_comp_a[] = {
0x07,0x07,0xf1,0x07
}; // 4b vs 8b uncompressed
