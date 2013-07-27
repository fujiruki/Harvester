#include <stdio.h>
#include "main.h"


//==============================
// 共通の定数や変数や関数
// 他の人がつくったもの
//==============================
// 他の先生が作った便利な関数使うときはここに書いておく。
// ここに書いてあるものは実機にすでにあるということにする。
// 実機で動かすときはこの部分はコピペしない。
/*{{{移植の必要のないもの*/
void fillBox(int x1, int y1, int x2, int y2, int color);

void fillBox(int x1, int y1, int x2, int y2, int color) {
	int i, j;

	//全部はみ出ていれば、なにもしない。
	if (H_SIZE <= x1 || V_SIZE <= y1 || x2 < 0 || y2 < 0) { return; }

	// 横と縦はみ出ていれば、収まるようにサイズ調整
	if (x1 < 0) { x1 = 0; }
	if (y1 < 0) { x1 = 0; }
	if (H_SIZE < x2) { x2 = H_SIZE; }
	if (V_SIZE < y2) { y2 = V_SIZE; }

	for (i=y1; i<y2; i++) {
		for (j=x1; j<x2; j++) {
			pat[i][j] = color;
		}
	}

	return;
}

// Font Glyph
void put_string(int x, int y, char String[], unsigned char Color);
void put_number(int x, int y, int Number, unsigned char Color);
void Init_Area(int x1, int y1, int x2, int y2, unsigned char Init_Color);

void Init_Area(int x1, int y1, int x2, int y2, unsigned char Init_Color){
int i,j;
 for(i=x1;i<x2;i++)
   for(j=y1;j<y2;j++)
     pat[j][i]=Init_Color;
}

//__attribute__((space(auto_psv))) 
unsigned int FontMap_5x3[95]={	     // map size = 5x3
  0x0000,0x2482,0x5A00,0x5F7D,0x3C9E,	//  ,!,",#,$,
  0x42A1,0x2AAF,0x2800,0x1491,0x4494,	// %,&,',(,),
  0x05D5,0x05D0,0x0014,0x01C0,0x0002,	// *,+,,,-,.,
  0x02A0,0x7B6F,0x2C92,0x73E7,0x73CF,	// /,0,1,2,3,
  0x1779,0x79CF,0x79EF,0x7A49,0x7BEF,	// 4,5,6,7,8,
  0x7BCF,0x0410,0x0414,0x1511,0x0E38,	// 9,:,;,<,=,
  0x4454,0x7282,0x2BEA,0x2BED,0x6BAE,	// >,?,@,A,B,
  0x3923,0x6B6E,0x79A7,0x79A4,0x39EB,	// C,D,E,F,G,
  0x5BED,0x7497,0x326A,0x5BAD,0x4927,	// H,I,J,K,L,
  0x5FED,0x4F6D,0x2B6A,0x6BA4,0x2B73,	// M,N,O,P,Q,
  0x6BAD,0x388E,0x7492,0x5B6F,0x5B6A,	// R,S,T,U,V,
  0x5BFD,0x5AAD,0x5A92,0x72A7,0x3493,	// W,X,Y,Z,[,
  0x0888,0x6496,0x2A00,0x0007,0x4400,	// \,],^,_,`,
  0x22EB,0x49AE,0x01E7,0x12EB,0x05E3,	// a,b,c,d,e,
  0x35D2,0x2ACA,0x49AD,0x2092,0x2094,	// f,g,h,i,j,
  0x4975,0x4491,0x0BED,0x0D6D,0x056A,	// k,l,m,n,o,
  0x6BA4,0x3AC9,0x0BA4,0x028A,0x05D3,	// p,q,r,s,t,
  0x0B6F,0x0B6A,0x0B7D,0x0155,0x5BCF,	// u,v,w,x,y,
  0x0E57,0x3513,0x2492,0x6456,0x0C98	// z,{,|,},~
  };


//__attribute__((space(auto_psv))) 
unsigned long FontMap_5x5[95]={                     // map size = 5x5
  0x0000000,0x0421004,0x0A50000,0x0AFABEA,0x0FA38BE,//  ,!,",#,$,
  0x1111111,0x08AB64D,0x0440000,0x0662186,0x0C308CC,// %,&,',(,),
  0x04AB951,0x0427C84,0x0000088,0x0007C00,0x0000040,// *,+,,,-,.,
  0x0111110,0x0E9D72E,0x0461084,0x1E0BA1F,0x0E89A2E,// /,0,1,2,3,
  0x0654BE2,0x1F8783E,0x0E87A2E,0x1F88884,0x0E8BA2E,// 4,5,6,7,8,
  0x1F8FC3F,0x0020080,0x0020088,0x0222082,0x00F83E0,// 9,:,;,<,=,
  0x0820888,0x0E11004,0x0E8DF2E,0x04547F1,0x1E8FA3E,// >,?,@,A,B,
  0x0E8C22E,0x1E8C63E,0x1F87A1F,0x1F87A10,0x0E84E2E,// C,D,E,F,G,
  0x118FE31,0x0E2108E,0x0E21288,0x13B72D3,0x108421F,// H,I,J,K,L,
  0x11DD631,0x11CD671,0x0E8C62E,0x1E8FA10,0x0E8D64D,// M,N,O,P,Q,
  0x1E8FA51,0x0F8383E,0x1F21084,0x118C62E,0x118C544,// R,S,T,U,V,
  0x11AD6AA,0x1151151,0x1151084,0x1F1111F,0x0E4210E,// W,X,Y,Z,[,
  0x1041041,0x0E1084E,0x0450000,0x000001F,0x0820000,// \,],^,_,`,
  0x0E0BE6D,0x1087A3E,0x007C20F,0x010BE2F,0x0E8FE0E,// a,b,c,d,e,
  0x0727C84,0x0649C2E,0x1087A31,0x0401084,0x0401088,// f,g,h,i,j,
  0x10953D3,0x0821082,0x00556B5,0x00B6631,0x007462E,// k,l,m,n,o,
  0x1E8FA10,0x0F8BC21,0x009D310,0x064104C,0x0471082,// p,q,r,s,t,
  0x008C66D,0x008C544,0x008C6AA,0x000288A,0x1151110,// u,v,w,x,y,
  0x007088E,0x0622086,0x0421084,0x0C2088C,0x0045440 // z,{,|,},~
  };


//__attribute__((space(auto_psv))) 
unsigned long long FontMap_7x5[95]={                          //  map size = 7x5
  0x000000000,0x108420004,0x294A00000,0x295F57D4A,0x11F4717C4,//  ,!,",#,$,
  0x632222263,0x32544564D,0x308800000,0x088842082,0x208210888,// %,&,',(,),
  0x009575480,0x0084F9080,0x000003088,0x0000F8000,0x00000018C,// *,+,,,-,.,
  0x002222200,0x3A33AE62E,0x11842108E,0x3A211111F,0x7C441062E,// /,0,1,2,3,
  0x08CA97C42,0x7E1E0862E,0x1910F462E,0x7C2222108,0x3A317462E,// 4,5,6,7,8,
  0x3A317844C,0x018C03180,0x018C03088,0x088882082,0x001F07C00,// 9,:,;,<,=,
  0x208208888,0x3A2111004,0x3A216D6AE,0x11518FE31,0x7A31F463E,// >,?,@,A,B,
  0x3A308422E,0x72518C65C,0x7E10F421F,0x7E10F4210,0x3A30BC62F,// C,D,E,F,G,
  0x4631FC631,0x38842108E,0x1C4210A4C,0x4654C5251,0x42108421F,// H,I,J,K,L,
  0x4775AC631,0x4639ACE31,0x3A318C62E,0x7A31F4210,0x3A318D64D,// M,N,O,P,Q,
  0x7A31F5251,0x3E107043E,0x7C8421084,0x46318C62E,0x46318C544,// R,S,T,U,V,
  0x4631AD6AA,0x462A22A31,0x463151084,0x7C222221F,0x39084210E,// W,X,Y,Z,[,
  0x020820820,0x38421084E,0x115100000,0x00000001F,0x208200000,// \,],^,_,`,
  0x000E0BE2F,0x4216CC63E,0x000E8422E,0x042D9C62F,0x000E8FE0E,// a,b,c,d,e,
  0x1928E2108,0x36718BC2E,0x4216CC631,0x100C2108E,0x080610A4C,// f,g,h,i,j,
  0x4213A6293,0x30842108E,0x001AAD631,0x0016CC631,0x000E8C62E,// k,l,m,n,o,
  0x5B318FA10,0x36718BC21,0x0016CC210,0x000E8383E,0x211C42126,// p,q,r,s,t,
  0x00118C66D,0x00118C544,0x00118D6AA,0x001151151,0x46318BC2E,// u,v,w,x,y,
  0x001F1111F,0x088441082,0x108421084,0x208411088,0x0008A8800 // z,{,|,},~
  };


//__attribute__((space(auto_psv))) 
unsigned long long FontMap_14x9_u[95]={                                                          // upper map size =14x9
  0x0000000000000000,0x0C06030180C06030,0x1B0D824240000000,0x024121B1B3FDFE6C,0x040F8FEE9F4DE07C,//  ,!,",#,$,
  0x00000C191C999818,0x1E1F9CEC3739F878,0x0C06010100000000,0x0606060603030180,0x0C0300C030180603,// %,&,',(,),
  0x0002111C9B58F838,0x00000381C0E071FF,0x0000000000000000,0x00000000000001FF,0x0000000000000000,// *,+,,,-,.,
  0x0000001018181818,0x0E0F8C64763F379B,0x0607078FC0603018,0x1F1FDC7C180C0607,0x1F1FDC7C180C0C1C,// /,0,1,2,3,
  0x0180C0E070786C66,0x7FFFF80C060379FE,0x1F1FDC7C1E0379FE,0x7FFFF83830381818,0x1F1FD87E1F9DFC7C,// 4,5,6,7,8,
  0x1F1FDC7C1E0F8EFF,0x0000000180C00000,0x0000000180C00000,0x00C0C0C0C0C0C0C0,0x0000000007FFFE00,// 9,:,;,<,=,
  0x6018060180601806,0x1F1FDC7C180C0E0E,0x1F1FD8380CD6FBCD,0x0080C06070383C16,0x7E198C66331998F8,// >,?,@,A,B,
  0x0F4FEE360E030180,0x7F19CC763B1D8EC7,0x7FD86C16031198FC,0x7FD86C16031198FC,0x0F4FEE360E030180,// C,D,E,F,G,
  0x7BD8CC6633198CFE,0x1F070381C0E07038,0x078180C06030180C,0x7BD8CCC6C3C1C0F0,0x78180C06030180C0,// H,I,J,K,L,
  0x71D04C6633B97492,0x61D84C27138964B2,0x1F18C82C1E0F0783,0x7F18CC361B0D8CFC,0x1F18C82C1E0F0783,// M,N,O,P,Q,
  0x7F18CC361B0D8CFC,0x1F58F83C0F01C070,0x7FF77391C0E07038,0x79D84C26130984C2,0x79D84C261318CC64,// R,S,T,U,V,
  0x71D0482492492492,0x7BD8CC6631B0D838,0x60F07C7633B8F838,0x7FF0707830303818,0x0000000000000000,// W,X,Y,Z,[,
  0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,// \,],^,_,`,
  0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,// a,b,c,d,e,
  0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,// f,g,h,i,j,
  0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,// k,l,m,n,o,
  0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,// p,q,r,s,t,
  0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,// u,v,w,x,y,
  0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,// z,{,|,},~
  };

//__attribute__((space(auto_psv))) 
unsigned long long FontMap_14x9_l[95]={                                                          // lower  map size =14x9
  0x0000000000000000,0x0C06030000006030,0x0000000000000000,0x123FDFE6C6C24120,0x0782F97CBBF8F810,//  ,!,",#,$,
  0x0C0CCC9C4C180000,0x3CF731FC7777FEF6,0x0000000000000000,0x60300C0601806018,0x00C0606030303030,// %,&,',(,),
  0x1F1AD93888400000,0x7FC70381C0E00000,0x0000000180C02020,0x7FC0000000000000,0x0000000180C00000,// *,+,,,-,.,
  0x0C0C0C0C04000000,0x6CF67E371318F838,0x06030180C06031FF,0x038383838383FFFF,0x0380E03C1F1DFC7C,// /,0,1,2,3,
  0x31B0DFFFF8180C1F,0x71C0603C1F1DFC7C,0x71F0783C1F1DFC7C,0x06030180C0603018,0x3FB9F87C1F1DFC7C,// 4,5,6,7,8,
  0x1EC0603C1F1DFC7C,0x0000030180000000,0x0000030180404000,0x300C0300C0300C03,0x003FFFF000000000,// 9,:,;,<,=,
  0x0181818181818180,0x0606030180006030,0x6179F7E9A605FC7C,0x0D84C7E333198DEF,0x3398EC361B1D9DFC,// >,?,@,A,B,
  0x603018060B8CFC3C,0x31D8EC763B3D9DFC,0x33188C060B0587FF,0x33188C06030181E0,0x63F078160B8CFE3D,// C,D,E,F,G,
  0x3198CC6633198DEF,0x0E070381C0E0707C,0x033198C86673F0F0,0x3E1B0CC663398FEF,0x30180C060B0587FF,// H,I,J,K,L,
  0x24904824120905C7,0x269348E472190DC2,0x60F0783C1A098C7C,0x30180C06030181E0,0x60F0783DDB398C7D,// M,N,O,P,Q,
  0x36198CC633198DEF,0x0E0380E83E0F8D7C,0x0E070381C0E0707C,0x30984C261309CC7C,0x1B0D86C140E07010,// R,S,T,U,V,
  0x2D96CBC7E361B090,0x0E0D86C633198DEF,0x0E070381C0E0707C,0x0C0E06060F0707FF,0x0000000000000000,// W,X,Y,Z,[,
  0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,// \,],^,_,`,
  0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,// a,b,c,d,e,
  0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,// f,g,h,i,j,
  0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,// k,l,m,n,o,
  0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,// p,q,r,s,t,
  0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,// u,v,w,x,y,
  0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,// z,{,|,},~
  };



// Font Size Indexes
unsigned int small=0, normal=1, large=2, huge = 3;
unsigned int DefaultFont=1;
unsigned int FontSize=1, FontWidth=5, FontHeight=5, FontDepth=2, FontHSkip=6, FontVSkip=8;

unsigned int RankScore[3]={50,10,1};
char RankName[3][3]={"AAA","BBB","CCC"};
char RankNum[3][3]={"1st","2nd","3rd"};

////////////////////////////////////////////////////////////////////////
int Line_Score=0;

//スコアボードの表示
void Score_Board(){
 int i,j,k,x,y,RankIn=0;
 int TempScore;
 char font[]="DEF";
 char String[3];
 unsigned int Color;
 Init_Area(0,0,H_SIZE,V_SIZE,0x00);
 put_string(1,1,"RANKING",0x2C);

 if(Line_Score>RankScore[2]){				// ランクインしたときのデータソート
  RankIn=3;
  RankScore[2]=Line_Score; for(j=0;j<3;j++) RankName[2][j]=font[j];
  for(i=0;i<2;i++)
    if(RankScore[2-i]>RankScore[1-i]){
      RankIn=2-i;
      j=RankScore[2-i]; RankScore[2-i]=RankScore[1-i]; RankScore[1-i]=j;
      for(j=0;j<3;j++) font[j]=RankName[2-i][j];
      for(j=0;j<3;j++) RankName[2-i][j]=RankName[1-i][j];
      for(j=0;j<3;j++) RankName[1-i][j]=font[j];
    }
 }

 y=8; x=40; k=0; 
 for(i=0;i<3;i++){
   if(i>0){
    if(RankScore[i-1]>RankScore[i]) k++;		// ランクデータの順位付け
   }
   TempScore=RankScore[i];
   for(j=0;j<4;j++){
     put_number(36+FontHSkip*(3-j),y+i*16+6,TempScore%10,0xFC);
     TempScore=(int)TempScore/10;
     if(!i&&!RankIn){					// 取得したスコアの表示
       put_number(36+FontHSkip*(3-j),y+46,Line_Score%10,0xFC); 
       Line_Score=(int)Line_Score/10;
     }
     if(j<3){
       sprintf(String,"%c",RankName[i][2-j]);
       put_string(16+FontHSkip*(2-j),y+i*16+6,String,0x08);
       sprintf(String,"%c",RankNum[k][2-j]);
       if(k==0) Color=0x30; else if(k==1) Color=0xC0; else Color=0xB0;
       put_string(1+FontHSkip*(2-j),y+i*16,String,Color);
     }
   }
 }

while(!BTN1){ // チャタリング防止
 disp_frame();
 BTN1=1;
 }


 y=14+(RankIn-1)*16; x=16; j=0;
 while(BTN1){			// BTN1で名前決定．ゲームリスタート
   if(RankIn){
   Init_Area(x,y,x+FontHSkip*3,y+FontHeight+FontDepth+2,0x00);
   put_string(x,y,font,0x0C);
   for(i=0;i<FontWidth;i++)
     pat[y+FontHeight+FontDepth+1][x+FontHSkip*j+i]=0xFC;
   
   if(!U_BTN){
     if(font[j]=='a') font[j]='Z';
     else if(font[j]=='A') font[j]='z';
     else             font[j]-=1;
     while(!U_BTN){
      disp_frame();
      U_BTN=1;
      }
   }
   if(!D_BTN){
     if(font[j]=='Z') font[j]='a';
     else if(font[j]=='z') font[j]='A';
     else             font[j]+=1;
     while(!D_BTN){
      disp_frame();
      D_BTN=1;
      }
   }
   if(!R_BTN){
     if(++j>2) j=2;
     while(!R_BTN){
      disp_frame();
      R_BTN=1;
      }
   }
   if(!L_BTN){
     if(--j<0) j=0;
     while(!L_BTN){
      disp_frame();
      L_BTN=1;
      }
   }
   }
   disp_frame();
 }


 if(RankIn) for(j=0;j<3;j++) RankName[RankIn-1][j]=font[j];
 BTN1=1;
}// end of Score_Board()






////////////////////////////////



void SetFontSize(unsigned int FSize){
 switch(FSize){
   case 0 : FontSize=small; FontWidth=3; FontHeight=5;
            FontDepth=2;    FontHSkip=1+FontWidth;
            FontVSkip=1+FontHeight+FontDepth; break;
   case 1 : FontSize=normal;FontWidth=5; FontHeight=5;
            FontDepth=2;    FontHSkip=1+FontWidth;
            FontVSkip=1+FontHeight+FontDepth; break;
   case 2 : FontSize=large; FontWidth=5; FontHeight=7;
            FontDepth=2;    FontHSkip=1+FontWidth;
            FontVSkip=1+FontHeight+FontDepth; break;
   case 3 : FontSize=huge;  FontWidth=9; FontHeight=14;
            FontDepth=6;    FontHSkip=1+FontWidth;
            FontVSkip=1+FontHeight+FontDepth; break;
   }
 }

void put_string(int x, int y, char String[], unsigned char Color){
 int g=y,h,i,j;
 unsigned long long k,l;
 for(h=0;h<strlen(String);h++){
   y=g;
   if(String[h]=='g' || String[h]=='p' || String[h]=='q' || String[h]=='y')
    y+=FontDepth;
   switch(FontSize){
     case 0 : k=FontMap_5x3[String[h]-' '];    break;
     case 1 : k=FontMap_5x5[String[h]-' '];    break;
     case 2 : k=FontMap_7x5[String[h]-' '];    break;
     case 3 : l=FontMap_14x9_u[String[h]-' '];
              k=FontMap_14x9_l[String[h]-' ']; break;
   }
   for(i=FontHeight-1;i>=0;i--)
     for(j=FontWidth-1;j>=0;j--){
       if(FontSize==huge && i<7){
         pat[y+i][x+FontHSkip*h+j]=l&1>0?Color:pat[y+i][x+FontHSkip*h+j];
         l>>=1;
       }
       else{
         pat[y+i][x+FontHSkip*h+j]=k&1>0?Color:pat[y+i][x+FontHSkip*h+j];
         k>>=1;
       }
     }
   }
 SetFontSize(DefaultFont);
}

void put_number(int x, int y, int Number, unsigned char Color){
 int i,j;
 char String[200];
 i=Number;
 for(j=0;i;j++) i/=10;
 sprintf(String,"%d",Number);
 put_string(x,y,String,Color);
}


/*}}}*/



//==============================
// 定数宣言 LITERAL
//==============================
/*{{{Harvester-LITERAL*/
#define chat_UP	5			// チャタリング防止用の空回しループ回数
#define TIMELIMIT	30
#define PLAYER_W	5
#define PLAYER_H	8
#define PLAYER_SPEED	1.7

#define ROAD_Y			(V_SIZE-3) //(V_SIZE-PLAYER_H-3)
#define PLAYER_X_DEF	(20)
#define PLAYER_Y_DEF	(ROAD_Y-PLAYER_H)
#define HVESTER_COLOR	0x70
#define BASKET_FRAME_COLOR	0x10	// バスケットのフレームの色
#define BASKET_COLOR	0x60	// バスケットの色
#define BASKET_COLOR_BRIGHT	0x60	// バスケットの点滅時の色
// FRUIT
#define FRUITS_MAX	11				// フルーツの最大数
#define FR_STATE_NONE	0		// Fruitがない
#define FR_STATE_GREEN	1		// 青い小さい実
#define FR_STATE_BIG	2		// 青い大きな実
#define FR_STATE_RIPE	3		// 赤い大きな実(完熟)
#define FR_STATE_DROPPING	4	// 落下中
#define FR_RIPE_R			1		// フルーツの半径
#define FR_RIPE_DIA			2		// フルーツの直径	//Diameter
#define FR_COLOR_RIPE	0x30	// RIPEの色
#define FR_DROPPING_F	0.14	// 落下中のフルーツへかかる力
#define FR_BOUND_F		(-1.1)	// バウンドした瞬間のフルーツへかかる力
#define FR_DROPPING_MAXSPEED	1.7

//=== TYPE =====================
typedef struct Pos {
	int x, y;
} Pos;
typedef struct Size {
	int w, h;
} Size;
typedef struct FPos {
	float x, y;
} FPos;
typedef struct LevelConf {
	unsigned char level;	// 現在のレベル
	unsigned char level_prev;	// 直前までのレベル(変化を確認するため)
	char fruits_n;	// 現在の果実の最大数
	char fruits_n_prev;	// 直前までのレベル(変化を確認するため)
	char gstate;
	char gstate_cnt;
} LevelConf;/*}}}*/

//==============================
// 独自関数のプロトタイプ宣言 PROTOTYPE
//==============================
/*{{{Harvester-PROTOTYPE*/
void harvester_init(); // ゲームの初期化関数
void harvester_main(); // ゲームの関数
void plot(int x, int y, int color);
void draw_line(int x1, int y1, int x2, int y2, int color);
void hvr_draw_back();

void loop_chatter(unsigned char *counter, char *flag);	// counterをデクリメントして0ならflagを0にする

void check_level();
void check_collision_fruits();	// フルーツとの当たり判定

void move_harvester();
void draw_harvester();
void draw_basket();

void move_basket();

void set_fruit(int fruiti);	// 指定の番号にフルーツを作成する
void grow_fruits();	// フルーツを成長させる
void drop_fruits();	// フルーツを落とす
void draw_fruits();	// フルーツを描く

void approximate_timelimit();
void draw_timelimit();

//==============================
// 独自のグローバル変数の宣言 VALUE
//==============================

// 果実
typedef struct Fruit {
	FPos p;			// 現在の場所
	FPos p_prev; 	// 直前の場所
	float f;		// 現在加えられている力
	unsigned char state;	// 果実、完熟、落下中
	unsigned int state_cnt;
} Fruit;

// 収穫者
typedef struct Harvester {
	FPos p;		// 現在の場所
	FPos p_prev; // 直前の場所
	float f,fy;	// 現在加えられている力
	char isflying;	// 空中なら1
	char turnRight;		// 向き。1なら右、それ以外で左向き
} Harvester;

// カゴ
typedef struct Basket {
	Pos p;
	Size size;
} Basket;/*}}}*/

//=== VARIABLES =================
/*{{{Harvester-VARIABLES*/
#define LCOUNT_FRUITS_GROW	6
unsigned int lcnt_fruits_grow;
#define LCOUNT_TIMELIMIT	20
unsigned int lcnt_timelimit;
Fruit fruits[FRUITS_MAX];	// フルーツ(時間経過で成長、落下する。収穫者でバウンド)
Harvester hvester;			// 収穫者(プレイヤーが操作する)
LevelConf conf;
Basket basket;
unsigned char cloop_u_btn;	// loop for chatterring
unsigned char cloop_d_btn;
unsigned char cloop_btn1;
char C_U_BTN;			// チャタリング対策済みボタン変数(credible)
char C_D_BTN;
char C_L_BTN;
char C_R_BTN;
char C_BTN1;
char C_BTN2;
unsigned int score, score_prev;
unsigned int timelimit;
char str_score[20];
#define GSTATE_MAIN 1
#define GSTATE_END	2
#define GSTATE_RANK	3/*}}}*/


//==============================
// 独自関数 FUNCTION
//==============================
/*{{{Harvester-FUNCTIONS*/
void plot(int x, int y, int color) {
	if (0 <= x && x < H_SIZE && 0<=y && y < V_SIZE)
	{
		pat[y][x] = color;
	}
}
void draw_line(int x1, int y1, int x2, int y2, int color) {
	// 参考:http://fussy.web.fc2.com/algo/algo1-1.htm
	int i;
	Pos dist, direc;	// 2点間距離、方向
	int E;

	// 2点間距離
	dist.x = (x2 > x1) ? (x2-x1):(x1-x2);
	dist.y = (y2 > y1) ? (y2-y1):(y1-y2);

	// 2点の方向
	direc.x = (x2 > x1) ? 1 : -1;
	direc.y = (y2 > y1) ? 1 : -1;

	//傾きが1より小さい場合
	if ( dist.x > dist.y )
	{
		E = -dist.x;
		for ( i = 0 ; i <= dist.x ; i++ ) {
			plot( x1, y1, color );
			x1 += direc.x;
			E += 2 * dist.y;
			if ( E >= 0 ) {
				y1 += direc.y;
				E -= 2 * dist.x;
			}
		}
		/* 傾きが1以上の場合 */
	} else {
		E = -dist.y;
		for ( i = 0 ; i <= dist.y ; i++ ) {
			plot( x1, y1, color );
			y1 += direc.y;
			E += 2 * dist.x;
			if ( E >= 0 ) {
				x1 += direc.x;
				E -= 2 * dist.y;
			}
		}
	}
}

void move_basket() {
	if (hvester.turnRight == 1) {
		basket.p.x = hvester.p.x - basket.size.w - 1;
	} else {
		basket.p.x = hvester.p.x  + PLAYER_W;	//hvester.size.w;
	}
}

void move_harvester() {
	FPos p_tmp;
	p_tmp.x = hvester.p.x;

	if (!R_BTN) {
		hvester.p.x += PLAYER_SPEED;
		hvester.turnRight = 1;
	}
	if (!L_BTN) {
	 	hvester.p.x -= PLAYER_SPEED;
		hvester.turnRight = 0;
	}

/*
	if (!U_BTN && !hvester.isflying) {
		hvester.fy = -1.0;
		hvester.isflying=1;
	} else {
		hvester.fy = FR_BOUND_F;
	}
	
	if (hvester.isflying) {
		p_tmp.y = hvester.p.y;
		hvester.p.y -= +(hvester.p.y - hvester.p_prev.y) + hvester.fy;
		hvester.p_prev.y = p_tmp.y;
		if (hvester.p.y == ROAD_Y) {
			hvester.isflying=0;
		}
	}
*/

	hvester.p_prev.x = p_tmp.x;
}
void plot_vec(int r, int y, int col) {
	if (hvester.turnRight == 1) {
		// 右向き
		plot(hvester.p.x+2+r, hvester.p.y+y, col);
	} else {
		// 左向き
		plot(hvester.p.x+2-r, hvester.p.y+y, col);
	}
}
void draw_harvester() {
	fillBox(hvester.p.x, hvester.p.y,
			hvester.p.x + PLAYER_W, hvester.p.y + PLAYER_H, HVESTER_COLOR);

	plot_vec(2, 0, 0xff);
	plot_vec(1, 2, 0x30);
	plot_vec(-2, 0, 0xff);
	plot_vec(2, 5, 0xff);
	plot_vec(1, 5, 0xd4);
}


void draw_basket() {
	draw_line(basket.p.x, basket.p.y, basket.p.x, basket.p.y + basket.size.h, BASKET_FRAME_COLOR);
	draw_line(basket.p.x+basket.size.w, basket.p.y, basket.p.x+basket.size.w, basket.p.y + basket.size.h, BASKET_FRAME_COLOR);
	draw_line(basket.p.x, basket.p.y + basket.size.h, basket.p.x+basket.size.w, basket.p.y + basket.size.h, BASKET_FRAME_COLOR);
	fillBox(basket.p.x+1, basket.p.y, basket.p.x+basket.size.w, basket.p.y + basket.size.h, BASKET_COLOR);
}

//fruiti番目のフルーツをセットする
void set_fruit(int fruiti) {
	// fruits
	fruits[fruiti].p.x = rand() & 0x3f;
	fruits[fruiti].p.y = rand() & 0x03;
	fruits[fruiti].state = FR_STATE_NONE;
	fruits[fruiti].state_cnt = rand() & 0x0f +1;
}

void hvr_draw_back() {
	int i;
	char str[10];
	fillBox(0, 0, H_SIZE, V_SIZE, 0xff);
	draw_line(5, 0, H_SIZE-5, 0, 0xdc);
	draw_line(3, 1, H_SIZE-3, 1, 0xdc);
	draw_line(2, 2, H_SIZE-2, 2, 0xdc);

	/*
	// カラースケール
	for (i=0; i<0x3f;i++) {
		if (i < 60) {
			plot(i, 2, i<<2);
			plot(i, 1, (i&1)?0xff:0x00);
			if (i%10==0) {
				plot(i, 1, 0x30);
			}
		} else {
			plot(i-60, 2, i<<2);
		}
	}
	*/
}

void grow_fruits() {
	int i;
	for (i=0; i<conf.fruits_n; i++) {
		// 落下中はdrop_fruits()にまかせる。
		if (fruits[i].state == FR_STATE_DROPPING) {
			continue;
		}
		if (fruits[i].state_cnt!=0) {
			fruits[i].state_cnt--;
			continue;
		}

		fruits[i].state++;

		switch (fruits[i].state) {
			case FR_STATE_NONE:
					fruits[i].state_cnt = (rand() & 0x03)+2;
				break;
			case FR_STATE_GREEN:
					fruits[i].state_cnt = (rand() & 0x03)+1;
				break;
			case FR_STATE_BIG:
					fruits[i].state_cnt = (rand() & 0x03)+1;
				break;
			case FR_STATE_RIPE:
					fruits[i].state_cnt = (rand() & 0x01)+1;
					fruits[i].f = FR_DROPPING_F;
					fruits[i].p_prev.y = fruits[i].p.y;
				break;
			//case FR_STATE_DROPPING:
				//break;
			default:	// どれでもなくなったとき
				break;
		}
	}
}
// フルーツを描く
void draw_fruits() {
	int i;
	for (i=0; i<conf.fruits_n; i++) {
		switch (fruits[i].state) {
			case FR_STATE_NONE:
				break;
			case FR_STATE_GREEN:
				plot(fruits[i].p.x, fruits[i].p.y, 0x94);
				break;
			case FR_STATE_BIG:
				fillBox(fruits[i].p.x-1, fruits[i].p.y, fruits[i].p.x+1, fruits[i].p.y+2, 0x74);
				break;
			case FR_STATE_RIPE:
				fillBox(fruits[i].p.x-FR_RIPE_R, fruits[i].p.y, fruits[i].p.x+FR_RIPE_R, fruits[i].p.y+2, FR_COLOR_RIPE);
				break;
			case FR_STATE_DROPPING:
				fillBox(fruits[i].p.x-1, fruits[i].p.y, fruits[i].p.x+1, fruits[i].p.y+FR_RIPE_DIA, 0x20);
				break;
			default:	// どれでもなくなったとき
				break;
		}
	}
}

// フルーツを落とす
void drop_fruits() {
	int i;
	float y_tmp, vy;
	for (i=0; i<conf.fruits_n; i++) {
		if (fruits[i].state != FR_STATE_DROPPING) {
			continue;
		}

		y_tmp = fruits[i].p.y;
		vy = (fruits[i].p.y - fruits[i].p_prev.y) + fruits[i].f;
		if (vy > FR_DROPPING_MAXSPEED) { vy = FR_DROPPING_MAXSPEED; }
		fruits[i].p.y += vy;
		fruits[i].p_prev.y = y_tmp;

		// 画面外に出たら種にもどる
		if (fruits[i].p.y >= V_SIZE) {
			set_fruit(i);
			continue;
		}
	}
	
}
// フルーツとカゴの枠との当たり判定
void check_collision_basket_fruit(Fruit *fr)
{
	char fr_y;
	char x;
	fr_y = (*fr).p.y + FR_RIPE_DIA;

	for (x=(*fr).p.x+FR_RIPE_R-1; x>=(*fr).p.x-1; x--) {
		if (pat[fr_y][x] == BASKET_FRAME_COLOR || pat[fr_y][x] == HVESTER_COLOR) {
			// バウンドさせる
			(*fr).f = FR_BOUND_F;
			(*fr).p_prev.y = (*fr).p.y;
		}
	}
}
void draw_atari()
{
	char i;
	char fr_y;
	Fruit *fr;
	char x;
	for (i=0; i<conf.fruits_n; i++) {
		fr = &(fruits[i]);
		fr_y = (*fr).p.y + FR_RIPE_DIA;
		for (x=(*fr).p.x+FR_RIPE_R-1; x>=(*fr).p.x-1; x--) {
			plot(x, fr_y, 0x00);
		}
	}
}
// フルーツとの当たり判定
void check_collision_fruits() {
	char i;
	char y;
	Fruit *fr;

	for (i=0; i<conf.fruits_n; i++) {
		fr = &(fruits[i]);
		// もしカゴの枠ならバウンド
		if ((*fr).f != FR_DROPPING_F) {
			(*fr).f = FR_DROPPING_F;
		}
		check_collision_basket_fruit(fr);

		// もしカゴの中ならスコアプラス
		if (pat[(int)(*fr).p.y][(int)(*fr).p.x] == BASKET_COLOR) {
			if (conf.gstate==GSTATE_MAIN) {
				score++;
			}
			set_fruit(i);
		}
		// RIPEの位置なら
		//if (pat[(*fr).p.y][(*fr).p.x] == FR_COLOR_RIPE) 
	}
}

void check_level() {
	char next_fru_n;
	char i;

	next_fru_n = conf.fruits_n;
	switch (conf.level)
	{
		case 1:
			next_fru_n = 2;
			break;
		case 2:
			next_fru_n = 3;
			break;
		case 3:
			next_fru_n = 4;
			break;
		case 4:
			next_fru_n = 6;
			break;
		case 5:
			next_fru_n = 7;
			break;
		case 6:
			next_fru_n = 10;
			break;
		case 7:
			next_fru_n = FRUITS_MAX;
			break;
	}

	for (i=conf.fruits_n; i<next_fru_n; i++) {
		// フルーツ数が増えたら増やす
		set_fruit(i);
	}

	conf.fruits_n = next_fru_n;
}


// タイムリミットを計算
void approximate_timelimit() {
	if (timelimit<=0) {
		conf.gstate = GSTATE_END;
		conf.fruits_n = 5;
		return;
	}

	timelimit --;
	if        (timelimit <= 10 || score >= 20) {
		conf.level = 7;
	} else if (timelimit <= 14 || score >= 10) {
		conf.level = 6;
	} else if (timelimit <= 19 || score >= 7) {
		conf.level = 5;
	} else if (timelimit <= 24 || score >= 4) {
		conf.level = 4;
	} else if (timelimit <= 27 || score >= 3) {
		conf.level = 3;
	} else if (timelimit <= 33 || score >= 1) {
		conf.level = 2;
	}
}
// タイムリミットを描画
void draw_timelimit() {
	char x;
	char right = H_SIZE-18;
	int col;
	for (x=right-timelimit; x<= right; x++) {
		if (timelimit >= 10)     { col = 0xa0; }
		else if (timelimit >= 5) { col = 0xcc; }
		else                     { col = 0x30; }

		pat[V_SIZE-2][x]= col;
	}
}

//==============================
// ゲームの初期化関数 INIT
//==============================
void harvester_init()
{
	int i;

	// チャタリング対策済みボタン変数
	C_U_BTN = 1;
	C_D_BTN = 1;
	C_L_BTN = 1;
	C_R_BTN = 1;
	C_BTN1 = 1;
	C_BTN2 = 1;
	cloop_u_btn = 0;		// チャタリング防止用
	cloop_d_btn = 0;		// チャタリング防止用
	cloop_btn1 = 0;

	lcnt_fruits_grow = 0;

	hvester.p.x = hvester.p_prev.x = PLAYER_X_DEF;
	hvester.p.y = hvester.p_prev.y = PLAYER_Y_DEF;
	hvester.turnRight = 1;
	hvester.fy = FR_DROPPING_F;
	hvester.isflying = 0;
	basket.p.y = hvester.p.y - 2;
	basket.size.w = 6;
	basket.size.h = 8;
	draw_basket();

	// 全てのフルーツを存在させない
	for (i=0; i<FRUITS_MAX; i++) {
		fruits[i].state = FR_STATE_NONE;
	}


	conf.level_prev = 0;
	conf.level = 1;
	conf.gstate = GSTATE_MAIN;
	score = 0;
	score_prev = -1;	// はじめはあえて違う数字にする
	timelimit = TIMELIMIT;
}

// counterが1以上なら1減らし、
// 0になったらflagを0にする
void loop_chatter(unsigned char *counter, char *flag) {
	if (*counter > 0) {
		(*counter)--;
		if (*counter == 0) {
			// U_BTNが確定した
			*flag  = 0;
		}
	}
}
void hvr_draw_score() {
	if (score_prev != score) {
		score_prev = score;
		sprintf(str_score, "%3dpt", score);
	}
	SetFontSize(small);
	put_string(H_SIZE-22, V_SIZE-6, str_score, 0x00);
}

void draw_end() {
	put_string(10,20, str_score, HVESTER_COLOR);
}

//==============================
// ゲームのメインの処理の関数 MAIN
// 呼ばれた後、毎回disp_frame()が呼ばれている。
//==============================
void harvester_main()
{
	unsigned char *counter;
	char *flag;
	if (!BTN1) { set_fruit(0); }
	if (!U_BTN && cloop_u_btn==0) { cloop_u_btn = chat_UP; }
	if (!D_BTN && cloop_d_btn==0) { cloop_d_btn = chat_UP; }
	if (!BTN1 && cloop_btn1==0)   { cloop_btn1 = chat_UP; }
	loop_chatter(&cloop_u_btn, &C_U_BTN);
	loop_chatter(&cloop_d_btn, &C_D_BTN);
	loop_chatter(&cloop_btn1, &C_BTN1);

	/*
	// U_BTNが押されたら(チャタリング対策済み)
	// レベルを上げる
	if (!C_U_BTN) {
		C_U_BTN = 1;
		if (conf.level < 8) {
			conf.level++;
		}
	}
	if (!C_D_BTN) {
		C_D_BTN = 1;
		if (conf.level > 1) {
			conf.level--;
		}
	}
	*/
	if (!C_BTN1) {
		C_BTN1 = 1;
		// 終了状態でBTN1を押すとランキング表示
		if (conf.gstate == GSTATE_END) {
			//conf.gstate == GSTATE_RANK;
			harvester_init();
		}
	}


	// レベルが変化していれば設定を変更する
	if (conf.level != conf.level_prev) {
		conf.level_prev = conf.level;
		check_level();
	}


	// フルーツを成長させる
	if (++lcnt_fruits_grow >= LCOUNT_FRUITS_GROW) {
		lcnt_fruits_grow = 0;
		grow_fruits();
	}

	// フルーツを落とす
	drop_fruits();


	if (++lcnt_timelimit == LCOUNT_TIMELIMIT) {
		lcnt_timelimit = 0;
		approximate_timelimit();
	}

	if (timelimit>0) {
		// 収穫者をうごかす
		move_harvester();
		move_basket();				// カゴをうごかす
	}

	// 当たり判定
	check_collision_fruits();	// フルーツとの当たり判定
	
	// 画面クリア
	disp_frame();
	hvr_draw_back();
	//draw_atari();

	// 時間制限で終了画面を表示
	if (timelimit<=0) {
		if (conf.gstate == GSTATE_MAIN) {
			conf.gstate = GSTATE_END;
			sprintf(str_score, "score:%d", score);

			// 結果をスコアボードに書き込み
			Line_Score = score;
		}
		draw_end();
	}
	// フルーツを描く
	draw_fruits();
	draw_basket();
	// 自機を描く
	draw_harvester();
	//draw_line(5,5, 40,50, 0x00);
	
	draw_timelimit();
	if (conf.gstate == GSTATE_MAIN) {
		hvr_draw_score();
	}
}/*}}}*/
