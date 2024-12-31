#proc getdata
command: awk '{print $2, $5}' tlb_data.bat > parse_tlb_data.bat

#proc getdata
showdata: yes
delim: space
file: parse_tlb_data.bat

#proc areadef
title: TLB Size Measurements
titledetails: style=B size=14 align=C adjust=0,0.1
rectangle: 1 1 5 3
xrange: 1 1024
yrange: 0 100
xscaletype: log

#proc xaxis
label: Number of Pages
labeldetails: adjust=0,-0.1
selflocatingstubs: text
   1         1
   4         4
   16        16
   64        64
   256       256
   1024      1024

#proc yaxis
label: Time Per Access (ns)
stubs inc 20
stubdetails: align=R

#proc scatterplot
xfield: 1
yfield: 2
symbol: shape=circle fillcolor=red style=fillonly radius=0.02

#proc lineplot
xfield 1
yfield 2
linedetails: color=blue
pointsymbol: shape=diamond style=fill fillcolor=red radius=0.02
