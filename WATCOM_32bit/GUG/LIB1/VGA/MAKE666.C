//***************************************************************************
// Generate a 666 palette   
//
void GUGMake666Palette(char *pal) {
  int i,j,k; 

  // clear the game palette
  for(i = 0; i < 768; i++) pal[i] = 0;

  // Now set the game to a 666 palette
  for(i = 0; i < 6; i++) {
	 for(j = 0; j < 6; j++) {
		for(k = 0; k < 6; k++) {
		  pal[(i + j*6+  k*36)*3] = i*12.6;
		  pal[(i + j*6+  k*36)*3+1] = j*12.6;
		  pal[(i + j*6+  k*36)*3+2] = k*12.6;
		}
	 }
  }

  // Grey Scale Area
  pal[648] =  0; pal[649] =  0; pal[650] =  0;
  pal[651] =  7; pal[652] =  7; pal[653] =  7;
  pal[654] = 11; pal[655] = 11; pal[656] = 11;
  pal[657] = 15; pal[658] = 15; pal[659] = 15;
  pal[660] = 19; pal[661] = 19; pal[662] = 19;
  pal[663] = 23; pal[664] = 23; pal[665] = 23;
  pal[666] = 27; pal[667] = 27; pal[668] = 27;
  pal[669] = 31; pal[670] = 31; pal[671] = 31;
  pal[672] = 35; pal[673] = 35; pal[674] = 35;
  pal[675] = 39; pal[676] = 39; pal[677] = 39;
  pal[678] = 43; pal[679] = 43; pal[680] = 43;
  pal[681] = 47; pal[682] = 47; pal[683] = 47;
  pal[684] = 51; pal[685] = 51; pal[686] = 51;
  pal[687] = 55; pal[688] = 55; pal[689] = 55;
  pal[690] = 59; pal[691] = 59; pal[692] = 59;
  pal[693] = 63; pal[694] = 63; pal[695] = 63;

}
