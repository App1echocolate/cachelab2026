// student id: 2025200675
// please change the above line to your student id

#define _POSIX_C_SOURCE 200809L

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void printSummary(int hits, int misses, int evictions)
{
  printf("hits:%d misses:%d evictions:%d\n", hits, misses, evictions);
  FILE *output_fp = fopen(".csim_results", "w");
  assert(output_fp);
  fprintf(output_fp, "%d %d %d\n", hits, misses, evictions);
  fclose(output_fp);
}

void printHelp(const char *name)
{
  printf(
      "Usage: %s [-hv] -s <num> -E <num> -b <num> -t <file>\n"
      "Options:\n"
      "  -h         Print this help message.\n"
      "  -v         Optional verbose flag.\n"
      "  -s <num>   Number of set index bits.\n"
      "  -E <num>   Number of lines per set.\n"
      "  -b <num>   Number of block offset bits.\n"
      "  -t <file>  Trace file.\n\n"
      "Examples:\n"
      "  linux>  %s -s 4 -E 1 -b 4 -t traces/yi.trace\n"
      "  linux>  %s -v -s 8 -E 2 -b 4 -t traces/yi.trace\n",
      name, name, name);
}

typedef struct {
  int valid;
  unsigned long tag;
  unsigned long lru;
} CacheLine;

static int verbose = 0;
static int s = 0;
static int E = 0;
static int b = 0;
static int hits = 0;
static int misses = 0;
static int evictions = 0;
static unsigned long timestamp = 0;
static CacheLine **cache = NULL;

static void accessBlock(unsigned long addr)
{
  unsigned long set_index = (addr >> b) & ((1UL << s) - 1);
  unsigned long tag = addr >> (s + b);
  CacheLine *set = cache[set_index];

  for (int i = 0; i < E; i++) {
    if (set[i].valid && set[i].tag == tag) {
      hits++;
      set[i].lru = ++timestamp;
      if (verbose)
        printf(" hit");
      return;
    }
  }

  misses++;
  if (verbose)
    printf(" miss");

  int victim = -1;
  for (int i = 0; i < E; i++) {
    if (!set[i].valid) {
      victim = i;
      break;
    }
  }
  if (victim == -1) {
    evictions++;
    if (verbose)
      printf(" eviction");
    victim = 0;
    for (int i = 1; i < E; i++) {
      if (set[i].lru < set[victim].lru)
        victim = i;
    }
  }

  set[victim].valid = 1;
  set[victim].tag = tag;
  set[victim].lru = ++timestamp;
}


int main(int argc, char *argv[])
{
  char *tracefile = NULL;
  int opt;
  while ((opt = getopt(argc, argv, "hvs:E:b:t:")) != -1) {
    switch (opt) {
    case 'h':
      printHelp(argv[0]);
      return 0;
    case 'v':
      verbose = 1;
      break;
    case 's':
      s = atoi(optarg);
      break;
    case 'E':
      E = atoi(optarg);
      break;
    case 'b':
      b = atoi(optarg);
      break;
    case 't':
      tracefile = optarg;
      break;
    default:
      printHelp(argv[0]);
      return 1;
    }
  }

  if (s < 0 || E <= 0 || b < 0 || tracefile == NULL || s + b >= 64) {
    printHelp(argv[0]);
    return 1;
  }

  unsigned long num_sets = 1UL << s;
  cache = calloc(num_sets, sizeof(CacheLine *));
  assert(cache);
  for (unsigned long i = 0; i < num_sets; i++) {
    cache[i] = calloc((size_t)E, sizeof(CacheLine));
    assert(cache[i]);
  }

  FILE *fp = fopen(tracefile, "r");
  assert(fp);
  char op;
  unsigned long addr;
  int size, reg;
  while (fscanf(fp, " %c %lx,%d %d", &op, &addr, &size, &reg) == 4) {
    if (op == 'I')
      continue;
    if (verbose)
      printf("%c %lx,%d", op, addr, size);
    accessBlock(addr);
    if (verbose)
      printf("\n");
  }
  fclose(fp);

  printSummary(hits, misses, evictions);

  for (unsigned long i = 0; i < num_sets; i++)
    free(cache[i]);
  free(cache);
  return 0;
}
