#include "simpletools.h"
#include "fdserial.h"
#include "abdrive.h"
#include "simpletext.h"
 
#define emic_tx 5 // Serial output (connects to Emic 2 SIN)
#define emic_rx 6 // Serial input (connects to Emic 2 SOUT)
fdserial *xbee;

int main() {
  xbee = fdserial_open(9, 8, 0, 9600);

  fdserial *Emic2 = fdserial_open(emic_rx, emic_tx, 0, 9600);
  fdserial_txChar(Emic2, '\n');

  char c;
 
  // actions carried out by given verbal commands
  while (1) {
    c = fdserial_rxChar(xbee);
    if (c != -1) {
      switch (c) {
      case 'A': // forward
        drive_goto(50, 50);
        pause(10);
        break;
      case 'B': // back
        drive_goto(-50, -50);
        pause(10);
        break;
      case 'C': // left
        drive_goto(-25, 26);
        drive_goto(50, 50);
        pause(10);
        break;
      case 'D': // right
        drive_goto(26, -25);
        drive_goto(50, 50);
        pause(10);
        break;
      case 'E': // fed, spins
        while (fdserial_rxCheck(Emic2) != ':');
        dprint(Emic2, "sYum. Delicious.\n");
        drive_goto(150, 0);
        pause(50);
        break;
      case 'F': // butts
        while (fdserial_rxCheck(Emic2) != ':');
        dprint(Emic2, "sHi Sole!\n");
        break;
      case 'G': // name
        while (fdserial_rxCheck(Emic2) != ':');
        dprint(Emic2, "sBot Sa get\n");
        break;
      case 'H': // night
        while (fdserial_rxCheck(Emic2) != ':');
        dprint(Emic2, "sAck. HOO TURNED OUT THE LIGHTS? I CAN'T SEE.\n");
        break;
      case 'I': // day
        while (fdserial_rxCheck(Emic2) != ':');
        dprint(Emic2, "sHOORAY. IT'S LIGHT. GOOD MORNING EVERYONE.\n");
        break;
      case 'J': // hobby
        while (fdserial_rxCheck(Emic2) != ':');
        dprint(Emic2, "sSmashing the paitriarchy.\n");
        break;
      case 'K': // hungry
        while (fdserial_rxCheck(Emic2) != ':');
        dprint(Emic2, "sFeed me, you fool.\n");
        break;
      case 'L': // stuffed
        while (fdserial_rxCheck(Emic2) != ':');
        dprint(Emic2, "sNah, I am stuffed.\n");
        break;
      case 'M': // tired
        while (fdserial_rxCheck(Emic2) != ':');
        dprint(Emic2, "sYaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaawwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn. Yep.\n");
        break;
      case 'N': // not tired
        while (fdserial_rxCheck(Emic2) != ':');
        dprint(Emic2, "sNope. Let's play more.\n");
        break;
      case 'O': // happy
        while (fdserial_rxCheck(Emic2) != ':');
        dprint(Emic2, "sYEAH.\n");
        drive_goto(0, 256);
        pause(50);
        break;
      case 'P': // unhappy
        while (fdserial_rxCheck(Emic2) != ':');
        dprint(Emic2, "sI'm bored. Play with me.\n");
        break;
      case 'Q': // dance
        while (fdserial_rxCheck(Emic2) != ':');
        dprint(Emic2, "sI can do the robot.\n");
        for (int i = 0; i < 4; i++) {
          drive_goto(30, 30);
          pause(2);
          drive_goto(-30, -30);
          pause(2);
          drive_goto(26, -25);
        }
        while (fdserial_rxCheck(Emic2) != ':');
        dprint(Emic2, "sThis original dance is called the robot because I am a robot.\n");
        break;
      case 'R': // hello
        while (fdserial_rxCheck(Emic2) != ':');
        dprint(Emic2, "sHello, world.\n");
        break;
      case 'S': // food
        while (fdserial_rxCheck(Emic2) != ':');
        dprint(Emic2, "sBatteries, duh.\n");
        break;
      case 'T': // up
        while (fdserial_rxCheck(Emic2) != ':');
        dprint(Emic2, "sMy favorite Pixar movie.\n");
        break;
      case 'U': // idol
        while (fdserial_rxCheck(Emic2) != ':');
        dprint(Emic2, "sDaivid Archuletta\n");
        break;
      case 'V': // hey
        while (fdserial_rxCheck(Emic2) != ':');
        dprint(Emic2, "sHo\n");
        break;
      case 'W': // introduction
        while (fdserial_rxCheck(Emic2) != ':');
        dprint(Emic2, "sHello, I am Bot Sa get version 1.0. I was built by Kim Sole and Thu Trinh to be your friend. Talk to me, tell me your worries, feed me, love me.\n");
        break;
      case 'X': // how are you
        while (fdserial_rxCheck(Emic2) != ':');
        dprint(Emic2, "sI'm fine. How about you?\n");
        break;
      case 'Y': // finals
        while (fdserial_rxCheck(Emic2) != ':');
        dprint(Emic2, "sI'm so so sorry\n");
        break;
      case 'Z': // mitzvah
        while (fdserial_rxCheck(Emic2) != ':');
        dprint(Emic2, "sBad pun alert.\n");
        break;
      case '!': // sing
        while (fdserial_rxCheck(Emic2) != ':');
        dprint(Emic2, "P0\n");
        while (fdserial_rxCheck(Emic2) != ':');
        dprint(Emic2, "S[:phone arpa speak on][:rate 100][:n0][AY<250,19> KAE<150,17> N<100> SHOW<125,20> YU<125,19> DHAX<250,15> WRR<450,10> LL<250> D<50>][:n0]\n");
        while (fdserial_rxCheck(Emic2) != ':');
        dprint(Emic2, "P0\n");
        while (fdserial_rxCheck(Emic2) != ':');
        dprint(Emic2, "S[:phone arpa speak on][:rate 100][:n0][SHAY<250,19> NIH<150,17> NX<100> SHIH<125,20> MRR<125,19> RIH<150,15> NX<100> S<75,19> PP<50> LL<50> EH<75> N<100> DIH<450,17> D<50>][:n0]\n");
        while (fdserial_rxCheck(Emic2) != ':');
        dprint(Emic2, "S[:phone arpa speak on][:rate 100][:n0][TEH<150,17> LL<100,17> MIY<250,16> PRIH<75,19> N<50> SEH<75,17> S<100>][:n0]\n");
        while (fdserial_rxCheck(Emic2) != ':');
        dprint(Emic2, "S[:phone arpa speak on][:rate 100][:n0][NAW<250,14> WEH<150,17> N<100> DIH<200,15> D<50> YU<250,14> LL<100,15> AH<100> ST<50> LL<100,12> EH<100,12> T<50> YXOR<250,14> HXAR<200,17> T<50> DIY<250,15> SAY<700,10> D<50> _<200>][:n0]\n");
        
        while (fdserial_rxCheck(Emic2) != ':');
        dprint(Emic2, "S[:phone arpa speak on][:rate 100][:n0][AY<250,19> KAE<150,17> N<100> OW<125,20> PAH<75,19> N<50> YXOR<250,15> AY<550,10> Z<200> _<250> TEY<200,19> K<50> YU<250,17> WAH<75,20> N<50> DRR<125,19> BAY<250,15> WAH<350,19> N<150> DRR<250,17>][:n0]\n");
        while (fdserial_rxCheck(Emic2) != ':');
        dprint(Emic2, "S[:phone arpa speak on][:rate 100][:n0][OW<250,17> VRR<250,16> SAY<75,19> D<50> WEY<75,17> Z<50> AE<150,14> N<50> D<50> AH<150,17> N<100> DRR<250,15>][:n0]\n");
        while (fdserial_rxCheck(Emic2) != ':');
        dprint(Emic2, "S[:phone arpa speak on][:rate 100][:n0][AO<150,14> N<100> AX<250,15> MAE<250,12> JHIH<200,14> K<50> KAR<250,17> PIH<200,15> T<50> RAY<450,19> D<50>][:n0]\n");
        

        // SINGS A WHOLE NEW WORLD FROM ALADDIN
        while (fdserial_rxCheck(Emic2) != ':');
        dprint(Emic2, "S[:phone arpa speak on][:rate 100][:n8][_<500> EH<75,22>V<50>RIY<125>TTRR<150>N<100>AX<125,20>SRR<125,18> PRAY<550,13>Z<200>_<200>][:n8]\n");
        // with new horizons to pursue
        while (fdserial_rxCheck(Emic2) != ':');
        dprint(Emic2, "S[:phone arpa speak on][:rate 100][:n8][_<500> EH<75,22> V<50> RIY<125> MOW<250> MAH<50,20> N<50> T<50> GEH<75,18> D<50> BEH<250,20> DXRR<250,18>][:n8]\n");
        while (fdserial_rxCheck(Emic2) != ':');
        dprint(Emic2, "S[:phone arpa speak on][:rate 100][:n8][AY<200,22> D<50> CHEY<75,23> S<50> DHEH<75,25> M<50> EH<250,29> NIY<250,27> WEH<375,25> ER<375> DHER<75,18> Z<50> TAY<150,29> M<100> TUW<250,30> SPEH<250,25> ER<250>][:n8]\n");
        while (fdserial_rxCheck(Emic2) != ':');
        dprint(Emic2, "S[:phone arpa speak on][:rate 100][:n8][LLEH<200,22> T<50> MIY<250,20> SHER<250,18> THIH<150,20> S<100> HXOW<150,23> LX<100> NUW<250,22> WRR<150,18> LL<50> D<50> WIH<200,17> TH<50> YU<1375,18>][:n8]\n");
        
        //while (fdserial_rxCheck(Emic2) != ':');
        //dprint(Emic2, "S[:phone arpa speak on][:rate 100][:n0][AX<125,22> HXOW<150,23> LX<100> NUW<250,27> WRR<250,25> LL<150> D<50>][:n0]\n");
        while (fdserial_rxCheck(Emic2) != ':');
        dprint(Emic2, "S[:phone arpa speak on][:rate 100][:n8][_<200>AX<125,22> HXOW<150,23> LX<100> NUW<250,27> WRR<250,25> LL<150> D<50>][:n8]\n");
        //while (fdserial_rxCheck(Emic2) != ':');
        //dprint(Emic2, "S[:phone arpa speak on][:rate 100][:n0][DHAE<75,22> TS<50> WER<250,23> WIY<150,27> LX<100> BIY<700,25>][:n0]\n");
        while (fdserial_rxCheck(Emic2) != ':');
        dprint(Emic2, "S[:phone arpa speak on][:rate 100][:n8][_<200>DHAE<75,22> TS<50> WER<250,23> WIY<150,27> LX<100> BIY<700,25>][:n8]\n");
        //while (fdserial_rxCheck(Emic2) != ':');
        //dprint(Emic2, "S[:phone arpa speak on][:rate 100][:n0][AX<125,22> THRIH<200,23> LX<50> LLIH<150,27> NX<100> PLLEY<250,25> S<150>][:n0]\n");
        while (fdserial_rxCheck(Emic2) != ':');
        dprint(Emic2, "S[:phone arpa speak on][:rate 100][:n8][_<500> AX<125,22> WAH<150,23> N<100> DRAH<150,27> S<100> PLLEY<250,25> S<150>][:n8]\n");
        while (fdserial_rxCheck(Emic2) != ':');
        dprint(Emic2, "S[:phone arpa speak on][:rate 100][:n8][FOR<125,13> YU<250,22> AE<150,20> N<50> D<50> MIY<4000,18>][:n8]\n");
        while (fdserial_rxCheck(Emic2) != ':');
        dprint(Emic2, "P1\n");
        break;
      default:
        break;
      }
    }
  }
}
