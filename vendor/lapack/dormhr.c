/*  -- translated by f2c (version 20240504).
   You must link the resulting object file with libf2c:
	on Microsoft Windows system, link with libf2c.lib;
	on Linux or Unix systems, link with .../path/to/libf2c.a -lm
	or, if you install libf2c.a in a standard place, with -lf2c -lm
	-- in that order, at the end of the command line, as in
		cc *.o -lf2c -lm
	Source for libf2c is in /netlib/f2c/libf2c.zip, e.g.,

		http://www.netlib.org/f2c/libf2c.zip
*/

#include "f2c.h"

/* Table of constant values */

static integer c__1 = 1;
static integer c_n1 = -1;
static integer c__2 = 2;

/* > \brief \b DORMHR   

    =========== DOCUMENTATION ===========   

   Online html documentation available at   
              http://www.netlib.org/lapack/explore-html/   

   > \htmlonly   
   > Download DORMHR + dependencies   
   > <a href="http://www.netlib.org/cgi-bin/netlibfiles.tgz?format=tgz&filename=/lapack/lapack_routine/dormhr.
f">   
   > [TGZ]</a>   
   > <a href="http://www.netlib.org/cgi-bin/netlibfiles.zip?format=zip&filename=/lapack/lapack_routine/dormhr.
f">   
   > [ZIP]</a>   
   > <a href="http://www.netlib.org/cgi-bin/netlibfiles.txt?format=txt&filename=/lapack/lapack_routine/dormhr.
f">   
   > [TXT]</a>   
   > \endhtmlonly   

    Definition:   
    ===========   

         SUBROUTINE DORMHR( SIDE, TRANS, M, N, ILO, IHI, A, LDA, TAU, C,   
                            LDC, WORK, LWORK, INFO )   

         CHARACTER          SIDE, TRANS   
         INTEGER            IHI, ILO, INFO, LDA, LDC, LWORK, M, N   
         DOUBLE PRECISION   A( LDA, * ), C( LDC, * ), TAU( * ), WORK( * )   


   > \par Purpose:   
    =============   
   >   
   > \verbatim   
   >   
   > DORMHR overwrites the general real M-by-N matrix C with   
   >   
   >                 SIDE = 'L'     SIDE = 'R'   
   > TRANS = 'N':      Q * C          C * Q   
   > TRANS = 'T':      Q**T * C       C * Q**T   
   >   
   > where Q is a real orthogonal matrix of order nq, with nq = m if   
   > SIDE = 'L' and nq = n if SIDE = 'R'. Q is defined as the product of   
   > IHI-ILO elementary reflectors, as returned by DGEHRD:   
   >   
   > Q = H(ilo) H(ilo+1) . . . H(ihi-1).   
   > \endverbatim   

    Arguments:   
    ==========   

   > \param[in] SIDE   
   > \verbatim   
   >          SIDE is CHARACTER*1   
   >          = 'L': apply Q or Q**T from the Left;   
   >          = 'R': apply Q or Q**T from the Right.   
   > \endverbatim   
   >   
   > \param[in] TRANS   
   > \verbatim   
   >          TRANS is CHARACTER*1   
   >          = 'N':  No transpose, apply Q;   
   >          = 'T':  Transpose, apply Q**T.   
   > \endverbatim   
   >   
   > \param[in] M   
   > \verbatim   
   >          M is INTEGER   
   >          The number of rows of the matrix C. M >= 0.   
   > \endverbatim   
   >   
   > \param[in] N   
   > \verbatim   
   >          N is INTEGER   
   >          The number of columns of the matrix C. N >= 0.   
   > \endverbatim   
   >   
   > \param[in] ILO   
   > \verbatim   
   >          ILO is INTEGER   
   > \endverbatim   
   >   
   > \param[in] IHI   
   > \verbatim   
   >          IHI is INTEGER   
   >   
   >          ILO and IHI must have the same values as in the previous call   
   >          of DGEHRD. Q is equal to the unit matrix except in the   
   >          submatrix Q(ilo+1:ihi,ilo+1:ihi).   
   >          If SIDE = 'L', then 1 <= ILO <= IHI <= M, if M > 0, and   
   >          ILO = 1 and IHI = 0, if M = 0;   
   >          if SIDE = 'R', then 1 <= ILO <= IHI <= N, if N > 0, and   
   >          ILO = 1 and IHI = 0, if N = 0.   
   > \endverbatim   
   >   
   > \param[in] A   
   > \verbatim   
   >          A is DOUBLE PRECISION array, dimension   
   >                               (LDA,M) if SIDE = 'L'   
   >                               (LDA,N) if SIDE = 'R'   
   >          The vectors which define the elementary reflectors, as   
   >          returned by DGEHRD.   
   > \endverbatim   
   >   
   > \param[in] LDA   
   > \verbatim   
   >          LDA is INTEGER   
   >          The leading dimension of the array A.   
   >          LDA >= max(1,M) if SIDE = 'L'; LDA >= max(1,N) if SIDE = 'R'.   
   > \endverbatim   
   >   
   > \param[in] TAU   
   > \verbatim   
   >          TAU is DOUBLE PRECISION array, dimension   
   >                               (M-1) if SIDE = 'L'   
   >                               (N-1) if SIDE = 'R'   
   >          TAU(i) must contain the scalar factor of the elementary   
   >          reflector H(i), as returned by DGEHRD.   
   > \endverbatim   
   >   
   > \param[in,out] C   
   > \verbatim   
   >          C is DOUBLE PRECISION array, dimension (LDC,N)   
   >          On entry, the M-by-N matrix C.   
   >          On exit, C is overwritten by Q*C or Q**T*C or C*Q**T or C*Q.   
   > \endverbatim   
   >   
   > \param[in] LDC   
   > \verbatim   
   >          LDC is INTEGER   
   >          The leading dimension of the array C. LDC >= max(1,M).   
   > \endverbatim   
   >   
   > \param[out] WORK   
   > \verbatim   
   >          WORK is DOUBLE PRECISION array, dimension (MAX(1,LWORK))   
   >          On exit, if INFO = 0, WORK(1) returns the optimal LWORK.   
   > \endverbatim   
   >   
   > \param[in] LWORK   
   > \verbatim   
   >          LWORK is INTEGER   
   >          The dimension of the array WORK.   
   >          If SIDE = 'L', LWORK >= max(1,N);   
   >          if SIDE = 'R', LWORK >= max(1,M).   
   >          For optimum performance LWORK >= N*NB if SIDE = 'L', and   
   >          LWORK >= M*NB if SIDE = 'R', where NB is the optimal   
   >          blocksize.   
   >   
   >          If LWORK = -1, then a workspace query is assumed; the routine   
   >          only calculates the optimal size of the WORK array, returns   
   >          this value as the first entry of the WORK array, and no error   
   >          message related to LWORK is issued by XERBLA.   
   > \endverbatim   
   >   
   > \param[out] INFO   
   > \verbatim   
   >          INFO is INTEGER   
   >          = 0:  successful exit   
   >          < 0:  if INFO = -i, the i-th argument had an illegal value   
   > \endverbatim   

    Authors:   
    ========   

   > \author Univ. of Tennessee   
   > \author Univ. of California Berkeley   
   > \author Univ. of Colorado Denver   
   > \author NAG Ltd.   

   > \date November 2011   

   > \ingroup doubleOTHERcomputational   

    =====================================================================   
   Subroutine */ int igraphdormhr_(char *side, char *trans, integer *m, integer *n, 
	integer *ilo, integer *ihi, doublereal *a, integer *lda, doublereal *
	tau, doublereal *c__, integer *ldc, doublereal *work, integer *lwork, 
	integer *info)
{
    /* System generated locals */
    address a__1[2];
    integer a_dim1, a_offset, c_dim1, c_offset, i__1[2], i__2;
    char ch__1[2];

    /* Builtin functions   
       Subroutine */ int s_cat(char *, char **, integer *, integer *, ftnlen);

    /* Local variables */
    integer i1, i2, nb, mi, nh, ni, nq, nw;
    logical left;
    extern logical igraphlsame_(char *, char *);
    integer iinfo;
    extern /* Subroutine */ int igraphxerbla_(char *, integer *, ftnlen);
    extern integer igraphilaenv_(integer *, char *, char *, integer *, integer *, 
	    integer *, integer *, ftnlen, ftnlen);
    extern /* Subroutine */ int igraphdormqr_(char *, char *, integer *, integer *, 
	    integer *, doublereal *, integer *, doublereal *, doublereal *, 
	    integer *, doublereal *, integer *, integer *);
    integer lwkopt;
    logical lquery;


/*  -- LAPACK computational routine (version 3.4.0) --   
    -- LAPACK is a software package provided by Univ. of Tennessee,    --   
    -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..--   
       November 2011   


    =====================================================================   


       Test the input arguments   

       Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    --tau;
    c_dim1 = *ldc;
    c_offset = 1 + c_dim1;
    c__ -= c_offset;
    --work;

    /* Function Body */
    *info = 0;
    nh = *ihi - *ilo;
    left = igraphlsame_(side, "L");
    lquery = *lwork == -1;

/*     NQ is the order of Q and NW is the minimum dimension of WORK */

    if (left) {
	nq = *m;
	nw = *n;
    } else {
	nq = *n;
	nw = *m;
    }
    if (! left && ! igraphlsame_(side, "R")) {
	*info = -1;
    } else if (! igraphlsame_(trans, "N") && ! igraphlsame_(trans, 
	    "T")) {
	*info = -2;
    } else if (*m < 0) {
	*info = -3;
    } else if (*n < 0) {
	*info = -4;
    } else if (*ilo < 1 || *ilo > max(1,nq)) {
	*info = -5;
    } else if (*ihi < min(*ilo,nq) || *ihi > nq) {
	*info = -6;
    } else if (*lda < max(1,nq)) {
	*info = -8;
    } else if (*ldc < max(1,*m)) {
	*info = -11;
    } else if (*lwork < max(1,nw) && ! lquery) {
	*info = -13;
    }

    if (*info == 0) {
	if (left) {
/* Writing concatenation */
	    i__1[0] = 1, a__1[0] = side;
	    i__1[1] = 1, a__1[1] = trans;
	    s_cat(ch__1, a__1, i__1, &c__2, (ftnlen)2);
	    nb = igraphilaenv_(&c__1, "DORMQR", ch__1, &nh, n, &nh, &c_n1, (ftnlen)
		    6, (ftnlen)2);
	} else {
/* Writing concatenation */
	    i__1[0] = 1, a__1[0] = side;
	    i__1[1] = 1, a__1[1] = trans;
	    s_cat(ch__1, a__1, i__1, &c__2, (ftnlen)2);
	    nb = igraphilaenv_(&c__1, "DORMQR", ch__1, m, &nh, &nh, &c_n1, (ftnlen)
		    6, (ftnlen)2);
	}
	lwkopt = max(1,nw) * nb;
	work[1] = (doublereal) lwkopt;
    }

    if (*info != 0) {
	i__2 = -(*info);
	igraphxerbla_("DORMHR", &i__2, (ftnlen)6);
	return 0;
    } else if (lquery) {
	return 0;
    }

/*     Quick return if possible */

    if (*m == 0 || *n == 0 || nh == 0) {
	work[1] = 1.;
	return 0;
    }

    if (left) {
	mi = nh;
	ni = *n;
	i1 = *ilo + 1;
	i2 = 1;
    } else {
	mi = *m;
	ni = nh;
	i1 = 1;
	i2 = *ilo + 1;
    }

    igraphdormqr_(side, trans, &mi, &ni, &nh, &a[*ilo + 1 + *ilo * a_dim1], lda, &
	    tau[*ilo], &c__[i1 + i2 * c_dim1], ldc, &work[1], lwork, &iinfo);

    work[1] = (doublereal) lwkopt;
    return 0;

/*     End of DORMHR */

} /* igraphdormhr_ */

