STATE( Init,
       {
	   Actor title;
       },
       {
	   clearScreen = CLEAR_WHITE;

	   scope.title
	       .init()
	       .setPosition( 0, 64 )
	       .setAnimation( &titleAnim )
	       .moveTo(0, 0)
	       .setTweenWeight(2)
	       .show()
	       .flags |= ANIM_INVERT;
       },
       {
	  
	   // if( justPressed(A_BUTTON) ){
	       state = State::RaceMode;
	       // changeState( State::FightMode, 0xAA );
	       // }

	   if( justPressed(B_BUTTON) ){
	       Arduboy2Audio::toggle();
	       Arduboy2Audio::saveOnOff();
	   }	   
    
       }
       
    )
