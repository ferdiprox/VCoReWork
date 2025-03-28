#include <zlib.h>

#include "xgraph.h"
#include "3dgraph.h"
#include "3d_math.h"

#include "general.h"

extern XBuffer msg_buf;

int PRECISION_8 = 0;
int draw_mode = DRAW_GOURAUD;
int x_prec = 2;

Polygon* z_list_min=0;
Polygon* z_list_max=0;
Polygon* z_list_curr=0;
Polygon* max_z_poly=0;
Polygon* min_z_poly=0;

int poly_cnt=0;
int poly_number=-1;
int poly_save=0;

int focus=512;
double focus_flt=512.;

DBM A_g2s;
DBM A_s2g;
DBM A_g2sZ;
int ViewX = 0,ViewY = 0,ViewZ = 512;
Vector Refl(0,0,NORMAL),Light(NORMAL,0,NORMAL),View(0,0,NORMAL);
DBV CurrShadowDirection;
double ModulatedNORMAL;
int TurnAngle;
int sinTurn = 0,cosTurn = (1 << 16);
int sinTurnInv = 0,cosTurnInv = (1 << 16);
double sinTurnFlt = 0,cosTurnFlt = 1;
double sinTurnInvFlt = 0,cosTurnInvFlt = 1;
int SlopeAngle;
int ScreenCX;
int ScreenCY;
int TurnSecX;
int TurnSecY;
int ScaleMap = 256;
int ScaleMapInv = 256;
double ScaleMapFlt = 1.;
double ScaleMapInvFlt = 1.;

int CentrX = XGR_MAXX/2;
int CentrY = XGR_MAXY/2;
int CentrZ = 0;
int Xmax2 = XGR_MAXX/2 - 80;
int Ymax2 = XGR_MAXY/2 - 80;

int UcutLeft = 0;
int UcutRight = XGR_MAXX;
int VcutUp = 0;
int VcutDown = XGR_MAXY;

int u_cut_left;
int u_cut_right;
int v_cut_up;
int v_cut_down;

int flush_x = 0;
int flush_y = 0;
int flush_sx = XGR_MAXX;
int flush_sy = XGR_MAXY;

double Ha,Va;
double Hb,Vb;
double Oc,Hc,Vc;

int n_power = 8;

#ifdef _FOUT_
XStream fout("lst",XS_OUT);
#endif


/******************************************************************************
	 MEMORY HEAP Function & Variable
******************************************************************************/
MemoryHeap quant_heap("Quant mem heap overflow at addr");
MemoryHeap load_heap("Load mem heap overflow at addr");

MemoryHeap::MemoryHeap(const char* message)
	: overflow_message(message)
{
	offset = size = 0;
}
void MemoryHeap::alloc(int sz)
{
	if(size)
		ErrH.Abort("Multiple alloc for MemoryHeap");
	heap = new char[size = sz];
	offset = 0;
}

void MemoryHeap::end_alloc()
{
	if(size != offset) {
		if(size < offset) {
			ErrH.Abort("Defiбiency of locked memory");
		} else {
			ErrH.Abort("Abundance of locked memory");
        }
    }
	heap = 0;
	size = 0;
}

/******************************************************************************
	MAIN FUNCTION OF 3D GRAPH
******************************************************************************/
void graph3d_init()
{
	Light = DBV(Light).norm(NORMAL);

	if(!draw_buffer){
		draw_buffer = new unsigned char [2*DRAW_SX*DRAW_SY + 1];
		memset(draw_buffer,0,2*DRAW_SX*DRAW_SY + 1);
		}

	make_tables();

#ifndef COMPACT_3D
	max_z_poly = ALLOC(1,Polygon);
	min_z_poly = ALLOC(1,Polygon);
	max_z_poly -> num_vert = min_z_poly -> num_vert = 0;
	max_z_poly -> z_max = max_z_poly -> z_min = (float)INT_INF;
	min_z_poly -> z_max = min_z_poly -> z_min = (float)-INT_INF;

	min_z_poly -> prev = max_z_poly -> next = 0;
	z_list_max = min_z_poly -> next = max_z_poly;
	z_list_curr = z_list_min = max_z_poly -> prev = min_z_poly;
#endif

	poly_cnt = 0;

	focus_flt = focus = 512;

	UcutLeft = 0;
	UcutRight = XGR_MAXX ? XGR_MAXX : 640;
	VcutUp = 0;
	VcutDown = XGR_MAXY ? XGR_MAXY : 480;

#ifdef _MT_
	ViewX = (XGR_MAXX ? XGR_MAXX : 640)/2;
	ViewY = (XGR_MAXY ? XGR_MAXY : 480)/2;
#endif

#ifndef _SURMAP_
#ifdef _FOUT_
	fout.SetDigits(8);
#endif
	msg_buf.SetDigits(4);
	msg_buf < char(0);
#endif
}
void calc_border(int& x1,int& x2,int& xc,int& sx2,int& flush_x,int& flush_sx,int xmax)
{
	if(x1 < 0)
		x1 = 0;
	if(x2 >= xmax)
		x2 = xmax - 1;
	xc = (x1 + x2)/2;
	sx2 = (x2 - x1)/2;
	x1 = xc - sx2;
	x2 = xc + sx2;
	flush_x = x1;
	flush_sx = x2 - x1 + 1;
	if(flush_sx % 4)
		flush_sx += 8 - flush_sx % 8;
}
void calc_screen(int zoom_percent)
{
	if(zoom_percent > 0){
		Xmax2 = (XGR_MAXX*zoom_percent)/200;
		Ymax2 = (XGR_MAXY*zoom_percent)/200;

//		  focus = (Xmax2*540)/180;
		focus = 512;

		ScreenCX = XGR_MAXX/2;
		ScreenCY = XGR_MAXY/2;

		UcutLeft = ScreenCX - Xmax2;
		UcutRight = ScreenCX + Xmax2;
		VcutUp = ScreenCY - Ymax2;
		VcutDown = ScreenCY + Ymax2;

		calc_border(UcutLeft,UcutRight,ScreenCX,Xmax2,flush_x,flush_sx,XGR_MAXX);
		calc_border(VcutUp,VcutDown,ScreenCY,Ymax2,flush_y,flush_sy,XGR_MAXY);
		}

	focus_flt = focus;

#ifndef _SURMAP_
//	ViewX = XGR_MAXX/2;
//	ViewY = XGR_MAXY/2;
	ViewZ = focus;
#endif
}
/*******************************************************************************
		Vertex and Normal function
*******************************************************************************/


#ifndef COMPACT_3D
void Vertex::convert()
{
	if(PRECISION_8)
		turned = Vector(
			MUL(A_convert_8.a[0],x_8) + MUL(A_convert_8.a[1],y_8) + MUL(A_convert_8.a[2],z_8),
			MUL(A_convert_8.a[3],x_8) + MUL(A_convert_8.a[4],y_8) + MUL(A_convert_8.a[5],z_8),
			MUL(A_convert_8.a[6],x_8) + MUL(A_convert_8.a[7],y_8) + MUL(A_convert_8.a[8],z_8));
	else
		turned = A_convert*DBV(x,y,z);

	xscr = (turned.x > 0 ? turned.x + 1 >> 1: -(-turned.x + 1 >> 1)) + CentrX;
	yscr = (turned.y > 0 ? turned.y + 1 >> 1: -(-turned.y + 1 >> 1)) + CentrY;
	xscr_8 = (turned.x + 255) << x_prec - 1;
	yscr_8 = (turned.y + 255) >> 1;
}
void Normal::calc_intensity() // Metal
{
	int Intens;
	if(n_power){
		int Ln = Vector(*this)*Refl;
		int RV = (Refl - (Vector(*this)*Ln >> 13))*View;
		if(Ln < 0 || RV < 0){
			I = 0;
			I_8 = 0;
			return;
			}
		Intens = (power_table[(int(n_power) - 2 << 8) + (RV >> 7)] << 9)
				      + (Ln >> 1);
		}
	else{
		int Ln = Vector(*this)*Refl;
		if(Ln < 0){
			I = 0;
			I_8 = 0;
			return;
			}
		Intens = Ln;
		}

	if(Intens > (63 << 8))
		I = (63 << 8);
	else
		I = Intens;
	I_8 = I >> 7;
}
//void Normal::calc_intensity() // Diffuse
//{
//	  I = -(*this)*Refl >> 10;
//	  if(I < 0)
//		  I = 0;
//	  if(I > 63)
//		  I = 63;
//}
/*******************************************************************************
		Polygon function
*******************************************************************************/
void Polygon::put_in_list()
{
	Vertex* vl = vertices[0];
	Vertex* vc = vertices[1];
	Vertex* vr = vertices[2];
//	  int x0,y0,x1,y1,x2,y2;
//	  x0 = vl -> xscr; y0 = vl -> yscr;
//	  x1 = vc -> xscr; y1 = vc -> yscr;
//	  x2 = vr -> xscr; y2 = vr -> yscr;
//	  if((x0 - x1)*(y2 - y1) - (y0 - y1)*(x2 - x1) > 0)
//		  return;

	// SORTING
	z_max = CentrZ + max(vl -> turned.z,vc -> turned.z,vr -> turned.z);
	z_min = CentrZ + min(vl -> turned.z,vc -> turned.z,vr -> turned.z);

	z_max = (vl -> turned.z + vc -> turned.z + vr -> turned.z)/3;

	if(z_list_curr -> z_max < z_max){
		while(z_list_curr -> z_max < z_max)
			z_list_curr = z_list_curr -> next;
		next = z_list_curr;
		prev = z_list_curr -> prev;
		prev -> next = this;
		z_list_curr -> prev = this;
		}
	else{
		while(z_list_curr -> z_max > z_max)
			z_list_curr = z_list_curr -> prev;
		prev = z_list_curr;
		next = z_list_curr -> next;
		next -> prev = this;
		z_list_curr -> next = this;
		}
}


#ifndef _SURMAP_
void graph3d_flush()
{
	Polygon* poly = z_list_max -> prev;
	while(poly != z_list_min){
		switch(draw_mode){
			case DRAW_LINE:
				poly -> draw_line();
				break;
			case DRAW_FLAT:
				poly -> draw_flat();
				break;
			case DRAW_GOURAUD:
				poly -> draw_gouraud_old();
				break;
			}
		poly = poly -> prev;
		}

	min_z_poly -> prev = max_z_poly -> next = 0;
	z_list_max = min_z_poly -> next = max_z_poly;
	z_list_curr = z_list_min = max_z_poly -> prev = min_z_poly;

	poly_cnt = 0;
}
#endif
#endif

void z_line(int x1,int y1,int x2,int y2,int c1,int c2)
{
	#define F_PREC	8
	int k,a,b,x,y;
	int c,ck;
	if(x1 == x2 && y1 == y2) return;

	c1 <<= F_PREC;
	c2 <<= F_PREC;

	if(abs(x2 - x1) > abs(y2 - y1)){
		if(x1 > x2){
			xorSwap(x1,x2);
			xorSwap(y1,y2);
			xorSwap(c1,c2);
			}
		a = x2 - x1;
		b = y2 - y1;
		x = x1;
		y = (y1 << F_PREC) + (1 << (F_PREC - 1));
		k = (b << F_PREC)/a;
		ck = (c2 - c1)/a;
		c = c1;
		do{
			XGR_SetPixel(x,y >> F_PREC,c >> F_PREC);
			x++;
			y+=k;
			c+=ck;
			} while(--a >= 0);
		}
	else{
		if(y1 > y2){
			xorSwap(x1,x2);
			xorSwap(y1,y2);
			xorSwap(c1,c2);
			}
		a = x2 - x1;
		b = y2 - y1;
		x = (x1 << F_PREC) + (1 << (F_PREC - 1));
		y = y1;
		k = (a << F_PREC)/b;
		ck = (c2 - c1)/b;
		c = c1;
		do{
			XGR_SetPixel(x >> F_PREC,y,c >> F_PREC);
			y++;
			x+=k;
			c+=ck;
			} while(--b >= 0);
		}
}
void output_palette()
{
	char buf[256*3];
	XGR_GetPal(buf);
	XStream f("output.pal",XS_OUT);
	f.write(buf,256*3);
	ErrH.Abort("Palette is grabbed");
}

void clip_pixel(int x,int y,int col)
{
	if(x >= UcutLeft && x < UcutRight && y >= VcutUp && y < VcutDown)
		XGR_SetPixel(x,y,col);
}
void clip_line(int x1,int y1,int x2,int y2,int color)
{
	if(x1 >= UcutLeft && x1 <= UcutRight && y1 >= VcutUp && y1 <= VcutDown &&
	   x2 >= UcutLeft && x2 <= UcutRight && y2 >= VcutUp && y2 <= VcutDown)
		XGR_Line(x1,y1,x2,y2,color);
}



