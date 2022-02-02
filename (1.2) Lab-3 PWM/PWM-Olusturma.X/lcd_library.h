#include <xc.h>         //lcd_library.h 

#define rs RB0          // komut veri saklayicisi
#define rw RB1          // veri yazma okuma ucu
#define e RB2           // lcd ye gelen komut veri yazmaya baslama ucu e = 1 ise yaz e = 0 ise yazma

#define port_lcd PORTC  // lcd nin veri uclari (C0-C7) baglama portu. 

#define sil 1
#define BasaDon 2
#define Solayaz 4
#define Sagayaz 6
#define ImlecGizle 12
#define ImlecAltta 14
#define ImlecYanSon 15
#define ImlecGeri 16
#define KaydirSaga 24
#define KaydirSola 28
#define EkraniKapat 8
#define BirinciSatir 128
#define IkinciSatir 192
#define KarakUretAdres 64
#define CiftSatir 40
#define TekSatir 32

extern void bekle (void);
extern void veri_yolla(unsigned char c);
extern void lcd_sil(void);
extern void lcd_yaz(const char *s);
extern void lcd_gotoxy(unsigned char x,unsigned char y);
extern void lcd_hazirla(void);
extern void lcd_komut(unsigned char c);

