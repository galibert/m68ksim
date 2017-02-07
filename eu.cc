#include "eu.h"

void eu(cstate &s)
{

  /* top
    (s.ir & 0x003a) == 0x0038 && (s.ir & 0xf038) != 0xe038
    (s.ir & 0x003e) == 0x003a && (s.ir & 0xf038) != 0xe038
    (s.ir & 0xf000) != 0x5000 && (s.ir & 0xf100) != 0x0000
    nc
    (s.ir & 0xfff0) == 0x4e60
    nc
    nc
    (s.ir & 0xff00) == 0x6100 || (s.ir & 0xff00) == 0x4e00 || (s.ir & 0xffc0) == 0x4840
    ic
    ic
(s.ir & 0x0200) == 0x0200
(s.ir & 0x0400) == 0x0400
(s.ir & 0x0800) == 0x0800
(s.ir & 0xf1f8) == 0xc188
(s.ir & 0xa138) == 0x8108
(s.ir & 0xc138) == 0x8108
(s.ir & 0x90c0) == 0x90c0
(s.ir & 0xf1c0) == 0x41c0
(s.ir & 0xd000) == 0x1000
(s.ir & 0xe000) == 0x2000
(s.ir & 0x01c0) == 0x0000
(s.ir & 0xfb80) == 0x4880
(s.ir & 0xffb8) == 0x48a0

  */
  bool n6147 = true;

  if(s.eu_p) {
    s.euc_hd_sense_amp_keep = !ln(s, 55);
    s.euc_ha_sense_amp_keep = !ln(s, 54);
    s.euc_auh_aluh_w = ln(s, 48);

    s.eu_alul_ab_in = s.eu_aluh_ab_in = ln(s, 51, 50, 49) == 6;
    s.eu_aluh_cst_val = !ln(s, 50);
    s.eu_alul_bit_2p  = !ln(s, 50);
    s.eu_alul_bit_1   = !ln(s, 49);
    s.eu_alul_bit_0   = ln(s, 51, 50) != 1;
    s.eu_alul_add1    = !(ln(s, 51) && ((ln(s, 67, 66) == 3) || s.n3225 ? ln(s, 49) : !ln(s, 50)));
    s.eu_hl_a_connect = ln(s, 53);
    s.eu_hl_d_connect = ln(s, 52);
    s.eu_ld_a_connect = !ln(s, 32) && n6147;
    s.eu_ld_d_connect = ln(s, 33);

    s.disp = ln(s, 42, 41, 40, 39);

    s.eu_mvm_step    = s.disp == 0xa;                        // 0101
    s.disp2          = s.disp == 0xb;                        // 0100
    s.trace_srt_w    = s.disp == 0x1;                        // 1110
    s.trace_clear_w  = s.disp == 0xe;                        // 0001
    s.euc_ibuf_rw    = s.disp == 0xc;                        // 0011
    s.euc_ibuf_d     = (s.disp & 0xd) == 0x4;                // 10x1
    s.euc_ibuf_a     = (s.disp & 0xb) == 0x8;                // 0x11
    s.euc_ibuf_to_ib = s.disp == 0x2;                        // 1101
    s.euc_ib_to_ibuf = (s.disp & 0x1) == 0x1 && s.disp != 0xf;
    s.ipl_sr_w       = s.disp == 0x6;                        // 1001
    s.srt_clear_w    = s.disp == 0xf;
    s.eu_ib_sr_r     = s.disp == 0x7;
    s.disp13         = s.disp == 0x2 && s.n5283;             // 1101
    s.disp14         = s.disp == 0x5;
    s.disp15         = (s.disp & 0x7) == 0x1;                // x110
    s.disp16         = s.disp == 0x9;                        // 0110
    s.ib_ib1_w       = (s.disp & 0x3) == 0x1;                // xx10
    s.ib1_status_w   = s.disp == 0xd;                        // 0010
  }

  s.eu_auh_aluh_w = s.eu_w && s.euc_auh_aluh_w;
  s.eu_auh_a_w    = s.eu_r && (ln(s, 47, 46) == 1);
  s.eu_auh_d_w    = s.eu_r && (ln(s, 47, 46) == 2);
  s.eu_pch_auh_w  = s.eu_r && (ln(s, 47, 46) == 3);
  s.eu_aobh_d_w   = s.eu_r && (ln(s, 64, 63) == 1);
  s.eu_aobh_a_w   = s.eu_r && (ln(s, 64, 63) == 2);
  s.eu_aobh_auh_w = s.eu_r && (ln(s, 64, 63) == 3);




  if(!s.eu_ld_sense_amp_keep) {
    s.eu_hd_sense_amp_keep = false;
    s.eu_ha_sense_amp_keep = false;
  } else {
    s.eu_hd_sense_amp_keep = s.euc_hd_sense_amp_keep;
    s.eu_ha_sense_amp_keep = s.euc_ha_sense_amp_keep;
  }

  if(s.eu_p) {
    s.eu_ah = 0xffff;
    s.eu_dh = 0xffff;
    s.eu_al = 0xffff;
    s.eu_dl = 0xffff;
    s.eu_ad = 0xffff;
    s.eu_dd = 0xffff;

  } else {

    if(!s.eu_hd_sense_amp_keep) {
      if(s.eu_r18h_dbc)	s.eu_dh = s.eu_r18h;
      if(s.eu_r17h_dbc)	s.eu_dh = s.eu_r17h;
      if(s.eu_r16h_dbc)	s.eu_dh = s.eu_r16h;
      if(s.eu_r15h_dbc)	s.eu_dh = s.eu_r15h;
      if(s.eu_r14h_dbc)	s.eu_dh = s.eu_r14h;
      if(s.eu_r13h_dbc)	s.eu_dh = s.eu_r13h;
      if(s.eu_r12h_dbc)	s.eu_dh = s.eu_r12h;
      if(s.eu_r11h_dbc)	s.eu_dh = s.eu_r11h;
      if(s.eu_r10h_dbc)	s.eu_dh = s.eu_r10h;
      if(s.eu_r9h_dbc)  s.eu_dh = s.eu_r9h;
      if(s.eu_r8h_dbc)  s.eu_dh = s.eu_r8h;
      if(s.eu_r7h_dbc)  s.eu_dh = s.eu_r7h;
      if(s.eu_r6h_dbc)  s.eu_dh = s.eu_r6h;
      if(s.eu_r5h_dbc)  s.eu_dh = s.eu_r5h;
      if(s.eu_r4h_dbc)  s.eu_dh = s.eu_r4h;
      if(s.eu_r3h_dbc)  s.eu_dh = s.eu_r3h;
      if(s.eu_r2h_dbc)  s.eu_dh = s.eu_r2h;
      if(s.eu_r1h_dbc)  s.eu_dh = s.eu_r1h;
      if(s.eu_r0h_dbc)  s.eu_dh = s.eu_r0h;
      if(s.eu_pch_dbc)	s.eu_dh = s.eu_pch;
    }

    if(!s.eu_ha_sense_amp_keep) {
      if(s.eu_r18h_abc)	s.eu_ah = s.eu_r18h;
      if(s.eu_r17h_abc)	s.eu_ah = s.eu_r17h;
      if(s.eu_r16h_abc)	s.eu_ah = s.eu_r16h;
      if(s.eu_r15h_abc)	s.eu_ah = s.eu_r15h;
      if(s.eu_r14h_abc)	s.eu_ah = s.eu_r14h;
      if(s.eu_r13h_abc)	s.eu_ah = s.eu_r13h;
      if(s.eu_r12h_abc)	s.eu_ah = s.eu_r12h;
      if(s.eu_r11h_abc)	s.eu_ah = s.eu_r11h;
      if(s.eu_r10h_abc)	s.eu_ah = s.eu_r10h;
      if(s.eu_r9h_abc)  s.eu_ah = s.eu_r9h;
      if(s.eu_r8h_abc)  s.eu_ah = s.eu_r8h;
      if(s.eu_r7h_abc)  s.eu_ah = s.eu_r7h;
      if(s.eu_r6h_abc)  s.eu_ah = s.eu_r6h;
      if(s.eu_r5h_abc)  s.eu_ah = s.eu_r5h;
      if(s.eu_r4h_abc)  s.eu_ah = s.eu_r4h;
      if(s.eu_r3h_abc)  s.eu_ah = s.eu_r3h;
      if(s.eu_r2h_abc)  s.eu_ah = s.eu_r2h;
      if(s.eu_r1h_abc)  s.eu_ah = s.eu_r1h;
      if(s.eu_r0h_abc)  s.eu_ah = s.eu_r0h;
      if(s.eu_pch_abc)	s.eu_ah = s.eu_pch;
    }

    if(!s.eu_ld_sense_amp_keep) {
      if(s.eu_r9l_abc)  s.eu_ah = s.eu_r9l;
      if(s.eu_r9l_dbc)  s.eu_dh = s.eu_r9l;
      if(s.eu_r8l_abc)  s.eu_ah = s.eu_r8l;
      if(s.eu_r8l_dbc)  s.eu_dh = s.eu_r8l;
      if(s.eu_r7l_abc)  s.eu_ah = s.eu_r7l;
      if(s.eu_r7l_dbc)  s.eu_dh = s.eu_r7l;
      if(s.eu_r6l_abc)  s.eu_ah = s.eu_r6l;
      if(s.eu_r6l_dbc)  s.eu_dh = s.eu_r6l;
      if(s.eu_r5l_abc)  s.eu_ah = s.eu_r5l;
      if(s.eu_r5l_dbc)  s.eu_dh = s.eu_r5l;
      if(s.eu_r4l_abc)  s.eu_ah = s.eu_r4l;
      if(s.eu_r4l_dbc)  s.eu_dh = s.eu_r4l;
      if(s.eu_r3l_abc)  s.eu_ah = s.eu_r3l;
      if(s.eu_r3l_dbc)  s.eu_dh = s.eu_r3l;
      if(s.eu_r2l_abc)  s.eu_ah = s.eu_r2l;
      if(s.eu_r2l_dbc)  s.eu_dh = s.eu_r2l;
      if(s.eu_r1l_abc)  s.eu_ah = s.eu_r1l;
      if(s.eu_r1l_dbc)  s.eu_dh = s.eu_r1l;
      if(s.eu_r0l_abc)  s.eu_ah = s.eu_r0l;
      if(s.eu_r0l_dbc)  s.eu_dh = s.eu_r0l;
      if(s.eu_pcl_abc)	s.eu_ah = s.eu_pcl;
      if(s.eu_pcl_dbc)	s.eu_dh = s.eu_pcl;

      if(s.eu_r8d_abc)  s.eu_ah = s.eu_r8d;
      if(s.eu_r8d_dbc)  s.eu_dh = s.eu_r8d;
      if(s.eu_r7d_abc)  s.eu_ah = s.eu_r7d;
      if(s.eu_r7d_dbc)  s.eu_dh = s.eu_r7d;
      if(s.eu_r6d_abc)  s.eu_ah = s.eu_r6d;
      if(s.eu_r6d_dbc)  s.eu_dh = s.eu_r6d;
      if(s.eu_r5d_abc)  s.eu_ah = s.eu_r5d;
      if(s.eu_r5d_dbc)  s.eu_dh = s.eu_r5d;
      if(s.eu_r4d_abc)  s.eu_ah = s.eu_r4d;
      if(s.eu_r4d_dbc)  s.eu_dh = s.eu_r4d;
      if(s.eu_r3d_abc)  s.eu_ah = s.eu_r3d;
      if(s.eu_r3d_dbc)  s.eu_dh = s.eu_r3d;
      if(s.eu_r2d_abc)  s.eu_ah = s.eu_r2d;
      if(s.eu_r2d_dbc)  s.eu_dh = s.eu_r2d;
      if(s.eu_r1d_abc)  s.eu_ah = s.eu_r1d;
      if(s.eu_r1d_dbc)  s.eu_dh = s.eu_r1d;
      if(s.eu_r0d_abc)  s.eu_ah = s.eu_r0d;
      if(s.eu_r0d_dbc)  s.eu_dh = s.eu_r0d;
    }

    if(s.ib_ib1_w) {
      if(s.eu_r)
	s.ib = 0xffff;
      else if(s.eu_w) {
	if(s.ib1_status_w)
	  s.ib = 0x0000;
	else
	  s.ib = 0x0000;
      }
    }
    if(s.euc_ib_to_ibuf && s.eu_w)
      s.ibuf = s.ib;

    if(!s.euc_ibuf_rw && s.eu_r) {
      if(s.euc_ibuf_d)
	s.eu_dl = s.ibuf;
      if(s.euc_ibuf_a)
	s.eu_al = s.ibuf;
    }

    u32 alul = s.eu_dl
      + (s.eu_alul_ab_in ? s.eu_al :
	 (s.eu_alul_bit_0  ? 0 : 0x0001) |
	 (s.eu_alul_bit_1  ? 0 : 0x0002) |
	 (s.eu_alul_bit_2p ? 0 : 0xfffc))
      + (s.eu_alul_add1 ? 0 : 1);

    s.eu_alul = alul;
    s.eu_aluh = s.eu_dh + (s.eu_aluh_ab_in ? s.eu_ah :
			   s.eu_aluh_cst_val ? 0 : 0xffff) + (alul & 0x10000 ? 1 : 0);

    if(s.eu_auh_aluh_w) {
      s.eu_auh = s.eu_aluh;
      s.eu_aul = s.eu_alul;
    }
    if(s.eu_auh_a_w) {
      s.eu_al = s.eu_aul;
      s.eu_al = s.eu_aul;
    }
    if(s.eu_auh_d_w) {
      s.eu_dh = s.eu_auh;
      s.eu_dl = s.eu_aul;
    }

    if(s.eu_aobh_auh_w) {
      s.eu_aobh = s.eu_auh;
      s.eu_aobl = s.eu_aul;
    }
    if(s.eu_aobh_a_w) {
      s.eu_aobl = s.eu_al;
      s.eu_aobl = s.eu_al;
    }
    if(s.eu_aobh_d_w) {
      s.eu_aobh = s.eu_dh;
      s.eu_aobl = s.eu_dl;
    }

    if(s.eu_pch_auh_w) {
      s.eu_pch = s.eu_auh;
      s.eu_pcl = s.eu_aul;
    }

    if(s.eu_aobh_auh_w)
      s.eu_aobh = s.eu_auh;
    if(s.eu_aobh_a_w)
      s.eu_aobh = s.eu_ah;
    if(s.eu_aobh_d_w)
      s.eu_aobh = s.eu_dh;

    if(s.eu_aobh_r)
      s.eu_ah = s.eu_aobh;


    if(!s.eu_p && !s.euc_hd_sense_amp_keep && !(s.eu_dl & 0x8000))
      s.eu_dh = 0x0000;
    if(!s.eu_p && !s.euc_ha_sense_amp_keep && !(s.eu_al & 0x8000))
      s.eu_ah = 0x0000;


    if(s.eu_hl_a_connect)
      if(s.eu_ld_a_connect)
	s.eu_ad = s.eu_al = s.eu_ah = s.eu_ad & s.eu_al & s.eu_ah;
      else
	s.eu_al = s.eu_ah = s.eu_al & s.eu_ah;
    else if(s.eu_ld_a_connect)
      s.eu_ad = s.eu_al = s.eu_ad & s.eu_al;

    if(s.eu_hl_d_connect)
      if(s.eu_ld_d_connect)
	s.eu_dd = s.eu_dl = s.eu_dh = s.eu_dd & s.eu_dl & s.eu_dh;
      else
	s.eu_dl = s.eu_dh = s.eu_dl & s.eu_dh;
    else if(s.eu_ld_d_connect)
      s.eu_dd = s.eu_dl = s.eu_dd & s.eu_dl;

    if(s.euc_ibuf_rw && s.eu_w) {
      if(s.euc_ibuf_d)
	s.ibuf = s.eu_dl;
      if(s.euc_ibuf_a)
	s.ibuf = s.eu_al;
    }
    if(s.euc_ibuf_to_ib)
      s.ib = s.ibuf;

    if(s.eu_hd_sense_amp_keep) {
      if(s.eu_r18h_dbc)	s.eu_r18h = s.eu_dh;
      if(s.eu_r17h_dbc)	s.eu_r17h = s.eu_dh;
      if(s.eu_r16h_dbc)	s.eu_r16h = s.eu_dh;
      if(s.eu_r15h_dbc)	s.eu_r15h = s.eu_dh;
      if(s.eu_r14h_dbc)	s.eu_r14h = s.eu_dh;
      if(s.eu_r13h_dbc)	s.eu_r13h = s.eu_dh;
      if(s.eu_r12h_dbc)	s.eu_r12h = s.eu_dh;
      if(s.eu_r11h_dbc)	s.eu_r11h = s.eu_dh;
      if(s.eu_r10h_dbc)	s.eu_r10h = s.eu_dh;
      if(s.eu_r9h_dbc)	s.eu_r9h = s.eu_dh;
      if(s.eu_r8h_dbc)	s.eu_r8h = s.eu_dh;
      if(s.eu_r7h_dbc)	s.eu_r7h = s.eu_dh;
      if(s.eu_r6h_dbc)	s.eu_r6h = s.eu_dh;
      if(s.eu_r5h_dbc)	s.eu_r5h = s.eu_dh;
      if(s.eu_r4h_dbc)	s.eu_r4h = s.eu_dh;
      if(s.eu_r3h_dbc)	s.eu_r3h = s.eu_dh;
      if(s.eu_r2h_dbc)	s.eu_r2h = s.eu_dh;
      if(s.eu_r1h_dbc)	s.eu_r1h = s.eu_dh;
      if(s.eu_r0h_dbc)	s.eu_r0h = s.eu_dh;
      if(s.eu_pch_dbc)	s.eu_pch = s.eu_dh;
    }

    if(s.eu_ha_sense_amp_keep) {
      if(s.eu_r18h_abc)	s.eu_r18h = s.eu_ah;
      if(s.eu_r17h_abc)	s.eu_r17h = s.eu_ah;
      if(s.eu_r16h_abc)	s.eu_r16h = s.eu_ah;
      if(s.eu_r15h_abc)	s.eu_r15h = s.eu_ah;
      if(s.eu_r14h_abc)	s.eu_r14h = s.eu_ah;
      if(s.eu_r13h_abc)	s.eu_r13h = s.eu_ah;
      if(s.eu_r12h_abc)	s.eu_r12h = s.eu_ah;
      if(s.eu_r11h_abc)	s.eu_r11h = s.eu_ah;
      if(s.eu_r10h_abc)	s.eu_r10h = s.eu_ah;
      if(s.eu_r9h_abc)	s.eu_r9h = s.eu_ah;
      if(s.eu_r8h_abc)	s.eu_r8h = s.eu_ah;
      if(s.eu_r7h_abc)	s.eu_r7h = s.eu_ah;
      if(s.eu_r6h_abc)	s.eu_r6h = s.eu_ah;
      if(s.eu_r5h_abc)	s.eu_r5h = s.eu_ah;
      if(s.eu_r4h_abc)	s.eu_r4h = s.eu_ah;
      if(s.eu_r3h_abc)	s.eu_r3h = s.eu_ah;
      if(s.eu_r2h_abc)	s.eu_r2h = s.eu_ah;
      if(s.eu_r1h_abc)	s.eu_r1h = s.eu_ah;
      if(s.eu_r0h_abc)	s.eu_r0h = s.eu_ah;
      if(s.eu_pch_abc)	s.eu_pch = s.eu_ah;
    }

    if(!s.eu_ld_sense_amp_keep) {
      if(s.eu_r9l_abc)  s.eu_r9l = s.eu_ah;
      if(s.eu_r9l_dbc)  s.eu_r9l = s.eu_dh;
      if(s.eu_r8l_abc)  s.eu_r8l = s.eu_ah;
      if(s.eu_r8l_dbc)  s.eu_r8l = s.eu_dh;
      if(s.eu_r7l_abc)  s.eu_r7l = s.eu_ah;
      if(s.eu_r7l_dbc)  s.eu_r7l = s.eu_dh;
      if(s.eu_r6l_abc)  s.eu_r6l = s.eu_ah;
      if(s.eu_r6l_dbc)  s.eu_r6l = s.eu_dh;
      if(s.eu_r5l_abc)  s.eu_r5l = s.eu_ah;
      if(s.eu_r5l_dbc)  s.eu_r5l = s.eu_dh;
      if(s.eu_r4l_abc)  s.eu_r4l = s.eu_ah;
      if(s.eu_r4l_dbc)  s.eu_r4l = s.eu_dh;
      if(s.eu_r3l_abc)  s.eu_r3l = s.eu_ah;
      if(s.eu_r3l_dbc)  s.eu_r3l = s.eu_dh;
      if(s.eu_r2l_abc)  s.eu_r2l = s.eu_ah;
      if(s.eu_r2l_dbc)  s.eu_r2l = s.eu_dh;
      if(s.eu_r1l_abc)  s.eu_r1l = s.eu_ah;
      if(s.eu_r1l_dbc)  s.eu_r1l = s.eu_dh;
      if(s.eu_r0l_abc)  s.eu_r0l = s.eu_ah;
      if(s.eu_r0l_dbc)  s.eu_r0l = s.eu_dh;
      if(s.eu_pcl_abc)	s.eu_pcl = s.eu_ah;
      if(s.eu_pcl_dbc)	s.eu_pcl = s.eu_dh;

      if(s.eu_r8d_abc)  s.eu_r8d = s.eu_ah;
      if(s.eu_r8d_dbc)  s.eu_r8d = s.eu_dh;
      if(s.eu_r7d_abc)  s.eu_r7d = s.eu_ah;
      if(s.eu_r7d_dbc)  s.eu_r7d = s.eu_dh;
      if(s.eu_r6d_abc)  s.eu_r6d = s.eu_ah;
      if(s.eu_r6d_dbc)  s.eu_r6d = s.eu_dh;
      if(s.eu_r5d_abc)  s.eu_r5d = s.eu_ah;
      if(s.eu_r5d_dbc)  s.eu_r5d = s.eu_dh;
      if(s.eu_r4d_abc)  s.eu_r4d = s.eu_ah;
      if(s.eu_r4d_dbc)  s.eu_r4d = s.eu_dh;
      if(s.eu_r3d_abc)  s.eu_r3d = s.eu_ah;
      if(s.eu_r3d_dbc)  s.eu_r3d = s.eu_dh;
      if(s.eu_r2d_abc)  s.eu_r2d = s.eu_ah;
      if(s.eu_r2d_dbc)  s.eu_r2d = s.eu_dh;
      if(s.eu_r1d_abc)  s.eu_r1d = s.eu_ah;
      if(s.eu_r1d_dbc)  s.eu_r1d = s.eu_dh;
      if(s.eu_r0d_abc)  s.eu_r0d = s.eu_ah;
      if(s.eu_r0d_dbc)  s.eu_r0d = s.eu_dh;
    }
  }
}
