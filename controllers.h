using Controller = void (*)( CycleActor &, CycleActor * );
using Effect = void (*)( CycleActor &target );

void killActor( CycleActor &a ){
    a.hide();
    a.mode = 0;
}

Effect effects[] = {
    
    []( CycleActor &t ){ t.speedX <<= 1; },
    []( CycleActor &t ){ t.speedX = 0; },
    []( CycleActor &t ){ t.speedX = -t.speedX; },
    []( CycleActor &t ){ t.targetY = t.frame >= 5 ? 200 : -200; },
    []( CycleActor &t ){ t.noCollision = 50; },
    []( CycleActor &t ){ t.noCollision = 150; },
    

};

Controller controllers[] = {

// dead
    []( CycleActor &a, CycleActor * ){},

// player controller
    []( CycleActor &a, CycleActor *all ){

	if( doPhysics( a, a.frame >= 5 ) ){
	       
	    if( isPressed(RIGHT_BUTTON) ){
		a.speedX += 10;
	    }else if( isPressed(LEFT_BUTTON) ){
		a.speedX -= 10;
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

		    effects[ (other->mode-2)%( sizeof(effects)/sizeof(effects[0])) ]( a );

		    killActor( *other );
		
		});
	}

	offsetX = a.wx - (0x4000);
	
    }

};
