(G-CODE GENERATED BY FLATCAM v8.994 - www.flatcam.org - Version Date: 2020/11/7)

(Name: PCB1.TXT_cnc)
(Type: G-code from Geometry)
(Units: MM)

(Created on Thursday, 04 July 2024 at 16:33)

(This preprocessor is the default preprocessor used by FlatCAM.)
(It is made to work with MACH3 compatible motion controllers.)


(TOOLS DIAMETER: )
(Tool: 1 -> Dia: 1.0)

(FEEDRATE Z: )
(Tool: 1 -> Feedrate: 300)

(FEEDRATE RAPIDS: )
(Tool: 1 -> Feedrate Rapids: 1500)

(Z_CUT: )
(Tool: 1 -> Z_Cut: -1.7)

(Tools Offset: )
(Tool: 1 -> Offset Z: 0.0)

(Z_MOVE: )
(Tool: 1 -> Z_Move: 2)

(Z Toolchange: 15 mm)
(X,Y Toolchange: 0.0000, 0.0000 mm)
(Z Start: None mm)
(Z End: 0.5 mm)
(X,Y End: None mm)
(Steps per circle: 64)
(Preprocessor Excellon: default)

(X range:   25.0270 ...  100.1950  mm)
(Y range:    7.6280 ...   41.9020  mm)

(Spindle Speed: 0 RPM)
G21
G90
G94

G01 F300.00

M5
G00 Z15.0000
T1
G00 X0.0000 Y0.0000                
M6
(MSG, Change to Tool Dia = 1.0000 ||| Total drills for tool T1 = 33)
M0
G00 Z15.0000
M03 S1000.0

G01 F300.00
M03
G00 X30.2260 Y13.7160
G01 Z-1.7000
G01 Z0
G00 Z2.0000
G00 X25.5270 Y14.4780
G01 Z-1.7000
G01 Z0
G00 Z2.0000
G00 X25.5270 Y17.0180
G01 Z-1.7000
G01 Z0
G00 Z2.0000
G00 X25.5270 Y19.5580
G01 Z-1.7000
G01 Z0
G00 Z2.0000
G00 X30.2260 Y20.4470
G01 Z-1.7000
G01 Z0
G00 Z2.0000
G00 X36.7030 Y31.7500
G01 Z-1.7000
G01 Z0
G00 Z2.0000
G00 X44.1960 Y31.7500
G01 Z-1.7000
G01 Z0
G00 Z2.0000
G00 X52.0700 Y31.6230
G01 Z-1.7000
G01 Z0
G00 Z2.0000
G00 X51.8160 Y35.0520
G01 Z-1.7000
G01 Z0
G00 Z2.0000
G00 X52.4510 Y41.4020
G01 Z-1.7000
G01 Z0
G00 Z2.0000
G00 X83.5660 Y31.3690
G01 Z-1.7000
G01 Z0
G00 Z2.0000
G00 X95.5040 Y30.7340
G01 Z-1.7000
G01 Z0
G00 Z2.0000
G00 X95.5275 Y33.1470
G01 Z-1.7000
G01 Z0
G00 Z2.0000
G00 X99.6950 Y35.5670
G01 Z-1.7000
G01 Z0
G00 Z2.0000
G00 X99.6950 Y33.0670
G01 Z-1.7000
G01 Z0
G00 Z2.0000
G00 X99.6950 Y30.5670
G01 Z-1.7000
G01 Z0
G00 Z2.0000
G00 X99.6950 Y28.0670
G01 Z-1.7000
G01 Z0
G00 Z2.0000
G00 X99.6950 Y19.6920
G01 Z-1.7000
G01 Z0
G00 Z2.0000
G00 X99.6950 Y17.1920
G01 Z-1.7000
G01 Z0
G00 Z2.0000
G00 X99.6950 Y14.6920
G01 Z-1.7000
G01 Z0
G00 Z2.0000
G00 X99.6950 Y12.1920
G01 Z-1.7000
G01 Z0
G00 Z2.0000
G00 X94.6150 Y14.7320
G01 Z-1.7000
G01 Z0
G00 Z2.0000
G00 X94.6150 Y19.2405
G01 Z-1.7000
G01 Z0
G00 Z2.0000
G00 X92.0750 Y20.7010
G01 Z-1.7000
G01 Z0
G00 Z2.0000
G00 X86.1060 Y21.2090
G01 Z-1.7000
G01 Z0
G00 Z2.0000
G00 X81.9150 Y8.2550
G01 Z-1.7000
G01 Z0
G00 Z2.0000
G00 X77.5970 Y8.1280
G01 Z-1.7000
G01 Z0
G00 Z2.0000
G00 X73.2790 Y11.5570
G01 Z-1.7000
G01 Z0
G00 Z2.0000
G00 X75.4380 Y13.8430
G01 Z-1.7000
G01 Z0
G00 Z2.0000
G00 X74.6760 Y18.7960
G01 Z-1.7000
G01 Z0
G00 Z2.0000
G00 X52.0700 Y16.7640
G01 Z-1.7000
G01 Z0
G00 Z2.0000
G00 X44.1960 Y16.8910
G01 Z-1.7000
G01 Z0
G00 Z2.0000
G00 X36.7030 Y16.8910
G01 Z-1.7000
G01 Z0
G00 Z2.0000
M05
G00 Z0.50


