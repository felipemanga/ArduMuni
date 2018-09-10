uint8_t landscape[128];
uint8_t heightmap[128];
uint32_t offsetX, prevOffsetX;
int32_t prevDelta;
uint32_t score;

const char *effect;

void killActor( CycleActor &a ){
    a.hide();
    a.mode = 0;
}

bool common( CycleActor &a, bool kill ){
    uint32_t sx = a.wx - offsetX;
    a.x = sx;
    bool oob = sx >= 0x8000;
    if( oob && kill )
	killActor(a);
    return oob;
}

bool doPhysics( CycleActor &actor, bool flipped ){

    if( common(actor,false) )
	return;

    actor.y += actor.targetY << 4;
    actor.targetY -= actor.targetY >> 4;
    
    bool contact;
    if( flipped )
	contact = (actor.yH <= heightmap[ actor.xH ]);
    else
	contact = (actor.yH >= heightmap[ actor.xH ]);
    
    if( contact ){

	if( (flipped?-actor.targetY:actor.targetY) > 0 )
	    actor.targetY -= actor.targetY>>2;

	actor.yH = heightmap[ actor.xH ];

	int16_t incline = (
	    heightmap[ (actor.xH-5) ]
	    - heightmap[ (actor.xH+5) ]
	    );

	if( flipped ) incline = -incline;
	actor.speedX -= incline << 4;
	
	if( actor.speedX < 0 ) incline = -incline;
	actor.targetY -= incline;
	
    }else{
	
	int8_t g = 4;
	if( flipped ) g=-g;
	actor.targetY+=g;
	
    }
    
    actor.speedX -= actor.speedX >> 8;
    actor.wx += actor.speedX >> 2;
    actor.x = actor.wx - offsetX;

    return contact;
}

void initLandscape(){
    uint8_t tmp[128];

    for( uint8_t x=0; x<128; ++x )
	landscape[x] = noise3( x, 13, 40, 60 ) * 64;
    
    for( uint8_t s=0; s<2; ++s ){
	for( uint8_t x=0; x<128; ++x )
	    tmp[x]=(landscape[(x-1)&0x7F]+landscape[x]+landscape[(x+1)&0x7F])>>2;
	for( uint8_t x=0; x<128; ++x )
	    landscape[x] = ( tmp[(x-1)&0x7F] + tmp[x] + tmp[(x+1)&0x7F] )>>2;
    }
    
    for( uint8_t x=0; x<128; ++x )
	landscape[x] = 64 - landscape[x];

}

void drawLandscapeSection( int16_t x0, int16_t y0, int16_t x1, int16_t y1 ){
    // arduboy.drawLine( x0, y0, x1, y1, WHITE );
  // bresenham's algorithm - thx wikpedia
  bool steep = abs(y1 - y0) > abs(x1 - x0);
  if (steep) {
    arduboy.swap(x0, y0);
    arduboy.swap(x1, y1);
  }

  if (x0 > x1) {
    arduboy.swap(x0, x1);
    arduboy.swap(y0, y1);
  }

  int16_t dx, dy;
  dx = x1 - x0;
  dy = abs(y1 - y0);

  int16_t err = dx / 2;
  int8_t ystep;

  if (y0 < y1)
  {
    ystep = 1;
  }
  else
  {
    ystep = -1;
  }

  for (; x0 <= x1; x0++)
  {
    if (steep)
    {
	// drawPixel(y0, x0, color);
	arduboy.drawFasterVLine( y0, 0, x0 );
	if( uint8_t(y0)<128 )
	    heightmap[y0] = x0;
    }
    else
    {
	// drawPixel(x0, y0, color);
	arduboy.drawFasterVLine( x0, 0, y0 );
	if( uint8_t(x0)<128 )
	    heightmap[x0] = y0;
    }

    err -= dy;
    if (err < 0)
    {
      y0 += ystep;
      err += dx;
    }
  }
}

void drawLandscape(){
    prevDelta = int32_t( offsetX - prevOffsetX ) >> 8;
    prevOffsetX = offsetX;

    uint16_t x = offsetX >> 8;
    uint8_t cx = x >> 5;
    int8_t cc = - (x & 0x1F);
    
    for( uint8_t c=0; c<5; ++c, ++cx ){
	drawLandscapeSection(
	    (c<<5) + cc,
	    landscape[cx&0x7F],
	    ((c+1)<<5) + cc,
	    landscape[(cx+1)&0x7F]
	    );
    }
    
}
