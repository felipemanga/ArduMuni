#include "music.h"

#include "bmp/title.h"

#include "bmp/unicycle.h"
#include "shapes.h"
#include "bmp/shot1.h"
#include "bmp/shot2.h"

struct {
    AnimHeader header;
    AnimFrameWB f;
} const titleAnim PROGMEM = {
    {
	ANIM_WHITE,
	1, 0
    },
    { title_comp_a }
};

class CycleActor : public Actor {
public:
    uint32_t wx;
    int16_t speedX;
    uint8_t mode;
    uint8_t noCollision;
};

struct {
    AnimHeader header;
    AnimFrameWBXY s[10];
} const cycle PROGMEM = {
    {
	ANIM_WHITE |
	ANIM_BLACK |
	ANIM_OFFSET,
	10, 0,
	6, 11
    },
    {
	{
	    unicycle1_comp_w,
	    unicycle1_comp_b,
	    -3, -10
	},
	{
	    unicycle2_comp_w,
	    unicycle2_comp_b,
	    -3, -10
	},
	{
	    unicycle3_comp_w,
	    unicycle3_comp_b,
	    -3, -10
	},
	{
	    unicycle4_comp_w,
	    unicycle4_comp_b,
	    -3, -10
	},
	{
	    unicycle5_comp_w,
	    unicycle5_comp_b,
	    -3, -10
	},

	{
	    unicycle6_comp_w,
	    unicycle6_comp_b,
	    -3, 0
	},
	{
	    unicycle7_comp_w,
	    unicycle7_comp_b,
	    -3, 0
	},
	{
	    unicycle8_comp_w,
	    unicycle8_comp_b,
	    -3, 0
	},
	{
	    unicycle9_comp_w,
	    unicycle9_comp_b,
	    -3, 0
	},
	{
	    unicycle10_comp_w,
	    unicycle10_comp_b,
	    -3, 0
	}

    }
};

struct {
    AnimHeader header;
    AnimFrameWB f[10];
} const enemyanim PROGMEM = {
    {
	ANIM_BLACK | ANIM_WHITE,
	10, 0, 13, 13
    },
    {
	{
	    shape1_comp_w,
	    shape1_comp_b
	},
	{
	    shape2_comp_w,
	    shape2_comp_b
	},
	{
	    shape3_comp_w,
	    shape3_comp_b
	},
	{
	    shape4_comp_w,
	    shape4_comp_b
	},
	{
	    shape5_comp_w,
	    shape5_comp_b
	},
	{
	    shape6_comp_w,
	    shape6_comp_b
	},
	{
	    shape7_comp_w,
	    shape7_comp_b
	},
	{
	    shape8_comp_w,
	    shape8_comp_b
	},
	{
	    shape9_comp_w,
	    shape9_comp_b
	},
	{
	    shape10_comp_w,
	    shape10_comp_b
	}
    }
};

struct {
    AnimHeader header;
    AnimFrameWXY f[2];
} const shot PROGMEM = {
    {
	ANIM_WHITE |
	ANIM_INVERT |
	ANIM_OFFSET,
	1, 0,
	8, 8
    },
    {
//	{ shot1_comp_a, -4, -4 },
	{ shot2_comp_a, -4, -4 }
    }
};

uint16_t seed, seedSequence;

uint16_t NOISE( uint8_t x, uint8_t y, uint8_t z ){
    return ((SIN( (uint16_t(((y)+seed)/z)*13) + (uint16_t(((x)+seed)/z)*78) )*289&0xFF)*z);
}

int8_t random(int8_t min, int8_t max){
    return (SIN( (arduboy.frameCount*13+(seedSequence++)*79)*seed )*23789&0x3FF>>2 ) % (max-min) + min;
}

uint8_t noise3( uint8_t x, uint8_t y, uint8_t a, uint8_t b ){
    int16_t acc = 0;// 0x80;
    acc += NOISE( x, y, 4 );
    acc += NOISE( x, y, 2 );
    acc += NOISE( x, y, 1 );

    acc >>= 4;

    if( acc > b ) return 2;
    if( acc > a ) return 1;
    return 0;
    
}

uint8_t noise1( uint8_t x, uint8_t y, uint8_t a ){
    int16_t acc = 0;// 0x80;
    acc += NOISE( x, y, 4 );
    acc += NOISE( x, y, 2 );
    acc += NOISE( x, y, 1 );

    acc >>= 4;

    if( acc > a ) return 1;
    return 0;
    
}

#include "landscape.h"
#include "controllers.h"

typedef uint8_t (*PointCB)( uint8_t x, uint8_t y );

struct TileWindow {
    const unsigned char *tileset;
    uint8_t matrix[81];
    int16_t tx, ty;
    int16_t x, y;
    int8_t speedX, speedY;
    PointCB point;

    void clear(){
	for( uint8_t i=0; i<81; ++i )
	    matrix[i] = 0xFF;
    }
    
    void init( const unsigned char * tileset, PointCB p ){
	point = p;
	this->tileset = tileset;
	tx = ty = x = y = 0;
	speedX = speedY = 0;
	clear();
    }

    void shift( int8_t x, int8_t y ){
	if( x > 8 || y > 8 || x < -8 || y < -8 ){
	    clear();
	    return;
	}

	int8_t sy = 0, ey = 9, iy = 1, by = 9;
	int8_t sx = 0, ex = 9, ix = 1, bx = 9;
	if( y < 0 ){
	    iy = -1;
	    ey = -1;
	    sy = 8;
	    by = -1;
	}
	if( x < 0 ){
	    ix = -1;
	    ex = -1;
	    sx = 8;
	    bx = -1;
	}
	ey -= y;
	ex -= x;

	int8_t y9 = y*9;
  
	for( int8_t cy=sy; cy!=ey; cy += iy ){
	    int8_t cy9 = cy * 9;
	    for( int8_t cx=sx; cx!=ex; cx += ix )
		matrix[cy9+cx] = matrix[cy9+y9+cx+x];
	    for( int8_t cx=ex; cx!=bx; cx += ix )
		matrix[cy9+cx] = 0xFF;
	}
	
	for( int8_t cy=ey; cy!=by; cy += iy ){
	    int8_t cy9 = cy * 9;
	    for( int8_t cx=sx; cx!=bx; cx += ix )
		matrix[cy9+cx] = 0xFF;
	}
	
    }

    void tileToScreen( int16_t &x, int16_t &y ){
	x = x - this->tx;
	y = y - this->ty;
	x <<= 4;
	y <<= 4;
	x += this->x & 0xF;
	y += this->y & 0xF;
    }

    void render( ){
	const uint8_t size = 16;

	int16_t x = this->x + speedX;
	int16_t y = this->y + speedY;
	
	int8_t xL = x & 0xF;
	int8_t yL = y & 0xF;
	uint8_t xH = -x >> 4;
	uint8_t yH = -y >> 4;

	if( xL ) xH++;
	xL -= size;

	if( yL ) yH++;
	yL -= size;


	int8_t xd = xH - this->tx;
	int8_t yd = yH - this->ty;
	
	this->tx = xH;
	this->ty = yH;
	this->x = x;
	this->y = y;

	if( xd || yd )
	    shift( xd, yd );

	for( uint8_t ry=0; ry<5; ++ry ){
	    uint8_t ry9 = ry * 9;
	    int8_t screenY = ry*size+yL+cameraOffsetY;
	    for( uint8_t rx=0; rx<9; ++rx ){
		uint8_t i = ry9+rx;
		uint8_t tile = matrix[i];
		
		if( tile == 0xFF )
		    tile = matrix[i] = point(rx+xH, yH+ry);

		if( tile != 0xFF ){
		    Sprites::drawBitmap(
			rx*size+xL+cameraOffsetX,
			screenY,
			// (const uint8_tp) pgm_read_word( tileset+tile ),
			tileset+tile*32,
			NULL,
			16,16,
			2
			);
		}
		
	    }
	}
    }
};

struct LiveActor : public Actor {
    uint8_t hp;
    uint8_t immune;
    
    void (*onDamage)( LiveActor *actor );
    
    void damage( uint8_t amt ){
	if( !amt || !hp || immune ) return;
	
	if( amt > hp )
	    amt = hp;
	hp -= amt;
	immune = 5;
	flags |= ANIM_GRAY;
	
	(*onDamage)( this );
	
    }

    void update(){
	if( immune ){
	    immune--;
	    if( !immune )
		flags &= ~ANIM_GRAY;
	}
    }
};

struct Shot : public Actor {
    int8_t dx, dy, ttl;

    Actor *search;
    uint8_t searchCount;
    uint8_t searchSize;
    
    Actor &init( Actor &shooter, Actor *search, uint8_t searchCount, uint8_t searchSize ){
	ttl = 60;
	this->search = search;
	this->searchCount = searchCount;
	this->searchSize = searchSize;
	Actor::init()
	    .setAnimation( &shot );
	
	x = shooter.x;
	y = shooter.y;
	flags |= ANIM_INVERT;
	actorFlags &= ~ACTOR_HIDDEN;
	
	return *this;
    }
};

#define MAX_SHOT_COUNT 15

struct Enemy : public LiveActor {

    uint8_t timeAlive;
    uint8_t id;
    union{
	void *data;
	uint16_t data16;
	struct{
	    uint8_t dataA;
	    uint8_t dataB;
	};
    };
    void (*ai)( Enemy * );
    void (*shoot)( Enemy * );
    
    Actor &init(){
	Actor::init();
	hp = 0;
	timeAlive = 0;
	ai = NULL;
	return *this;
    }

    void destroy(){
	actorFlags |= ACTOR_HIDDEN;
	timeAlive = 0;
	hp = 0;
	ai = shoot = NULL;
	left = right = top = bottom = 0;
    }

    void update(){
	LiveActor::update();
	
	(*ai)( this );
	timeAlive++;
	    
	if( shoot && (timeAlive+id*167)%128==0 )
	    (*shoot)( this );	    
	if( !hp )
	    timeAlive = 0;
	if( !timeAlive )
	    destroy();
    }
    
};

#define MAX_ENEMY_COUNT 9


Enemy enemies[MAX_ENEMY_COUNT];
Shot shots[MAX_SHOT_COUNT];
Delayed<5> after;

Enemy *allocEnemy(){
    Enemy *enemy = NULL;
    uint8_t oldestIndex = 0, oldestAge = enemies[0].timeAlive;
    
    for( uint8_t i=0; i<MAX_ENEMY_COUNT; ++i ){
        enemy = &enemies[i];
	
	if( enemy->timeAlive ){
	    if( enemy->timeAlive > oldestAge ){
		oldestAge = enemy->timeAlive;
		oldestIndex = i;
	    }
	    enemy = &enemies[oldestIndex];
	}else{
	    enemy->init();
	    break;
	}
	
    }
    
    return enemy;
}

Shot *allocShot(){
    for( uint8_t i=0; i<MAX_SHOT_COUNT; ++i ){
	Shot &shot = shots[i];
	if( !shot.ttl )
	    return &shot;
    }
    return NULL;
}

void updateShots(){
    for( uint8_t i=0; i<MAX_SHOT_COUNT; ++i ){
	Shot &shot = shots[i];
	if( shot.ttl ){
	    
	    shot.xH += shot.dx;
	    shot.yH += shot.dy;

	    shot.ttl--;
	    
	    shot.checkCollision(
		shot.search,
		shot.searchSize,
		shot.searchCount,
		[]( Actor *target ){
		    ((LiveActor *)target)->damage(20);
		}
		);
	    
	    if( !shot.ttl )
		shot.actorFlags |= ACTOR_HIDDEN;


	}
    }
}

struct Pattern {
    int8_t startX, startY;
    uint8_t startAngle, angleDelta;
    int8_t radiusX, radiusY,
	radiusDelta;
    int8_t deltaX, deltaY, tweenWeight;
};

void patternAI( Enemy *e ){
    Pattern pattern;

    if( e->tweenWeight )
	return;

    uint8_t time = e->timeAlive;
    
    pgm_read_struct( &pattern, (const uint8_t *) e->data );

    int16_t x, y, a;
    a = pattern.startAngle;
    a += int16_t(pattern.angleDelta)*time;
	       
    x = COS(a) * (
	int16_t(pattern.radiusX)*2 +
	int16_t(pattern.radiusDelta)*time
	);
    x += (int16_t(pattern.deltaX)*time*16);
    x >>= 8;
    x += pattern.startX;

    y = SIN(a) * (
	int16_t(pattern.radiusY)*2 +
	int16_t(pattern.radiusDelta)*time
	);
    y += (int16_t(pattern.deltaY)*time*16);
    y >>= 8;
    y += pattern.startY;
    
    if( pattern.tweenWeight && time > 1 ){
	e->moveTo( x, y )
	    .setTweenWeight( pattern.tweenWeight );
    }else{
	e->setPosition( x, y );
    }

}

typedef bool (*SpawnCallback)(
    Enemy &,
    uint8_t waveId
    );

struct Wave {
    uint8_t enemySpawnDelay, defaultEnemySpawnDelay;
    uint8_t enemySpawnCount, defaultEnemySpawnCount;
    uint8_t waveDelay, defaultWaveDelay, id;
    SpawnCallback onSpawn;
    void update();
    void init(
	uint8_t waveDelay,
	uint8_t spawnDelay,
	uint8_t spawnCount,
	SpawnCallback onSpawn
	);
};

void Wave::init(
    uint8_t waveDelay,
    uint8_t spawnDelay,
    uint8_t spawnCount,
    SpawnCallback onSpawn
    ){
    id = 0xFF;
    this->waveDelay = defaultWaveDelay = waveDelay;
    enemySpawnDelay = 0; defaultEnemySpawnDelay = spawnDelay;
    enemySpawnCount = 0; defaultEnemySpawnCount = spawnCount;
    this->onSpawn = onSpawn;
}
    
void Wave::update(){
    waveDelay -= arduboy.frameCount & 1;
    if( waveDelay ){

	if( !enemySpawnCount || enemySpawnDelay-- ) return;
	
	enemySpawnDelay = defaultEnemySpawnDelay;

	auto enemy = allocEnemy();
	enemySpawnCount--;

	if( enemy ){
	    enemy->id = defaultEnemySpawnCount-enemySpawnCount;
	    (*onSpawn)( *enemy, id );
	}
	
    }else{
	
	id++;
	waveDelay = 4*30;
	enemySpawnCount = defaultEnemySpawnCount;
	enemySpawnDelay = 0;
	
    }
	   
}

void updateEnemies( ){
    
    for( uint8_t i=0; i<MAX_ENEMY_COUNT; ++i ){
	auto &enemy = enemies[i];
	if( enemy.timeAlive )
	    enemy.update();	
    }

}

void initEnemies(){
    
    for( uint8_t i=0; i<MAX_ENEMY_COUNT; ++i ){
	auto &enemy = enemies[i];
	enemy.show();
	enemy.destroy();
    }

}

void initShots(){
    
    for( uint8_t i=0; i<MAX_SHOT_COUNT; ++i ){
	Shot &shot = shots[i];
	shot.show();
	shot.ttl = 0;
	shot.actorFlags = ACTOR_HIDDEN;
    }

}

/*
  startX startY
  startAngle angleDelta
  radiusX radiusY radiusDelta
  deltaX, deltaY, tweenWeight;
*/
       
const Pattern patterns[] PROGMEM = {
    { // O Right 1
	127,22,
	127,1,
	100,10,0,
	0,0,0
    },
    { // O Left 2
	0,22,
	205,0xFF,
	100,10,0,
	0,0,0
    },
    { // Coil Top Left 3
	0,0,
	0,5,
	10,10,0,
	17,5,0
    },
    { // Coil Top Right 4
	127,0,
	0,5,
	10,10,0,
	-17,5,0
    },
    { // Mosquito Top Right 5
	127, 16,
	0,180,
	0,15,0,
	-15,0,2	       
    },	   
    { // Mosquito Mid Left 6
	0, 32,
	0,180,
	0,15,0,
	15,0,2	       
    },	   
    { // ZigZag Left 7
	30,-15, 
	0,5,
	15,0,0,
	0,10,
	0 
    },
    { // ZigZag Right 8
	128-30,-15, 
	0,255-5,
	15,0,0,
	0,10,
	0
    },
    { // O Top 9
	64,-10,
	0,1,
	60,50,0,
	0,0,0
    },
    { // O Top2 10
	64,-10,
	128,0xFF,
	40,40,0,
	0,0,0
    },
    { // O Bottom 11
	64,64,
	0,0xFF,
	50,50,0,
	0,0,0
    },
    { // ZigZag big 12
	64,-15, 
	0,1,
	70,0,0,
	0,3,2 
    },
    { // v-line 13
	64,-15, 
	0,0,
	0,0,0,
	0,15,0 
    }
    
};

State nextState;
uint8_t transitionColor;
void changeState( State ns, uint8_t tc ){
    nextState = ns;
    state = State::Transition;
    clearScreen = CLEAR_NONE;
    transitionColor = tc;
}

