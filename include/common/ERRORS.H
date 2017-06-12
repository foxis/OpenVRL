/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/common/ERRORS.H,v $
 * $Implementation: $
 * $Revision: 1.1.1.1 $
 * $Author: foxis $
 * $Date: 2005/02/02 15:39:11 $
 * $Description: Declares most common errors $
 *
 * $Log: ERRORS.H,v $
 * Revision 1.1.1.1  2005/02/02 15:39:11  foxis
 * sources import
 *
 * Revision 0.2  20010409  12:10:33 FoxiE
 * Ispletimas .cpp pakeistas i .cc
 *
 * Revision 0.1  20010409  11:52:40 FoxiE
 * Pradejau rasyti logus :)
 *
 */



#if !defined(__ovrl_ERRORS_H)
#define __ovrl_ERRORS_H

/*  */
#define ER_NOTENOUGHMEMORY	-1

/* File errors */
#define ER_COULDNOTOPEN 	-2
#define ER_COULDNOTCREATE	-3
#define ER_READERROR		-4
#define ER_WRITEERROR		-5
#define ER_GENERAL		-32768
#define ER_FATAL		-1

/* Other file errors */
#define ER_WRONGFORMAT		-6
#define ER_FORMATNOTSUPPORTED	    -7
#define ER_FILEISDAMAGED	-8

#define ER_SYNTAX	     -9
#define ER_DIVIDEBYZERO      -10
#define ER_NUMBERTOOBIG      -11
#define ER_WRONGNUMBERFORMAT -12


/* Statuses */
#define STAT_NOTREADY		(ER_NOTENOUGHMEMORY-100)
#define STAT_NEM		(ER_NOTENOUGHMEMORY)
#define STAT_GENERALERROR	(ER_GENERAL)
#define STAT_OK 		0
#define STAT_USER		(STAT_OK+0x200)
#define STAT_CONTAINSTRANSPARENT	(STAT_OK+0x100)

#define STAT_NULL_ADDR		(STAT_OK+1)
#define STAT_SURFACE_ALREADY_LOCKED	(STAT_OK+2)
#define STAT_SURFACE_NOT_LOCKED (STAT_OK+3)
#define STAT_SURFACE_NOT_EMPTY	(STAT_OK+4)
#define STAT_OUT_OF_RANGE	(STAT_OK+100)

#endif /* !defined(__ovrl_ERRORS_H) */
