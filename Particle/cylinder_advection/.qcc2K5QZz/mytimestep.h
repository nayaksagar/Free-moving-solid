#ifndef BASILISK_HEADER_26
#define BASILISK_HEADER_26
#line 1 "/home/sagar/basilisk/basilisk/src/mytimestep.h"
// note: u is weighted by fm
double timestep (const face vector u, double dtmax)
{
  static double previous = 0.;
  dtmax /= CFL;
  foreach_face(reduction(min:dtmax))
    if (u.x[] != 0.) {
      double dt = Delta/fabs(u.x[]);
#if EMBED
      assert (fm.x[]);
      dt *= fm.x[];
#else
      dt *= cm[];
#endif
      if (dt < dtmax) dtmax = dt;
    }
  dtmax *= CFL;

  /**
  We rest *previous* between successive runs. */

  if (t == 0.)
    previous = 0.;
  
  if (dtmax > previous)
    dtmax = (previous + 0.1*dtmax)/1.1;
  previous = dtmax;
  return dtmax;
}

#endif
