#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "../external/fwlib/fwlib32.h"

#define TIMEOUT 10

short unsigned int libh;  // fwlib handle

short rdparam(short num, IODBPSD *param) {
  short ret;
  ret = cnc_rdparam(libh, num, ALL_AXES, sizeof(*param), param);
  if (ret != EW_OK) {
    fprintf(stderr, "Failed to read parameter %d: %d!\n", num, ret);
    return 1;
  }
  return 0;
}

void cleanup() {
  if (cnc_freelibhndl(libh) != EW_OK)
    fprintf(stderr, "Failed to free library handle!\n");
  cnc_exitprocess();
}

int main(int argc, char **argv) {
  int devicePort = 8193; /* typical FOCAS port */
  short axisCount = MAX_AXIS;
  char deviceIP[40] = "127.0.0.1";
  unsigned long cncIDs[4];
  char cncID[36];
  IODBPSD param = {0}; /* reset param result memory, not set */
  ODBSYS sysinfo;
  ODBAXISNAME axes[MAX_AXIS];

  if (argc < 2) {
    fprintf(stderr, "%% Usage: %s <ip> <port>\n", argv[0]);
    exit(EXIT_FAILURE);
    return 1;
  }
  if (argc >= 3) {
    sscanf(argv[2], "%d", &devicePort);
  }
  sscanf(argv[1], "%s", deviceIP);

  if (cnc_startupprocess(0, "focas.log") != EW_OK) {
    fprintf(stderr, "Failed to create required log file!\n");
    exit(EXIT_FAILURE);
    return 1;
  }

  printf("Connecting to %s:%d\n", deviceIP, devicePort);

  // library handle.  needs to be closed when finished.
  if (cnc_allclibhndl3(deviceIP, devicePort, TIMEOUT, &libh) != EW_OK) {
    fprintf(stderr, "Failed to connect to cnc!\n");
    exit(EXIT_FAILURE);
    return 1;
  }
  atexit(cleanup);

  // get cnc information
  if (cnc_sysinfo(libh, &sysinfo) != EW_OK ||
      cnc_rdcncid(libh, cncIDs) != EW_OK ||
      cnc_rdaxisname(libh, &axisCount, axes) != EW_OK) {
    fprintf(stderr, "Failed to get cnc info!\n");
    exit(EXIT_FAILURE);
    return 1;
  }

#if __SIZEOF_LONG__ == 8
  sprintf(cncID, "%08lx-%08lx-%08lx-%08lx", cncIDs[0] & 0xffffffff,
          cncIDs[0] >> 32 & 0xffffffff, cncIDs[1] & 0xffffffff,
          cncIDs[1] >> 32 & 0xffffffff);
#else
  sprintf(cncID, "%08lx-%08lx-%08lx-%08lx", cncIDs[0] & 0xffffffff,
          cncIDs[1] & 0xffffffff, cncIDs[2] & 0xffffffff,
          cncIDs[3] & 0xffffffff);
#endif

  printf("Retrieved info from cnc! (id: %s, axes: %d, series: %.4s)\n", cncID,
         axisCount, sysinfo.series);

  // read parameter (part count)
  if (rdparam(6711, &param)) {
    fprintf(stderr, "Failed to get part count!\n");
    exit(EXIT_FAILURE);
    return 1;
  }

  printf("Part count (%d): %ld\n", param.datano, param.u.ldata);

  exit(EXIT_SUCCESS);
  return 0;
}
