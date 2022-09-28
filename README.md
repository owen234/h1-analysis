# h1-analysis

## Bin center corrections
The H1 legacy papers use Bin Center Corrections (BCCs).  We probably won't use those in the future, but we need them in order to do direct comparisons to the H1 measurements.  The binning is defined in [utils.c](utils.c) and the bin centers, where the cross sections are evaluated, are set in [fill_h1_rxsec_th2.c](fill_h1_rxsec_th2.c).  The BCCs are calculated by [calc_bincentercf_poly.C](calc_bincentercf_poly.C), which must be compiled within the H1OO framework at DESY.  The file [h1-binning.pdf](h1-binning.pdf) shows the global bin index (gbi) and the bin center values inside the TH2Poly histograms.
