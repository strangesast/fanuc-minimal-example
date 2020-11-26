#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../external/fwlib/fwlib32.h"

short unsigned int libh;  // fwlib handle

int rdparam(short num, IODBPSD *param) {
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
  int device_port = 8193; /* typical FOCAS port */
  char device_ip[40] = "127.0.0.1";
  char cnc_id[36];
  char axes_names[MAX_AXIS * 2] = "";
  short axis_count = MAX_AXIS;
  unsigned long cnc_ids[4];
  IODBPSD param = {0}; /* reset param result memory, not set */
  ODBSYS sysinfo = {0};
  ODBAXISNAME axes[MAX_AXIS] = {{0}};

  if (argc < 2) {
    fprintf(stderr, "%% Usage: %s <ip> <port>\n", argv[0]);
    return 1;
  }
  if (argc >= 3) {
    sscanf(argv[2], "%d", &device_port);
  }
  sscanf(argv[1], "%s", device_ip);

  if (cnc_startupprocess(0, "focas.log") != EW_OK) {
    fprintf(stderr, "Failed to create required log file!\n");
    return 1;
  }

  printf("Connecting to %s:%d\n", device_ip, device_port);

  // library handle.  needs to be closed when finished.
  if (cnc_allclibhndl3(device_ip, device_port, 10 /* timeout */, &libh) !=
      EW_OK) {
    fprintf(stderr, "Failed to connect to cnc!\n");
    return 1;
  }
  atexit(cleanup);

  // get cnc information
  // axis_count set by rdaxisname
  if (cnc_sysinfo(libh, &sysinfo) != EW_OK ||
      cnc_rdcncid(libh, cnc_ids) != EW_OK ||
      cnc_rdaxisname(libh, &axis_count, axes) != EW_OK) {
    fprintf(stderr, "Failed to get cnc info!\n");
    return 1;
  }

#if __SIZEOF_LONG__ == 8
  sprintf(cnc_id, "%08lx-%08lx-%08lx-%08lx", cnc_ids[0] & 0xffffffff,
          cnc_ids[0] >> 32 & 0xffffffff, cnc_ids[1] & 0xffffffff,
          cnc_ids[1] >> 32 & 0xffffffff);
#else
  sprintf(cnc_id, "%08lx-%08lx-%08lx-%08lx", cnc_ids[0] & 0xffffffff,
          cnc_ids[1] & 0xffffffff, cnc_ids[2] & 0xffffffff,
          cnc_ids[3] & 0xffffffff);
#endif

  // ','.join(cnc_ids)
  char *j = axes_names;
  for (int i = 0; i < axis_count; i++) {
    if (i > 0) *(j++) = ',';
    *(j++) = axes[i].name;
  }
  *j = '\0';

  printf("Retrieved info from cnc!\nid: %s\naxes: %d (%s)\nseries: %.4s\n",
         cnc_id, axis_count, axes_names, sysinfo.series);

  // read parameter (part count)
  if (rdparam(6711, &param)) {
    fprintf(stderr, "Failed to get part count!\n");
    return 1;
  }

  printf("part count (%d): %ld\n", param.datano, param.u.ldata);

  return 0;
}
