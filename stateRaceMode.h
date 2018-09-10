STATE( RaceMode,
       {
	   CycleActor actors[6];
       },
       {
	   
	   seed = 0x1234;
	   seedSequence = 0;
	   clearScreen = CLEAR_GRAY;

	   after.init();
	   initLandscape();

	   for( uint8_t i=0; i<6; ++i ){
	       scope.actors[i].init();
	       scope.actors[i].mode = 0;
	   }

	   scope.actors[0]
	       .setPosition(0,0)
	       .setAnimation( &cycle )
	       .show()
	       .frame = 0;
	   scope.actors[0].mode = 1;

       },
       {
	   
	   drawLandscape( );

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
	   	   
	   /*
	 after.update();	 
	 move();
	 scope.ground.render();
	 updateEnemies();
	   
	 scope.player.checkCollision(
				     enemies,
				     MAX_ENEMY_COUNT,
				     []( Actor *a ){
				       auto e = (Enemy *) a;
				       if( e->timeAlive ){
					 changeState( State::FightMode, 0 );
				       }
				     });
	   */
       },

       void move(){
	   
       }
       
       )
