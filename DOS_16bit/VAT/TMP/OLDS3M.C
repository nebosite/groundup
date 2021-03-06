/**************************************************************************

	S3M.C

  Code by Bryan Wilkins and Eric Jorgensen


**************************************************************************/

#include <stdio.h>
#include <alloc.h>
#include "vat.h"

// ------------------------------------ internal functions

void sdodiv(void);
void sdotick(void);
void inits3m(void);


// ------------------------------------ external varaibles

extern SHORT dma_bufferlen;
extern SHORT *mix_buffer;
extern SHORT vsin[];
extern SHORT vtable[256][64];

// ------------------------------------ S3m Variables

                                       // Default periods for calculating
                                       // Notes.
LONG s3m_period[12] = {109568L,103424L,97536L,92160L,86784L,81920L,
											77312L,72960L,68864L, 65024L,61440L,58048L};

                                       // This is for volume settings in effect
                                       // number Q retrig+volslide
SHORT s3m_retvol[16] = {0,-1,-2,-4,-8,-16,99,99,0,1,2,4,8,16,99,99};

SHORT channels;
SHORT s3m_division;
SHORT s3m_loopcount=-1;
SHORT s3m_vibratocount=0;
SHORT s3m_reset=FALSE;
SHORT s3m_bytespertick=220;
SHORT s3m_divspot;
SHORT s3m_volume=8;
SHORT s3m_on=FALSE;
SHORT s3m_order;
SHORT s3m_patterndelay=0;
SHORT s3m_divbytes=160;
BYTE VFAR *s3m_pattern,*s3m_pstop,*s3m_loopspot=NULL;
S3M VFAR *s3m_data=NULL;
SHORT s3m_currentbyte,s3m_currenttick,s3m_ticksperdivision=6;
                                       // Allows on/off control of s3mchannels
SHORT s3m_channelselect[32] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                             1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
static CHANNEL VFAR chan[32];

/*************************************************************************
void s3mplayer(void)

DESCRIPTION: Routine for playing s3m files.  This is designed to be called
             from a timer interrupt.  To use these values must be set:

             s3m_data must point to a filled s3m structure
             s3m_reset must be TRUE.
             s3m_on must be TRUE.

             The interrupt should pick up from here.
*************************************************************************/
void s3mplayer(void)
{
	static SHORT i,j,vol;
  SHORT lastbyte;

  debugnum++;

  if(s3m_reset) {
		debugnum += 10000;
		channels=s3m_data->channelnum;       // Reset the S3M?
    for(i = 0; i < channels; i++ ) {     // Reset all channels
      chan[i].bufferdummy1 = 0;
      chan[i].bufferdummy2 = 0;
      chan[i].sdata = NULL;
      chan[i].offset = 0;
      chan[i].rlength = 0;
      chan[i].end = 0;
      chan[i].volume = 0;
      chan[i].sample_number = 0;
      chan[i].position= 0;
      chan[i].pos = (DWORD *)(((BYTE *)&chan[i].position)+1);
      chan[i].counter = 0;
			chan[i].pinc = 0;
      chan[i].effect = 0;
      chan[i].x = 0;
      chan[i].y = 0;
      chan[i].s3m_fine=FALSE;
      chan[i].fineperiod=0;
    }
																				 // reset the global s3m variables
		s3m_divbytes=s3m_data->channelnum * 5;
    s3m_pattern=s3m_data->pattern_data[s3m_data->order[0]];
		s3m_pstop=s3m_pattern+s3m_divbytes*64;
    s3m_bytespertick=((s3m_data->inittempo-250)*220)/-125;
    s3m_bytespertick=(WORD)(((LONG)sample_rate*s3m_bytespertick)/11000L);
    s3m_ticksperdivision=s3m_data->initspeed;
    s3m_currentbyte=0;
    s3m_currenttick=0;
    s3m_reset=FALSE;
    s3m_order=0;
		s3m_division=0;
  }
                                         //Mix the buffer if the number of
                                         //left is bigger than bufferlen
  if(s3m_currentbyte > dma_bufferlen) {
    for(i=0;i<channels;i++){             //loop through ALL channels...
      if(chan[i].volume && *chan[i].pos < chan[i].end) {
				vol = (chan[i].volume * s3m_volume)/64;
				for(j=0;j<dma_bufferlen;j++){
					*(mix_buffer+j) += vtable[*(chan[i].sdata + (WORD)*chan[i].pos)+128][vol];
					chan[i].position+=chan[i].pinc;
          if(*chan[i].pos>=chan[i].end) {
            if(chan[i].sflag&0x1) {      //If this inst loops loop it...
              chan[i].position=chan[i].offset*256L;
              chan[i].counter=0;
              chan[i].end=chan[i].rlength;
            }
            else break;
          }
        }
      }
    }
    s3m_currentbyte -= dma_bufferlen;
  }
                                         //if we have less than bufferlen to
                                         //mix then we mix the rest and call
                                         //our tick routine, if it as a division
                                         //we also call our division routine
  else {
    for(i=0;i<channels;i++){             //mix ALL channels
      if(chan[i].volume && *chan[i].pos < chan[i].end) {
				vol = (chan[i].volume * s3m_volume)/64;
				for(j=0;j<s3m_currentbyte;j++){
					*(mix_buffer+j) += vtable[*(chan[i].sdata + (WORD)*chan[i].pos)+128][vol];
					chan[i].position+=chan[i].pinc;
          if(*chan[i].pos>=chan[i].end) {
            if(chan[i].sflag&0x1) {
              chan[i].position=chan[i].offset*256L;
              chan[i].counter=0;
              chan[i].end=chan[i].rlength;
            }
            else break;
          }
        }
      }
    }
    lastbyte=s3m_currentbyte;            //if we are at a division call it
    if(s3m_currenttick >= s3m_ticksperdivision*(s3m_patterndelay+1)) {
      s3m_patterndelay=0;
      sdodiv();
			s3m_division++;
      if(s3m_pattern == s3m_pstop) {
        s3m_order++;
				s3m_division=0;
        if(s3m_order == s3m_data->orders) {
          s3m_on=FALSE;
          s3m_reset=TRUE;
        }
        else {
          s3m_pattern=s3m_data->pattern_data[s3m_data->order[s3m_order]];
					s3m_pstop=s3m_pattern+s3m_divbytes*64;
        }
      }
      s3m_currenttick=0;
    }
    s3m_currentbyte=s3m_bytespertick;    //reset current byte
    s3m_currenttick++;
    sdotick();                           //do the tick stuff
    for(i=0;i<channels;i++){             //mix the rest of ALL channels up to
                                         //bufferlen
      if(chan[i].volume && *chan[i].pos < chan[i].end) {
				vol = (chan[i].volume * s3m_volume)/64;
				for(j=lastbyte;j<dma_bufferlen;j++){
					*(mix_buffer+j) += vtable[*(chan[i].sdata + (WORD)*chan[i].pos)+128][vol];
					chan[i].position+=chan[i].pinc;
          if(*chan[i].pos>=chan[i].end) {
            if(chan[i].sflag&0x1) {
              chan[i].position=chan[i].offset*256L;
              chan[i].counter=0;
              chan[i].end=chan[i].rlength;
            }
          }
        }
      }
    }
    s3m_currentbyte-=(dma_bufferlen-lastbyte);
  }
}

/********************************************************************

  void sdodiv(void)

  Description: Handles all of the division commands at each div of
  of the s3m.

********************************************************************/
void sdodiv(void)
{                                      //local variables
  SHORT k,row,pattern_break=FALSE,position_jump=FALSE,loop=FALSE;
  static BYTE instrument,note,octave,volume,command,info;
  BYTE infox,infoy;
	DWORD rate;

	for(k=0;k<channels;k++){               //check all of the channels
		chan[k].cut=-1;
    note=*(s3m_pattern)&0x0f;            //pull note out of pattern
    octave=(*(s3m_pattern)&0xf0)>>4;     //pull octave out of pattern
    instrument=*(s3m_pattern+1);         //get the instrument too
    volume=*(s3m_pattern+2);             //and the volume
    command=*(s3m_pattern+3);            //plus the effect
		chan[k].effect=command;
    info=*(s3m_pattern+4);               //effects info...
    infox=(info&0xf0)>>4;
    infoy=info&0x0f;
		chan[k].x=info;
		if(volume!=255) chan[k].volume=volume;
    if(*(s3m_pattern)==254){             //254 means that this channel is turned
                                         //off.
			chan[k].sdata=NULL;
			chan[k].position=0;
			chan[k].counter=0;
			chan[k].end=0;
      note=255;
    }
    if(*s3mKEA virtual file.    @j�;  LINEPLAYSCR             ! � J  LISSAJOUSCR             ! � W  LOGO    INI           ����`   WINTEL  INI           t��E�  LOVE    BMP           �iX�6  LSM     DLL           �
�� �  LSMTOGL DLL           �
�� � LSMTOGL1EXE           �
�    LVIEW   INI           �`u�  MAIN    GRP           kv��0  MARBLE  PAL           Z[c�   MARBLE  BMP           d[c�k  MCIOLE  DLL             c 0  MICROSOFGRP           gvY�#  MINIFRACBMP           o7qF�  unidrv_help About GetAppCompatFlags  	  
    DeleteSpoolPage unidrv.dll  dmcolor.dll unidrv.hlp  Size Unit Brush Intensity Band  Memory  MemReserve  Number of Cartridges  Cartridge   Page Protection Left  Top Right Bottom  device windows unidrv_help  PrinterAliases icountry intl  HLP InstallExtFonts About     3.1.4 V.  GetAppCompatFlags UseDMColor   SoftFonts   
       $ 0 EngineGetGlyphBmp: Different BitmapMetrics Unidrv      Cartridge                             Cartridge   Symbol Zapf Dingbats ZapfDingbats Cartridge SoftFont                                            
     	                   Pitch    
                            �"        � �     �	�	    d d     ��    ��                         0123456789ABCDEFUNIDRV  DMCOLOR.DLL DMMONO.DLL  DISPLAY GDI KERNEL  unidrv.hlp  ForceTextBand MinMemory ResetPrinter  ����������   ����       �               ����������������������    ������   ������   ����  
 ������   ������   ��������������                                   @  Orientation              Paper Size               Paper Length             Paper Width              Scale                    Copies                   Default Source           Print Quality            Color                    Duplex                   Y Resolution             TrueType Option          Default Destination      Text Quality             Paper Quality            Job Separation                                      ��������������hX`x���� H���(P����@08p��Č����l\d|���$L���,T����D4<t@�`�H�h��� ��(p�P�x�X��0��8�L�l�D�d���,��$|�\�t�T��<��4�                @  @  � T � T m U � � m w � � m � k � w � w �3�3�3�3� o � � � � � � ��� �� ��� �"� ����"��UwU�UwU�*���������/弟�^*�������*��������w��w����������~��?�l��?����~��?��������w���w�������~����������������������������������������������  ��      ���          ���                          ���	
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 ��.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              hh�  z                 � L 	 ,(  �         �        �        � . �$  D,  p,  �                     L         .      Z �@��hh3   ��         "   ,   2          ����L         .      Z �@�hh3   ��  T   Z b   n   v   | �         ����L         .        � �hh3   ��  �   � �   �   �   � �         ����L         .      Z �@��hh3   ��  �   � �   �   �           ����L         .        � ��hh3   ��    &  6  >  DR        ����L         .      Z �@��hh3   ��  V  \d  p  z  ��        ����L         .        � ��hh3   ��  �  ��  �  �   N        ����L         .      Z �@�hh3   ��  R  X`  l  t  z          ����L 	        .        � �hh3   ��  �  ��  �  �  �          ����(            0    � ��������(                � � ��������(                Z x ��������  	    �p    Z �         *        pB                4        �x    Z           ��        ��    Z           >     	  �H    Z           H    '    �x                R                Z           R             ��   F Z   \   F Z   f    h  p    z    � �       �                �       �       	�       
�       �       �              
                            "       (       .       4       :       @       F       L       R       X       ^       d       j       p        v       !|       "�       #�       $�       %�       &�       '�       (�       )�       *�       +�       ,         -�       .�       /�       0�       1�      $    ������������������������$    ������������������������,     � � ������������������ ����,           *4>FNX������������bl����     �v����������          2 < > D E                            	         ! # % '   2 <                              % & ' (      2 <                                % & ' (      2 @                          * + , - .      2 @                           * + , - .      2 <                               	 
                        ! " # $ % & ' (      2 <                                 	 
                        ! " # $ % & ' (      2 <                              % & ' (   2 <                                % & ' (            . .   / /   0 0   1 1       ) )   * *   & &   % %   	 	   
 
                                                                                     ! !   " "   # #   $ $   ' '   ( (         %     '      A B     - / C                        Z%l     *'%l      *!%l      C      C      C      C      C                        x0      x1      @Il6R Tr P           @     @tR P6T   $%l         0     F3%c       �        
                  U      U       EG     FH     4     5     -      -       p      p       r       r      r      r      r      r v���        6DDRV Pinwriter 24 pin printers:100,360,360;100,360,360  DISABLE 
DEVICEMODE DEVGETCHARWIDTH CREATEDIBITMAP 
STRETCHDIB REALIZEOBJECT
 EXTDEVICEMODEZ SETDIBITSTODEVICE DEVICECAPABILITIES[ ENUMOBJ STRBLT ENABLE CONTROL 	DEVBITBLT OUTPUT QUERYDEVICENAMES\ PIXEL	 SCANLR 	COLORINFO 
ENUMDFONTS 
DEVINSTALL^ DEVEXTTEXTOUT ADVANCEDSETUPDIALOG] DEVICEBITMAPBITS  2.51  $ %s%.*Fs"%s" DEC PATHWORKS WinSock DLL Version 5.0                                     Wollongong %s  "%s" %02x ffnetapi.dll wsockspx.dll winsock.dll ioctlsocket WSAAsyncSelect WSAStartup WSACleanup None            PZSerial          �kLAT             �[Telnet          r`KEAlink-MSU     �\NetWare for LAT �[INT14           &[Net/1           b[CTERM           �YFirefox NOV*IX  �`NW-LAT          �[                  �	��  WVk^����^�.�����tT�~�F��^�.��D�|�F
�DV�����tV�|��j j h��h� jW�����D  �F�V�Z�Z��^_��U��V�vV�\�_��^��U��V�v�vV�\�_��^�ːU��V�v�| t�t�����t������| t�D  V�\�_��+��Z�Z^�ːU��V�v�vV�\�_��^�ːU��V�v�vV�\�_��^�ːU��V�v�v�v
�vV�\�_��^�ː�  WV�v�u3�~�v�vk��F��P�v
���@��
�t?�^�.�����]�0��u3�~�vk�P�v
��@��
�v�v
VW�]�_��� ^_�ː�~�v�v
VW�]�_��^_���  V�N�v�Z�\�G �W"�F��V��tQV�^���^�ːU��^�ù
 �������� � ��ÐU��~ t�d �3�3ң����ÐU����t�������^�G�ÐU��WV�~�=�u�u�t	V�u�/��� ^_��Ț  WV�~
}� �F
���F���)F
j�v��f�P��m?���F�3��v�F&�< |&�<}	&��C����C� �F�v��F�F�^�*�&�Ph~� +F�P�F���f��P��rE��F�G��|��v�v�Ƃf�+2��C戂g��F�P��f�Phu�	�.���N�t�_��~
 � j�v��f�P���>���F�3��v�M&�< |&�<}&��C���C� G�F�v��F�F�^�*�&�Ph~� +F�P�F���f��P���D��F��F�F
�N
���C� �F�PhF���#��W��f�Ph�	�.��^_�Ð�(Z�%�*Z?-�"Zf&�$Z?-�,ZZ�>Z  �Z�U��V�v�|  t�D   �DDt�t�t��p�/��+��D�D�D*�D(^�ːU��V�v�DDuh �\o�/���D�T�DDt(�D   � �D"�D,�L�T���L(�T*V����^��3�^�ːU���v�&��3���U��N��H|pH~HtHtHtQ�v�=���ː3��˸ �ːU��N��t��
u�^�F
�G&�ː�v�v
Q�v�j��U��FHt3��ː� �ːU��WV�~���|0 tj j j h� j�t������D0  �|. t[�~�t.�t*�t(�t�t�Bq�/��
�ЋD.�E�L�T�M�UD$3��D.�D9DtVh?-h�)��0���D  � ^_�ːj �vW���^_�ː�  WV�v�~�*�-� t� ^_�ˋD;E~�E�F��}& tG�D uA�}. ~�u ���� �^_�ː�E,;F�~�F��F�P�t�t�u*�u(�Bq�/��
�F��E.�DF��D�F�)Du�D�t��E0 ��W���3�^_��U���v�v
�v�~ t�wZ���~ZP����ːU��V�v�t�t�t�t������t�t�t
�t��
���D �ZZtV�Z��� ^�ːU��V�v�th?-h#�t����V�����tj j �t�����D  ^�ːU��F= w+��.���'��'�'�'�'(�'�'�'
((�'�'�'�'�'�'(3��ˋ^�G�˸@�ː���t���� ��ː� �ː� �ː�  V�F= v�� ��.��4(�(�(�(@(�(�(�v�F
�V�Z�Z�| tVh?-h�)������D  �ZZt�6Z�6ZVh?-h�)����
�D ^�ː��v
�0����v�C���^�ː�v
�����v�F�P�t�����t*�~��u�~� t�v��u�/���F�P�t�����u�^�ː�  V�N�N��ZZtY�ك t,�v�w��U�^����G  ���D  +��D�D� ^�˃ u�6Z�6ZQh?-h�)��J�^���
�G �^��w�����~
 t
j ��p��3�^��U���v� ��ːU��V�v�t������t��x��^��U��^�w�����U��^�w������U��^k�������ZːU��V�v�ZZt�D V�����D  � ^��U����t&��Q�^9Gth�h����.���6��6���<����  V��Z�< v���\�D�L���4��'�  ��*���Zv�^��Ȝ WV�F��F�k'k^*��d����Z w����Z t����Zh���'��d����Z���Z���Zh���'��d����Z���Z���Zh���'��d����Z���Z���Zh���'��d����Z���Zh��f�P���Z�F��t� ��d����Z��f�u1��g���t8��g� u"�й
 ��n��j�����;��u+��t�v�^ ���F�l'�~ tI�й% ��j�� �����;��u+��u� ��3��^������Z t�F�  �^�t�  �F�^_���  V�vk�*�^����Z ~���Z t���Z�^����Z� ^�ː3�^�ː�  V�vk�*�^����Z u���Z���Z�� �.�^������Z���Z^�ː� ��  WV�V�F�  ��Z�� 9W�t� �F�F�F
�F���W�V��u� �^����F�F�&9Dud�F�&�Dt[&�DHtHtHt&�<�~�&�\
&� �F�&�\�$��~�&�t
������~�&�t
�����F�&�\&�?�F�&�D��!F�u�I&�&�T���V��F��t�z��^��F���*��[w$�V9W�t�8��^�k�*ķ�Z&� �Fğ�Z&�3��^_���  WV�~ t�� +��F��F�k^*�^򋇮Z���Z���V��u�>�F�F�&9Dud&�D��#F
;�uW&�&�T���V��F�F�u�^򉿮Z���Z��F��^�&�?&�G�F�&�D��!F
V��p�/���F��F��~��~
 u!�� ��v��V��v��V��ގ�&�&�W�F��V��F�F�u� �v��b�j�\o�/�����V��u��N�F��F&�D�F
&�D�F&�DHtHt-Ht*�F�N��^�G��W�&�D
��&�T�G��W�&�D&�T���N��^�G���&�D
�G��W�&�D&�Tk^*�^򋇮Z���Z&�&�T���Z���Z�v�Ĝ�Z�F�  ���t�N��~&9u&O&����u�N��~� t�v�6�@�^����Zj �v����Z��+��F��F��vh�h~f�F�P�^����Z�������^_��3�^_���  WV��Z�~�F�V
k�*�v����Z���Z�F�V���Z���ZC���~����Z��@�v&��v����Z��Z^_�ːU��k^*Ǉ�Z  �ː�  W�F�RP���V��ujh j j h �V �.��
3�_�ˋ��^�F��G3��G�G�� �?_��U��V�v��tQ��3��D��D�D�D^��� \ �    �0?-�0?-�0?-}0?-o0?-A0?-.0?-!0?-KEAAttention KEATransferReceive KEATransferSend src\snd.c $Revision:   1.4  $ KEADisconnect KEAConnect KEAExit KEAStart SystemDefault �� \  ːU���v�^��.���/.���/� ���  WV�> \ u3�^_�ː�~
��% = ��؉F����Шt�N��� t�N��� t�N��� t�N��v�v�v��  ���u�� t
j ��� ��^_���@  V�v�}3�^�Ðj �6̕��Q����tP96ʕtJj�6̕��9����t0j j@�F�Pj�6̕��U���
j h` �F�Ph�V �.��
=@ t�j�}���6�c96ʕu�>�c t|�6̕�����u���c  �a��h?-h"4h�bhc�v����
�̕�t�F�ʕ�Ѓ~ t*j j@�F�Pj �v�����
jh �F�Ph/�V �.��
��c � � ^��NW-LAT  ��4?-    ��5?-  ��7?-    ��7?-             �9?-     :?-    �L8?-   %                   src\tasks.c $Revision:   2.76  $ �h?-h"4h�bhc3��ʕP����
�̕P��%��Ð�@  WVj �6̕�����t�� �~���c�Ў��3�� �~��j�6̕��l����j j j�6̕��p��j j@�F�Pj�6̕��x��
j �:	���~t�~u!j�6̕�� ���t��l�~�~� tb�6̕��y���u
j�����V�>̕ tOj j@�F�Pj�6̕����
�F�Pj�J#w0���F�P��/�.��j j�������j j ����t� ^_�ÐU��̕9Fuj ���U��N���>�c t�ɀ�>̕ tQ�6̕�����>ʕ tj j j�J#w0��h�@��/�.�ÐU��>̕ t�v�6̕�������  V�v*��t- t%Hu�Ht&Hu�� �.��Dt�$��c ���c�֕���|u��6Εj�^����tv�>�c uoj �6̕�����t�� 9�ct{9�cuj�6̕�����uC9�ct9�c� ���3�Q�6̕��T���V��t�v�Pj h� �tV�\��� ^�ːj�����toj �6̕��1���u]��j�#���Q��c9֕t&j �6̕��
���tj�~����6֕j ����j �6̕�����= ���P������c  3�^���H  WV�v*��t- u� Hu�� �{�ʕ�Εj j@�F�P3ɉN�QQ�����
�~� tf�^�Gu(�~��M2�ю��Ɏٹ��3����+��t����t�F�Pj h� �^�wS�_��j j@�F�Pj �F��v���\��
�~� u���c^_�ˋD�Ε�>Е uh*h�2���.��j j j h� �6ЕV�\��� ����Gu� �F�Pj@�F�Pj �O�ΕQ�����
�~��M2�ю��Ɏٹ��3����+��t����u\�F�Pj@�F�P3�VV����
�~� t,�F��V�9F�u9V�t�F�Pj@�F�Pj FV����
�~� uԋF��V�9F�u	9V�u�6Ε�6Εj �����3�^_�ːU��V�v*��t- t�&j�6̕����^�ː�D�RPj�6̕����3�^�ː�  WV�~*�= tRw
�t
,t3�^_��j�6̕�����F��/�h�j
�F�PW�/-�����F��RPj�6̕������^_��h�j
�F�PW�/-��^_���
  V�v�F� �F�  �*��t- u�� Hu�HHHu�A�D�D�Е�̕�F��>ҕ t�F�Pj h� �6ҕV�\���>ԕ t�F�Pj h� �6ԕV�\���ʕ9Εt!j j j j �6Ε�����
�F��u�L�Dj �v������F��V��t�v�Pj h� �tV�\����L�ʕ9Εt�v���+���>ҕ t�F�Pj h� �6ҕV�\���>ԕ to�F�Pj h� �6ԕV�\���X�6Εj������t<�>�c t�>�c � ��3�Q�6̕�����F��V��t�v�Pj h� �t묐� ^���Е  3�^�ːU��V�v*�= tw 
�t
,t3�^�ː�D�ҕ3�^�ː�ҕ  3�^�ːU��V�v*�= tw 
�t
,t3�^�ː�D�ԕ3�^�ː�ԕ  3�^�ːU��V�vhT2j h� �tV�\��3�^�ː�@  j j@�F�Pj�6̕��{��
j �6̕��7���t0j�6̕��%���tj h`�F�Ph�V �.��
=@ u3��˸ �ː�>̕ t,j �6̕������tj�\����6̕��t���̕  ����ːU��V�v*��t- tHt	����c^�ˡ�c9Dt�>�c��أ�c3�^�ː�>�c t�>�c �>̕ tj������U��^*��t- t+�W�j �6̕��G���tj�6̕��6���t4� �ːj �6̕�����tj����j �6̕�����uj�� 3���U��WV�v*��t- t?�a�j�6̕��������u
�| u�L ��tj �6̕�����u+� ^_��j �6̕�����tj j j�6̕����3�^_��U��V�v*��t- t<�^�| uXj�6̕��S���u�L �@j �6̕��;���u.�L� ^��j �6̕�����tj j j�6̕��!��3�^�ː�@  �>̕ u�� �~ td�>�c ]j j@�F�Pj�6̕����
j�6̕������t�F�Pj5j �lv�/��h?-h�=� ��F�Pj7j �lv�/��h?-h>�a��>�c t3j j@�F�Pj �6�c����
�F�Pj:j �lv�/���>�c ~#3���$�>ʕ u#j j j8j �lv�/���>�c ݸ>�?-RPj6�j j j j �lv�/��j j j4j#�6�a��w�/�Ðj�S���ːU��F
�tHt�ː�>�c u;�F��c�ː�F9�cu)3���cP�6̕����= ���P����h?-h�=��s�/��h?-h�=�Zs�/���>ʕ ujj hT2�*��>�c t�>�c � ��3�jj Q�6̕��F��RP��/-����@  WV�v*�- tHt'Hu�� Hu�g�j j@hޕj�6̕��P��
�n�Du� �ޕ�RPj	�6̕������c �6̕��`���u��c  � ^_�ˍ~���c�Ў��3�� �~��Pj@�F�Pj�6̕�����
�F�Pj�J#w0���F�P��/�.��j j������c  �ܕ � �|u�� �>�c u���c �ޕ�RPj	�6̕��c���6̕�����uPPPh� �6 �V�\���C��~���c�Ў��3�� �~��Pj@�N�Qj�6̕��2��
�F�Pj�J#w0���F�P��/�.��j j��������c  �#��$� j �6̕������t�~��t�F�P�ʃ�� �F�$�F��F�$��F��F�� ��؊F�&�F��^��F�����F������&�G�^�������&��F�F������&�G�^�������&�G�F�>� t-�F�P�$ʃ��F�P�ʃ��~��t�~��t�F�P�ʃ��F�$��F��F�$�F��F�� P�F�� P�v�h�q��
�F��F�� =� u�=� t+=� ta=� u���=� u�=� u�=� u���^��デ��'ǭ�Z�M�>�,����ƪƦƚƋ�|�_�S�ET�=�.�����V��V��V��V����������VŵřŊ�l�]�I�:�(�$� ������������������ļĶįīĦĝė�h�Y�E�6>��?��~��~(�F�P�ƃ�j �F�P�VŃ��F��
 ���Ǉ	  ��^��デ��~���/�F��
 ��؃�	 t+�F��
 ���Ǉ	  �F�P�,ƃ�j �F�P��ă��� �F��
 ��V��؉��F�� P�F��
 ���X���F�� P�F��
 ���X���F� P�F��
 ���X���>� u�F��
 ���Ǉ  �F��
 ���Ǉ	 �~�	}v�F�P�F�P��Ã���� P�F��
 ���X��� ������F��~�?~�F�? �F�P�F�P�-ă���^�&�� � ��P�F�P�����F�P��ă��C�^��デ��7�^��デ��+�^������� �^��������^��デ��	��  � �^���� tO�F�P�F������&�G�v�����&�wP�`F  ���^������V��F��    �^������^����� }���
�� w������^���)���F���&�G;F�~��^��<j<m<p<s<v<U���Vj jP�    ���V�F�F�F�uhf�v�v
�    ��3�3����^�&�GJ  &�GH  �^�&�GN  &�GL  �^�&�GF  hu�v�v�    ���V��F��F�F�u�v�vhx�v�v
�    ��3�3��i�v��v�jj����P�    ��Ɔ�� h�����P�    ���t'h��v�v
�    ���v��v��    ��3�3���v��v��G  ���V��F��~� |>�~�� v5�v��v�    ��h��v�v
�    ���v��v��    ��3�3���v��v���F  ���F�~� t;�~�t5�v��v�    ��h��v�v
�    ���v��v��    ���.��V��V����VϾTϩVϛVǒωV�fT�QV�CV�:�-V	�$�V��V����V��ΑVƈ�qV�bT�`T�^T�\T�ZT�XT�G�@�<�1�(����V����T������ŴŭŢŗŋ��\�L�"���������ļħĒ�d�S�;�-� b��C�3�3��e�^�F�&��v��v���F  ���F�~�|�~� ~8�v��v�    ���v�h��v�v
�    ��
�v��v��    ��3�3���^�F�&�G�v��v���F  ���F�F��3�+��^�&�G�F�  ��v��v�jj����P�    ��Ɔ�� h�����P�    ���t8�v��v�    ���v�h��v�v
�    ��
�v��v��    ��3�3��j�v��v��G  ���V��F��v��v��    ���^����v��&�T&�D�F����^��&�G&Gu[��N��F����^��&�w&�w�    ���~� u��v��v�    ��h �v�v
�    ���v��v��    ��3�3��� �v��v��v�j�F����^��&�w&�w�    ���F�  �F��F�V�;F�wdr;V�s]��N��F����^��&�w&�w�    ���~� u��v��v�    ���v�h �v�v
�    ��
�v��v��    ��3�3��(�F��^�&�G;F�~�A��v��v��    ���V�F�� ^��U���V�F�  �^^�&�� 3��^
&�W&�%� �� �tL�^
&�'&�g �F��^
&�W&���    �^^�&��^�� ��P��R�[Y���v
&�\&��F��u��F�@� ^��U���v�v�    ����P�v�v�    ��ZЋ�� ]�U����F�  �F�  �v�v�    ��� �F�  �F��F�  �/�V��F���    PR�v�v�    ��� Z[؃� �V��^��F��~�|ˋV��F�� ��U����F�  �F�  �� �� �F��V���F��V��F��V��^�&�G"&�W �F��V��F�F�t�^�&�G&�W;Fu�;VuƋF�F�u� �� �^�&�G �^��� ��ǢǞ�dV�WV�6V�V��VκV�_V�9V�+V�"�V�V��V͛V͍Vń�{V�gV�V�T��V��V����V��V	ĸ̪V�xT�YV�KV�B�6V�T���G�&�G  &�G  �F�F�u�^�&�G"&�W �� �� �h�^�&�G"&�W �^�&�G"&�W �^�&�G&�W�F��V��5�^�&�G&�W�F��V��^�&�G �^�&�G  &�G  �F��V�F��V��F�F�u�� ��U����F�  ��F��~�2}�F��( ��  �؎�&�� u��~�2u3�3��� �F��( ��  �F�  �F��^�&�G  &�  �^�&�G  &�G �^�&�G
  &�G  �F��V���	�^�&�G&�W�^�&�G �^�&�G  �^�&�G�^�&�G�^��� �� &�G&�W�� ��  �^�&�G  &�G  �^�&�G"  &�G   �^�&�G&  &�G$  �V��F�� ��U�����>� |U�� �� �F��V���^�&�G"&�W �F��V��F�F�t�^�&�G &G"t�^�&�_ &��u��^�&�w&�w�������V��F��F�F�u�3�3��y�^��F�V&�G&��F�V
��  �^�&�G&�W�~u�^�&�G�^�&�_&��^��F&�G�^��� �� &�G"&�W �F��V��� �� �� ��^�&�W&�G� ��U�����v�v��K  ���V��F��F�F�u�3�3�� ����V��F��F�F�u�3�3�� �^��F�V&�G&��F�V
��  �^�&�G&�W�~u�^�&�G�^�&�_&��^��F&�G��^�&�G&�W�F��V��^�&�G&Gu��^��F��V�&�G&�W��^�&�W&�G� ��U����v�v��K  ���V��F��F�F�u3���^��F�V
&�G&&�W$� � ��U����F�  ��F��~�2}#�F��( ��  �؎�&�� &�� ;Fu�;Vuԃ~�2u3�3���F��( ��    � ��U����v�v���1�s ��T��T��T��T˷T�gTΚT�z�v�r�a�]ŨŤŞ�[�V�J�F��T��TĻTȲT�%�!ɠ�K��V��F��F�F�u� �^
��v� ��.���L�^�&�G
  &�G  �^�&�G�i�v�v�E����Z�^�&�G �P�^�&�G�F�^�&�G
  &�G  �5�^��F&�G�)�^�&�_�F&���^��F&�G��^��F&�G�� ��L-L<LFLPLaLmL|L�LU��^��w;��.���L��  ��  �(��   ��  ���   ���  �
��  �� ]˼L�L�L�L�LU��^��w;��.��HM�� �� �(��  �� ���  ��� �
�� �� ]�MM,M4M<MU���V�F� j h��    ���V�F�F�F�uhC �v�v
�    ��3�3���^�&Ǉ�  &Ǉ�  �^�&Ǉ�  &Ǉ�  �^�&Ǉ�  hQ �v�v�    ���V��F��F�F�u-�v��v�    ���v�vhT �v�v
�    ��3�3��j j h8�v��v��    ��
�v��v�jj�F�P�    ���F� hh �F�P�    ���u�F� �6hm �F�P�    ���u�F� �hr �F�P�    ���u�F� �v��v��    ���v��v�jj�v��v�    ���^�&Ƈ[ �F�  ���v��v�jj�F�� ��V�Ѓ��v�R�    ���v��v��    ����P�v��v��    ��Z���F����^��&����v��v��    ��% �F��~�~�n��^�^��F�&����v��v��    ���^�^�&����v��v��    ����P�v��v��    ��Z���F����^��&���v��v��    ����P�v��v��    ��Z���F����^��&��T�F����^��&��Tu�F����^��&ǇT  �Ȝ��VϯVύV�{V�bV�6V�V�V��VνVΥVΎV	Ɔ�rV	�j�VV	�N�AV�*V�V���V��V��͕VŌ�uV�aT�_T�]T�[T�YT�O�G�?�7�1�)�#�T�T�T�	T�T�T����������������TĹTķTĵTĳTıTįTĭTīTĩT�#T���OF����^��&���V����^��&�T�V����^��&;��w� �F����^��&��T�V����^��&;��v1�F����^��&����V����^��&��T�F����^��&Ǉ  �<�F����^��&��T�V����^��&��V����^��&+���V����^��&)��F��F�t�^�&��[�F��F�;F�}����v��v��    ���^�&����v��v��    ���v��v�h� j�F���v�P�    ���~�u'�v��v�jj�F�V�v�P�    ���^�&ƇZ �hw �F�V�v�P�    ���^�&Ƈ� �F�  �+�^�^�&����^�&:��v�^�^�&����^�&����F��^�&���� ;F���F�  ��F����^��&Ǉ]  &Ǉ[  �F��~�� |��F�  � j h �    ���^����v��&��]&��[�F����^��&��[&�]uV�F�  � �F����^��&��]&��[�    ���F��F�;F�|�h| �v�v
�    ���v��v�    ��3�3����v��v�h j�F����^��&��]&��[�    ���F��^�&���� ;F�|�4��F�  ��F����^��&Ǉ^  &Ǉ\  �F��~� |��F�  �:�F����^��&Ǉ^  &Ǉ\  �F����^��&��� u�	�F����^��&���@j P�    ���^����v��&��^&��\�F����^��&��\&�^t� �F�  � �F����^��&��]&��[�    ���F��^�&���� ;F�}��F�  � �F����^��&��^&��\�    ���F��F�;F�|�h� �v�v
�    ���v��v�    ��3�3��X�v��v��F����^��&���j�F����^���L ��V��VǻϧV�qV�VΏV�`V�RV�I�5V��V�\V�O�;V�V��V��V}��S�&��^&��\�    ���F��F�;F�}���v��v��    ���V�F�� ^��U���2h� �v�v�    ���V��F��F�F�u�^
&�G  &� 3�3���v��v�jj�F�P�    ���F� �v��v�jj�F�P�    ���v��v�jj�F�P�    ���F� h� �F�P�    ���t�v��v��    ��3�3���v��v�jj�F�P�    ���F� �v��v�jj�F�P�    ���~� rw�~�� v
�F�  �F�� �v��v�jj�F�P�    ���v��v�jj�F�P�