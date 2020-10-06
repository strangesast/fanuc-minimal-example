#include <stdio.h>
#include <stdlib.h>
#include "../external/fwlib/fwlib32.h"

unsigned short libh;

void cleanup() {
  if (cnc_freelibhndl(libh) != EW_OK)
    fprintf(stderr, "Failed to free library handle!\n");
  cnc_exitprocess();
}

int main() {
  unsigned long cncIDs[4];
  char cncID[36];

  if (cnc_startupprocess(0, "focas.log") != EW_OK) {
    fprintf(stderr, "Failed to create required log file!\n");
    exit(EXIT_FAILURE);
    return 1;
  }

  if (cnc_allclibhndl3("127.0.0.1", 8193, 10, &libh) != EW_OK) {
    fprintf(stderr, "Failed to connect to cnc!\n");
    exit(EXIT_FAILURE);
    return 1;
  }
  atexit(cleanup);

  if (cnc_rdcncid(libh, cncIDs) != EW_OK) {
    fprintf(stderr, "Failed to read cnc id!\n");
    exit(EXIT_FAILURE);
    return 1;
  }

  if (sizeof(long) == 4) {
    sprintf(cncID, "%08lx-%08lx-%08lx-%08lx", cncIDs[0] & 0xffffffff,
            cncIDs[1] & 0xffffffff, cncIDs[2] & 0xffffffff,
            cncIDs[3] & 0xffffffff);
  } else {
    sprintf(cncID, "%08lx-%08lx-%08lx-%08lx", cncIDs[0] & 0xffffffff,
            cncIDs[0] >> 32 & 0xffffffff, cncIDs[1] & 0xffffffff,
            cncIDs[1] >> 32 & 0xffffffff);
  }
  printf("%s\n", cncID);

  exit(EXIT_SUCCESS);
}
