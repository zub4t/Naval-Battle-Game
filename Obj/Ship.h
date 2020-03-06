#define  SIZES  {0,5,4,3,3,2}
#define  VERTICAL  1
#define  HORIZONTAL 0
typedef struct Block
{
  int hit;
  int x;
  int y;
  void (*makeHit)(int);
} Block;

typedef struct Ship
{
  int ID;
  int ID_owner;
  int type;
  /* 1- Carrier sizeof(5)
     2- BattleShip sizeof(4)
     3- Cruiser sizeof(3)
     4- Submarine sizeof(3)
     5- Destroyer sizeof(2)
  */
  Block *blocks;
  int  (*isAlive)(struct Ship);
} Ship;
