#ifndef __UTIL_H__
#define __UTIL_H__

double rangeConvert(double oldValue) {
    // NewValue = (((OldValue - OldMin) * (NewMax - NewMin)) / (OldMax - OldMin)) + NewMin
    return (((oldValue - 0.0) * (255.0 - 0.0)) / (1.0 - 0.0)) + 0.0;
}

#endif  // __UTIL_H__