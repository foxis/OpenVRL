#define STAR_VB	OVRL_VB_XYZ|OVRL_VB_NORMAL
#define STAR_IB OVRL_IB_16

struct star_vertex
{
		float x, y, z;
		float nx, ny, nz;
};

star_vertex g_star_vb[] = {
			{0.0f, -0.0f, 0.0f,},
			{0.214286f, -0.214286f, 0.214286f,},
			{-0.214286f, -0.214286f, 0.214286f,},
			{-0.214286f, -0.214286f, -0.214286f,},
			{0.214286f, -0.214286f, -0.214286f,},
			{0.214286f, 0.214286f, 0.214286f,},
			{-0.214286f, 0.214286f, 0.214286f,},
			{-0.214286f, 0.214286f, -0.214286f,},
			{0.214286f, 0.214286f, -0.214286f,},
			{0.000000f, 0.000000f, 1.000000f,},
			{0.000000f, 0.000000f, -1.000000f,},
			{1.000000f, 0.000000f, 0.000000f,},
			{-1.000000f, 0.000000f, 0.000000f,},
			{0.000000f, -1.000000f, 0.000000f,},
			{0.000000f, 1.000000f, 0.000000f,},
		};

ushort g_star_ib[] = 
{9, 5, 6, 9, 1, 5, 9, 6, 2, 9, 2, 1, 11, 5, 1, 11, 8, 5, 11, 4, 8, 11, 1, 4,
12, 2, 6, 12, 6, 7, 12, 7, 3, 2, 12, 3, 10, 7, 8, 10, 8, 4, 10, 3, 7, 3, 10, 4,
13, 1, 2, 13, 4, 1, 13, 2, 3, 13, 3, 4, 5, 14, 6, 5, 8, 14, 6, 14, 7, 7, 14, 8,
};