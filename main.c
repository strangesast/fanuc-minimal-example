#include <stdio.h>
#include <stdlib.h>
#include "./external/fwlib/fwlib32.h"

#define TIMEOUT 10

short unsigned int libh;  // fwlib handle

void cleanup() {
  short ret = cnc_freelibhndl(libh);
  if (ret != EW_OK) {
    fprintf(stderr, "Failed to free library handle!\n");
  }
}

int main(int argc, char **argv) {
  short ret;
  int devicePort;
  short axisCount = MAX_AXIS;
  char deviceIP[40];
  ODBSYS sysinfo;
  ODBAXISNAME axes[MAX_AXIS];

  if (argc != 3) {
    fprintf(stderr, "%% Usage: %s <ip> <port>\n", argv[0]);
    exit(EXIT_FAILURE);
    return 1;
  }
  sscanf(argv[2], "%d", &devicePort);
  sscanf(argv[1], "%s", deviceIP);

  ret = cnc_startupprocess(0, "focas.log");
  if (ret != EW_OK) {
    fprintf(stderr, "Failed to create required log file!\n");
    exit(EXIT_FAILURE);
    return 1;
  }

  printf("Connecting to %s:%d\n", deviceIP, devicePort);

  // library handle.  needs to be closed when finished.
  ret = cnc_allclibhndl3(deviceIP, devicePort, TIMEOUT, &libh);
  if (ret != EW_OK) {
    fprintf(stderr, "Failed to connect to cnc!\n");
    exit(EXIT_FAILURE);
    return 1;
  }
  atexit(cleanup);

  if (cnc_sysinfo(libh, &sysinfo) != EW_OK ||
      cnc_rdaxisname(libh, &axisCount, axes) != EW_OK) {
    fprintf(stderr, "Failed to get cnc info!\n");
    exit(EXIT_FAILURE);
    return 1;
  }

  printf("Retrieved info from cnc! (axes: %d, series: %.4s)\n", axisCount,
         sysinfo.series);

  exit(EXIT_SUCCESS);
  return 0;
}
