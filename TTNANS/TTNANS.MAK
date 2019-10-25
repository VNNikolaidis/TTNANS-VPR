#
# Borland C++ IDE generated makefile
#
.AUTODEPEND


#
# Borland C++ tools
#
IMPLIB  = Implib
BCC32   = Bcc32 +BccW32.cfg 
TLINK32 = TLink32
TLIB    = TLib
BRC32   = Brc32
TASM32  = Tasm32
#
# IDE macros
#


#
# Options
#
IDE_LFLAGS32 =  -LE:\BIN\WIN\BC4\LIB
LLATC32_ttnansdexe =  -Tpe -ap -c
RLATC32_ttnansdexe =  -IE:\BIN\WIN\BC4\INCLUDE;TTNANS -w32
BLATC32_ttnansdexe = 
LEAT_ttnansdexe = $(LLATC32_ttnansdexe)
REAT_ttnansdexe = $(RLATC32_ttnansdexe)
BEAT_ttnansdexe = $(BLATC32_ttnansdexe)

#
# Dependency List
#
Dep_ttnans = \
   ttnans.exe

ttnans : BccW32.cfg $(Dep_ttnans)
  echo MakeNode ttnans

Dep_ttnansdexe = \
   ttnans\tcon_glo.obj\
   ttnans\tglobal.obj\
   ttnans\ttnans.obj\
   ttnans\ttnans1.obj\
   ttnans\ttnans2.obj\
   ttnans\ttnaxum.obj\
   ttnans\ttnbandx.obj\
   ttnans\ttnclafi.obj\
   ttnans\ttncon_f.obj\
   ttnans\ttncon_u.obj\
   ttnans\ttndafi.obj\
   ttnans\ttndata1.obj\
   ttnans\ttndata2.obj\
   ttnans\ttneigen.obj\
   ttnans\ttnerror.obj\
   ttnans\ttnfile.obj\
   ttnans\ttnfilte.obj\
   ttnans\ttnfname.obj\
   ttnans\ttngt.obj\
   ttnans\ttnkcn.obj\
   ttnans\ttnlvqsw.obj\
   ttnans\ttnmain.obj\
   ttnans\ttnmath.obj\
   ttnans\ttnmemor.obj\
   ttnans\ttnother.obj\
   ttnans\ttnpca.obj\
   ttnans\ttnpca_2.obj\
   ttnans\ttnplbp.obj\
   ttnans\ttnprb.obj\
   ttnans\ttnprep2.obj\
   ttnans\ttnprep3.obj\
   ttnans\ttnprepr.obj\
   ttnans\ttnrand.obj\
   ttnans\ttnreprt.obj\
   ttnans\ttnreslt.obj\
   ttnans\ttnsetti.obj\
   ttnans\ttnthres.obj\
   ttnans\ttnui.obj

ttnans.exe : $(Dep_ttnansdexe)
  $(TLINK32) @&&|
 /v $(IDE_LFLAGS32) $(LEAT_ttnansdexe) +
E:\BIN\WIN\BC4\LIB\c0x32.obj+
ttnans\tcon_glo.obj+
ttnans\tglobal.obj+
ttnans\ttnans.obj+
ttnans\ttnans1.obj+
ttnans\ttnans2.obj+
ttnans\ttnaxum.obj+
ttnans\ttnbandx.obj+
ttnans\ttnclafi.obj+
ttnans\ttncon_f.obj+
ttnans\ttncon_u.obj+
ttnans\ttndafi.obj+
ttnans\ttndata1.obj+
ttnans\ttndata2.obj+
ttnans\ttneigen.obj+
ttnans\ttnerror.obj+
ttnans\ttnfile.obj+
ttnans\ttnfilte.obj+
ttnans\ttnfname.obj+
ttnans\ttngt.obj+
ttnans\ttnkcn.obj+
ttnans\ttnlvqsw.obj+
ttnans\ttnmain.obj+
ttnans\ttnmath.obj+
ttnans\ttnmemor.obj+
ttnans\ttnother.obj+
ttnans\ttnpca.obj+
ttnans\ttnpca_2.obj+
ttnans\ttnplbp.obj+
ttnans\ttnprb.obj+
ttnans\ttnprep2.obj+
ttnans\ttnprep3.obj+
ttnans\ttnprepr.obj+
ttnans\ttnrand.obj+
ttnans\ttnreprt.obj+
ttnans\ttnreslt.obj+
ttnans\ttnsetti.obj+
ttnans\ttnthres.obj+
ttnans\ttnui.obj
$<,$*
E:\BIN\WIN\BC4\LIB\bidsf.lib+
E:\BIN\WIN\BC4\LIB\import32.lib+
E:\BIN\WIN\BC4\LIB\cw32.lib

|

ttnans\tcon_glo.obj :  ttnans\tcon_glo.cpp
  $(BCC32) -c $(CEAT_ttnansdexe) -o$@ ttnans\tcon_glo.cpp

ttnans\tglobal.obj :  ttnans\tglobal.cpp
  $(BCC32) -c $(CEAT_ttnansdexe) -o$@ ttnans\tglobal.cpp

ttnans\ttnans.obj :  ttnans\ttnans.cpp
  $(BCC32) -c $(CEAT_ttnansdexe) -o$@ ttnans\ttnans.cpp

ttnans\ttnans1.obj :  ttnans\ttnans1.cpp
  $(BCC32) -c $(CEAT_ttnansdexe) -o$@ ttnans\ttnans1.cpp

ttnans\ttnans2.obj :  ttnans\ttnans2.cpp
  $(BCC32) -c $(CEAT_ttnansdexe) -o$@ ttnans\ttnans2.cpp

ttnans\ttnaxum.obj :  ttnans\ttnaxum.cpp
  $(BCC32) -c $(CEAT_ttnansdexe) -o$@ ttnans\ttnaxum.cpp

ttnans\ttnbandx.obj :  ttnans\ttnbandx.cpp
  $(BCC32) -c $(CEAT_ttnansdexe) -o$@ ttnans\ttnbandx.cpp

ttnans\ttnclafi.obj :  ttnans\ttnclafi.cpp
  $(BCC32) -c $(CEAT_ttnansdexe) -o$@ ttnans\ttnclafi.cpp

ttnans\ttncon_f.obj :  ttnans\ttncon_f.cpp
  $(BCC32) -c $(CEAT_ttnansdexe) -o$@ ttnans\ttncon_f.cpp

ttnans\ttncon_u.obj :  ttnans\ttncon_u.cpp
  $(BCC32) -c $(CEAT_ttnansdexe) -o$@ ttnans\ttncon_u.cpp

ttnans\ttndafi.obj :  ttnans\ttndafi.cpp
  $(BCC32) -c $(CEAT_ttnansdexe) -o$@ ttnans\ttndafi.cpp

ttnans\ttndata1.obj :  ttnans\ttndata1.cpp
  $(BCC32) -c $(CEAT_ttnansdexe) -o$@ ttnans\ttndata1.cpp

ttnans\ttndata2.obj :  ttnans\ttndata2.cpp
  $(BCC32) -c $(CEAT_ttnansdexe) -o$@ ttnans\ttndata2.cpp

ttnans\ttneigen.obj :  ttnans\ttneigen.cpp
  $(BCC32) -c $(CEAT_ttnansdexe) -o$@ ttnans\ttneigen.cpp

ttnans\ttnerror.obj :  ttnans\ttnerror.cpp
  $(BCC32) -c $(CEAT_ttnansdexe) -o$@ ttnans\ttnerror.cpp

ttnans\ttnfile.obj :  ttnans\ttnfile.cpp
  $(BCC32) -c $(CEAT_ttnansdexe) -o$@ ttnans\ttnfile.cpp

ttnans\ttnfilte.obj :  ttnans\ttnfilte.cpp
  $(BCC32) -c $(CEAT_ttnansdexe) -o$@ ttnans\ttnfilte.cpp

ttnans\ttnfname.obj :  ttnans\ttnfname.cpp
  $(BCC32) -c $(CEAT_ttnansdexe) -o$@ ttnans\ttnfname.cpp

ttnans\ttngt.obj :  ttnans\ttngt.cpp
  $(BCC32) -c $(CEAT_ttnansdexe) -o$@ ttnans\ttngt.cpp

ttnans\ttnkcn.obj :  ttnans\ttnkcn.cpp
  $(BCC32) -c $(CEAT_ttnansdexe) -o$@ ttnans\ttnkcn.cpp

ttnans\ttnlvqsw.obj :  ttnans\ttnlvqsw.cpp
  $(BCC32) -c $(CEAT_ttnansdexe) -o$@ ttnans\ttnlvqsw.cpp

ttnans\ttnmain.obj :  ttnans\ttnmain.cpp
  $(BCC32) -c $(CEAT_ttnansdexe) -o$@ ttnans\ttnmain.cpp

ttnans\ttnmath.obj :  ttnans\ttnmath.cpp
  $(BCC32) -c $(CEAT_ttnansdexe) -o$@ ttnans\ttnmath.cpp

ttnans\ttnmemor.obj :  ttnans\ttnmemor.cpp
  $(BCC32) -c $(CEAT_ttnansdexe) -o$@ ttnans\ttnmemor.cpp

ttnans\ttnother.obj :  ttnans\ttnother.cpp
  $(BCC32) -c $(CEAT_ttnansdexe) -o$@ ttnans\ttnother.cpp

ttnans\ttnpca.obj :  ttnans\ttnpca.cpp
  $(BCC32) -c $(CEAT_ttnansdexe) -o$@ ttnans\ttnpca.cpp

ttnans\ttnpca_2.obj :  ttnans\ttnpca_2.cpp
  $(BCC32) -c $(CEAT_ttnansdexe) -o$@ ttnans\ttnpca_2.cpp

ttnans\ttnplbp.obj :  ttnans\ttnplbp.cpp
  $(BCC32) -c $(CEAT_ttnansdexe) -o$@ ttnans\ttnplbp.cpp

ttnans\ttnprb.obj :  ttnans\ttnprb.cpp
  $(BCC32) -c $(CEAT_ttnansdexe) -o$@ ttnans\ttnprb.cpp

ttnans\ttnprep2.obj :  ttnans\ttnprep2.cpp
  $(BCC32) -c $(CEAT_ttnansdexe) -o$@ ttnans\ttnprep2.cpp

ttnans\ttnprep3.obj :  ttnans\ttnprep3.cpp
  $(BCC32) -c $(CEAT_ttnansdexe) -o$@ ttnans\ttnprep3.cpp

ttnans\ttnprepr.obj :  ttnans\ttnprepr.cpp
  $(BCC32) -c $(CEAT_ttnansdexe) -o$@ ttnans\ttnprepr.cpp

ttnans\ttnrand.obj :  ttnans\ttnrand.cpp
  $(BCC32) -c $(CEAT_ttnansdexe) -o$@ ttnans\ttnrand.cpp

ttnans\ttnreprt.obj :  ttnans\ttnreprt.cpp
  $(BCC32) -c $(CEAT_ttnansdexe) -o$@ ttnans\ttnreprt.cpp

ttnans\ttnreslt.obj :  ttnans\ttnreslt.cpp
  $(BCC32) -c $(CEAT_ttnansdexe) -o$@ ttnans\ttnreslt.cpp

ttnans\ttnsetti.obj :  ttnans\ttnsetti.cpp
  $(BCC32) -c $(CEAT_ttnansdexe) -o$@ ttnans\ttnsetti.cpp

ttnans\ttnthres.obj :  ttnans\ttnthres.cpp
  $(BCC32) -c $(CEAT_ttnansdexe) -o$@ ttnans\ttnthres.cpp

ttnans\ttnui.obj :  ttnans\ttnui.cpp
  $(BCC32) -c $(CEAT_ttnansdexe) -o$@ ttnans\ttnui.cpp

# Compiler configuration file
BccW32.cfg : 
   Copy &&|
-R
-v
-vi
-X-
-H
-IE:\BIN\WIN\BC4\INCLUDE
-H=vprcon.csm
-IE:\BIN\WIN\BC4\INCLUDE;TTNANS
-D_CONSOLE;bool=unsigned;true=1;false=0
-Og
-Ot
-WC
-4
| $@


