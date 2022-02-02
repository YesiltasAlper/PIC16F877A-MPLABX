Burada 400 mikro saniye PWM periyodu %50 Duty Cycle olarak calistirilmistir.
Uygulamanin anlatimi asagidadir.

CCP1CON registerinda ilk 4 bit (0-1-2-3) capture compare pwm modu ayarlama bitidir
ve biz hepsini 1 yaparak pwm moduna ayarladik.Ardindan bu registerin 4. ve 5.biti
pwm'in duty cycle'ini etkileyen bitlerdir.CCP1Y 4.bitidir CCP1X 5.bitidir.
Bu durumda toplam 10 bitlik olan pwm'in ilk 2 dusuk biti CCP1CON registerinin
4. ve 5. bitidir.Diger 8 yuksek degerlikli bit degerini ise CCPR1L tutar.

Ardindan T2CON registerinda PWM Timer2'yi kullandigi icin TMR2 aktif edilerek
prescaler degeri 4 yapilmistir.

PWM'in periyodu = (PR2+1) * (4) * (Tosc)        * (TMR2 Prescaler)
		= (100+1) * (4) * (1/4x10^6 sn) * (4)
sonucunda 400 mikro saniye olarak pwm'in periyodu bulunmustur.

PWM'in Duty Cycle = (CCPR1L:CCP1CON<5:4>) * (Tosc)        *  (TMR2 Prescaler)
		  = (200) 		  * (1/4x10^6 sn)    (4)
sonucunda 200 mikro saniye olarak pwm aktiftir.

Bu durumda pwm sinyali %50 duty cycle ile calisir.
Dikkat edilmesi gereken sey (CCPR1L:CCP1CON<5:4>) buraya yazilan deger eger
yuksek olursa ve PWM'in periyodunu gecerse (400 mikro saniye) bu durumda
PWM sinyali olusmaz.Oraya yazilacak deger bu duruma gore hesap edilmelidir.

Ayrica 200 degeri CCPR1L ve CCP1CON<5:4>'e yazilmalidir.Bunun icin
CCPR1L = duty>>2;	CCP1Y = duty&1;		CCP1X = duty&2;  islemleri yapildi.

Cunku CCPR1L bu 200'un yuksek degerlikli 8 bitini tutarken CCP1Y ve CCP1X 200
sayisinin dusuk degerlikli iki bitini tutar.En dusuk degerlikli bit ise CCP1Y'dir.

16 bit degiskende tutulan 200 degeri --->>  00000000 11001000
CCPR1L = duty>>2; sonrasi --->> 00110010 (CCPR1L 8 bittir)
CCP1X = duty&2;   sonrasi --->> 0 (CCP1X ve CCP1Y kalan 2 biti olusturur)	
CCP1Y = duty&1;   sonrasi --->> 0 (CCP1Y ise en dusuk degerlikli bittir)

Son durum olarak 10 bit   --->> 0011001000
(CCPR1L)(CCP1X)(CCP1Y)
				(8 BIT) (1 BIT)(1 BIT)
