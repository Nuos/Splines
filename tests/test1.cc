/*--------------------------------------------------------------------------*\
 |                                                                          |
 |  Copyright (C) 1998                                                      |
 |                                                                          |
 |         , __                 , __                                        |
 |        /|/  \               /|/  \                                       |
 |         | __/ _   ,_         | __/ _   ,_                                | 
 |         |   \|/  /  |  |   | |   \|/  /  |  |   |                        |
 |         |(__/|__/   |_/ \_/|/|(__/|__/   |_/ \_/|/                       |
 |                           /|                   /|                        |
 |                           \|                   \|                        |
 |                                                                          |
 |      Enrico Bertolazzi                                                   |
 |      Dipartimento di Ingegneria Industriale                              |
 |      Universita` degli Studi di Trento                                   |
 |      email: enrico.bertolazzi@unitn.it                                   |
 |                                                                          |
\*--------------------------------------------------------------------------*/

#include "Splines.hh"
#include <fstream>

using namespace SplinesLoad ;
using namespace std ;
using Splines::valueType ;
using Splines::indexType ;
using Splines::sizeType ;

// Test problem for Akima interpolation
// Ref. : Hiroshi Akima, Journal of the ACM, Vol. 17, No. 4, October 1970, pages 589-602.

valueType xx0[] = {  0,  1,  2,  3,  4,  5,    6,  7,  8,  9, 10 } ; 
valueType yy0[] = { 10, 10, 10, 10, 10, 10, 10.5, 15, 50, 60, 85 } ;

valueType xx1[] = {  0,  1,  3,  4,  6,  7,    9, 10, 12, 13, 15 } ;
valueType yy1[] = { 10, 10, 10, 10, 10, 10, 10.5, 15, 50, 60, 85 } ;

valueType xx2[] = {  0,  2,  3,  5,  6,  8,    9, 11, 12, 14, 15 } ;
valueType yy2[] = { 10, 10, 10, 10, 10, 10, 10.5, 15, 50, 60, 85 } ;

// RPN 14
valueType xx3[] = { 7.99, 8.09,       8.19,       8.7,      9.2,      10,       12,       15,       20       } ;
valueType yy3[] = { 0,    2.76429e-5, 4.37498e-2, 0.169183, 0.469428, 0.943740, 0.998636, 0.999919, 0.999994 } ;

// Titanium
valueType xx4[] = { 595,   635,   695,   795,   855,   875,   895,   915,   935,   985,   1035,  1075  } ;
valueType yy4[] = { 0.644, 0.652, 0.644, 0.694, 0.907, 1.336, 2.169, 1.598, 0.916, 0.607, 0.603, 0.608 } ;

// toolpath
valueType xx5[] = { 0.11, 0.12, 0.15, 0.16 } ;
valueType yy5[] = { 0.0003, 0.0003, 0.0004, 0.0004 } ;

sizeType  n[]   = { 11, 11, 11, 9, 12, 4 } ;

int
main() {

  AkimaSpline    ak ;
  CubicSpline    cs ;
  BesselSpline   be ;
  PchipSpline    pc ;
  QuinticSpline  qs ;
  ofstream       file_ak ;
  ofstream       file_cs ;
  ofstream       file_be ;
  ofstream       file_pc ;
  ofstream       file_qs ;

  for ( indexType k = 0 ; k < 6 ; ++ k ) {
    valueType * xx, * yy ;
    switch ( k ) {
      case 0: xx = xx0 ; yy = yy0 ; break ;
      case 1: xx = xx1 ; yy = yy1 ; break ;
      case 2: xx = xx2 ; yy = yy2 ; break ;
      case 3: xx = xx3 ; yy = yy3 ; break ;
      case 4: xx = xx4 ; yy = yy4 ; break ;
      case 5: xx = xx5 ; yy = yy5 ; break ;
    }
    char fname[100] ;
    sprintf( fname, "Akima%d.txt",    k) ; file_ak . open(fname) ;
    sprintf( fname, "Cubic%d.txt",    k) ; file_cs . open(fname) ;
    sprintf( fname, "Bessel%d.txt",   k) ; file_be . open(fname) ;
    sprintf( fname, "Pchip%d.txt",    k) ; file_pc . open(fname) ;
    sprintf( fname, "Quintic%d.txt",  k) ; file_qs . open(fname) ;
    valueType xmin = xx[0] ;
    valueType xmax = xx[n[k]-1] ;
    
    #define SAVE(S) \
    S.build( xx, yy, n[k] ) ; \
    file_##S << "x\ty\tDy\tDDy\n" ; \
    for ( valueType x = xmin-(xmax-xmin)*0.01 ; x <= xmax+(xmax-xmin)*0.01 ; x += (xmax-xmin)/1000 ) \
      file_##S << x << '\t' << S(x) << '\t' << S.D(x) << '\t' << S.DD(x) << '\n' ; \
    file_##S.close()
    
    SAVE(ak) ;
    SAVE(cs) ;
    SAVE(be) ;
    SAVE(pc) ;
    SAVE(qs) ;
  }
  
  cout << "ALL DONE!\n" ;
}