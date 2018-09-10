#include <Arduboy2.h>

class Arduboy2Ext : public Arduboy2 {
public:    
    Arduboy2Ext() : Arduboy2() { }
    
    void drawCompressed(int16_t sx, int16_t sy, const uint8_t *bitmap, uint8_t color, bool mirror=false );

    void drawFasterVLine( int16_t x, int16_t y, uint8_t h, uint8_t color=0xFF )
    {

      if( static_cast<uint16_t>(x)>=WIDTH )
	return;

      if( y>=HEIGHT )
	return;

      if( y < 0 ){
	if( y+h < 0 ) return;
	h += y;
	y = 0;
      }

      if( y+h > HEIGHT )
	h = HEIGHT - y;

      uint16_t row = x + (y / 8) * WIDTH;
      uint8_t offset = y&7;
      
      if( offset ){
	
	uint8_t mask = 0xFF;

	if( h < 8-offset ){
	  mask >>= (8-h);
	  h = 0;
	}else{
	  h -= 8-offset;
	}

	mask <<= offset;
	
	sBuffer[row] = ( sBuffer[row] & ~mask ) | (color & mask);
	row += WIDTH;
	
      }
      
      while( h>=8 ){
	
	sBuffer[row] = color;
	h -= 8;
	row += WIDTH;	  
	  
      }

      if( h>0 ){
	
	uint8_t mask = 0xFF >> (8-h);
	sBuffer[row] = ( sBuffer[row] & ~mask ) | (color & mask);
	
      }
      
    }
    
};

struct BitStreamReader {

  const uint8_t *source;
  uint16_t sourceIndex;
  uint8_t bitBuffer;
  uint8_t byteBuffer;
  
  BitStreamReader(const uint8_t *source)
    : source(source), sourceIndex(), bitBuffer(), byteBuffer()
  {
  }
  
  uint16_t readBits(uint16_t bitCount)
  {
    uint16_t result = 0;
    for (uint16_t i = 0; i < bitCount; i++)
    {
      if (this->bitBuffer == 0)
      {
        this->bitBuffer = 0x1;
        this->byteBuffer = pgm_read_byte(&this->source[this->sourceIndex]);
        ++this->sourceIndex;
      }
      
      if ((this->byteBuffer & this->bitBuffer) != 0)
        result |= (1 << i); // result |= bitshift_left[i];
        
      this->bitBuffer <<= 1;
    }
    return result;
  }
  
};


const unsigned char reverse[] PROGMEM = {0,128,64,192,32,160,96,224,16,144,80,208,48,176,112,240,8,136,72,200,40,168,104,232,24,152,88,216,56,184,120,248,4,132,68,196,36,164,100,228,20,148,84,212,52,180,116,244,12,140,76,204,44,172,108,236,28,156,92,220,60,188,124,252,2,130,66,194,34,162,98,226,18,146,82,210,50,178,114,242,10,138,74,202,42,170,106,234,26,154,90,218,58,186,122,250,6,134,70,198,38,166,102,230,22,150,86,214,54,182,118,246,14,142,78,206,46,174,110,238,30,158,94,222,62,190,126,254,1,129,65,193,33,161,97,225,17,145,81,209,49,177,113,241,9,137,73,201,41,169,105,233,25,153,89,217,57,185,121,249,5,133,69,197,37,165,101,229,21,149,85,213,53,181,117,245,13,141,77,205,45,173,109,237,29,157,93,221,61,189,125,253,3,131,67,195,35,163,99,227,19,147,83,211,51,179,115,243,11,139,75,203,43,171,107,235,27,155,91,219,59,187,123,251,7,135,71,199,39,167,103,231,23,151,87,215,55,183,119,247,15,143,79,207,47,175,111,239,31,159,95,223,63,191,127,255};

void Arduboy2Ext::drawCompressed(int16_t sx, int16_t sy, const uint8_t *bitmap, uint8_t color, bool mirror)
{
  // set up decompress state

  BitStreamReader cs = BitStreamReader(bitmap);

  // read header

  int width = (int)cs.readBits(8) + 1;
  int height = (int)cs.readBits(8) + 1;
  uint8_t spanColour = (uint8_t)cs.readBits(1); // starting colour

  // no need to draw at all if we're offscreen
  if ((sx + width < 0) || (sx > WIDTH - 1) || (sy + height < 0) || (sy > HEIGHT - 1))
    return;

  // sy = sy - (frame * height);

  int yOffset = abs(sy) % 8;
  int startRow = sy / 8;
  if (sy < 0) {
    startRow--;
    yOffset = 8 - yOffset;
  }
  int rows = height / 8;
  if ((height % 8) != 0)
    ++rows;

  int rowOffset = 0; // +(frame*rows);
  int columnOffset = 0;
  
  if (mirror) {
    columnOffset = width - 1;
  }
  else {
    columnOffset = 0;
  }

  uint8_t byte = 0x00;
  uint8_t bit = 0x01;
  while (rowOffset < rows) // + (frame*rows))
  {
    uint16_t bitLength = 1;
    while (cs.readBits(1) == 0)
      bitLength += 2;

    uint16_t len = cs.readBits(bitLength) + 1; // span length

    // draw the span
    for (uint16_t i = 0; i < len; ++i)
    {
      if (spanColour != 0)
        byte |= bit;
      bit <<= 1;

      if (bit == 0) // reached end of byte
      {
        // draw
        int bRow = startRow + rowOffset;

        //if (byte) // possible optimisation
        if ((bRow <= (HEIGHT / 8) - 1) && (bRow > -2) && (columnOffset + sx <= (WIDTH - 1)) && (columnOffset + sx >= 0))
        {
          int16_t offset = (bRow * WIDTH) + sx + columnOffset;
          if (bRow >= 0)
          {
            int16_t index = offset;
            uint8_t value = byte << yOffset;
            
            if (color != 0)
              sBuffer[index] |= value;
            else
              sBuffer[index] &= ~value;
          }
          if ((yOffset != 0) && (bRow < (HEIGHT / 8) - 1))
          {
            int16_t index = offset + WIDTH;
            uint8_t value = byte >> (8 - yOffset);
            
            if (color != 0)
              sBuffer[index] |= value;
            else
              sBuffer[index] &= ~value;
          }
        }


        // iterate
        if (!mirror) {
          ++columnOffset;
          if (columnOffset >= width)
          {
            columnOffset = 0;
            ++rowOffset;
          }
        }
        else {
          --columnOffset;
          if (columnOffset < 0) {
            columnOffset = width - 1;
            ++rowOffset;
          }
        }


        // reset byte
        byte = 0x00;
        bit = 0x01;
      }
    }

    spanColour ^= 0x01; // toggle colour bit (bit 0) for next span
  }
}

