G28 ;Home all axis
M106 S0 ;EXTRUDER FAN OFF
;M117 Abbassa piano Z
M117 Move down Z plate
G90 (set positioning to absolute)
G1 Z200
M84
M117 %PRINTER%
