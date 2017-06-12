/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/common/Colors.h,v $
 * $Implementation: $
 * $Revision: 1.2 $
 * $Author: foxis $
 * $Date: 2005/02/03 11:24:24 $
 * $Description:  $
 *
 * $Log: Colors.h,v $
 * Revision 1.2  2005/02/03 11:24:24  foxis
 * added log header everywhere
 *
 *
 */

#if !defined(_ovrl_COLORS_H)
#define _ovrl_COLORS_H

#include "common/all.h"

namespace openvrl {

// Whites
static const DRGB_t RGB_ANTIQUE_WHITE	      = {0.9804f, 0.9216f, 0.8431f, 0.0f};
static const DRGB_t RGB_AZURE		      = {0.9412f, 1.0000f, 1.0000f, 0.0f};
static const DRGB_t RGB_BISQUE 	      = {1.0000f, 0.8941f, 0.7686f, 0.0f};
static const DRGB_t RGB_BLANCHED_ALMOND      = {1.0000f, 0.9216f, 0.8039f, 0.0f};
static const DRGB_t RGB_CORNSILK	      = {1.0000f, 0.9725f, 0.8627f, 0.0f};
static const DRGB_t RGB_EGGSHELL	      = {0.9900f, 0.9000f, 0.7900f, 0.0f};
static const DRGB_t RGB_FLORAL_WHITE	      = {1.0000f, 0.9804f, 0.9412f, 0.0f};
static const DRGB_t RGB_GAINSBORO	      = {0.8627f, 0.8627f, 0.8627f, 0.0f};
static const DRGB_t RGB_GHOST_WHITE	      = {0.9725f, 0.9725f, 1.0000f, 0.0f};
static const DRGB_t RGB_HONEYDEW	      = {0.9412f, 1.0000f, 0.9412f, 0.0f};
static const DRGB_t RGB_IVORY		      = {1.0000f, 1.0000f, 0.9412f, 0.0f};
static const DRGB_t RGB_LAVENDER	      = {0.9020f, 0.9020f, 0.9804f, 0.0f};
static const DRGB_t RGB_LAVENDER_BLUSH       = {1.0000f, 0.9412f, 0.9608f, 0.0f};
static const DRGB_t RGB_LEMON_CHIFFON	      = {1.0000f, 0.9804f, 0.8039f, 0.0f};
static const DRGB_t RGB_LINEN		      = {0.9804f, 0.9412f, 0.9020f, 0.0f};
static const DRGB_t RGB_MINT_CREAM	      = {0.9608f, 1.0000f, 0.9804f, 0.0f};
static const DRGB_t RGB_MISTY_ROSE	      = {1.0000f, 0.8941f, 0.8824f, 0.0f};
static const DRGB_t RGB_MOCCASIN	      = {1.0000f, 0.8941f, 0.7098f, 0.0f};
static const DRGB_t RGB_NAVAJO_WHITE	      = {1.0000f, 0.8706f, 0.6784f, 0.0f};
static const DRGB_t RGB_OLD_LACE	      = {0.9922f, 0.9608f, 0.9020f, 0.0f};
static const DRGB_t RGB_PAPAYA_WHIP	      = {1.0000f, 0.9373f, 0.8353f, 0.0f};
static const DRGB_t RGB_PEACH_PUFF	      = {1.0000f, 0.8549f, 0.7255f, 0.0f};
static const DRGB_t RGB_SEASHELL	      = {1.0000f, 0.9608f, 0.9333f, 0.0f};
static const DRGB_t RGB_SNOW		      = {1.0000f, 0.9804f, 0.9804f, 0.0f};
static const DRGB_t RGB_THISTLE	      = {0.8471f, 0.7490f, 0.8471f, 0.0f};
static const DRGB_t RGB_TITANIUM_WHITE       = {0.9900f, 1.0000f, 0.9400f, 0.0f};
static const DRGB_t RGB_WHEAT		      = {0.9608f, 0.8706f, 0.7020f, 0.0f};
static const DRGB_t RGB_WHITE		      = {1.0000f, 1.0000f, 1.0000f, 0.0f};
static const DRGB_t RGB_WHITE_SMOKE	      = {0.9608f, 0.9608f, 0.9608f, 0.0f};
static const DRGB_t RGB_ZINC_WHITE	      = {0.9900f, 0.9700f, 1.0000f, 0.0f};

//  GREYS
static const DRGB_t RGB_COLD_GREY	      = {0.5000f, 0.5400f, 0.5300f, 0.0f};
static const DRGB_t RGB_DIM_GREY	      = {0.4118f, 0.4118f, 0.4118f, 0.0f};
static const DRGB_t RGB_GREY		      = {0.7529f, 0.7529f, 0.7529f, 0.0f};
static const DRGB_t RGB_LIGHT_GREY	      = {0.8275f, 0.8275f, 0.8275f, 0.0f};
static const DRGB_t RGB_SLATE_GREY	      = {0.4392f, 0.5020f, 0.5647f, 0.0f};
static const DRGB_t RGB_SLATE_GREY_DARK      = {0.1843f, 0.3098f, 0.3098f, 0.0f};
static const DRGB_t RGB_SLATE_GREY_LIGHT     = {0.4667f, 0.5333f, 0.6000f, 0.0f};
static const DRGB_t RGB_WARM_GREY	      = {0.5000f, 0.5000f, 0.4100f, 0.0f};

//  BLACKS
static const DRGB_t RGB_BLACK		      = {0.0000f, 0.0000f, 0.0000f, 0.0f};
static const DRGB_t RGB_IVORY_BLACK	      = {0.1600f, 0.1400f, 0.1300f, 0.0f};
static const DRGB_t RGB_LAMP_BLACK	      = {0.1800f, 0.2800f, 0.2300f, 0.0f};

//  Reds
static const DRGB_t RGB_ALIZARIN_CRIMSON     = {0.8900f, 0.1500f, 0.2100f, 0.0f};
static const DRGB_t RGB_BRICK		      = {0.6100f, 0.4000f, 0.1200f, 0.0f};
static const DRGB_t RGB_CADMIUM_RED_DEEP     = {0.8900f, 0.0900f, 0.0500f, 0.0f};
static const DRGB_t RGB_CORAL		      = {1.0000f, 0.4980f, 0.3137f, 0.0f};
static const DRGB_t RGB_CORAL_LIGHT	      = {0.9412f, 0.5020f, 0.5020f, 0.0f};
static const DRGB_t RGB_DEEP_PINK	      = {1.0000f, 0.0784f, 0.5765f, 0.0f};
static const DRGB_t RGB_ENGLISH_RED	      = {0.8300f, 0.2400f, 0.1000f, 0.0f};
static const DRGB_t RGB_FIREBRICK	      = {0.6980f, 0.1333f, 0.1333f, 0.0f};
static const DRGB_t RGB_GERANIUM_LAKE	      = {0.8900f, 0.0700f, 0.1900f, 0.0f};
static const DRGB_t RGB_HOT_PINK	      = {1.0000f, 0.4118f, 0.7059f, 0.0f};
static const DRGB_t RGB_INDIAN_RED	      = {0.6900f, 0.0900f, 0.1200f, 0.0f};
static const DRGB_t RGB_LIGHT_SALMON	      = {1.0000f, 0.6275f, 0.4784f, 0.0f};
static const DRGB_t RGB_MADDER_LAKE_DEEP     = {0.8900f, 0.1800f, 0.1900f, 0.0f};
static const DRGB_t RGB_MAROON 	      = {0.6902f, 0.1882f, 0.3765f, 0.0f};
static const DRGB_t RGB_PINK		      = {1.0000f, 0.7529f, 0.7961f, 0.0f};
static const DRGB_t RGB_PINK_LIGHT	      = {1.0000f, 0.7137f, 0.7569f, 0.0f};
static const DRGB_t RGB_RASPBERRY	      = {0.5300f, 0.1500f, 0.3400f, 0.0f};
static const DRGB_t RGB_RED		      = {1.0000f, 0.0000f, 0.0000f, 0.0f};
static const DRGB_t RGB_ROSE_MADDER	      = {0.8900f, 0.2100f, 0.2200f, 0.0f};
static const DRGB_t RGB_SALMON 	      = {0.9804f, 0.5020f, 0.4471f, 0.0f};
static const DRGB_t RGB_TOMATO 	      = {1.0000f, 0.3882f, 0.2784f, 0.0f};
static const DRGB_t RGB_VENETIAN_RED	      = {0.8300f, 0.1000f, 0.1200f, 0.0f};

//   BROWNS
static const DRGB_t RGB_BEIGE		      = {0.6400f, 0.5800f, 0.5000f, 0.0f};
static const DRGB_t RGB_BROWN		      = {0.5000f, 0.1647f, 0.1647f, 0.0f};
static const DRGB_t RGB_BROWN_MADDER	      = {0.8600f, 0.1600f, 0.1600f, 0.0f};
static const DRGB_t RGB_BROWN_OCHRE	      = {0.5300f, 0.2600f, 0.1200f, 0.0f};
static const DRGB_t RGB_BURLYWOOD	      = {0.8706f, 0.7216f, 0.5294f, 0.0f};
static const DRGB_t RGB_BURNT_SIENNA	      = {0.5400f, 0.2100f, 0.0600f, 0.0f};
static const DRGB_t RGB_BURNT_UMBER	      = {0.5400f, 0.2000f, 0.1400f, 0.0f};
static const DRGB_t RGB_CHOCOLATE	      = {0.8235f, 0.4118f, 0.1176f, 0.0f};
static const DRGB_t RGB_DEEP_OCHRE	      = {0.4500f, 0.2400f, 0.1000f, 0.0f};
static const DRGB_t RGB_FLESH		      = {1.0000f, 0.4900f, 0.2500f, 0.0f};
static const DRGB_t RGB_FLESH_OCHRE	      = {1.0000f, 0.3400f, 0.1300f, 0.0f};
static const DRGB_t RGB_GOLD_OCHRE	      = {0.7800f, 0.4700f, 0.1500f, 0.0f};
static const DRGB_t RGB_GREENISH_UMBER       = {1.0000f, 0.2400f, 0.0500f, 0.0f};
static const DRGB_t RGB_KHAKI		      = {0.9412f, 0.9020f, 0.5490f, 0.0f};
static const DRGB_t RGB_KHAKI_DARK	      = {0.7412f, 0.7176f, 0.4196f, 0.0f};
static const DRGB_t RGB_LIGHT_BEIGE	      = {0.9608f, 0.9608f, 0.8627f, 0.0f};
static const DRGB_t RGB_PERU		      = {0.8039f, 0.5216f, 0.2471f, 0.0f};
static const DRGB_t RGB_ROSY_BROWN	      = {0.7373f, 0.5608f, 0.5608f, 0.0f};
static const DRGB_t RGB_RAW_SIENNA	      = {0.7800f, 0.3800f, 0.0800f, 0.0f};
static const DRGB_t RGB_RAW_UMBER	      = {0.4500f, 0.2900f, 0.0700f, 0.0f};
static const DRGB_t RGB_SEPIA		      = {0.3700f, 0.1500f, 0.0700f, 0.0f};
static const DRGB_t RGB_SIENNA 	      = {0.6275f, 0.3216f, 0.1765f, 0.0f};
static const DRGB_t RGB_SADDLE_BROWN	      = {0.5451f, 0.2706f, 0.0745f, 0.0f};
static const DRGB_t RGB_SANDY_BROWN	      = {0.9569f, 0.6431f, 0.3765f, 0.0f};
static const DRGB_t RGB_TAN		      = {0.8235f, 0.7059f, 0.5490f, 0.0f};
static const DRGB_t RGB_VAN_DYKE_BROWN       = {0.3700f, 0.1500f, 0.0200f, 0.0f};

//   ORANGES
static const DRGB_t RGB_CADMIUM_ORANGE       = {1.0000f, 0.3800f, 0.0100f, 0.0f};
static const DRGB_t RGB_CADMIUM_RED_LIGHT    = {1.0000f, 0.0100f, 0.0500f, 0.0f};
static const DRGB_t RGB_CARROT 	      = {0.9300f, 0.5700f, 0.1300f, 0.0f};
static const DRGB_t RGB_DARK_ORANGE	      = {1.0000f, 0.5490f, 0.0000f, 0.0f};
static const DRGB_t RGB_MARS_ORANGE	      = {0.5900f, 0.2700f, 0.0800f, 0.0f};
static const DRGB_t RGB_MARS_YELLOW	      = {0.8900f, 0.4400f, 0.1000f, 0.0f};
static const DRGB_t RGB_ORANGE 	      = {1.0000f, 0.5000f, 0.0000f, 0.0f};
static const DRGB_t RGB_ORANGE_RED	      = {1.0000f, 0.2706f, 0.0000f, 0.0f};
static const DRGB_t RGB_YELLOW_OCHRE	      = {0.8900f, 0.5100f, 0.0900f, 0.0f};

//   YELLOWS
static const DRGB_t RGB_AUREOLINE_YELLOW     = {1.0000f, 0.6600f, 0.1400f, 0.0f};
static const DRGB_t RGB_BANANA 	      = {0.8900f, 0.8100f, 0.3400f, 0.0f};
static const DRGB_t RGB_CADMIUM_LEMON	      = {1.0000f, 0.8900f, 0.0100f, 0.0f};
static const DRGB_t RGB_CADMIUM_YELLOW       = {1.0000f, 0.6000f, 0.0700f, 0.0f};
static const DRGB_t RGB_CADMIUM_YELLOW_LIGHT = {1.0000f, 0.6900f, 0.0600f, 0.0f};
static const DRGB_t RGB_GOLD		      = {1.0000f, 0.8431f, 0.0000f, 0.0f};
static const DRGB_t RGB_GOLDENROD	      = {0.8549f, 0.6471f, 0.1255f, 0.0f};
static const DRGB_t RGB_GOLDENROD_DARK       = {0.7216f, 0.5255f, 0.0431f, 0.0f};
static const DRGB_t RGB_GOLDENROD_LIGHT      = {0.9804f, 0.9804f, 0.8235f, 0.0f};
static const DRGB_t RGB_GOLDENROD_PALE       = {0.9333f, 0.9098f, 0.6667f, 0.0f};
static const DRGB_t RGB_LIGHT_GOLDENROD      = {0.9333f, 0.8667f, 0.5098f, 0.0f};
static const DRGB_t RGB_MELON		      = {0.8900f, 0.6600f, 0.4100f, 0.0f};
static const DRGB_t RGB_NAPLES_YELLOW_DEEP   = {1.0000f, 0.6600f, 0.0700f, 0.0f};
static const DRGB_t RGB_YELLOW 	      = {1.0000f, 1.0000f, 0.0000f, 0.0f};
static const DRGB_t RGB_YELLOW_LIGHT	      = {1.0000f, 1.0000f, 0.8784f, 0.0f};

//  GREENS
static const DRGB_t RGB_CHARTREUSE	      = {0.4980f, 1.0000f, 0.0000f, 0.0f};
static const DRGB_t RGB_CHROME_OXIDE_GREEN   = {0.4000f, 0.5000f, 0.0800f, 0.0f};
static const DRGB_t RGB_CINNABAR_GREEN       = {0.3800f, 0.7000f, 0.1600f, 0.0f};
static const DRGB_t RGB_COBALT_GREEN	      = {0.2400f, 0.5700f, 0.2500f, 0.0f};
static const DRGB_t RGB_EMERALD_GREEN	      = {0.0000f, 0.7900f, 0.3400f, 0.0f};
static const DRGB_t RGB_FOREST_GREEN	      = {0.1333f, 0.5451f, 0.1333f, 0.0f};
static const DRGB_t RGB_GREEN		      = {0.0000f, 1.0000f, 0.0000f, 0.0f};
static const DRGB_t RGB_GREEN_DARK	      = {0.0000f, 0.3922f, 0.0000f, 0.0f};
static const DRGB_t RGB_GREEN_PALE	      = {0.5961f, 0.9843f, 0.5961f, 0.0f};
static const DRGB_t RGB_GREEN_YELLOW	      = {0.6784f, 1.0000f, 0.1843f, 0.0f};
static const DRGB_t RGB_LAWN_GREEN	      = {0.4863f, 0.9882f, 0.0000f, 0.0f};
static const DRGB_t RGB_LIME_GREEN	      = {0.1961f, 0.8039f, 0.1961f, 0.0f};
static const DRGB_t RGB_MINT		      = {0.7400f, 0.9900f, 0.7900f, 0.0f};
static const DRGB_t RGB_OLIVE		      = {0.2300f, 0.3700f, 0.1700f, 0.0f};
static const DRGB_t RGB_OLIVE_DRAB	      = {0.4196f, 0.5569f, 0.1373f, 0.0f};
static const DRGB_t RGB_OLIVE_GREEN_DARK     = {0.3333f, 0.4196f, 0.1843f, 0.0f};
static const DRGB_t RGB_PERMANENT_GREEN      = {0.0400f, 0.7900f, 0.1700f, 0.0f};
static const DRGB_t RGB_SAP_GREEN	      = {0.1900f, 0.5000f, 0.0800f, 0.0f};
static const DRGB_t RGB_SEA_GREEN	      = {0.1804f, 0.5451f, 0.3412f, 0.0f};
static const DRGB_t RGB_SEA_GREEN_DARK       = {0.5608f, 0.7373f, 0.5608f, 0.0f};
static const DRGB_t RGB_SEA_GREEN_MEDIUM     = {0.2353f, 0.7020f, 0.4431f, 0.0f};
static const DRGB_t RGB_SEA_GREEN_LIGHT      = {0.1255f, 0.6980f, 0.6667f, 0.0f};
static const DRGB_t RGB_SPRING_GREEN	      = {0.0000f, 1.0000f, 0.4980f, 0.0f};
static const DRGB_t RGB_SPRING_GREEN_MEDIUM  = {0.0000f, 0.9804f, 0.6039f, 0.0f};
static const DRGB_t RGB_TERRE_VERTE	      = {0.2200f, 0.3700f, 0.0600f, 0.0f};
static const DRGB_t RGB_VIRIDIAN_LIGHT       = {0.4300f, 1.0000f, 0.4400f, 0.0f};
static const DRGB_t RGB_YELLOW_GREEN	      = {0.6039f, 0.8039f, 0.1961f, 0.0f};

//   CYANS
static const DRGB_t RGB_AQUAMARINE	      = {0.4980f, 1.0000f, 0.8314f, 0.0f};
static const DRGB_t RGB_AQUAMARINE_MEDIUM    = {0.4000f, 0.8039f, 0.6667f, 0.0f};
static const DRGB_t RGB_CYAN		      = {0.0000f, 1.0000f, 1.0000f, 0.0f};
static const DRGB_t RGB_CYAN_WHITE	      = {0.8784f, 1.0000f, 1.0000f, 0.0f};
static const DRGB_t RGB_TURQUOISE	      = {0.2510f, 0.8784f, 0.8157f, 0.0f};
static const DRGB_t RGB_TURQUOISE_DARK       = {0.0000f, 0.8078f, 0.8196f, 0.0f};
static const DRGB_t RGB_TURQUOISE_MEDIUM     = {0.2824f, 0.8196f, 0.8000f, 0.0f};
static const DRGB_t RGB_TURQUOISE_PALE       = {0.6863f, 0.9333f, 0.9333f, 0.0f};

//    BLUES
static const DRGB_t RGB_ALICE_BLUE	      = {0.9412f, 0.9725f, 1.0000f, 0.0f};
static const DRGB_t RGB_BLUE		      = {0.0000f, 0.0000f, 1.0000f, 0.0f};
static const DRGB_t RGB_BLUE_LIGHT	      = {0.6784f, 0.8471f, 0.9020f, 0.0f};
static const DRGB_t RGB_BLUE_MEDIUM	      = {0.0000f, 0.0000f, 0.8039f, 0.0f};
static const DRGB_t RGB_CADET		      = {0.3725f, 0.6196f, 0.6275f, 0.0f};
static const DRGB_t RGB_COBALT 	      = {0.2400f, 0.3500f, 0.6700f, 0.0f};
static const DRGB_t RGB_CORNFLOWER	      = {0.3922f, 0.5843f, 0.9294f, 0.0f};
static const DRGB_t RGB_CERULEAN	      = {0.0200f, 0.7200f, 0.8000f, 0.0f};
static const DRGB_t RGB_DODGER_BLUE	      = {0.1176f, 0.5647f, 1.0000f, 0.0f};
static const DRGB_t RGB_INDIGO 	      = {0.0300f, 0.1800f, 0.3300f, 0.0f};
static const DRGB_t RGB_MANGANESE_BLUE       = {0.0100f, 0.6600f, 0.6200f, 0.0f};
static const DRGB_t RGB_MIDNIGHT_BLUE	      = {0.0980f, 0.0980f, 0.4392f, 0.0f};
static const DRGB_t RGB_NAVY		      = {0.0000f, 0.0000f, 0.5020f, 0.0f};
static const DRGB_t RGB_PEACOCK	      = {0.2000f, 0.6300f, 0.7900f, 0.0f};
static const DRGB_t RGB_POWDER_BLUE	      = {0.6902f, 0.8784f, 0.9020f, 0.0f};
static const DRGB_t RGB_ROYAL_BLUE	      = {0.2549f, 0.4118f, 0.8824f, 0.0f};
static const DRGB_t RGB_SLATE_BLUE	      = {0.4157f, 0.3529f, 0.8039f, 0.0f};
static const DRGB_t RGB_SLATE_BLUE_DARK      = {0.2824f, 0.2392f, 0.5451f, 0.0f};
static const DRGB_t RGB_SLATE_BLUE_LIGHT     = {0.5176f, 0.4392f, 1.0000f, 0.0f};
static const DRGB_t RGB_SLATE_BLUE_MEDIUM    = {0.4824f, 0.4078f, 0.9333f, 0.0f};
static const DRGB_t RGB_SKY_BLUE	      = {0.5294f, 0.8078f, 0.9216f, 0.0f};
static const DRGB_t RGB_SKY_BLUE_DEEP	      = {0.0000f, 0.7490f, 1.0000f, 0.0f};
static const DRGB_t RGB_SKY_BLUE_LIGHT       = {0.5294f, 0.8078f, 0.9804f, 0.0f};
static const DRGB_t RGB_STEEL_BLUE	      = {0.2745f, 0.5098f, 0.7059f, 0.0f};
static const DRGB_t RGB_STEEL_BLUE_LIGHT     = {0.6902f, 0.7686f, 0.8706f, 0.0f};
static const DRGB_t RGB_TURQUOISE_BLUE       = {0.0000f, 0.7800f, 0.5500f, 0.0f};
static const DRGB_t RGB_ULTRAMARINE	      = {0.0700f, 0.0400f, 0.5600f, 0.0f};

//   MAGENTAS
static const DRGB_t RGB_BLUE_VIOLET	      = {0.5412f, 0.1686f, 0.8863f, 0.0f};
static const DRGB_t RGB_COBALT_VIOLET_DEEP   = {0.5700f, 0.1300f, 0.6200f, 0.0f};
static const DRGB_t RGB_MAGENTA	      = {1.0000f, 0.0000f, 1.0000f, 0.0f};
static const DRGB_t RGB_ORCHID 	      = {0.8549f, 0.4392f, 0.8392f, 0.0f};
static const DRGB_t RGB_ORCHID_DARK	      = {0.6000f, 0.1961f, 0.8000f, 0.0f};
static const DRGB_t RGB_ORCHID_MEDIUM	      = {0.7294f, 0.3333f, 0.8275f, 0.0f};
static const DRGB_t RGB_PERMANENT_RED_VIOLET = {0.8600f, 0.1500f, 0.2700f, 0.0f};
static const DRGB_t RGB_PLUM		      = {0.8667f, 0.6275f, 0.8667f, 0.0f};
static const DRGB_t RGB_PURPLE 	      = {0.6275f, 0.1255f, 0.9412f, 0.0f};
static const DRGB_t RGB_PURPLE_MEDIUM	      = {0.5765f, 0.4392f, 0.8588f, 0.0f};
static const DRGB_t RGB_ULTRAMARINE_VIOLET   = {0.3600f, 0.1400f, 0.4300f, 0.0f};
static const DRGB_t RGB_VIOLET 	      = {0.5600f, 0.3700f, 0.6000f, 0.0f};
static const DRGB_t RGB_VIOLET_DARK	      = {0.5804f, 0.0000f, 0.8275f, 0.0f};
static const DRGB_t RGB_VIOLET_RED	      = {0.8157f, 0.1255f, 0.5647f, 0.0f};
static const DRGB_t RGB_VIOLET_RED_MEDIUM    = {0.7804f, 0.0824f, 0.5216f, 0.0f};
static const DRGB_t RGB_VIOLET_RED_PALE      = {0.8588f, 0.4392f, 0.5765f, 0.0f};

};

#endif // !defined(_ovrl_COLORS_H)
