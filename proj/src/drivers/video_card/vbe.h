#ifndef _VBE_H_
#define _VBE_H_


// MODES
#define MODE1   0x105	// 1024x768	    Indexed	8
#define MODE2   0x110	// 640x480	    Direct color	15((1:)5:5:5)
#define MODE3   0x115	// 800x600	    Direct color	24 (8:8:8)
#define MODE4   0x11A	// 1280x1024	  Direct color	16 (5:6:5)
#define MODE5   0x14C	// 1152x864	    Direct color	32 ((8:)8:8:8)

#define WRT_FUNC 0x4F

#define VBE_GET_MODE 0x01    
#define VBE_SET_MODE 0x02

#define LINEAR_FRAME_BUFFER BIT(14)

#define FUNC_SUPPORTED 0x4F

#define TRANSPARENT 0xFF00FF
#define LETTER_WIDTH 76

#endif
