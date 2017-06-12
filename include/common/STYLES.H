/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/common/STYLES.H,v $
 * $Implementation: $
 * $Revision: 1.1.1.1 $
 * $Author: foxis $
 * $Date: 2005/02/02 15:39:13 $
 * $Description: Defines most common styles $
 *
 * $Log: STYLES.H,v $
 * Revision 1.1.1.1  2005/02/02 15:39:13  foxis
 * sources import
 *
 * Revision 0.2  20010409  12:10:33 FoxiE
 * Ispletimas .cpp pakeistas i .cc
 *
 * Revision 0.1  20010409  11:52:40 FoxiE
 * Pradejau rasyti logus :)
 *
 */



#if !defined(__ovrl_STYLES_H)
#define __ovrl_STYLES_H


/*******************************************************************
 face styles
*******************************************************************/
#define FS_POINT_A	0x0001U
#define FS_POINT_B	0x0002U
#define FS_POINT_C	0x0004U
#define FS_BOLB_A	0x0010U
#define FS_BOLB_B	0x0020U
#define FS_BOLB_C	0x0040U
#define FS_LINE_AB	0x0100U
#define FS_LINE_BC	0x0200U
#define FS_LINE_AC	0x0400U
#define FS_POINTS_ONLY	(FS_POINT_A|FS_POINT_B|FS_POINT_C)
#define FS_BOLBS_ONLY	(FS_BOLB_A|FS_BOLB_B|FS_BOLB_C)
#define FS_LINES_ONLY	(FS_LINE_AB|FS_LINE_BC|FS_LINE_AC)


/*******************************************************************
 renderer styles
*******************************************************************/
#define RS_USELIGHTS		0x0000U
#define RS_USEHARDWARE		0x0000U
#define RS_USEZBUFFER		0x0000U
#define RS_USEWBUFFER		0x0000U
#define RS_USEABUFFER		0x0000U
#define RS_USEQSORT		0x0000U
#define RS_USEHIDDENREMOVE	0x0000U
#define RS_USEZCLIPPING 	0x0000U
#define RS_USE5PLANECLIPPING	0x0000U
#define RS_USE3DCLIPPING	(RS_USEZCLIPPING|RS_USE5PLANECLIPPING)


/*******************************************************************
 Paint styles(for SurfaceBitBlt, SurfaceFill, etc.)
*******************************************************************/
#define PS_WHITE		0x0001U
#define PS_BLACK		0x0002U
#define PS_SRCCPY		0x0004U
#define PS_SRCOR		0x0008U
#define PS_SRCXOR		0x0010U
#define PS_SRCADD		0x0020U
#define PS_SRCSPLIT		0x0040U
#define PS_SRCTRANSPAR		0x0080U

/*******************************************************************
 ... misc
*******************************************************************/
#define TRANSLATE_X		0x01
#define TRANSLATE_Y		0x02
#define TRANSLATE_Z		0x04
#define TRANSLATE_XY		(TRANSLATE_X|TRANSLATE_Y)
#define TRANSLATE_XZ		(TRANSLATE_X|TRANSLATE_Z)
#define TRANSLATE_YZ		(TRANSLATE_Y|TRANSLATE_Z)
#define TRANSLATE_XYZ		(TRANSLATE_X|TRANSLATE_Y|TRANSLATE_Z)



#endif /* !defined(__ovrl_STYLES_H) */
