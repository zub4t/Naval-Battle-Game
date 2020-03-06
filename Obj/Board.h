
typedef struct PBoard
{
  int shipBlocksAlive;
  int size;
  int **Mboard;
  void (*toSting)(int size, struct PBoard board);
} PBoard;
