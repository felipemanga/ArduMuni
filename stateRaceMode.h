STATE( RaceMode,
       {
	   CycleActor actors[6];
       },
       {
	   
	   seed = 0x3095;
	   seedSequence = 0;
	   clearScreen = CLEAR_GRAY;

	   after.init();
	   initLandscape();
	   score = -8;

	   for( uint8_t i=0; i<6; ++i ){
	       scope.actors[i].init().setAnimation(&enemyanim);
	       scope.actors[i].mode = 0;
	   }

	   scope.actors[0]
	       .setPosition(0,0)
	       .setAnimation( &cycle )
	       .show()
	       .frame = 0;
	   scope.actors[0].mode = 1;

	   effect = PSTR("Go!");

       },
       {
	   
	   drawLandscape( );

	   score += abs(prevDelta) >> 3;
	   level += abs(prevDelta);
	   uint32_t lsd = level >> 8;
	   if( lsd > 255 ) lsd = 255;
	   if( ttspawn >= 0 ) ttspawn -= lsd;

	   arduboy.setCursor(1,1);
	   arduboy.print( score );
	   arduboy.print( F("  ") );
	   arduboy.print( reinterpret_cast<const __FlashStringHelper *>(effect) );

	   for( uint8_t i=0; i<6; ++i ){
	       
	       if( scope.actors[i].noCollision ){
		   scope.actors[i].noCollision--;
		   if( !scope.actors[i].noCollision ){
		       scope.actors[i].flags &= ~ANIM_GRAY;
		   }else{
		       scope.actors[i].flags |= ANIM_GRAY;
		   }
	       }
	       
	       controllers[ scope.actors[i].mode ]( scope.actors[i], scope.actors );
	   }
       }
       
       )
