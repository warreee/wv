
# 20150416-103618.gnuplot [generated by /home/warreee/attenload/adsparse-wave.pl]
# single gnuplot file, with two potentially independent scripts
# generates three plots: one based on integer, other based on real (SI) values
# and one bitmap overlay - and then montages them using ImageMagick

# attengrab .csv can just be centered (over t)
# -> the x=0 (t=0) will correspond to scope center
# (but .DAV/.CSV will also need extra sample alignment)

# in Linux, to see available fonts, do:
# fc-list --verbose | grep 'fullname:' | less
# the two fonts used here:
# LMSansDemiCond10-Regular or "Latin Modern Sans Demi Cond"; and Helvetica
# Helvetica doesn't even get reported on my system:
# $ fc-list --verbose | grep 'fullname:' | grep -i 'Helvetica\|Demi Cond'
#	fullname: "LM Sans Demi Cond 10 Regular"(s) "LMSansDemiCond10-Regular"(s)


print "Gnuplotting..."

## "master settings" (shared between both parts of script)

# line color - specified by linestyles
set style line 1 linetype 1 linecolor rgb "red"
set style line 2 linetype 1 linecolor rgb "green"
set style line 3 linetype 1 linecolor rgb "orange"
set style line 4 linetype 1 linecolor rgb "aquamarine"
set style line 5 linetype -1 linecolor rgb "black"
set style line 6 linetype -1 linecolor rgb "gray"
set style line 7 linetype 1 linecolor rgb "blue"


# VARIABLES ########### ########### ###########

fnbase="20150416-103618"
fn_bmp = fnbase . ".bmp"
fn_pngr = fnbase . "_r.png"
fn_pngi = fnbase . "_i.png"
fn_pngov = fnbase . "_ov.png"
fn_pngt = fnbase . "_tmp.png"
fn_pngo = fnbase . ".png"

# scope screen(shot) properties
tdiv = 1          # T/DIV (50e-9)
toffs = 0.00129999995231628        # time offset (scope) (200e-9)
vdiv1 = 1        # V/DIV CH1 (500e-3)
vdiv2 = 1         # V/DIV CH2 (50e-3)
voffs1 = -0.4         # volt offset CH1 (-1.5)
voffs2 = -0.48       # volt offset CH2 (100e-3)
sampintp  = 0.0020000001563    # (500e-12)
sampintf  = 1/sampintp
sratacqf  = 2500      # (250e6)
sratacqp  = 1/sratacqf
#osf = 1.00    # oversample factor (multiplies .CSV and .DAV time domain) # unused here
adsFactor = 1.28

# (edges of current capture and divisions)
scope_hdiv=18
scope_vdiv=8
# enforce floating point (see below)
scope_trange = scope_hdiv*tdiv*1.0    # (900e-9)
scope_left=toffs-(scope_trange/2)     # (-250e-9)
scope_right=toffs+(scope_trange/2)    # (650e-9)
scope_bottom=-voffs1-(scope_vdiv*vdiv1/2) # -500e-3
scope_top=-voffs1+(scope_vdiv*vdiv1/2)    # 3.5

totalch1Vspan=scope_vdiv*vdiv1
totalch2Vspan=scope_vdiv*vdiv2
ch1Vcoeff = adsFactor*totalch1Vspan/(2**8)
ch2Vcoeff = adsFactor*totalch2Vspan/(2**8)

voffs1int = voffs1/ch1Vcoeff  # -10
voffs2int = voffs2/ch2Vcoeff  # -12

acsv_fn = fnbase . '.csv' # '20130020-013902.csv' # from attenload tmp_wav
acsz=6000         # tmp_wav/.csv size (900)
fts=0.0020000001563         # final timestep (sampling period)
# here scope_trange could be 18*1, with acsz 16000;
# if as integer, 18/16000 would be 0 - enforce floating point
# above enforcing scope_trange to float doesn't work,
# must again here:
tdivp = 1.0*scope_trange/acsz   # sampling rate, based on scope range and numsamples in tmp (1ns)
tdivf = 1/tdivp             # freq based on that sampling rate

# just in case - not needed usually:
triglevel=440e-3
trigholdoff=100e-9

toffsamp = toffs/fts		# 0
# time finetune offset - int (samples) (depends on range)
tfoi = -164


#### extract bitmap from .png, if .bmp not present
# was -crop 480x234+10+10; now -crop 480x234+95+128

cmdstr = 'if (! test -f "'.fn_bmp.'") ; then \
  echo -n "'.fn_bmp.' not found .. " ; \
  if [ -f "'.fn_pngo.'" ] ; then \
    echo -n "'.fn_pngo.' found - extracting" ; \
    convert -crop 480x234+95+128 "'.fn_pngo.'" "'.fn_bmp.'" ; \
  else \
    echo -n "'.fn_pngo.' not found - cannot extract" ; \
  fi ; \
else \
  echo -n "'.fn_bmp.' found - using that" ; \
fi; echo'

#print cmdstr
# note - since cmdstr above uses double quotes,
# must use single quotes for bash here!:
print system("bash -c '". cmdstr ."' 2>&1")


##################################
###### plot directly with unsigned byte data

set terminal png size 840,480
set termoption enhanced
set termoption font "Helvetica, 12"

set output fn_pngi
set datafile separator ","

# set axis label
set xlabel "index" offset 0.0,0.8
set ylabel "byte unsigned value" offset 1.0,0.0


# horizontal line as functions
zeroline(x)=128
ch1offs(x)=128+voffs1int # (-10)
ch2offs(x)=128+voffs2int # (-12)

# vertical line - headless arrow
# "y" scope axis in middle:
ymI = acsz/2
set arrow from ymI,0 to ymI,255 nohead ls 5
# time offset:
toI = ymI - toffs/fts
set arrow from toI,0 to toI,255 nohead ls 6


# must use multiplot here, to have two x-axes
# and thus, must set lmargin, so both graphs match

set size 1.0,0.9      # 0.1/2 = 0.05
set bmargin 0
set lmargin 10
set yrange [0:255] # 8-bit


set multiplot

set origin 0,0.1
set xrange [0:acsz]
set xtics in
set xtics offset 0,graph 0.08
plot \
  zeroline(x) with lines notitle ls 5,\
  acsv_fn using 1:2 with lines title "ch1" ls 1, \
  "" using 1:3 with lines title "ch2" ls 2, \
  ch1offs(x) with lines notitle ls 3, \
  ch2offs(x) with lines notitle ls 4

unset arrow # if big offset, line from prev. can 'leak' in next at diff place, so reset

set origin 0,0.1
set xtics out
set xtics offset 0,graph 0.02
set xrange [-acsz/2:acsz/2-1]
#set xtics nomirror 500
set noytics
set noylabel
unset xlabel # set xlabel ""
set border 1
plot 0 notitle

set nomultiplot


### reset previous settings
#unset border # no work for default
set border    # Draw default borders:
set ytics
unset yrange


##################################
###### plot with converted real SI units

# reset # resets set style line!

set terminal png size 840,480
set termoption enhanced
set termoption font "Helvetica, 12"

set output fn_pngr
set datafile separator ","

# set axis label
set xlabel "t [s]" offset 0.0,0.1
set ylabel "U [V]" offset 1.0,0.0

# axis tics format
set format y "%.1s%c"
set format x "%.1s%c"


# horizontal line as functions
zerolineR(x)=0
# don't show real offsets; they could be way off depending on V/DIV
#ch1offsR(x)=0+(-0.4)
#ch2offsR(x)=0+(-0.48)

# "y" scope axis in middle (the +1 added to ymI so it snaps at 0):
ymR=(ymI+1)*fts
set arrow from ymR,graph 0 to ymR,graph 1 nohead ls 5
# time offset:
toR=toI*fts
set arrow from toR,graph 0 to toR,graph 1 nohead ls 6
# indicate scope range here too
set arrow from scope_left+toR,graph 0 to scope_left+toR,graph 1 nohead ls 7
set arrow from scope_right+toR,graph 0 to scope_right+toR,graph 1 nohead ls 7


# must use multiplot here, to have two x-axes
# and thus, must set lmargin, so both graphs match

set size 1.0,0.9      # 0.1/2 = 0.05
set bmargin 0
set lmargin 10
set yrange [] writeback # since we don't set explicity, must save autorange
set autoscale y

set multiplot

set origin 0,0.13
set xrange [0:acsz*fts]
set xtics out
set xtics offset 0,graph -0.03
plot \
  zerolineR(x) with lines notitle ls 5,\
  acsv_fn using ($4+tfoi*fts):5 with lines title "ch1" ls 1, \
  "" using ($4+tfoi*fts):6 with lines title "ch2" ls 2

set yrange restore # this saves the found yrange after `plot`
unset arrow # if big offset, line from prev. can 'leak' in next at diff place, so reset

set origin 0,0.13
set xtics out
set xtics offset 0,graph 0.02
set xrange [(-acsz/2)*fts:(acsz/2-1)*fts]
set noytics
set noylabel
unset xlabel # set xlabel ""
set border 1
plot GPVAL_Y_MIN notitle

set origin 0,0.13
set xtics in
set xtics offset 0,graph 0.08
# wrong to put xrange [scope_left:scope_right] here;
# as [scope_left:scope_right] could be a snippet,
# and this graph shows entire capture!
# simply move the previous scale for toffset
toRR=(acsz/2.)*fts-toR
set xrange [(-acsz/2)*fts+toRR:(acsz/2-1)*fts+toRR]
set noytics
set noylabel
unset xlabel # set xlabel ""
set border 1
plot GPVAL_Y_MIN notitle

set nomultiplot


##################################
###### plot with bitmap and data overlay

# here 840,480 remains as output png size,
# even if not set explicitly; also, make
# the height smaller - so can have gravity North in montage

set terminal png truecolor size 640,305 # size 840,480
set termoption enhanced
myfont="LMSansDemiCond10-Regular"   # LMSansDemiCond10-Regular or "Latin Modern Sans Demi Cond"
# cannot do concatenation direct in termoption line, so in separate string
myfontb="".myfont.", 12"
set termoption font myfontb

set output fn_pngov
set datafile separator ","


set autoscale
unset xtics
unset ytics
unset border
unset arrow # delete all arrows
unset object # (hopefully) delete objects?

set xrange [scope_left:scope_right]
xticstep=(scope_right-scope_left)/scope_hdiv
set xtics in scope_left,xticstep,scope_right scale 1
set yrange [scope_bottom:scope_top]
yticstep=(scope_top-scope_bottom)/scope_vdiv
set ytics in scope_bottom,yticstep,scope_top scale 1
set grid xtics ytics back linecolor rgb "magenta"
# right is only gnuplot 4.6 - without it ok w/ 4.4
#set xtics rotate by -45 offset 2.5,-1.50 right format "%+.1s%c" font myfont.',10'
set xtics rotate by -45 offset 0.0,0.0 format "%+.1s%c" font myfont.',10'
set key noenhanced

# dimensions of scope screenshot bitmap
bmp_w=480
bmp_h=234

# alpha bmp transparency [0:255]
bmp_alpha = 150
# boxes fillstyle transparent solid 0.10
box_transp = (1.-(acsz/16384.))*0.9 + 0.10

# plot string for data in transparent bitmap:
plot1au = "(($0-acsz/2.+tfoi)*fts+toffs):($5)"

# bmp_w=480 bmp_h=234 ; inside 451x201+15+14
# on plot: scope_left:scope_right and scope_bottom:scope_top!
# (so toffset is built in!)

bdx = scope_trange/(451.0-1)  # [s/pixel] /451: 1.99557e-09 vs 2.000e-9 manually
bdy = totalch1Vspan/(201.0-1) # [V/pixel] /201: 0.0199005 vs 0.02005 manually
bofx = -((scope_trange/2.0)-toffs+(15.0+0)*bdx) #-15.0*bdx # -2.8e-7
bofy = -((totalch1Vspan/2.0)+voffs1+(14.0+5)*bdy) #-14.0*bdy # -0.88

# seems `boxes fillstyle transparent solid 0.40` makes some seethroughs
# or something with bmp alpha overlay; but even without, all the same?
# because the red + blue (somehow inverted) creates a gray.. better green or orange

_plot_str = "zerolineR(x) with lines notitle ls 1,\
acsv_fn \
  using ".plot1au." with boxes fillstyle transparent solid box_transp noborder linestyle 3\
  title 'BITMAP+DATA OVERLAY: '.acsv_fn.' (CH1 only)',\
fn_bmp \
  binary array=(bmp_w,bmp_h) skip=54 format='%uchar' \
  dx=bdx dy=bdy origin=(bofx,bofy) \
  using 1:2:3:(bmp_alpha) \
  with rgbalpha t ''"

# seems actual plot in screenshot bitmap (480 × 234)
#  is at: 451x201+15+14; aspect ratio 201/451 = 0.445676
set size ratio 0.445676

eval("plot " . _plot_str)




##################################
###### montage commands

# used to be in attengrab; now here
# call ImageMagick montage via system
# and montage in `gnuplot` (easier to separate)

print "Montaging images..."
# this works in ImageMagick 6.6.2-6, but not in 6.5.7-8
#      '.fn_pngov.' -gravity Center -extent x480  \#
# must spec -extent 640x480 for 6.5

cmdstr = 'montage \
  <(montage \
    <(convert \
      '.fn_bmp.' -gravity Center -crop 640x480-10+0! -flatten  \
      bmp:-) \
    <(convert \
      '.fn_pngov.' -gravity Center -extent 640x480  \
      bmp:-) \
  -tile 1x -geometry +0+0  \
  bmp:-) \
  <(montage \
    '.fn_pngi.' \
    '.fn_pngr.' \
  -tile 1x -geometry +0+0  \
  bmp:-) \
-geometry +0+0 -border 5 \
'.fn_pngo

print cmdstr
print system('bash -c "'. cmdstr .'" 2>&1')

print "Deleting temp files ..."

delcmd = "rm"

# leave the bitmap for now
# actually, let attengrab handle it - since
# it may need to be re-taken!
# #cmdstr = delcmd ." ". fn_bmp
# #print cmdstr . "  " . system(cmdstr . " 2>&1")

cmdstr = delcmd ." ". fn_pngr
print cmdstr . "  " . system(cmdstr . " 2>&1")

cmdstr = delcmd ." ". fn_pngi
print cmdstr . "  " . system(cmdstr . " 2>&1")

cmdstr = delcmd ." ". fn_pngov
print cmdstr . "  " . system(cmdstr . " 2>&1")




# note:
# set terminal png size 840,480 # size defaults to 640x480 px
# set terminal pdf size 10,3 # size defaults to 5x3 in
# enhanced text: set termoption enhanced

# vertical line - headless arrow
# need ymin and ymax; gnuplot gives them only after plot -
# - and even then they do not correspond to end ticks
# - and even then, cannot get the arrow to show, after the second `plot`
# .. nor can I edit it anyhow; it must run before the first `plot`
# so instead of that, position y coordinates relative to graph (0 to 1)
#set arrow 1 from graph 0.5,0 to graph 0.5,1 nohead ls 5

# in multiplot, yrange should be after the size command
# note: xrange could be 2250 or 450
# so leave it to autoscale here? will be accurate since it's integer index...
# now set explicitly by script # below in multiplot

# axis tics format
# for engineering notation - 'help format specifiers':
# "A 'scientific' power is one such that the exponent is a multiple of three."

# print "Montaging images..."

# "The 'tile' size is then set to the largest dimentions
# of all the resized images, and the size actually specified."
# "by removing the 'size' component, non of the images will
# be resized, and the 'tile' size will be set to the largest
# dimensions of all the images given"
# not so simple: http://unix.stackexchange.com/questions/4046/
# can be done in one command with bash subprocess pipes (bash only)
# was: .fn_bmp.' -gravity NorthWest ; fn_pngov.' -gravity North
# can pad with -gravity Center -extent 640x480;
# but also with crop! -flatten - there have offset too!
# -geometry +2+2 can also mess up the last -border 5 !

# bmp scale worked for:
# bmp_w=480 bmp_h=234 ; inside 451x201+15+14
# tdiv = 5e-08,  toffs = 2e-07,  vdiv1 = 0.5,   voffs1 = -1.5,
# dx=2.000e-9 dy=0.02005 origin=(-2.8e-7,-0.88) for
# tspan = 18*tdiv = 18*5e-08 = 9e-07s
# vspan1 = 8*vdiv1 = 8*0.5 = 4V
# tspan/451 = 9e-07/451 = 1.99557e-09 s/pixel
# vspan1/201 = 4/201 = 0.0199005 V/pixel
# bdx=tspan/(451-1) = '9e-07/(451-1)' = 2e-09
# bdy=vspan1/(201-1) = '4/(201-1)' = 0.02
# 15*bdx = 15*2e-9 = 3e-08
# 14*bdy = 14*0.02 = 0.28
# 15*1.99557e-09 = 2.99335e-08
# 14*0.0199005 = 0.278607

