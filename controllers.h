using Controller = void (*)( CycleActor &, CycleActor * );
using Effect = void (*)( CycleActor &target );

char const E_SPEEDP[] PROGMEM = {"SPEED+"};
char const E_STOP[]  PROGMEM = {"STOP"};
char const E_REVERSE[] PROGMEM = {"REVERSE"};
char const E_BOUNCE[] PROGMEM = {"BOUNCE"};
char const E_INV1[] PROGMEM = {"GHOST"};
char const E_INV2[] PROGMEM = {"GHOST+"};

char * const effectNames[] PROGMEM = {
    E_SPEEDP,
    E_STOP,
    E_REVERSE,
    E_BOUNCE,
    E_INV1,
    E_INV2
};

Effect effects[] = {
    
    []( CycleActor &t ){ t.speedX <<= 1; },
    []( CycleActor &t ){ t.speedX = 0; },
    []( CycleActor &t ){ t.speedX = -t.speedX; },
    []( CycleActor &t ){ t.targetY = t.frame >= 5 ? 200 : -200; },
    []( CycleActor &t ){ t.noCollision = 50; },
    []( CycleActor &t ){ t.noCollision = 150; },

};

uint32_t level;
int32_t ttspawn;

void dead( CycleActor &a, CycleActor * );

Controller controllers[] = {

// dead
    dead,

// player controller
    []( CycleActor &a, CycleActor *all ){
	doPhysics( a, a.frame >= 5 );
	if( true ){
	       
	    if( isPressed(RIGHT_BUTTON) ){
		a.speedX += 6;
	    }else if( isPressed(LEFT_BUTTON) ){
		a.speedX -= 6;
	    }

	    bool flipped = a.frame>=5?5:0;

	    int16_t speed = a.speedX;
	    if( speed < 0 ) speed = -speed;
	    if( speed > 240 ) speed = 240;
	    speed /= 80;
	    a.frame = speed + (flipped ? 5 : 0);
	    if( a.speedX<0 )
		a.actorFlags |= ACTOR_MIRROR;
	    else
		a.actorFlags &= ~ACTOR_MIRROR;

	    if( justPressed(B_BUTTON) ){
	       
		if( flipped ) a.frame -= 5;
		else a.frame += 5;
	       
	    }else if( justPressed(A_BUTTON) ){
		a.targetY += flipped ? 70 : -70;
	    }
	       
	}

	if( !a.noCollision ){
	    a.checkCollision(
		all,
		6,
		[&]( Actor *othera ){
		    CycleActor *other = static_cast<CycleActor *>(othera);
		
		    if( other->mode <= 1 )
			return;

		    uint8_t eid = (other->mode-2)%( sizeof(effects)/sizeof(effects[0]));

		    effects[ eid ]( a );

		    const char *str;
		    pgm_read_struct( &str, &effectNames[eid] );
		    effect = str;

		    killActor( *other );
		
		});
	}

	offsetX = a.wx - (0x4000);
	
    },

// 2 - Just sit still
    []( CycleActor &a, CycleActor * ){
	if( common(a,true) ) return;
    },

// 3 - take off
    []( CycleActor &a, CycleActor * ){
	a.wx += prevDelta < 0 ? 128 : -128;
	if( common(a,true) ) return;
	a.y -= ((heightmap[ a.xH ]<<8) - a.y) >> 3;
    },

// 4 - Bob
    []( CycleActor &a, CycleActor * ){
	if( common(a,true) ) return;
	a.y = int16_t(SIN( arduboy.frameCount )) << 4 + 32;
    },
    
};

void dead( CycleActor &a, CycleActor *all ){
    if( prevDelta == 0 )
	return;
	
    if( ttspawn < 0 ){
	ttspawn = 512;
	a.mode = 2 + level%3;
	a.show();
	a.wx = offsetX + (prevDelta > 0 ? 0x7FFF:0);
	a.frame = (a.mode-2)%10;
	common( a, false );
	a.yH = heightmap[ a.xH ];
    }
}
