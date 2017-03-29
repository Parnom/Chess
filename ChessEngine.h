#pragma once
 //  #define VER "5.3.2"
#define VER "6.0.3"

#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#include <conio.h>
#include <sys/timeb.h>
struct _timeb tv;
#else
#include <sys/time.h>
struct timeval tv;
struct timezone tz;
#endif

typedef unsigned long long u64;
typedef unsigned long u32;
typedef int Move;

#define PAWN 1             // Bauer
#define KNIGHT 2           // Pferd
#define KING 3             // König
#define ENP 4              // Enpassant = wenn bauer 2 felder zieht kann gegner bauer schlagen 
#define BISHOP 5           // Läufer
#define ROOK 6             // Turm
#define QUEEN 7            // Dame

#define CNODES 0xFFFF
const int pval[] = { 0, 100, 290, 0, 100, 310, 500, 950 };
const int pawnrun[] = { 0, 0, 1, 8, 16, 32, 64, 128 };

#define FROM(x) ((x) & 63)               // abfrage ersten 6 Bit
#define TO(x) (((x) >> 6) & 63)          // abfrage Bit 7 bis 12
#define PROM(x) (((x) >> 12) & 7)
#define PIECE(x) (((x) >> 15) & 7)       // Bauer = 1 usw...
#define ONMV(x) (((x) >> 18) & 1)        // On Move  (weiss od. schwarz)
#define CAP(x) (((x) >> 19) & 7)         // liefert Bit 19  bis 21

#define _TO(x) ((x) << 6)
#define _PROM(x) ((x) << 12)
#define _PIECE(x) ((x) << 15)
#define _ONMV(x) ((x) << 18)
#define _CAP(x) ((x) << 19)             // liefert die oberen Bits
#define PREMOVE(f, p) ((f) | _ONMV(c) | _PIECE(p))

#define RATT1(f) rays[((f) << 7) | key000(BOARD, f)]
#define RATT2(f) rays[((f) << 7) | key090(BOARD, f) | 0x2000]
#define BATT3(f) rays[((f) << 7) | key045(BOARD, f) | 0x4000]
#define BATT4(f) rays[((f) << 7) | key135(BOARD, f) | 0x6000]
#define RXRAY1(f) rays[((f) << 7) | key000(BOARD, f) | 0x8000]
#define RXRAY2(f) rays[((f) << 7) | key090(BOARD, f) | 0xA000]
#define BXRAY3(f) rays[((f) << 7) | key045(BOARD, f) | 0xC000]
#define BXRAY4(f) rays[((f) << 7) | key135(BOARD, f) | 0xE000]

#define ROCC1(f) (RATT1(f) & BOARD)
#define ROCC2(f) (RATT2(f) & BOARD)
#define BOCC3(f) (BATT3(f) & BOARD)
#define BOCC4(f) (BATT4(f) & BOARD)
#define RMOVE1(f) (RATT1(f) & (~BOARD))
#define RMOVE2(f) (RATT2(f) & (~BOARD))
#define BMOVE3(f) (BATT3(f) & (~BOARD))
#define BMOVE4(f) (BATT4(f) & (~BOARD))
#define RCAP1(f, c) (RATT1(f) & colorb[(c)^1])
#define RCAP2(f, c) (RATT2(f) & colorb[(c)^1])
#define BCAP3(f, c) (BATT3(f) & colorb[(c)^1])
#define BCAP4(f, c) (BATT4(f) & colorb[(c)^1])
#define ROCC(f) (ROCC1(f) | ROCC2(f))
#define BOCC(f) (BOCC3(f) | BOCC4(f))
#define RMOVE(f) (RMOVE1(f) | RMOVE2(f))
#define BMOVE(f) (BMOVE3(f) | BMOVE4(f))
#define RCAP(f, c) (ROCC(f) & colorb[(c)^1])
#define BCAP(f, c) (BOCC(f) & colorb[(c)^1])

#define SHORTMOVE(x) ((x) & ((x)^BOARD))
#define SHORTOCC(x) ((x) & BOARD)
#define SHORTCAP(x, c) ((x) & colorb[(c)^1])

#define NMOVE(x) (SHORTMOVE(nmoves[x]))
#define KMOVE(x) (SHORTMOVE(kmoves[x]))
#define PMOVE(x, c) (pmoves[(x) | ((c)<<6)] & (~BOARD))
#define NOCC(x) (SHORTOCC(nmoves[x]))
#define KOCC(x) (SHORTOCC(kmoves[x]))
#define POCC(x, c) (pcaps[(x) | ((c)<<6)] & BOARD)
#define NCAP(x, c) (SHORTCAP(nmoves[x], (c)))
#define KCAP(x, c) (SHORTCAP(kmoves[x], (c)))
#define PCAP(x, c) (pcaps[(x) | ((c)<<6)] & colorb[(c)^1])
#define PCA3(x, c) (pcaps[(x) | ((c)<<6) | 128] & (colorb[(c)^1] | ((BIT[ENPASS]) & (c ? 0xFF0000LL : 0xFF0000000000LL))))
#define PCA4(x, c) (pcaps[(x) | ((c)<<6) | 256] & (colorb[(c)^1] | ((BIT[ENPASS]) & (c ? 0xFF0000LL : 0xFF0000000000LL))))

#define RANK(x, y) (((x) & 0x38) == (y))
#define TEST(f, b) (BIT[f] & (b))
#define ENPASS (flags & 63)
#define CASTLE (flags & 960)      // Roucharde !!
#define COUNT (count_a & 0x3FF)   // Halbzug

#define HSIZEB 0x200000
#define HMASKB 0x1FFFFF
#define HINVB 0xFFFFFFFFFFE00000LL

#define HSIZEP 0x400000
#define HMASKP 0x3FFFFF
#define HINVP 0xFFFFFFFFFFC00000LL

u64 hashDB[HSIZEB];
u64 hashDP[HSIZEP];  // Hash nur für Bauern (Pawn)
u64 hashb;
u64 hstack[0x800];
u64 mstack[0x800];

u64 mstackCopy[0x800];
u64 piecebCopy[8];
u64 colorbCopy[2];
int countCopy;

static u64 hashxor[4096];
static u64 rays[0x10000];
static u64 pmoves[128];  // Bauern Züge
static u64 pcaps[384];
static u64 nmoves[64];  // Pferd Züge
static u64 kmoves[64];  // König Züge
static int _knight[8] = { -17,-10,6,15,17,10,-6,-15 };   // Pferd Züge möglichkeiten
static int _king[8] = { -9,-1,7,8,9,1,-7,-8 };           // König Züge möglichkeiten
static u64 BIT[64];      // Bit Maske 0000001, 0000010,0000100,00010000, usw
static char LSB[0x10000];
static char BITC[0x10000];
static int crevoke[64];
static int nmobil[64];
static int kmobil[64];
static int pawnprg[128];
static u64 pawnfree[128];
static u64 pawnfile[128];
static u64 pawnhelp[128];
Move movelist[64 * 256]; // alle möglichen Züge einer Farbe
int movenum[64];
Move pv[64][64];    // Zugbaum pv[0][0] = letzter Zug
int pvlength[64];
int value[64]; // Werte der züge
int iter;
const char pieceChar[] = "*PNK.BRQ";
u64 searchtime, maxtime, starttime;
int sabort, noabort;         // Search Abort
int ponder = 0, pondering = 0;
Move pon = 0;
int count_a, flags, mat, onmove, engine = -1;
int sd = 32;       // max Search Deep
int kingpos[2];    // Position der Könige
u64 pieceb[8];    // Positionsspeicher [1] = Bauern , [2] = Pferd , usw 
u64 colorb[2];    // Positionsspeicher [0] = Weiss , [1] = Schwarze Figuren
char irbuf[256];  // Eingabe Buffer

int automatik = 0; //   Comp vs Comp
int turnB = 1;     // Console weiss unten oder oben  1 = weiss unten
int hint = 0;
//    int colorBack = 7; // Hintergrundfarbe Console 
int maxMove = 0;
#define BOARDXY1(x) ((((x / 8) + 1) * 8 - (x % 8) - 1))      // 7,6,5,4,3,2,1,0,15,.....
#define BOARDXY0(x) ((7 - (x / 8)) * 8 + (x % 8))          //56,57,58,59,60,61,62,63,48,49,.........

long long zähler = 0; //  wegen Tests

#define BOARD (colorb[0] | colorb[1])   // liefert alle Figuren vom Brett weiss + schwarz
#define RQU (pieceb[QUEEN] | pieceb[ROOK]) // liefert alle Damen und Türme
#define BQU (pieceb[QUEEN] | pieceb[BISHOP]) // liefert alle Damen und Läufer


void setBit(int f, u64 *b) {      // Bit Setzen
	*b |= BIT[f];
}

void xorBit(int f, u64 *b) {      // Bit umschalten
	*b ^= BIT[f];
}

u64 getLowestBit(u64 bb) {
	return bb & (-(long long)bb);        // gibt das loweste bit in zB 128 zurück ??
}

int _getpiece(char s, int *c) {         // gibt Figuren zurück 
	int i;
	for (i = 1; i < 8; i++)
		if (pieceChar[i] == s) { *c = 0; return i; }
		else if (pieceChar[i] == s - 32) { *c = 1; return i; }
		return 0;
}

int book;
void _parse_fen(char *fen) {                   //einscannen von char to system (SPIELFELDFIGUREN)
	char s, mv, pos[128], cas[5], enps[3];
	int c, i, halfm = 0, fullm = 1, col = 0, row = 7;
	for (i = 0; i < 8; i++) pieceb[i] = 0LL;
	colorb[0] = colorb[1] = hashb = 0LL;
	mat = book = i = c = cas[0] = enps[0] = 0;
	sscanf(fen, "%s %c %s %s %d %d", pos, &mv, cas, enps, &halfm, &fullm);
	while ((s = pos[i++])) {
		if (s == '/') {
			row--;
			col = 0;
		}
		else if (s >= '1' && s <= '8') {
			col += s - '0';
		}
		else {
			int p = _getpiece(s, &c);
			if (p == KING) kingpos[c] = row * 8 + col;
			else mat += c ? -pval[p] : pval[p];
			hashb ^= hashxor[col | row << 3 | i << 6 | (c ? 512 : 0)];
			setBit(row * 8 + col, pieceb + p);
			setBit(row * 8 + (col++), colorb + c);
		}
	}
	onmove = mv == 'b' ? 1 : 0;
	flags = i = 0;
	while ((s = cas[i++])) {
		if (s == 'K') flags |= BIT[6];
		if (s == 'k') flags |= BIT[7];
		if (s == 'Q') flags |= BIT[8];
		if (s == 'q') flags |= BIT[9];
	}
	if (enps[0] >= 'a' && enps[0] <= 'h' && enps[1] >= '1' && enps[1] <= '8') flags |= 8 * (enps[1] - '1') + enps[0] - 'a';
	count_a = (fullm - 1) * 2 + onmove + (halfm << 10);
	for (i = 0; i < COUNT; i++) hstack[i] = 0LL;
}

int parseMoveNExec(char*, int, Move*);
int parseMove(char*, int, Move);
int protV2(char*);
char *sfen = "rnbqkbnr/pppppppp/////PPPPPPPP/RNBQKBNR w KQkq - 0 1"; // Anfangs Brettaufstellung 
#define BKSIZE 1024
Move bkmove[BKSIZE * 32];
int bkflag[BKSIZE];
int bkcount[3];
/*
void displaym(Move m) {
	printf("%c%c%c%c", 'a' + FROM(m) % 8, '1' + FROM(m) / 8,
		'a' + TO(m) % 8, '1' + TO(m) / 8);
	if (PROM(m)) printf("%c", pieceChar[PROM(m)] + 32);
}

void setConsolColor(int fgcolor, int bgcolor) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), bgcolor * 16 + fgcolor);
}
*/



void _readbook(char *bk) {         // Eröffnungszüge momentan nicht benützt 
	char buf[256], s0[64], s1[64], s2[64];
	int k = 0;
	int n = 0;
	FILE *in = fopen(bk, "r");
	bkcount[0] = bkcount[1] = 0;
	for (k = 0; k < BKSIZE; k++) bkflag[k] = 2;
	if (in != NULL) {
		while (!feof(in)) {
			fgets(buf, 255, in);
			if (buf[0] == '[') {
				sscanf(buf, "%s %s", s1, s2);
				if (!strncmp(s2, "\"OliThink", 8)) bkflag[n] = strncmp(s1, "[Black", 6) ? 0 : 1;
			}
			else if (buf[0] == '1') {
				int i = 0, j = 0;
				_parse_fen(sfen);
				for (;;) {
					sscanf(buf + i, "%s %s", s0, s2);
					if (s0[0] < '1' || s0[0] > '9') break;
					i += (int)(strlen(s0) + strlen(s2) + 2);
					sscanf(s0, "%*[^.].%[^.]", s1);
					parseMoveNExec(s1, 0, bkmove + n * 32 + (j++));
					if (s2[0] == 0 || s2[0] == '*') break;
					parseMoveNExec(s2, 1, bkmove + n * 32 + (j++));
					if (j > 30) break;
				}
				bkmove[n * 32 + j] = 0;
				if (j) bkcount[bkflag[n]]++;
				if (++n == BKSIZE) break;
			}
		}
		fclose(in);
	}
	_parse_fen(sfen);
	if (bkcount[0] > 0 || bkcount[1] > 0) book = 1;
	engine = 1;
	sd = 32;
}

int saveStellung(char string[]) {   		//Save lt. "Fen" Standart
	char buf[256] = { 0 };	
	int countLeer = 0;	int c = 0;	int x = 0;	int i = 0;
	FILE *zugsp;
	for (i = 0; i < 64; i++) {
		x = BOARDXY0(i);
		if (((i) % 8 == 0) && i != 0) { buf[c] = '/';c++; }
		if ((BIT[x] & colorb[0]) || (BIT[x] & colorb[1])) {
			if (BIT[x] & pieceb[PAWN])buf[c] = 'P';
			else if (BIT[x] & pieceb[KNIGHT])buf[c] = 'N';
			else if (BIT[x] & pieceb[KING])buf[c] = 'K';
			else if (BIT[x] & pieceb[BISHOP])buf[c] = 'B';
			else if (BIT[x] & pieceb[ROOK])buf[c] = 'R';
			else if (BIT[x] & pieceb[QUEEN])buf[c] = 'Q';
			if ((BIT[x] & colorb[NULL]) == 0) buf[c] += 32;
			c++;
		}
		else {
			if ((BIT[x + 1] & colorb[0]) || (BIT[x + 1] & colorb[1])) {
				buf[c] = ('1') + countLeer;
				countLeer = 0;
				c++;
			}
			else countLeer++;
		}
		if (((i + 1) % 8 == 0) && countLeer != 0) { buf[c] = ('0') + countLeer;c++;countLeer = 0; }
	}
	buf[c] = ' ';	c++;
	onmove == 1 ? buf[c] = 'b' : buf[c] = 'w';	c++;
	buf[c] = ' '; c++;
	if (!((flags >> 6) & 0xf)) { buf[c] = '-'; c++; }
	else {
		if (flags & BIT[6]) { buf[c] = 'K'; c++; };
		if (flags & BIT[8]) { buf[c] = 'Q'; c++; };
		if (flags & BIT[7]) { buf[c] = 'k'; c++; };
		if (flags & BIT[9]) { buf[c] = 'q'; c++; };
	};
	buf[c] = ' ';	 c++;
	int a = 0;
	if ((flags & 0x3f) != 0) {
		a = (flags & 0x3f);
		buf[c] = 'a' + (a % 8);	c++;
		buf[c] = '1' + (a / 8);	c++;
		buf[c] = ' ';c++;
	}
	else { buf[c] = '-'; c++; buf[c] = ' ';c++; };
	int z = (count_a >> 10);
	if (z / 10 >= 1) {
		buf[c] = '0' + (z / 10);c++;
		z -= 10 * (z / 10);
	}
	buf[c] = '0' + z;	 c++;
	buf[c] = ' ';	 c++;
	int b = (COUNT);
	b = (b / 2) + 1;
	if (b / 1000 >= 1) {
		buf[c] = '0' + (b / 1000);c++;b -= 1000;
	}
	if (b / 100 >= 1) {
		buf[c] = '0' + (b / 100);c++;b -= 100 * (b / 100);
	}
	if (b / 10 >= 1) {
		buf[c] = '0' + (b / 10);c++;b -= 10 * (b / 10);
	}
	buf[c] = '0' + b;c++;buf[c] = ' ';c++;buf[c] = '\0';
	zugsp = fopen(string, "w");
	if (zugsp == NULL) {
	//	printf("\nSpielstand kann nicht angelegt werden !\n");
		return 1;
	}
	else {
		fputs(buf, zugsp);
	}
	fclose(zugsp);
	return 0;
}

void saveValues() {
	countCopy = COUNT;
	for (int i = 0; i < COUNT; i++) {
		mstackCopy[i] = mstack[i];
	}
	for (int i = 0; i < 8; i++) {
		piecebCopy[i] = pieceb[i];
	}
	for (int i = 0; i < 2; i++) {
		colorbCopy[i] = colorb[i];
	}
}

int saveMstack(char string[]) {
	FILE *mstackB = fopen(string, "w");
	if (mstackB == NULL) {
	//	printf("\nStackdatei kann nicht angelegt werden !!\n");
		return 1;
	}
	else {
		for (int z = 0; z < 2047; z++) {
			fprintf(mstackB, "%llu\n", mstack[z]);
			if (mstack[z] == 0) break;
		}
	}
	fclose(mstackB);
	return 0;
}

int loadMstack(char string[]) {
	FILE *in = fopen(string, "r");
	if (in == NULL) {
	//	printf("Stackdatei nicht gefunden !!");
		return 1;
	}
	else {
		for (int a = 0; a < 2048; a++) {
			fscanf(in, "%llu\n", &mstack[a]);
			if (mstack[a] == 0)	break;
		}
	}
	fclose(in);
	saveValues();
	return 0;
}

int loadStellung(char string[]) {
	
	char buf[256];
	FILE *in = fopen(string, "r");
	if (in != NULL) {
		while (!feof(in)) {
			fgets(buf, 255, in);
			_parse_fen(buf);
		}
	}
	else {
	//	printf("\n Spielstand kann nicht geladen werden !! \n");
		_parse_fen(sfen);
		return 1;
	}
	fclose(in);
	saveValues();
	return 0;
}

#define LOW16(x) ((x) & 0xFFFF)
#define LOW32(x) ((x) & 0xFFFFFFFF)
static u32 r_x = 30903, r_y = 30903, r_z = 30903, r_w = 30903, r_carry = 0;
u32 _rand_32() {
	u32 t;
	r_x = LOW32(r_x * 69069 + 1);
	r_y ^= LOW32(r_y << 13);
	r_y ^= LOW32(r_y >> 17);
	r_y ^= LOW32(r_y << 5);
	t = LOW32((r_w << 1) + r_z + r_carry);
	r_carry = (LOW32(r_z >> 2) + LOW32(r_w >> 3) + LOW32(r_carry >> 2)) >> 30;
	r_z = r_w;
	r_w = t;
	return LOW32(r_x + r_y + r_w);
}

u64 _rand_64() { u64 c = _rand_32(); return _rand_32() | (c << 32); }

u64 getTime() {
#ifdef _WIN32
	_ftime(&tv);
	return(tv.time * 1000LL + tv.millitm);
#else
	gettimeofday(&tv, &tz);
	return(tv.tv_sec * 1000LL + (tv.tv_usec / 1000));
#endif
}

char getLsb(u64 bm) {
	u32 n = (u32)LOW32(bm);
	if (n) {
		if LOW16(n) return LSB[LOW16(n)];
		else return 16 | LSB[LOW16(n >> 16)];
	}
	else {
		n = (u32)(bm >> 32);
		if LOW16(n) return 32 | LSB[LOW16(n)];
		else return 48 | LSB[LOW16(n >> 16)];
	}
}

char _slow_lsb(u64 bm) {
	int k = -1;
	while (bm) { k++; if (bm & 1) break; bm >>= 1; }
	return (char)k;
}

int pullLsb(u64* bit) {
	int f = getLsb(*bit);
	*bit ^= BIT[f];
	return f;
}

char _bitcnt(u64 bit) {      // !! Ausgefinkelter Bit Zähler :-)
	char c = 0;
	while (bit) { bit &= (bit - 1); c++; }
	return c;
}

char bitcnt(u64 n) {
	return BITC[LOW16(n)]
		+ BITC[LOW16(n >> 16)]
		+ BITC[LOW16(n >> 32)]
		+ BITC[LOW16(n >> 48)];
}

int identPiece(int f) {            // Schachfigur identifizieren
	if (TEST(f, pieceb[PAWN])) return PAWN;
	if (TEST(f, pieceb[KNIGHT])) return KNIGHT;
	if (TEST(f, pieceb[BISHOP])) return BISHOP;
	if (TEST(f, pieceb[ROOK])) return ROOK;
	if (TEST(f, pieceb[QUEEN])) return QUEEN;
	if (TEST(f, pieceb[KING])) return KING;
	return ENP;                    // Enpassant
}

u64 bmask45[64];
u64 bmask135[64];
int key000(u64 b, int f) {
	return (int)((b >> (f & 56)) & 0x7E);
}

int key090(u64 b, int f) {
	u64 _b = (b >> (f & 7)) & 0x0101010101010101LL;
	_b = _b * 0x0080402010080400LL;
	return (int)(_b >> 57);
}

int keyDiag(u64 _b) {
	_b = _b * 0x0202020202020202LL;
	return (int)(_b >> 57);
}

int key045(u64 b, int f) {
	return keyDiag(b & bmask45[f]);
}

int key135(u64 b, int f) {
	return keyDiag(b & bmask135[f]);
}

#define DUALATT(x, y, c) (battacked(x, c) || battacked(y, c))
int battacked(int f, int c) {
	if (PCAP(f, c) & pieceb[PAWN]) return 1;
	if (NCAP(f, c) & pieceb[KNIGHT]) return 1;
	if (KCAP(f, c) & pieceb[KING]) return 1;
	if (RCAP1(f, c) & RQU) return 1;
	if (RCAP2(f, c) & RQU) return 1;
	if (BCAP3(f, c) & BQU) return 1;
	if (BCAP4(f, c) & BQU) return 1;
	return 0;
}

u64 reach(int f, int c) {
	return (NCAP(f, c) & pieceb[KNIGHT])
		| (RCAP1(f, c) & RQU)
		| (RCAP2(f, c) & RQU)
		| (BCAP3(f, c) & BQU)
		| (BCAP4(f, c) & BQU);
}

u64 attacked(int f, int c) {
	return (PCAP(f, c) & pieceb[PAWN]) | reach(f, c);
}

void _init_pawns(u64* moves, u64* caps, u64* freep, u64* filep, u64* helpp, int c) {
	int i, j;
	for (i = 0; i < 64; i++) {
		int rank = i / 8;
		int file = i & 7;
		int m = i + (c ? -8 : 8);
		pawnprg[i + (c << 6)] = pawnrun[c ? 7 - rank : rank];
		for (j = 0; j < 64; j++) {
			int jrank = j / 8;
			int jfile = j & 7;
			int dfile = (jfile - file)*(jfile - file);
			if (dfile > 1) continue;
			if ((c && jrank < rank) || (!c && jrank > rank)) {//The not touched half of the pawn
				if (dfile == 0) setBit(j, filep + i);
				setBit(j, freep + i);
			}
			else if (dfile != 0 && (jrank - rank)*(jrank - rank) <= 1) {
				setBit(j, helpp + i);
			}
		}
		if (m < 0 || m > 63) continue;            // Pferd abfrage :) nachdenken mal?
		setBit(m, moves + i);
		if (file > 0) {
			m = i + (c ? -9 : 7);
			if (m < 0 || m > 63) continue;
			setBit(m, caps + i);
			setBit(m, caps + i + 128 * (2 - c));
		}
		if (file < 7) {
			m = i + (c ? -7 : 9);
			if (m < 0 || m > 63) continue;
			setBit(m, caps + i);
			setBit(m, caps + i + 128 * (c + 1));
		}
	}
}

void _init_shorts(u64* moves, int* m) {
	int i, j, n;
	for (i = 0; i < 64; i++) {
		for (j = 0; j < 8; j++) {
			n = i + m[j];
			if (n < 64 && n >= 0 && ((n & 7) - (i & 7))*((n & 7) - (i & 7)) <= 4) {
				setBit(n, moves + i);
			}
		}
	}
}

u64 _occ_free_board(int bc, int del, u64 free) {      // ???????????????????????
	u64 low, perm = free;
	int i;
	for (i = 0; i < bc; i++) {
		low = getLowestBit(free);
		free &= (~low);
		if (!TEST(i, del)) perm &= (~low);
	}
	return perm;
}

void _init_rays(u64* rays, u64(*rayFunc)(int, u64, int), int(*key)(u64, int)) {
	int i, f, iperm, bc, index;
	u64 board, mmask, occ, move, xray;
	for (f = 0; f < 64; f++) {
		mmask = (*rayFunc)(f, 0LL, 0) | BIT[f];
		iperm = 1 << (bc = bitcnt(mmask));
		for (i = 0; i < iperm; i++) {
			board = _occ_free_board(bc, i, mmask);
			move = (*rayFunc)(f, board, 1);
			occ = (*rayFunc)(f, board, 2);
			xray = (*rayFunc)(f, board, 3);
			index = (*key)(board, f);
			rays[(f << 7) + index] = occ | move;
			rays[(f << 7) + index + 0x8000] = xray;
		}
	}
}

#define RAYMACRO {if (TEST(i, board)) { if (b) { setBit(i, &xray); break; } else { setBit(i, &occ); b = 1; } } if (!b) setBit(i, &free);}
u64 _rook0(int f, u64 board, int t) {
	u64 free = 0LL, occ = 0LL, xray = 0LL;
	int i, b;
	for (b = 0, i = f + 1; i < 64 && i % 8 != 0; i++) RAYMACRO     // Türme horizontal prüfung 
		for (b = 0, i = f - 1; i >= 0 && i % 8 != 7; i--) RAYMACRO
			return (t < 2) ? free : (t == 2 ? occ : xray);
}

u64 _rook90(int f, u64 board, int t) {
	u64 free = 0LL, occ = 0LL, xray = 0LL;
	int i, b;
	for (b = 0, i = f - 8; i >= 0; i -= 8) RAYMACRO                // Türme vertikal prüfung
		for (b = 0, i = f + 8; i < 64; i += 8) RAYMACRO
			return (t < 2) ? free : (t == 2 ? occ : xray);
}

u64 _bishop45(int f, u64 board, int t) {
	u64 free = 0LL, occ = 0LL, xray = 0LL;
	int i, b;
	for (b = 0, i = f + 9; i < 64 && (i % 8 != 0); i += 9) RAYMACRO      // Läufer 45 grad Prüfung
		for (b = 0, i = f - 9; i >= 0 && (i % 8 != 7); i -= 9) RAYMACRO
			return (t < 2) ? free : (t == 2 ? occ : xray);
}

u64 _bishop135(int f, u64 board, int t) {
	u64 free = 0LL, occ = 0LL, xray = 0LL;
	int i, b;
	for (b = 0, i = f - 7; i >= 0 && (i % 8 != 0); i -= 7) RAYMACRO      // Läufer 135 grad Prüfung
		for (b = 0, i = f + 7; i < 64 && (i % 8 != 7); i += 7) RAYMACRO
			return (t < 2) ? free : (t == 2 ? occ : xray);
}

int isDraw(u64 hp, int nrep) {
	if (count_a > 0xFFF) { //fifty > 3
		int i, c = 0, n = COUNT - (count_a >> 10);
		if (count_a >= 0x400 * 100) return 2; //100 plies
		for (i = COUNT - 2; i >= n; i--)
			if (hstack[i] == hp && ++c == nrep) return 1;
	}
	else if (!(pieceb[PAWN] | RQU)) { //Check for mating material
		if (_bitcnt(colorb[0]) <= 2 && _bitcnt(colorb[1]) <= 2) return 3;
	}
	return 0;
}

u64 pinnedPieces(int f, int oc) {      // festgenagelte Stücke
	u64 pin = 0LL;
	u64 b = ((RXRAY1(f) | RXRAY2(f)) & colorb[oc]) & RQU;
	while (b) {
		int t = pullLsb(&b);
		pin |= RCAP(t, oc) & ROCC(f);
	}
	b = ((BXRAY3(f) | BXRAY4(f)) & colorb[oc]) & BQU;
	while (b) {
		int t = pullLsb(&b);
		pin |= BCAP(t, oc) & BOCC(f);
	}
	return pin;
}

char getDir(int f, int t) {
	if (!((f ^ t) & 56)) return 8;
	if (!((f ^ t) & 7)) return 16;
	return ((f - t) % 7) ? 32 : 64;
}

#define XORHASH(f, p, c) hashb ^= hashxor[(f) | (p) << 6 | (c) << 9]
/* move is for both doMove and undoMove, only for unmakeMove the globalflags have to be restored (counter, castle, enpass...) */
void move(Move m, int c) {
	int f = FROM(m);
	int t = TO(m);
	int p = PIECE(m);
	int a = CAP(m);

	xorBit(f, colorb + c);
	xorBit(f, pieceb + p);

	xorBit(t, colorb + c);
	xorBit(t, pieceb + p);
	XORHASH(f, p, c);
	XORHASH(t, p, c);

	flags &= 960;
	count_a += 0x401;
	if (a) {
		if (a == ENP) { // Enpassant Capture
			t = (t & 7) | (f & 56);
			a = PAWN;
		}
		else if (a == ROOK && CASTLE) { //Revoke castling rights.
			flags &= crevoke[t];
		}
		xorBit(t, pieceb + a);
		xorBit(t, colorb + (c ^ 1));
		XORHASH(t, a, c ^ 1);
		count_a &= 0x3FF; //Reset Fifty Counter
		mat += c ? -pval[a] : +pval[a];
	}
	if (p == PAWN) {
		if (((f^t) & 8) == 0) flags |= f ^ 24; //Enpassant
		else if ((t & 56) == 0 || (t & 56) == 56) {
			xorBit(t, pieceb + PAWN);
			xorBit(t, pieceb + PROM(m));
			XORHASH(t, PAWN, c);
			XORHASH(t, PROM(m), c);
			mat += c ? pval[PAWN] - pval[PROM(m)] : -pval[PAWN] + pval[PROM(m)];
		}
		count_a &= 0x3FF; //Reset Fifty Counter
	}
	else if (p == KING) {
		if (kingpos[c] == f) kingpos[c] = t; else kingpos[c] = f;
		flags &= ~(320 << c); // Lose castling rights
		if (((f^t) & 3) == 2) { // Castle
			if (t == 6) { f = 7; t = 5; }
			else if (t == 2) { f = 0; t = 3; }
			else if (t == 62) { f = 63; t = 61; }
			else { f = 56; t = 59; }
			xorBit(f, colorb + c);
			xorBit(f, pieceb + ROOK);
			xorBit(t, colorb + c);
			xorBit(t, pieceb + ROOK);
			XORHASH(f, ROOK, c);
			XORHASH(t, ROOK, c);
		}
	}
	else if (p == ROOK && CASTLE) {
		flags &= crevoke[f];
	}
}

void doMove(Move m, int c) {
	mstack[COUNT] = count_a | (flags << 17) | (((u64)(mat + 0x4000)) << 27) | (((u64)m) << 42);
	move(m, c);
}

void undoMove(Move m, int c) {
	u64 u = mstack[COUNT - 1];
	move(m, c);
	count_a = u & 0x1FFFF;
	flags = (u >> 17L) & 0x3FF;
	mat = ((u >> 27L) & 0x7FFF) - 0x4000;
}
void redoMove(Move m, int c) {     // da ist noch ein fehler drin !!!!  !!!!!!!!!!!!!!!!!!
	u64 u = mstack[COUNT + 1];
	move(m, c);
	count_a = u & 0x1FFFF;
	flags = (u >> 17L) & 0x3FF;
	mat = ((u >> 27L) & 0x7FFF) - 0x4000;
}

void regMoves(Move m, u64 bt, int* mlist, int* mn, int cap) {
	while (bt) {
		int t = pullLsb(&bt);
		mlist[(*mn)++] = m | _TO(t) | (cap ? _CAP(identPiece(t)) : 0LL);
	}
}

void regMovesCaps(Move m, u64 bc, u64 bm, int* mlist, int* mn) {
	regMoves(m, bc, mlist, mn, 1);
	regMoves(m, bm, mlist, mn, 0);
}

void regPromotions(int f, int c, u64 bt, int* mlist, int* mn, int cap, int queen) {
	while (bt) {
		int t = pullLsb(&bt);
		Move m = f | _ONMV(c) | _PIECE(PAWN) | _TO(t) | (cap ? _CAP(identPiece(t)) : 0);
		if (queen) mlist[(*mn)++] = m | _PROM(QUEEN);
		mlist[(*mn)++] = m | _PROM(KNIGHT);
		mlist[(*mn)++] = m | _PROM(ROOK);
		mlist[(*mn)++] = m | _PROM(BISHOP);
	}
}

void regKings(Move m, u64 bt, int* mlist, int* mn, int c, int cap) {
	while (bt) {
		int t = pullLsb(&bt);
		if (battacked(t, c)) continue;
		mlist[(*mn)++] = m | _TO(t) | (cap ? _CAP(identPiece(t)) : 0LL);
	}
}

int generateCheckEsc(u64 ch, u64 apin, int c, int k, int *ml, int *mn) {
	u64 cc, fl;
	int d, bf = _bitcnt(ch);
	xorBit(k, colorb + c);
	regKings(PREMOVE(k, KING), KCAP(k, c), ml, mn, c, 1);
	regKings(PREMOVE(k, KING), KMOVE(k), ml, mn, c, 0);
	xorBit(k, colorb + c);
	if (bf > 1) return bf; //Doublecheck
	bf = getLsb(ch);

	cc = attacked(bf, c ^ 1) & apin;  //Can we capture the checker?
	while (cc) {
		int cf = pullLsb(&cc);
		int p = identPiece(cf);
		if (p == PAWN && RANK(cf, c ? 0x08 : 0x30))
			regPromotions(cf, c, ch, ml, mn, 1, 1);
		else
			regMovesCaps(PREMOVE(cf, p), ch, 0LL, ml, mn);
	}
	if (ENPASS && (ch & pieceb[PAWN])) { //Enpassant capture of attacking Pawn
		cc = PCAP(ENPASS, c ^ 1) & pieceb[PAWN] & apin;
		while (cc) {
			int cf = pullLsb(&cc);
			regMovesCaps(PREMOVE(cf, PAWN), BIT[ENPASS], 0LL, ml, mn);
		}
	}
	if (ch & (nmoves[k] | kmoves[k])) return 1; //We can't move anything between!

	d = getDir(bf, k);
	if (d & 8) fl = RMOVE1(bf) & RMOVE1(k);
	else if (d & 16) fl = RMOVE2(bf) & RMOVE2(k);
	else if (d & 32) fl = BMOVE3(bf) & BMOVE3(k);
	else fl = BMOVE4(bf) & BMOVE4(k);

	while (fl) {
		int f = pullLsb(&fl);
		cc = reach(f, c ^ 1) & apin;
		while (cc) {
			int cf = pullLsb(&cc);
			int p = identPiece(cf);
			regMovesCaps(PREMOVE(cf, p), 0LL, BIT[f], ml, mn);
		}
		bf = c ? f + 8 : f - 8;
		if (bf < 0 || bf > 63) continue;
		if (BIT[bf] & pieceb[PAWN] & colorb[c] & apin) {
			if (RANK(bf, c ? 0x08 : 0x30))
				regPromotions(bf, c, BIT[f], ml, mn, 0, 1);
			else
				regMovesCaps(PREMOVE(bf, PAWN), 0LL, BIT[f], ml, mn);
		}
		if (RANK(f, c ? 0x20 : 0x18) && (BOARD & BIT[bf]) == 0 && (BIT[c ? f + 16 : f - 16] & pieceb[PAWN] & colorb[c] & apin))
			regMovesCaps(PREMOVE(c ? f + 16 : f - 16, PAWN), 0LL, BIT[f], ml, mn);
	}
	return 1;
}

int generateNonCaps(u64 ch, int c, int f, u64 pin, int *ml, int *mn) {
	int t;
	u64 m, b, cb = colorb[c] & (~pin);

	regKings(PREMOVE(f, KING), KMOVE(f), ml, mn, c, 0);

	b = pieceb[PAWN] & cb;
	while (b) {
		f = pullLsb(&b);
		m = PMOVE(f, c);
		if (m && RANK(f, c ? 0x30 : 0x08)) m |= PMOVE(c ? f - 8 : f + 8, c);
		if (RANK(f, c ? 0x08 : 0x30)) {
			u64 a = PCAP(f, c);
			regPromotions(f, c, m, ml, mn, 0, 0);
			if (a) regPromotions(f, c, a, ml, mn, 1, 0);
		}
		else {
			regMoves(PREMOVE(f, PAWN), m, ml, mn, 0);
		}
	}

	b = pin & pieceb[PAWN];
	while (b) {
		f = pullLsb(&b);
		t = getDir(f, kingpos[c]);
		if (t & 8) continue;
		m = 0LL;
		if (t & 16) {
			m = PMOVE(f, c);
			if (m && RANK(f, c ? 0x30 : 0x08)) m |= PMOVE(c ? f - 8 : f + 8, c);
		}
		if (RANK(f, c ? 0x08 : 0x30)) {
			u64 a = (t & 32) ? PCA3(f, c) : ((t & 64) ? PCA4(f, c) : 0LL);
			regPromotions(f, c, m, ml, mn, 0, 0);
			if (a) regPromotions(f, c, a, ml, mn, 1, 0);
		}
		else {
			regMoves(PREMOVE(f, PAWN), m, ml, mn, 0);
		}
	}

	b = pieceb[KNIGHT] & cb;
	while (b) {
		f = pullLsb(&b);
		regMoves(PREMOVE(f, KNIGHT), NMOVE(f), ml, mn, 0);
	}

	b = pieceb[ROOK] & cb;
	while (b) {
		f = pullLsb(&b);
		regMoves(PREMOVE(f, ROOK), RMOVE(f), ml, mn, 0);
		if (CASTLE && !ch) {
			if (c) {
				if ((flags & 128) && (f == 63) && (RMOVE1(63) & BIT[61]))
					if (!DUALATT(61, 62, c)) regMoves(PREMOVE(60, KING), BIT[62], ml, mn, 0);
				if ((flags & 512) && (f == 56) && (RMOVE1(56) & BIT[59]))
					if (!DUALATT(59, 58, c)) regMoves(PREMOVE(60, KING), BIT[58], ml, mn, 0);
			}
			else {
				if ((flags & 64) && (f == 7) && (RMOVE1(7) & BIT[5]))
					if (!DUALATT(5, 6, c)) regMoves(PREMOVE(4, KING), BIT[6], ml, mn, 0);
				if ((flags & 256) && (f == 0) && (RMOVE1(0) & BIT[3]))
					if (!DUALATT(3, 2, c)) regMoves(PREMOVE(4, KING), BIT[2], ml, mn, 0);
			}
		}
	}

	b = pieceb[BISHOP] & cb;
	while (b) {
		f = pullLsb(&b);
		regMoves(PREMOVE(f, BISHOP), BMOVE(f), ml, mn, 0);
	}

	b = pieceb[QUEEN] & cb;
	while (b) {
		f = pullLsb(&b);
		regMoves(PREMOVE(f, QUEEN), RMOVE(f) | BMOVE(f), ml, mn, 0);
	}

	b = pin & (pieceb[ROOK] | pieceb[BISHOP] | pieceb[QUEEN]);
	while (b) {
		int p;
		f = pullLsb(&b);
		p = identPiece(f);
		t = p | getDir(f, kingpos[c]);
		if ((t & 10) == 10) regMoves(PREMOVE(f, p), RMOVE1(f), ml, mn, 0);
		if ((t & 18) == 18) regMoves(PREMOVE(f, p), RMOVE2(f), ml, mn, 0);
		if ((t & 33) == 33) regMoves(PREMOVE(f, p), BMOVE3(f), ml, mn, 0);
		if ((t & 65) == 65) regMoves(PREMOVE(f, p), BMOVE4(f), ml, mn, 0);
	}
	return 0;
}

int generateCaps(u64 ch, int c, int f, u64 pin, int *ml, int *mn) {
	int t;
	u64 m, b, a, cb = colorb[c] & (~pin);

	regKings(PREMOVE(f, KING), KCAP(f, c), ml, mn, c, 1);

	b = pieceb[PAWN] & cb;
	while (b) {
		f = pullLsb(&b);
		a = PCAP(f, c);
		if (RANK(f, c ? 0x08 : 0x30)) {
			regMovesCaps(PREMOVE(f, PAWN) | _PROM(QUEEN), a, PMOVE(f, c), ml, mn);
		}
		else {
			if (ENPASS && (BIT[ENPASS] & pcaps[(f) | ((c) << 6)])) {
				u64 hh;
				int clbd = ENPASS ^ 8;
				xorBit(clbd, colorb + (c ^ 1));
				hh = ROCC1(f);
				if (!(hh & BIT[kingpos[c]]) || !(hh & colorb[c ^ 1] & RQU)) {
					a = a | BIT[ENPASS];
				}
				xorBit(clbd, colorb + (c ^ 1));
			}
			regMoves(PREMOVE(f, PAWN), a, ml, mn, 1);
		}
	}

	b = pin & pieceb[PAWN];
	while (b) {
		f = pullLsb(&b);
		t = getDir(f, kingpos[c]);
		if (t & 8) continue;
		m = a = 0LL;
		if (t & 16) {
			m = PMOVE(f, c);
		}
		else if (t & 32) {
			a = PCA3(f, c);
		}
		else {
			a = PCA4(f, c);
		}
		if (RANK(f, c ? 0x08 : 0x30)) {
			regMovesCaps(PREMOVE(f, PAWN) | _PROM(QUEEN), a, m, ml, mn);
		}
		else {
			regMoves(PREMOVE(f, PAWN), a, ml, mn, 1);
		}
	}

	b = pieceb[KNIGHT] & cb;
	while (b) {
		f = pullLsb(&b);
		regMoves(PREMOVE(f, KNIGHT), NCAP(f, c), ml, mn, 1);
	}

	b = pieceb[BISHOP] & cb;
	while (b) {
		f = pullLsb(&b);
		regMoves(PREMOVE(f, BISHOP), BCAP(f, c), ml, mn, 1);
	}

	b = pieceb[ROOK] & cb;
	while (b) {
		f = pullLsb(&b);
		regMoves(PREMOVE(f, ROOK), RCAP(f, c), ml, mn, 1);
	}

	b = pieceb[QUEEN] & cb;
	while (b) {
		f = pullLsb(&b);
		regMoves(PREMOVE(f, QUEEN), RCAP(f, c) | BCAP(f, c), ml, mn, 1);
	}

	b = pin & (pieceb[ROOK] | pieceb[BISHOP] | pieceb[QUEEN]);
	while (b) {
		int p;
		f = pullLsb(&b);
		p = identPiece(f);
		t = p | getDir(f, kingpos[c]);
		if ((t & 10) == 10) regMoves(PREMOVE(f, p), RCAP1(f, c), ml, mn, 1);
		if ((t & 18) == 18) regMoves(PREMOVE(f, p), RCAP2(f, c), ml, mn, 1);
		if ((t & 33) == 33) regMoves(PREMOVE(f, p), BCAP3(f, c), ml, mn, 1);
		if ((t & 65) == 65) regMoves(PREMOVE(f, p), BCAP4(f, c), ml, mn, 1);
	}
	return 0;
}

#define GENERATE(c) generate(attacked(kingpos[c], c), c, 0, 1, 1)
int generate(u64 ch, int c, int ply, int cap, int noncap) {
	int f = kingpos[c];
	u64 pin = pinnedPieces(f, c ^ 1);
	int *mn = movenum + ply;
	int *ml = movelist + (ply << 8);
	*mn = 0;
	if (ch) return generateCheckEsc(ch, ~pin, c, f, ml, mn);
	if (cap) generateCaps(ch, c, f, pin, ml, mn);
	if (noncap) generateNonCaps(ch, c, f, pin, ml, mn);
	return *mn;
}

int swap(Move m) //SEE Stuff
{
	int s_list[32];
	int f = FROM(m), t = TO(m), onmv = ONMV(m);
	int a_piece = pval[CAP(m)], piece = PIECE(m), c = onmv ^ 1, nc = 1;
	u64 attacks, temp = 0, colstore0 = colorb[0], colstore1 = colorb[1];

	attacks = attacked(t, 0) | attacked(t, 1);
	s_list[0] = a_piece;
	a_piece = pval[piece];
	colorb[onmv] ^= BIT[f];
	if (piece & 4 || piece == 1) {
		int d = getDir(f, t);
		if (d == 32 || d == 64) attacks |= BOCC(t) & BQU;
		if (d == 8 || d == 16) attacks |= ROCC(t) & RQU;
	}
	attacks &= BOARD;

	while (attacks) {
		if ((temp = pieceb[PAWN] & colorb[c] & attacks)) piece = PAWN;
		else if ((temp = pieceb[KNIGHT] & colorb[c] & attacks)) piece = KNIGHT;
		else if ((temp = pieceb[BISHOP] & colorb[c] & attacks)) piece = BISHOP;
		else if ((temp = pieceb[ROOK] & colorb[c] & attacks)) piece = ROOK;
		else if ((temp = pieceb[QUEEN] & colorb[c] & attacks)) piece = QUEEN;
		else if ((temp = pieceb[KING] & colorb[c] & attacks)) piece = KING;
		else break;

		temp &= -(long long)temp;
		colorb[c] ^= temp;
		if (piece & 4 || piece == 1) {
			if (piece & 1) attacks |= BOCC(t) & BQU;
			if (piece & 2) attacks |= ROCC(t) & RQU;
		}
		attacks &= BOARD;

		s_list[nc] = -s_list[nc - 1] + a_piece;
		a_piece = pval[piece];
		nc++;
		c ^= 1;
	}

	while (--nc)
		if (s_list[nc] > -s_list[nc - 1])
			s_list[nc - 1] = -s_list[nc];

	colorb[0] = colstore0;
	colorb[1] = colstore1;
	return s_list[0];
}

/* In quiesce the moves are ordered just for the value of the captured piece */
Move qpick(Move* ml, int mn, int s) {
	Move m;
	int i, t, pi = 0, vmax = -9999;
	for (i = s; i < mn; i++) {
		m = ml[i];
		t = pval[CAP(m)];
		if (t > vmax) {
			vmax = t;
			pi = i;
		}
	}
	m = ml[pi];
	if (pi != s) ml[pi] = ml[s];
	return m;
}

Move killer[128];
int history[0x1000];
/* In normal search some basic move ordering heuristics are used */
Move spick(Move* ml, int mn, int s, int ply) {
	Move m;
	int i, pi = 0, vmax = -9999;
	for (i = s; i < mn; i++) {
		m = ml[i];
		if (m == killer[ply]) {
			pi = i;
			break;
		}
		if (vmax < history[m & 0xFFF]) {
			vmax = history[m & 0xFFF];
			pi = i;
		}
	}
	m = ml[pi];
	if (pi != s) ml[pi] = ml[s];
	return m;
}

/* The evulation for Color c. It's almost only mobility stuff. Pinned pieces are still awarded for limiting opposite's king */
int evalc(int c, int* sf) {
	int t, f;
	int mn = 0, katt = 0;
	int oc = c ^ 1;
	u64 ocb = colorb[oc];
	u64 m, b, a, cb;
	u64 kn = kmoves[kingpos[oc]];
	u64 pin = pinnedPieces(kingpos[c], oc);

	b = pieceb[PAWN] & colorb[c];
	while (b) {
		int ppos = 0;
		f = pullLsb(&b);
		t = f + (c << 6);
		ppos = pawnprg[t];
		m = PMOVE(f, c);
		a = POCC(f, c);
		if (a & kn) katt += _bitcnt(a & kn) << 4;
		if (BIT[f] & pin) {
			if (!(getDir(f, kingpos[c]) & 16)) m = 0;
		}
		else {
			ppos += _bitcnt(a & pieceb[PAWN] & colorb[c]) << 2;
		}
		if (m) ppos += 8; else ppos -= 8;
		/* The only non-mobility eval is the detection of free pawns/hanging pawns */
		if (!(pawnfile[t] & pieceb[PAWN] & ocb)) { //Free file?
			if (!(pawnfree[t] & pieceb[PAWN] & ocb)) ppos *= 2; //Free run?
			if (!(pawnhelp[t] & pieceb[PAWN] & colorb[c])) ppos -= 33; //Hanging backpawn?
		}

		mn += ppos;
	}

	cb = colorb[c] & (~pin);
	b = pieceb[KNIGHT] & cb;
	while (b) {
		*sf += 1;
		f = pullLsb(&b);
		a = nmoves[f];
		if (a & kn) katt += _bitcnt(a & kn) << 4;
		mn += nmobil[f];
	}

	b = pieceb[KNIGHT] & pin;
	while (b) {
		*sf += 1;
		f = pullLsb(&b);
		a = nmoves[f];
		if (a & kn) katt += _bitcnt(a & kn) << 4;
	}

	xorBit(kingpos[oc], colorb + oc); //Opposite King doesn't block mobility at all
	b = pieceb[QUEEN] & cb;
	while (b) {
		*sf += 4;
		f = pullLsb(&b);
		a = RATT1(f) | RATT2(f) | BATT3(f) | BATT4(f);
		if (a & kn) katt += _bitcnt(a & kn) << 4;
		mn += bitcnt(a);
	}

	colorb[oc] ^= RQU & ocb; //Opposite Queen & Rook doesn't block mobility for bishop
	b = pieceb[BISHOP] & cb;
	while (b) {
		*sf += 1;
		f = pullLsb(&b);
		a = BATT3(f) | BATT4(f);
		if (a & kn) katt += _bitcnt(a & kn) << 4;
		mn += bitcnt(a) << 3;
	}

	colorb[oc] ^= pieceb[ROOK] & ocb; //Opposite Queen doesn't block mobility for rook.
	colorb[c] ^= pieceb[ROOK] & cb; //Own non-pinned Rook doesn't block mobility for rook.
	b = pieceb[ROOK] & cb;
	while (b) {
		*sf += 2;
		f = pullLsb(&b);
		a = RATT1(f) | RATT2(f);
		if (a & kn) katt += _bitcnt(a & kn) << 4;
		mn += bitcnt(a) << 2;
	}

	colorb[c] ^= pieceb[ROOK] & cb; // Back
	b = pin & (pieceb[ROOK] | pieceb[BISHOP] | pieceb[QUEEN]);
	while (b) {
		int p;
		f = pullLsb(&b);
		p = identPiece(f);
		if (p == BISHOP) {
			*sf += 1;
			a = BATT3(f) | BATT4(f);
			if (a & kn) katt += _bitcnt(a & kn) << 4;
		}
		else if (p == ROOK) {
			*sf += 2;
			a = RATT1(f) | RATT2(f);
			if (a & kn) katt += _bitcnt(a & kn) << 4;
		}
		else {
			*sf += 4;
			a = RATT1(f) | RATT2(f) | BATT3(f) | BATT4(f);
			if (a & kn) katt += _bitcnt(a & kn) << 4;
		}
		t = p | getDir(f, kingpos[c]);
		if ((t & 10) == 10) mn += _bitcnt(RATT1(f));
		if ((t & 18) == 18) mn += _bitcnt(RATT2(f));
		if ((t & 33) == 33) mn += _bitcnt(BATT3(f));
		if ((t & 65) == 65) mn += _bitcnt(BATT4(f));
	}

	colorb[oc] ^= pieceb[QUEEN] & ocb; //Back
	xorBit(kingpos[oc], colorb + oc); //Back
	if (*sf == 1 && !(pieceb[PAWN] & colorb[c])) mn = -200; //No mating material
	if (*sf < 7) katt = katt * (*sf) / 7; //Reduce the bonus for attacking king squares
	if (*sf < 2) *sf = 2;
	return mn + katt;
}

int eval1 = 0;
int eval(int c) {
	int sf0 = 0, sf1 = 0;
	int ev0 = evalc(0, &sf0);
	int ev1 = evalc(1, &sf1);
	eval1++;

	if (sf1 < 6) ev0 += kmobil[kingpos[0]] * (6 - sf1);
	if (sf0 < 6) ev1 += kmobil[kingpos[1]] * (6 - sf0);

	return (c ? (ev1 - ev0) : (ev0 - ev1));
}

u64 nodes;
u64 qnodes;
int quiesce(u64 ch, int c, int ply, int alpha, int beta) {             // Suchbäume  Stilllegen  
	int i, w, best = -32000, poff;
	int cmat = c ? -mat : mat;

	if (ply == 63) return eval(c) + cmat;
	if (!ch) do {
		if (cmat - 200 >= beta) return beta;
		if (cmat + 200 <= alpha) break;
		best = eval(c) + cmat;
		if (best > alpha) {
			alpha = best;
			if (best >= beta) return beta;
		}
	} while (0);

	generate(ch, c, ply, 1, 0);
	if (ch && movenum[ply] == 0) return -32000 + ply;
	poff = ply << 8;

	for (i = 0; i < movenum[ply]; i++) {
		Move m = qpick(movelist + poff, movenum[ply], i);
		if (!ch && !PROM(m) && pval[PIECE(m)] > pval[CAP(m)] && swap(m) < 0) continue;

		doMove(m, c);
		qnodes++;

		w = -quiesce(attacked(kingpos[c ^ 1], c ^ 1), c ^ 1, ply + 1, -beta, -alpha);

		undoMove(m, c);

		if (w > best) {
			best = w;
			if (w > alpha) {
				alpha = w;
				if (w >= beta) return beta;
			}
		}
	}
	return best > -32000 ? best : eval(c) + cmat;
}

int retPVMove(int c, int ply) {
	int i;
	GENERATE(c);
	for (i = 0; i < movenum[0]; i++) {
		Move m = movelist[i];
		if (m == pv[0][ply]) return m;
	}
	return 0;
}

int inputSearch() {
	int ex;
	if (!pondering) return 1;
	fgets(irbuf, 255, stdin);
	ex = protV2(irbuf);
	if (!automatik || !ponder || ex || engine != onmove) pondering = 0; //     !! aufpassen ob automatik= ok 
	if (!ex) irbuf[0] = 0;
	if (ex != -1) return !pondering;
	ex = parseMove(irbuf, ONMV(pon), pon);
	if (!ex || ex == -1) return 1;  // wenn eingabe falsch ex = -1
	irbuf[0] = 0;
	return (pon = 0);
}

const int nullvar[] = { 13, 43, 149, 519, 1809, 6311, 22027 };
static int nullvariance(int delta) {
	int r = 0;
	if (delta >= 4) for (r = 1; r <= 7; r++) if (delta < nullvar[r - 1]) break;
	return r;
}

#define HASHP (hashb ^ hashxor[flags | 1024 | c << 11])
#define HASHB ((hashb ^ hashxor[flags | 1024]) ^ hashxor[c | d << 1 | 2048])
int search(u64 ch, int c, int d, int ply, int alpha, int beta, int pvnode, int null) {
	int i, j, n, w, poff, asave, first, best;
	Move hmove;
	u64 hb, hp, he;

	pvlength[ply] = ply;
	if (ply == 63) return eval(c) + (c ? -mat : mat);
	if ((++nodes & CNODES) == 0) {
		u64 consumed = getTime() - starttime;
		if (!pondering && (consumed > maxtime || (consumed > searchtime && !noabort))) sabort = 1;
	//	if (bioskey()) { automatik = 0; sabort = inputSearch(); }  //  Abbruch wegen Konsole eingabe bzw. weiter wenn ok 
	}
	if (sabort) return 0;

	hp = HASHP;
	if (ply && isDraw(hp, 1)) return 0;

	if (d == 0) return quiesce(ch, c, ply, alpha, beta);
	hstack[COUNT] = hp;

	hb = HASHB;
	he = hashDB[hb & HMASKB];              // Hash vergleich 
	if (!((he^hb) & HINVB)) {
		w = (u32)LOW16(he) - 32768;
		if (he & 0x10000) {
			null = 0;
			if (w <= alpha) return alpha;
		}
		else {
			if (w >= beta) return beta;
		}
	}
	else w = c ? -mat : mat;

	//Null Move    versucht einen Zug zu spielen ohne gegner Zug um Suchbäume zu reduzieren
	if (!pvnode && !ch && null && d > 1 && bitcnt(colorb[c] & (~pieceb[PAWN]) & (~pinnedPieces(kingpos[c], c ^ 1))) > 2) {
		int flagstore = flags;
		int R = (10 + d + nullvariance(w - beta)) / 4;
		if (R > d) R = d;
		flags &= 960;
		count_a += 0x401;
		w = -search(0LL, c ^ 1, d - R, ply + 1, -beta, -alpha, 0, 0);
		flags = flagstore;
		count_a -= 0x401;
		if (!sabort && w >= beta) {
			hashDB[hb & HMASKB] = (hb & HINVB) | (w + 32768);
			return beta;
		}
	}

	hmove = 0;
	if (ply) {
		he = hashDP[hp & HMASKP];
		if (!((he^hp) & HINVP)) hmove = (Move)(he & HMASKP);

		if (d >= 4 && hmove == 0) { // Simple version of Internal Iterative Deepening
			w = search(ch, c, d - 3, ply, alpha, beta, pvnode, 0);
			he = hashDP[hp & HMASKP];
			if (!((he^hp) & HINVP)) hmove = (Move)(he & HMASKP);
		}
	}
	else {
		hmove = retPVMove(c, ply);
	}

	poff = ply << 8;
	best = pvnode ? alpha : -32001;
	asave = alpha;
	first = 1;
	for (n = 1; n <= (ch ? 2 : 3); n++) {
		if (n == 1) {
			if (hmove == 0) continue;
			movenum[ply] = 1;
		}
		else if (n == 2) {
			generate(ch, c, ply, 1, 0);
		}
		else {
			generate(ch, c, ply, 0, 1);
		}
		for (i = 0; i < movenum[ply]; i++) {
			Move m;
			u64 nch;
			int ext = 0;
			if (n == 1) {
				m = hmove;
			}
			else {
				if (n == 2) m = qpick(movelist + poff, movenum[ply], i);
				else m = spick(movelist + poff, movenum[ply], i, ply);
				if (m == hmove) continue;
			}

			doMove(m, c);
			nch = attacked(kingpos[c ^ 1], c ^ 1);
			if (nch) ext++; // Check Extension
			else if (d >= 3 && n == 3 && !pvnode) { //LMR
				if (m == killer[ply]); //Don't reduce killers
				else if (PIECE(m) == PAWN && !(pawnfree[TO(m) + (c << 6)] & pieceb[PAWN] & colorb[c ^ 1])); //Don't reduce free pawns
				else ext--;
			}

			if (first && pvnode) {
				w = -search(nch, c ^ 1, d - 1 + ext, ply + 1, -beta, -alpha, 1, 1);
				if (!ply) noabort = (iter > 1 && w < value[iter - 1] - 40) ? 1 : 0;
			}
			else {
				w = -search(nch, c ^ 1, d - 1 + ext, ply + 1, -alpha - 1, -alpha, 0, 1);
				if (w > alpha && ext < 0) w = -search(nch, c ^ 1, d - 1, ply + 1, -alpha - 1, -alpha, 0, 1);
				if (w > alpha && w < beta && pvnode) w = -search(nch, c ^ 1, d - 1 + ext, ply + 1, -beta, -alpha, 1, 1);
			}
			undoMove(m, c);

			if (!sabort && w > best) {
				if (w > alpha) {
					hashDP[hp & HMASKP] = (hp & HINVP) | m;
					alpha = w;
				}
				if (w >= beta) {
					if (CAP(m) == 0) {
						killer[ply] = m;
						history[m & 0xFFF]++;
					}
					hashDB[hb & HMASKB] = (hb & HINVB) | (w + 32768);
					return beta;
				}
				if (pvnode && w >= alpha) {
					pv[ply][ply] = m;
					for (j = ply + 1; j < pvlength[ply + 1]; j++) pv[ply][j] = pv[ply + 1][j];
					pvlength[ply] = pvlength[ply + 1];
					if (!ply && iter > 1 && w > value[iter - 1] - 20) noabort = 0;
					if (w == 31999 - ply) return w;
				}
				best = w;
			}
			first = 0;
		}
	}
	if (first) return ch ? -32000 + ply : 0;
	if (pvnode) {
		if (!sabort && asave == alpha) hashDB[hb & HMASKB] = (hb & HINVB) | 0x10000 | (asave + 32768);
	}
	else {
		if (!sabort && best < beta) hashDB[hb & HMASKB] = (hb & HINVB) | 0x10000 | (best + 32768);
	}
	return alpha;
}

int execMove(Move m) {
	int i, c;
	doMove(m, onmove);
	onmove ^= 1;
	c = onmove;
	if (book) for (i = 0; i < BKSIZE; i++) {
		if (bkflag[i] < 2 && (bkmove[i * 32 + COUNT - 1] != m || bkmove[i * 32 + COUNT] == 0)) {
			bkcount[bkflag[i]]--;
			bkflag[i] = 2;
		}
	}
	hstack[COUNT] = HASHP;
	for (i = 0; i < 127; i++) killer[i] = killer[i + 1];
	for (i = 0; i < 0x1000; i++) history[i] = 0;
	i = GENERATE(c);
	if (pondering) return (movenum[0] == 0);

	if (movenum[0] == 0) {
	//	setConsolColor(12, colorBack);
		automatik = 0;
		engine = -1;            // wichtig!!!!!
		if (!i) {
			draw = true;
			return 4;
		}
		else {
			c ? whiteMates = true : blackMates = true; 
			return 5 + c;
		}
	}
	switch (isDraw(HASHP, 2)) {
	case 1: drawCauseMoveRepeat = true; return 1;
	case 2: drawBecause50Moves = true; return 2;
	case 3:unsuficientMatereals = true; return 3;

	}
	return 0;
}

#define ISRANK(c) (c >= '1' && c <= '8')
#define ISFILE(c) (c >= 'a' && c <= 'h')
int ismove(Move m, int to, int from, int piece, int prom, int h) {
	if (TO(m) != to) return 0;
	if (from < 0 && PIECE(m) != piece) return 0;
	if (from >= 0 && FROM(m) != from) return 0;
	if (ISFILE(h) && (FROM(m) & 7) != h - 'a') return 0;
	if (ISRANK(h) && (FROM(m) & 56) != 8 * (h - '1')) return 0;
	if (prom && PROM(m) != prom) return 0;
	return 1;
}

int parseMove(char *s, int c, Move p) {          // Eingabe analysieren
	int i, to, from = -1, piece = PAWN, prom = 0;
	char h = 0, c1, c2;
	if (!strncmp(s, "O-O-O", 5)) strcpy(s, c ? "Kc8" : "Kc1");     // Rocharde
	else if (!strncmp(s, "O-O", 3)) strcpy(s, c ? "Kg8" : "Kg1");
	if (s[0] >= 'A' && s[0] <= 'Z') if ((piece = _getpiece(*s++, &i)) < 1) return -1;
	if (s[0] == 'x') s++;
	if (ISRANK(s[0])) { h = *s++; if (s[0] == 'x') s++; }
	if (!ISFILE(s[0])) return -1;
	c1 = *s++;
	if (s[0] == 'x') s++;
	if (ISFILE(s[0])) { h = c1; c1 = *s++; }
	c2 = *s++;
	if (!ISRANK(c2)) return -1;
	if (*s >= '0') {
		if (*s == '=') prom = _getpiece(s[1], &i);
		else if (*s == '+');
		else { // Algebraic Notation
			from = c1 - 'a' + 8 * (c2 - '1');
			c1 = *s++; c2 = *s++;
			if (!ISFILE(c1) || !ISRANK(c2)) return -1;
			prom = _getpiece(*s, &i);
		}
	}
	to = c1 - 'a' + 8 * (c2 - '1');
	if (p) {
		if (ismove(p, to, from, piece, prom, h)) return p;
		return 0;
	}
	GENERATE(c);
	for (i = 0; i < movenum[0]; i++) if (ismove(movelist[i], to, from, piece, prom, h)) return movelist[i];
	return 0;
}

int parseMoveNExec(char *s, int c, Move *m) {      // Zug überprüfung 
	*m = parseMove(s, c, 0);
	if (*m == -1) {
	//	setConsolColor(12, colorBack);
	//	printf("UNKNOWN COMMAND: %s\n", s);
	//	setConsolColor(0, colorBack);
	}
	else if (*m == 0) {
	//	setConsolColor(12, colorBack);
	//	fprintf(stderr, "Ungueltiger Zug: %s\n", s);
	//	setConsolColor(0, colorBack);
	}
	else return execMove(*m);
	return -1;
}

void undo() {
	if (COUNT > 0)
	{
		int cnt = COUNT - 1;
		onmove ^= 1;
		undoMove((mstack[cnt] >> 42L), onmove);
	}
}

void redo() {
	int cnt = COUNT + 1;
	onmove ^= 1;
	redoMove((mstack[cnt] >> 42L), onmove);
}

int ttime = 30000;
int mps = 0;
int base = 5;
int inc = 0;
// int post = 1;              //////////////////////////// !!!!!!!!!!!!!!!!!!!!
int st = 0;  // Search Time in Sec.



int calc(int sd, int tm) {

	int i, j, t1 = 0, m2go = 32;
	u64 ch = attacked(kingpos[onmove], onmove);
	eval1 = sabort = iter = value[0] = 0;
	qnodes = nodes = 0LL;
	if (mps > 0) m2go = 1 + mps - ((COUNT / 2) % mps);

	searchtime = (tm * 10LL) / m2go + inc * 1000LL;
	maxtime = inc ? tm * 3LL : tm * 2LL;
	if (st > 0) maxtime = searchtime = st * 1000LL;

	starttime = getTime();
	srand((u32)starttime);
	if (book) {
		if (!bkcount[onmove]) book = 0;
		else {
			j = rand() % bkcount[onmove];      // Zufallsfaktor 
			for (i = 0; i < BKSIZE; i++) {
				if (bkflag[i] == onmove && j == t1++) { pv[0][0] = bkmove[i * 32 + COUNT]; break; }
			}
		}
	}
	if (!book) for (iter = 1; iter <= sd; iter++) {	
		noabort = 0;
		value[iter] = search(ch, onmove, iter, 0, -32000, 32000, 1, 0);
		t1 = (int)(getTime() - starttime);
		if (sabort && !pvlength[0] && iter--) break;
	//	if (post && pvlength[0] > 0) {
	//		printf("%2d %5d %6d %9lu  ", iter, value[iter], t1 / 10, (u32)(nodes + qnodes));
	//		displaypv(); printf("\n");
	//	}
		if (!pondering && (iter >= 32000 - value[iter] || (u32)t1 > searchtime / 2)) break;
		if (sabort) break;
	}
	pondering = 0;
	if (pon) {
		undo();
		pon = 0;
		return engine != onmove;
	}
//	if (value[iter > sd ? sd : iter] < 0)setConsolColor(4, colorBack);
//	else setConsolColor(2, colorBack);
//	if (post) printf("\nParnoms: %d Nodes: %lu QNodes: %lu Evals: %d cs: %d knps: %lu\n", value[iter > sd ? sd : iter], (u32)nodes, (u32)qnodes, eval1, t1 / 10, (u32)(nodes + qnodes) / (t1 + 1));
//	printf("ZUG == "); displaym(pv[0][0]); printf("\n");
//	if (post) 




	return execMove(pv[0][0]);
}

int doponder(int c) {
	pon = retPVMove(c, 1);
	if (pon) {
		pondering = 1;
		if (execMove(pon)) {
			pondering = 0;
			undo();
			pon = 0;
		}
	}
	return pondering ? 0 : -1;
}


u64 perft(int c, int d, int div) {     // Performancetest zählt alle Legalmoves und terminalnodes
	int i, ply = 63 - d, poff = ply << 8;
	u64 n, cnt = 0LL;

	generate(attacked(kingpos[c], c), c, ply, 1, 1);
	if (d == 1) return (u64)movenum[ply];
	for (i = 0; i < movenum[ply]; i++) {
		Move m = movelist[poff + i];
		doMove(m, c);
		cnt += n = perft(c ^ 1, d - 1, 0);
	//	if (div) { displaym(m); printf(" %llu\n ", n); }
		undoMove(m, c);
	}
	return cnt;
}


int protV2(char* buf) {
	if (!strncmp(buf, "xboard", 6));
	else if (!strncmp(buf, "quit", 4)) return -2;
	else if (!strncmp(buf, "q", 1)) return -2;
	else if (!strncmp(buf, "new", 3)) return -3;
	else if (!strncmp(buf, "remove", 6)) return -4;
	else if (!strncmp(buf, "force", 5)) engine = -1;
	else if (!strncmp(buf, "go", 2)) engine = pondering ? onmove ^ 1 : onmove;
	else if (!strncmp(buf, "setboard", 8)) _parse_fen(buf + 9);
	else if (!strncmp(buf, "undo", 4)) { undo(); engine = -1; }
	else if (!strncmp(buf, "redo", 4)) { redo(); engine = -1; }
	else if (!strncmp(buf, "easy", 4)) ponder = 0;
	else if (!strncmp(buf, "hard", 4)) ponder = 1;
	else if (!strncmp(buf, "sd", 2)) sscanf(buf + 3, "%d", &sd);
	else if (!strncmp(buf, "time", 4)) sscanf(buf + 5, "%d", &ttime);
	else if (!strncmp(buf, "level", 4)) sscanf(buf + 6, "%d %d %d", &mps, &base, &inc);
//	else if (!strncmp(buf, "post", 4)) post = 1;
//	else if (!strncmp(buf, "nopost", 6)) post = 0;
	else if (!strncmp(buf, "st", 2)) sscanf(buf + 3, "%d", &st);
	else if (!strncmp(buf, "hint", 4)) hint = 1;
	else if (!strncmp(buf, "perft", 5)) { int i; for (i = 1; i <= sd; i++) printf("Depth: %d Nodes: %llu\n", i, perft(onmove, i, 0)); }
	else if (!strncmp(buf, "divide", 5)) perft(onmove, sd, 1);
	else if (!strncmp(buf, "turn", 4))  turnB ^= 1; // Konsole Schachbrett umdrehen
	else if (!strncmp(buf, "auto", 4)) automatik = 1;
	else if (!strncmp(buf, "save", 4)) { saveMstack("stackst.txt"); saveStellung("Stellung.txt"); }
	else if (!strncmp(buf, "load", 4)) { loadMstack("stackst.txt"); loadStellung("Stellung.txt"); engine = -1; }
	
	else  return -1;
	return 0;
}

int input(int c) {
	Move m;
	int ex;
	char buf[256];
	if (irbuf[0]) strcpy(buf, irbuf);
	else if (automatik == 1) engine = pondering ? onmove ^ 1 : onmove;
	else fgets(buf, 255, stdin);
	irbuf[0] = 0;
	ex = protV2(buf);
	if (ex == -1) return parseMoveNExec(buf, c, &m);
	return ex;
}

void startResetEngine() {
	int i = -1;
	setbuf(stdout, NULL);
	setbuf(stdin, NULL);
	signal(SIGINT, SIG_IGN);
	for (i = 0; i < 0x10000; i++) LSB[i] = _slow_lsb(i);
	for (i = 0; i < 0x10000; i++) BITC[i] = _bitcnt(i);
	for (i = 0; i < 4096; i++) hashxor[i] = _rand_64();
	for (i = 0; i < HSIZEB; i++) hashDB[i] = 0LL;
	for (i = 0; i < HSIZEP; i++) hashDP[i] = 0LL;
	for (i = 0; i < 64; i++) BIT[i] = 1LL << i;
	for (i = 0; i < 128; i++) pmoves[i] = pawnfree[i] = pawnfile[i] = pawnhelp[i] = 0LL;
	for (i = 0; i < 384; i++) pcaps[i] = 0LL;
	for (i = 0; i < 64; i++) bmask45[i] = _bishop45(i, 0LL, 0) | BIT[i];
	for (i = 0; i < 64; i++) bmask135[i] = _bishop135(i, 0LL, 0) | BIT[i];
	for (i = 0; i < 64; i++) crevoke[i] = 0x3FF;
	for (i = 0; i < 64; i++) kmoves[i] = nmoves[i] = 0LL;
	crevoke[7] ^= BIT[6];
	crevoke[63] ^= BIT[7];
	crevoke[0] ^= BIT[8];
	crevoke[56] ^= BIT[9];

	_init_rays(rays, _rook0, key000);
	_init_rays(rays + 0x2000, _rook90, key090);
	_init_rays(rays + 0x4000, _bishop45, key045);
	_init_rays(rays + 0x6000, _bishop135, key135);
	_init_shorts(nmoves, _knight);
	_init_shorts(kmoves, _king);
	_init_pawns(pmoves, pcaps, pawnfree, pawnfile, pawnhelp, 0);
	_init_pawns(pmoves + 64, pcaps + 64, pawnfree + 64, pawnfile + 64, pawnhelp + 64, 1);
	_readbook("olibook.pgn");
//	loadStellung("letzteStellung.txt");
//	loadMstack("stack.txt");
	engine = -1;

	for (i = 0; i < 64; i++) nmobil[i] = (bitcnt(nmoves[i]) - 1) * 6;
	for (i = 0; i < 64; i++) kmobil[i] = (bitcnt(nmoves[i]) / 2) * 2;
	
	irbuf[0] = 0;
}
int ex = -1;

void goFuckEngine() {
	saveValues();
	for (;;) {
		
		if (engine == onmove) {
			ex = calc(sd, ttime);
			
		}
		else if (ex == 0 && ponder && engine != -1 && !book) {
			ex = doponder(onmove);
			saveValues();
			break;
		}

		if (!ponder || book || engine == -1 || ex != 0) {
			//	showBoard();

		//	setConsolColor(0, colorBack);
			ex = input(onmove);
			irbuf[0] = 0;
			saveValues();
			break;
		};
		if (ex > 0) { engine = -1; automatik = 0; };
		if (ex == -2) {
			saveMstack("stack.txt");
			saveStellung("letzteStellung.txt");
			saveValues();
			break;
		}
		if (ex == -3) { _readbook("olibook.pgn"); }
		if (ex == -4) { undo(); undo(); }
	}

}

