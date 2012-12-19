/* xrwhisto.c
 *
 * Copyright 2012 David G. Barnes
 *
 * This file is part of S2VOLSURF.
 *
 * S2VOLSURF is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License,
 * or (at your option) any later version.
 *
 * S2VOLSURF is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with S2VOLSURF.  If not, see <http://www.gnu.org/licenses/>. 
 *
 * We would appreciate it if research outcomes using S2VOLSURF would
 * provide the following acknowledgement:
 *
 * "Three-dimensional visualisation was conducted with the S2PLOT
 * progamming library"
 *
 * and a reference to
 *
 * D.G.Barnes, C.J.Fluke, P.D.Bourke & O.T.Parry, 2006, Publications
 * of the Astronomical Society of Australia, 23(2), 82-93.
 *
 * $Id: xrwhisto.c 70 2012-11-22 23:00:34Z barnesd $
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "cpgplot.h"
#include "libxrw.c"

int main(int argc, char **argv) {
  
  if (argc != 2) {
    fprintf(stderr, "Usage: %s xrwfilename\n", argv[0]);
    return -1;
  }

  XRAW_STRUCT *xr = loadXraw(argv[1]);
  if (!xr) {
    fprintf(stderr, "Failed to open or read '%s'.\n", argv[1]);
    return -1;
  }
  
  int nbin = 256;
  float x[256];
  float data[256];
  int centre = 1;
  
  int i;
  for (i = 0; i < 256; i++) {
    x[i] = ((float)i + 0.5) / 256.0;
    data[i] = 0.;
  }
  
  for (i = 0; i < xr->nx * xr->ny * xr->nz; i++) {
    data[xr->data[i]] += 1.0;
  }

  for (i = 0; i < 256; i++) {
    data[i] = log10f(data[i]+1);
  }

  cpgopen("?");
  cpgswin(0,1.0,0,7);

  cpglab("Normalised data value", "Log(count)", argv[1]);
  cpgbox("BCNT", 0.0, 0, "BCLNT", 0.0, 0);
  cpgbin(nbin, x, data, centre);
  cpgend();

  return 0;
}
