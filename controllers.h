using Controller = void (*)( CycleActor & );

Controller controllers[] = {

// dead
    []( CycleActor &a ){},

// player controller
    []( CycleActor &a ){

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

	offsetX = a.wx - (0x4000);
	
    }

};
